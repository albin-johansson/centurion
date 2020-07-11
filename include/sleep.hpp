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
 * @file sleep.hpp
 *
 * @brief Provides the `sleep(milliseconds<u32>)` method.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

#ifndef CENTURION_SLEEP_HEADER
#define CENTURION_SLEEP_HEADER

#include <SDL_timer.h>

#include "centurion_api.hpp"
#include "centurion_types.hpp"

namespace centurion {

/**
 * @brief Forces the currently executing thread to halt for at least the
 * specified amount of milliseconds.
 *
 * @note The actual time spent sleeping may differ, depending on the
 * scheduling of the operating system. You shouldn't use this method for
 * precise timing.
 *
 * @param ms the minimum amount of time to sleep for, in milliseconds.
 *
 * @since 3.0.0
 */
inline void sleep(milliseconds<u32> ms) noexcept
{
  SDL_Delay(ms.count());
}

}  // namespace centurion

#endif  // CENTURION_SLEEP_HEADER