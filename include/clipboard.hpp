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

#ifndef CENTURION_CLIPBOARD_HEADER
#define CENTURION_CLIPBOARD_HEADER

#include <SDL.h>

#include <cassert>  // assert
#include <string>   // string

#include "centurion_cfg.hpp"
#include "czstring.hpp"
#include "not_null.hpp"
#include "sdl_string.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

/// \addtogroup system
/// \{

/**
 * \namespace cen::clipboard
 *
 * \brief Provides functions related to managing the clipboard.
 *
 * \since 5.0.0
 */
namespace cen::clipboard {

/**
 * \brief Indicates whether or not there is a clipboard exists and that it
 * contains non-empty text.
 *
 * \return `true` if there is a clipboard that contains non-empty text; `false`
 * otherwise.
 *
 * \since 5.0.0
 */
[[nodiscard]] inline auto has_text() noexcept -> bool
{
  return SDL_HasClipboardText();
}

/**
 * \brief Returns the current text in the clipboard.
 *
 * \note If the clipboard cannot be obtained, this function returns the empty
 * string.
 *
 * \return the current clipboard text.
 *
 * \since 5.0.0
 */
[[nodiscard]] inline auto get_text() -> std::string
{
  const sdl_string text{SDL_GetClipboardText()};
  return text.copy();
}

/**
 * \brief Sets the current clipboard text.
 *
 * \pre `text` cannot be null.
 *
 * \param text the text that will be stored in the clipboard.
 *
 * \return `true` if the clipboard text was successfully set; `false` otherwise.
 *
 * \since 5.0.0
 */
inline auto set_text(not_null<czstring> text) noexcept -> bool
{
  assert(text);
  return SDL_SetClipboardText(text) == 0;
}

}  // namespace cen::clipboard

/// \}

#endif  // CENTURION_CLIPBOARD_HEADER
