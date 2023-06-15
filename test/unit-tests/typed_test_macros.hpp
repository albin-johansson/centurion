/*
 * MIT License
 *
 * Copyright (c) 2019-2023 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#include <gtest/gtest.h>

// Macros to reduce the quite severe boilerplate required to set up typed tests

// Defines a typed test with its own class with the specified name
#define CENTURION_DEFINE_TYPED_TEST(Name, Types) \
  template <typename T>                          \
  class Name : public testing::Test {};          \
                                                 \
  template <typename T>                          \
  using Name##Suite = Name<T>;                   \
                                                 \
  TYPED_TEST_SUITE_P(Name##Suite);               \
  TYPED_TEST_P(Name##Suite, Name##TypedTest)

// Defines a typed test based on a variant of an existing test class
#define CENTURION_DEFINE_TYPED_TEST_FROM_CLASS(Name, Class, Types) \
  template <typename T>                                            \
  using Name##Suite = Class<T>;                                    \
                                                                   \
  TYPED_TEST_SUITE_P(Name##Suite);                                 \
  TYPED_TEST_P(Name##Suite, Name##TypedTest)

// Registers a typed test, use the name and types provided to the above macros
#define CENTURION_REGISTER_TYPED_TEST(Name, Types)           \
  REGISTER_TYPED_TEST_SUITE_P(Name##Suite, Name##TypedTest); \
  INSTANTIATE_TYPED_TEST_SUITE_P(Name##s, Name##Suite, Types)
