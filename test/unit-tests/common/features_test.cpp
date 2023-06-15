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

#include "centurion/features.hpp"

#include <gtest/gtest.h>

#include <array>    // array
#include <cstddef>  // byte

#if CENTURION_HAS_FEATURE_CONCEPTS
#include <concepts>
#endif  // CENTURION_HAS_FEATURE_CONCEPTS

#if CENTURION_HAS_FEATURE_FORMAT
#include <format>
#endif  // CENTURION_HAS_FEATURE_FORMAT

#if CENTURION_HAS_FEATURE_CONCEPTS

TEST(Features, Concepts)
{
  using foo = int;
  using bar = int;
  static_assert(std::same_as<foo, bar>);
}

#endif  // CENTURION_HAS_FEATURE_CONCEPTS

#if CENTURION_HAS_FEATURE_FORMAT

TEST(Features, Format)
{
  ASSERT_EQ("foo: 42", std::format("foo: {}", 42));
}

#endif  // CENTURION_HAS_FEATURE_FORMAT
