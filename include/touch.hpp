/*
 * MIT License
 *
 * Copyright (c) 2019-2021 Albin Johansson
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

#ifndef CENTURION_TOUCH_HEADER
#define CENTURION_TOUCH_HEADER

#include <SDL.h>

#include <optional>  // optional

#include "centurion_cfg.hpp"
#include "integers.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

/**
 * \namespace cen::touch
 *
 * \ingroup input
 *
 * \brief Provides the touch API components and methods.
 *
 * \since 4.3.0
 */
namespace cen::touch {

/**
 * \enum device_type
 *
 * \brief Mirrors the `SDL_TouchDeviceType` enum.
 *
 * \since 4.3.0
 *
 * \var device_type::invalid
 * Indicates an invalid touch device type.
 * \var device_type::direct
 * Indicates a touch screen with window-relative coordinates.
 * \var device_type::indirect_absolute
 * Indicates a trackpad with absolute device coordinates.
 * \var device_type::indirect_relative
 * Indicates a trackpad with screen cursor-relative coordinates.
 *
 * \headerfile touch.hpp
 */
enum class device_type
{
  invalid = SDL_TOUCH_DEVICE_INVALID,
  direct = SDL_TOUCH_DEVICE_DIRECT,
  indirect_absolute = SDL_TOUCH_DEVICE_INDIRECT_ABSOLUTE,
  indirect_relative = SDL_TOUCH_DEVICE_INDIRECT_RELATIVE
};

/**
 * \brief Indicates whether or not two touch device types are the same.
 *
 * \param lhs the left-hand side touch device type.
 * \param rhs the right-hand side touch device type.
 *
 * \return `true` if the values are the same; `false` otherwise.
 *
 * \since 4.3.0
 */
[[nodiscard]] constexpr auto operator==(const device_type lhs,
                                        const SDL_TouchDeviceType rhs) noexcept
    -> bool
{
  return static_cast<SDL_TouchDeviceType>(lhs) == rhs;
}

/**
 * \copydoc operator==(device_type, SDL_TouchDeviceType)
 */
[[nodiscard]] constexpr auto operator==(const SDL_TouchDeviceType lhs,
                                        const device_type rhs) noexcept -> bool
{
  return rhs == lhs;
}

/**
 * \brief Indicates whether or not two touch device types aren't the same.
 *
 * \param lhs the left-hand side touch device type.
 * \param rhs the right-hand side touch device type.
 *
 * \return `true` if the values aren't the same; `false` otherwise.
 *
 * \since 4.3.0
 */
[[nodiscard]] constexpr auto operator!=(const device_type lhs,
                                        const SDL_TouchDeviceType rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/**
 * \copydoc operator!=(device_type, SDL_TouchDeviceType)
 */
[[nodiscard]] constexpr auto operator!=(const SDL_TouchDeviceType lhs,
                                        const device_type rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/**
 * \brief Returns the number of registered touch devices.
 *
 * \return the number of registered touch devices.
 *
 * \since 4.3.0
 */
[[nodiscard]] inline auto num_devices() noexcept -> int
{
  return SDL_GetNumTouchDevices();
}

/**
 * \brief Returns the touch device ID associated with the specified index.
 *
 * \param index the index of the desired touch device.
 *
 * \return a `SDL_TouchID` value; or `std::nullopt` if there is no such value.
 *
 * \since 4.3.0
 */
[[nodiscard]] inline auto get_device(const int index) noexcept
    -> std::optional<SDL_TouchID>
{
  const auto device = SDL_GetTouchDevice(index);
  if (device != 0) {
    return device;
  } else {
    return std::nullopt;
  }
}

/**
 * \brief Returns the type of a touch device.
 *
 * \param id the touch device that will be queried.
 *
 * \return the type of the specified touch device.
 *
 * \since 4.3.0
 */
[[nodiscard]] inline auto type_of(const SDL_TouchID id) noexcept -> device_type
{
  return static_cast<device_type>(SDL_GetTouchDeviceType(id));
}

/**
 * \brief Returns the number of active fingers for a given touch device.
 *
 * \param id the touch device that will be queried.
 *
 * \return the amount of active fingers in a touch device.
 *
 * \since 4.3.0
 */
[[nodiscard]] inline auto num_fingers(const SDL_TouchID id) noexcept -> int
{
  return SDL_GetNumTouchFingers(id);
}

/**
 * \brief Returns the finger associated with the specified touch ID and index.
 *
 * \param id the touch ID of the finger.
 * \param index the index of the finger object.
 *
 * \return an `SDL_Finger` instance; or `std::nullopt` if no such instance could
 * be obtained.
 *
 * \since 4.3.0
 */
[[nodiscard]] inline auto get_finger(const SDL_TouchID id,
                                     const int index) noexcept
    -> std::optional<SDL_Finger>
{
  if (const auto* finger = SDL_GetTouchFinger(id, index)) {
    return *finger;
  } else {
    return std::nullopt;
  }
}

/**
 * \brief Returns the device ID used for mouse events simulated with touch
 * input.
 *
 * \return a device ID.
 *
 * \since 4.3.0
 */
[[nodiscard]] constexpr auto touch_mouse_id() noexcept -> u32
{
  return SDL_TOUCH_MOUSEID;
}

/**
 * \brief Returns the `SDL_TouchID` used by touch events simulated with mouse
 * input.
 *
 * \return a `SDL_TouchID` value.
 *
 * \since 4.3.0
 */
[[nodiscard]] constexpr auto mouse_touch_id() noexcept -> SDL_TouchID
{
  return SDL_MOUSE_TOUCHID;
}

}  // namespace cen::touch

#endif  // CENTURION_TOUCH_HEADER