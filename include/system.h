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

#ifndef CENTURION_SYSTEM_HEADER
#define CENTURION_SYSTEM_HEADER

#include <SDL.h>

#include <optional>

#include "centurion_api.h"
#include "pixel_format.h"

namespace centurion {
namespace system {

/**
 * An enum class that provides values that represent various different operating
 * systems.
 *
 * @since 3.0.0
 */
enum class Platform { Unknown, Windows, MacOSX, Linux, Ios, Android };

/**
 * Returns a value that represents the current platform.
 *
 * @return a value that represents the current platform.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API
Platform get_platform() noexcept;

#ifdef CENTURION_HAS_OPTIONAL

/**
 * Returns the name of the current platform.
 *
 * @return the name of the current platform; std::nullopt if the name cannot
 * be deduced.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API
std::optional<std::string> get_platform_name() noexcept;

#endif

/**
 * The CPU class is a utility class that provides information related to,
 * unsurprisingly, the CPU.
 *
 * @since 3.0.0
 */
class CPU final {
 public:
  CPU() = delete;

  /**
   * Returns the CPU L1 cache line size.
   *
   * @return the CPU L1 cache line size, in bytes.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  static int get_cache_line_size() noexcept;

  /**
   * Returns the amount of cores that the CPU has.
   *
   * @return the amount of cores that the CPU has.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  static int get_cores() noexcept;

  /**
   * Indicates whether or not the CPU has the RDTSC instruction.
   * 
   * @return true if the CPU has the RDTSC instruction; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  static bool has_rdtsc() noexcept;

  /**
   * Indicates whether or not the CPU has AltiVec features. 
   * 
   * @return true if the CPU has AltiVec features; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  static bool has_altivec() noexcept;

  /**
   * Indicates whether or not the CPU has MMX features.
   * 
   * @return true if the CPU has MMX features; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  static bool has_mmx() noexcept;

  /**
   * Indicates whether or not the CPU has 3DNow! features.
   * 
   * @return true if the CPU has 3DNow! features; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  static bool has_3dnow() noexcept;

  /**
   * Indicates whether or not the CPU has SSE features.
   * 
   * @return true if the CPU has SSE features; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  static bool has_sse() noexcept;

  /**
   * Indicates whether or not the CPU has SSE2 features.
   * 
   * @return true if the CPU has SSE2 features; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  static bool has_sse2() noexcept;

  /**
   * Indicates whether or not the CPU has SSE3 features.
   * 
   * @return true if the CPU has SSE3 features; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  static bool has_sse3() noexcept;

  /**
   * Indicates whether or not the CPU has SSE4.1 features.
   * 
   * @return true if the CPU has SSE4.1 features; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  static bool has_sse41() noexcept;

  /**
   * Indicates whether or not the CPU has SSE4.2 features.
   * 
   * @return true if the CPU has SSE4.2 features; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  static bool has_sse42() noexcept;

  /**
   * Indicates whether or not the CPU has AVX features.
   * 
   * @return true if the CPU has AVX features; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  static bool has_avx() noexcept;

  /**
   * Indicates whether or not the CPU has AVX2 features.
   * 
   * @return true if the CPU has AVX2 features; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  static bool has_avx2() noexcept;

  /**
   * Indicates whether or not the CPU has AVX-512F (foundation) features.
   * 
   * @return true if the CPU has AVX-512F (foundation) features; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  static bool has_avx512f() noexcept;

  /**
   * Indicates whether or not the CPU has NEON (ARM SIMD) features.
   * 
   * @return true if the CPU has NEON (ARM SIMD) features; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  static bool has_neon() noexcept;

  /**
   * Indicates whether or not the CPU uses big-endian byte ordering.
   *
   * @return true if the CPU uses big-endian byte ordering; false otherwise.
   * @since 3.1.0
   */
  CENTURION_NODISCARD
  constexpr static bool is_big_endian() noexcept
  {
    return SDL_BYTEORDER == SDL_BIG_ENDIAN;
  }

  /**
   * Indicates whether or not the CPU uses little-endian byte ordering.
   *
   * @return true if the CPU uses little-endian byte ordering; false otherwise.
   * @since 3.1.0
   */
  CENTURION_NODISCARD
  constexpr static bool is_little_endian() noexcept
  {
    return SDL_BYTEORDER == SDL_LIL_ENDIAN;
  }
};

/**
 * The RAM class is a utility class that provides information related to,
 * unsurprisingly, the system RAM.
 *
 * @since 3.0.0
 */
class RAM final {
 public:
  RAM() = delete;

  /**
   * Returns the total amount of system RAM in megabytes.
   *
   * @return the total amount of system RAM in megabytes.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  static int get_size_mb() noexcept;

  /**
   * Returns the total amount of system RAM in gigabytes.
   *
   * @return the total amount of system RAM in gigabytes.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  static int get_size_gb() noexcept;
};

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

#ifdef CENTURION_HAS_OPTIONAL

  /**
   * Returns the seconds of battery life that is remaining.
   *
   * @return the seconds of battery life that is remaining; std::nullopt if the
   * value cannot be computed.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  static std::optional<int> get_seconds_left() noexcept;

  /**
   * Returns the amount of minutes of battery life that is remaining.
   *
   * @return the amount of minutes of battery life that is remaining;
   * std::nullopt if the value cannot be computed.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  static std::optional<int> get_minutes_left() noexcept;

  /**
   * Returns the percentage of battery life that is currently left.
   *
   * @return the percentage of battery life that is currently left, in the range
   * [0, 100]; std::nullopt if the battery percentage isn't available.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  static std::optional<int> get_percentage() noexcept;

#endif

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

/**
 * The Screen class provides information about the primary screen monitor.
 *
 * @since 3.0.0
 */
class Screen final {
 public:
  Screen() = delete;

  /**
   * Sets whether or not screen savers are enabled. By default, screen
   * savers are disabled.
   *
   * @param enabled true if screen savers should be enabled; false otherwise.
   * @since 4.0.0
   */
  CENTURION_API
  static void set_screen_saver_enabled(bool enabled) noexcept;

  /**
   * Indicates whether or not screen savers are enabled. By default, screen
   * savers are disabled.
   *
   * @return true if screen savers are enabled; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  static bool is_screen_saver_enabled() noexcept;

  /**
   * Returns the width of the screen.
   *
   * @return the width of the screen.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  static int get_width() noexcept;

  /**
   * Returns the height of the screen.
   *
   * @return the height of the screen.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  static int get_height() noexcept;

  /**
   * Returns the refresh rate of the screen.
   *
   * @return the refresh rate of the screen.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  static int get_refresh_rate() noexcept;

  /**
   * Returns the pixel format of the desktop display mode.
   *
   * @return the pixel format of the desktop display mode.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  static video::PixelFormat get_pixel_format() noexcept;
};

}  // namespace system
}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "system.cpp"
#endif

#endif  // CENTURION_SYSTEM_HEADER