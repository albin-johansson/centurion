/*
 * MIT License
 *
 * Copyright (c) 2019 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once
#include <optional>
#include <SDL_power.h>
#include "centurion_api.h"

namespace centurion {

/**
 * An enum class that provides values that represent various different operating systems.
 *
 * @since 3.0.0
 */
enum class Platform {
  Unknown,
  Windows,
  MacOSX,
  Linux,
  Ios,
  Android
};

/**
 * The System class is a general utility class that provides information about the operating system.
 *
 * @since 3.0.0
 */
class CENTURION_API System final {
 public:
  System() = delete;

  /**
   * Returns a value that represents the current platform.
   *
   * @return a value that represents the current platform.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API static Platform get_platform() noexcept;

  /**
   * Returns the name of the current platform.
   *
   * @return the name of the current platform; std::nullopt if the name cannot be deduced.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API static std::optional<std::string> get_platform_name() noexcept;
};

/**
 * The CPU class is a utility class that provides information related to, unsurprisingly, the CPU.
 *
 * @since 3.0.0
 */
class CENTURION_API CPU final {
 public:
  CPU() = delete;

  /**
   * Returns the CPU L1 cache line size.
   *
   * @return the CPU L1 cache line size, in bytes.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API static int get_cache_line_size() noexcept;

  /**
   * Returns the amount of cores that the CPU has.
   *
   * @return the amount of cores that the CPU has.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API static int get_cores() noexcept;
};

/**
 * The RAM class is a utility class that provides information related to, unsurprisingly, the
 * system RAM.
 *
 * @since 3.0.0
 */
class CENTURION_API RAM final {
 public:
  RAM() = delete;

  /**
   * Returns the total amount of system RAM in megabytes.
   *
   * @return the total amount of system RAM in megabytes.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API static int get_size_mb() noexcept;

  /**
   * Returns the total amount of system RAM in gigabytes.
   *
   * @return the total amount of system RAM in gigabytes.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API static int get_size_gb() noexcept;
};

/**
 * The PowerState enum class mirrors the values of the SDL_PowerState enum.
 *
 * Unknown: Indicates that the power status is unknown.
 *
 * <p>
 * OnBattery: Indicates that the device isn't plugged in and is running on the battery.
 *
 * <p>
 * NoBattery: Indicates that the device is plugged in and no battery is available.
 *
 * <p>
 * Charging: Indicates that the device is plugged in and the battery is charging.
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
inline bool operator==(PowerState a, SDL_PowerState b) noexcept {
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
inline bool operator==(SDL_PowerState a, PowerState b) noexcept {
  return a == static_cast<SDL_PowerState>(b);
}

/**
 * The Power class provides utilities related to the battery of the system.
 *
 * @since 3.0.0
 */
class CENTURION_API Power final {
 public:
  Power() = delete;

  /**
   * Returns the seconds of battery life that is remaining.
   *
   * @return the seconds of battery life that is remaining; std::nullopt if the value cannot be
   * computed.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API static std::optional<int> get_battery_seconds_left() noexcept;

  /**
   * Returns the amount of minutes of battery life that is remaining.
   *
   * @return the amount of minutes of battery life that is remaining; std::nullopt if the value
   * cannot be computed.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API static std::optional<int> get_battery_minutes_left() noexcept;

  /**
   * Returns the percentage of battery life that is currently left.
   *
   * @return the percentage of battery life that is currently left, in the range [0, 100];
   * std::nullopt if the battery percentage isn't available.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API static std::optional<int> get_battery_percentage() noexcept;

  /**
   * Returns the current power state.
   *
   * @return the current power state.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API static PowerState get_state() noexcept;
};

/**
 * The Screen class provides information about the primary screen monitor.
 *
 * @since 3.0.0
 */
class CENTURION_API Screen final {
 public:
  Screen() = delete;

  /**
   * Returns the width of the screen.
   *
   * @return the width of the screen.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API static int get_width() noexcept;

  /**
   * Returns the height of the screen.
   *
   * @return the height of the screen.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API static int get_height() noexcept;

  /**
   * Returns the refresh rate of the screen.
   *
   * @return the refresh rate of the screen.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API static int get_refresh_rate() noexcept;

  /**
   * Returns the pixel format of the desktop display mode.
   *
   * @return the pixel format of the desktop display mode.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API static uint32_t get_pixel_format() noexcept;
};

}
