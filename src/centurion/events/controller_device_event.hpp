#ifndef CENTURION_EVENTS_CONTROLLER_DEVICE_EVENT_HPP_
#define CENTURION_EVENTS_CONTROLLER_DEVICE_EVENT_HPP_

#include <SDL.h>

#include "../common.hpp"
#include "event_base.hpp"

namespace cen {

/// \addtogroup event
/// \{

/**
 * \class controller_device_event
 *
 * \brief Represents events related to game controller devices such as adding
 * or removing game controller devices.
 *
 * \see `SDL_ControllerDeviceEvent`
 *
 * \since 4.0.0
 */
class controller_device_event final : public EventBase<SDL_ControllerDeviceEvent> {
 public:
  /**
   * \brief Creates a controller device event of type `controller_device_added`.
   *
   * \since 4.0.0
   */
  controller_device_event() noexcept : EventBase{EventType::ControllerDeviceAdded} {}

  /**
   * \brief Creates a controller device event that is based on the supplied SDL
   * controller device event.
   *
   * \param event the SDL event that will be copied.
   *
   * \since 4.0.0
   */
  explicit controller_device_event(const SDL_ControllerDeviceEvent& event) noexcept
      : EventBase{event}
  {}

  /**
   * \brief Sets the joystick device index or instance ID.
   *
   * \details If the event type is `Added`, then this value is the joystick
   * device index. If the type of the event is either `Removed` or
   * `Remapped`, then this value is the instance ID.
   *
   * \param which the joystick device index or instance ID.
   *
   * \since 4.0.0
   */
  void set_which(const Sint32 which) noexcept { m_event.which = which; }

  /**
   * \brief Returns the joystick device index or instance ID.
   *
   * \details Returns the joystick device index if the type of the event is
   * `Added`. Returns the instance ID if the type of the event is either
   * `Removed` or `Remapped`.
   *
   * \return the joystick device index or instance ID.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto which() const noexcept -> Sint32 { return m_event.which; }
};

/// \name SDL event conversions
/// \{

template <>
inline auto AsSDLEvent(const EventBase<SDL_ControllerDeviceEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.cdevice = event.get();
  return e;
}

/// \} End of SDL event conversions

/// \} End of group event

}  // namespace cen

#endif  // CENTURION_EVENTS_CONTROLLER_DEVICE_EVENT_HPP_
