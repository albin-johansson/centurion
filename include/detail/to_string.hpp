/*
 * MIT License
 *
 * Copyright (c) 2019-2020 Albin Johansson
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

/**
 * @file to_string.hpp
 *
 * @brief Provides the `to_string` function.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

#ifndef CENTURION_DETAIL_TO_STRING_HEADER
#define CENTURION_DETAIL_TO_STRING_HEADER

#include <array>     // array
#include <charconv>  // to_chars
#include <memory_resource>
#include <optional>      // optional, nullopt
#include <string>        // string
#include <system_error>  // errc

#include "centurion_api.hpp"

namespace cen::detail {

/**
 * @brief Returns a string representation of an arithmetic value.
 *
 * @note This function is guaranteed to work for 32-bit integers and floats.
 * You might have to increase the buffer size for larger types.
 *
 * @tparam bufferSize the size of the stack buffer used, must be big enough
 * to store the characters of the string representation of the value.
 * @tparam T the type of the value that will be converted, must be arithmetic.
 *
 * @param value the value that will be converted.
 *
 * @return a string representation of the supplied value; `std::nullopt` if
 * something goes wrong.
 *
 * @since 5.0.0
 */
template <std::size_t bufferSize = 16, typename T>
[[nodiscard]] auto to_string(T value) -> std::optional<std::string>
{
  std::array<char, bufferSize> buffer;  // NOLINT uninitialized buffer is OK
  const auto [ptr, err] =
      std::to_chars(buffer.data(), buffer.data() + buffer.size(), value);
  if (err == std::errc{}) {
    return std::string{buffer.data(), ptr};
  } else {
    return std::nullopt;
  }
}

// class pmr_string final
//{
// public:
//  template <std::size_t size, typename T>
//  explicit pmr_string(std::array<char, size>& buffer, T value) noexcept
//  {
//    const auto [ptr, err] =
//        std::to_chars(buffer.data(), buffer.data() + buffer.size(), value);
//    if (err == std::errc{}) {
//      m_string.emplace(buffer.data(), ptr);
//    }
//  }
//
//  [[nodiscard]] auto ok() const noexcept -> bool
//  {
//    return m_string.has_value();
//  }
//
//  [[nodiscard]] auto value() const -> const std::pmr::string&
//  {
//    return m_string.value();
//  }
//
// private:
//  std::optional<std::pmr::string> m_string;
//};

}  // namespace cen::detail

#endif  // CENTURION_DETAIL_TO_STRING_HEADER
