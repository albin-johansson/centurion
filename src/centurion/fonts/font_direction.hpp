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

#ifndef CENTURION_FONTS_FONT_DIRECTION_HPP_
#define CENTURION_FONTS_FONT_DIRECTION_HPP_

#ifndef CENTURION_NO_SDL_TTF

#include <SDL_ttf.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../common.hpp"

namespace cen {

#if SDL_TTF_VERSION_ATLEAST(2, 20, 0)

enum class font_direction
{
  ltr = TTF_DIRECTION_LTR,  ///< Left to right.
  rtl = TTF_DIRECTION_RTL,  ///< Right to left.
  ttb = TTF_DIRECTION_TTB,  ///< Top to bottom.
  btt = TTF_DIRECTION_BTT   ///< Bottom to top.
};

[[nodiscard]] inline auto to_string(const font_direction dir) -> std::string_view
{
  switch (dir) {
    case font_direction::ltr:
      return "ltr";

    case font_direction::rtl:
      return "rtl";

    case font_direction::ttb:
      return "ttb";

    case font_direction::btt:
      return "btt";

    default:
      throw exception{"Invalid font direction!"};
  }
}

inline auto operator<<(std::ostream& stream, const font_direction dir) -> std::ostream&
{
  return stream << to_string(dir);
}

#endif  // SDL_TTF_VERSION_ATLEAST(2, 20, 0)

}  // namespace cen

#endif  // CENTURION_NO_SDL_TTF
#endif  // CENTURION_FONTS_FONT_DIRECTION_HPP_
