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

#ifndef CENTURION_TOUCH_HEADER
#define CENTURION_TOUCH_HEADER

#include <SDL_touch.h>

#include "centurion_api.h"
#include "centurion_utils.h"

namespace centurion {

/**
 * A type alias for SDL_TouchID.
 *
 * @since 4.0.0
 */
using TouchID = SDL_TouchID;

/**
 * A type alias for SDL_GestureID.
 *
 * @since 4.0.0
 */
using GestureID = SDL_GestureID;

/**
 * A type alias for SDL_FingerID.
 *
 * @since 4.0.0
 */
using FingerID = SDL_FingerID;

namespace touch {

/**
 * @enum DeviceType
 * @brief Mirrors the `SDL_TouchDeviceType` enum.
 *
 * @since 4.3.0
 *
 * @var DeviceType::Invalid
 * Indicates an invalid touch device type.
 * @var DeviceType::Direct
 * Indicates a touch screen with window-relative coordinates.
 * @var DeviceType::IndirectAbsolute
 * Indicates a trackpad with absolute device coordinates.
 * @var DeviceType::IndirectRelative
 * Indicates a trackpad with screen cursor-relative coordinates.
 *
 * @headerfile touch.h
 */
enum class DeviceType {
  Invalid = SDL_TOUCH_DEVICE_INVALID,
  Direct = SDL_TOUCH_DEVICE_DIRECT,
  IndirectAbsolute = SDL_TOUCH_DEVICE_INDIRECT_ABSOLUTE,
  IndirectRelative = SDL_TOUCH_DEVICE_INDIRECT_RELATIVE
};

/**
 * @brief Indicates whether or not two touch device types are the same.
 *
 * @param lhs the left-hand side touch device type.
 * @param rhs the right-hand side touch device type.
 *
 * @return `true` if the values are the same; `false` otherwise.
 *
 * @since 4.3.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator==(DeviceType lhs, SDL_TouchDeviceType rhs) noexcept;

/**
 * @brief Indicates whether or not two touch device types are the same.
 *
 * @param lhs the left-hand side touch device type.
 * @param rhs the right-hand side touch device type.
 *
 * @return `true` if the values are the same; `false` otherwise.
 *
 * @since 4.3.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator==(SDL_TouchDeviceType lhs, DeviceType rhs) noexcept;

/**
 * @brief Indicates whether or not two touch device types aren't the same.
 *
 * @param lhs the left-hand side touch device type.
 * @param rhs the right-hand side touch device type.
 *
 * @return `true` if the values aren't the same; `false` otherwise.
 *
 * @since 4.3.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator!=(DeviceType lhs, SDL_TouchDeviceType rhs) noexcept;

/**
 * @brief Indicates whether or not two touch device types aren't the same.
 *
 * @param lhs the left-hand side touch device type.
 * @param rhs the right-hand side touch device type.
 *
 * @return `true` if the values aren't the same; `false` otherwise.
 *
 * @since 4.3.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator!=(SDL_TouchDeviceType lhs, DeviceType rhs) noexcept;

/**
 * @brief Returns the number of registered touch devices.
 *
 * @return the number of registered touch devices.
 *
 * @since 4.3.0
 */
CENTURION_NODISCARD
CENTURION_API int num_devices() noexcept;

/**
 * @brief Returns the touch device ID associated with the specified index.
 *
 * @param index the index of the desired touch device.
 *
 * @return a `TouchID` value; or `nothing` if there is no such value.
 *
 * @since 4.3.0
 */
CENTURION_NODISCARD
CENTURION_API Optional<TouchID> get_device(int index) noexcept;

/**
 * @brief Returns the type of a touch device.
 *
 * @param id the touch device that will be queried.
 *
 * @return the type of the specified touch device.
 *
 * @since 4.3.0
 */
CENTURION_NODISCARD
CENTURION_API DeviceType type_of(TouchID id) noexcept;

/**
 * @brief Returns the number of active fingers for a given touch device.
 *
 * @param id the touch device that will be queried.
 *
 * @return the amount of active fingers in a touch device.
 *
 * @since 4.3.0
 */
CENTURION_NODISCARD
CENTURION_API int num_fingers(TouchID id) noexcept;

/**
 * @brief Returns the finger associated with the specified touch ID and index.
 *
 * @param id the touch ID of the finger.
 * @param index the index of the finger object.
 *
 * @return an `SDL_Finger` instance; or `nothing` if no such instance could
 * be obtained.
 *
 * @since 4.3.0
 */
CENTURION_NODISCARD
CENTURION_API Optional<SDL_Finger> get_finger(TouchID id, int index) noexcept;

/**
 * @brief Returns the device ID used for mouse events simulated with touch
 * input.
 *
 * @return a device ID.
 *
 * @since 4.3.0
 */
CENTURION_NODISCARD inline constexpr Uint32 touch_mouse_id() noexcept
{
  return SDL_TOUCH_MOUSEID;
}

/**
 * @brief Returns the `TouchID` used by touch events simulated with mouse
 * input.
 *
 * @return a `TouchID` value.
 *
 * @since 4.3.0
 */
CENTURION_NODISCARD inline constexpr TouchID mouse_touch_id() noexcept
{
  return SDL_MOUSE_TOUCHID;
}

}  // namespace touch
}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "touch.cpp"
#endif  // CENTURION_HEADER_ONLY

#endif  // CENTURION_TOUCH_HEADER