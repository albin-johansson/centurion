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

#ifndef CENTURION_PLATFORM_HEADER
#define CENTURION_PLATFORM_HEADER

#include <SDL.h>

#include "centurion_api.h"
#include "centurion_utils.h"
#include "pixel_format.h"

namespace centurion {
namespace system {

/**
 * An enum class that provides values that represent various different operating
 * systems.
 *
 * @since 3.0.0
 */
enum class Platform { Unknown, Windows, MacOSX, Linux, Ios, Android };

/**
 * Returns a value that represents the current platform.
 *
 * @return a value that represents the current platform.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API
Platform get_platform() noexcept;

/**
 * Returns the name of the current platform.
 *
 * @return the name of the current platform; std::nullopt if the name cannot
 * be deduced.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API
Optional<std::string> get_platform_name() noexcept;

}  // namespace system
}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "platform.cpp"
#endif

#endif  // CENTURION_PLATFORM_HEADER