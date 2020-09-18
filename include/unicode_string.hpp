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
 * @file unicode_string.hpp
 *
 * @ingroup input
 *
 * @brief Provides the `unicode_string` class.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

#ifndef CENTURION_UNICODE_STRING_HEADER
#define CENTURION_UNICODE_STRING_HEADER

#include <cassert>
#include <initializer_list>
#include <vector>

#include "centurion_api.hpp"
#include "types.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/**
 * @class unicode_string
 *
 * @brief Represents a null-terminated string encoded in unicode.
 *
 * @details This class is a wrapper around a `std::vector<unicode>`, that
 * provides a similar interface to that of `std::string`.
 *
 * @headerfile unicode_string.hpp
 */
class unicode_string final
{
 public:
  using value_type = std::vector<unicode>::value_type;

  using pointer = std::vector<unicode>::pointer;
  using const_pointer = std::vector<unicode>::const_pointer;

  using reference = std::vector<unicode>::reference;
  using const_reference = std::vector<unicode>::const_reference;

  using iterator = std::vector<unicode>::iterator;
  using const_iterator = std::vector<unicode>::const_iterator;

  using reverse_iterator = std::vector<unicode>::reverse_iterator;
  using const_reverse_iterator = std::vector<unicode>::const_reverse_iterator;

  using size_type = std::vector<unicode>::size_type;
  using difference_type = std::vector<unicode>::difference_type;

  /**
   * @brief Creates an empty Unicode string.
   *
   * @since 5.0.0
   */
  unicode_string() { m_data.push_back(0); }

  /**
   * @brief Creates a Unicode string based on the supplied values.
   *
   * @param codes the list of glyphs that will be used.
   *
   * @since 5.0.0
   */
  unicode_string(std::initializer_list<unicode> codes)
  {
    reserve(codes.size() + 1);
    m_data.insert(m_data.end(), codes.begin(), codes.end());
    m_data.push_back(0);
  }

  /**
   * @brief Reserves enough memory to hold the specified amount of elements.
   *
   * @details Use this method to optimize additions to the string when you
   * know or can approximate the amount of elements that will be added. This
   * can reduce the amount of unnecessary allocations and copies of the
   * underlying array.
   *
   * @param n the amount of elements to allocate memory for.
   *
   * @since 5.0.0
   */
  void reserve(size_type n) { m_data.reserve(n); }

  /**
   * @brief Appends a Unicode glyph to the end of the string.
   *
   * @param ch the glyph that will be appended.
   *
   * @since 5.0.0
   */
  void append(unicode ch) { m_data.insert(m_data.end() - 1, ch); }

  /**
   * @brief Appends a series of glyphs to the string.
   *
   * @tparam First the type of the first glyph, always `unicode`.
   * @tparam Args the types of the other glyphs, always `unicode`.
   *
   * @param first the first glyph that will be added.
   * @param codes the other glyphs that will be added.
   *
   * @since 5.0.0
   */
  template <typename First, typename... Args>
  void append(First first, Args... codes)
  {
    static_assert(std::is_same_v<unicode, First>);
    append(first);
    append(codes...);
  }

  /**
   * @copydoc append(unicode)
   */
  void operator+=(unicode ch) { append(ch); }

  /**
   * @brief Removes the last element from the string.
   *
   * @details This method has no effect if the string is empty.
   *
   * @since 5.0.0
   */
  void pop_back()
  {
    if (!empty()) {
      m_data.erase(m_data.end() - 2);
    }
  }

  /**
   * @brief Returns the number of elements stored in the string.
   *
   * @note This method does *not* include the null-terminator.
   *
   * @return the number of elements in the string.
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto size() const noexcept -> size_type
  {
    return m_data.size() - 1;
  }

  /**
   * @brief Returns the capacity of the string.
   *
   * @return the capacity of the string (the amount of elements that can be
   * stored before needing to allocate more memory).
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto capacity() const noexcept -> size_type
  {
    return m_data.capacity();
  }

  /**
   * @brief Indicates whether or not the string is empty.
   *
   * @note The string is considered empty if the only element is the
   * null-terminator.
   *
   * @return `true` if the string is empty; `false` otherwise.
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto empty() const noexcept -> bool
  {
    return m_data.size() == 1;
  }

  /**
   * @brief Returns a pointer to the first glyph.
   *
   * @return a pointer to the first glyph.
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto data() noexcept -> pointer { return m_data.data(); }

  /**
   * @copydoc data
   */
  [[nodiscard]] auto data() const noexcept -> const_pointer
  {
    return m_data.data();
  }

  /**
   * @brief Returns an iterator that points to the first element in the string.
   *
   * @details Iteration using the iterator is done consecutively, as you
   * would expect.
   *
   * @return an iterator that points to the first element in the string.
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto begin() noexcept -> iterator { return m_data.begin(); }

  /**
   * @copydoc begin
   */
  [[nodiscard]] auto begin() const noexcept -> const_iterator
  {
    return m_data.begin();
  }

  /**
   * @brief Returns an iterator that points one-past the last element in the
   * string.
   *
   * @note The null-terminator is purposefully skipped.
   *
   * @return an iterator that points one-past the last element in the
   * string.
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto end() noexcept -> iterator { return m_data.end() - 1; }

  /**
   * @copydoc end
   */
  [[nodiscard]] auto end() const noexcept -> const_iterator
  {
    return m_data.end() - 1;
  }

  /**
   * @brief Returns the element at the specified index.
   *
   * @details This method will throw an exception if the supplied index is
   * out-of-bounds.
   *
   * @param index the index of the desired element.
   *
   * @return the element at the specified index.
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto at(size_type index) -> reference
  {
    return m_data.at(index);
  }

  /**
   * @copydoc at
   */
  [[nodiscard]] auto at(size_type index) const -> const_reference
  {
    return m_data.at(index);
  }

  /**
   * @brief Returns the element at the specified index.
   *
   * @pre `index` **must** be in the range [0, `size()`);
   *
   * @details This method will does *not* perform bounds-checking. However, in
   * debug-mode, an assertion will abort the program if the supplied index is
   * out-of-bounds.
   *
   * @param index the index of the desired element.
   *
   * @return the element at the specified index.
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto operator[](size_type index) noexcept -> reference
  {
    assert(index < m_data.size());
    return m_data[index];
  }

  /**
   * @copydoc operator[]
   */
  [[nodiscard]] auto operator[](size_type index) const noexcept
      -> const_reference
  {
    assert(index < m_data.size());
    return m_data[index];
  }

 private:
  std::vector<unicode> m_data;
};

/**
 * @brief Indicates whether or not two Unicode strings are the same.
 *
 * @param lhs the left-hand side string.
 * @param rhs the right-hand side string.
 *
 * @return `true` if the strings are the same; `false` otherwise.
 *
 * @since 5.0.0
 */
[[nodiscard]] inline auto operator==(const unicode_string& lhs,
                                     const unicode_string& rhs) -> bool
{
  if (lhs.size() != rhs.size()) {
    return false;
  }

  for (unicode_string::size_type index = 0; index < lhs.size(); ++index) {
    const auto a = lhs.at(index);
    const auto b = rhs.at(index);
    if (a != b) {
      return false;
    }
  }

  return true;
}

/**
 * @brief Indicates whether or not two Unicode strings aren't the same.
 *
 * @param lhs the left-hand side string.
 * @param rhs the right-hand side string.
 *
 * @return `true` if the strings are the same; `false` otherwise.
 *
 * @since 5.0.0
 */
[[nodiscard]] inline auto operator!=(const unicode_string& lhs,
                                     const unicode_string& rhs) -> bool
{
  return !(lhs == rhs);
}

namespace literals {

/**
 * @brief Creates a `unicode` value from a `char`.
 *
 * @param c the character used to create the unicode value.
 *
 * @return a `unicode` value.
 *
 * @since 5.0.0
 */
inline constexpr auto operator""_uni(char c) noexcept -> unicode
{
  return static_cast<unicode>(c);
}

/**
 * @brief Creates a `unicode` value from a integral value.
 *
 * @param i the integer used to create the unicode value.
 *
 * @return a `unicode` value.
 *
 * @since 5.0.0
 */
inline constexpr auto operator""_uni(unsigned long long int i) noexcept
    -> unicode
{
  return static_cast<unicode>(i);
}

}  // namespace literals

}  // namespace cen

#endif  // CENTURION_UNICODE_STRING_HEADER
