#ifndef CENTURION_KEYBOARD_EVENT_HEADER
#define CENTURION_KEYBOARD_EVENT_HEADER

#include <SDL.h>

#include "../core/integers.hpp"
#include "../core/to_underlying.hpp"
#include "../input/button_state.hpp"
#include "../input/key_code.hpp"
#include "../input/key_modifier.hpp"
#include "../input/scan_code.hpp"
#include "common_event.hpp"

namespace cen {

/// \addtogroup event
/// \{

/**
 * \class keyboard_event
 *
 * \brief Represents an event associated with some sort of key action, such
 * as the release or pressing of a key.
 *
 * \see `SDL_KeyboardEvent`
 *
 * \since 4.0.0
 */
class keyboard_event final : public common_event<SDL_KeyboardEvent>
{
 public:
  /**
   * \brief Creates a keyboard event of type `key_down`.
   *
   * \since 4.0.0
   */
  keyboard_event() noexcept : common_event{event_type::key_down}
  {}

  /**
   * \brief Creates a keyboard event based on the supplied SDL event.
   *
   * \param event the SDL event that will be copied.
   *
   * \since 4.0.0
   */
  explicit keyboard_event(const SDL_KeyboardEvent& event) noexcept : common_event{event}
  {}

  /**
   * \brief Sets the scan code that is associated with the event.
   *
   * \param code the scan code that will be associated with the event.
   *
   * \since 5.0.0
   */
  void set_scan_code(const scan_code& code) noexcept
  {
    m_event.keysym.scancode = code.get();
  }

  /**
   * \brief Sets the key code that is associated with the event.
   *
   * \param code the key code that will be associated with the event.
   *
   * \since 5.0.0
   */
  void set_key_code(const key_code& code) noexcept
  {
    m_event.keysym.sym = code.get();
  }

  /**
   * \brief Sets the button state associated with the event.
   *
   * \param state the button state that will be associated with the event
   *
   * \since 5.0.0
   */
  void set_button_state(const button_state state) noexcept
  {
    m_event.state = to_underlying(state);
  }

  /**
   * \brief Sets the status of a key modifier.
   *
   * \param modifier the key modifier that will be affected.
   * \param active `true` if the key modifier is active; `false` otherwise.
   *
   * \since 4.0.0
   */
  void set_modifier(const key_modifier modifier, const bool active) noexcept
  {
    if (active)
    {
      m_event.keysym.mod |= to_underlying(modifier);
    }
    else
    {
      m_event.keysym.mod &= ~to_underlying(modifier);
    }
  }

  /**
   * \brief Sets the flag that indicates whether or not the key associated with
   * this key event was repeatedly triggered.
   *
   * \param repeated `true` if the key was repeatedly triggered; `false`
   * otherwise.
   *
   * \since 4.0.0
   */
  void set_repeated(const bool repeated) noexcept
  {
    m_event.repeat = repeated;
  }

  /**
   * \brief Sets the window ID that is associated with this key event.
   *
   * \param id the window ID that should be associated with the key event.
   *
   * \since 4.0.0
   */
  void set_window_id(const u32 id) noexcept
  {
    m_event.windowID = id;
  }

  /**
   * \brief Indicates whether or not the event is associated with the
   * specified scan code.
   *
   * \param code the scan code that will be checked.
   *
   * \return `true` if the supplied scan code is associated with the event;
   * `false` otherwise.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto is_active(const scan_code& code) const noexcept -> bool
  {
    return m_event.keysym.scancode == code.get();
  }

  /**
   * \brief Indicates whether or not the event is associated with the
   * specified key code.
   *
   * \param code the key code that will be checked.
   *
   * \return `true` if the supplied key code is associated with the event;
   * `false` otherwise.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto is_active(const key_code& code) const noexcept -> bool
  {
    return static_cast<SDL_KeyCode>(m_event.keysym.sym) == code.get();
  }

  /**
   * \brief Indicates whether or not the specified key modifier is active.
   *
   * \note Multiple key modifiers can be active at the same time.
   *
   * \param modifier the key modifier that will be checked.
   *
   * \return `true` if the specified key modifier is active; `false` otherwise.
   *
   * \since 6.1.0
   */
  [[nodiscard]] auto is_active(const key_modifier modifier) const noexcept -> bool
  {
    return m_event.keysym.mod & to_underlying(modifier);
  }

  /**
   * \brief Indicates whether or not the specified key modifier is active.
   *
   * \note Multiple key modifiers can be active at the same time.
   *
   * \param modifier the key modifier that will be checked.
   *
   * \return `true` if the specified key modifier is active; `false` otherwise.
   *
   * \deprecated Since 6.1.0. Use `is_active(key_modifier)` instead.
   *
   * \since 4.0.0
   */
  [[deprecated, nodiscard]] auto modifier_active(
      const key_modifier modifier) const noexcept -> bool
  {
    return is_active(modifier);
  }

  /**
   * \brief Indicates whether or not any of the SHIFT modifiers are active.
   *
   * \return `true` if any of the SHIFT modifiers are active; `false` otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto shift_active() const noexcept -> bool
  {
    return is_active(key_modifier::left_shift) || is_active(key_modifier::right_shift);
  }

  /**
   * \brief Indicates whether or not any of the CTRL modifiers are active.
   *
   * \return `true` if any of the CTRL modifiers are active; `false` otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto ctrl_active() const noexcept -> bool
  {
    return is_active(key_modifier::left_ctrl) || is_active(key_modifier::right_ctrl);
  }

  /**
   * \brief Indicates whether or not any of the ALT modifiers are active.
   *
   * \return `true` if any of the ALT modifiers are active; `false` otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto alt_active() const noexcept -> bool
  {
    return is_active(key_modifier::left_alt) || is_active(key_modifier::right_alt);
  }

  /**
   * \brief Indicates whether or not any of the GUI modifiers are active.
   *
   * \return `true` if any of the GUI modifiers are active; `false` otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto gui_active() const noexcept -> bool
  {
    return is_active(key_modifier::left_gui) || is_active(key_modifier::right_gui);
  }

  /**
   * \brief Indicates whether or not the CAPS modifier is active.
   *
   * \return `true` if the CAPS modifier is active; `false` otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto caps_active() const noexcept -> bool
  {
    return is_active(key_modifier::caps);
  }

  /**
   * \brief Indicates whether or not the NUM modifier is active.
   *
   * \return `true` if the NUM modifier is active; `false` otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto num_active() const noexcept -> bool
  {
    return is_active(key_modifier::num);
  }

  /**
   * \brief Indicates whether or not the key associated with this key event has
   * been repeatedly triggered.
   *
   * \return `true` if the key associated with the event was repeated; false
   * otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto repeated() const noexcept -> bool
  {
    return m_event.repeat;
  }

  /**
   * \brief Returns the button state of the key associated with the event.
   *
   * \return the button state of the key associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto state() const noexcept -> button_state
  {
    return static_cast<button_state>(m_event.state);
  }

  /**
   * \brief Indicates whether or not the event is associated with the release
   * of a key.
   *
   * \note This function is equivalent to `state() ==  button_state::released`.
   *
   * \return `true` if the event is a key released event; `false` otherwise.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto released() const noexcept -> bool
  {
    return state() == button_state::released;
  }

  /**
   * \brief Indicates whether or not the event is associated with the press
   * of a key.
   *
   * \note This function is equivalent to `state() ==  button_state::pressed`.
   *
   * \return `true` if the event is a key pressed event; `false` otherwise.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto pressed() const noexcept -> bool
  {
    return state() == button_state::pressed;
  }

  /**
   * \brief Returns the scan code that is associated with the event.
   *
   * \return the scan code that is associated with the event.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto get_scan_code() const noexcept -> scan_code
  {
    return m_event.keysym.scancode;
  }

  /**
   * \brief Returns the key code that is associated with the event.
   *
   * \return the key code that is associated with the event.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto get_key_code() const noexcept -> key_code
  {
    return static_cast<SDL_KeyCode>(m_event.keysym.sym);
  }

  /**
   * \brief Returns the ID of the window associated with the event.
   *
   * \return the ID of the window associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto window_id() const noexcept -> u32
  {
    return m_event.windowID;
  }
};

template <>
inline auto as_sdl_event(const common_event<SDL_KeyboardEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.key = event.get();
  return e;
}

/// \} End of group event

}  // namespace cen

#endif  // CENTURION_KEYBOARD_EVENT_HEADER
