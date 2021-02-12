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

#ifndef CENTURION_EXCEPTION_HEADER
#define CENTURION_EXCEPTION_HEADER

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include <cassert>    // assert
#include <exception>  // exception

#include "centurion_cfg.hpp"
#include "czstring.hpp"
#include "not_null.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/**
 * \class exception
 *
 * \ingroup misc
 *
 * \brief The base of all exceptions explicitly thrown by the library.
 *
 * \todo Centurion 6: Rename to cen_error, similar to sdl_error, etc.
 *
 * \headerfile exception.hpp
 *
 * \since 3.0.0
 */
class exception : public std::exception
{
 public:
  exception() noexcept = default;

  /**
   * \param what the message of the exception.
   *
   * \since 3.0.0
   */
  explicit exception(const not_null<czstring> what) noexcept : m_what{what}
  {
    assert(what && "Cannot supply null exception message!");
  }

  [[nodiscard]] auto what() const noexcept -> czstring override
  {
    return m_what;
  }

 private:
  czstring m_what{"N/A"};
};

/**
 * \class sdl_error
 *
 * \brief Represents an error related to the core SDL2 library.
 *
 * \since 5.0.0
 *
 * \headerfile exception.hpp
 */
class sdl_error final : public exception
{
 public:
  /**
   * \brief Creates an `sdl_error` with the error message obtained from
   * `SDL_GetError()`.
   *
   * \since 5.0.0
   */
  sdl_error() noexcept : exception{SDL_GetError()}
  {}

  /**
   * \brief Creates an `sdl_error` with the specified error message.
   *
   * \param what the error message that will be used.
   *
   * \since 5.0.0
   */
  explicit sdl_error(const not_null<czstring> what) noexcept : exception{what}
  {}
};

/**
 * \class img_error
 *
 * \brief Represents an error related to the SDL2_image library.
 *
 * \since 5.0.0
 *
 * \headerfile exception.hpp
 */
class img_error final : public exception
{
 public:
  /**
   * \brief Creates an `img_error` with the error message obtained from
   * `IMG_GetError()`.
   *
   * \since 5.0.0
   */
  img_error() noexcept : exception{IMG_GetError()}
  {}

  /**
   * \brief Creates an `img_error` with the specified error message.
   *
   * \param what the error message that will be used.
   *
   * \since 5.0.0
   */
  explicit img_error(const not_null<czstring> what) noexcept : exception{what}
  {}
};

/**
 * \class ttf_error
 *
 * \brief Represents an error related to the SDL2_ttf library.
 *
 * \since 5.0.0
 *
 * \headerfile exception.hpp
 */
class ttf_error final : public exception
{
 public:
  /**
   * \brief Creates a `ttf_error` with the error message obtained from
   * `TTF_GetError()`.
   *
   * \since 5.0.0
   */
  ttf_error() noexcept : exception{TTF_GetError()}
  {}

  /**
   * \brief Creates a `ttf_error` with the specified error message.
   *
   * \param what the error message that will be used.
   *
   * \since 5.0.0
   */
  explicit ttf_error(const not_null<czstring> what) noexcept : exception{what}
  {}
};

/**
 * \class mix_error
 *
 * \brief Represents an error related to the SDL2_mixer library.
 *
 * \since 5.0.0
 *
 * \headerfile exception.hpp
 */
class mix_error final : public exception
{
 public:
  /**
   * \brief Creates a `mix_error` with the error message obtained from
   * `Mix_GetError()`.
   *
   * \since 5.0.0
   */
  mix_error() noexcept : exception{Mix_GetError()}
  {}

  /**
   * \brief Creates a `mix_error` with the specified error message.
   *
   * \param what the error message that will be used.
   *
   * \since 5.0.0
   */
  explicit mix_error(const not_null<czstring> what) noexcept : exception{what}
  {}
};

}  // namespace cen

#endif  // CENTURION_EXCEPTION_HEADER
