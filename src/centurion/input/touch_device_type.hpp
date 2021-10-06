#ifndef CENTURION_TOUCH_DEVICE_TYPE_HEADER
#define CENTURION_TOUCH_DEVICE_TYPE_HEADER

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../core/exception.hpp"

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

/// \addtogroup input
/// \{

// Added for consistency with rest of codebase (no classes in nested namespaces)
using touch_device_type = touch::device_type;

[[nodiscard]] constexpr auto to_string(touch_device_type type) -> std::string_view;

namespace touch {

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of a touch device type enumerator.
 *
 * \param stream the output stream that will be used.
 * \param type the enumerator that will be printed.
 *
 * \see `to_string(touch_device_type)`
 *
 * \return the used stream.
 *
 * \since 6.2.0
 */
inline auto operator<<(std::ostream& stream, const touch_device_type type) -> std::ostream&
{
  return stream << to_string(type);
}

/// \} End of streaming

}  // namespace touch

/// \name String conversions
/// \{

/**
 * \brief Returns a textual version of the supplied touch device type.
 *
 * \details This function returns a string that mirrors the name of the enumerator, e.g.
 * `to_string(device_type::direct) == "direct"`.
 *
 * \param type the enumerator that will be converted.
 *
 * \return a string that mirrors the name of the enumerator.
 *
 * \throws cen_error if the enumerator is not recognized.
 *
 * \since 6.2.0
 */
[[nodiscard]] constexpr auto to_string(const touch_device_type type) -> std::string_view
{
  switch (type) {
    case touch_device_type::invalid:
      return "invalid";

    case touch_device_type::direct:
      return "direct";

    case touch_device_type::indirect_absolute:
      return "indirect_absolute";

    case touch_device_type::indirect_relative:
      return "indirect_relative";

    default:
      throw cen_error{"Did not recognize touch device type!"};
  }
}

/// \} End of string conversions

/// \} End of group input

}  // namespace cen

#endif  // CENTURION_TOUCH_DEVICE_TYPE_HEADER
