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

#ifndef __ThreadsafePluginParameterSet_h__
#define	__ThreadsafePluginParameterSet_h__

#if ENABLE_MULTITHREADED
#include "PluginParameterSet.h"
#include "PluginParameters.h"
#include "EventDispatcher.h"

namespace teragon {

class AsyncDispatcherCallbackData {
public:
  EventDispatcher& dispatcher;
  EventDispatcherConditionVariable asyncInitCond;
  EventDispatcherMutex asyncInitMutex;
  volatile bool initFinished;

  AsyncDispatcherCallbackData(EventDispatcher& d) : dispatcher(d), initFinished(false) {}
  virtual ~AsyncDispatcherCallbackData() {}
};

static void asyncDispatcherCallback(void *arg) {
  AsyncDispatcherCallbackData* data = reinterpret_cast<AsyncDispatcherCallbackData*>(arg);

  {
    // Notify the main thread that it can return. At this point, we are ready to
    // process data. Sent from either thread.
    EventDispatcherLockGuard initGuard(data->asyncInitMutex);
    data->initFinished = true;
    data->asyncInitMutex.unlock();
    data->asyncInitCond.notify_all();
  }

  EventDispatcherLockGuard guard(data->dispatcher.getMutex());
  while(!data->dispatcher.isKilled()) {
    data->dispatcher.wait();
    // This thread can be notified both in case of an event callback or when the
    // thread should join and exit. In the second case, we should not attempt to
    // run process(), as bad things may happen.
    if(!data->dispatcher.isKilled()) {
      data->dispatcher.process();
    }
  }
}

class ThreadsafePluginParameterSet : public PluginParameterSet, public EventScheduler {
public:
  explicit ThreadsafePluginParameterSet() : PluginParameterSet(), EventScheduler(),
    asyncDispatcher(this, false), realtimeDispatcher(this, true),
    asyncCallbackData(asyncDispatcher),
    asyncDispatcherThread(asyncDispatcherCallback, &asyncCallbackData) {
    // This looks a bit strange, but it's necessary in case the main thread is
    // very short lived. This can occur during unit tests or if a plugin is
    // opened and then closed directly afterwards. This means that the main
    // thread can actually exit before the async thread is even started, causing
    // all sorts of havoc during destruction.
    //
    // Likewise, if the main thread's process() method is called before the
    // async thread is started, some observers may not be notified of parameter
    // changes scheduled immediately after initialization.
    //
    // Therefore the constructor must initialize itself synchronously by waiting
    // until the async thread is completely started before returning.
    EventDispatcherLockGuard initLockGuard(asyncCallbackData.asyncInitMutex);
    asyncDispatcherThread.set_name("PluginParameterSetScheduler");
    asyncDispatcherThread.detach();
    asyncDispatcherThread.set_low_priority();
    while(!asyncCallbackData.initFinished) {
      asyncCallbackData.asyncInitCond.wait(asyncCallbackData.asyncInitMutex);
    }
  }

  virtual ~ThreadsafePluginParameterSet() {
    asyncDispatcher.kill();
    asyncDispatcherThread.join();
  }

  /**
   * Process events on the realtime dispatcher. This method should be called
   * in the plugin's process() function.
   */
  virtual void processRealtimeEvents() {
    realtimeDispatcher.process();
  }

  virtual void set(const ParameterString& name, const ParameterValue value,
    const bool realtime = false, PluginParameterObserver* sender = NULL) {
    PluginParameter* parameter = get(name);
    if(parameter != NULL) {
      set(parameter, value, realtime, sender);
    }
  }

  virtual void set(const int index, const ParameterValue value,
    bool realtime = false, PluginParameterObserver* sender = NULL) {
    return set(parameterList.at(index), value, realtime, sender);
  }

  virtual void set(PluginParameter* parameter, const ParameterValue value,
    bool realtime = false, PluginParameterObserver* sender = NULL) {
    scheduleEvent(new Event(parameter, value, realtime, sender));
  }

  // TODO: Should disappear with templated version of PluginParameter
  virtual void set(const ParameterString& name, const ParameterString value,
    const bool realtime = false, PluginParameterObserver* sender = NULL) {
    PluginParameter* parameter = get(name);
    if(parameter != NULL) {
      set(parameter, value, realtime, sender);
    }
  }

  virtual void set(const int index, const ParameterString value,
    bool realtime = false, PluginParameterObserver* sender = NULL) {
    return set(parameterList.at(index), value, realtime, sender);
  }

  virtual void set(PluginParameter* parameter, const ParameterString value,
    bool realtime = false, PluginParameterObserver* sender = NULL) {
    StringParameter* stringParameter = dynamic_cast<StringParameter*>(parameter);
    if(stringParameter != NULL) {
      scheduleEvent(new StringEvent(stringParameter, value, realtime, sender));
    }
  }

protected:
  virtual void scheduleEvent(Event* event) {
    if(event->isRealtime) {
      realtimeDispatcher.add(event);
    }
    else {
      asyncDispatcher.add(event);
      asyncDispatcher.notify();
    }
  }

private:
  EventDispatcher asyncDispatcher;
  EventDispatcher realtimeDispatcher;
  AsyncDispatcherCallbackData asyncCallbackData;
  EventDispatcherThread asyncDispatcherThread;
};
} // namespace teragon

#endif // ENABLE_MULTITHREADED
#endif // __ThreadsafePluginParameterSet_h__
