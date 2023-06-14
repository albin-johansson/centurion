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

#ifndef CENTURION_IO_FILE_MODE_HPP_
#define CENTURION_IO_FILE_MODE_HPP_

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../common.hpp"

namespace cen {

enum class file_mode {
  r,    ///< Read existing ("r").
  rb,   ///< Read existing binary ("rb").
  w,    ///< Write ("w").
  wb,   ///< Write binary ("wb").
  a,    ///< Append/create ("a").
  ab,   ///< Append/create binary ("ab").
  rx,   ///< Read/write existing ("r+").
  rbx,  ///< Read/write existing binary ("rb+").
  wx,   ///< Read/write replace ("w+").
  wbx,  ///< Read/write replace binary ("wb+").
  ax,   ///< Read/append ("a+").
  abx,  ///< Read/append binary ("ab+").
};

[[nodiscard]] constexpr auto to_string(const file_mode mode) -> std::string_view
{
  switch (mode) {
    case file_mode::r:
      return "r";

    case file_mode::rb:
      return "rb";

    case file_mode::w:
      return "w";

    case file_mode::wb:
      return "wb";

    case file_mode::a:
      return "a";

    case file_mode::ab:
      return "ab";

    case file_mode::rx:
      return "rx";

    case file_mode::rbx:
      return "rbx";

    case file_mode::wx:
      return "wx";

    case file_mode::wbx:
      return "wbx";

    case file_mode::ax:
      return "ax";

    case file_mode::abx:
      return "abx";

    default:
      throw exception {"Did not recognize file mode!"};
  }
}

inline auto operator<<(std::ostream& stream, const file_mode mode) -> std::ostream&
{
  return stream << to_string(mode);
}

}  // namespace cen

#endif  // CENTURION_IO_FILE_MODE_HPP_
