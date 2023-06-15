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

#ifndef CENTURION_COMMON_SDL_STRING_HPP_
#define CENTURION_COMMON_SDL_STRING_HPP_

#include <memory>  // unique_ptr
#include <string>  // string

#include "../detail/sdl_deleter.hpp"
#include "primitives.hpp"

namespace cen {

/**
 * Represents an SDL style string.
 *
 * \details Certain SDL APIs return `char*` strings that need to be freed using `SDL_free()`,
 *          this class serves as a small wrapper around such strings. Use the `copy()` member
 *          function to convert the string into a corresponding `std::string`.
 *
 * \note Instances of `sdl_string` may hold null strings. Use the overloaded `operator bool()`
 *       in order to determine whether the associated string is null.
 */
class sdl_string final {
 public:
  explicit sdl_string(owner<char*> str) noexcept : mStr {str} {}

  /// Returns a potentially null pointer to the internal string.
  [[nodiscard]] auto get() const noexcept -> const char* { return mStr.get(); }

  /**
   * Returns a copy of the internal string.
   *
   * \details The empty string is returned if the internal pointer is null.
   *
   * \return a standard string instance.
   */
  [[nodiscard]] auto copy() const -> std::string
  {
    if (mStr) {
      return std::string {get()};
    }
    else {
      return std::string {};
    }
  }

  /// Indicates whether the internal pointer is non-null.
  explicit operator bool() const noexcept { return mStr != nullptr; }

 private:
  std::unique_ptr<char, detail::sdl_deleter> mStr;
};

}  // namespace cen

#endif  // CENTURION_COMMON_SDL_STRING_HPP_
