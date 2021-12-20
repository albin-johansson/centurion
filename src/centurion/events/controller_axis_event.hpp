#ifndef CENTURION_EVENTS_CONTROLLER_AXIS_EVENT_HPP_
#define CENTURION_EVENTS_CONTROLLER_AXIS_EVENT_HPP_

#include <SDL.h>

#include "../common.hpp"
#include "../input/controller.hpp"
#include "event_base.hpp"

namespace cen {

/// \addtogroup event
/// \{

/**
 * \class controller_axis_event
 *
 * \brief Represents an event triggered by game controller axis motion.
 *
 * \since 4.0.0
 */
class controller_axis_event final : public EventBase<SDL_ControllerAxisEvent> {
 public:
  /**
   * \brief Creates a controller axis event of type `controller_axis_motion`.
   *
   * \since 4.0.0
   */
  controller_axis_event() noexcept : EventBase{cen::EventType::ControllerAxisMotion} {}

  /**
   * \brief Creates a controller axis event that is based on the supplied SDL
   * controller axis event.
   *
   * \param event the SDL event that will be copied.
   *
   * \since 4.0.0
   */
  explicit controller_axis_event(const SDL_ControllerAxisEvent& event) noexcept
      : EventBase{event}
  {}

  /**
   * \brief Sets the joystick instance ID associated with the event.
   *
   * \param which the instance ID of the joystick that the event is
   * associated with.
   *
   * \since 4.0.0
   */
  void set_which(const SDL_JoystickID which) noexcept { mEvent.which = which; }

  /**
   * \brief Sets the game controller axis value associated with the event.
   *
   * \param axis the game controller axis value associated with the event.
   *
   * \since 4.0.0
   */
  void set_axis(const ControllerAxis axis) noexcept
  { mEvent.axis = static_cast<Uint8>(axis);
  }

  /**
   * \brief Sets the axis value associated with the event.
   *
   * \param value the new axis value associated with the event.
   *
   * \since 4.0.0
   */
  void set_value(const Sint16 value) noexcept { mEvent.value = value; }

  /**
   * \brief Returns the joystick instance ID associated with the event.
   *
   * \return the joystick instance ID associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto which() const noexcept -> SDL_JoystickID { return mEvent.which; }

  /**
   * \brief Returns the game controller axis value associated with the event.
   *
   * \return the game controller axis value associated with the event.
   *
   * \see `GameControllerAxis`
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto axis() const noexcept -> ControllerAxis
  {
    return static_cast<ControllerAxis>(mEvent.axis);
  }

  /**
   * \brief Returns the axis value associated with the event.
   *
   * \return the axis value associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto value() const noexcept -> Sint16 { return mEvent.value; }
};

/// \name SDL event conversions
/// \{

template <>
inline auto AsSDLEvent(const EventBase<SDL_ControllerAxisEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.caxis = event.get();
  return e;
}

/// \} End of SDL event conversions

/// \} End of group event

}  // namespace cen

#endif  // CENTURION_EVENTS_CONTROLLER_AXIS_EVENT_HPP_
