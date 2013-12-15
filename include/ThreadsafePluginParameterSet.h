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
#define __ThreadsafePluginParameterSet_h__

#if ENABLE_MULTITHREADED
#include "PluginParameterSet.h"
#include "PluginParameters.h"
#include "EventDispatcher.h"

#if HAVE_TESTRUNNER
#define SLEEP_AFTER_CREATION_MS 100
#endif

#ifndef SLEEP_AFTER_CREATION_MS
#define SLEEP_AFTER_CREATION_MS 0
#endif

namespace teragon {

static void asyncDispatcherCallback(void *arg) {
  EventDispatcher* dispatcher = reinterpret_cast<EventDispatcher*>(arg);
  EventDispatcherLockGuard guard(dispatcher->getMutex());
  while(!dispatcher->isKilled()) {
    dispatcher->wait();
    // This thread can be notified both in case of an event callback or when the
    // thread should join and exit. In the second case, we should not attempt to
    // run process(), as bad things may happen.
    if(!dispatcher->isKilled()) {
      dispatcher->process();
    }
  }
}

class ThreadsafePluginParameterSet : public PluginParameterSet, public EventScheduler {
public:
  /**
   * Create a new parameter set which can be used by multiple threads. This
   * assumes that there is one high-priority thread which is executed from a
   * runloop, and one or more low-priority threads for background tasks or GUI.
   *
   * Simply using this class in place of PluginParameterSet does not guarantee
   * thread-safe code. See the top-level README for information and examples
   * regarding correct usage of this class.
   */
  explicit ThreadsafePluginParameterSet() : PluginParameterSet(), EventScheduler(),
    asyncDispatcher(this, false), realtimeDispatcher(this, true),
    asyncDispatcherThread(asyncDispatcherCallback, &asyncDispatcher) {
    asyncDispatcherThread.set_name("PluginParameterSetScheduler");
    asyncDispatcherThread.detach();
    asyncDispatcherThread.set_low_priority();

    /*
     * It is very difficult to guarantee that the async callback thread will be
     * ready and waiting on the condition variable by the time this constructor
     * exits, at least without forcing scheduleEvent() to have a mutex.
     *
     * Therefore scheduling parameter changes from the async thread immediately
     * after constructing the set may result in these events not being applied.
     * This effectively means that sending such events after construction is NOT
     * recommended. However if you absolutely need this (and do you, really?),
     * then you can define SLEEP_AFTER_CREATION_MS to some non-zero value to
     * allow time for the async thread to finish initializing.
     *
     * However, is is always the case with sleeping code, this is NOT guaranteed
     * to allow one to schedule async events right away, it just reduces the
     * likelihood of that event occurring. Thus, the recommended behavior is to
     * not schedule parameter changes directly after constructing the set.
     */
    if(SLEEP_AFTER_CREATION_MS > 0) {
      usleep(SLEEP_AFTER_CREATION_MS * 1000);
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

  /**
   * Set a parameter's value. When ENABLE_MULTITHREADED is set, then this method
   * must be used rather than PluginParameter::set(). The actual operation will
   * be redispatched to the main thread and executed there, and any async
   * observers will be notified afterwards. This means that there can be some
   * small delay before other async observers receive their notifications.
   *
   * @param name Parameter name
   * @param value New value
   * @param sender Sending object (can be NULL). If non-NULL, then this object
   *               will *not* receive notifications on the observer callback,
   *               since presumably this object is pushing state to other
   *               observers.
   */
  virtual void set(const ParameterString& name, const ParameterValue value,
    PluginParameterObserver* sender = NULL) {
    PluginParameter* parameter = get(name);
    if(parameter != NULL) {
      set(parameter, value, sender);
    }
  }

  /**
   * Set a parameter's value. When ENABLE_MULTITHREADED is set, then this method
   * must be used rather than PluginParameter::set(). The actual operation will
   * be redispatched to the main thread and executed there, and any async
   * observers will be notified afterwards. This means that there can be some
   * small delay before other async observers receive their notifications.
   *
   * @param index Parameter index
   * @param value New value
   * @param sender Sending object (can be NULL). If non-NULL, then this object
   *               will *not* receive notifications on the observer callback,
   *               since presumably this object is pushing state to other
   *               observers.
   */
  virtual void set(const int index, const ParameterValue value,
    PluginParameterObserver* sender = NULL) {
    return set(parameterList.at(index), value, sender);
  }

  /**
   * Set a parameter's value. When ENABLE_MULTITHREADED is set, then this method
   * must be used rather than PluginParameter::set(). The actual operation will
   * be redispatched to the main thread and executed there, and any async
   * observers will be notified afterwards. This means that there can be some
   * small delay before other async observers receive their notifications.
   *
   * @param parameter Parameter
   * @param value New value
   * @param sender Sending object (can be NULL). If non-NULL, then this object
   *               will *not* receive notifications on the observer callback,
   *               since presumably this object is pushing state to other
   *               observers.
   */
  virtual void set(PluginParameter* parameter, const ParameterValue value,
    PluginParameterObserver* sender = NULL) {
    scheduleEvent(new Event(parameter, value, true, sender));
  }

  /**
   * Set a parameter's value. When ENABLE_MULTITHREADED is set, then this method
   * must be used rather than PluginParameter::set(). The actual operation will
   * be redispatched to the main thread and executed there, and any async
   * observers will be notified afterwards. This means that there can be some
   * small delay before other async observers receive their notifications.
   *
   * @param name Parameter name
   * @param value New value
   * @param sender Sending object (can be NULL). If non-NULL, then this object
   *               will *not* receive notifications on the observer callback,
   *               since presumably this object is pushing state to other
   *               observers.
   */
  virtual void setScaled(const ParameterString& name, const ParameterValue value,
    PluginParameterObserver* sender = NULL) {
    PluginParameter* parameter = get(name);
    if(parameter != NULL) {
      setScaled(parameter, value, sender);
    }
  }

  /**
   * Set a parameter's value. When ENABLE_MULTITHREADED is set, then this method
   * must be used rather than PluginParameter::set(). The actual operation will
   * be redispatched to the main thread and executed there, and any async
   * observers will be notified afterwards. This means that there can be some
   * small delay before other async observers receive their notifications.
   *
   * @param index Parameter index
   * @param value New value
   * @param sender Sending object (can be NULL). If non-NULL, then this object
   *               will *not* receive notifications on the observer callback,
   *               since presumably this object is pushing state to other
   *               observers.
   */
  virtual void setScaled(const int index, const ParameterValue value,
    PluginParameterObserver* sender = NULL) {
    return setScaled(parameterList.at(index), value, sender);
  }

  /**
   * Set a parameter's value. When ENABLE_MULTITHREADED is set, then this method
   * must be used rather than PluginParameter::set(). The actual operation will
   * be redispatched to the main thread and executed there, and any async
   * observers will be notified afterwards. This means that there can be some
   * small delay before other async observers receive their notifications.
   *
   * @param parameter Parameter
   * @param value New value
   * @param sender Sending object (can be NULL). If non-NULL, then this object
   *               will *not* receive notifications on the observer callback,
   *               since presumably this object is pushing state to other
   *               observers.
   */
  virtual void setScaled(PluginParameter* parameter, const ParameterValue value,
    PluginParameterObserver* sender = NULL) {
    scheduleEvent(new ScaledEvent(parameter, value, true, sender));
  }

  // TODO: Should disappear with templated version of PluginParameter
  /**
   * Set a parameter's value. When ENABLE_MULTITHREADED is set, then this method
   * must be used rather than PluginParameter::set(). The actual operation will
   * be redispatched to the main thread and executed there, and any async
   * observers will be notified afterwards. This means that there can be some
   * small delay before other async observers receive their notifications.
   *
   * @param name Parameter name
   * @param value New string value
   * @param sender Sending object (can be NULL). If non-NULL, then this object
   *               will *not* receive notifications on the observer callback,
   *               since presumably this object is pushing state to other
   *               observers.
   */
  virtual void set(const ParameterString& name, const ParameterString value,
    PluginParameterObserver* sender = NULL) {
    PluginParameter* parameter = get(name);
    if(parameter != NULL) {
      set(parameter, value, sender);
    }
  }

  // TODO: Should disappear with templated version of PluginParameter
  /**
   * Set a parameter's value. When ENABLE_MULTITHREADED is set, then this method
   * must be used rather than PluginParameter::set(). The actual operation will
   * be redispatched to the main thread and executed there, and any async
   * observers will be notified afterwards. This means that there can be some
   * small delay before other async observers receive their notifications.
   *
   * @param index Parameter index
   * @param value New string value
   * @param sender Sending object (can be NULL). If non-NULL, then this object
   *               will *not* receive notifications on the observer callback,
   *               since presumably this object is pushing state to other
   *               observers.
   */
  virtual void set(const int index, const ParameterString value,
    PluginParameterObserver* sender = NULL) {
    return set(parameterList.at(index), value, sender);
  }

  // TODO: Should disappear with templated version of PluginParameter
  /**
   * Set a parameter's value. When ENABLE_MULTITHREADED is set, then this method
   * must be used rather than PluginParameter::set(). The actual operation will
   * be redispatched to the main thread and executed there, and any async
   * observers will be notified afterwards. This means that there can be some
   * small delay before other async observers receive their notifications.
   *
   * @param parameter Parameter
   * @param value New string value
   * @param sender Sending object (can be NULL). If non-NULL, then this object
   *               will *not* receive notifications on the observer callback,
   *               since presumably this object is pushing state to other
   *               observers.
   */
  virtual void set(PluginParameter* parameter, const ParameterString value,
    PluginParameterObserver* sender = NULL) {
    StringParameter* stringParameter = dynamic_cast<StringParameter*>(parameter);
    if(stringParameter != NULL) {
      scheduleEvent(new StringEvent(stringParameter, value, true, sender));
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
  EventDispatcherThread asyncDispatcherThread;
};
} // namespace teragon

#endif // ENABLE_MULTITHREADED
#endif // __ThreadsafePluginParameterSet_h__
