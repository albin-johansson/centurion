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

#include <SDL_events.h>
#include <SDL_keyboard.h>

#include "button_state.h"
#include "centurion_api.h"
#include "common_event.h"
#include "key.h"
#include "key_modifier.h"

namespace centurion {
namespace event {

/**
 * The KeyboardEvent class represents an event associated with some sort of
 * key action, such as the release or pressing of a key.
 *
 * @see SDL_KeyboardEvent
 * @since 4.0.0
 */
class KeyboardEvent : public CommonEvent<SDL_KeyboardEvent> {
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

  /**
   * Sets the button state associated with a key.
   *
   * @param key the key to set the button state of.
   * @param state the new button state of the key.
   * @since 4.0.0
   */
  CENTURION_API void set_key(const Key& key, ButtonState state) noexcept;

  /**
   * Sets the status of a key modifier.
   *
   * @param modifier the key modifier that will be affected.
   * @param active true if the key modifier is active; false otherwise.
   * @since 4.0.0
   */
  CENTURION_API void set_modifier(KeyModifier modifier, bool active) noexcept;

  /**
   * Sets the flag that indicates whether or not the key associated with this
   * key event was repeatedly triggered.
   *
   * @param repeated true if the key was repeatedly triggered; false otherwise.
   * @since 4.0.0
   */
  CENTURION_API void set_repeated(bool repeated) noexcept;

  /**
   * Sets the window ID that is associated with this key event.
   *
   * @param id the window ID that should be associated with the key event.
   * @since 4.0.0
   */
  CENTURION_API void set_window_id(Uint32 id) noexcept;

  /**
   * Indicates whether or not the supplied key represents the same key that
   * triggered this keyboard event.
   *
   * @param key the key that will be checked.
   * @return true if the supplied key caused this keyboard event; false
   * otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool is_active(const Key& key) const noexcept;

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
  CENTURION_API bool caps_active() const noexcept;

  /**
   * Indicates whether or not the NUM modifier is active.
   *
   * @return true if the NUM modifier is active; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool num_active() const noexcept;

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

  /**
   * Returns the key that triggered this keyboard event.
   *
   * @return the key that triggered this keyboard event.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API Key key() const noexcept;

  /**
   * Returns the ID of the window associated with the event.
   *
   * @return the ID of the window associated with the event.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API Uint32 window_id() const noexcept;
};

static_assert(validate_event<KeyboardEvent, SDL_KeyboardEvent>(),
              "KeyboardEvent failed the event type specification!");

}  // namespace event
}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "keyboard_event.cpp"
#endif  // CENTURION_HEADER_ONLY

#endif  // CENTURION_KEYBOARD_EVENT_HEADER