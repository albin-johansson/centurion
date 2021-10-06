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
   * \brief Sets the status of key modifiers.
   *
   * \param modifiers the modifiers that will be affected.
   * \param active `true` if the modifiers should be active; `false` otherwise.
   *
   * \since 4.0.0
   */
  void set_modifier(const key_mod modifiers, const bool active) noexcept
  {
    if (active) {
      m_event.keysym.mod |= to_underlying(modifiers);
    }
    else {
      m_event.keysym.mod &= ~to_underlying(modifiers);
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
   * \brief Indicates whether or not the specified modifiers are active.
   *
   * \note Multiple key modifiers can be active at the same time.
   *
   * \param modifiers the modifiers to check for.
   *
   * \return `true` if any of the specified modifiers are active; `false` otherwise.
   *
   * \see `is_only_active(key_mod)`
   * \see `is_only_any_of_active(key_mod)`
   *
   * \since 6.1.0
   */
  [[nodiscard]] auto is_active(const key_mod modifiers) const noexcept -> bool
  {
    return detail::is_active(modifiers, m_event.keysym.mod);
  }

  /**
   * \brief Indicates whether or not the specified modifiers are solely active.
   *
   * \details This function differs from `is_active(key_mod)` in that this function
   * will return `false` if modifiers other than those specified are active. For example,
   * if the `shift` and `alt` modifiers are being pressed, then
   * `is_only_active(cen::key_mod::shift)` would evaluate to `false`.
   *
   * \param modifiers the modifiers to check for.
   *
   * \return `true` if *only* the specified modifiers are active; false otherwise.
   *
   * \see `is_active(key_mod)`
   *
   * \since 6.1.0
   */
  [[nodiscard]] auto is_only_active(const key_mod modifiers) const noexcept -> bool
  {
    return detail::is_only_active(modifiers, m_event.keysym.mod);
  }

  /**
   * \brief Indicates whether or not only any of the specified modifiers are active.
   *
   * \details This function is very similar to `is_only_active()`, but differs in that not
   * all of the specified modifiers need to be active for this function to return `true`.
   * For example, if you supply `shift` to this function, and only the left shift key is
   * being pressed, then `is_only_any_of_active(cen::key_mod::shift)` would evaluate
   * to `true`. However, if some other modifiers were also being pressed other than the
   * left shift key, the same function call would instead evaluate to `false`.
   *
   * \param modifiers the modifiers to check for.
   *
   * \return `true` if *any* of the specified modifiers are active, but no other
   * modifiers; false otherwise.
   *
   * \see `is_only_active(key_mod)`
   *
   * \since 6.1.0
   */
  [[nodiscard]] auto is_only_any_of_active(const key_mod modifiers) const noexcept -> bool
  {
    return detail::is_only_any_of_active(modifiers, m_event.keysym.mod);
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
   * \since 6.1.0
   */
  [[nodiscard]] auto scan() const noexcept -> scan_code
  {
    return m_event.keysym.scancode;
  }

  /**
   * \brief Equivalent to `scan()`.
   * \since 5.0.0
   */
  [[nodiscard]] auto get_scan_code() const noexcept -> scan_code
  {
    return scan();
  }

  /**
   * \brief Returns the key code that is associated with the event.
   *
   * \return the key code that is associated with the event.
   *
   * \since 6.1.0
   */
  [[nodiscard]] auto key() const noexcept -> key_code
  {
    return static_cast<SDL_KeyCode>(m_event.keysym.sym);
  }

  /**
   * \brief Equivalent to `key()`.
   * \since 5.0.0
   */
  [[nodiscard]] auto get_key_code() const noexcept -> key_code
  {
    return key();
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

/// \name SDL event conversions
/// \{

template <>
inline auto as_sdl_event(const common_event<SDL_KeyboardEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.key = event.get();
  return e;
}

/// \} End of SDL event conversions

/// \} End of group event

}  // namespace cen

#endif  // CENTURION_KEYBOARD_EVENT_HEADER
