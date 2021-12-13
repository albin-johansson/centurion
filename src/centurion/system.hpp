#ifndef CENTURION_SYSTEM_SYSTEM_HPP_
#define CENTURION_SYSTEM_SYSTEM_HPP_

#include <SDL.h>

#include <cassert>      // assert
#include <chrono>       // duration_cast
#include <optional>     // optional
#include <ostream>      // ostream
#include <string>       // string
#include <string_view>  // string_view

#include "core/common.hpp"
#include "core/exception.hpp"
#include "core/sdl_string.hpp"
#include "core/time.hpp"

namespace cen {

/// \addtogroup system
/// \{

enum class PowerState {
  Unknown = SDL_POWERSTATE_UNKNOWN,      /* The status is unknown. */
  OnBattery = SDL_POWERSTATE_ON_BATTERY, /* Not plugged in and running on battery. */
  NoBattery = SDL_POWERSTATE_NO_BATTERY, /* No battery available. */
  Charging = SDL_POWERSTATE_CHARGING,    /* Charging the battery. */
  Charged = SDL_POWERSTATE_CHARGED       /* Plugged in and charged. */
};

/* Indicates whether the CPU uses little-endian byte ordering. */
[[nodiscard]] constexpr auto IsLittleEndian() noexcept -> bool
{
  return SDL_BYTEORDER == SDL_LIL_ENDIAN;
}

/* Indicates whether the CPU uses big-endian byte ordering. */
[[nodiscard]] constexpr auto IsBigEndian() noexcept -> bool
{
  return SDL_BYTEORDER == SDL_BIG_ENDIAN;
}

/* Returns the current value of the high-performance counter. */
[[nodiscard]] inline auto Now() noexcept -> Uint64
{
  return SDL_GetPerformanceCounter();
}

/* Returns the frequency of the high-performance counter. */
[[nodiscard]] inline auto GetFrequency() noexcept -> Uint64
{
  return SDL_GetPerformanceFrequency();
}

/* Returns the value of the high-performance counter in seconds. */
template <typename T>
[[nodiscard]] auto NowInSeconds() noexcept(noexcept(seconds<T>{})) -> seconds<T>
{
  return seconds<T>{static_cast<T>(Now()) / static_cast<T>(GetFrequency())};
}

/* Returns the amount of milliseconds since SDL was initialized. */
[[nodiscard, deprecated]] inline auto GetTicks() noexcept(noexcept(u32_ms{Uint32{}})) -> u32_ms
{
  return u32_ms{SDL_GetTicks()};
}

#if SDL_VERSION_ATLEAST(2, 0, 18)

/* Returns the amount of milliseconds since SDL was initialized. */
[[nodiscard]] inline auto GetTicks64() noexcept(noexcept(u64_ms{Uint64{}})) -> u64_ms
{
  return u64_ms{SDL_GetTicks64()};
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 18)

/* Returns the seconds of remaining battery life. */
[[nodiscard]] inline auto GetBatterySeconds() -> std::optional<seconds<int>>
{
  int secondsLeft = -1;
  SDL_GetPowerInfo(&secondsLeft, nullptr);
  if (secondsLeft != -1) {
    return seconds<int>{secondsLeft};
  }
  else {
    return std::nullopt;
  }
}

/* Returns the minutes of remaining battery life. */
[[nodiscard]] inline auto GetBatteryMinutes() -> std::optional<minutes<int>>
{
  if (const auto secondsLeft = GetBatterySeconds()) {
    return std::chrono::duration_cast<minutes<int>>(*secondsLeft);
  }
  else {
    return std::nullopt;
  }
}

/* Returns the percentage of remaining battery life. */
[[nodiscard]] inline auto GetBatteryPercentage() noexcept -> std::optional<int>
{
  int percentageLeft = -1;
  SDL_GetPowerInfo(nullptr, &percentageLeft);
  if (percentageLeft != -1) {
    return percentageLeft;
  }
  else {
    return std::nullopt;
  }
}

[[nodiscard]] inline auto QueryBattery() noexcept -> PowerState
{
  return static_cast<PowerState>(SDL_GetPowerInfo(nullptr, nullptr));
}

[[nodiscard]] inline auto IsBatteryAvailable() noexcept -> bool
{
  const auto state = QueryBattery();
  return state != PowerState::NoBattery && state != PowerState::Unknown;
}

[[nodiscard]] inline auto IsBatteryCharging() noexcept -> bool
{
  return QueryBattery() == PowerState::Charging;
}

[[nodiscard]] inline auto IsBatteryCharged() noexcept -> bool
{
  return QueryBattery() == PowerState::Charged;
}

[[nodiscard]] inline auto GetMemoryMB() noexcept -> int
{
  return SDL_GetSystemRAM();
}

[[nodiscard]] inline auto GetMemoryGB() noexcept -> int
{
  return GetMemoryMB() / 1'000;
}

inline auto SetClipboard(const char* text) noexcept -> result
{
  assert(text);
  return SDL_SetClipboardText(text) == 0;
}

inline auto SetClipboard(const std::string& text) noexcept -> result
{
  return SetClipboard(text.c_str());
}

[[nodiscard]] inline auto GetClipboard() -> std::string
{
  const sdl_string text{SDL_GetClipboardText()};
  return text.copy();
}

/* Indicates whether the clipboard exists and contains non-empty text. */
[[nodiscard]] inline auto HasClipboard() noexcept -> bool
{
  return SDL_HasClipboardText();
}

#if SDL_VERSION_ATLEAST(2, 0, 14)

inline auto OpenURL(const char* url) noexcept -> result
{
  assert(url);
  return SDL_OpenURL(url) == 0;
}

inline auto OpenURL(const std::string& url) noexcept -> result
{
  return OpenURL(url.c_str());
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

[[nodiscard]] constexpr auto to_string(const PowerState state) -> std::string_view
{
  switch (state) {
    case PowerState::Unknown:
      return "Unknown";

    case PowerState::OnBattery:
      return "OnBattery";

    case PowerState::NoBattery:
      return "NoBattery";

    case PowerState::Charging:
      return "Charging";

    case PowerState::Charged:
      return "Charged";

    default:
      throw Error{"Did not recognize power state!"};
  }
}

inline auto operator<<(std::ostream& stream, const PowerState state) -> std::ostream&
{
  return stream << to_string(state);
}

/// \} End of group system

}  // namespace cen

#endif  // CENTURION_SYSTEM_SYSTEM_HPP_
