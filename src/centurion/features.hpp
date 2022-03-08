/*
 * MIT License
 *
 * Copyright (c) 2019-2022 Albin Johansson
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

#ifndef CENTURION_FEATURES_HPP_
#define CENTURION_FEATURES_HPP_

/// Do we have general C++20 support?
#if __cplusplus >= 202002L
#define CENTURION_HAS_FEATURE_CPP20 1
#else
#define CENTURION_HAS_FEATURE_CPP20 0
#endif  // __cplusplus >= 202002L

/// C++20 nodiscard constructors
#if nodiscard >= 201907L
#define CENTURION_NODISCARD_CTOR [[nodiscard]]
#else
#define CENTURION_NODISCARD_CTOR
#endif  // nodiscard >= 201907L

#ifdef __has_include

#if __has_include(<version>)
#include <version>
#endif  // __has_include(<version>)

#ifdef __cpp_lib_format
#define CENTURION_HAS_FEATURE_FORMAT 1
#else
#define CENTURION_HAS_FEATURE_FORMAT 0
#endif  // __cpp_lib_format

#ifdef __cpp_lib_concepts
#define CENTURION_HAS_FEATURE_CONCEPTS 1
#else
#define CENTURION_HAS_FEATURE_CONCEPTS 0
#endif  // __cpp_lib_concepts

#ifdef __cpp_lib_interpolate
#define CENTURION_HAS_FEATURE_LERP 1
#else
#define CENTURION_HAS_FEATURE_LERP 0
#endif  // __cpp_lib_interpolate

#ifdef __cpp_lib_three_way_comparison
#define CENTURION_HAS_FEATURE_SPACESHIP 1
#else
#define CENTURION_HAS_FEATURE_SPACESHIP 0
#endif  // __cpp_lib_three_way_comparison

#if __cpp_lib_chrono >= 201907L
#define CENTURION_HAS_FEATURE_CHRONO_TIME_ZONES 1
#else
#define CENTURION_HAS_FEATURE_CHRONO_TIME_ZONES 0
#endif  // __cpp_lib_chrono >= 201907L

#if __cpp_lib_to_array >= 201907L
#define CENTURION_HAS_FEATURE_TO_ARRAY 1
#else
#define CENTURION_HAS_FEATURE_TO_ARRAY 0
#endif  // __cpp_lib_to_array >= 201907L

#if __cpp_lib_to_chars >= 201611L
#define CENTURION_HAS_FEATURE_CHARCONV 1
#else
#define CENTURION_HAS_FEATURE_CHARCONV 0
#endif  // __cpp_lib_to_chars >= 201611L

#endif  // __has_include

#endif  // CENTURION_FEATURES_HPP_
