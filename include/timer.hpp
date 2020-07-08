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
 * @brief Provides utilities related to to the system clock and timing.
 * @todo Rename `Timer` to Clock/Counter.
 * @todo Move `Timer::delay` to somewhere else
 * @file timer.hpp
 * @author Albin Johansson
 * @date 2019-2020
 * @copyright MIT License
 */

#ifndef CENTURION_TIMER_HEADER
#define CENTURION_TIMER_HEADER

#include <SDL_timer.h>

#include "centurion_api.hpp"
#include "centurion_types.hpp"

namespace centurion {

/**
 * The Timer class provides utilities related to the system clock.
 *
 * @since 3.0.0
 */
class Timer final {
 public:
  Timer() = delete;

  /**
   * @brief Forces the currently executing thread to halt for at least the
   * specified amount of milliseconds.
   *
   * @note The actual time spent sleeping may be longer, depending on the
   * scheduling of the operating system.
   *
   * @param ms the minimum amount of time to sleep for, in milliseconds.
   *
   * @since 3.0.0
   */
  CENTURION_API static void delay(milliseconds<u32> ms) noexcept;

  /**
   * @brief Returns the frequency of the system high-performance counter.
   *
   * @return the frequency of the system high-performance counter.
   *
   * @since 3.0.0
   */
  CENTURION_QUERY static auto high_res_freq() noexcept -> u64;

  /**
   * @brief Returns the current value of the system high-performance counter.
   *
   * @return the current value of the system high-performance counter.
   *
   * @since 3.0.0
   */
  [[nodiscard]] static auto now() noexcept -> u64
  {
    return SDL_GetPerformanceCounter();
  }

  /**
   * @brief Returns the amount of milliseconds since the library was
   * initialized.
   *
   * @return the amount of milliseconds since the library was initialized.
   *
   * @since 3.0.0
   */
  [[nodiscard]] static auto now_ms() noexcept -> milliseconds<u32>
  {
    return milliseconds<u32>{SDL_GetTicks()};
  }
};

}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "timer.cpp"
#endif

#endif  // CENTURION_TIMER_HEADER