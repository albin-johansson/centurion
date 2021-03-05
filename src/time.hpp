/*
 * MIT License
 *
 * Copyright (c) 2019-2021 Albin Johansson
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

#ifndef CENTURION_TIME_HEADER
#define CENTURION_TIME_HEADER

#include <chrono>  // duration
#include <ratio>   // milli, micro, nano

#include "centurion_cfg.hpp"
#include "integers.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/**
 * \typedef seconds
 *
 * \brief Templated alias for durations in seconds.
 */
template <typename T>
using seconds = std::chrono::duration<T>;

/**
 * \typedef milliseconds
 *
 * \brief Templated alias for durations in milliseconds.
 */
template <typename T>
using milliseconds = std::chrono::duration<T, std::milli>;

/**
 * \typedef microseconds
 *
 * \brief Templated alias for durations in microseconds.
 */
template <typename T>
using microseconds = std::chrono::duration<T, std::micro>;

/**
 * \typedef nanoseconds
 *
 * \brief Templated alias for durations in nanoseconds.
 */
template <typename T>
using nanoseconds = std::chrono::duration<T, std::nano>;

/**
 * \typedef minutes
 *
 * \brief Templated alias for durations in minutes.
 */
template <typename T>
using minutes = std::chrono::duration<T, std::ratio<60>>;

/**
 * \namespace literals
 *
 * \brief Contains suffix operators.
 *
 * \since 5.0.0
 */
namespace literals {

constexpr auto operator"" _ns(const unsigned long long int value) noexcept
    -> nanoseconds<u32>
{
  return nanoseconds<u32>{value};
}

constexpr auto operator"" _us(const unsigned long long int value) noexcept
    -> microseconds<u32>
{
  return microseconds<u32>{value};
}

constexpr auto operator"" _ms(const unsigned long long int value) noexcept
    -> milliseconds<u32>
{
  return milliseconds<u32>{value};
}

constexpr auto operator"" _s(const unsigned long long int value) noexcept
    -> seconds<u32>
{
  return seconds<u32>{value};
}

}  // namespace literals
}  // namespace cen

#endif  // CENTURION_TIME_HEADER
