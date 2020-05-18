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

#ifndef CENTURION_KEY_STATE_HEADER
#define CENTURION_KEY_STATE_HEADER

#include <SDL.h>

#include <array>

#include "centurion_api.h"
#include "centurion_utils.h"
#include "key.h"
#include "key_modifier.h"

namespace centurion {
namespace input {

/**
 * The KeyState class provides information about the keyboard state. Using the
 * keyboard state is an alternative to using events for keyboard input.
 *
 * @since 3.0.0
 */
class KeyState final {
 public:
  /**
   * @since 3.0.0
   */
  CENTURION_API KeyState() noexcept;

  /**
   * Creates and returns a unique pointer to a KeyState instance.
   *
   * @return a unique pointer to a KeyState instance.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static UniquePtr<KeyState> unique();

  /**
   * Creates and returns a shared pointer to a KeyState instance.
   *
   * @return a shared pointer to a KeyState instance.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static SharedPtr<KeyState> shared();

  /**
   * Updates the state of the key state object. Note! SDL_PumpEvents isn't
   * invoked by this method.
   *
   * @since 3.0.0
   */
  CENTURION_API void update() noexcept;

  /**
   * Indicates whether or not the specified key is being pressed. This method
   * returns false if the supplied key isn't recognized.
   *
   * @param key the key that will be checked.
   * @return true if the key is being pressed; false otherwise.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool is_pressed(const Key& key) const noexcept;

  /**
   * Indicates whether or not the specified key has been pressed during more
   * than one update of the key state. This method returns false if the
   * supplied key isn't recognized.
   *
   * @param key the key that will be checked.
   * @return true if the key has been held down; false otherwise.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool is_held(const Key& key) const noexcept;

  /**
   * Indicates whether or not a key just became pressed in the last update of
   * the key state. This method returns false if the supplied key isn't
   * recognized.
   *
   * @param key the key that will be checked.
   * @return true if the key has just been pressed; false otherwise.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool was_just_pressed(const Key& key) const noexcept;

  /**
   * Indicates whether or not the specified key was released in the last update
   * of the key state. This method returns false if the supplied key isn't
   * recognized.
   *
   * @param key the key that will be checked.
   * @return true if the key was released; false otherwise.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool was_just_released(const Key& key) const noexcept;

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
   * Returns the total amount of keys.
   *
   * @return the total amount of keys.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  int amount_of_keys() const noexcept { return m_nKeys; }

 private:
  const Uint8* m_states = nullptr;
  std::array<Uint8, static_cast<int>(SDL_NUM_SCANCODES)> m_previousStates;
  int m_nKeys = 0;
};

#ifdef CENTURION_HAS_IS_FINAL_TYPE_TRAIT
static_assert(std::is_final<KeyState>::value, "KeyState isn't final!");
#endif

static_assert(std::is_default_constructible<KeyState>::value,
              "KeyState isn't default constructible!");

static_assert(std::is_nothrow_destructible<KeyState>::value,
              "KeyState isn't nothrow destructible!");

static_assert(std::is_nothrow_move_constructible<KeyState>::value,
              "KeyState isn't nothrow move constructible!");

static_assert(std::is_nothrow_move_assignable<KeyState>::value,
              "KeyState isn't nothrow move assignable!");

static_assert(std::is_nothrow_copy_constructible<KeyState>::value,
              "KeyState isn't nothrow copy constructible!");

static_assert(std::is_nothrow_copy_assignable<KeyState>::value,
              "KeyState isn't nothrow copy assignable!");

}  // namespace input
}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "key_state.cpp"
#endif

#endif  // CENTURION_KEY_STATE_HEADER
