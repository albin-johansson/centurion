#ifndef CENTURION_PLATFORM_HEADER
#define CENTURION_PLATFORM_HEADER

#include <SDL.h>

#include <optional>     // optional
#include <ostream>      // ostream
#include <string>       // string
#include <string_view>  // string_view

#include "../core/exception.hpp"
#include "../core/str.hpp"
#include "../detail/czstring_eq.hpp"

namespace cen {

/// \addtogroup system
/// \{

/**
 * \enum platform_id
 *
 * \brief Provides values that represent various different operating systems.
 *
 * \since 3.0.0
 */
enum class platform_id
{
  unknown,   ///< Indicates that the platform is unknown.
  windows,   ///< Represents the Windows platform.
  mac_osx,   ///< Represents the Apple OSX platform.
  linux_os,  ///< Represents the Linux platform.
  ios,       ///< Represents the Apple iOS platform.
  android    ///< Represents the Android platform.
};

/// \name String conversions
/// \{

/**
 * \brief Returns a textual version of the supplied platform ID.
 *
 * \details This function returns a string that mirrors the name of the enumerator, e.g.
 * `to_string(platform_id::windows) == "windows"`.
 *
 * \param id the enumerator that will be converted.
 *
 * \return a string that mirrors the name of the enumerator.
 *
 * \throws cen_error if the enumerator is not recognized.
 *
 * \since 6.2.0
 */
[[nodiscard]] inline auto to_string(const platform_id id) -> std::string_view
{
  switch (id) {
    case platform_id::unknown:
      return "unknown";

    case platform_id::windows:
      return "windows";

    case platform_id::mac_osx:
      return "mac_osx";

    case platform_id::linux_os:
      return "linux_os";

    case platform_id::ios:
      return "ios";

    case platform_id::android:
      return "android";

    default:
      throw cen_error{"Did not recognize platform ID!"};
  }
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of a platform ID enumerator.
 *
 * \param stream the output stream that will be used.
 * \param id the enumerator that will be printed.
 *
 * \see `to_string(platform_id)`
 *
 * \return the used stream.
 *
 * \since 6.2.0
 */
inline auto operator<<(std::ostream& stream, const platform_id id) -> std::ostream&
{
  return stream << to_string(id);
}

/// \} End of streaming

/// \name Platform information functions
/// \{

/**
 * \brief Returns the value that represents the current platform.
 *
 * \return the value that represents the current platform.
 *
 * \since 3.0.0
 */
[[nodiscard]] inline auto current_platform() noexcept -> platform_id
{
  const str platform = SDL_GetPlatform();
  if (detail::czstring_eq(platform, "Windows")) {
    return platform_id::windows;
  }
  else if (detail::czstring_eq(platform, "Mac OS X")) {
    return platform_id::mac_osx;
  }
  else if (detail::czstring_eq(platform, "Linux")) {
    return platform_id::linux_os;
  }
  else if (detail::czstring_eq(platform, "iOS")) {
    return platform_id::ios;
  }
  else if (detail::czstring_eq(platform, "Android")) {
    return platform_id::android;
  }
  else {
    return platform_id::unknown;
  }
}

/**
 * \brief Indicates whether or not the current platform is Windows.
 *
 * \return `true` if the current platform is Windows; `false` otherwise.
 *
 * \since 5.0.0
 */
[[nodiscard]] inline auto is_windows() noexcept -> bool
{
  return current_platform() == platform_id::windows;
}

/**
 * \brief Indicates whether or not the current platform is Mac OSX.
 *
 * \return `true` if the current platform is Mac OSX; `false` otherwise.
 *
 * \since 5.0.0
 */
[[nodiscard]] inline auto is_mac_osx() noexcept -> bool
{
  return current_platform() == platform_id::mac_osx;
}

/**
 * \brief Indicates whether or not the current platform is Linux.
 *
 * \return `true` if the current platform is Linux; `false` otherwise.
 *
 * \since 5.0.0
 */
[[nodiscard]] inline auto is_linux() noexcept -> bool
{
  return current_platform() == platform_id::linux_os;
}

/**
 * \brief Indicates whether or not the current platform is iOS.
 *
 * \return `true` if the current platform is iOS; `false` otherwise.
 *
 * \since 5.0.0
 */
[[nodiscard]] inline auto is_ios() noexcept -> bool
{
  return current_platform() == platform_id::ios;
}

/**
 * \brief Indicates whether or not the current platform is Android.
 *
 * \return `true` if the current platform is Android; `false` otherwise.
 *
 * \since 5.0.0
 */
[[nodiscard]] inline auto is_android() noexcept -> bool
{
  return current_platform() == platform_id::android;
}

/**
 * \brief Returns the name of the current platform.
 *
 * \return the name of the current platform; `std::nullopt` if the name cannot be deduced.
 *
 * \since 3.0.0
 */
[[nodiscard]] inline auto platform_name() -> std::optional<std::string>
{
  const std::string name{SDL_GetPlatform()};
  if (name != "Unknown") {
    return name;
  }
  else {
    return std::nullopt;
  }
}

/**
 * \brief Indicates whether or not the current system is a tablet.
 *
 * \return `true` if the current system is a tablet; `false` otherwise.
 *
 * \since 5.2.0
 */
[[nodiscard]] inline auto is_tablet() noexcept -> bool
{
  return static_cast<bool>(SDL_IsTablet());
}

/**
 * \brief Indicates whether or not the current OS is 32-bit Windows.
 *
 * \note This function should return `true` on 64-bit Windows as well.
 *
 * \return `true` if the current OS is 32-bit Windows; `false` otherwise.
 *
 * \since 5.3.0
 */
[[nodiscard]] constexpr auto ifdef_win32() noexcept -> bool
{
#ifdef _WIN32
  return true;
#else
  return false;
#endif
}

/**
 * \brief Indicates whether or not the current OS is 64-bit Windows.
 *
 * \return `true` if the current OS is 64-bit Windows; `false` otherwise.
 *
 * \since 5.3.0
 */
[[nodiscard]] constexpr auto ifdef_win64() noexcept -> bool
{
#ifdef _WIN64
  return true;
#else
  return false;
#endif
}

/**
 * \brief Indicates whether or not the current OS is derived from Linux.
 *
 * \return `true` if the current OS is derived from Linux; `false` otherwise.
 *
 * \since 5.3.0
 */
[[nodiscard]] constexpr auto ifdef_linux() noexcept -> bool
{
#ifdef __linux__
  return true;
#else
  return false;
#endif
}

/**
 * \brief Indicates whether or not the current OS is Android.
 *
 * \return `true` if the current OS is Android; `false` otherwise.
 *
 * \since 5.3.0
 */
[[nodiscard]] constexpr auto ifdef_android() noexcept -> bool
{
#ifdef __ANDROID__
  return true;
#else
  return false;
#endif
}

/**
 * \brief Indicates whether or not the current OS is either MacOS or iOS.
 *
 * \return `true` if the current OS is Android; `false` otherwise.
 *
 * \since 5.3.0
 */
[[nodiscard]] constexpr auto ifdef_apple() noexcept -> bool
{
#ifdef __APPLE__
  return true;
#else
  return false;
#endif
}

/// \} End of platform information functions

/// \} End of group system

}  // namespace cen

#endif  // CENTURION_PLATFORM_HEADER