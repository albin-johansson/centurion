/*
 * MIT License
 *
 * Copyright (c) 2019-2022 Albin Johansson
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

#ifndef CENTURION_SYSTEM_PLATFORM_HPP_
#define CENTURION_SYSTEM_PLATFORM_HPP_

#include <SDL.h>

#include <cassert>      // assert
#include <ostream>      // ostream
#include <string>       // string
#include <string_view>  // string_view

#include "../common/errors.hpp"
#include "../common/primitives.hpp"

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

enum class platform_id {
  unknown,
  windows,
  macos,
  linux_os,
  ios,
  android
};

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
      throw exception {"Did not recognize platform!"};
  }
}

inline auto operator<<(std::ostream& stream, const platform_id id) -> std::ostream&
{
  return stream << to_string(id);
}

[[nodiscard]] inline auto platform_name() -> maybe<std::string>
{
  std::string name {SDL_GetPlatform()};
  if (name != "Unknown") {
    return name;
  }
  else {
    return nothing;
  }
}

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

[[nodiscard]] inline auto is_windows() noexcept -> bool
{
  return current_platform() == platform_id::windows;
}

[[nodiscard]] inline auto is_macos() noexcept -> bool
{
  return current_platform() == platform_id::macos;
}

[[nodiscard]] inline auto is_linux() noexcept -> bool
{
  return current_platform() == platform_id::linux_os;
}

[[nodiscard]] inline auto is_ios() noexcept -> bool
{
  return current_platform() == platform_id::ios;
}

[[nodiscard]] inline auto is_android() noexcept -> bool
{
  return current_platform() == platform_id::android;
}

[[nodiscard]] inline auto is_tablet() noexcept -> bool
{
  return SDL_IsTablet() == SDL_TRUE;
}

#if SDL_VERSION_ATLEAST(2, 0, 14)

inline auto open_url(const char* url) noexcept -> result
{
  assert(url);
  return SDL_OpenURL(url) == 0;
}

inline auto open_url(const std::string& url) noexcept -> result
{
  return open_url(url.c_str());
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

}  // namespace cen

#endif  // CENTURION_SYSTEM_PLATFORM_HPP_
