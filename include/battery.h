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

#ifndef CENTURION_BATTERY_HEADER
#define CENTURION_BATTERY_HEADER

#include <SDL.h>

#include "centurion_api.h"
#include "centurion_utils.h"

namespace centurion {
namespace system {

/**
 * The PowerState enum class mirrors the values of the SDL_PowerState enum.
 *
 * Unknown: Indicates that the power status is unknown.
 *
 * <p>
 * OnBattery: Indicates that the device isn't plugged in and is running on the
 * battery.
 *
 * <p>
 * NoBattery: Indicates that the device is plugged in and no battery is
 * available.
 *
 * <p>
 * Charging: Indicates that the device is plugged in and the battery is
 * charging.
 *
 * <p>
 * Charged: Indicates that the device is plugged in and the battery is charged.
 *
 * @since 3.0.0
 */
enum class PowerState {
  Unknown = SDL_POWERSTATE_UNKNOWN,
  OnBattery = SDL_POWERSTATE_ON_BATTERY,
  NoBattery = SDL_POWERSTATE_NO_BATTERY,
  Charging = SDL_POWERSTATE_CHARGING,
  Charged = SDL_POWERSTATE_CHARGED
};

/**
 * Indicates whether or not the power states hold the same values.
 *
 * @param a the lhs Centurion power state.
 * @param b the rhs SDL power state.
 * @return true if the power states are the same.
 * @since 3.0.0
 */
inline bool operator==(PowerState a, SDL_PowerState b) noexcept
{
  return static_cast<SDL_PowerState>(a) == b;
}

/**
 * Indicates whether or not the power states hold the same values.
 *
 * @param a the lhs SDL power state.
 * @param b the rhs Centurion power state.
 * @return true if the power states are the same.
 * @since 3.0.0
 */
inline bool operator==(SDL_PowerState a, PowerState b) noexcept
{
  return a == static_cast<SDL_PowerState>(b);
}

/**
 * The Battery class provides utilities related to the battery of the system.
 *
 * @since 3.0.0
 */
class Battery final {
 public:
  Battery() = delete;

  /**
   * Returns the seconds of battery life that is remaining.
   *
   * @return the seconds of battery life that is remaining; nullopt if the
   * value cannot be computed.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  static Optional<int> get_seconds_left() noexcept;

  /**
   * Returns the amount of minutes of battery life that is remaining.
   *
   * @return the amount of minutes of battery life that is remaining;
   * nullopt if the value cannot be computed.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  static Optional<int> get_minutes_left() noexcept;

  /**
   * Returns the percentage of battery life that is currently left.
   *
   * @return the percentage of battery life that is currently left, in the range
   * [0, 100]; nullopt if the battery percentage isn't available.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  static Optional<int> get_percentage() noexcept;

  /**
   * Returns the current power state.
   *
   * @return the current power state.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  static PowerState get_state() noexcept;
};

}  // namespace system
}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "battery.cpp"
#endif

#endif  // CENTURION_BATTERY_HEADER