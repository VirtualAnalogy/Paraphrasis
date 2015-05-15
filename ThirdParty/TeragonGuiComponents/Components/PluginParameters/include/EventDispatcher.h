/*
 * Copyright (c) 2013 Teragon Audio. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */


#ifndef __PluginParameters_EventDispatcher_h__
#define __PluginParameters_EventDispatcher_h__

#if PLUGINPARAMETERS_MULTITHREADED
#include "readerwriterqueue/readerwriterqueue.h"
#include <thread>
#include <mutex>
#include <condition_variable>
#endif

#include "Event.h"
#include "Parameter.h"

namespace teragon {

#if PLUGINPARAMETERS_MULTITHREADED
typedef std::thread EventDispatcherThread;
typedef std::lock_guard<std::mutex> EventDispatcherLockGuard;
typedef std::mutex EventDispatcherMutex;
typedef std::condition_variable EventDispatcherConditionVariable;
#endif

class EventScheduler {
public:
    EventScheduler() {}
    virtual ~EventScheduler() {}

    virtual void scheduleEvent(Event *event) = 0;
};

class EventDispatcher {
#if PLUGINPARAMETERS_MULTITHREADED
public:
    EventDispatcher(EventScheduler *s, bool realtime) :
    eventQueue(), scheduler(s), isRealtime(realtime), started(false), killed(false) {}

    virtual ~EventDispatcher() {}

    void add(Event *event) {
        eventQueue.enqueue(event);
    }

    void process() {
        Event *event = NULL;
        while(eventQueue.try_dequeue(event)) {
            if(event != NULL) {
                // Only execute parameter changes on the realtime thread
                if(isRealtime) {
                    event->apply();
                }

                // Notify all observers of the same type
                for(size_t i = 0; i < event->parameter->getNumObservers(); ++i) {
                    ParameterObserver *observer = event->parameter->getObserver(i);
                    if(observer != NULL &&
                        observer->isRealtimePriority() == isRealtime &&
                        observer != event->sender) {
                        observer->onParameterUpdated(event->parameter);
                    }
                }

                if(isRealtime) {
                    // Re-dispatch the event to the async thread
                    event->isRealtime = false;
                    scheduler->scheduleEvent(event);
                }
                else {
                    // If this is the async thread, then all observers know about the
                    // parameter change and this event can be deleted.
                    delete event;
                }
            }
            event = NULL;
        }
    }

    volatile bool isStarted() const {
        return started;
    }

    void start() {
        started = true;
    }

    volatile bool isKilled() const {
        return killed;
    }

    void kill() {
        killed = true;
        notify();
    }

    void notify() {
        waitLock.notify_all();
    }

    void wait() {
        std::unique_lock<std::mutex> lock(mutex);
        waitLock.wait(lock);
    }

private:
    std::condition_variable waitLock;
    EventDispatcherMutex mutex;
    moodycamel::ReaderWriterQueue<Event *> eventQueue;

    EventScheduler *scheduler;
    const bool isRealtime;
    volatile bool started;
    volatile bool killed;

#endif // PLUGINPARAMETERS_MULTITHREADED
};

} // namespace teragon

#endif // __PluginParameters_EventDispatcher_h__
