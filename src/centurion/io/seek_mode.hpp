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

#ifndef CENTURION_IO_SEEK_MODE_HPP_
#define CENTURION_IO_SEEK_MODE_HPP_

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../common.hpp"

namespace cen {

enum class seek_mode {
  from_beginning = RW_SEEK_SET,       ///< From the beginning.
  relative_to_current = RW_SEEK_CUR,  ///< Relative to the current read point.
  relative_to_end = RW_SEEK_END       ///< Relative to the end.
};

[[nodiscard]] constexpr auto to_string(const seek_mode mode) -> std::string_view
{
  switch (mode) {
    case seek_mode::from_beginning:
      return "from_beginning";

    case seek_mode::relative_to_current:
      return "relative_to_current";

    case seek_mode::relative_to_end:
      return "relative_to_end";

    default:
      throw exception {"Did not recognize seek mode!"};
  }
}

inline auto operator<<(std::ostream& stream, const seek_mode mode) -> std::ostream&
{
  return stream << to_string(mode);
}

}  // namespace cen

#endif  // CENTURION_IO_SEEK_MODE_HPP_
