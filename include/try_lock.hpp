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
 * @file try_lock.hpp
 *
 * @ingroup thread
 *
 * @brief Provides the `try_lock` class.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

#ifndef CENTURION_TRY_LOCK_HEADER
#define CENTURION_TRY_LOCK_HEADER

#include <SDL_mutex.h>

#include <type_traits>

#include "centurion_api.hpp"
#include "centurion_fwd.hpp"
#include "mutex.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/// @addtogroup thread
/// @{

/**
 * @class try_lock
 *
 * @brief Represents an RAII-style non-blocking lock that automatically unlocks
 * the associated mutex upon destruction.
 *
 * @since 5.0.0
 *
 * @headerfile try_lock.hpp
 */
class try_lock final
{
 public:
  /**
   * @brief Attempts to lock the supplied mutex.
   *
   * @param mutex the mutex that will be locked.
   *
   * @since 5.0.0
   */
  CENTURION_API
  explicit try_lock(mutex& mutex) noexcept;

  try_lock(const try_lock&) = delete;

  auto operator=(const try_lock&) -> try_lock& = delete;

  /**
   * @brief Unlocks the associated mutex if it was successfully locked.
   *
   * @since 5.0.0
   */
  CENTURION_API
  ~try_lock() noexcept;

  /**
   * @brief Returns the result of trying to lock the associated mutex.
   *
   * @return the lock status.
   *
   * @since 5.0.0
   */
  CENTURION_QUERY
  auto get_status() const noexcept -> lock_status;

  /**
   * @brief Indicates whether or not the mutex was successfully locked.
   *
   * @return `true` if the mutex was locked; `false` otherwise.
   *
   * @since 5.0.0
   */
  CENTURION_QUERY
  auto success() const noexcept -> bool;

  /**
   * @brief Indicates whether or not the lock timed out whilst trying to lock
   * the mutex.
   *
   * @return `true` if the locking timed out; `false` otherwise.
   *
   * @since 5.0.0
   */
  CENTURION_QUERY
  auto timed_out() const noexcept -> bool;

  /**
   * @brief Indicates whether or not there was an error whilst locking the
   * mutex.
   *
   * @return `true` if something went wrong whilst locking the mutex; `false`
   * otherwise.
   *
   * @since 5.0.0
   */
  CENTURION_QUERY
  auto error() const noexcept -> bool;

  /**
   * @copydoc success()
   */
  CENTURION_QUERY
  explicit operator bool() const noexcept;

 private:
  mutex* m_mutex{};
  lock_status m_status{};
};

static_assert(!std::is_copy_constructible_v<try_lock>);
static_assert(!std::is_copy_assignable_v<try_lock>);

/// @}

}  // namespace cen

#endif  // CENTURION_TRY_LOCK_HEADER
