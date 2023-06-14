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

#ifndef CENTURION_CONCURRENCY_MUTEX_HPP_
#define CENTURION_CONCURRENCY_MUTEX_HPP_

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../common/errors.hpp"
#include "../common/memory.hpp"
#include "../common/result.hpp"

namespace cen {

enum class lock_status {
  success = 0,
  timed_out = SDL_MUTEX_TIMEDOUT,
  error = -1
};

[[nodiscard]] constexpr auto to_string(const lock_status status) -> std::string_view
{
  switch (status) {
    case lock_status::success:
      return "success";

    case lock_status::timed_out:
      return "timed_out";

    case lock_status::error:
      return "error";

    default:
      throw exception {"Did not recognize lock status!"};
  }
}

inline auto operator<<(std::ostream& stream, const lock_status status) -> std::ostream&
{
  return stream << to_string(status);
}

/**
 * Represents a recursive mutex.
 *
 * \see scoped_lock
 * \see try_lock
 */
class mutex final {
 public:
  /// Creates an unlocked mutex.
  mutex() : mMutex {SDL_CreateMutex()}
  {
    if (!mMutex) {
      throw sdl_error {};
    }
  }

  /// Attempts to lock the mutex, blocks if the mutex isn't available.
  auto lock() noexcept -> result { return SDL_LockMutex(data()) == 0; }

  /// Attempts to lock the mutex and returns immediately.
  auto try_lock() noexcept -> lock_status
  {
    return static_cast<lock_status>(SDL_TryLockMutex(data()));
  }

  auto unlock() noexcept -> result { return SDL_UnlockMutex(data()) == 0; }

  [[nodiscard]] auto data() noexcept -> SDL_mutex* { return mMutex.get(); }

  [[nodiscard]] auto data() const noexcept -> const SDL_mutex* { return mMutex.get(); }

 private:
  managed_ptr<SDL_mutex> mMutex;

#ifdef CENTURION_MOCK_FRIENDLY_MODE

 public:
  explicit mutex(int /*dummy*/) {};

#endif  // CENTURION_MOCK_FRIENDLY_MODE
};

}  // namespace cen

#endif  // CENTURION_CONCURRENCY_MUTEX_HPP_
