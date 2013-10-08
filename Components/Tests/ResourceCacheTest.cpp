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
#include "Resources.h"

using namespace teragon;

////////////////////////////////////////////////////////////////////////////////
// Test suite macros
////////////////////////////////////////////////////////////////////////////////

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
  if(fabs(fabs(result) - fabs(expected)) > 0.001) { \
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

static bool testCreateResourceCache() {
  ResourceCache* r = Resources::getCache();
  ASSERT_NOT_NULL(r);
  delete r;
  return true;
}

int main(int argc, char* argv[]) {
  ADD_TEST("CreateResourceCache", testCreateResourceCache());
  return 0;
}
