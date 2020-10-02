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
 * @file platform.hpp
 *
 * @brief Provides utilities for obtaining information about the current
 * platform.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

/**
 * @defgroup system System
 *
 * @brief Contains various utilities related to system resources.
 */

#ifndef CENTURION_PLATFORM_HEADER
#define CENTURION_PLATFORM_HEADER

#include <optional>
#include <string>

#include "centurion_api.hpp"
#include "detail/utils.hpp"
#include "pixel_format.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

/**
 * @namespace cen::platform
 *
 * @ingroup system
 *
 * @brief Contains utilities related to platform information.
 *
 * @since 5.0.0
 *
 * @headerfile platform.hpp
 */
namespace cen::platform {

/// @addtogroup system
/// @{

/**
 * @enum platform_id
 *
 * @brief Provides values that represent various different operating
 * systems.
 *
 * @details The `linuxx` enumerator has its ugly name because of a weird
 * compilation error on GCC.
 *
 * @since 3.0.0
 *
 * @headerfile platform.hpp
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

/**
 * @brief Returns the value that represents the current platform.
 *
 * @return the value that represents the current platform.
 *
 * @since 3.0.0
 */
CENTURION_QUERY
auto id() noexcept -> platform_id;

/**
 * @brief Indicates whether or not the current platform is Windows.
 *
 * @return `true` if the current platform is Windows; `false` otherwise.
 *
 * @since 5.0.0
 */
CENTURION_QUERY
auto is_windows() noexcept -> bool;

/**
 * @brief Indicates whether or not the current platform is Mac OSX.
 *
 * @return `true` if the current platform is Mac OSX; `false` otherwise.
 *
 * @since 5.0.0
 */
CENTURION_QUERY
auto is_mac_osx() noexcept -> bool;

/**
 * @brief Indicates whether or not the current platform is Linux.
 *
 * @return `true` if the current platform is Linux; `false` otherwise.
 *
 * @since 5.0.0
 */
CENTURION_QUERY
auto is_linux() noexcept -> bool;

/**
 * @brief Indicates whether or not the current platform is iOS.
 *
 * @return `true` if the current platform is iOS; `false` otherwise.
 *
 * @since 5.0.0
 */
CENTURION_QUERY
auto is_ios() noexcept -> bool;

/**
 * @brief Indicates whether or not the current platform is Android.
 *
 * @return `true` if the current platform is Android; `false` otherwise.
 *
 * @since 5.0.0
 */
CENTURION_QUERY
auto is_android() noexcept -> bool;

/**
 * @brief Returns the name of the current platform.
 *
 * @return the name of the current platform; `std::nullopt` if the name cannot
 * be deduced.
 *
 * @since 3.0.0
 */
CENTURION_QUERY
auto name() -> std::optional<std::string>;

/// @}

}  // namespace cen::platform

#endif  // CENTURION_PLATFORM_HEADER