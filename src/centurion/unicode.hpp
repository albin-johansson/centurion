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

#ifndef CENTURION_UNICODE_HPP_
#define CENTURION_UNICODE_HPP_

#include <cassert>           // assert
#include <initializer_list>  // initializer_list
#include <string_view>       // u16string_view
#include <type_traits>       // is_same_v, decay_t
#include <vector>            // vector

#include "common.hpp"

namespace cen {

/// Represents a null-terminated string of Unicode characters.
class unicode_string final
{
 public:
  using value_type = std::vector<unicode_t>::value_type;

  using pointer = std::vector<unicode_t>::pointer;
  using const_pointer = std::vector<unicode_t>::const_pointer;

  using reference = std::vector<unicode_t>::reference;
  using const_reference = std::vector<unicode_t>::const_reference;

  using iterator = std::vector<unicode_t>::iterator;
  using const_iterator = std::vector<unicode_t>::const_iterator;

  using size_type = std::vector<unicode_t>::size_type;

  unicode_string() { mData.push_back(0); }

  /* implicit */ unicode_string(const std::u16string_view str)
  {
    reserve(str.size());

    for (const auto ch : str) {
      mData.push_back(ch);
    }

    mData.push_back(0);
  }

  unicode_string(std::initializer_list<unicode_t> codes)
  {
    reserve(codes.size() + 1);
    mData.insert(mData.end(), codes.begin(), codes.end());
    mData.push_back(0);
  }

  void reserve(const size_type n) { mData.reserve(n + 1u); }

  void append(const unicode_t ch) { mData.insert(mData.end() - 1, ch); }

  template <typename... Character>
  void append(Character... code)
  {
    static_assert(sizeof...(Character) != 0, "Must append at least 1 value!");
    static_assert((std::is_convertible_v<Character, unicode_t> && ...),
                  "Must append unicode_t values!");
    (append(static_cast<unicode_t>(code)), ...);
  }

  void operator+=(const unicode_t ch) { append(ch); }

  void pop_back()
  {
    if (!empty()) {
      mData.erase(mData.end() - 2);
    }
  }

  [[nodiscard]] auto at(const size_type index) -> reference
  {
    if (is_valid_index(index)) {
      return mData[index];
    }
    else {
      throw exception{"Invalid unicode string index!"};
    }
  }

  [[nodiscard]] auto at(const size_type index) const -> const_reference
  {
    if (is_valid_index(index)) {
      return mData[index];
    }
    else {
      throw exception{"Invalid unicode string index!"};
    }
  }

  /// Returns the element at the specified index (with no bounds checking).
  [[nodiscard]] auto operator[](const size_type index) noexcept(on_msvc) -> reference
  {
    assert(is_valid_index(index));
    return mData[index];
  }

  /// Returns the element at the specified index (with no bounds checking).
  [[nodiscard]] auto operator[](const size_type index) const noexcept(on_msvc)
      -> const_reference
  {
    assert(is_valid_index(index));
    return mData[index];
  }

  [[nodiscard]] auto size() const noexcept -> size_type
  {
    assert(!mData.empty());
    return mData.size() - 1u;
  }

  [[nodiscard]] auto capacity() const noexcept -> size_type
  {
    assert(mData.capacity() >= 1u);
    return mData.capacity() - 1u;
  }

  [[nodiscard]] auto empty() const noexcept -> bool { return mData.size() == 1; }

  [[nodiscard]] auto data() noexcept -> pointer { return mData.data(); }
  [[nodiscard]] auto data() const noexcept -> const_pointer { return mData.data(); }

  [[nodiscard]] auto begin() noexcept -> iterator { return mData.begin(); }
  [[nodiscard]] auto begin() const noexcept -> const_iterator { return mData.begin(); }

  [[nodiscard]] auto end() noexcept -> iterator { return mData.end() - 1; }
  [[nodiscard]] auto end() const noexcept -> const_iterator { return mData.end() - 1; }

  template <typename Archive>
  void serialize(Archive& archive)
  {
    archive(mData);
  }

 private:
  std::vector<unicode_t> mData;

  [[nodiscard]] auto is_valid_index(const size_type index) const noexcept -> bool
  {
    return index < mData.size() - 1; /* Do not include null-terminator */
  }
};

[[nodiscard]] inline auto operator==(const unicode_string& a, const unicode_string& b) -> bool
{
  if (a.size() != b.size()) {
    return false;
  }

  for (unicode_string::size_type index = 0; index < a.size(); ++index) {
    const auto aChar = a.at(index);
    const auto bChar = b.at(index);
    if (aChar != bChar) {
      return false;
    }
  }

  return true;
}

[[nodiscard]] inline auto operator!=(const unicode_string& a, const unicode_string& b) -> bool
{
  return !(a == b);
}

}  // namespace cen

#endif  // CENTURION_UNICODE_HPP_
