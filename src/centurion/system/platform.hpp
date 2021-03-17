#ifndef CENTURION_PLATFORM_HEADER
#define CENTURION_PLATFORM_HEADER

#include <SDL.h>

#include <cassert>   // assert
#include <optional>  // optional
#include <string>    // string

#include "../centurion_cfg.hpp"
#include "../czstring.hpp"
#include "../detail/czstring_eq.hpp"
#include "../not_null.hpp"
#include "../video/pixel_format.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

/**
 * \namespace cen::platform
 *
 * \ingroup system
 *
 * \brief Contains utilities related to platform information.
 *
 * \since 5.0.0
 *
 * \headerfile platform.hpp
 */
namespace cen::platform {

/// \addtogroup system
/// \{

/**
 * \enum platform_id
 *
 * \brief Provides values that represent various different operating
 * systems.
 *
 * \details The `linuxx` enumerator has its ugly name because of a weird
 * compilation error on GCC.
 *
 * \since 3.0.0
 *
 * \headerfile platform.hpp
 */
enum class platform_id
{
  unknown,  ///< Indicates that the platform is unknown.
  windows,  ///< Represents the Windows platform.
  mac_osx,  ///< Represents the Apple OSX platform.
  linuxx,   ///< Represents the Linux platform.
  ios,      ///< Represents the Apple iOS platform.
  android   ///< Represents the Android platform.
};

#if SDL_VERSION_ATLEAST(2, 0, 14)

/**
 * \brief Attempts to open a URL using a web browser or even a file manager for
 * local files.
 *
 * \note This function will return `true` if there was at least an "attempt" to
 * open the specified URL, but it doesn't mean that the URL was successfully
 * loaded.
 *
 * \remarks This function will differ greatly in its effects depending on the
 * current platform.
 *
 * \param url the URL that should be opened, cannot be null.
 *
 * \return `true` on success; `false` otherwise.
 *
 * \see SDL_OpenURL
 *
 * \since 5.2.0
 */
inline auto open_url(const not_null<czstring> url) noexcept -> bool
{
  assert(url);
  return SDL_OpenURL(url) == 0;
}

/**
 * \see open_url()
 * \since 5.3.0
 */
inline auto open_url(const std::string& url) noexcept -> bool
{
  return open_url(url.c_str());
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

/**
 * \brief Returns the value that represents the current platform.
 *
 * \return the value that represents the current platform.
 *
 * \since 3.0.0
 */
[[nodiscard]] inline auto id() noexcept -> platform_id
{
  const czstring platform = SDL_GetPlatform();
  if (detail::czstring_eq(platform, "Windows"))
  {
    return platform_id::windows;
  }
  else if (detail::czstring_eq(platform, "Mac OS X"))
  {
    return platform_id::mac_osx;
  }
  else if (detail::czstring_eq(platform, "Linux"))
  {
    return platform_id::linuxx;
  }
  else if (detail::czstring_eq(platform, "iOS"))
  {
    return platform_id::ios;
  }
  else if (detail::czstring_eq(platform, "Android"))
  {
    return platform_id::android;
  }
  else
  {
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
  return id() == platform_id::windows;
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
  return id() == platform_id::mac_osx;
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
  return id() == platform_id::linuxx;
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
  return id() == platform_id::ios;
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
  return id() == platform_id::android;
}

/**
 * \brief Returns the name of the current platform.
 *
 * \return the name of the current platform; `std::nullopt` if the name cannot
 * be deduced.
 *
 * \since 3.0.0
 */
[[nodiscard]] inline auto name() -> std::optional<std::string>
{
  const std::string name{SDL_GetPlatform()};
  if (name != "Unknown")
  {
    return name;
  }
  else
  {
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

/// \} End of group system

}  // namespace cen::platform

#endif  // CENTURION_PLATFORM_HEADER