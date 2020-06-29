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

#ifndef CENTURION_KEY_HEADER
#define CENTURION_KEY_HEADER

#include <SDL_keycode.h>
#include <SDL_scancode.h>

#include "centurion_api.h"
#include "centurion_utils.h"

namespace centurion {

/**
 * The Key class is a simple value class that represents a keyboard key and
 * can be created from either SDL_Scancode or SDL_Keycode values. This class
 * is implicitly convertible to both SDL_Scancode and SDL_Keycode.
 *
 * @see SDL_Scancode
 * @see SDL_Keycode
 * @since 4.0.0
 */
class Key final {
 public:
  /**
   * Creates a Key instance with the UNKNOWN scancode and keycode values.
   *
   * @since 4.0.0
   */
  CENTURION_API Key() noexcept;

  /**
   * Creates a Key instance based on the supplied scancode.
   *
   * @param scancode the scancode that the Key will be based on.
   * @since 4.0.0
   */
  CENTURION_API Key(SDL_Scancode scancode) noexcept;

  /**
   * Creates a Key instance based on the supplied keycode.
   *
   * @param keycode the keycode that the Key will be based on.
   * @since 4.0.0
   */
  CENTURION_API Key(SDL_Keycode keycode) noexcept;

  /**
   * Creates a Key instance from the specified key name. If no key is
   * associated with the specified name, then the created instance will
   * assume the key- and scancodes that represent an unknown key.
   *
   * @param name the name of the key that the created instance will
   * represent, can safely be null.
   * @since 4.1.0
   */
  CENTURION_API explicit Key(CZString name) noexcept;

  /**
   * Sets the value of the key.
   *
   * @param scancode the scancode of the key that the key instance will
   * represent.
   * @since 4.0.0
   */
  CENTURION_API void set(SDL_Scancode scancode) noexcept;

  /**
   * Sets the value of the key.
   *
   * @param keycode the keycode of the key that the key instance will
   * represent.
   * @since 4.0.0
   */
  CENTURION_API void set(SDL_Keycode keycode) noexcept;

  /**
   * Returns the name of the key associated with the Key instance. This
   * method returns the empty string if no name is found to be associated with
   * the key that the Key instance represents.
   *
   * @return the name of the key associated with this Key instance; the empty
   * string if the name couldn't be deduced.
   * @since 4.1.0
   */
  CENTURION_NODISCARD
  CENTURION_API std::string name() const noexcept;

  /**
   * Indicates whether or not the Key instance is associated with a known key.
   *
   * @return true if no key is associated with the Key instance; false
   * otherwise.
   * @since 4.1.0
   */
  CENTURION_NODISCARD
  bool unknown() const noexcept { return m_scancode == SDL_SCANCODE_UNKNOWN; }

  /**
   * Returns the scancode associated with the key.
   *
   * @return the scancode associated with the key.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  SDL_Scancode scancode() const noexcept { return m_scancode; }

  /**
   * Returns the keycode associated with the key.
   *
   * @return the keycode associated with the key.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  SDL_Keycode keycode() const noexcept { return m_keycode; }

  /**
   * Implicitly converts the Key instance to an SDL_Scancode value.
   *
   * @return an SDL_Scancode value.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  operator SDL_Scancode() const noexcept { return m_scancode; }

  /**
   * Implicitly converts the Key instance to an SDL_Keycode value.
   *
   * @return an SDL_Keycode value.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  operator SDL_Keycode() const noexcept { return m_keycode; }

 private:
  SDL_Scancode m_scancode;
  SDL_Keycode m_keycode;
};

#ifdef CENTURION_HAS_IS_FINAL_TYPE_TRAIT
static_assert(std::is_final<Key>::value, "Key isn't final!");
#endif  // CENTURION_HAS_IS_FINAL_TYPE_TRAIT

static_assert(std::is_copy_constructible<Key>::value, "Key isn't copyable!");
static_assert(std::is_copy_assignable<Key>::value, "Key isn't copyable!");

static_assert(std::is_move_constructible<Key>::value, "Key isn't movable!");
static_assert(std::is_move_assignable<Key>::value, "Key isn't movable!");

/**
 * Indicates whether or not two keys represent the same keyboard key.
 *
 * @param lhs the left-hand side key.
 * @param rhs the right-hand side key.
 * @return true if the two keys are the same; false otherwise.
 * @since 4.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator==(const Key& lhs, const Key& rhs) noexcept;

/**
 * Indicates whether or not two keys don't represent the same keyboard key.
 *
 * @param lhs the left-hand side key.
 * @param rhs the right-hand side key.
 * @return true if the two keys aren't the same; false otherwise.
 * @since 4.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator!=(const Key& lhs, const Key& rhs) noexcept;

}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "key.cpp"
#endif  // CENTURION_HEADER_ONLY

#endif  // CENTURION_KEY_HEADER