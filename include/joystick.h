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
 * @brief Provides the joystick API.
 *
 * @file joystick.h
 * @author Albin Johansson
 * @copyright MIT License
 * @date 2019-2020
 */

#ifndef CENTURION_JOYSTICK_HEADER
#define CENTURION_JOYSTICK_HEADER

#include <SDL_joystick.h>

#include "centurion_api.h"
#include "centurion_utils.h"

namespace centurion {

/**
 * @brief Represents various types of joysticks.
 *
 * @class Joystick
 * @headerfile joystick.h
 * @since 4.2.0
 * @see SDL_Joystick
 */
class Joystick final {
 public:
  /**
   * @brief Mirrors the SDL_JoystickPowerLevel enum.
   *
   * @enum Power
   * @headerfile joystick.h
   * @since 4.2.0
   */
  enum class Power {
    Unknown = SDL_JOYSTICK_POWER_UNKNOWN, /**< Unknown power level. */
    Empty = SDL_JOYSTICK_POWER_EMPTY,     /**< Indicates <= 5% power. */
    Low = SDL_JOYSTICK_POWER_LOW,         /**< Indicates <= 20% power. */
    Medium = SDL_JOYSTICK_POWER_MEDIUM,   /**< Indicates <= 70% power. */
    Full = SDL_JOYSTICK_POWER_FULL,       /**< Indicates <= 100% power. */
    Wired = SDL_JOYSTICK_POWER_WIRED,     /**< Wired joystick, no need to
                                           * worry about power. */
    Max = SDL_JOYSTICK_POWER_MAX          /**< Maximum power level. */
  };

  CENTURION_API explicit Joystick(int deviceIndex);

  CENTURION_API explicit Joystick(Owner<SDL_Joystick*> joystick);

  CENTURION_API ~Joystick() noexcept;

  /**
   * @brief Returns the current power level of the joystick.
   * @return a `Joystick::Power` value that represents the current power level.
   * @since 4.2.0
   */
  CENTURION_NODISCARD
  CENTURION_API Power power() const noexcept;

 private:
  SDL_Joystick* m_joystick;
};

}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "joystick.cpp"
#endif  // CENTURION_HEADER_ONLY

#endif  // CENTURION_JOYSTICK_HEADER