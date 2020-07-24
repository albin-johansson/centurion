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
 * @file centurion_exception.hpp
 *
 * @brief Provides the general exception class used by the library.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

#ifndef CENTURION_EXCEPTION_HEADER
#define CENTURION_EXCEPTION_HEADER

#include <exception>
#include <type_traits>
#include <utility>

#include "centurion_api.hpp"
#include "centurion_types.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace centurion {

/**
 * @class centurion_exception
 *
 * @ingroup misc
 *
 * @brief The only exception explicitly thrown by the library.
 *
 * @headerfile centurion_exception.hpp
 *
 * @since 3.0.0
 */
class centurion_exception final : public std::exception {
 public:
  centurion_exception() = default;

  /**
   * @param what the message of the exception. If the string is null, "N/A" is
   * used.
   *
   * @since 3.0.0
   */
  explicit centurion_exception(czstring what) noexcept
      : m_what{what ? what : "N/A"} {};

  /**
   * @param what the message of the exception. If the string is empty, "N/A"
   * is used.
   *
   * @since 3.0.0
   */
  explicit centurion_exception(std::string what) noexcept
      : m_what{what.empty() ? "N/A" : std::move(what)} {};

  [[nodiscard]] auto what() const noexcept -> czstring override
  {
    return m_what.c_str();
  }

 private:
  std::string m_what;
};

static_assert(std::is_final_v<centurion_exception>);
static_assert(std::is_default_constructible_v<centurion_exception>);
static_assert(std::is_nothrow_move_constructible_v<centurion_exception>);
static_assert(std::is_nothrow_destructible_v<centurion_exception>);

}  // namespace centurion

#endif  // CENTURION_EXCEPTION_HEADER