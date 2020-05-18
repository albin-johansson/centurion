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

#ifndef CENTURION_TIMER_HEADER
#define CENTURION_TIMER_HEADER

#include <SDL_timer.h>

#include "centurion_api.h"

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
   * Forces the currently executing thread to halt for at least the specified
   * amount of milliseconds. However, the actual time spent sleeping may be
   * longer, depending on the scheduling of the operating system.
   *
   * @param ms the minimum amount of time to sleep for, in milliseconds.
   * @since 3.0.0
   */
  CENTURION_API static void delay(Uint32 ms) noexcept;

  /**
   * Returns the frequency of the system high-performance counter.
   *
   * @return the frequency of the system high-performance counter.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static Uint64 high_res_freq() noexcept;

  /**
   * Returns the current value of the system high-performance counter.
   *
   * @return the current value of the system high-performance counter.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  static Uint64 high_res() noexcept { return SDL_GetPerformanceCounter(); }

  /**
   * Returns the amount of milliseconds since the library was initialized.
   *
   * @return the amount of milliseconds since the library was initialized.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  static Uint32 millis() noexcept { return SDL_GetTicks(); }
};

}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "timer.cpp"
#endif

#endif  // CENTURION_TIMER_HEADER