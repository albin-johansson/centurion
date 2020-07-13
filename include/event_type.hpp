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
 * @file event_type.hpp
 *
 * @brief Provides the `EventType` enum.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

#ifndef CENTURION_EVENT_TYPE_HEADER
#define CENTURION_EVENT_TYPE_HEADER

#include <SDL_events.h>

#include "centurion_api.hpp"

namespace centurion {

/**
 * @enum EventType
 *
 * @brief Mirrors the `SDL_EventType` enum.
 *
 * @see `SDL_EventType`
 *
 * @since 3.1.0
 *
 * @headerfile event_type.hpp
 */
enum class event_type {
  Quit = SDL_QUIT,

  AppTerminating = SDL_APP_TERMINATING,
  AppLowMemory = SDL_APP_LOWMEMORY,
  AppWillEnterBackground = SDL_APP_WILLENTERBACKGROUND,
  AppDidEnterBackground = SDL_APP_DIDENTERBACKGROUND,
  AppDidEnterForeground = SDL_APP_DIDENTERFOREGROUND,

  Display = SDL_DISPLAYEVENT,

  Window = SDL_WINDOWEVENT,
  System = SDL_SYSWMEVENT,

  KeyDown = SDL_KEYDOWN,
  KeyUp = SDL_KEYUP,
  TextEditing = SDL_TEXTEDITING,
  TextInput = SDL_TEXTINPUT,
  KeymapChanged = SDL_KEYMAPCHANGED,

  MouseMotion = SDL_MOUSEMOTION,
  MouseButtonDown = SDL_MOUSEBUTTONDOWN,
  MouseButtonUp = SDL_MOUSEBUTTONUP,
  MouseWheel = SDL_MOUSEWHEEL,

  JoystickAxisMotion = SDL_JOYAXISMOTION,
  JoystickBallMotion = SDL_JOYBALLMOTION,
  JoystickHatMotion = SDL_JOYHATMOTION,
  JoystickButtonDown = SDL_JOYBUTTONDOWN,
  JoystickButtonUp = SDL_JOYBUTTONUP,
  JoystickDeviceAdded = SDL_JOYDEVICEADDED,
  JoystickDeviceRemoved = SDL_JOYDEVICEREMOVED,

  ControllerAxisMotion = SDL_CONTROLLERAXISMOTION,
  ControllerButtonDown = SDL_CONTROLLERBUTTONDOWN,
  ControllerButtonUp = SDL_CONTROLLERBUTTONUP,
  ControllerDeviceAdded = SDL_CONTROLLERDEVICEADDED,
  ControllerDeviceRemoved = SDL_CONTROLLERDEVICEREMOVED,
  ControllerDeviceRemapped = SDL_CONTROLLERDEVICEREMAPPED,

  TouchDown = SDL_FINGERDOWN,
  TouchUp = SDL_FINGERUP,
  TouchMotion = SDL_FINGERMOTION,

  DollarGesture = SDL_DOLLARGESTURE,
  DollarRecord = SDL_DOLLARRECORD,
  MultiGesture = SDL_MULTIGESTURE,

  ClipboardUpdate = SDL_CLIPBOARDUPDATE,

  DropFile = SDL_DROPFILE,
  DropText = SDL_DROPTEXT,
  DropBegin = SDL_DROPBEGIN,
  DropComplete = SDL_DROPCOMPLETE,

  AudioDeviceAdded = SDL_AUDIODEVICEADDED,
  AudioDeviceRemoved = SDL_AUDIODEVICEREMOVED,

  SensorUpdate = SDL_SENSORUPDATE,

  RenderTargetsReset = SDL_RENDER_TARGETS_RESET,
  RenderDeviceReset = SDL_RENDER_DEVICE_RESET,

  User = SDL_USEREVENT
};

/**
 * @brief Indicates whether or not two event type values are the same.
 *
 * @param lhs the left-hand side event type value
 * @param rhs the right-hand side event type value
 *
 * @return `true` if the values are the same; `false` otherwise.
 *
 * @since 3.1.0
 */
[[nodiscard]] inline constexpr auto operator==(event_type lhs,
                                               SDL_EventType rhs) noexcept
    -> bool
{
  return static_cast<SDL_EventType>(lhs) == rhs;
}

/**
 * @copydoc operator==(EventType, SDL_EventType)
 */
[[nodiscard]] inline constexpr auto operator==(SDL_EventType lhs,
                                               event_type rhs) noexcept -> bool
{
  return rhs == lhs;
}

/**
 * @brief Indicates whether or not two event type values aren't the same.
 *
 * @param lhs the left-hand side event type value
 * @param rhs the right-hand side event type value
 *
 * @return `true` if the values aren't the same; `false` otherwise.
 *
 * @since 3.1.0
 */
[[nodiscard]] inline constexpr auto operator!=(event_type lhs,
                                               SDL_EventType rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/**
 * @copydoc operator!=(EventType, SDL_EventType)
 */
[[nodiscard]] inline constexpr auto operator!=(SDL_EventType lhs,
                                               event_type rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

}  // namespace centurion

#endif  // CENTURION_EVENT_TYPE_HEADER