#ifndef CENTURION_DETAIL_ARRAY_UTILS_HPP_
#define CENTURION_DETAIL_ARRAY_UTILS_HPP_

#include <array>    // array, to_array
#include <cstddef>  // size_t

#include "../common.hpp"
#include "../features.hpp"

/// \cond FALSE

namespace cen::detail {

template <typename T, std::size_t Size>
constexpr void assign(const std::array<T, Size>& array, T (&out)[Size])
{
  std::size_t index = 0;
  for (auto&& value : array) {
    out[index] = value;
    ++index;
  }
}

template <typename T, std::size_t Size>
[[nodiscard]] constexpr auto to_array(const T (&data)[Size]) -> std::array<T, Size>
{
#if CENTURION_HAS_FEATURE_TO_ARRAY
  return std::to_array(data);
#else
  std::array<T, Size> array;  // NOLINT

  for (std::size_t i = 0; i < Size; ++i) {
    array[i] = data[i];
  }

  return array;
#endif  // CENTURION_HAS_FEATURE_TO_ARRAY
}

}  // namespace cen::detail

/// \endcond

#endif  // CENTURION_DETAIL_ARRAY_UTILS_HPP_
