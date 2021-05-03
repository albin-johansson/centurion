#ifndef CENTURION_DETAIL_CLAMP_HEADER
#define CENTURION_DETAIL_CLAMP_HEADER

#include <cassert>  // assert

/// \cond FALSE
namespace cen::detail {

// clang-format off

/**
 * \brief Clamps a value to be within the range [min, max].
 *
 * \pre `min` must be less than or equal to `max`.
 *
 * \note The standard library provides `std::clamp`, but it isn't mandated to be
 * `noexcept` (although MSVC does mark it as `noexcept`), which is the reason this
 * function exists.
 *
 * \tparam T the type of the values.
 *
 * \param value the value that will be clamped.
 * \param min the minimum value (inclusive).
 * \param max the maximum value (inclusive).
 *
 * \return the clamped value.
 *
 * \since 5.1.0
 */
template <typename T>
[[nodiscard]] constexpr auto clamp(const T& value,
                                   const T& min,
                                   const T& max)
    noexcept(noexcept(value < min) && noexcept(value > max)) -> T
{
  assert(min <= max);
  if (value < min)
  {
    return min;
  }
  else if (value > max)
  {
    return max;
  }
  else
  {
    return value;
  }
}

// clang-format on

}  // namespace cen::detail
/// \endcond

#endif  // CENTURION_DETAIL_CLAMP_HEADER
