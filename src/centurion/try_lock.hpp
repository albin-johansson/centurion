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

#ifndef CENTURION_TRY_LOCK_HEADER
#define CENTURION_TRY_LOCK_HEADER

#include <SDL.h>

#include "centurion_cfg.hpp"
#include "mutex.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/// \addtogroup thread
/// \{

/**
 * \class try_lock
 *
 * \brief Represents an RAII-style non-blocking lock that automatically unlocks
 * the associated mutex upon destruction.
 *
 * \since 5.0.0
 *
 * \headerfile try_lock.hpp
 */
class try_lock final
{
 public:
  /**
   * \brief Attempts to lock the supplied mutex.
   *
   * \param mutex the mutex that will be locked.
   *
   * \since 5.0.0
   */
  explicit try_lock(mutex& mutex) noexcept
      : m_mutex{&mutex}
      , m_status{mutex.try_lock()}
  {}

  try_lock(const try_lock&) = delete;

  auto operator=(const try_lock&) -> try_lock& = delete;

  /**
   * \brief Unlocks the associated mutex if it was successfully locked.
   *
   * \since 5.0.0
   */
  ~try_lock() noexcept
  {
    if (m_status == lock_status::success) {
      m_mutex->unlock();
    }
  }

  /**
   * \brief Returns the result of trying to lock the associated mutex.
   *
   * \return the lock status.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto get_status() const noexcept -> lock_status
  {
    return m_status;
  }

  /**
   * \brief Indicates whether or not the mutex was successfully locked.
   *
   * \return `true` if the mutex was locked; `false` otherwise.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto success() const noexcept -> bool
  {
    return get_status() == lock_status::success;
  }

  /**
   * \brief Indicates whether or not the lock timed out whilst trying to lock
   * the mutex.
   *
   * \return `true` if the locking timed out; `false` otherwise.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto timed_out() const noexcept -> bool
  {
    return get_status() == lock_status::timed_out;
  }

  /**
   * \brief Indicates whether or not there was an error whilst locking the
   * mutex.
   *
   * \return `true` if something went wrong whilst locking the mutex; `false`
   * otherwise.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto error() const noexcept -> bool
  {
    return get_status() == lock_status::error;
  }

  /**
   * \copydoc success()
   */
  [[nodiscard]] explicit operator bool() const noexcept
  {
    return success();
  }

 private:
  mutex* m_mutex{};
  lock_status m_status{};
};

/// \}

}  // namespace cen

#endif  // CENTURION_TRY_LOCK_HEADER
