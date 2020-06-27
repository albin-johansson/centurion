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
 * @brief Provides battery related utilities.
 *
 * @file battery.h
 * @author Albin Johansson
 * @date 2019-2020
 * @copyright MIT License
 */

#ifndef CENTURION_BATTERY_HEADER
#define CENTURION_BATTERY_HEADER

#include <SDL.h>

#include "centurion_api.h"
#include "centurion_utils.h"

namespace centurion {

/**
 * @enum PowerState
 * @brief Mirrors the values of the SDL_PowerState enum.
 * @headerfile battery.h
 * @since 3.0.0
 */
enum class PowerState {
  Unknown = SDL_POWERSTATE_UNKNOWN, /**< The status is unknown. */
  OnBattery =
      SDL_POWERSTATE_ON_BATTERY, /**< Not plugged in and running on battery.*/
  NoBattery = SDL_POWERSTATE_NO_BATTERY, /**< No battery available.*/
  Charging = SDL_POWERSTATE_CHARGING,    /**< Currently charging the battery.*/
  Charged = SDL_POWERSTATE_CHARGED       /**< Currently plugged in and
                                          * charged.*/
};

/**
 * Indicates whether or not the power states hold the same values.
 *
 * @param a the lhs Centurion power state.
 * @param b the rhs SDL power state.
 * @return true if the power states are the same.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator==(PowerState a, SDL_PowerState b) noexcept;

/**
 * Indicates whether or not the power states hold the same values.
 *
 * @param a the lhs SDL power state.
 * @param b the rhs Centurion power state.
 * @return true if the power states are the same.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator==(SDL_PowerState a, PowerState b) noexcept;

/**
 * @class Battery
 * @brief Provides utilities related to the battery of the system.
 *
 * @since 3.0.0
 * @headerfile battery.h
 */
class Battery final {
 public:
  Battery() = delete;

  /**
   * Returns the seconds of battery life that is remaining.
   *
   * @return the seconds of battery life that is remaining; nothing if the
   * value cannot be computed.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static Optional<int> seconds_left() noexcept;

  /**
   * Returns the amount of minutes of battery life that is remaining.
   *
   * @return the amount of minutes of battery life that is remaining;
   * nothing if the value cannot be computed.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static Optional<int> minutes_left() noexcept;

  /**
   * Returns the percentage of battery life that is currently left.
   *
   * @return the percentage of battery life that is currently left, in the range
   * [0, 100]; nothing if the battery percentage isn't available.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static Optional<int> percentage() noexcept;

  /**
   * Returns the current power state.
   *
   * @return the current power state.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static PowerState state() noexcept;

  /**
   * Indicates whether or not the system is running on a battery. This method
   * is simply a convenience method that is based on the <code>state()
   * </code> method.
   *
   * @return true if the system is running on a battery; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static bool exists() noexcept;
};

}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "battery.cpp"
#endif

#endif  // CENTURION_BATTERY_HEADER