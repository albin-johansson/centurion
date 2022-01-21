#ifndef CENTURION_UNICODE_HPP_
#define CENTURION_UNICODE_HPP_

#include <cassert>           // assert
#include <initializer_list>  // initializer_list
#include <string_view>       // u16string_view
#include <type_traits>       // is_same_v, decay_t
#include <vector>            // vector

#include "common.hpp"

namespace cen {

/**
 * \ingroup text
 * \defgroup unicode Unicode
 *
 * \brief Contains Unicode-related utilities.
 */

/// \addtogroup unicode
/// \{

/**
 * \brief Represents a null-terminated string of Unicode characters.
 *
 * \serializable
 */
class unicode_string final {
 public:
  using value_type = std::vector<unicode_t>::value_type;

  using pointer = std::vector<unicode_t>::pointer;
  using const_pointer = std::vector<unicode_t>::const_pointer;

  using reference = std::vector<unicode_t>::reference;
  using const_reference = std::vector<unicode_t>::const_reference;

  using iterator = std::vector<unicode_t>::iterator;
  using const_iterator = std::vector<unicode_t>::const_iterator;

  using size_type = std::vector<unicode_t>::size_type;

  /**
   * \brief Creates an empty string.
   */
  unicode_string() { mData.push_back(0); }

  /**
   * \brief Creates a Unicode string from a `char16_t` string view.
   *
   * \param str the string that will be copied.
   */
  /* implicit */ unicode_string(const std::u16string_view str)
  {
    reserve(str.size());

    for (const auto ch : str) {
      mData.push_back(ch);
    }

    mData.push_back(0);
  }

  /**
   * \brief Creates a Unicode string with the supplied characters.
   *
   * \param codes the list of glyphs that will be used.
   */
  unicode_string(std::initializer_list<unicode_t> codes)
  {
    reserve(codes.size() + 1);
    mData.insert(mData.end(), codes.begin(), codes.end());
    mData.push_back(0);
  }

  /**
   * \brief Reserves enough memory to hold the specified amount of elements.
   *
   * \details Use this function to optimize additions to the string when you know or can
   * approximate the amount of elements that will be added. This can reduce the amount of
   * unnecessary allocations and copies of the underlying array.
   *
   * \param n the amount of elements to allocate memory for.
   */
  void reserve(const size_type n) { mData.reserve(n + 1u); }

  /**
   * \brief Appends a Unicode glyph to the end of the string.
   *
   * \param ch the glyph that will be appended.
   */
  void append(const unicode_t ch) { mData.insert(mData.end() - 1, ch); }

  /**
   * \brief Appends a series of glyphs to the string.
   *
   * \tparam Character the types of the other glyphs, always `unicode_t`.
   *
   * \param code the pack of glyphs that will be added, cannot be empty.
   */
  template <typename... Character>
  void append(Character... code)
  {
    static_assert(sizeof...(Character) != 0, "Must append at least 1 value!");
    static_assert((std::is_convertible_v<Character, unicode_t> && ...),
                  "Must append unicode_t values!");
    (append(static_cast<unicode_t>(code)), ...);
  }

  /// \copydoc append()
  void operator+=(const unicode_t ch) { append(ch); }

  /**
   * \brief Removes the last element from the string.
   *
   * \details This function has no effect if the string is empty.
   */
  void pop_back()
  {
    if (!empty()) {
      mData.erase(mData.end() - 2);
    }
  }

  /**
   * \brief Returns the element at the specified index.
   *
   * \param index the index of the desired element.
   *
   * \return the element at the specified index.
   *
   * \throws exception if the index is invalid.
   */
  [[nodiscard]] auto at(const size_type index) -> reference
  {
    if (is_valid_index(index)) {
      return mData[index];
    }
    else {
      throw exception{"Invalid unicode string index!"};
    }
  }

  /// \copydoc at()
  [[nodiscard]] auto at(const size_type index) const -> const_reference
  {
    if (is_valid_index(index)) {
      return mData[index];
    }
    else {
      throw exception{"Invalid unicode string index!"};
    }
  }

  /**
   * \brief Returns the element at the specified index.
   *
   * \pre the index must be valid.
   *
   * \details This function performs no bounds checking.
   *
   * \param index the index of the desired element.
   *
   * \return the element at the specified index.
   */
  [[nodiscard]] auto operator[](const size_type index) noexcept(on_msvc) -> reference
  {
    assert(is_valid_index(index));
    return mData[index];
  }

  /// \copydoc operator[]
  [[nodiscard]] auto operator[](const size_type index) const noexcept(on_msvc)
      -> const_reference
  {
    assert(is_valid_index(index));
    return mData[index];
  }

  /**
   * \brief Returns the number of characters stored in the string.
   *
   * \note This function does not include the null-terminator.
   *
   * \return the number of elements in the string.
   */
  [[nodiscard]] auto size() const noexcept -> size_type
  {
    assert(!mData.empty());
    return mData.size() - 1u;
  }

  /**
   * \brief Returns the capacity of the string.
   *
   * \details The capacity is the amount of elements that can be stored before needing to
   * allocate more memory.
   *
   * \return the string character capacity.
   */
  [[nodiscard]] auto capacity() const noexcept -> size_type
  {
    assert(mData.capacity() >= 1u);
    return mData.capacity() - 1u;
  }

  /**
   * \brief Indicates whether the string is empty.
   *
   * \note The string is considered empty if the only element is the null-terminator.
   *
   * \return `true` if the string is empty; `false` otherwise.
   */
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

/// \name Unicode string functions
/// \{

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

/// \} End of unicode string functions

/// \} End of group unicode

}  // namespace cen

#endif  // CENTURION_UNICODE_HPP_
