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
 * @file exception.hpp
 *
 * @brief Provides the exception types used by the Centurion library.
 *
 * @see `exception`
 * @see `sdl_error`
 * @see `ttf_error`
 * @see `mix_error`
 * @see `img_error`
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
#include <string_view>
#include <type_traits>
#include <utility>  // move

#include "centurion_api.hpp"
#include "types.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/**
 * @class exception
 *
 * @ingroup misc
 *
 * @brief The base of all exceptions explicitly thrown by the library.
 *
 * @headerfile exception.hpp
 *
 * @since 3.0.0
 */
class exception : public std::exception
{
 public:
  exception() = default;

  /**
   * @param what the message of the exception. If the string is null, "N/A" is
   * used.
   *
   * @since 3.0.0
   */
  explicit exception(czstring what)
  {
    if (what) {
      set_what(what);
    }
  }

  /**
   * @param what the message of the exception. If the string is empty, "N/A"
   * is used.
   *
   * @since 3.0.0
   */
  explicit exception(std::string what)
  {
    if (!what.empty()) {
      set_what(std::move(what));
    }
  }

  [[nodiscard]] auto what() const noexcept -> czstring override
  {
    return m_what.c_str();
  }

 protected:
  void set_what(std::string what) { m_what = std::move(what); }

 private:
  std::string m_what{"N/A"};
};

static_assert(std::has_virtual_destructor_v<exception>);
static_assert(std::is_default_constructible_v<exception>);
static_assert(std::is_nothrow_move_constructible_v<exception>);
static_assert(std::is_nothrow_destructible_v<exception>);

/**
 * @class sdl_error
 *
 * @brief Represents an error related to the core SDL2 library.
 *
 * @since 5.0.0
 *
 * @headerfile exception.hpp
 */
class sdl_error final : public exception
{
 public:
  sdl_error() = default;

  /**
   * @brief Creates an `sdl_error` with the specified error message.
   *
   * @details The message will be formatted according to `what + ": " +
   * SDL_GetError()`.
   *
   * @param what the error message that will be used.
   *
   * @since 5.0.0
   */
  CENTURION_API
  explicit sdl_error(std::string_view what);
};

/**
 * @class img_error
 *
 * @brief Represents an error related to the SDL2_image library.
 *
 * @since 5.0.0
 *
 * @headerfile exception.hpp
 */
class img_error final : public exception
{
 public:
  img_error() = default;

  /**
   * @brief Creates an `img_error` with the specified error message.
   *
   * @details The message will be formatted according to `what + ": " +
   * IMG_GetError()`.
   *
   * @param what the error message that will be used.
   *
   * @since 5.0.0
   */
  CENTURION_API
  explicit img_error(std::string_view what);
};

/**
 * @class ttf_error
 *
 * @brief Represents an error related to the SDL2_ttf library.
 *
 * @since 5.0.0
 *
 * @headerfile exception.hpp
 */
class ttf_error final : public exception
{
 public:
  ttf_error() = default;

  /**
   * @brief Creates a `ttf_error` with the specified error message.
   *
   * @details The message will be formatted according to `what + ": " +
   * TTF_GetError()`.
   *
   * @param what the error message that will be used.
   *
   * @since 5.0.0
   */
  CENTURION_API
  explicit ttf_error(std::string_view what);
};

/**
 * @class mix_error
 *
 * @brief Represents an error related to the SDL2_mixer library.
 *
 * @since 5.0.0
 *
 * @headerfile exception.hpp
 */
class mix_error final : public exception
{
 public:
  mix_error() = default;

  /**
   * @brief Creates a `mix_error` with the specified error message.
   *
   * @details The message will be formatted according to `what + ": " +
   * Mix_GetError()`.
   *
   * @param what the error message that will be used.
   *
   * @since 5.0.0
   */
  CENTURION_API
  explicit mix_error(std::string_view what);
};

}  // namespace cen

#endif  // CENTURION_EXCEPTION_HEADER
