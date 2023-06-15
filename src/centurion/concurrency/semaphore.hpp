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

#ifndef CENTURION_CONCURRENCY_SEMAPHORE_HPP_
#define CENTURION_CONCURRENCY_SEMAPHORE_HPP_

#include <SDL.h>

#include "../common/errors.hpp"
#include "../common/memory.hpp"
#include "../common/primitives.hpp"
#include "../common/result.hpp"
#include "mutex.hpp"

namespace cen {

/// Represents a semaphore with a set of "tokens" (or "permits").
class semaphore final {
 public:
  /// Creates a semaphore with an initial amount of tokens.
  explicit semaphore(const uint32 tokens) : mSemaphore {SDL_CreateSemaphore(tokens)}
  {
    if (!mSemaphore) {
      throw sdl_error {};
    }
  }

  /// Acquires a token from the semaphore, blocks until a token is available.
  auto acquire() noexcept -> result { return SDL_SemWait(mSemaphore.get()) == 0; }

  auto acquire(const u32ms duration) noexcept(noexcept(duration.count())) -> lock_status
  {
    return static_cast<lock_status>(SDL_SemWaitTimeout(mSemaphore.get(), duration.count()));
  }

  auto try_acquire() noexcept -> lock_status
  {
    return static_cast<lock_status>(SDL_SemTryWait(mSemaphore.get()));
  }

  /// Returns a token to the semaphore and notifies waiting threads.
  auto release() noexcept -> result { return SDL_SemPost(mSemaphore.get()) == 0; }

  /// Returns the amount of available tokens.
  [[nodiscard]] auto count() const noexcept -> uint32
  {
    return SDL_SemValue(mSemaphore.get());
  }

 private:
  managed_ptr<SDL_sem> mSemaphore;
};

}  // namespace cen

#endif  // CENTURION_CONCURRENCY_SEMAPHORE_HPP_
