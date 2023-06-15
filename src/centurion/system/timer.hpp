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

#ifndef CENTURION_SYSTEM_TIMER_HPP_
#define CENTURION_SYSTEM_TIMER_HPP_

#include <SDL.h>

#include "../common/primitives.hpp"

namespace cen {

/// Returns the frequency of the system high-performance counter.
[[nodiscard]] inline auto frequency() noexcept -> uint64
{
  return SDL_GetPerformanceFrequency();
}

/// Returns the current value of the high-performance counter.
[[nodiscard]] inline auto now() noexcept -> uint64
{
  return SDL_GetPerformanceCounter();
}

/// Returns the value of the system high-performance counter in seconds.
[[nodiscard]] inline auto now_in_seconds() noexcept(noexcept(seconds<double> {}))
    -> seconds<double>
{
  return seconds<double> {static_cast<double>(now()) / static_cast<double>(frequency())};
}

#if SDL_VERSION_ATLEAST(2, 0, 18)

[[nodiscard]] inline auto ticks64() noexcept(noexcept(u64ms {uint64 {}})) -> u64ms
{
  return u64ms {SDL_GetTicks64()};
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 18)

[[nodiscard, deprecated]] inline auto ticks32() noexcept(noexcept(u32ms {uint32 {}})) -> u32ms
{
  return u32ms {SDL_GetTicks()};
}

}  // namespace cen

#endif  // CENTURION_SYSTEM_TIMER_HPP_
