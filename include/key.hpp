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

/**
 * @file key.hpp
 *
 * @brief Provides the `Key` class.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

#ifndef CENTURION_KEY_HEADER
#define CENTURION_KEY_HEADER

#include <SDL_keycode.h>
#include <SDL_scancode.h>

#include "centurion_api.hpp"
#include "centurion_utils.hpp"

namespace centurion {

/**
 * @class Key
 *
 * @brief Represents a keyboard key.
 *
 * @details Instances of this class can be created from both `SDL_Scancode` and
 * `SDL_Keycode` values.
 *
 * @see `SDL_Scancode`
 * @see `SDL_Keycode`
 *
 * @since 4.0.0
 */
class Key final {
 public:
  /**
   * @brief Creates a Key instance with the `UNKNOWN` scancode and keycode
   * values.
   *
   * @since 4.0.0
   */
  CENTURION_API
  Key() noexcept;

  /**
   * @brief Creates a Key instance based on the supplied scancode.
   *
   * @param scancode the scancode that the Key will be based on.
   *
   * @since 4.0.0
   */
  CENTURION_API
  explicit Key(SDL_Scancode scancode) noexcept;

  /**
   * @brief Creates a Key instance based on the supplied keycode.
   *
   * @param keycode the keycode that the Key will be based on.
   *
   * @since 4.0.0
   */
  CENTURION_API
  explicit Key(SDL_Keycode keycode) noexcept;

  /**
   * @brief Creates a Key instance from the specified key name.
   *
   * @details If no key is associated with the specified name, then the created
   * instance will assume the key- and scancodes that represent an unknown key.
   *
   * @param name the name of the key that the created instance will
   * represent, can safely be null.
   *
   * @since 4.1.0
   */
  CENTURION_API
  explicit Key(czstring name) noexcept;

  /**
   * @brief Sets the value of the key.
   *
   * @param scancode the scancode of the key that the key instance will
   * represent.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set(SDL_Scancode scancode) noexcept;

  /**
   * @brief Sets the value of the key.
   *
   * @param keycode the keycode of the key that the key instance will
   * represent.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set(SDL_Keycode keycode) noexcept;

  /**
   * @brief Returns the name of the key associated with the Key instance.
   *
   * @details This method returns the empty string if no name is found to be
   * associated with the key that the Key instance represents.
   *
   * @return the name of the key associated with this Key instance; the empty
   * string if the name couldn't be deduced.
   *
   * @since 4.1.0
   */
  CENTURION_QUERY
  auto name() const -> std::string;

  /**
   * @brief Indicates whether or not the Key instance is associated with a known
   * key.
   *
   * @return `true` if no key is associated with the Key instance; `false`
   * otherwise.
   *
   * @since 4.1.0
   */
  [[nodiscard]] auto unknown() const noexcept -> bool
  {
    return m_scancode == SDL_SCANCODE_UNKNOWN;
  }

  /**
   * @brief Returns the scancode associated with the key.
   *
   * @return the scancode associated with the key.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto scancode() const noexcept -> SDL_Scancode
  {
    return m_scancode;
  }

  /**
   * @brief Returns the keycode associated with the key.
   *
   * @return the keycode associated with the key.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto keycode() const noexcept -> SDL_Keycode
  {
    return m_keycode;
  }

  /**
   * @brief Converts to a scancode value.
   *
   * @return an `SDL_Scancode` value.
   *
   * @since 4.0.0
   */
  [[nodiscard]] explicit operator SDL_Scancode() const noexcept
  {
    return m_scancode;
  }

  /**
   * @brief Converts to a keycode value.
   *
   * @return an `SDL_Keycode` value.
   *
   * @since 4.0.0
   */
  [[nodiscard]] explicit operator SDL_Keycode() const noexcept
  {
    return m_keycode;
  }

 private:
  SDL_Scancode m_scancode;
  SDL_Keycode m_keycode;
};

static_assert(std::is_final_v<Key>);
static_assert(std::is_copy_constructible_v<Key>);
static_assert(std::is_copy_assignable_v<Key>);
static_assert(std::is_move_constructible_v<Key>);
static_assert(std::is_move_assignable_v<Key>);

/**
 * @brief Indicates whether or not two key instances represent the same keyboard
 * key.
 *
 * @param lhs the left-hand side key.
 * @param rhs the right-hand side key.
 *
 * @return `true` if the two keys are the same; `false` otherwise.
 *
 * @since 4.0.0
 */
[[nodiscard]] inline auto operator==(const Key& lhs, const Key& rhs) noexcept
    -> bool
{
  return lhs.scancode() == rhs.scancode();
}

/**
 * @brief Indicates whether or not two key instances don't represent the same
 * keyboard key.
 *
 * @param lhs the left-hand side key.
 * @param rhs the right-hand side key.
 *
 * @return `true` if the two keys aren't the same; `false` otherwise.
 *
 * @since 4.0.0
 */
[[nodiscard]] inline auto operator!=(const Key& lhs, const Key& rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "key.cpp"
#endif  // CENTURION_HEADER_ONLY

#endif  // CENTURION_KEY_HEADER