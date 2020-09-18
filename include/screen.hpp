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

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

/**
 * @namespace cen::screen
 *
 * @ingroup system
 *
 * @brief Contains functions that provide information about the screen.
 *
 * @since 5.0.0
 *
 * @headerfile screen.hpp
 */
namespace cen::screen {

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

#endif  // CENTURION_SCREEN_HEADER