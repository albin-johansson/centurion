#ifndef CENTURION_TOUCH_HPP_
#define CENTURION_TOUCH_HPP_

#include <SDL.h>

#include <optional>     // optional
#include <ostream>      // ostream
#include <string_view>  // string_view

#include "common.hpp"
#include "input.hpp"

namespace cen {

/**
 * \ingroup input
 *
 * \defgroup touch Touch
 *
 * \brief Provides the touch API.
 */

/// \addtogroup touch
/// \{

using touch_id = SDL_TouchID;

/**
 * \brief Returns the device ID used for mouse events simulated with touch input.
 *
 * \return a device identifier.
 */
[[nodiscard]] constexpr auto touch_mouse_id() noexcept -> uint32
{
  return SDL_TOUCH_MOUSEID;
}

/**
 * \brief Returns the touch ID used by touch events simulated with mouse input.
 *
 * \return a touch identifier.
 */
[[nodiscard]] constexpr auto mouse_touch_id() noexcept -> touch_id
{
  return SDL_MOUSE_TOUCHID;
}

/**
 * \brief Represents different touch device types.
 *
 * \see `SDL_TouchDeviceType`
 */
enum class touch_device_type
{
  invalid = SDL_TOUCH_DEVICE_INVALID,  ///< Invalid touch device.

  /**
   * \brief Touch screen with window-relative coordinates.
   */
  direct = SDL_TOUCH_DEVICE_DIRECT,

  /**
   * \brief Trackpad with absolute device coordinates.
   */
  indirect_absolute = SDL_TOUCH_DEVICE_INDIRECT_ABSOLUTE,

  /**
   * \brief Trackpad with screen cursor-relative coordinates.
   */
  indirect_relative = SDL_TOUCH_DEVICE_INDIRECT_RELATIVE
};

/// \name Touch device type functions
/// \{

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
      throw exception{"Did not recognize touch device type!"};
  }
}

inline auto operator<<(std::ostream& stream, const touch_device_type type) -> std::ostream&
{
  return stream << to_string(type);
}

/// \} End of touch device type functions

/**
 * \brief Provides a read-only view into the state of a touch finger.
 */
class finger final
{
 public:
  using id_type = SDL_FingerID;

  /// \name Factory functions
  /// \{

  /**
   * \brief Returns a finger associated with a touch device.
   *
   * \param id the identifier of the touch device.
   * \param index the index of the finger.
   *
   * \return the associated finger; an empty optional is returned upon failure.
   */
  [[nodiscard]] static auto find(const touch_id id, const int index) noexcept
      -> std::optional<finger>
  {
    if (const auto* data = SDL_GetTouchFinger(id, index)) {
      return finger{*data};
    }
    else {
      return std::nullopt;
    }
  }

  /// \} End of factory functions

  /**
   * \brief Returns the identifier associated with the finger.
   *
   * \return the finger ID.
   */
  [[nodiscard]] auto id() const noexcept -> id_type { return mFinger.id; }

  /**
   * \brief Returns the x-coordinate of the finger.
   *
   * \return the finger x-coordinate.
   */
  [[nodiscard]] auto x() const noexcept -> float { return mFinger.x; }

  /**
   * \brief Returns the y-coordinate of the finger.
   *
   * \return the finger y-coordinate.
   */
  [[nodiscard]] auto y() const noexcept -> float { return mFinger.y; }

  /**
   * \brief Returns the pressure of the finger.
   *
   * \return the finger pressure.
   */
  [[nodiscard]] auto pressure() const noexcept -> float { return mFinger.pressure; }

  [[nodiscard]] auto get() const noexcept -> const SDL_Finger& { return mFinger; }

 private:
  SDL_Finger mFinger{};

  explicit finger(const SDL_Finger& other) noexcept : mFinger{other} {}
};

/// \name Touch device queries
/// \{

/**
 * \brief Returns the number of registered touch devices.
 *
 * \return the touch device count.
 */
[[nodiscard]] inline auto touch_device_count() noexcept -> int
{
  return SDL_GetNumTouchDevices();
}

/**
 * \brief Returns the identifier associated with a touch device.
 *
 * \param index the device index of the desired touch device.
 *
 * \return the touch device identifier; an empty optional is returned upon failure.
 */
[[nodiscard]] inline auto get_touch_device(const int index) noexcept -> std::optional<touch_id>
{
  const auto device = SDL_GetTouchDevice(index);
  if (device != 0) {
    return device;
  }
  else {
    return std::nullopt;
  }
}

/**
 * \brief Returns the type of a touch device.
 *
 * \param id the identifier associated with the touch device that will be queried.
 *
 * \return the touch device type.
 */
[[nodiscard]] inline auto get_touch_type(const touch_id id) noexcept -> touch_device_type
{
  return static_cast<touch_device_type>(SDL_GetTouchDeviceType(id));
}

/**
 * \brief Returns the number of active fingers for a touch device.
 *
 * \param id the identifier associated with the touch device that will be queried.
 *
 * \return the touch device finger count.
 */
[[nodiscard]] inline auto get_touch_finger_count(const touch_id id) noexcept -> int
{
  return SDL_GetNumTouchFingers(id);
}

/// \} End of touch device queries

/// \} End of group touch

}  // namespace cen

#endif  // CENTURION_TOUCH_HPP_