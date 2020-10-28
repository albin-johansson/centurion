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
 * \defgroup input Input
 *
 * \brief Contains components related to input from mice, keyboards,
 * controllers, etc.
 */

#ifndef CENTURION_KEY_STATE_HEADER
#define CENTURION_KEY_STATE_HEADER

#include <SDL.h>

#include <array>

#include "centurion_api.hpp"
#include "detail/utils.hpp"
#include "key_code.hpp"
#include "key_modifier.hpp"
#include "scan_code.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/**
 * \class key_state
 *
 * \ingroup input
 *
 * \brief Provides information about the keyboard state.
 *
 * \details Using the keyboard state is an alternative to using events for
 * keyboard input.
 *
 * \since 3.0.0
 *
 * \headerfile key_state.hpp
 */
class key_state final
{
 public:
  /**
   * \brief Creates a `key_state` instance.
   *
   * \since 3.0.0
   */
  CENTURION_API
  key_state() noexcept;

  /**
   * \brief Updates the state of the key state object.
   *
   * \note `SDL_PumpEvents` isn't invoked by this method.
   *
   * \since 3.0.0
   */
  CENTURION_API
  void update() noexcept;

  /**
   * \brief Indicates whether or not the specified key is being pressed.
   *
   * \details This method returns false if the supplied key isn't recognized.
   *
   * \param code the scan code that will be checked.
   *
   * \return `true` if the key is being pressed; `false` otherwise.
   *
   * \since 3.0.0
   */
  CENTURION_QUERY
  auto is_pressed(const scan_code& code) const noexcept -> bool;

  /**
   * \brief Indicates whether or not the specified key is being pressed.
   *
   * \details This method returns false if the supplied key isn't recognized.
   *
   * \note This method is slightly slower that the `scan_code` version.
   *
   * \param code the key code that will be checked.
   *
   * \return `true` if the key is being pressed; `false` otherwise.
   *
   * \since 3.0.0
   */
  CENTURION_QUERY
  auto is_pressed(const key_code& code) const noexcept -> bool;

  /**
   * \brief Indicates whether or not the specified key has been pressed during
   * more than one update of the key state.
   *
   * \details This method returns false if the supplied key isn't recognized.
   *
   * \param code the scan code that will be checked.
   *
   * \return `true` if the key has been held down; `false` otherwise.
   *
   * \since 3.0.0
   */
  CENTURION_QUERY
  auto is_held(const scan_code& code) const noexcept -> bool;

  /**
   * \brief Indicates whether or not the specified key has been pressed during
   * more than one update of the key state.
   *
   * \details This method returns false if the supplied key isn't recognized.
   *
   * \note This method is slightly slower that the `scan_code` version.
   *
   * \param code the key code that will be checked.
   *
   * \return `true` if the key has been held down; `false` otherwise.
   *
   * \since 3.0.0
   */
  CENTURION_QUERY
  auto is_held(const key_code& code) const noexcept -> bool;

  /**
   * \brief Indicates whether or not a key just became pressed in the last
   * update of the key state.
   *
   * \details This method returns false if the supplied key isn't recognized.
   *
   * \param code the scan code that will be checked.
   *
   * \return `true` if the key has just been pressed; `false` otherwise.
   *
   * \since 3.0.0
   */
  CENTURION_QUERY
  auto was_just_pressed(const scan_code& code) const noexcept -> bool;

  /**
   * \brief Indicates whether or not a key just became pressed in the last
   * update of the key state.
   *
   * \details This method returns false if the supplied key isn't recognized.
   *
   * \note This method is slightly slower that the `scan_code` version.
   *
   * \param code the key code that will be checked.
   *
   * \return `true` if the key has just been pressed; `false` otherwise.
   *
   * \since 3.0.0
   */
  CENTURION_QUERY
  auto was_just_pressed(const key_code& code) const noexcept -> bool;

  /**
   * \brief Indicates whether or not the specified key was released in the last
   * update of the key state.
   *
   * \details This method returns false if the supplied key isn't recognized.
   *
   * \param code the scan code that will be checked.
   *
   * \return `true` if the key was released; `false` otherwise.
   *
   * \since 3.0.0
   */
  CENTURION_QUERY
  auto was_just_released(const scan_code& code) const noexcept -> bool;

  /**
   * \brief Indicates whether or not the specified key was released in the last
   * update of the key state.
   *
   * \details This method returns false if the supplied key isn't recognized.
   *
   * \note This method is slightly slower that the `scan_code` version.
   *
   * \param code the key code that will be checked.
   *
   * \return `true` if the key was released; `false` otherwise.
   *
   * \since 3.0.0
   */
  CENTURION_QUERY
  auto was_just_released(const key_code& code) const noexcept -> bool;

  /**
   * \brief Indicates whether or not the specified key modifier is active.
   *
   * \note Multiple key modifiers can be active at the same time.
   *
   * \param modifier the key modifier that will be checked.
   *
   * \return `true` if the specified key modifier is active; `false` otherwise.
   *
   * \since 4.0.0
   */
  CENTURION_QUERY
  static auto modifier_active(key_modifier modifier) noexcept -> bool;

  /**
   * \brief Returns the total amount of keys.
   *
   * \return the total amount of keys.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto amount_of_keys() const noexcept -> int
  {
    return m_nKeys;
  }

 private:
  const u8* m_states{};
  std::array<u8, static_cast<int>(SDL_NUM_SCANCODES)> m_previousStates;
  int m_nKeys{};
};

}  // namespace cen

#endif  // CENTURION_KEY_STATE_HEADER
