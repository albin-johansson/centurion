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

#ifndef CENTURION_SCOPED_LOCK_HEADER
#define CENTURION_SCOPED_LOCK_HEADER

#include <SDL.h>

#include "centurion_cfg.hpp"
#include "exception.hpp"
#include "mutex.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/// \addtogroup thread
/// \{

/**
 * \class scoped_lock
 *
 * \brief Represents an RAII-style blocking lock that automatically unlocks the
 * associated mutex upon destruction.
 *
 * \remarks This class is purposefully similar to `std::scoped_lock`.
 *
 * \since 5.0.0
 *
 * \headerfile scoped_lock.hpp
 */
class scoped_lock final
{
 public:
  /**
   * \brief Attempts to lock the supplied mutex.
   *
   * \param mutex the mutex that will be locked.
   *
   * \throws sdl_error if the mutex can't be locked.
   *
   * \since 5.0.0
   */
  explicit scoped_lock(mutex& mutex) : m_mutex{&mutex}
  {
    if (!mutex.lock()) {
      throw sdl_error{};
    }
  }

  scoped_lock(const scoped_lock&) = delete;

  auto operator=(const scoped_lock&) -> scoped_lock& = delete;

  /**
   * \brief Unlocks the associated mutex.
   *
   * \since 5.0.0
   */
  ~scoped_lock() noexcept
  {
    m_mutex->unlock();
  }

 private:
  mutex* m_mutex{};
};

/// \}

}  // namespace cen

#endif  // CENTURION_SCOPED_LOCK_HEADER
