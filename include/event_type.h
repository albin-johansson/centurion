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

#ifndef CENTURION_EVENT_TYPE_HEADER
#define CENTURION_EVENT_TYPE_HEADER

#include <SDL_events.h>

#include "centurion_api.h"

namespace centurion {
namespace event {

/**
 * The EventType enum class mirrors the SDL_EventType enum.
 *
 * @see SDL_EventType
 * @since 3.1.0
 */
enum class EventType {
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
 * Indicates whether or not two event type values are the same.
 *
 * @param lhs the left-hand side Centurion value.
 * @param rhs the right-hand side SDL value.
 * @return true if the values represent the same event type; false otherwise.
 * @since 3.1.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator==(EventType lhs, SDL_EventType rhs) noexcept;

/**
 * Indicates whether or not two event type values are the same.
 *
 * @param lhs the left-hand side SDL value.
 * @param rhs the right-hand side Centurion value.
 * @return true if the values represent the same event type; false otherwise.
 * @since 3.1.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator==(SDL_EventType lhs, EventType rhs) noexcept;

/**
 * Indicates whether or not two event type values aren't the same.
 *
 * @param lhs the left-hand side Centurion value.
 * @param rhs the right-hand side SDL value.
 * @return true if the values don't represent the same event type; false
 * otherwise.
 * @since 3.1.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator!=(EventType lhs, SDL_EventType rhs) noexcept;

/**
 * Indicates whether or not two event type values aren't the same.
 *
 * @param lhs the left-hand side SDL value.
 * @param rhs the right-hand side Centurion value.
 * @return true if the values don't represent the same event type; false
 * otherwise.
 * @since 3.1.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator!=(SDL_EventType lhs, EventType rhs) noexcept;

}  // namespace event
}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "event_type.cpp"
#endif  // CENTURION_HEADER_ONLY

#endif  // CENTURION_EVENT_TYPE_HEADER