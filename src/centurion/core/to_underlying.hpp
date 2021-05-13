#ifndef CENTURION_TO_UNDERLYING_HEADER
#define CENTURION_TO_UNDERLYING_HEADER

#include <type_traits>  // underlying_type_t, enable_if_t, is_enum_v

namespace cen {

/**
 * \brief Converts an enum value to an integral value using the underlying type.
 *
 * \ingroup core
 *
 * \note If you're using C++23, see `std::to_underlying()`.
 *
 * \tparam Enum the enum type.
 *
 * \param value the enum value that will be converted.
 *
 * \return the value of the enum, in the underlying type.
 *
 * \since 6.0.0
 */
template <typename Enum, std::enable_if_t<std::is_enum_v<Enum>, int> = 0>
[[nodiscard]] constexpr auto to_underlying(const Enum value) noexcept
    -> std::underlying_type_t<Enum>
{
  return static_cast<std::underlying_type_t<Enum>>(value);
}

}  // namespace cen

#endif  // CENTURION_TO_UNDERLYING_HEADER
