#ifndef CENTURION_EVENTS_KEYBOARD_EVENT_HPP_
#define CENTURION_EVENTS_KEYBOARD_EVENT_HPP_

#include <SDL.h>

#include "../common.hpp"
#include "../input/button_state.hpp"
#include "../keyboard.hpp"
#include "event_base.hpp"

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
class keyboard_event final : public EventBase<SDL_KeyboardEvent> {
 public:
  /**
   * \brief Creates a keyboard event of type `key_down`.
   *
   * \since 4.0.0
   */
  keyboard_event() noexcept : EventBase{EventType::KeyDown} {}

  /**
   * \brief Creates a keyboard event based on the supplied SDL event.
   *
   * \param event the SDL event that will be copied.
   *
   * \since 4.0.0
   */
  explicit keyboard_event(const SDL_KeyboardEvent& event) noexcept : EventBase{event} {}

  /**
   * \brief Sets the scan code that is associated with the event.
   *
   * \param code the scan code that will be associated with the event.
   *
   * \since 5.0.0
   */
  void set_scan_code(const ScanCode& code) noexcept { mEvent.keysym.scancode = code.get(); }

  /**
   * \brief Sets the key code that is associated with the event.
   *
   * \param code the key code that will be associated with the event.
   *
   * \since 5.0.0
   */
  void set_key_code(const KeyCode& code) noexcept { mEvent.keysym.sym = code.get(); }

  /**
   * \brief Sets the button state associated with the event.
   *
   * \param state the button state that will be associated with the event
   *
   * \since 5.0.0
   */
  void set_button_state(const ButtonState state) noexcept
  {
    mEvent.state = ToUnderlying(state);
  }

  /**
   * \brief Sets the status of key modifiers.
   *
   * \param modifiers the modifiers that will be affected.
   * \param active `true` if the modifiers should be active; `false` otherwise.
   *
   * \since 4.0.0
   */
  void set_modifier(const KeyMod modifiers, const bool active) noexcept
  {
    if (active) {
      mEvent.keysym.mod |= ToUnderlying(modifiers);
    }
    else {
      mEvent.keysym.mod &= ~ToUnderlying(modifiers);
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
  void set_repeated(const bool repeated) noexcept { mEvent.repeat = repeated; }

  /**
   * \brief Sets the window ID that is associated with this key event.
   *
   * \param id the window ID that should be associated with the key event.
   *
   * \since 4.0.0
   */
  void set_window_id(const Uint32 id) noexcept { mEvent.windowID = id; }

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
  [[nodiscard]] auto is_active(const ScanCode& code) const noexcept -> bool
  {
    return mEvent.keysym.scancode == code.get();
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
  [[nodiscard]] auto is_active(const KeyCode& code) const noexcept -> bool
  {
    return static_cast<SDL_KeyCode>(mEvent.keysym.sym) == code.get();
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
   * \see `IsOnlyActive(KeyMod)`
   * \see `IsOnlyAnyOfActive(KeyMod)`
   *
   * \since 6.1.0
   */
  [[nodiscard]] auto is_active(const KeyMod modifiers) const noexcept -> bool
  {
    return detail::IsActive(modifiers, mEvent.keysym.mod);
  }

  /**
   * \brief Indicates whether or not the specified modifiers are solely active.
   *
   * \details This function differs from `IsActive(KeyMod)` in that this function
   * will return `false` if modifiers other than those specified are active. For example,
   * if the `shift` and `alt` modifiers are being pressed, then
   * `IsOnlyActive(cen::KeyMod::shift)` would evaluate to `false`.
   *
   * \param modifiers the modifiers to check for.
   *
   * \return `true` if *only* the specified modifiers are active; false otherwise.
   *
   * \see `IsActive(KeyMod)`
   *
   * \since 6.1.0
   */
  [[nodiscard]] auto is_only_active(const KeyMod modifiers) const noexcept -> bool
  {
    return detail::IsOnlyActive(modifiers, mEvent.keysym.mod);
  }

  /**
   * \brief Indicates whether or not only any of the specified modifiers are active.
   *
   * \details This function is very similar to `IsOnlyActive()`, but differs in that not
   * all of the specified modifiers need to be active for this function to return `true`.
   * For example, if you supply `shift` to this function, and only the left shift key is
   * being pressed, then `IsOnlyAnyOfActive(cen::KeyMod::shift)` would evaluate
   * to `true`. However, if some other modifiers were also being pressed other than the
   * left shift key, the same function call would instead evaluate to `false`.
   *
   * \param modifiers the modifiers to check for.
   *
   * \return `true` if *any* of the specified modifiers are active, but no other
   * modifiers; false otherwise.
   *
   * \see `IsOnlyActive(KeyMod)`
   *
   * \since 6.1.0
   */
  [[nodiscard]] auto is_only_any_of_active(const KeyMod modifiers) const noexcept -> bool
  {
    return detail::IsOnlyAnyOfActive(modifiers, mEvent.keysym.mod);
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
  [[nodiscard]] auto repeated() const noexcept -> bool { return mEvent.repeat; }

  /**
   * \brief Returns the button state of the key associated with the event.
   *
   * \return the button state of the key associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto state() const noexcept -> ButtonState
  {
    return static_cast<ButtonState>(mEvent.state);
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
    return state() == ButtonState::Released;
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
    return state() == ButtonState::Pressed;
  }

  /**
   * \brief Returns the scan code that is associated with the event.
   *
   * \return the scan code that is associated with the event.
   *
   * \since 6.1.0
   */
  [[nodiscard]] auto scan() const noexcept -> ScanCode { return mEvent.keysym.scancode; }

  /**
   * \brief Equivalent to `scan()`.
   * \since 5.0.0
   */
  [[nodiscard]] auto get_scan_code() const noexcept -> ScanCode { return scan(); }

  /**
   * \brief Returns the key code that is associated with the event.
   *
   * \return the key code that is associated with the event.
   *
   * \since 6.1.0
   */
  [[nodiscard]] auto key() const noexcept -> KeyCode
  {
    return static_cast<SDL_KeyCode>(mEvent.keysym.sym);
  }

  /**
   * \brief Equivalent to `key()`.
   * \since 5.0.0
   */
  [[nodiscard]] auto get_key_code() const noexcept -> KeyCode { return key(); }

  /**
   * \brief Returns the ID of the window associated with the event.
   *
   * \return the ID of the window associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto window_id() const noexcept -> Uint32 { return mEvent.windowID; }
};

/// \name SDL event conversions
/// \{

template <>
inline auto AsSDLEvent(const EventBase<SDL_KeyboardEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.key = event.get();
  return e;
}

/// \} End of SDL event conversions

/// \} End of group event

}  // namespace cen

#endif  // CENTURION_EVENTS_KEYBOARD_EVENT_HPP_
