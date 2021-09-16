#ifndef CENTURION_JOY_BUTTON_EVENT_HEADER
#define CENTURION_JOY_BUTTON_EVENT_HEADER

#include <SDL.h>

#include "../core/integers.hpp"
#include "../core/to_underlying.hpp"
#include "../input/button_state.hpp"
#include "common_event.hpp"

namespace cen {

/// \addtogroup event
/// \{

/**
 * \class joy_button_event
 *
 * \brief Represents an event associated with the press or release of a
 * joystick button.
 *
 * \see `SDL_JoyButtonEvent`
 *
 * \since 4.0.0
 */
class joy_button_event final : public common_event<SDL_JoyButtonEvent>
{
 public:
  /**
   * \brief Creates a joystick button event of type `joystick_button_down`.
   *
   * \since 4.0.0
   */
  joy_button_event() noexcept : common_event{event_type::joystick_button_down}
  {}

  /**
   * \brief Creates a joy_button_event based on the supplied event.
   *
   * \param event the event that will be copied.
   *
   * \since 4.0.0
   */
  explicit joy_button_event(const SDL_JoyButtonEvent& event) noexcept : common_event{event}
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
   * \brief Sets the button index associated with the event.
   *
   * \param button the button index associated with the event.
   *
   * \since 4.0.0
   */
  void set_button(const u8 button) noexcept
  {
    m_event.button = button;
  }

  /**
   * \brief Sets the button state that is associated with the button that
   * triggered the event.
   *
   * \param state the button state that is associated with the button that
   * triggered the event.
   *
   * \since 4.0.0
   */
  void set_state(const button_state state) noexcept
  {
    m_event.state = to_underlying(state);
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
   * \brief Returns the index of the button that changed.
   *
   * \return the index of the button that changed.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto button() const noexcept -> u8
  {
    return m_event.button;
  }

  /**
   * \brief Returns the state of the button associated with the event.
   *
   * \return the state of the button associated with the event.
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
};

/// \name SDL event conversions
/// \{

template <>
inline auto as_sdl_event(const common_event<SDL_JoyButtonEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.jbutton = event.get();
  return e;
}

/// \} End of SDL event conversions

/// \} End of group event

}  // namespace cen

#endif  // CENTURION_JOY_BUTTON_EVENT_HEADER
