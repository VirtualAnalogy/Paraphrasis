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

#ifndef __PluginParameters_ConcurrentParameterSet_h__
#define __PluginParameters_ConcurrentParameterSet_h__

#include "ParameterSet.h"
#include "Parameter.h"
#include "EventDispatcher.h"

	namespace teragon {

#if PLUGINPARAMETERS_MULTITHREADED
	static void asyncDispatcherCallback(void *arg) {
	    EventDispatcher *dispatcher = reinterpret_cast<EventDispatcher *>(arg);
	    dispatcher->start();

	    while(!dispatcher->isKilled()) {
		// WARNING: Deadlock can occur here
		// If this thread is interrupted between these two lines, and the main thread
		// exits (ie, the ConcurrentParameterSet is destroyed directly after creation),
		// then the corresponding notify() call thrown by kill() will not be received.
		// To avoid this problem, you should not destroy a ConcurrentParameterSet right
		// after creating it.
		dispatcher->wait();
		// This thread can be notified both in case of an event callback or when the
		// thread should join and exit. In the second case, we should not attempt to
		// run process(), as bad things may happen.
		if(!dispatcher->isKilled()) {
		    dispatcher->process();
		}
	    }
	}
#endif // PLUGINPARAMETERS_MULTITHREADED

	class ConcurrentParameterSet : public ParameterSet, public EventScheduler {
#if PLUGINPARAMETERS_MULTITHREADED
	public:
	    /**
	     * Create a new parameter set which can be used by multiple threads. This
	     * assumes that there is one high-priority thread which is executed from a
	     * runloop, and one or more low-priority threads for background tasks or GUI.
	     *
	     * Simply using this class in place of ParameterSet does not guarantee
	     * thread-safe code. See the top-level README for information and examples
	     * regarding correct usage of this class.
	     */
	    explicit ConcurrentParameterSet() : 
		    ParameterSet(), 
		    EventScheduler(),
		    asyncDispatcher(this, false),
		    realtimeDispatcher(this, true),
		    asyncDispatcherThread(asyncDispatcherCallback, &asyncDispatcher),
		    realtimeEventLoopPaused(false) 
		{

			// Wait for the async dispatcher thread to be fully started.
			while(!asyncDispatcher.isStarted()) {
			    sleep(10);
			}
		    }

		    virtual ~ConcurrentParameterSet() {
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
		     * Set a parameter's value. When PLUGINPARAMETERS_MULTITHREADED is set,
		     * then this method must be used rather than Parameter::set(). The actual
		     * operation will be dispatched to the main thread and executed there, and
		     * any asynchronous observers will be notified afterwards. This means that
		     * there can a some small delay before other asynchronous observers receive
		     * their notifications. Realtime observers, however, will be notified during
		     * the next call to processRealtimeEvents().
		     *
		     * @param name Parameter name. No error checking is done here, you must ensure
		     *             that the name is valid. Otherwise, this call will fail silently.
		     * @param value New value
		     * @param sender Sending object (can be NULL). If non-NULL, then this object
		     *               will *not* receive notifications on the observer callback,
		     *               since presumably this object is pushing state to other
		     *               observers.
		     */
		    virtual void set(const ParameterString &name, const ParameterValue value,
				     ParameterObserver *sender = NULL) {
			Parameter *parameter = get(name);
			if(parameter != NULL) {
			    set(parameter, value, sender);
			}
		    }

		    /**
		     * Set a parameter's value. When PLUGINPARAMETERS_MULTITHREADED is set,
		     * then this method must be used rather than Parameter::set(). The actual
		     * operation will be dispatched to the main thread and executed there, and
		     * any asynchronous observers will be notified afterwards. This means that
		     * there can a some small delay before other asynchronous observers receive
		     * their notifications. Realtime observers, however, will be notified during
		     * the next call to processRealtimeEvents().
		     *
		     * @param index Parameter index. No error checking is done here, you must
		     *              ensure that the index is valid.
		     * @param value New value
		     * @param sender Sending object (can be NULL). If non-NULL, then this object
		     *               will *not* receive notifications on the observer callback,
		     *               since presumably this object is pushing state to other
		     *               observers.
		     */
		    virtual void set(const size_t index, const ParameterValue value,
				     ParameterObserver *sender = NULL) {
			return set(parameterList.at(index), value, sender);
		    }

		    /**
		     * Set a parameter's value. When PLUGINPARAMETERS_MULTITHREADED is set,
		     * then this method must be used rather than Parameter::set(). The actual
		     * operation will be dispatched to the main thread and executed there, and
		     * any asynchronous observers will be notified afterwards. This means that
		     * there can a some small delay before other asynchronous observers receive
		     * their notifications. Realtime observers, however, will be notified during
		     * the next call to processRealtimeEvents().
		     *
		     * @param parameter Parameter
		     * @param value New value
		     * @param sender Sending object (can be NULL). If non-NULL, then this object
		     *               will *not* receive notifications on the observer callback,
		     *               since presumably this object is pushing state to other
		     *               observers.
		     */
		    virtual void set(Parameter *parameter, const ParameterValue value,
				     ParameterObserver *sender = NULL) {
			scheduleEvent(new Event(parameter, value, true, sender));
		    }

		    /**
		     * Set a parameter's value. When PLUGINPARAMETERS_MULTITHREADED is set,
		     * then this method must be used rather than Parameter::set(). The actual
		     * operation will be dispatched to the main thread and executed there, and
		     * any asynchronous observers will be notified afterwards. This means that
		     * there can a some small delay before other asynchronous observers receive
		     * their notifications. Realtime observers, however, will be notified during
		     * the next call to processRealtimeEvents().
		     *
		     * @param name Parameter name. No error checking is done here, you must ensure
		     *             that the name is valid. Otherwise, this call will fail silently.
		     * @param value New value
		     * @param sender Sending object (can be NULL). If non-NULL, then this object
		     *               will *not* receive notifications on the observer callback,
		     *               since presumably this object is pushing state to other
		     *               observers.
		     */
		    virtual void setScaled(const ParameterString &name, const ParameterValue value,
					   ParameterObserver *sender = NULL) {
			Parameter *parameter = get(name);
			if(parameter != NULL) {
			    setScaled(parameter, value, sender);
			}
		    }

		    /**
		     * Set a parameter's value. When PLUGINPARAMETERS_MULTITHREADED is set,
		     * then this method must be used rather than Parameter::set(). The actual
		     * operation will be dispatched to the main thread and executed there, and
		     * any asynchronous observers will be notified afterwards. This means that
		     * there can a some small delay before other asynchronous observers receive
		     * their notifications. Realtime observers, however, will be notified during
		     * the next call to processRealtimeEvents().
		     *
		     * @param index Parameter index. No error checking is done here, you must
		     *              ensure that the index is valid.
		     * @param value New value
		     * @param sender Sending object (can be NULL). If non-NULL, then this object
		     *               will *not* receive notifications on the observer callback,
		     *               since presumably this object is pushing state to other
		     *               observers.
		     */
		    virtual void setScaled(const size_t index, const ParameterValue value,
					   ParameterObserver *sender = NULL) {
			return setScaled(parameterList.at(index), value, sender);
		    }

		    /**
		     * Set a parameter's value. When PLUGINPARAMETERS_MULTITHREADED is set,
		     * then this method must be used rather than Parameter::set(). The actual
		     * operation will be dispatched to the main thread and executed there, and
		     * any asynchronous observers will be notified afterwards. This means that
		     * there can a some small delay before other asynchronous observers receive
		     * their notifications. Realtime observers, however, will be notified during
		     * the next call to processRealtimeEvents().
		     *
		     * @param parameter Parameter
		     * @param value New value
		     * @param sender Sending object (can be NULL). If non-NULL, then this object
		     *               will *not* receive notifications on the observer callback,
		     *               since presumably this object is pushing state to other
		     *               observers.
		     */
		    virtual void setScaled(Parameter *parameter, const ParameterValue value,
					   ParameterObserver *sender = NULL) {
			scheduleEvent(new ScaledEvent(parameter, value, true, sender));
		    }

		    /**
		     * Set a parameter's value. When PLUGINPARAMETERS_MULTITHREADED is set,
		     * then this method must be used rather than Parameter::set(). The actual
		     * operation will be dispatched to the main thread and executed there, and
		     * any asynchronous observers will be notified afterwards. This means that
		     * there can a some small delay before other asynchronous observers receive
		     * their notifications. Realtime observers, however, will be notified during
		     * the next call to processRealtimeEvents().
		     *
		     * @param name Parameter name. No error checking is done here, you must ensure
		     *             that the name is valid. Otherwise, this call will fail silently.
		     * @param value New data value
		     * @param dataSize Data size, in bytes
		     * @param sender Sending object (can be NULL). If non-NULL, then this object
		     *               will *not* receive notifications on the observer callback,
		     *               since presumably this object is pushing state to other
		     *               observers.
		     */
		    virtual void setData(const ParameterString &name, const void *data,
					 const size_t dataSize, ParameterObserver *sender = NULL) {
			Parameter *parameter = get(name);
			if(parameter != NULL) {
			    setData(parameter, data, dataSize, sender);
			}
		    }

		    /**
		     * Set a parameter's value. When PLUGINPARAMETERS_MULTITHREADED is set,
		     * then this method must be used rather than Parameter::set(). The actual
		     * operation will be dispatched to the main thread and executed there, and
		     * any asynchronous observers will be notified afterwards. This means that
		     * there can a some small delay before other asynchronous observers receive
		     * their notifications. Realtime observers, however, will be notified during
		     * the next call to processRealtimeEvents().
		     *
		     * @param index Parameter index. No error checking is done here, you must
		     *              ensure that the index is valid.
		     * @param value New data value
		     * @param dataSize Data size, in bytes
		     * @param sender Sending object (can be NULL). If non-NULL, then this object
		     *               will *not* receive notifications on the observer callback,
		     *               since presumably this object is pushing state to other
		     *               observers.
		     */
		    virtual void setData(const size_t index, const void *data,
					 const size_t dataSize, ParameterObserver *sender = NULL) {
			return setData(parameterList.at(index), data, dataSize, sender);
		    }

		    /**
		     * Set a parameter's value. When PLUGINPARAMETERS_MULTITHREADED is set,
		     * then this method must be used rather than Parameter::set(). The actual
		     * operation will be dispatched to the main thread and executed there, and
		     * any asynchronous observers will be notified afterwards. This means that
		     * there can a some small delay before other asynchronous observers receive
		     * their notifications. Realtime observers, however, will be notified during
		     * the next call to processRealtimeEvents().
		     *
		     * @param parameter Parameter
		     * @param value New data value
		     * @param dataSize Data size, in bytes
		     * @param sender Sending object (can be NULL). If non-NULL, then this object
		     *               will *not* receive notifications on the observer callback,
		     *               since presumably this object is pushing state to other
		     *               observers.
		     */
		    virtual void setData(Parameter *parameter, const void *data,
					 const size_t dataSize, ParameterObserver *sender = NULL) {
			DataParameter *dataParameter = dynamic_cast<DataParameter *>(parameter);
			if(dataParameter != NULL) {
			    scheduleEvent(new DataEvent(dataParameter, data, dataSize, true, sender));
			}
		    }

		    /**
		     * Pause normal processing of realtime events. When this method is called,
		     * then events will be executed on both the realtime and asynchronous
		     * threads immediately after scheduling them. This is necessary so that the
		     * GUI still looks and behaves normally when even when audio processing
		     * is stopped.
		     *
		     * This method should be called by the plugin when the transport changes
		     * from playback to paused/stopped. Leaving a ConcurrentParameterSet paused
		     * while playback is active may result in priority inversion, be careful!
		     */
		    virtual void pause() {
			realtimeEventLoopPaused = true;
		    }

		    /**
		     * Resume normal processing of realtime events. This method should be
		     * called by the plugin when the transport changes from pause/stopped
		     * to playing.
		     */
		    virtual void resume() {
			realtimeEventLoopPaused = false;
	    }

	    static void sleep(const unsigned long milliseconds) {
		std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
	    }

	protected:
	    virtual void scheduleEvent(Event *event) {
		if(!asyncDispatcher.isStarted()) {
		    return;
		}
		else if(asyncDispatcher.isKilled()) {
		    return;
		}

		if(event->isRealtime) {
		    realtimeDispatcher.add(event);
		}
		else {
		    asyncDispatcher.add(event);
		    asyncDispatcher.notify();
		}

		if(realtimeEventLoopPaused) {
		    processRealtimeEvents();
		}
	    }

	private:
	    EventDispatcher asyncDispatcher;
	    EventDispatcher realtimeDispatcher;
	    EventDispatcherThread asyncDispatcherThread;
    bool realtimeEventLoopPaused;

#endif // PLUGINPARAMETERS_MULTITHREADED
};

} // namespace teragon

#endif // __PluginParameters_ConcurrentParameterSet_h__
