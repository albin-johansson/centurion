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

#ifndef CENTURION_VIDEO_DISPLAY_HPP_
#define CENTURION_VIDEO_DISPLAY_HPP_

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../common/math.hpp"
#include "../common/primitives.hpp"
#include "pixels.hpp"

namespace cen {

enum class orientation {
  unknown = SDL_ORIENTATION_UNKNOWN,
  landscape = SDL_ORIENTATION_LANDSCAPE,
  landscape_flipped = SDL_ORIENTATION_LANDSCAPE_FLIPPED,
  portrait = SDL_ORIENTATION_PORTRAIT,
  portrait_flipped = SDL_ORIENTATION_PORTRAIT_FLIPPED
};

struct dpi_info final {
  float diagonal {};
  float horizontal {};
  float vertical {};
};

class display_mode final {
 public:
  [[nodiscard]] static auto current(const int index = 0) -> display_mode
  {
    SDL_DisplayMode mode {};
    if (SDL_GetCurrentDisplayMode(index, &mode) == 0) {
      return display_mode {mode};
    }
    else {
      throw sdl_error {};
    }
  }

  [[nodiscard]] static auto desktop(const int index = 0) -> display_mode
  {
    SDL_DisplayMode mode {};
    if (SDL_GetDesktopDisplayMode(index, &mode) == 0) {
      return display_mode {mode};
    }
    else {
      throw sdl_error {};
    }
  }

  [[nodiscard]] auto format() const noexcept -> pixel_format
  {
    return static_cast<pixel_format>(mMode.format);
  }

  [[nodiscard]] auto width() const noexcept -> int { return mMode.w; }
  [[nodiscard]] auto height() const noexcept -> int { return mMode.h; }
  [[nodiscard]] auto size() const noexcept -> iarea { return {mMode.w, mMode.h}; }

  [[nodiscard]] auto refresh_rate() const noexcept -> maybe<int>
  {
    if (mMode.refresh_rate != 0) {
      return mMode.refresh_rate;
    }
    else {
      return nothing;
    }
  }

  [[nodiscard]] auto driver_data() noexcept -> void* { return mMode.driverdata; }
  [[nodiscard]] auto driver_data() const noexcept -> const void* { return mMode.driverdata; }

 private:
  SDL_DisplayMode mMode {};

  explicit display_mode(const SDL_DisplayMode mode) : mMode {mode} {}
};

inline void set_screen_saver_enabled(const bool enabled) noexcept
{
  if (enabled) {
    SDL_EnableScreenSaver();
  }
  else {
    SDL_DisableScreenSaver();
  }
}

[[nodiscard]] inline auto is_screen_saver_enabled() noexcept -> bool
{
  return SDL_IsScreenSaverEnabled();
}

[[nodiscard]] inline auto display_count() noexcept -> maybe<int>
{
  const auto count = SDL_GetNumVideoDisplays();
  if (count >= 1) {
    return count;
  }
  else {
    return nothing;
  }
}

[[nodiscard]] inline auto display_name(const int index = 0) -> maybe<std::string>
{
  if (const char* name = SDL_GetDisplayName(index)) {
    return std::string {name};
  }
  else {
    return nothing;
  }
}

[[nodiscard]] inline auto display_orientation(const int index = 0) noexcept -> orientation
{
  return static_cast<orientation>(SDL_GetDisplayOrientation(index));
}

[[nodiscard]] inline auto display_dpi(const int index = 0) noexcept -> maybe<dpi_info>
{
  dpi_info info;
  if (SDL_GetDisplayDPI(index, &info.diagonal, &info.horizontal, &info.vertical) == 0) {
    return info;
  }
  else {
    return nothing;
  }
}

[[nodiscard]] inline auto display_bounds(const int index = 0) noexcept -> maybe<irect>
{
  irect result;
  if (SDL_GetDisplayBounds(index, result.data()) == 0) {
    return result;
  }
  else {
    return nothing;
  }
}

[[nodiscard]] inline auto display_usable_bounds(const int index = 0) noexcept -> maybe<irect>
{
  irect result;
  if (SDL_GetDisplayUsableBounds(index, result.data()) == 0) {
    return result;
  }
  else {
    return nothing;
  }
}

#if SDL_VERSION_ATLEAST(2, 24, 0)

[[nodiscard]] inline auto display_with(const ipoint& point) noexcept -> maybe<int>
{
  const auto index = SDL_GetPointDisplayIndex(point.data());
  if (index >= 0) {
    return index;
  }
  else {
    return nothing;
  }
}

[[nodiscard]] inline auto display_with(const irect& rect) noexcept -> maybe<int>
{
  const auto index = SDL_GetRectDisplayIndex(rect.data());
  if (index >= 0) {
    return index;
  }
  else {
    return nothing;
  }
}

#endif  // SDL_VERSION_ATLEAST(2, 24, 0)

[[nodiscard]] constexpr auto to_string(const orientation o) -> std::string_view
{
  switch (o) {
    case orientation::unknown:
      return "unknown";

    case orientation::landscape:
      return "landscape";

    case orientation::landscape_flipped:
      return "landscape_flipped";

    case orientation::portrait:
      return "portrait";

    case orientation::portrait_flipped:
      return "portrait_flipped";

    default:
      throw exception {"Did not recognize display orientation!"};
  }
}

inline auto operator<<(std::ostream& stream, const orientation o) -> std::ostream&
{
  return stream << to_string(o);
}

}  // namespace cen

#endif  // CENTURION_VIDEO_DISPLAY_HPP_
