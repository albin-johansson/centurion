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

#ifndef CENTURION_GAME_CONTROLLER_BUTTON_HEADER
#define CENTURION_GAME_CONTROLLER_BUTTON_HEADER

#include <SDL_gamecontroller.h>

#include "centurion_api.h"

namespace centurion {
namespace event {

/**
 * The GameControllerButton enum class mirrors the values of the
 * SDL_GameControllerButton enum.
 *
 * @since 4.0.0
 */
enum class GameControllerButton {
  Invalid = SDL_CONTROLLER_BUTTON_INVALID,
  A = SDL_CONTROLLER_BUTTON_A,
  B = SDL_CONTROLLER_BUTTON_B,
  X = SDL_CONTROLLER_BUTTON_X,
  Y = SDL_CONTROLLER_BUTTON_Y,
  Back = SDL_CONTROLLER_BUTTON_BACK,
  Guide = SDL_CONTROLLER_BUTTON_GUIDE,
  Start = SDL_CONTROLLER_BUTTON_START,
  LeftStick = SDL_CONTROLLER_BUTTON_LEFTSTICK,
  RightStick = SDL_CONTROLLER_BUTTON_RIGHTSTICK,
  LeftShoulder = SDL_CONTROLLER_BUTTON_LEFTSHOULDER,
  RightShoulder = SDL_CONTROLLER_BUTTON_RIGHTSHOULDER,
  DpadUp = SDL_CONTROLLER_BUTTON_DPAD_UP,
  DpadDown = SDL_CONTROLLER_BUTTON_DPAD_DOWN,
  DpadLeft = SDL_CONTROLLER_BUTTON_DPAD_LEFT,
  DpadRight = SDL_CONTROLLER_BUTTON_DPAD_RIGHT,
  Max = SDL_CONTROLLER_BUTTON_MAX
};

/**
 * Indicates whether or not two game controller button values are the same.
 *
 * @param button the lhs Centurion game controller button.
 * @param sdlButton the rhs SDL game controller button.
 * @return true if the game controller button values are the same; false
 * otherwise.
 * @since 4.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator==(GameControllerButton button,
                              SDL_GameControllerButton sdlButton) noexcept;

/**
 * Indicates whether or not two game controller button values are the same.
 *
 * @param button the lhs SDL game controller button.
 * @param sdlButton the rhs Centurion game controller button.
 * @return true if the game controller button values are the same; false
 * otherwise.
 * @since 4.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator==(SDL_GameControllerButton sdlButton,
                              GameControllerButton button) noexcept;

/**
 * Indicates whether or not two game controller button values aren't the same.
 *
 * @param button the lhs Centurion game controller button.
 * @param sdlButton the rhs SDL game controller button.
 * @return true if the game controller button values aren't the same; false
 * otherwise.
 * @since 4.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator!=(GameControllerButton button,
                              SDL_GameControllerButton sdlButton) noexcept;

/**
 * Indicates whether or not two game controller button values aren't the same.
 *
 * @param button the lhs SDL game controller button.
 * @param sdlButton the rhs Centurion game controller button.
 * @return true if the game controller button values aren't the same; false
 * otherwise.
 * @since 4.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator!=(SDL_GameControllerButton sdlButton,
                              GameControllerButton button) noexcept;
}  // namespace event
}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "game_controller_button.cpp"
#endif  // CENTURION_HEADER_ONLY

#endif  // CENTURION_GAME_CONTROLLER_BUTTON_HEADER
