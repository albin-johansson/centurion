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
#include "detail/sdl_deleter.hpp"
#include "detail/stdlib.hpp"

namespace cen {

/**
 * \defgroup system System
 *
 * \brief Provides system-related information, such as RAM amount, counters, and platform.
 */

/// \addtogroup system
/// \{

/// \name Platform indicator constants
/// \{

/**
 * \var on_linux
 * \brief Indicates whether the current platform is Linux.
 */

/**
 * \var on_apple
 * \brief Indicates whether the current platform is some sort of Apple system.
 */

/**
 * \var on_win32
 * \brief Indicates whether the current platform is at least 32-bit Windows.
 */

/**
 * \var on_win64
 * \brief Indicates whether the current platform is 64-bit Windows.
 */

/**
 * \var on_windows
 * \brief Indicates whether the current platform is some variant of Windows.
 */

/**
 * \var on_android
 * \brief Indicates whether the current platform is Android.
 */

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

/// \} End of platform indicator constants

/**
 * \brief Represents various operating systems.
 */
enum class platform_id
{
  unknown,   ///< An unknown platform.
  windows,   ///< The Windows operating system.
  macos,     ///< The macOS operating system.
  linux_os,  ///< The Linux operating system.
  ios,       ///< The iOS operating system.
  android    ///< The Android operating system.
};

/// \name Platform ID functions
/// \{

[[nodiscard]] inline auto to_string(const platform_id id) -> std::string_view
{
  switch (id) {
    case platform_id::unknown:
      return "unknown";

    case platform_id::windows:
      return "windows";

    case platform_id::macos:
      return "macos";

    case platform_id::linux_os:
      return "linux_os";

    case platform_id::ios:
      return "ios";

    case platform_id::android:
      return "android";

    default:
      throw exception{"Did not recognize platform!"};
  }
}

inline auto operator<<(std::ostream& stream, const platform_id id) -> std::ostream&
{
  return stream << to_string(id);
}

/// \} End of platform ID functions

/**
 * \brief Represents a shared object, e.g. dynamic libraries.
 */
class shared_object final
{
 public:
  /**
   * \brief Loads a shared object.
   *
   * \param object the name of the shared object.
   *
   * \throws sdl_error if the object cannot be loaded.
   */
  explicit shared_object(const char* object) : mObject{SDL_LoadObject(object)}
  {
    if (!mObject) {
      throw sdl_error{};
    }
  }

  /// \copydoc shared_object()
  explicit shared_object(const std::string& object) : shared_object{object.c_str()} {}

  /**
   * \brief Attempts to load a C function.
   *
   * \note This function can only load C functions.
   *
   * \tparam T the signature of the function, e.g. `void(int, float)`.
   *
   * \param name the function name.
   *
   * \return the loaded function; a null pointer is returned if something goes wrong.
   */
  template <typename T>
  [[nodiscard]] auto load_function(const char* name) const noexcept -> T*
  {
    assert(name);
    return reinterpret_cast<T*>(SDL_LoadFunction(mObject.get(), name));
  }

  /// \copydoc load_function()
  template <typename T>
  [[nodiscard]] auto load_function(const std::string& name) const noexcept -> T*
  {
    return load_function<T>(name.c_str());
  }

 private:
  struct deleter final
  {
    void operator()(void* object) noexcept { SDL_UnloadObject(object); }
  };
  std::unique_ptr<void, deleter> mObject;

#ifdef CENTURION_MOCK_FRIENDLY_MODE

 public:
  shared_object() = default;

#endif  // CENTURION_MOCK_FRIENDLY_MODE
};

/// \name Runtime platform information functions
/// \{

/**
 * \brief Returns the name of the current platform.
 *
 * \return the name of the current platform; an empty optional is returned if the name cannot
 * be deduced.
 */
[[nodiscard]] inline auto platform_name() -> std::optional<std::string>
{
  std::string name{SDL_GetPlatform()};
  if (name != "Unknown") {
    return name;
  }
  else {
    return std::nullopt;
  }
}

/**
 * \brief Returns an identifier that represents the current platform.
 *
 * \return the current platform.
 */
[[nodiscard]] inline auto current_platform() noexcept -> platform_id
{
  const auto name = platform_name();
  if (name == "Windows") {
    return platform_id::windows;
  }
  else if (name == "Mac OS X") {
    return platform_id::macos;
  }
  else if (name == "Linux") {
    return platform_id::linux_os;
  }
  else if (name == "iOS") {
    return platform_id::ios;
  }
  else if (name == "Android") {
    return platform_id::android;
  }
  else {
    return platform_id::unknown;
  }
}

/**
 * \brief Indicates whether the current platform is Windows.
 *
 * \return `true` if the platform is Windows; `false` otherwise.
 */
[[nodiscard]] inline auto is_windows() noexcept -> bool
{
  return current_platform() == platform_id::windows;
}

/**
 * \brief Indicates whether the current platform is macOS.
 *
 * \return `true` if the platform is macOS; `false` otherwise.
 */
[[nodiscard]] inline auto is_macos() noexcept -> bool
{
  return current_platform() == platform_id::macos;
}

/**
 * \brief Indicates whether the current platform is Linux.
 *
 * \return `true` if the platform is Linux; `false` otherwise.
 */
[[nodiscard]] inline auto is_linux() noexcept -> bool
{
  return current_platform() == platform_id::linux_os;
}

/**
 * \brief Indicates whether the current platform is iOS.
 *
 * \return `true` if the platform is iOS; `false` otherwise.
 */
[[nodiscard]] inline auto is_ios() noexcept -> bool
{
  return current_platform() == platform_id::ios;
}

/**
 * \brief Indicates whether the current platform is Android.
 *
 * \return `true` if the platform is Android; `false` otherwise.
 */
[[nodiscard]] inline auto is_android() noexcept -> bool
{
  return current_platform() == platform_id::android;
}

/**
 * \brief Indicates whether the current system is a tablet.
 *
 * \return `true` if the system is a tablet; `false` otherwise.
 */
[[nodiscard]] inline auto is_tablet() noexcept -> bool
{
  return SDL_IsTablet() == SDL_TRUE;
}

/// \} End of runtime platform information functions

/// \name System counter functions
/// \{

/**
 * \brief Returns the frequency of the system high-performance counter.
 *
 * \return the counter frequency.
 */
[[nodiscard]] inline auto frequency() noexcept -> uint64
{
  return SDL_GetPerformanceFrequency();
}

/**
 * \brief Returns the current value of the high-performance counter.
 *
 * \note The unit of the returned value is platform dependent, see `frequency()`.
 *
 * \return the current value of the counter.
 */
[[nodiscard]] inline auto now() noexcept -> uint64
{
  return SDL_GetPerformanceCounter();
}

/**
 * \brief Returns the value of the system high-performance counter in seconds.
 *
 * \tparam T the representation type.
 *
 * \return the current value of the counter.
 */
[[nodiscard]] inline auto now_in_seconds() noexcept(noexcept(seconds<double>{}))
    -> seconds<double>
{
  return seconds<double>{static_cast<double>(now()) / static_cast<double>(frequency())};
}

#if SDL_VERSION_ATLEAST(2, 0, 18)

/**
 * \brief Returns the amount of milliseconds since SDL was initialized.
 *
 * \return the time since SDL was initialized.
 *
 * \atleastsdl 2.0.18
 */
[[nodiscard]] inline auto ticks64() noexcept(noexcept(u64ms{uint64{}})) -> u64ms
{
  return u64ms{SDL_GetTicks64()};
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 18)

/**
 * \brief Returns the amount of milliseconds since SDL was initialized.
 *
 * \return the time since SDL was initialized.
 *
 * \deprecated since 7.0.0, use `ticks64()` instead.
 */
[[nodiscard, deprecated]] inline auto ticks32() noexcept(noexcept(u32ms{uint32{}})) -> u32ms
{
  return u32ms{SDL_GetTicks()};
}

/// \} End of system counter functions

/// \name System RAM functions
/// \{

/**
 * \brief Returns the total amount of system RAM.
 *
 * \return the amount of RAM, in megabytes.
 */
[[nodiscard]] inline auto ram_mb() noexcept -> int
{
  return SDL_GetSystemRAM();
}

/**
 * \brief Returns the total amount of system RAM.
 *
 * \return the amount of RAM, in gigabytes.
 */
[[nodiscard]] inline auto ram_gb() noexcept -> int
{
  return ram_mb() / 1'000;
}

/// \} End of system RAM functions

/// \name Clipboard functions
/// \{

/**
 * \brief Sets the current clipboard text.
 *
 * \param text the text that will be stored in the clipboard.
 *
 * \return `success` if the clipboard text was set; `failure` otherwise.
 */
inline auto set_clipboard(const char* text) noexcept -> result
{
  assert(text);
  return SDL_SetClipboardText(text) == 0;
}

/// \copydoc set_clipboard()
inline auto set_clipboard(const std::string& text) noexcept -> result
{
  return set_clipboard(text.c_str());
}

/**
 * \brief Indicates whether the clipboard exists and contains non-empty text.
 *
 * \return `true` if the clipboard has non-empty text; `false` otherwise.
 */
[[nodiscard]] inline auto has_clipboard() noexcept -> bool
{
  return SDL_HasClipboardText();
}

/**
 * \brief Returns the current text in the clipboard.
 *
 * \details If the clipboard cannot be obtained, this function returns an empty string.
 *
 * \return the current clipboard text.
 */
[[nodiscard]] inline auto get_clipboard() -> std::string
{
  const sdl_string text{SDL_GetClipboardText()};
  return text.copy();
}

/// \} End of clipboard functions

/// \name URL functions
/// \{

#if SDL_VERSION_ATLEAST(2, 0, 14)

/**
 * \brief Attempts to open a URL using a web browser (or file manager for local files).
 *
 * \details This function will return `success` if there was at least an attempt to open
 * the specified URL, but it doesn't mean that the URL was successfully loaded.
 *
 * \details This function will differ greatly in its effects depending on the current platform.
 *
 * \param url the URL that should be opened.
 *
 * \return `success` if there was an attempt to open the URL; `failure` otherwise.
 *
 * \atleastsdl 2.0.14
 */
inline auto open_url(const char* url) noexcept -> result
{
  assert(url);
  return SDL_OpenURL(url) == 0;
}

/// \copydoc open_url()
inline auto open_url(const std::string& url) noexcept -> result
{
  return open_url(url.c_str());
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

/// \} End of URL functions

/// \} End of group system

}  // namespace cen

#endif  // CENTURION_SYSTEM_SYSTEM_HPP_
