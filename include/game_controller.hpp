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

#include "centurion_api.hpp"

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

}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "game_controller.cpp"
#endif  // CENTURION_HEADER_ONLY

#endif  // CENTURION_GAME_CONTROLLER_HEADER
