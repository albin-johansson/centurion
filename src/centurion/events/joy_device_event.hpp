#ifndef CENTURION_JOY_DEVICE_EVENT_HEADER
#define CENTURION_JOY_DEVICE_EVENT_HEADER

#include <SDL.h>

#include "../core/integers.hpp"
#include "common_event.hpp"

namespace cen {

/// \addtogroup event
/// \{

/**
 * \class joy_device_event
 *
 * \brief Represents an event triggered by adding or removing a joystick device.
 *
 * \see `SDL_JoyDeviceEvent`
 *
 * \since 4.0.0
 */
class joy_device_event final : public common_event<SDL_JoyDeviceEvent>
{
 public:
  /**
   * \brief Creates a joystick device event of type `joystick_device_added`.
   *
   * \since 4.0.0
   */
  joy_device_event() noexcept : common_event{event_type::joystick_device_added}
  {}

  /**
   * \brief Creates a joy_device_event that is based on the supplied SDL event.
   *
   * \param event the SDL event that will be copied.
   *
   * \since 4.0.0
   */
  explicit joy_device_event(const SDL_JoyDeviceEvent& event) noexcept : common_event{event}
  {}

  /**
   * \brief Sets the joystick device index or instance ID, depending on the type
   * of the event.
   *
   * \param which the joystick device index or instance ID.
   *
   * \since 4.0.0
   */
  void set_which(const i32 which) noexcept
  {
    m_event.which = which;
  }

  /**
   * \brief Returns the joystick device index or instance ID.
   *
   * \details The returned value is the joystick device index if the type is
   * `JoystickDeviceAdded`, or the joystick instance ID if the type is
   * `JoystickDeviceRemoved`.
   *
   * \return the joystick device index or instance ID.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto which() const noexcept -> i32
  {
    return m_event.which;
  }
};

/// \name SDL event conversions
/// \{

template <>
inline auto as_sdl_event(const common_event<SDL_JoyDeviceEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.jdevice = event.get();
  return e;
}

/// \} End of SDL event conversions

/// \} End of group event

}  // namespace cen

#endif  // CENTURION_JOY_DEVICE_EVENT_HEADER
