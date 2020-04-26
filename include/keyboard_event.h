/*
 * MIT License
 *
 * Copyright (c) 2019-2020 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef CENTURION_KEYBOARD_EVENT_HEADER
#define CENTURION_KEYBOARD_EVENT_HEADER

#include <SDL_keyboard.h>

#include "centurion_api.h"

namespace centurion {
namespace event {

/**
 * The KeyModifier enum class mirrors the values of the SDL_Keymod enum.
 *
 * @see SDL_Keymod
 * @since 3.1.0
 */
enum class KeyModifier {
  None = KMOD_NONE,
  LeftShift = KMOD_LSHIFT,
  RightShift = KMOD_RSHIFT,
  LeftControl = KMOD_LCTRL,
  RightControl = KMOD_RCTRL,
  LeftAlt = KMOD_LALT,
  RightAlt = KMOD_RALT,
  LeftGUI = KMOD_LGUI,
  RightGUI = KMOD_RGUI,
  Num = KMOD_NUM,
  Caps = KMOD_CAPS,
  Mode = KMOD_MODE
};

/**
 * The KeyboardEvent class represents an event associated with some sort of
 * key action, such as the release or pressing of a key.
 *
 * @see SDL_KeyboardEvent
 * @since 4.0.0
 */
class KeyboardEvent : public TEvent<SDL_KeyboardEvent> {  // TODO test
 public:
  /**
   * Creates a default-initialized keyboard event.
   *
   * @since 4.0.0
   */
  CENTURION_API KeyboardEvent() noexcept;

  /**
   * Creates a keyboard event based on the supplied SDL event.
   *
   * @param event the SDL event that will be copied.
   * @since 4.0.0
   */
  CENTURION_API explicit KeyboardEvent(const SDL_KeyboardEvent& event) noexcept;

  /**
   * Creates a keyboard event based on the supplied SDL event.
   *
   * @param event the SDL event that will be moved.
   * @since 4.0.0
   */
  CENTURION_API explicit KeyboardEvent(SDL_KeyboardEvent&& event) noexcept;

  CENTURION_API void set_modifier(KeyModifier modifier, bool active) noexcept;
  CENTURION_API void set_key(SDL_Keycode keycode, ButtonState state) noexcept;
  CENTURION_API void set_key(SDL_Scancode scancode, ButtonState state) noexcept;

  /**
   * Indicates whether or not the supplied keycode represents the same key that
   * triggered this keyboard event.
   *
   * @param keycode the keycode of the key that will be checked.
   * @return true if the key associated with the supplied keycode caused this
   * keyboard event; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool is_key_active(SDL_Keycode keycode) const noexcept;

  /**
   * Indicates whether or not the supplied scancode represents the same key that
   * triggered this keyboard event.
   *
   * @param scancode the scancode of the key that will be checked.
   * @return true if the key associated with the supplied scancode caused this
   * keyboard event; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool is_key_active(SDL_Scancode scancode) const noexcept;

  /**
   * Indicates whether or not the specified key modifier is active. Multiple key
   * modifiers can be active at the same time.
   *
   * @param modifier the key modifier that will be checked.
   * @return true if the specified key modifier is active; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool modifier_active(KeyModifier modifier) const noexcept;

  /**
   * Indicates whether or not any of the SHIFT modifiers are active.
   *
   * @return true if any of the SHIFT modifiers are active; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool shift_active() const noexcept;

  /**
   * Indicates whether or not any of the CTRL modifiers are active.
   *
   * @return true if any of the CTRL modifiers are active; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool ctrl_active() const noexcept;

  /**
   * Indicates whether or not any of the ALT modifiers are active.
   *
   * @return true if any of the ALT modifiers are active; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool alt_active() const noexcept;

  /**
   * Indicates whether or not any of the GUI modifiers are active.
   *
   * @return true if any of the GUI modifiers are active; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool gui_active() const noexcept;

  /**
   * Indicates whether or not the CAPS modifier is active.
   *
   * @return true if the CAPS modifier is active; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool caps_active() const noexcept;  // TODO test

  /**
   * Indicates whether or not the NUM modifier is active.
   *
   * @return true if the NUM modifier is active; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool num_active() const noexcept;  // TODO test

  /**
   * Indicates whether or not the key associated with this key event has been
   * repeatedly triggered.
   *
   * @return true if the key associated with the event was repeated; false
   * otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool repeated() const noexcept;

  /**
   * Returns the button state of the key associated with the event.
   *
   * @return the button state of the key associated with the event.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API ButtonState state() const noexcept;

  CENTURION_NODISCARD
  CENTURION_API SDL_Scancode scancode() const noexcept;

  CENTURION_NODISCARD
  CENTURION_API SDL_Keycode keycode() const noexcept;
};

}  // namespace event
}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "keyboard_event.cpp"
#endif  // CENTURION_HEADER_ONLY

#endif  // CENTURION_KEYBOARD_EVENT_HEADER