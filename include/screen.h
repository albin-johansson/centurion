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

#ifndef CENTURION_SCREEN_HEADER
#define CENTURION_SCREEN_HEADER

#include "area.h"
#include "centurion_api.h"
#include "pixel_format.h"

namespace centurion {

/**
 * The Screen class provides information about the primary screen monitor.
 *
 * @since 3.0.0
 */
class Screen final {
 public:
  Screen() = delete;

  /**
   * Sets whether or not screen savers are enabled. By default, screen
   * savers are disabled.
   *
   * @param enabled true if screen savers should be enabled; false otherwise.
   * @since 4.0.0
   */
  CENTURION_API static void set_screen_saver_enabled(bool enabled) noexcept;

  /**
   * Indicates whether or not screen savers are enabled. By default, screen
   * savers are disabled.
   *
   * @return true if screen savers are enabled; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static bool screen_saver_enabled() noexcept;

  /**
   * Returns the width of the screen.
   *
   * @return the width of the screen.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static int width() noexcept;

  /**
   * Returns the height of the screen.
   *
   * @return the height of the screen.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static int height() noexcept;

  /**
   * Returns the size of the screen.
   *
   * @return the size of the screen.
   * @since 4.1.0
   */
  CENTURION_NODISCARD
  CENTURION_API static IArea size() noexcept;

  /**
   * Returns the refresh rate of the screen.
   *
   * @return the refresh rate of the screen.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static int refresh_rate() noexcept;

  /**
   * Returns the pixel format of the desktop display mode.
   *
   * @return the pixel format of the desktop display mode.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static PixelFormat pixel_format() noexcept;
};

}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "screen.cpp"
#endif

#endif  // CENTURION_SCREEN_HEADER