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

#ifndef CENTURION_VIDEO_FLASH_OP_HPP_
#define CENTURION_VIDEO_FLASH_OP_HPP_

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../common.hpp"

namespace cen {

#if SDL_VERSION_ATLEAST(2, 0, 16)

enum class flash_op {
  cancel = SDL_FLASH_CANCEL,               ///< Cancel any current flashing.
  briefly = SDL_FLASH_BRIEFLY,             ///< Briefly flash the window.
  until_focused = SDL_FLASH_UNTIL_FOCUSED  ///< Flash the window until it's focused.
};

[[nodiscard]] constexpr auto to_string(const flash_op op) -> std::string_view
{
  switch (op) {
    case flash_op::cancel:
      return "cancel";

    case flash_op::briefly:
      return "briefly";

    case flash_op::until_focused:
      return "until_focused";

    default:
      throw exception {"Did not recognize window flash operation!"};
  }
}

inline auto operator<<(std::ostream& stream, const flash_op op) -> std::ostream&
{
  return stream << to_string(op);
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 16)

}  // namespace cen

#endif  // CENTURION_VIDEO_FLASH_OP_HPP_
