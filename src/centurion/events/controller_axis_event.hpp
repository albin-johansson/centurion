#ifndef CENTURION_CONTROLLER_AXIS_EVENT_HEADER
#define CENTURION_CONTROLLER_AXIS_EVENT_HEADER

#include <SDL.h>

#include "../core/integers.hpp"
#include "../input/controller.hpp"
#include "common_event.hpp"

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
class controller_axis_event final : public common_event<SDL_ControllerAxisEvent>
{
 public:
  /**
   * \brief Creates a controller axis event of type `controller_axis_motion`.
   *
   * \since 4.0.0
   */
  controller_axis_event() noexcept : common_event{cen::event_type::controller_axis_motion}
  {}

  /**
   * \brief Creates a controller axis event that is based on the supplied SDL
   * controller axis event.
   *
   * \param event the SDL event that will be copied.
   *
   * \since 4.0.0
   */
  explicit controller_axis_event(const SDL_ControllerAxisEvent& event) noexcept
      : common_event{event}
  {}

  /**
   * \brief Sets the joystick instance ID associated with the event.
   *
   * \param which the instance ID of the joystick that the event is
   * associated with.
   *
   * \since 4.0.0
   */
  void set_which(const SDL_JoystickID which) noexcept
  {
    m_event.which = which;
  }

  /**
   * \brief Sets the game controller axis value associated with the event.
   *
   * \param axis the game controller axis value associated with the event.
   *
   * \since 4.0.0
   */
  void set_axis(const controller_axis axis) noexcept
  {
    m_event.axis = static_cast<u8>(axis);
  }

  /**
   * \brief Sets the axis value associated with the event.
   *
   * \param value the new axis value associated with the event.
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
   * \brief Returns the game controller axis value associated with the event.
   *
   * \return the game controller axis value associated with the event.
   *
   * \see `GameControllerAxis`
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto axis() const noexcept -> controller_axis
  {
    return static_cast<controller_axis>(m_event.axis);
  }

  /**
   * \brief Returns the axis value associated with the event.
   *
   * \return the axis value associated with the event.
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
inline auto as_sdl_event(const common_event<SDL_ControllerAxisEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.caxis = event.get();
  return e;
}

/// \} End of SDL event conversions

/// \} End of group event

}  // namespace cen

#endif  // CENTURION_CONTROLLER_AXIS_EVENT_HEADER
