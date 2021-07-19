#ifndef CENTURION_JOY_AXIS_EVENT_HEADER
#define CENTURION_JOY_AXIS_EVENT_HEADER

#include <SDL.h>

#include "../core/integers.hpp"
#include "common_event.hpp"

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
class joy_axis_event final : public common_event<SDL_JoyAxisEvent>
{
 public:
  /**
   * \brief Creates a joy axis event.
   *
   * \since 4.0.0
   */
  joy_axis_event() noexcept : common_event{event_type::joystick_axis_motion}
  {}

  /**
   * \brief Creates a joy axis event based on the supplied SDL joy axis event.
   *
   * \param event the SDL joy axis event that will be copied.
   *
   * \since 4.0.0
   */
  explicit joy_axis_event(const SDL_JoyAxisEvent& event) noexcept : common_event{event}
  {}

  /**
   * \brief Sets the joystick instance ID associated with the event.
   *
   * \param which the joystick instance ID associated with the event.
   *
   * \since 4.0.0
   */
  void set_which(const SDL_JoystickID which) noexcept
  {
    m_event.which = which;
  }

  /**
   * \brief Sets the joystick axis index associated with the event.
   *
   * \param axis the joystick axis index associated with the event.
   *
   * \since 4.0.0
   */
  void set_axis(const u8 axis) noexcept
  {
    m_event.axis = axis;
  }

  /**
   * \brief Sets the joystick axis value associated with the event.
   *
   * \param value the joystick axis value associated with the event.
   *
   * \since 4.0.0
   */
  void set_value(const i16 value) noexcept
  {
    m_event.value = value;
  }

  /**
   * \brief Returns the joystick instance ID associated with the event.
   *
   * \return the joystick instance ID associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto which() const noexcept -> SDL_JoystickID
  {
    return m_event.which;
  }

  /**
   * \brief Returns the joystick axis index associated with the event.
   *
   * \return the joystick axis index associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto axis() const noexcept -> u8
  {
    return m_event.axis;
  }

  /**
   * \brief Returns the joystick axis value associated with the event.
   *
   * \return the joystick axis value associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto value() const noexcept -> i16
  {
    return m_event.value;
  }
};

/// \name SDL event conversions
/// \{

template <>
inline auto as_sdl_event(const common_event<SDL_JoyAxisEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.jaxis = event.get();
  return e;
}

/// \} End of SDL event conversions

/// \} End of group event

}  // namespace cen

#endif  // CENTURION_JOY_AXIS_EVENT_HEADER
