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

/**
 * @file screen.hpp
 *
 * @brief Provides information about the system screen.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

#ifndef CENTURION_SCREEN_HEADER
#define CENTURION_SCREEN_HEADER

#include "area.hpp"
#include "centurion_api.hpp"
#include "pixel_format.hpp"
#include "rect.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

/// @addtogroup system
/// @{

/**
 * @namespace cen::screen
 *
 * @brief Contains functions that provide information about the screen.
 *
 * @since 5.0.0
 *
 * @headerfile screen.hpp
 */
namespace cen::screen {

/**
 * @struct dpi_info
 *
 * @brief Simple POD-type for storing diagonal, horizontal and vertical DPI
 * values.
 *
 * @headerfile screen.hpp
 *
 * @since 5.0.0
 */
struct dpi_info final
{
  float diagonal{};    ///< The diagonal DPI value.
  float horizontal{};  ///< The horizontal DPI value.
  float vertical{};    ///< The vertical DPI value.
};

/**
 * @enum orientation
 *
 * @brief Represents different screen orientations.
 *
 * @since 5.0.0
 *
 * @see SDL_DisplayOrientation
 *
 * @headerfile screen.hpp
 */
enum class orientation
{
  unknown = SDL_ORIENTATION_UNKNOWN,
  landscape = SDL_ORIENTATION_LANDSCAPE,
  landscape_flipped = SDL_ORIENTATION_LANDSCAPE_FLIPPED,
  portrait = SDL_ORIENTATION_PORTRAIT,
  portrait_flipped = SDL_ORIENTATION_PORTRAIT_FLIPPED
};

/**
 * @brief Returns DPI information about a display.
 *
 * @param displayIndex the index of the display to query, must be in the range
 * [0, `cen::screen::amount()`].
 *
 * @return DPI information about the specified display; `std::nullopt` if
 * something went wrong.
 *
 * @see SDL_GetDisplayDPI
 *
 * @since 5.0.0
 */
[[nodiscard]] inline auto dpi(int displayIndex = 0) -> std::optional<dpi_info>
{
  dpi_info info{};
  const auto res = SDL_GetDisplayDPI(
      displayIndex, &info.diagonal, &info.horizontal, &info.vertical);
  if (res == 0) {
    return info;
  } else {
    return std::nullopt;
  }
}

/**
 * @brief Returns vertical DPI information about a display.
 *
 * @param displayIndex the index of the display to query, must be in the range
 * [0, `cen::screen::amount()`].
 *
 * @return the vertical DPI information about the specified display;
 * `std::nullopt` if something went wrong.
 *
 * @since 5.0.0
 */
[[nodiscard]] inline auto vertical_dpi(int displayIndex = 0)
    -> std::optional<float>
{
  float vertical{};
  const auto res = SDL_GetDisplayDPI(displayIndex, nullptr, nullptr, &vertical);
  if (res == 0) {
    return vertical;
  } else {
    return std::nullopt;
  }
}

/**
 * @brief Returns diagonal DPI information about a display.
 *
 * @param displayIndex the index of the display to query, must be in the range
 * [0, `cen::screen::amount()`].
 *
 * @return the diagonal DPI information about the specified display;
 * `std::nullopt` if something went wrong.
 *
 * @since 5.0.0
 */
[[nodiscard]] inline auto diagonal_dpi(int displayIndex = 0)
    -> std::optional<float>
{
  float diagonal{};
  const auto res = SDL_GetDisplayDPI(displayIndex, &diagonal, nullptr, nullptr);
  if (res == 0) {
    return diagonal;
  } else {
    return std::nullopt;
  }
}

/**
 * @brief Returns horizontal DPI information about a display.
 *
 * @param displayIndex the index of the display to query, must be in the range
 * [0, `cen::screen::amount()`].
 *
 * @return the horizontal DPI information about the specified display;
 * `std::nullopt` if something went wrong.
 *
 * @since 5.0.0
 */
[[nodiscard]] inline auto horizontal_dpi(int displayIndex = 0)
    -> std::optional<float>
{
  float horizontal{};
  if (!SDL_GetDisplayDPI(displayIndex, nullptr, &horizontal, nullptr)) {
    return horizontal;
  } else {
    return std::nullopt;
  }
}

/**
 * @brief Returns the bounds of a display.
 *
 * @param displayIndex the index of the display to query, must be in the range
 * [0, `cen::screen::amount()`].
 *
 * @return the bounds of the specified display; `std::nullopt` if something went
 * wrong.
 *
 * @see SDL_GetDisplayBounds
 *
 * @since 5.0.0
 */
[[nodiscard]] inline auto bounds(int displayIndex = 0) -> std::optional<irect>
{
  irect result{};
  if (SDL_GetDisplayBounds(displayIndex, &result.get()) == 0) {
    return result;
  } else {
    return std::nullopt;
  }
}

/**
 * @brief Returns the usable bounds of a display.
 *
 * @param displayIndex the index of the display to query, must be in the range
 * [0, `cen::screen::amount()`].
 *
 * @return the usable bounds of the specified display; `std::nullopt` if
 * something went wrong.
 *
 * @see SDL_GetDisplayUsableBounds
 *
 * @since 5.0.0
 */
[[nodiscard]] inline auto usable_bounds(int displayIndex = 0)
    -> std::optional<irect>
{
  irect result{};
  if (SDL_GetDisplayUsableBounds(displayIndex, &result.get()) == 0) {
    return result;
  } else {
    return std::nullopt;
  }
}

/**
 * @brief Returns the orientation of the specified display.
 *
 * @param displayIndex the index of the display to obtain the orientation of,
 * must be in the range [0, `cen::screen::amount()`].
 *
 * @return the orientation of the specified display.
 *
 * @since 5.0.0
 */
[[nodiscard]] inline auto get_orientation(int displayIndex = 0) -> orientation
{
  const auto result = SDL_GetDisplayOrientation(displayIndex);
  return static_cast<orientation>(result);
}

/**
 * @brief Returns the amount of available displays.
 *
 * @return the number of available displays.
 *
 * @since 5.0.0
 */
[[nodiscard]] inline auto amount() noexcept -> int
{
  return SDL_GetNumVideoDisplays();
}

/**
 * @brief Returns the name of a display.
 *
 * @param displayIndex the index of the display to obtain the name of, must be
 * in the range [0, `cen::screen::amount()`].
 *
 * @return the name of the specified display, might be null.
 *
 * @since 5.0.0
 */
[[nodiscard]] inline auto name(int displayIndex = 0) noexcept -> czstring
{
  return SDL_GetDisplayName(displayIndex);
}

/**
 * @brief Sets whether or not screen savers are enabled.
 *
 * @note By default, screen savers are disabled.
 *
 * @param enabled `true` if screen savers should be enabled; `false` otherwise.
 *
 * @since 4.0.0
 */
CENTURION_API
void set_screen_saver_enabled(bool enabled) noexcept;

/**
 * @brief Indicates whether or not screen savers are enabled.
 *
 * @note By default, screen savers are disabled.
 *
 * @return `true` if screen savers are enabled; `false` otherwise.
 *
 * @since 4.0.0
 */
CENTURION_QUERY
auto screen_saver_enabled() noexcept -> bool;

/**
 * @brief Returns the width of the screen.
 *
 * @return the width of the screen.
 *
 * @since 3.0.0
 */
CENTURION_QUERY
auto width() noexcept -> int;

/**
 * @brief Returns the height of the screen.
 *
 * @return the height of the screen.
 *
 * @since 3.0.0
 */
CENTURION_QUERY
auto height() noexcept -> int;

/**
 * @brief Returns the size of the screen.
 *
 * @return the size of the screen.
 *
 * @since 4.1.0
 */
CENTURION_QUERY
auto size() noexcept -> iarea;

/**
 * @brief Returns the refresh rate of the screen.
 *
 * @return the refresh rate of the screen.
 *
 * @since 3.0.0
 */
CENTURION_QUERY
auto refresh_rate() noexcept -> int;

/**
 * @brief Returns the pixel format of the desktop display mode.
 *
 * @note This function returns the pixel format used by the desktop display
 * mode, i.e. the fullscreen display mode, so it might not be accurate for
 * non-fullscreen windows.
 *
 * @return the pixel format of the desktop display mode.
 *
 * @since 3.0.0
 */
CENTURION_QUERY
auto get_pixel_format() noexcept -> pixel_format;

}  // namespace cen::screen

/// @}

#endif  // CENTURION_SCREEN_HEADER