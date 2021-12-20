#ifndef CENTURION_EVENTS_CONTROLLER_BUTTON_EVENT_HPP_
#define CENTURION_EVENTS_CONTROLLER_BUTTON_EVENT_HPP_

#include <SDL.h>

#include "../common.hpp"
#include "../input/controller.hpp"
#include "common_event.hpp"

namespace cen {

/// \addtogroup event
/// \{

/**
 * \class controller_button_event
 *
 * \brief Represents events associated with the state of buttons of a game
 * controller.
 *
 * \see `SDL_ControllerButtonEvent`
 *
 * \since 4.0.0
 */
class controller_button_event final : public common_event<SDL_ControllerButtonEvent> {
 public:
  /**
   * \brief Creates a controller button event of type `controller_button_down`.
   *
   * \since 4.0.0
   */
  controller_button_event() noexcept : common_event{EventType::ControllerButtonDown} {}

  /**
   * \brief Creates a controller button event that is based on the supplied SDL
   * controller button event.
   *
   * \param event the SDL event that will be copied.
   *
   * \since 4.0.0
   */
  explicit controller_button_event(const SDL_ControllerButtonEvent& event) noexcept
      : common_event{event}
  {}

  /**
   * \brief Sets the game controller button associated with the event.
   *
   * \param button the game controller button associated with the event.
   *
   * \since 4.0.0
   */
  void set_button(const ControllerButton button) noexcept
  {
    m_event.button = static_cast<Uint8>(button);
  }

  /**
   * \brief Sets the button state associated with the event.
   *
   * \param state the button state associated with the event.
   *
   * \since 4.0.0
   */
  void set_state(const ButtonState state) noexcept { m_event.state = ToUnderlying(state); }

  /**
   * \brief Sets the joystick instance ID associated with the event.
   *
   * \param id the instance ID of the joystick that the event is associated
   * with.
   *
   * \since 4.0.0
   */
  void set_which(const SDL_JoystickID id) noexcept { m_event.which = id; }

  /**
   * \brief Returns the game controller button associated with the event.
   *
   * \return the game controller button associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto button() const noexcept -> ControllerButton
  {
    return static_cast<ControllerButton>(m_event.button);
  }

  /**
   * \brief Returns the button state associated with the event.
   *
   * \return the button state associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto state() const noexcept -> ButtonState
  {
    return static_cast<ButtonState>(m_event.state);
  }

  /**
   * \brief Indicates whether or not the associated button is pressed.
   *
   * \return `true` if the associated button is pressed; `false` otherwise.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto pressed() const noexcept -> bool
  {
    return state() == ButtonState::Pressed;
  }

  /**
   * \brief Indicates whether or not the associated button is released.
   *
   * \return `true` if the associated button is released; `false` otherwise.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto released() const noexcept -> bool
  {
    return state() == ButtonState::Released;
  }

  /**
   * \brief Returns the joystick instance ID associated with the event.
   *
   * \return the joystick instance ID associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto which() const noexcept -> SDL_JoystickID { return m_event.which; }
};

/// \name SDL event conversions
/// \{

template <>
inline auto as_sdl_event(const common_event<SDL_ControllerButtonEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.cbutton = event.get();
  return e;
}

/// \} End of SDL event conversions

/// \} End of group event

}  // namespace cen

#endif  // CENTURION_EVENTS_CONTROLLER_BUTTON_EVENT_HPP_
