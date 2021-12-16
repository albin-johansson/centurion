#ifndef CENTURION_SYSTEM_SYSTEM_HPP_
#define CENTURION_SYSTEM_SYSTEM_HPP_

#include <SDL.h>

#include <cassert>      // assert
#include <chrono>       // duration_cast
#include <cstddef>      // size_t
#include <memory>       // unique_ptr
#include <optional>     // optional
#include <ostream>      // ostream
#include <string>       // string
#include <string_view>  // string_view

#include "core/common.hpp"
#include "core/exception.hpp"
#include "core/sdl_string.hpp"
#include "core/time.hpp"
#include "detail/sdl_deleter.hpp"
#include "detail/stdlib.hpp"

namespace cen {

#ifdef __linux__
inline constexpr bool on_linux = true;
#else
inline constexpr bool on_linux = false;
#endif  // __linux__

#ifdef __APPLE__
inline constexpr bool on_apple = true;
#else
inline constexpr bool on_apple = false;
#endif  // __APPLE__

#ifdef _WIN32
inline constexpr bool on_win32 = true;
#else
inline constexpr bool on_win32 = false;
#endif  // _WIN32

#ifdef _WIN64
inline constexpr bool on_win64 = true;
#else
inline constexpr bool on_win64 = false;
#endif  // _WIN64

inline constexpr bool on_windows = on_win32 || on_win64;

#ifdef __ANDROID__
inline constexpr bool on_android = true;
#else
inline constexpr bool on_android = false;
#endif  // __ANDROID__

enum class Platform {
  Unknown,
  Windows,
  MacOS,
  Linux,
  IOS, /* Apple iOS */
  Android
};

enum class PowerState {
  Unknown = SDL_POWERSTATE_UNKNOWN,      /* The status is unknown. */
  OnBattery = SDL_POWERSTATE_ON_BATTERY, /* Not plugged in and running on battery. */
  NoBattery = SDL_POWERSTATE_NO_BATTERY, /* No battery available. */
  Charging = SDL_POWERSTATE_CHARGING,    /* Charging the battery. */
  Charged = SDL_POWERSTATE_CHARGED       /* Plugged in and charged. */
};

/* Represents a shared object, such as dynamic libraries. */
class SharedObject final {
 public:
  /* Loads a shared object. */
  explicit SharedObject(const char* object) : mObject{SDL_LoadObject(object)}
  {
    if (!mObject) {
      throw SDLError{};
    }
  }

  explicit SharedObject(const std::string& object) : SharedObject{object.c_str()} {}

  /* Attempts to load a C function with a specific name. */
  template <typename T>
  [[nodiscard]] auto LoadFunction(const char* name) const noexcept -> T*
  {
    assert(name);
    return reinterpret_cast<T*>(SDL_LoadFunction(mObject.get(), name));
  }

  template <typename T>
  [[nodiscard]] auto LoadFunction(const std::string& name) const noexcept -> T*
  {
    return LoadFunction<T>(name.c_str());
  }

 private:
  struct deleter final {
    void operator()(void* object) noexcept { SDL_UnloadObject(object); }
  };
  std::unique_ptr<void, deleter> mObject;

#ifdef CENTURION_MOCK_FRIENDLY_MODE

 public:
  SharedObject() = default;

#endif  // CENTURION_MOCK_FRIENDLY_MODE
};

#if SDL_VERSION_ATLEAST(2, 0, 14)

class Locale final {
 public:
  /* Returns the current preferred locales on the system. */
  [[nodiscard]] static auto GetPreferred() noexcept -> Locale
  {
    return Locale{SDL_GetPreferredLocales()};
  }

  /* Indicates whether a language (and optionally a country) is a part of the locale. */
  [[nodiscard]] auto HasLanguage(const char* language,
                                 const char* country = nullptr) const noexcept -> bool
  {
    assert(language);

    if (const auto* array = mLocales.get()) {
      for (auto index = 0u; array[index].language; ++index) {
        const auto& item = array[index];

        if (country && item.country) {
          if (detail::cmp(language, item.language) && detail::cmp(country, item.country)) {
            return true;
          }
        }
        else {
          if (detail::cmp(language, item.language)) {
            return true;
          }
        }
      }
    }

    return false;
  }

  /* Returns the amount of entries in the locale. */
  [[nodiscard]] auto GetSize() const noexcept -> std::size_t
  {
    std::size_t result{0};

    if (const auto* array = mLocales.get()) {
      for (auto index = 0u; array[index].language; ++index) {
        ++result;
      }
    }

    return result;
  }

  /* Indicates whether the locale contains a non-null pointer. */
  explicit operator bool() const noexcept { return mLocales != nullptr; }

 private:
  std::unique_ptr<SDL_Locale, detail::sdl_deleter> mLocales;

  explicit Locale(SDL_Locale* locales) noexcept : mLocales{locales} {}
};

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

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

[[nodiscard]] inline auto GetPlatformName() -> std::optional<std::string>
{
  std::string name{SDL_GetPlatform()};
  if (name != "Unknown") {
    return name;
  }
  else {
    return std::nullopt;
  }
}

[[nodiscard]] inline auto GetCurrentPlatform() noexcept -> Platform
{
  const auto name = GetPlatformName();
  if (name == "Windows") {
    return Platform::Windows;
  }
  else if (name == "Mac OS X") {
    return Platform::MacOS;
  }
  else if (name == "Linux") {
    return Platform::Linux;
  }
  else if (name == "iOS") {
    return Platform::IOS;
  }
  else if (name == "Android") {
    return Platform::Android;
  }
  else {
    return Platform::Unknown;
  }
}

[[nodiscard]] inline auto IsWindows() noexcept -> bool
{
  return GetCurrentPlatform() == Platform::Windows;
}

[[nodiscard]] inline auto IsMacOS() noexcept -> bool
{
  return GetCurrentPlatform() == Platform::MacOS;
}

[[nodiscard]] inline auto IsLinux() noexcept -> bool
{
  return GetCurrentPlatform() == Platform::Linux;
}

[[nodiscard]] inline auto IsIOS() noexcept -> bool
{
  return GetCurrentPlatform() == Platform::IOS;
}

[[nodiscard]] inline auto IsAndroid() noexcept -> bool
{
  return GetCurrentPlatform() == Platform::Android;
}

[[nodiscard]] inline auto IsTablet() noexcept -> bool
{
  return SDL_IsTablet() == SDL_TRUE;
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
[[nodiscard]] inline auto NowInSeconds() noexcept(noexcept(Seconds<double>{}))
    -> Seconds<double>
{
  return Seconds<double>{static_cast<double>(Now()) / static_cast<double>(GetFrequency())};
}

#if SDL_VERSION_ATLEAST(2, 0, 18)

/* Returns the amount of milliseconds since SDL was initialized. */
[[nodiscard]] inline auto GetTicks() noexcept(noexcept(U64_Millis{Uint64{}})) -> U64_Millis
{
  return U64_Millis{SDL_GetTicks64()};
}

#else

/* Returns the amount of milliseconds since SDL was initialized. */
[[nodiscard, deprecated]] inline auto GetTicks() noexcept(noexcept(U32_Millis{Uint32{}}))
    -> U32_Millis
{
  return U32_Millis{SDL_GetTicks()};
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 18)

/* Returns the seconds of remaining battery life. */
[[nodiscard]] inline auto GetBatterySeconds() -> std::optional<Seconds<int>>
{
  int secondsLeft = -1;
  SDL_GetPowerInfo(&secondsLeft, nullptr);
  if (secondsLeft != -1) {
    return Seconds<int>{secondsLeft};
  }
  else {
    return std::nullopt;
  }
}

/* Returns the minutes of remaining battery life. */
[[nodiscard]] inline auto GetBatteryMinutes() -> std::optional<Minutes<int>>
{
  if (const auto secondsLeft = GetBatterySeconds()) {
    return std::chrono::duration_cast<Minutes<int>>(*secondsLeft);
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

inline auto SetClipboard(const char* text) noexcept -> Result
{
  assert(text);
  return SDL_SetClipboardText(text) == 0;
}

inline auto SetClipboard(const std::string& text) noexcept -> Result
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

inline auto OpenURL(const char* url) noexcept -> Result
{
  assert(url);
  return SDL_OpenURL(url) == 0;
}

inline auto OpenURL(const std::string& url) noexcept -> Result
{
  return OpenURL(url.c_str());
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

/** Swaps the byte order of the specified value. */
[[nodiscard]] inline auto SwapByteOrder(const Uint16 value) noexcept -> Uint16
{
  return SDL_Swap16(value);
}

[[nodiscard]] inline auto SwapByteOrder(const Uint32 value) noexcept -> Uint32
{
  return SDL_Swap32(value);
}

[[nodiscard]] inline auto SwapByteOrder(const Uint64 value) noexcept -> Uint64
{
  return SDL_Swap64(value);
}

[[nodiscard]] inline auto SwapByteOrder(const float value) noexcept -> float
{
  return SDL_SwapFloat(value);
}

/* Swaps a big endian value to a little endian value. */
[[nodiscard]] inline auto SwapBigEndian(const Uint16 value) noexcept -> Uint16
{
  return SDL_SwapBE16(value);
}

[[nodiscard]] inline auto SwapBigEndian(const Uint32 value) noexcept -> Uint32
{
  return SDL_SwapBE32(value);
}

[[nodiscard]] inline auto SwapBigEndian(const Uint64 value) noexcept -> Uint64
{
  return SDL_SwapBE64(value);
}

[[nodiscard]] inline auto SwapBigEndian(const float value) noexcept -> float
{
  return SDL_SwapFloatBE(value);
}

/* Swaps a little endian value to a big endian value. */
[[nodiscard]] inline auto SwapLittleEndian(const Uint16 value) noexcept -> Uint16
{
  return SDL_SwapLE16(value);
}

[[nodiscard]] inline auto SwapLittleEndian(const Uint32 value) noexcept -> Uint32
{
  return SDL_SwapLE32(value);
}

[[nodiscard]] inline auto SwapLittleEndian(const Uint64 value) noexcept -> Uint64
{
  return SDL_SwapLE64(value);
}

[[nodiscard]] inline auto SwapLittleEndian(const float value) noexcept -> float
{
  return SDL_SwapFloatLE(value);
}

[[nodiscard]] inline auto to_string(const Platform id) -> std::string_view
{
  switch (id) {
    case Platform::Unknown:
      return "Unknown";

    case Platform::Windows:
      return "Windows";

    case Platform::MacOS:
      return "MacOS";

    case Platform::Linux:
      return "Linux";

    case Platform::IOS:
      return "IOS";

    case Platform::Android:
      return "Android";

    default:
      throw Error{"Did not recognize platform!"};
  }
}

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

inline auto operator<<(std::ostream& stream, const Platform id) -> std::ostream&
{
  return stream << to_string(id);
}

inline auto operator<<(std::ostream& stream, const PowerState state) -> std::ostream&
{
  return stream << to_string(state);
}

}  // namespace cen

#endif  // CENTURION_SYSTEM_SYSTEM_HPP_
