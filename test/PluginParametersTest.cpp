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

#include <stdio.h>
#include <stdlib.h>
#include "TestRunner.h"
#include "PluginParameters.h"

#if ENABLE_MULTITHREADED
// Simulate a realtime audio system by sleeping a bit after processing events.
// Here we assume 11ms sleep per block, which is approximately the amount of
// time needed to process 512 samples at 44100Hz sample rate.
// Several blocks may be processed before async changes are received, but here
// we only want to ensure that the event was routed from async->realtime.
#define SLEEP_TIME_PER_BLOCK_MS 11
#define TEST_NUM_BLOCKS_TO_PROCESS 10
#endif

namespace teragon {

////////////////////////////////////////////////////////////////////////////////
// Observers
////////////////////////////////////////////////////////////////////////////////

class TestObserver : public PluginParameterObserver {
public:
  TestObserver() : PluginParameterObserver(), notified(false) {}
  bool isRealtimePriority() const { return true; }
  void onParameterUpdated(const PluginParameter* parameter) {
    notified = true;
  }
  bool notified;
};

class TestCounterObserver : public PluginParameterObserver {
public:
  TestCounterObserver(bool isRealtime = true) : PluginParameterObserver(),
    realtime(isRealtime), count(0) {}
  virtual ~TestCounterObserver() {}
  bool isRealtimePriority() const { return realtime; }
  void onParameterUpdated(const PluginParameter* parameter) {
    count++;
  }
  const bool realtime;
  int count;
};

class BooleanParameterObserver : public PluginParameterObserver {
public:
  BooleanParameterObserver() : PluginParameterObserver(), value(false) {}
  virtual ~BooleanParameterObserver() {}
  bool isRealtimePriority() const { return true; }
  void onParameterUpdated(const PluginParameter *parameter) {
    value = parameter->getValue();
  }
  bool value;
};

class StringParameterObserver : public PluginParameterObserver {
public:
  StringParameterObserver() : PluginParameterObserver(), value("") {}
  virtual ~StringParameterObserver() {}
  bool isRealtimePriority() const { return true; }
  void onParameterUpdated(const PluginParameter* parameter) {
    value = parameter->getDisplayText();
  }
  ParameterString value;
};

////////////////////////////////////////////////////////////////////////////////
// Tests
////////////////////////////////////////////////////////////////////////////////

class _Tests {
public:
static bool testCreateBoolParameter() {
  BooleanParameter p("test");
  ASSERT_FALSE(p.getValue());
  ASSERT_EQUALS(0.0, p.getScaledValue());
  ASSERT_STRING("test", p.getName());
  ASSERT_EQUALS(0.0, p.getDisplayValue());
  ASSERT_STRING("false", p.getDisplayText());
  ASSERT_STRING("test", p.getSafeName());
  return true;
}

static bool testSetBoolParameter() {
  BooleanParameter p("test");
  ASSERT_FALSE(p.getValue());
  p.setValue(1.0);
  ASSERT(p.getValue());
  return true;
}

static bool testSetBoolParameterWithListener() {
  BooleanParameter *p = new BooleanParameter("test");
  BooleanParameterObserver l;
  p->addObserver(&l);
  p->setValue(true);
  ASSERT(l.value);
  delete p;
  return true;
}

static bool testCreateDecibelParameter() {
  DecibelParameter p("test", -60.0, 3.0, 0.0);
  ASSERT_EQUALS(0.707739, p.getScaledValue());
  ASSERT_EQUALS(1.0, p.getValue());
  ASSERT_STRING("0.0 dB", p.getDisplayText());
  return true;
}

static bool testSetDecibelParameter() {
  DecibelParameter p("test", -60.0, 3.0, -10.0);
  ASSERT_STRING("-10.0 dB", p.getDisplayText());
  p.setValue(1.0);
  ASSERT_EQUALS(0.707739, p.getScaledValue());
  ASSERT_EQUALS(1.0, p.getValue());
  ASSERT_STRING("0.0 dB", p.getDisplayText());
  p.setScaledValue(0.5);
  ASSERT_EQUALS(0.5, p.getScaledValue());
  ASSERT_EQUALS(0.706769, p.getValue());
  ASSERT_STRING("-3.0 dB", p.getDisplayText());
  return true;
}

static bool testCreateFloatParameter() {
  FloatParameter p("test", 0.0, 50.0, 25.0);
  ASSERT_EQUALS(25.0, p.getValue());
  ASSERT_EQUALS(0.5, p.getScaledValue());
  ASSERT_STRING("25.0", p.getDisplayText());
  return true;
}

static bool testSetFloatParameter() {
  FloatParameter p("test", 0.0, 60.0, 0.0);
  p.setValue(30.0);
  ASSERT_EQUALS(30.0, p.getValue());
  ASSERT_EQUALS(0.5, p.getScaledValue());
  p.setScaledValue(0.25);
  ASSERT_EQUALS(15.0, p.getValue());
  ASSERT_EQUALS(0.25, p.getScaledValue());
  return true;
}

static bool testCreateFrequencyParameter() {
  FrequencyParameter p("test", 20.0, 20000.0, 10000.0);
  ASSERT_EQUALS(10000.0, p.getValue());
  ASSERT_EQUALS(0.899657, p.getScaledValue());
  ASSERT_STRING("10.0 kHz", p.getDisplayText());
  return true;
}

static bool testSetFrequencyParameter() {
  FrequencyParameter p("test", 20.0, 20000.0, 10000.0);
  p.setValue(666.0);
  ASSERT_EQUALS(666.0, p.getValue());
  ASSERT_EQUALS(0.507481, p.getScaledValue());
  p.setScaledValue(0.75);
  ASSERT_EQUALS(3556.559, p.getValue());
  ASSERT_EQUALS(0.75, p.getScaledValue());
  return true;
}

static bool testCreateIntegerParameter() {
  IntegerParameter p("test", 0, 60, 15);
  ASSERT_EQUALS(15.0, p.getValue());
  ASSERT_EQUALS(0.25, p.getScaledValue());
  ASSERT_STRING("15", p.getDisplayText());
  return true;
}

static bool testSetIntegerParameter() {
  IntegerParameter p("test", 0, 60, 15);
  p.setValue(30);
  ASSERT_EQUALS(30.0, p.getValue());
  ASSERT_EQUALS(0.5, p.getScaledValue());
  p.setScaledValue(0.75);
  ASSERT_EQUALS(45.0, p.getValue());
  ASSERT_EQUALS(0.75, p.getScaledValue());
  return true;
}

static bool testCreateStringParameter() {
  StringParameter p("test", "whatever");
  ASSERT_EQUALS(0.0, p.getValue());
  ASSERT_STRING("whatever", p.getDisplayText());
  return true;
}

static bool testSetStringParameter() {
  StringParameter p("test", "whatever");
  ASSERT_EQUALS(0.0, p.getValue());
  ASSERT_STRING("whatever", p.getDisplayText());
  p.setValue("something");
  ASSERT_STRING("something", p.getDisplayText());
  return true;
}

static bool testSetStringParameterWithListener() {
  StringParameter *p = new StringParameter("test", "whatever");
  StringParameterObserver l;
  p->addObserver(&l);
  p->setValue("something");
  ASSERT_STRING("something", l.value);
  delete p;
  return true;
}

static bool testCreateVoidParameter() {
  VoidParameter *p = new VoidParameter("test");
  ASSERT_EQUALS(0.0, p->getValue());
  TestCounterObserver l;
  p->addObserver(&l);
  p->setValue();
  ASSERT_INT_EQUALS(1, l.count);
  delete p;
  return true;
}

static bool testCreateParameterWithBadName() {
  // NOTE: This test will succeed, I'd rather not throw from the ctor!
  // So use your head and don't make any weird parameter names. Just know
  // that the library isn't going to protect you from yourself. :)
  BooleanParameter p("");
  return true;
}

static bool testCreateParameterWithBadRange() {
  // NOTE: This test will also succeed, PluginParameters doesn't check for bad ranges
  // Just be aware of this behavior rather than trying to abuse the library.
  IntegerParameter p("bad", 100.0, 0.0, 300.0);
  return true;
}

static bool testCreateParameterSet() {
  PluginParameterSet s;
  // Really just a basic sanity check
  ASSERT_INT_EQUALS(0, s.size());
  return true;
}

static bool testAddParameterToSet() {
  PluginParameterSet s;
  PluginParameter* _p1;
  PluginParameter* _p2;

  _p1 = s.add(new BooleanParameter("Parameter 1"));
  ASSERT_NOT_NULL(_p1);
  _p2 = s.add(new BooleanParameter("Parameter 2"));
  ASSERT_NOT_NULL(_p2);
  ASSERT_INT_EQUALS(2, s.size());
  ASSERT_STRING("Parameter 1", s.get(0)->getName());
  ASSERT_STRING("Parameter 1", _p1->getName());
  ASSERT_STRING("Parameter 2", s.get(1)->getName());
  ASSERT_STRING("Parameter 2", _p2->getName());
  return true;
}

static bool testAddNullParameterToSet() {
  PluginParameterSet s;
  ASSERT_IS_NULL(s.add(NULL));
  ASSERT_INT_EQUALS(0, s.size());
  return true;
}

static bool testAddDuplicateParameterToSet() {
  BooleanParameter *p = new BooleanParameter("test");
  PluginParameterSet s;
  ASSERT_NOT_NULL(s.add(p));
  ASSERT_IS_NULL(s.add(p));
  ASSERT_INT_EQUALS(1, s.size());
  return true;
}

static bool testAddDuplicateSafeNameParameterToSet() {
  PluginParameterSet s;
  ASSERT_NOT_NULL(s.add(new BooleanParameter("Parameter1")));
  ASSERT_IS_NULL(s.add(new BooleanParameter("Parameter 1")));
  ASSERT_INT_EQUALS(1, s.size());
  return true;
}

static bool testClearParameterSet() {
  PluginParameterSet s;
  ASSERT_NOT_NULL(s.add(new BooleanParameter("Parameter1")));
  ASSERT_NOT_NULL(s.add(new BooleanParameter("Parameter2")));
  ASSERT_INT_EQUALS(2, s.size());
  s.clear();
  ASSERT_INT_EQUALS(0, s.size());
  return true;
}

static bool testGetParameterByName() {
  PluginParameterSet s;
  ASSERT_NOT_NULL(s.add(new BooleanParameter("Parameter 1")));
  ASSERT_NOT_NULL(s.add(new BooleanParameter("Parameter 2")));
  ASSERT_INT_EQUALS(2, s.size());
  PluginParameter *pe = s.get("Parameter 2");
  ASSERT_NOT_NULL(pe);
  ASSERT_STRING("Parameter 2", pe->getName());
  return true;
}

static bool testGetParameterByIndex() {
  PluginParameterSet s;
  ASSERT_NOT_NULL(s.add(new BooleanParameter("Parameter 1")));
  ASSERT_NOT_NULL(s.add(new BooleanParameter("Parameter 2")));
  ASSERT_INT_EQUALS(2, s.size());
  ASSERT_STRING("Parameter 2", s.get(1)->getName());
  return true;
}

static bool testGetParameterByNameOperator() {
  PluginParameterSet s;
  ASSERT_NOT_NULL(s.add(new BooleanParameter("Parameter 1")));
  ASSERT_NOT_NULL(s.add(new BooleanParameter("Parameter 2")));
  ASSERT_INT_EQUALS(2, s.size());
  ASSERT_STRING("Parameter 2", s["Parameter 2"]->getName());
  return true;
}

static bool testGetParameterByIndexOperator() {
  PluginParameterSet s;
  ASSERT_NOT_NULL(s.add(new BooleanParameter("Parameter 1")));
  ASSERT_NOT_NULL(s.add(new BooleanParameter("Parameter 2")));
  ASSERT_INT_EQUALS(2, s.size());
  ASSERT_STRING("Parameter 2", s[1]->getName());
  return true;
}

static bool testGetSafeName() {
  BooleanParameter p("hi there");
  ASSERT_STRING("hithere", p.getSafeName());
  return true;
}

static bool testAddObserver() {
  BooleanParameter *p = new BooleanParameter("test");
  TestObserver t;
  p->addObserver(&t);
  p->setValue(1.0);
  ASSERT(t.notified);
  delete p;
  return true;
}

static bool testRemoveObserver() {
  BooleanParameter p("test");
  TestObserver t;
  p.addObserver(&t);
  p.removeObserver(&t);
  p.setValue(1.0);
  ASSERT_FALSE(t.notified);
  return true;
}

static bool testShouldNotNotifyForSameValue() {
  BooleanParameter p("test", false);
  TestCounterObserver l;
  p.addObserver(&l);
  p.setValue(p.getValue());
  ASSERT_INT_EQUALS(0, l.count);
  return true;
}

static bool testParameterType() {
  BooleanParameter p("test");
  ASSERT_INT_EQUALS(0, p.getType());
  p.setType(1234);
  ASSERT_INT_EQUALS(1234, p.getType());
  return true;
}

static bool testGetMinValue() {
  FloatParameter p("test", 0.123, 1.23, 1.00);
  ASSERT_EQUALS(0.123, p.getMinValue());
  return true;
}

static bool testGetMaxValue() {
  FloatParameter p("test", 0.123, 1.23, 1.00);
  ASSERT_EQUALS(1.23, p.getMaxValue());
  return true;
}

static bool testGetDefaultValue() {
  FloatParameter p("test", 0.123, 1.23, 1.00);
  ASSERT_EQUALS(1.0, p.getDefaultValue());
  return true;
}

static bool testSetParameterUnit() {
  FloatParameter p("test", 0.0, 1.0, 0.0);
  ASSERT_STRING("0.0", p.getDisplayText());
  p.setUnit("foo");
  ASSERT_STRING("0.0 foo", p.getDisplayText());
  return true;
}

static bool testSetPrecision() {
  FloatParameter p("test", 0.0, 1.0, 0.123456);
  ASSERT_STRING("0.1", p.getDisplayText());
  p.setDisplayPrecision(3);
  ASSERT_STRING("0.123", p.getDisplayText());
  // Rounding!
  p.setDisplayPrecision(5);
  ASSERT_STRING("0.12346", p.getDisplayText());
  return true;
}

#if ENABLE_MULTITHREADED
static bool testCreateThreadsafeParameterSet() {
  ThreadsafePluginParameterSet s;
  ASSERT_INT_EQUALS(0, s.size());
  return true;
}

static bool testCreateManyThreadsafeParameterSets() {
  // Attempt to reveal bugs caused by fast-exiting threads
  for(int i = 0; i < 100; i++) {
    ThreadsafePluginParameterSet *s = new ThreadsafePluginParameterSet();
    ASSERT_INT_EQUALS(0, s->size());
    delete s;
  }
  return true;
}

static bool testThreadsafeSetParameterRealtime() {
  ThreadsafePluginParameterSet s;
  PluginParameter *p = s.add(new BooleanParameter("test"));
  ASSERT_NOT_NULL(p);
  ASSERT_FALSE(p->getValue());
  s.set(p, true, true);
  s.processRealtimeEvents();
  ASSERT(p->getValue());
  return true;
}

static bool testThreadsafeSetParameterAsync() {
  ThreadsafePluginParameterSet s;
  PluginParameter *p = s.add(new BooleanParameter("test"));
  ASSERT_NOT_NULL(p);
  ASSERT_FALSE(p->getValue());
  s.set(p, true, false);
  while(!p->getValue()) {
    s.processRealtimeEvents();
    usleep(1000 * SLEEP_TIME_PER_BLOCK_MS);
  }
  ASSERT(p->getValue());
  return true;
}

static bool testThreadsafeSetParameterBothThreadsFromAsync() {
  ThreadsafePluginParameterSet s;
  TestCounterObserver realtimeObserver(true);
  TestCounterObserver asyncObserver(false);
  PluginParameter *p = s.add(new BooleanParameter("test"));
  ASSERT_NOT_NULL(p);
  p->addObserver(&realtimeObserver);
  p->addObserver(&asyncObserver);
  ASSERT_FALSE(p->getValue());
  s.set(p, true, false);
  for(int i = 0; i < TEST_NUM_BLOCKS_TO_PROCESS; i++) {
    s.processRealtimeEvents();
    usleep(1000 * SLEEP_TIME_PER_BLOCK_MS);
  }
  ASSERT(p->getValue());
  ASSERT_INT_EQUALS(1, realtimeObserver.count);
  ASSERT_INT_EQUALS(1, asyncObserver.count);
  return true;
}

static bool testThreadsafeSetParameterBothThreadsFromRealtime() {
  ThreadsafePluginParameterSet s;
  TestCounterObserver realtimeObserver(true);
  TestCounterObserver asyncObserver(false);
  PluginParameter *p = s.add(new BooleanParameter("test"));
  ASSERT_NOT_NULL(p);
  p->addObserver(&realtimeObserver);
  p->addObserver(&asyncObserver);
  ASSERT_FALSE(p->getValue());
  s.set(p, true, true);
  for(int i = 0; i < TEST_NUM_BLOCKS_TO_PROCESS; i++) {
    s.processRealtimeEvents();
    usleep(1000 * SLEEP_TIME_PER_BLOCK_MS);
  }
  ASSERT(p->getValue());
  ASSERT_INT_EQUALS(1, realtimeObserver.count);
  ASSERT_INT_EQUALS(1, asyncObserver.count);
  return true;
}

static bool testThreadsafeSetParameterWithSender() {
  ThreadsafePluginParameterSet s;
  TestCounterObserver realtimeObserver(true);
  TestCounterObserver asyncObserver(false);
  PluginParameter *p = s.add(new BooleanParameter("test"));
  ASSERT_NOT_NULL(p);
  p->addObserver(&realtimeObserver);
  p->addObserver(&asyncObserver);
  ASSERT_FALSE(p->getValue());
  s.set(p, true, false, &asyncObserver);
  for(int i = 0; i < TEST_NUM_BLOCKS_TO_PROCESS; i++) {
    s.processRealtimeEvents();
    usleep(1000 * SLEEP_TIME_PER_BLOCK_MS);
  }
  ASSERT(p->getValue());
  ASSERT_INT_EQUALS(1, realtimeObserver.count);
  // The sender should NOT be called for its own events
  ASSERT_INT_EQUALS(0, asyncObserver.count);
  return true;
}
};
#endif

} // namespace teragon

using namespace teragon;

////////////////////////////////////////////////////////////////////////////////
// Run test suite
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[]) {
  gNumFailedTests = 0;
  ADD_TEST(_Tests::testCreateBoolParameter());
  ADD_TEST(_Tests::testSetBoolParameter());
  ADD_TEST(_Tests::testSetBoolParameterWithListener());

  ADD_TEST(_Tests::testCreateDecibelParameter());
  ADD_TEST(_Tests::testSetDecibelParameter());

  ADD_TEST(_Tests::testCreateFloatParameter());
  ADD_TEST(_Tests::testSetFloatParameter());

  ADD_TEST(_Tests::testCreateFrequencyParameter());
  ADD_TEST(_Tests::testSetFrequencyParameter());

  ADD_TEST(_Tests::testCreateIntegerParameter());
  ADD_TEST(_Tests::testSetIntegerParameter());

  ADD_TEST(_Tests::testCreateStringParameter());
  ADD_TEST(_Tests::testSetStringParameter());
  ADD_TEST(_Tests::testSetStringParameterWithListener());

  ADD_TEST(_Tests::testCreateVoidParameter());

  ADD_TEST(_Tests::testCreateParameterWithBadName());
  ADD_TEST(_Tests::testCreateParameterWithBadRange());

  ADD_TEST(_Tests::testCreateParameterSet());
  ADD_TEST(_Tests::testAddParameterToSet());
  ADD_TEST(_Tests::testAddNullParameterToSet());
  ADD_TEST(_Tests::testAddDuplicateParameterToSet());
  ADD_TEST(_Tests::testAddDuplicateSafeNameParameterToSet());

  ADD_TEST(_Tests::testClearParameterSet());
  ADD_TEST(_Tests::testGetParameterByName());
  ADD_TEST(_Tests::testGetParameterByIndex());
  ADD_TEST(_Tests::testGetParameterByNameOperator());
  ADD_TEST(_Tests::testGetParameterByIndexOperator());

  ADD_TEST(_Tests::testGetSafeName());
  ADD_TEST(_Tests::testAddObserver());
  ADD_TEST(_Tests::testRemoveObserver());
  ADD_TEST(_Tests::testShouldNotNotifyForSameValue());

  ADD_TEST(_Tests::testParameterType());
  ADD_TEST(_Tests::testGetMinValue());
  ADD_TEST(_Tests::testGetMaxValue());
  ADD_TEST(_Tests::testGetDefaultValue());
  ADD_TEST(_Tests::testSetParameterUnit());
  ADD_TEST(_Tests::testSetPrecision());
  
#if ENABLE_MULTITHREADED
  ADD_TEST(_Tests::testThreadsafeSetParameterAsync());
  ADD_TEST(_Tests::testCreateThreadsafeParameterSet());
  ADD_TEST(_Tests::testCreateManyThreadsafeParameterSets());
  ADD_TEST(_Tests::testThreadsafeSetParameterRealtime());
  ADD_TEST(_Tests::testThreadsafeSetParameterBothThreadsFromAsync());
  ADD_TEST(_Tests::testThreadsafeSetParameterBothThreadsFromRealtime());
  ADD_TEST(_Tests::testThreadsafeSetParameterWithSender());
#endif

  if(gNumFailedTests > 0) {
    printf("\nFAILED %d tests\n", gNumFailedTests);
  }
  else {
    printf("\nAll tests passed\n");
  }

  return gNumFailedTests;
}
