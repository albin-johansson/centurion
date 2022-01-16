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

#include "common.hpp"
#include "core/sdl_string.hpp"
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

/* Represents a shared object, such as dynamic libraries. */
class SharedObject final {
 public:
  /* Loads a shared object. */
  explicit SharedObject(const char* object) : mObject{SDL_LoadObject(object)}
  {
    if (!mObject) {
      throw sdl_error{};
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
[[nodiscard]] inline auto Now() noexcept -> uint64
{
  return SDL_GetPerformanceCounter();
}

/* Returns the frequency of the high-performance counter. */
[[nodiscard]] inline auto GetFrequency() noexcept -> uint64
{
  return SDL_GetPerformanceFrequency();
}

/* Returns the value of the high-performance counter in seconds. */
[[nodiscard]] inline auto NowInSeconds() noexcept(noexcept(seconds<double>{}))
    -> seconds<double>
{
  return seconds<double>{static_cast<double>(Now()) / static_cast<double>(GetFrequency())};
}

#if SDL_VERSION_ATLEAST(2, 0, 18)

/* Returns the amount of milliseconds since SDL was initialized. */
[[nodiscard]] inline auto GetTicks() noexcept(noexcept(u64ms{uint64{}})) -> u64ms
{
  return u64ms{SDL_GetTicks64()};
}

#else

/* Returns the amount of milliseconds since SDL was initialized. */
[[nodiscard, deprecated]] inline auto GetTicks() noexcept(noexcept(u32ms{uint32{}})) -> u32ms
{
  return u32ms{SDL_GetTicks()};
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 18)

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

[[nodiscard]] inline auto ToString(const Platform id) -> std::string_view
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
      throw exception{"Did not recognize platform!"};
  }
}

inline auto operator<<(std::ostream& stream, const Platform id) -> std::ostream&
{
  return stream << ToString(id);
}

}  // namespace cen

#endif  // CENTURION_SYSTEM_SYSTEM_HPP_
