#ifndef CENTURION_CONTROLLER_BUTTON_EVENT_HEADER
#define CENTURION_CONTROLLER_BUTTON_EVENT_HEADER

#include <SDL.h>

#include "../core/integers.hpp"
#include "../core/to_underlying.hpp"
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
class controller_button_event final : public common_event<SDL_ControllerButtonEvent>
{
 public:
  /**
   * \brief Creates a controller button event of type `controller_button_down`.
   *
   * \since 4.0.0
   */
  controller_button_event() noexcept : common_event{event_type::controller_button_down}
  {}

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
  void set_button(const controller_button button) noexcept
  {
    m_event.button = static_cast<u8>(button);
  }

  /**
   * \brief Sets the button state associated with the event.
   *
   * \param state the button state associated with the event.
   *
   * \since 4.0.0
   */
  void set_state(const button_state state) noexcept
  {
    m_event.state = to_underlying(state);
  }

  /**
   * \brief Sets the joystick instance ID associated with the event.
   *
   * \param id the instance ID of the joystick that the event is associated
   * with.
   *
   * \since 4.0.0
   */
  void set_which(const SDL_JoystickID id) noexcept
  {
    m_event.which = id;
  }

  /**
   * \brief Returns the game controller button associated with the event.
   *
   * \return the game controller button associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto button() const noexcept -> controller_button
  {
    return static_cast<controller_button>(m_event.button);
  }

  /**
   * \brief Returns the button state associated with the event.
   *
   * \return the button state associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto state() const noexcept -> button_state
  {
    return static_cast<button_state>(m_event.state);
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
    return state() == button_state::pressed;
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
    return state() == button_state::released;
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

#endif  // CENTURION_CONTROLLER_BUTTON_EVENT_HEADER
