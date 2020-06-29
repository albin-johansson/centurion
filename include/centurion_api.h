/*
 * MIT License
 *
 * Copyright (c) 2019-2020 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * @brief Defines various compatibility macros.
 *
 * @file centurion_api.h
 * @author Albin Johansson
 * @date 2019-2020
 * @copyright MIT License
 */

#ifndef CENTURION_API_HEADER
#define CENTURION_API_HEADER

#include <memory>
#include <type_traits>

#include "centurion_cfg.h"

/**
 * @brief Used for exporting entities in generated Windows DLL.
 *
 * @def CENTURION_API
 * @headerfile centurion_api.h
 * @internal https://atomheartother.github.io/c++/2018/07/12/CPPDynLib.html
 */
#if defined(_WIN32) && !defined(CENTURION_HEADER_ONLY)
#ifdef WIN_EXPORT
#define CENTURION_API __declspec(dllexport)
#else
#define CENTURION_API __declspec(dllimport)
#endif  // WIN_EXPORT
#else
#define CENTURION_API
#endif  // defined(_WIN32) && !defined(CENTURION_HEADER_ONLY)

/**
 * @brief Indicates that return values shouldn't be ignored.
 *
 * Effectively equivalent to `[[nodiscard]]` in C++17.
 *
 * @def CENTURION_NODISCARD
 * @headerfile centurion_api.h
 */
#ifndef CENTURION_NODISCARD
#if defined(__GNUC__)
#define CENTURION_NODISCARD __attribute__((warn_unused_result))
#elif defined(_MSC_VER) && _MSC_VER >= 1700
#define CENTURION_NODISCARD _Check_return_
#else
#if __cplusplus >= 201603
#define CENTURION_NODISCARD [[nodiscard]]
#else
#define CENTURION_NODISCARD
#endif
#endif
#endif

/**
 * @brief Indicates that something shouldn't be used.
 *
 * Effectively equivalent to `[[deprecated]]` in C++17.
 *
 * @def CENTURION_DEPRECATED
 * @headerfile centurion_api.h
 */
#ifndef CENTURION_DEPRECATED
#if defined(__GNUC__)
#define CENTURION_DEPRECATED __attribute__((deprecated))
#elif defined(_MSC_VER) && _MSC_VER >= 1300
#define CENTURION_DEPRECATED __declspec(deprecated)
#else
#if __cplusplus >= 201309
#define CENTURION_DEPRECATED [[deprecated]]
#else
#define CENTURION_DEPRECATED
#endif
#endif
#endif

/**
 * @brief Used when the pseudo-header-only mode is enabled.
 *
 * When header-only mode is enabled, definitions are specified as `inline`.
 *
 * @def CENTURION_DEF
 * @headerfile centurion_api.h
 */
#if !defined(CENTURION_DEF) && defined(CENTURION_HEADER_ONLY)
#define CENTURION_DEF inline
#else
#define CENTURION_DEF
#endif

/**
 * @brief Indicates whether or not `std::is_final` is available.
 *
 * @def CENTURION_HAS_IS_FINAL_TYPE_TRAIT
 * @headerfile centurion_api.h
 */
#if !defined(CENTURION_HAS_IS_FINAL_TYPE_TRAIT) && defined(__cpp_lib_is_final)
#define CENTURION_HAS_IS_FINAL_TYPE_TRAIT
#endif

/**
 * @brief Indicates whether or not `std::make_unique` is available.
 *
 * @def CENTURION_HAS_MAKE_UNIQUE
 * @headerfile centurion_api.h
 */
#if !defined(CENTURION_HAS_MAKE_UNIQUE) && defined(__cpp_lib_make_unique)
#define CENTURION_HAS_MAKE_UNIQUE
#endif

#endif  // CENTURION_API_HEADER