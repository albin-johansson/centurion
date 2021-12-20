#ifndef CENTURION_UNICODE_HPP_
#define CENTURION_UNICODE_HPP_

#include <cassert>           // assert
#include <initializer_list>  // initializer_list
#include <type_traits>       // is_same_v, decay_t
#include <vector>            // vector

#include "common.hpp"

namespace cen {

/* Represents a null-terminated string encoded in Unicode. */
class UnicodeString final {
 public:
  using value_type = std::vector<Unicode>::value_type;

  using pointer = std::vector<Unicode>::pointer;
  using const_pointer = std::vector<Unicode>::const_pointer;

  using reference = std::vector<Unicode>::reference;
  using const_reference = std::vector<Unicode>::const_reference;

  using iterator = std::vector<Unicode>::iterator;
  using const_iterator = std::vector<Unicode>::const_iterator;

  using reverse_iterator = std::vector<Unicode>::reverse_iterator;
  using const_reverse_iterator = std::vector<Unicode>::const_reverse_iterator;

  using size_type = std::vector<Unicode>::size_type;
  using difference_type = std::vector<Unicode>::difference_type;

  UnicodeString() { mData.push_back(0); }

  UnicodeString(std::initializer_list<Unicode> codes)
  {
    reserve(codes.size() + 1);
    mData.insert(mData.end(), codes.begin(), codes.end());
    mData.push_back(0);
  }

  void reserve(const size_type n) { mData.reserve(n); }

  void append(const Unicode ch) { mData.insert(mData.end() - 1, ch); }

  template <typename... Character>
  void append(Character... code)
  {
    static_assert(sizeof...(Character) != 0, "Must append at least 1 value!");
    static_assert((std::is_convertible_v<Character, Unicode> && ...),
                  "Must append Unicode values!");
    (append(static_cast<Unicode>(code)), ...);
  }

  void operator+=(const Unicode ch) { append(ch); }

  void pop_back()
  {
    if (!empty()) {
      mData.erase(mData.end() - 2);
    }
  }

  [[nodiscard]] auto size() const noexcept -> size_type { return mData.size() - 1; }

  [[nodiscard]] auto capacity() const noexcept -> size_type { return mData.capacity(); }

  [[nodiscard]] auto empty() const noexcept -> bool { return mData.size() == 1; }

  [[nodiscard]] auto data() noexcept -> pointer { return mData.data(); }
  [[nodiscard]] auto data() const noexcept -> const_pointer { return mData.data(); }

  [[nodiscard]] auto begin() noexcept -> iterator { return mData.begin(); }
  [[nodiscard]] auto begin() const noexcept -> const_iterator { return mData.begin(); }

  [[nodiscard]] auto end() noexcept -> iterator { return mData.end() - 1; }
  [[nodiscard]] auto end() const noexcept -> const_iterator { return mData.end() - 1; }

  /* Checked element retrieval. */
  [[nodiscard]] auto at(const size_type index) -> reference { return mData.at(index); }

  [[nodiscard]] auto at(const size_type index) const -> const_reference
  {
    return mData.at(index);
  }

  /* Unchecked element retrieval. */
  [[nodiscard]] auto operator[](const size_type index) noexcept(on_msvc) -> reference
  {
    assert(index < mData.size());
    return mData[index];
  }

  [[nodiscard]] auto operator[](const size_type index) const noexcept(on_msvc)
      -> const_reference
  {
    assert(index < mData.size());
    return mData[index];
  }

  template <typename Archive>
  void serialize(Archive& archive)
  {
    archive(mData);
  }

 private:
  std::vector<Unicode> mData;
};

[[nodiscard]] inline auto operator==(const UnicodeString& a, const UnicodeString& b) -> bool
{
  if (a.size() != b.size()) {
    return false;
  }

  for (UnicodeString::size_type index = 0; index < a.size(); ++index) {
    const auto aChar = a.at(index);
    const auto bChar = b.at(index);
    if (aChar != bChar) {
      return false;
    }
  }

  return true;
}

[[nodiscard]] inline auto operator!=(const UnicodeString& a, const UnicodeString& b) -> bool
{
  return !(a == b);
}

/// \} End of Unicode string comparison operators

}  // namespace cen

#endif  // CENTURION_UNICODE_HPP_
