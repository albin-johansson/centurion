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

#ifndef CENTURION_CONCURRENCY_LOCKS_HPP_
#define CENTURION_CONCURRENCY_LOCKS_HPP_

#include <SDL.h>

#include "../common/errors.hpp"
#include "../common/primitives.hpp"
#include "../common/utils.hpp"
#include "mutex.hpp"

namespace cen {

/// An RAII style blocking lock that unlocks the associated mutex upon destruction.
class scoped_lock final {
 public:
  /// Attempts to lock a mutex.
  CENTURION_NODISCARD_CTOR explicit scoped_lock(mutex& mutex) : mMutex {&mutex}
  {
    if (!mutex.lock()) {
      throw sdl_error {};
    }
  }

  CENTURION_DISABLE_COPY(scoped_lock)
  CENTURION_DISABLE_MOVE(scoped_lock)

  ~scoped_lock() noexcept { mMutex->unlock(); }

 private:
  mutex* mMutex {};
};

/// An RAII style non-blocking lock that unlocks the associated mutex upon destruction.
class try_lock final {
 public:
  /// Attempts to lock a mutex.
  CENTURION_NODISCARD_CTOR explicit try_lock(mutex& mutex) noexcept
      : mMutex {&mutex}
      , mStatus {mutex.try_lock()}
  {
  }

  CENTURION_DISABLE_COPY(try_lock)

  ~try_lock() noexcept
  {
    if (mStatus == lock_status::success) {
      mMutex->unlock();
    }
  }

  [[nodiscard]] auto status() const noexcept -> lock_status { return mStatus; }

  [[nodiscard]] auto locked() const noexcept -> bool
  {
    return status() == lock_status::success;
  }

  [[nodiscard]] auto timed_out() const noexcept -> bool
  {
    return status() == lock_status::timed_out;
  }

  [[nodiscard]] auto failed() const noexcept -> bool { return status() == lock_status::error; }

  /// Indicates whether the mutex was successfully locked.
  [[nodiscard]] explicit operator bool() const noexcept { return locked(); }

 private:
  mutex* mMutex {};
  lock_status mStatus {};
};

}  // namespace cen

#endif  // CENTURION_CONCURRENCY_LOCKS_HPP_
