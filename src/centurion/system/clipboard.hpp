/*
 * MIT License
 *
 * Copyright (c) 2019-2022 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef CENTURION_SYSTEM_CLIPBOARD_HPP_
#define CENTURION_SYSTEM_CLIPBOARD_HPP_

#include <SDL.h>

#include <cassert>  // assert
#include <string>   // string

#include "../common.hpp"

namespace cen {

inline auto set_clipboard(const char* text) noexcept -> result
{
  assert(text);
  return SDL_SetClipboardText(text) == 0;
}

inline auto set_clipboard(const std::string& text) noexcept -> result
{
  return set_clipboard(text.c_str());
}

[[nodiscard]] inline auto has_clipboard() noexcept -> bool
{
  return SDL_HasClipboardText();
}

[[nodiscard]] inline auto get_clipboard() -> std::string
{
  const sdl_string text {SDL_GetClipboardText()};
  return text.copy();
}

}  // namespace cen

#endif  // CENTURION_SYSTEM_CLIPBOARD_HPP_
