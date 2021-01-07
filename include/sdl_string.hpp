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

#ifndef CENTURION_SDL_STRING_HEADER
#define CENTURION_SDL_STRING_HEADER

#include <SDL.h>

#include <memory>  // unique_ptr
#include <string>  // string

#include "centurion_cfg.hpp"
#include "types.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/**
 * \class sdl_string
 *
 * \brief Represents a string obtained from SDL, usually a `char*` that has to
 * be freed using `SDL_free`.
 *
 * \since 5.0.0
 *
 * \headerfile sdl_string.hpp
 */
class sdl_string final
{
 public:
  /**
   * \brief
   *
   * \param str the string that will be claimed, can be null.
   *
   * \since 5.0.0
   */
  explicit sdl_string(owner<zstring> str) noexcept : m_str{str}
  {}

  /**
   * \brief Returns the internal string, which might be null.
   *
   * \return the internal string; `nullptr` if there is none.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto get() const noexcept -> czstring
  {
    return m_str.get();
  }

  /**
   * \brief Returns a copy of the internal string.
   *
   * \details This function returns the empty string if the internal string
   * is a null pointer.
   *
   * \return a copy of the internal string.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto copy() const -> std::string
  {
    if (m_str) {
      return std::string{get()};
    } else {
      return std::string{};
    }
  }

  /**
   * \brief Indicates whether or not the internal string is non-null.
   *
   * \return `true` if the internal string is non-null; `false` otherwise.
   *
   * \since 5.0.0
   */
  explicit operator bool() const noexcept
  {
    return m_str.operator bool();
  }

 private:
  struct deleter final
  {
    void operator()(zstring text) noexcept
    {
      SDL_free(text);
    }
  };
  std::unique_ptr<char, deleter> m_str;
};

}  // namespace cen

#endif  // CENTURION_SDL_STRING_HEADER
