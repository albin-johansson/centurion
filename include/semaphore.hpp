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

#ifndef CENTURION_SEMAPHORE_HEADER
#define CENTURION_SEMAPHORE_HEADER

#include <SDL.h>

#include <memory>  // unique_ptr

#include "centurion_cfg.hpp"
#include "exception.hpp"
#include "integers.hpp"
#include "mutex.hpp"
#include "time.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/// \addtogroup thread
/// \{

/**
 * \class semaphore
 *
 * \brief Represents a semaphore with a set of "tokens" (or permits).
 *
 * \since 5.0.0
 *
 * \headerfile semaphore.hpp
 */
class semaphore final
{
 public:
  /**
   * \brief Creates a semaphore with the specified amount of tokens.
   *
   * \param tokens the initial amount of tokens.
   *
   * \throws sdl_error if the semaphore cannot be created.
   *
   * \since 5.0.0
   */
  explicit semaphore(const u32 tokens)
      : m_semaphore{SDL_CreateSemaphore(tokens)}
  {
    if (!m_semaphore) {
      throw sdl_error{};
    }
  }

  /**
   * \brief Acquires a token from the semaphore.
   *
   * \note This function blocks the calling thread until a token is available.
   *
   * \return `true` if a token was acquired; `false` on failure.
   *
   * \since 5.0.0
   */
  auto acquire() noexcept -> bool
  {
    return SDL_SemWait(m_semaphore.get()) == 0;
  }

  /**
   * \brief Attempts to acquire a token from the semaphore.
   *
   * \param ms the maximum amount of time to wait.
   *
   * \return `success` if a token was acquired; `timed_out` if no token was
   * acquired in the specified duration; `error` if something goes wrong.
   *
   * \since 5.0.0
   */
  auto acquire(const milliseconds<u32> ms) -> lock_status
  {
    return static_cast<lock_status>(
        SDL_SemWaitTimeout(m_semaphore.get(), ms.count()));
  }

  /**
   * \brief Attempts to acquire a token from the semaphore.
   *
   * \return `success` if a token was acquired; `timed_out` if the thread
   * would've been blocked; `error` if something goes wrong.
   *
   * \since 5.0.0
   */
  auto try_acquire() noexcept -> lock_status
  {
    return static_cast<lock_status>(SDL_SemTryWait(m_semaphore.get()));
  }

  /**
   * \brief Returns a token to the semaphore and notifies waiting threads.
   *
   * \return `true` on success; `false` on failure.
   *
   * \since 5.0.0
   */
  auto release() noexcept -> bool
  {
    return SDL_SemPost(m_semaphore.get()) == 0;
  }

  /**
   * \brief Returns the amount of available tokens.
   *
   * \return the current amount of available tokens.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto tokens() const noexcept -> u32
  {
    return SDL_SemValue(m_semaphore.get());
  }

 private:
  struct deleter final
  {
    void operator()(SDL_sem* semaphore) noexcept
    {
      SDL_DestroySemaphore(semaphore);
    }
  };
  std::unique_ptr<SDL_sem, deleter> m_semaphore;
};

/// \}

}  // namespace cen

#endif  // CENTURION_SEMAPHORE_HEADER
