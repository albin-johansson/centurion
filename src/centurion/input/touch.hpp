#ifndef CENTURION_INPUT_TOUCH_HPP_
#define CENTURION_INPUT_TOUCH_HPP_

#include <SDL.h>

#include <optional>  // optional

#include "../common.hpp"
#include "button_state.hpp"
#include "touch_device_type.hpp"

/**
 * \namespace cen::touch
 *
 * \ingroup input
 *
 * \brief Provides the touch API components and methods.
 *
 * \since 4.3.0
 */
namespace cen::touch {

/// \addtogroup input
/// \{

/**
 * \struct finger_state
 *
 * \brief Represents the state of a finger.
 *
 * \todo Centurion 7: Rename to touch_finger_state and move out of touch namespace.
 *
 * \since 5.2.0
 */
struct finger_state final {
  ButtonState state;  ///< Whether or not the finger is pressed or release.
  float x;            ///< The current x-coordinate.
  float y;            ///< The current y-coordinate.
  float pressure;     ///< The current applied pressure.
};

/**
 * \brief Returns the number of registered touch devices.
 *
 * \return the number of registered touch devices.
 *
 * \since 4.3.0
 */
[[nodiscard]] inline auto device_count() noexcept -> int
{
  return SDL_GetNumTouchDevices();
}

/**
 * \brief Returns the touch device ID associated with the specified index.
 *
 * \param index the index of the desired touch device.
 *
 * \return the touch device ID associated with the index; `std::nullopt` if there is no
 * such value.
 *
 * \since 4.3.0
 */
[[nodiscard]] inline auto get_device(const int index) noexcept -> std::optional<SDL_TouchID>
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
 * \param id the touch device that will be queried.
 *
 * \return the type of the specified touch device.
 *
 * \since 4.3.0
 */
[[nodiscard]] inline auto type_of(const SDL_TouchID id) noexcept -> device_type
{
  return static_cast<device_type>(SDL_GetTouchDeviceType(id));
}

/**
 * \brief Returns the number of active fingers for a given touch device.
 *
 * \param id the touch device that will be queried.
 *
 * \return the amount of active fingers in a touch device.
 *
 * \since 4.3.0
 */
[[nodiscard]] inline auto finger_count(const SDL_TouchID id) noexcept -> int
{
  return SDL_GetNumTouchFingers(id);
}

/**
 * \brief Returns the finger associated with the specified touch ID and index.
 *
 * \param id the touch ID of the finger.
 * \param index the index of the finger object.
 *
 * \return the associated finger; `std::nullopt` if no such instance could be obtained.
 *
 * \since 4.3.0
 */
[[nodiscard]] inline auto get_finger(const SDL_TouchID id, const int index) noexcept
    -> std::optional<SDL_Finger>
{
  if (const auto* finger = SDL_GetTouchFinger(id, index)) {
    return *finger;
  }
  else {
    return std::nullopt;
  }
}

/**
 * \brief Returns the device ID used for mouse events simulated with touch input.
 *
 * \return a device ID.
 *
 * \since 4.3.0
 */
[[nodiscard]] constexpr auto touch_mouse_id() noexcept -> Uint32
{
  return SDL_TOUCH_MOUSEID;
}

/**
 * \brief Returns the touch ID used by touch events simulated with mouse input.
 *
 * \return the touch ID used by touch events simulated with mouse input.
 *
 * \since 4.3.0
 */
[[nodiscard]] constexpr auto mouse_touch_id() noexcept -> SDL_TouchID
{
  return SDL_MOUSE_TOUCHID;
}

/// \} End of group input

}  // namespace cen::touch

namespace cen {

/// \addtogroup input
/// \{

// Added for consistency with rest of codebase (no classes in nested namespaces)
using touch_finger_state = touch::finger_state;

/// \} End of group input

}  // namespace cen

#endif  // CENTURION_INPUT_TOUCH_HPP_