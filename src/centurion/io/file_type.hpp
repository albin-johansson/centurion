/*
 * MIT License
 *
 * Copyright (c) 2019-2023 Albin Johansson
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

#ifndef CENTURION_IO_FILE_TYPE_HPP_
#define CENTURION_IO_FILE_TYPE_HPP_

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../common/errors.hpp"

namespace cen {

enum class file_type : unsigned {
  unknown = SDL_RWOPS_UNKNOWN,
  win = SDL_RWOPS_WINFILE,
  std = SDL_RWOPS_STDFILE,
  jni = SDL_RWOPS_JNIFILE,
  memory = SDL_RWOPS_MEMORY,
  memory_ro = SDL_RWOPS_MEMORY_RO
};

[[nodiscard]] constexpr auto to_string(const file_type type) -> std::string_view
{
  switch (type) {
    case file_type::unknown:
      return "unknown";

    case file_type::win:
      return "win";

    case file_type::std:
      return "std";

    case file_type::jni:
      return "jni";

    case file_type::memory:
      return "memory";

    case file_type::memory_ro:
      return "memory_ro";

    default:
      throw exception {"Did not recognize file type!"};
  }
}

inline auto operator<<(std::ostream& stream, const file_type type) -> std::ostream&
{
  return stream << to_string(type);
}

}  // namespace cen

#endif  // CENTURION_IO_FILE_TYPE_HPP_
