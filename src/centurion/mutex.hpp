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

#ifndef CENTURION_MUTEX_HEADER
#define CENTURION_MUTEX_HEADER

#include <SDL.h>

#include <memory>  // unique_ptr

#include "centurion_cfg.hpp"
#include "exception.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/// \addtogroup thread
/// \{

enum class lock_status
{
  success = 0,
  timed_out = SDL_MUTEX_TIMEDOUT,
  error = -1
};

/**
 * \class mutex
 *
 * \brief Represents a recursive mutex.
 *
 * \details The fact that the mutex is recursive mutex means that it's possible
 * to nest lock and unlock calls with the same mutex.
 *
 * \since 5.0.0
 *
 * \see `scoped_lock`
 * \see `try_lock`
 *
 * \headerfile mutex.hpp
 */
class mutex final
{
 public:
  /**
   * \brief Creates an unlocked mutex.
   *
   * \throws sdl_error if the mutex cannot be created.
   *
   * \since 5.0.0
   */
  mutex() : m_mutex{SDL_CreateMutex()}
  {
    if (!m_mutex) {
      throw sdl_error{};
    }
  }

  /**
   * \brief Attempts to lock the mutex, blocks if the mutex isn't available.
   *
   * \return `true` if the mutex was successfully locked; `false` on failure.
   *
   * \since 5.0.0
   */
  auto lock() noexcept -> bool
  {
    return SDL_LockMutex(get()) == 0;
  }

  /**
   * \brief Attempts to lock the mutex, returns if the mutex isn't available.
   *
   * \return the result of the operation.
   *
   * \since 5.0.0
   */
  auto try_lock() noexcept -> lock_status
  {
    return static_cast<lock_status>(SDL_TryLockMutex(get()));
  }

  /**
   * \brief Attempts to unlock the mutex.
   *
   * \return `true` if the mutex was successfully unlocked; `false` otherwise.
   *
   * \since 5.0.0
   */
  auto unlock() noexcept -> bool
  {
    return SDL_UnlockMutex(get()) == 0;
  }

  /**
   * \brief Returns a pointer to the associated SDL mutex.
   *
   * \return a pointer to the internal mutex.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto get() noexcept -> SDL_mutex*
  {
    return m_mutex.get();
  }

 private:
  struct deleter final
  {
    void operator()(SDL_mutex* mutex) noexcept
    {
      SDL_DestroyMutex(mutex);
    }
  };
  std::unique_ptr<SDL_mutex, deleter> m_mutex;

#ifdef CENTURION_MOCK_FRIENDLY_MODE
 public:
  explicit mutex(int){};
#endif  // CENTURION_MOCK_FRIENDLY_MODE
};

/// \}

}  // namespace cen

#endif  // CENTURION_MUTEX_HEADER
