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
 * @file game_controller.hpp
 *
 * @brief Provides the game controller API.
 *
 * @todo Expand the game controller API.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

#ifndef CENTURION_GAME_CONTROLLER_HEADER
#define CENTURION_GAME_CONTROLLER_HEADER

#include <SDL_gamecontroller.h>

#include <cstring>
#include <memory>
#include <ostream>
#include <string>
#include <type_traits>

#include "button_state.hpp"
#include "centurion_api.hpp"
#include "centurion_types.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace centurion {

/**
 * @enum game_controller_axis
 *
 * @ingroup input
 *
 * @brief Mirrors the values of the `SDL_GameControllerAxis` enum.
 *
 * @see `SDL_GameControllerAxis`
 *
 * @since 4.0.0
 *
 * @headerfile game_controller.hpp
 */
enum class game_controller_axis {
  invalid = SDL_CONTROLLER_AXIS_INVALID,
  left_x = SDL_CONTROLLER_AXIS_LEFTX,
  left_y = SDL_CONTROLLER_AXIS_LEFTY,
  right_x = SDL_CONTROLLER_AXIS_RIGHTX,
  right_y = SDL_CONTROLLER_AXIS_RIGHTY,
  trigger_left = SDL_CONTROLLER_AXIS_TRIGGERLEFT,
  trigger_right = SDL_CONTROLLER_AXIS_TRIGGERRIGHT,
  max = SDL_CONTROLLER_AXIS_MAX
};

/**
 * @brief Indicates whether or not two game controller axis values are the same.
 *
 * @ingroup input
 *
 * @param lhs the left-hand-side game controller axis value.
 * @param rhs the right-hand-side game controller axis value.
 *
 * @return `true` if the values are the same; `false` otherwise.
 *
 * @since 4.0.0
 */
[[nodiscard]] inline constexpr auto operator==(
    game_controller_axis lhs,
    SDL_GameControllerAxis rhs) noexcept -> bool
{
  return static_cast<SDL_GameControllerAxis>(lhs) == rhs;
}

/**
 * @copydoc operator==(game_controller_axis, SDL_GameControllerAxis)
 *
 * @ingroup input
 */
[[nodiscard]] inline constexpr auto operator==(
    SDL_GameControllerAxis lhs,
    game_controller_axis rhs) noexcept -> bool
{
  return rhs == lhs;
}

/**
 * @brief Indicates whether or not two game controller axis values aren't the
 * same.
 *
 * @ingroup input
 *
 * @param lhs the left-hand-side game controller axis value.
 * @param rhs the right-hand-side game controller axis value.
 *
 * @return `true` if the values aren't the same; `false` otherwise.
 *
 * @since 4.0.0
 */
[[nodiscard]] inline constexpr auto operator!=(
    game_controller_axis lhs,
    SDL_GameControllerAxis rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/**
 * @copydoc operator!=(game_controller_axis, SDL_GameControllerAxis)
 *
 * @ingroup input
 */
[[nodiscard]] inline constexpr auto operator!=(
    SDL_GameControllerAxis lhs,
    game_controller_axis rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/**
 * @enum game_controller_button
 *
 * @ingroup input
 *
 * @brief Mirrors the values of the `SDL_GameControllerButton` enum.
 *
 * @since 4.0.0
 *
 * @headerfile game_controller.hpp
 */
enum class game_controller_button {
  invalid = SDL_CONTROLLER_BUTTON_INVALID,
  a = SDL_CONTROLLER_BUTTON_A,
  b = SDL_CONTROLLER_BUTTON_B,
  x = SDL_CONTROLLER_BUTTON_X,
  y = SDL_CONTROLLER_BUTTON_Y,
  back = SDL_CONTROLLER_BUTTON_BACK,
  guide = SDL_CONTROLLER_BUTTON_GUIDE,
  start = SDL_CONTROLLER_BUTTON_START,
  left_stick = SDL_CONTROLLER_BUTTON_LEFTSTICK,
  right_stick = SDL_CONTROLLER_BUTTON_RIGHTSTICK,
  left_shoulder = SDL_CONTROLLER_BUTTON_LEFTSHOULDER,
  right_shoulder = SDL_CONTROLLER_BUTTON_RIGHTSHOULDER,
  dpad_up = SDL_CONTROLLER_BUTTON_DPAD_UP,
  dpad_down = SDL_CONTROLLER_BUTTON_DPAD_DOWN,
  dpad_left = SDL_CONTROLLER_BUTTON_DPAD_LEFT,
  dpad_right = SDL_CONTROLLER_BUTTON_DPAD_RIGHT,
  max = SDL_CONTROLLER_BUTTON_MAX
};

/**
 * @brief Indicates whether or not two game controller button values are the
 * same.
 *
 * @ingroup input
 *
 * @param lhs the left-hand side game controller button value.
 * @param rhs the right-hand side game controller button value.
 *
 * @return `true` if the game controller button values are the same; `false`
 * otherwise.
 *
 * @since 4.0.0
 */
[[nodiscard]] inline constexpr auto operator==(
    game_controller_button lhs,
    SDL_GameControllerButton rhs) noexcept -> bool
{
  return static_cast<SDL_GameControllerButton>(lhs) == rhs;
}

/**
 * @copydoc operator==(game_controller_button, SDL_GameControllerButton)
 *
 * @ingroup input
 */
[[nodiscard]] inline constexpr auto operator==(
    SDL_GameControllerButton lhs,
    game_controller_button rhs) noexcept -> bool
{
  return rhs == lhs;
}

/**
 * @brief Indicates whether or not two game controller button values aren't the
 * same.
 *
 * @ingroup input
 *
 * @param lhs the left-hand side game controller button value.
 * @param rhs the right-hand side game controller button value.
 *
 * @return `true` if the game controller button values aren't the same; `false`
 * otherwise.
 *
 * @since 4.0.0
 */
[[nodiscard]] inline constexpr auto operator!=(
    game_controller_button lhs,
    SDL_GameControllerButton rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/**
 * @copydoc operator!=(game_controller_button, SDL_GameControllerButton)
 *
 * @ingroup input
 */
[[nodiscard]] inline constexpr auto operator!=(
    SDL_GameControllerButton lhs,
    game_controller_button rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/**
 * @class game_controller
 *
 * @brief Represents a game controller, e.g. an xbox-controller.
 *
 * @ingroup input
 *
 * @since 5.0.0
 *
 * @headerfile game_controller.hpp
 */
class game_controller final {
 public:
  /**
   * @brief Attempts to create a `game_controller` instance.
   *
   * @details The joystick index is the same as the device index passed to the
   * `joystick` constructor. The index passed as an argument refers to the
   * n'th game controller on the system.
   *
   * @note The supplied index is not the value which will identify the
   * controller in controller events. Instead, the joystick's instance id
   * (SDL_JoystickID) will be used.
   *
   * @param joystickIndex the device index, can't be >= than the amount of
   * number of joysticks.
   *
   * @throws centurion_exception if the game controller cannot be opened.
   *
   * @since 5.0.0
   */
  CENTURION_API
  explicit game_controller(int joystickIndex);

  CENTURION_API
  ~game_controller() noexcept;

  CENTURION_QUERY
  auto name() const noexcept -> czstring;

  CENTURION_QUERY
  static auto name(int joystickIndex) noexcept -> czstring;

  CENTURION_QUERY
  auto get_button_state(game_controller_button button) const noexcept
      -> button_state;

  CENTURION_QUERY
  auto is_button_pressed(game_controller_button button) const noexcept -> bool;

  CENTURION_QUERY
  auto is_button_released(game_controller_button button) const noexcept -> bool;

  CENTURION_QUERY
  auto get_joystick() noexcept -> SDL_Joystick*;  // TODO joystick_handle

  CENTURION_API
  static void update() noexcept;

  CENTURION_QUERY
  static auto is_valid(int joystickIndex) noexcept -> bool;

  CENTURION_API
  static void set_polling(bool polling) noexcept;

  CENTURION_QUERY
  static auto is_polling() noexcept -> bool;

 private:
  SDL_GameController* m_controller;
};

static_assert(std::is_final_v<game_controller>);
static_assert(std::is_nothrow_destructible_v<game_controller>);

static_assert(std::is_nothrow_move_constructible_v<game_controller>);
static_assert(std::is_nothrow_move_assignable_v<game_controller>);

}  // namespace centurion

#endif  // CENTURION_GAME_CONTROLLER_HEADER
