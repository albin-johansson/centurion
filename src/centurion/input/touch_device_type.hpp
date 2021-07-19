#ifndef CENTURION_TOUCH_DEVICE_TYPE_HEADER
#define CENTURION_TOUCH_DEVICE_TYPE_HEADER

#include <SDL.h>

namespace cen {
namespace touch {

/// \addtogroup input
/// \{

/**
 * \enum device_type
 *
 * \brief Provides values that represent different touch device types.
 *
 * \see `SDL_TouchDeviceType`
 *
 * \todo Centurion 7: Rename to touch_device_type and move out of touch namespace.
 *
 * \since 4.3.0
 */
enum class device_type
{
  // clang-format off
  invalid = SDL_TOUCH_DEVICE_INVALID,                      ///< Invalid touch device.
  direct = SDL_TOUCH_DEVICE_DIRECT,                        ///< Touch screen with window-relative coordinates.
  indirect_absolute = SDL_TOUCH_DEVICE_INDIRECT_ABSOLUTE,  ///< Trackpad with absolute device coordinates.
  indirect_relative = SDL_TOUCH_DEVICE_INDIRECT_RELATIVE   ///< Trackpad with screen cursor-relative coordinates.
  // clang-format on
};

/// \name Touch device comparison operators
/// \{

/**
 * \brief Indicates whether or not two touch device types are the same.
 *
 * \param lhs the left-hand side touch device type.
 * \param rhs the right-hand side touch device type.
 *
 * \return `true` if the values are the same; `false` otherwise.
 *
 * \since 4.3.0
 */
[[nodiscard]] constexpr auto operator==(const device_type lhs,
                                        const SDL_TouchDeviceType rhs) noexcept -> bool
{
  return static_cast<SDL_TouchDeviceType>(lhs) == rhs;
}

/// \copydoc operator==(device_type, SDL_TouchDeviceType)
[[nodiscard]] constexpr auto operator==(const SDL_TouchDeviceType lhs,
                                        const device_type rhs) noexcept -> bool
{
  return rhs == lhs;
}

/**
 * \brief Indicates whether or not two touch device types aren't the same.
 *
 * \param lhs the left-hand side touch device type.
 * \param rhs the right-hand side touch device type.
 *
 * \return `true` if the values aren't the same; `false` otherwise.
 *
 * \since 4.3.0
 */
[[nodiscard]] constexpr auto operator!=(const device_type lhs,
                                        const SDL_TouchDeviceType rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \copydoc operator!=(device_type, SDL_TouchDeviceType)
[[nodiscard]] constexpr auto operator!=(const SDL_TouchDeviceType lhs,
                                        const device_type rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \} End of touch device comparison operators

/// \} End of group input

}  // namespace touch

// Added for consistency with rest of codebase (no classes in nested namespaces)
using touch_device_type = touch::device_type;

}  // namespace cen

#endif  // CENTURION_TOUCH_DEVICE_TYPE_HEADER
