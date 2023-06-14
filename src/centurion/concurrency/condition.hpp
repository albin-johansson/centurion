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

#ifndef CENTURION_CONCURRENCY_CONDITION_HPP_
#define CENTURION_CONCURRENCY_CONDITION_HPP_

#include <SDL.h>

#include "../common/errors.hpp"
#include "../common/memory.hpp"
#include "../common/result.hpp"
#include "locks.hpp"
#include "mutex.hpp"

namespace cen {

/// Represents a condition variable.
class condition final {
 public:
  condition() : mCond {SDL_CreateCond()}
  {
    if (!mCond) {
      throw sdl_error {};
    }
  }

  /// Wakes up one of the threads waiting on the condition variable.
  auto signal() noexcept -> result { return SDL_CondSignal(mCond.get()) == 0; }

  /// Wakes up all threads that are waiting on the condition variable.
  auto broadcast() noexcept -> result { return SDL_CondBroadcast(mCond.get()) == 0; }

  auto wait(mutex& mutex) noexcept -> result
  {
    return SDL_CondWait(mCond.get(), mutex.data()) == 0;
  }

  auto wait(mutex& mutex, const u32ms duration) noexcept(noexcept(duration.count()))
      -> lock_status
  {
    return static_cast<lock_status>(
        SDL_CondWaitTimeout(mCond.get(), mutex.data(), duration.count()));
  }

 private:
  managed_ptr<SDL_cond> mCond;
};

}  // namespace cen

#endif  // CENTURION_CONCURRENCY_CONDITION_HPP_
