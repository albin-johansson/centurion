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

#ifndef CENTURION_FONTS_FONT_HINT_HPP_
#define CENTURION_FONTS_FONT_HINT_HPP_

#ifndef CENTURION_NO_SDL_TTF

#include <SDL_ttf.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../common.hpp"

namespace cen {

enum class font_hint {
  normal = TTF_HINTING_NORMAL,
  light = TTF_HINTING_LIGHT,

#if SDL_TTF_VERSION_ATLEAST(2, 0, 18)
  light_subpixel = TTF_HINTING_LIGHT_SUBPIXEL,
#endif  // SDL_TTF_VERSION_ATLEAST(2, 0, 18)

  mono = TTF_HINTING_MONO,
  none = TTF_HINTING_NONE
};

[[nodiscard]] constexpr auto to_string(const font_hint hint) -> std::string_view
{
  switch (hint) {
    case font_hint::normal:
      return "normal";

    case font_hint::light:
      return "light";

#if SDL_TTF_VERSION_ATLEAST(2, 0, 18)

    case font_hint::light_subpixel:
      return "light_subpixel";

#endif  // SDL_TTF_VERSION_ATLEAST(2, 0, 18)

    case font_hint::mono:
      return "mono";

    case font_hint::none:
      return "none";

    default:
      throw exception {"Did not recognize font hint!"};
  }
}

inline auto operator<<(std::ostream& stream, const font_hint hint) -> std::ostream&
{
  return stream << to_string(hint);
}

}  // namespace cen

#endif  // CENTURION_NO_SDL_TTF
#endif  // CENTURION_FONTS_FONT_HINT_HPP_
