#ifndef CENTURION_UNICODE_STRING_HEADER
#define CENTURION_UNICODE_STRING_HEADER

#include <cassert>           // assert
#include <initializer_list>  // initializer_list
#include <type_traits>       // is_same_v, decay_t
#include <vector>            // vector

#include "../compiler/compiler.hpp"
#include "../core/integers.hpp"

namespace cen {

/// \addtogroup video
/// \{

/**
 * \typedef unicode
 *
 * \brief The representation of Unicode glyphs.
 *
 * \since 5.0.0
 */
using unicode = u16;

/**
 * \class unicode_string
 *
 * \brief Represents a null-terminated string encoded in unicode.
 *
 * \serializable
 *
 * \details This class is a wrapper around a `std::vector<unicode>`, that provides a
 * similar interface to that of `std::string`.
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

  /// \name Construction
  /// \{

  /**
   * \brief Creates an empty Unicode string.
   *
   * \since 5.0.0
   */
  unicode_string()
  {
    m_data.push_back(0);
  }

  /**
   * \brief Creates a Unicode string based on the supplied values.
   *
   * \param codes the list of glyphs that will be used.
   *
   * \since 5.0.0
   */
  unicode_string(std::initializer_list<unicode> codes)
  {
    reserve(codes.size() + 1);
    m_data.insert(m_data.end(), codes.begin(), codes.end());
    m_data.push_back(0);
  }

  /// \} End of construction

  /**
   * \brief Reserves enough memory to hold the specified amount of elements.
   *
   * \details Use this function to optimize additions to the string when you know or can
   * approximate the amount of elements that will be added. This can reduce the amount of
   * unnecessary allocations and copies of the underlying array.
   *
   * \param n the amount of elements to allocate memory for.
   *
   * \since 5.0.0
   */
  void reserve(const size_type n)
  {
    m_data.reserve(n);
  }

  /**
   * \brief Appends a Unicode glyph to the end of the string.
   *
   * \param ch the glyph that will be appended.
   *
   * \since 5.0.0
   */
  void append(const unicode ch)
  {
    m_data.insert(m_data.end() - 1, ch);
  }

  /**
   * \brief Appends a series of glyphs to the string.
   *
   * \tparam First the type of the first glyph, always `unicode`.
   * \tparam Character the types of the other glyphs, always `unicode`.
   *
   * \param code the pack of glyphs that will be added, cannot be empty.
   *
   * \since 5.0.0
   */
  template <typename... Character>
  void append(Character... code)
  {
    static_assert(sizeof...(Character) != 0, "Function requires at least 1 argument!");
    static_assert((std::is_same_v<unicode, std::decay_t<Character>> && ...),
                  "Cannot append values that aren't of type \"unicode\"!");
    (append(code), ...);
  }

  /// \copydoc append(unicode)
  void operator+=(const unicode ch)
  {
    append(ch);
  }

  /**
   * \brief Removes the last element from the string.
   *
   * \details This function has no effect if the string is empty.
   *
   * \since 5.0.0
   */
  void pop_back()
  {
    if (!empty()) {
      m_data.erase(m_data.end() - 2);
    }
  }

  /**
   * \brief Returns the number of elements stored in the string.
   *
   * \note This function does *not* include the null-terminator.
   *
   * \return the number of elements in the string.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto size() const noexcept -> size_type
  {
    return m_data.size() - 1;
  }

  /**
   * \brief Returns the capacity of the string.
   *
   * \return the capacity of the string (the amount of elements that can be stored before
   * needing to allocate more memory).
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto capacity() const noexcept -> size_type
  {
    return m_data.capacity();
  }

  /**
   * \brief Indicates whether or not the string is empty.
   *
   * \note The string is considered empty if the only element is the null-terminator.
   *
   * \return `true` if the string is empty; `false` otherwise.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto empty() const noexcept -> bool
  {
    return m_data.size() == 1;
  }

  /**
   * \brief Returns a pointer to the first glyph.
   *
   * \return a pointer to the first glyph.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto data() noexcept -> pointer
  {
    return m_data.data();
  }

  /// \copydoc data
  [[nodiscard]] auto data() const noexcept -> const_pointer
  {
    return m_data.data();
  }

  /**
   * \brief Returns an iterator that points to the first element in the string.
   *
   * \details Iteration using the iterator is done consecutively, as you would expect.
   *
   * \return an iterator that points to the first element in the string.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto begin() noexcept -> iterator
  {
    return m_data.begin();
  }

  /// \copydoc begin
  [[nodiscard]] auto begin() const noexcept -> const_iterator
  {
    return m_data.begin();
  }

  /**
   * \brief Returns an iterator that points one-past the last element in the string.
   *
   * \note The null-terminator is purposefully skipped.
   *
   * \return an iterator that points one-past the last element in the string.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto end() noexcept -> iterator
  {
    return m_data.end() - 1;
  }

  /// \copydoc end
  [[nodiscard]] auto end() const noexcept -> const_iterator
  {
    return m_data.end() - 1;
  }

  /**
   * \brief Returns the element at the specified index.
   *
   * \details This function will throw an exception if the supplied index is
   * out-of-bounds.
   *
   * \param index the index of the desired element.
   *
   * \return the element at the specified index.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto at(const size_type index) -> reference
  {
    return m_data.at(index);
  }

  /// \copydoc at
  [[nodiscard]] auto at(const size_type index) const -> const_reference
  {
    return m_data.at(index);
  }

  /**
   * \brief Returns the element at the specified index.
   *
   * \pre `index` **must** be in the range [0, `size()`);
   *
   * \details This function will does *not* perform bounds-checking. However, in
   * debug-mode, an assertion will abort the program if the supplied index is
   * out-of-bounds.
   *
   * \param index the index of the desired element.
   *
   * \return the element at the specified index.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto operator[](const size_type index) noexcept(on_msvc()) -> reference
  {
    assert(index < m_data.size());
    return m_data[index];
  }

  /// \copydoc operator[]
  [[nodiscard]] auto operator[](const size_type index) const noexcept(on_msvc())
      -> const_reference
  {
    assert(index < m_data.size());
    return m_data[index];
  }

  /**
   * \brief Serializes the string.
   *
   * \details This function expects that the archive provides an overloaded `operator()`,
   * used for serializing data. This API is based on the Cereal serialization library.
   *
   * \tparam Archive the type of the archive.
   *
   * \param archive the archive used to serialize the string.
   *
   * \since 5.3.0
   */
  template <typename Archive>
  void serialize(Archive& archive)
  {
    archive(m_data);
  }

 private:
  std::vector<unicode> m_data;
};

/// \name Unicode string comparison operators
/// \{

/**
 * \brief Indicates whether or not two Unicode strings are the same.
 *
 * \param lhs the left-hand side string.
 * \param rhs the right-hand side string.
 *
 * \return `true` if the strings are the same; `false` otherwise.
 *
 * \since 5.0.0
 */
[[nodiscard]] inline auto operator==(const unicode_string& lhs, const unicode_string& rhs)
    -> bool
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
 * \brief Indicates whether or not two Unicode strings aren't the same.
 *
 * \param lhs the left-hand side string.
 * \param rhs the right-hand side string.
 *
 * \return `true` if the strings are the same; `false` otherwise.
 *
 * \since 5.0.0
 */
[[nodiscard]] inline auto operator!=(const unicode_string& lhs, const unicode_string& rhs)
    -> bool
{
  return !(lhs == rhs);
}

/// \} End of unicode string comparison operators

namespace literals {

/**
 * \brief Creates a `unicode` value from a `char`.
 *
 * \param c the character used to create the unicode value.
 *
 * \return a `unicode` value.
 *
 * \since 5.0.0
 */
constexpr auto operator""_uni(const char c) noexcept -> unicode
{
  return static_cast<unicode>(c);
}

/**
 * \brief Creates a `unicode` value from a integral value.
 *
 * \param i the integer used to create the unicode value.
 *
 * \return a `unicode` value.
 *
 * \since 5.0.0
 */
constexpr auto operator""_uni(const ulonglong i) noexcept -> unicode
{
  return static_cast<unicode>(i);
}

}  // namespace literals

/// \} End of group video

}  // namespace cen

#endif  // CENTURION_UNICODE_STRING_HEADER
