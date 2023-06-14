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

#ifndef CENTURION_FONTS_WRAP_ALIGNMENT_HPP_
#define CENTURION_FONTS_WRAP_ALIGNMENT_HPP_

#ifndef CENTURION_NO_SDL_TTF

#include <SDL_ttf.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../common.hpp"

namespace cen {

#if SDL_TTF_VERSION_ATLEAST(2, 20, 0)

enum class wrap_alignment {
  left = TTF_WRAPPED_ALIGN_LEFT,
  center = TTF_WRAPPED_ALIGN_CENTER,
  right = TTF_WRAPPED_ALIGN_RIGHT,
};

[[nodiscard]] inline auto to_string(const wrap_alignment align) -> std::string_view
{
  switch (align) {
    case wrap_alignment::left:
      return "left";

    case wrap_alignment::center:
      return "center";

    case wrap_alignment::right:
      return "right";

    default:
      throw exception {"Invalid alignment!"};
  }
}

inline auto operator<<(std::ostream& stream, const wrap_alignment align) -> std::ostream&
{
  return stream << to_string(align);
}

#endif  // SDL_TTF_VERSION_ATLEAST(2, 20, 0)

}  // namespace cen

#endif  // CENTURION_NO_SDL_TTF
#endif  // CENTURION_FONTS_WRAP_ALIGNMENT_HPP_
