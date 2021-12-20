#ifndef CENTURION_EVENTS_JOY_AXIS_EVENT_HPP_
#define CENTURION_EVENTS_JOY_AXIS_EVENT_HPP_

#include <SDL.h>

#include "../common.hpp"
#include "event_base.hpp"

namespace cen {

/// \addtogroup event
/// \{

/**
 * \class joy_axis_event
 *
 * \brief Represents an event that occurs whenever a user moves an axis on a
 * joystick.
 *
 * \see `SDL_JoyAxisEvent`
 *
 * \since 4.0.0
 */
class joy_axis_event final : public EventBase<SDL_JoyAxisEvent> {
 public:
  /**
   * \brief Creates a joy axis event.
   *
   * \since 4.0.0
   */
  joy_axis_event() noexcept : EventBase{EventType::JoyAxisMotion} {}

  /**
   * \brief Creates a joy axis event based on the supplied SDL joy axis event.
   *
   * \param event the SDL joy axis event that will be copied.
   *
   * \since 4.0.0
   */
  explicit joy_axis_event(const SDL_JoyAxisEvent& event) noexcept : EventBase{event} {}

  /**
   * \brief Sets the joystick instance ID associated with the event.
   *
   * \param which the joystick instance ID associated with the event.
   *
   * \since 4.0.0
   */
  void set_which(const SDL_JoystickID which) noexcept { m_event.which = which; }

  /**
   * \brief Sets the joystick axis index associated with the event.
   *
   * \param axis the joystick axis index associated with the event.
   *
   * \since 4.0.0
   */
  void set_axis(const Uint8 axis) noexcept { m_event.axis = axis; }

  /**
   * \brief Sets the joystick axis value associated with the event.
   *
   * \param value the joystick axis value associated with the event.
   *
   * \since 4.0.0
   */
  void set_value(const Sint16 value) noexcept { m_event.value = value; }

  /**
   * \brief Returns the joystick instance ID associated with the event.
   *
   * \return the joystick instance ID associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto which() const noexcept -> SDL_JoystickID { return m_event.which; }

  /**
   * \brief Returns the joystick axis index associated with the event.
   *
   * \return the joystick axis index associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto axis() const noexcept -> Uint8 { return m_event.axis; }

  /**
   * \brief Returns the joystick axis value associated with the event.
   *
   * \return the joystick axis value associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto value() const noexcept -> Sint16 { return m_event.value; }
};

/// \name SDL event conversions
/// \{

template <>
inline auto AsSDLEvent(const EventBase<SDL_JoyAxisEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.jaxis = event.get();
  return e;
}

/// \} End of SDL event conversions

/// \} End of group event

}  // namespace cen

#endif  // CENTURION_EVENTS_JOY_AXIS_EVENT_HPP_
