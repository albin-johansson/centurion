/*
 * MIT License
 *
 * Copyright (c) 2019-2021 Albin Johansson
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

#include <algorithm>  // copy
#include <array>      // array

#include "centurion_cfg.hpp"
#include "integers.hpp"
#include "key_code.hpp"
#include "key_modifier.hpp"
#include "scan_code.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/// \addtogroup input
/// \{

/**
 * \class key_state
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
  key_state() noexcept
  {
    m_states = SDL_GetKeyboardState(&m_nKeys);
  }

  /**
   * \brief Updates the state of the key state object.
   *
   * \note `SDL_PumpEvents` isn't invoked by this method.
   *
   * \since 3.0.0
   */
  void update() noexcept
  {
    std::copy(m_states, m_states + m_nKeys, m_prevStates.begin());
  }

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
  [[nodiscard]] auto is_pressed(const scan_code& code) const noexcept -> bool
  {
    return check_state(code, [this](const SDL_Scancode sc) noexcept {
      return m_states[sc];
    });
  }

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
  [[nodiscard]] auto is_pressed(const key_code& code) const noexcept -> bool
  {
    return is_pressed(code.to_scan_code());
  }

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
  [[nodiscard]] auto is_held(const scan_code& code) const noexcept -> bool
  {
    return check_state(code, [this](const SDL_Scancode sc) noexcept {
      return m_states[sc] && m_prevStates[sc];
    });
  }

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
  [[nodiscard]] auto is_held(const key_code& code) const noexcept -> bool
  {
    return is_held(code.to_scan_code());
  }

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
  [[nodiscard]] auto was_just_pressed(const scan_code& code) const noexcept
      -> bool
  {
    return check_state(code, [this](const SDL_Scancode sc) noexcept {
      return m_states[sc] && !m_prevStates[sc];
    });
  }

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
  [[nodiscard]] auto was_just_pressed(const key_code& code) const noexcept
      -> bool
  {
    return was_just_pressed(code.to_scan_code());
  }

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
  [[nodiscard]] auto was_just_released(const scan_code& code) const noexcept
      -> bool
  {
    return check_state(code, [this](const SDL_Scancode sc) noexcept {
      return !m_states[sc] && m_prevStates[sc];
    });
  }

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
  [[nodiscard]] auto was_just_released(const key_code& code) const noexcept
      -> bool
  {
    return was_just_released(code.to_scan_code());
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
   * \since 4.0.0
   */
  [[nodiscard]] static auto modifier_active(
      const key_modifier modifier) noexcept -> bool
  {
    return static_cast<SDL_Keymod>(modifier) & SDL_GetModState();
  }

  /**
   * \brief Returns the total amount of keys.
   *
   * \return the total amount of keys.
   *
   * \deprecated Since 5.1.0, use `key_count()` instead.
   *
   * \since 3.0.0
   */
  [[nodiscard, deprecated]] auto amount_of_keys() const noexcept -> int
  {
    return key_count();
  }

  /**
   * \brief Returns the total amount of keys.
   *
   * \return the total amount of keys.
   *
   * \since 5.1.0
   */
  [[nodiscard]] auto key_count() const noexcept -> int
  {
    return m_nKeys;
  }

 private:
  const u8* m_states{};
  std::array<u8, cen::scan_code::count()> m_prevStates{};
  int m_nKeys{};

  template <typename Predicate>
  auto check_state(const cen::scan_code& code,
                   Predicate&& predicate) const noexcept -> bool
  {
    const auto sc = code.get();
    if (sc >= 0 && sc < m_nKeys) {
      return predicate(sc);
    } else {
      return false;
    }
  }
};

/// \}

}  // namespace cen

#endif  // CENTURION_KEY_STATE_HEADER
