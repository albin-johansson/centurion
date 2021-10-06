#ifndef CENTURION_SFINAE_HEADER
#define CENTURION_SFINAE_HEADER

#include <type_traits>  // enable_if_t, is_same_v, is_integral_v, is_floating_point_v, ...

namespace cen {

/// \addtogroup core
/// \{

// clang-format off

/// Enables a template if the type is either integral of floating-point, but not a boolean.
template <typename T>
using enable_if_number_t = std::enable_if_t<!std::is_same_v<T, bool> &&
                                            (std::is_integral_v<T> ||
                                             std::is_floating_point_v<T>), int>;

// clang-format on

/// Enables a template if the type is a pointer.
template <typename T>
using enable_if_pointer_v = std::enable_if_t<std::is_pointer_v<T>, int>;

/// Enables a template if T is convertible to any of the specified types.
template <typename T, typename... Args>
using enable_if_convertible_t = std::enable_if_t<(std::is_convertible_v<T, Args> || ...), int>;

/// \} End of group core

}  // namespace cen

#endif  // CENTURION_SFINAE_HEADER
