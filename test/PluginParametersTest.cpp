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
#include "PluginParameters.h"

using namespace teragon;

#define ADD_TEST(name, func) { \
  printf("Test %s: ", name); \
  if(func) printf("success\n"); \
  else printf("FAIL\n"); \
}

#define ASSERT(result) { \
  if(!result) return false; \
}

#define ASSERT_NOT_NULL(result) { \
  if(result == NULL) return false; \
}

#define ASSERT_FALSE(result) { \
  if(result) return false; \
}

#define ASSERT_EQUALS(expected, result) { \
  if(abs(abs(result) - abs(expected)) > 0.001) { \
    printf("Expected %f, got %f. ", expected, result); \
    return false; \
  } \
}

#define ASSERT_INT_EQUALS(expected, result) { \
  if(result != expected) { \
    printf("Expected %d, got %d. ", expected, result); \
    return false; \
  } \
}

#define ASSERT_STRING(expected, result) { \
  std::string e(expected); \
  if(e.compare(result) != 0) { \
    printf("Expected '%s', got '%s'. ", expected, result.c_str()); \
    return false; \
  } \
}

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
  ASSERT_STRING("10000.0 Hz", p.getDisplayText());
  return true;
}

static bool testSetFrequencyParameter() {
  FrequencyParameter p("test", 20.0, 20000.0, 10000.0);
  p.setValue(666.0);
  ASSERT_EQUALS(666.0, p.getValue());
  ASSERT_EQUALS(0.5, p.getScaledValue());
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

static bool testAddParameterToSet() {
  BooleanParameter p1("Parameter 1");
  BooleanParameter p2("Parameter 2");
  PluginParameterSet s;
  ASSERT(s.add(&p1));
  ASSERT(s.add(&p2));
  ASSERT_INT_EQUALS(2, s.size());
  ASSERT_STRING("Parameter 1", s.get(0)->getName());
  ASSERT_STRING("Parameter 2", s.get(1)->getName());
  return true;
}

static bool testAddNullParameterToSet() {
  PluginParameterSet s;
  ASSERT_FALSE(s.add(NULL));
  ASSERT_INT_EQUALS(0, s.size());
  return true;
}

static bool testAddDuplicateParameterToSet() {
  BooleanParameter p("test");
  PluginParameterSet s;
  ASSERT(s.add(&p));
  ASSERT_FALSE(s.add(&p));
  ASSERT_INT_EQUALS(1, s.size());
  return true;
}

static bool testAddDuplicateSafeNameParameterToSet() {
  BooleanParameter p1("Parameter1");
  BooleanParameter p2("Parameter 1");
  PluginParameterSet s;
  ASSERT(s.add(&p1));
  ASSERT_FALSE(s.add(&p2));
  ASSERT_INT_EQUALS(1, s.size());
  return true;
}

static bool testGetParameterByName() {
  BooleanParameter p1("Parameter 1");
  BooleanParameter p2("Parameter 2");
  PluginParameterSet s;
  ASSERT(s.add(&p1));
  ASSERT(s.add(&p2));
  ASSERT_INT_EQUALS(2, s.size());
  PluginParameter *pe = s.get("Parameter 2");
  ASSERT_NOT_NULL(pe);
  ASSERT_STRING("Parameter 2", pe->getName());
  return true;
}

static bool testGetParameterByIndex() {
  BooleanParameter p1("Parameter 1");
  BooleanParameter p2("Parameter 2");
  PluginParameterSet s;
  ASSERT(s.add(&p1));
  ASSERT(s.add(&p2));
  ASSERT_INT_EQUALS(2, s.size());
  ASSERT_STRING("Parameter 2", s.get(1)->getName());
  return true;
}

static bool testGetParameterByNameOperator() {
  BooleanParameter p1("Parameter 1");
  BooleanParameter p2("Parameter 2");
  PluginParameterSet s;
  ASSERT(s.add(&p1));
  ASSERT(s.add(&p2));
  ASSERT_INT_EQUALS(2, s.size());
  ASSERT_STRING("Parameter 2", s["Parameter 2"]->getName());
  return true;
}

static bool testGetParameterByIndexOperator() {
  BooleanParameter p1("Parameter 1");
  BooleanParameter p2("Parameter 2");
  PluginParameterSet s;
  ASSERT(s.add(&p1));
  ASSERT(s.add(&p2));
  ASSERT_INT_EQUALS(2, s.size());
  ASSERT_STRING("Parameter 2", s[1]->getName());
  return true;
}

static bool testGetSafeName() {
  BooleanParameter p("hi there");
  ASSERT_STRING("hithere", p.getSafeName());
  return true;
}

class TestObserver : public PluginParameterObserver {
public:
  TestObserver(bool &inB) : b(inB) {}
  void onParameterUpdated(const PluginParameter* parameter) const {
    b = true;
  }
private:
  bool& b;
};

static bool testAddObserver() {
  bool b = false;
  BooleanParameter p("test");
  TestObserver t(b);
  p.addObserver(&t);
  p.setValue(1.0);
  ASSERT(b);
  return true;
}

static bool testRemoveObserver() {
  bool b = false;
  BooleanParameter p("test");
  TestObserver t(b);
  p.addObserver(&t);
  p.removeObserver(&t);
  p.setValue(1.0);
  ASSERT_FALSE(b);
  return true;
}

int main(int argc, char* argv[]) {
  ADD_TEST("CreateBoolParameter", testCreateBoolParameter());
  ADD_TEST("SetBoolParameter", testSetBoolParameter());
  ADD_TEST("CreateDecibelParameter", testCreateDecibelParameter());
  ADD_TEST("SetDecibelParameter", testSetDecibelParameter());
  ADD_TEST("CreateFloatParameter", testCreateFloatParameter());
  ADD_TEST("SetFloatParameter", testSetFloatParameter());
  ADD_TEST("CreateFrequencyParameter", testCreateFrequencyParameter());
  ADD_TEST("SetFrequencyParameter", testSetFrequencyParameter());
  ADD_TEST("CreateIntegerParameter", testCreateIntegerParameter());
  ADD_TEST("SetIntegerParameter", testSetIntegerParameter());
  ADD_TEST("CreateParameterWithBadName", testCreateParameterWithBadName());
  ADD_TEST("CreateParameterWithBadRange", testCreateParameterWithBadRange());
  ADD_TEST("AddParameterToSet", testAddParameterToSet());
  ADD_TEST("AddNullParameterToSet", testAddNullParameterToSet());
  ADD_TEST("AddDuplicateParameterToSet", testAddDuplicateParameterToSet());
  ADD_TEST("AddDuplicateSafeNameParameterToSet", testAddDuplicateSafeNameParameterToSet());
  ADD_TEST("GetParameterByName", testGetParameterByName());
  ADD_TEST("GetParameterByIndex", testGetParameterByIndex());
  ADD_TEST("GetParameterByNameOperator", testGetParameterByNameOperator());
  ADD_TEST("GetParameterByIndexOperator", testGetParameterByIndexOperator());
  ADD_TEST("GetSafeName", testGetSafeName());
  ADD_TEST("AddObserver", testAddObserver());
  ADD_TEST("RemoveObserver", testRemoveObserver());
  return 0;
}
