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

#ifndef CENTURION_EVENT_TYPE_HEADER
#define CENTURION_EVENT_TYPE_HEADER

#include <SDL.h>

#include "centurion_cfg.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/// \addtogroup event
/// \{

/**
 * \enum event_type
 *
 * \brief Mirrors the `SDL_EventType` enum.
 *
 * \see `SDL_EventType`
 *
 * \since 3.1.0
 *
 * \headerfile event_type.hpp
 */
enum class event_type
{
  quit = SDL_QUIT,

  app_terminating = SDL_APP_TERMINATING,
  app_low_memory = SDL_APP_LOWMEMORY,
  app_will_enter_background = SDL_APP_WILLENTERBACKGROUND,
  app_did_enter_background = SDL_APP_DIDENTERBACKGROUND,
  app_did_enter_foreground = SDL_APP_DIDENTERFOREGROUND,

  display = SDL_DISPLAYEVENT,

  window = SDL_WINDOWEVENT,
  system = SDL_SYSWMEVENT,

  key_down = SDL_KEYDOWN,
  key_up = SDL_KEYUP,
  text_editing = SDL_TEXTEDITING,
  text_input = SDL_TEXTINPUT,
  keymap_changed = SDL_KEYMAPCHANGED,

  mouse_motion = SDL_MOUSEMOTION,
  mouse_button_down = SDL_MOUSEBUTTONDOWN,
  mouse_button_up = SDL_MOUSEBUTTONUP,
  mouse_wheel = SDL_MOUSEWHEEL,

  joystick_axis_motion = SDL_JOYAXISMOTION,
  joystick_ball_motion = SDL_JOYBALLMOTION,
  joystick_hat_motion = SDL_JOYHATMOTION,
  joystick_button_down = SDL_JOYBUTTONDOWN,
  joystick_button_up = SDL_JOYBUTTONUP,
  joystick_device_added = SDL_JOYDEVICEADDED,
  joystick_device_removed = SDL_JOYDEVICEREMOVED,

  controller_axis_motion = SDL_CONTROLLERAXISMOTION,
  controller_button_down = SDL_CONTROLLERBUTTONDOWN,
  controller_button_up = SDL_CONTROLLERBUTTONUP,
  controller_device_added = SDL_CONTROLLERDEVICEADDED,
  controller_device_removed = SDL_CONTROLLERDEVICEREMOVED,
  controller_device_remapped = SDL_CONTROLLERDEVICEREMAPPED,

  touch_down = SDL_FINGERDOWN,
  touch_up = SDL_FINGERUP,
  touch_motion = SDL_FINGERMOTION,

  dollar_gesture = SDL_DOLLARGESTURE,
  dollar_record = SDL_DOLLARRECORD,
  multi_gesture = SDL_MULTIGESTURE,

  clipboard_update = SDL_CLIPBOARDUPDATE,

  drop_file = SDL_DROPFILE,
  drop_text = SDL_DROPTEXT,
  drop_begin = SDL_DROPBEGIN,
  drop_complete = SDL_DROPCOMPLETE,

  audio_device_added = SDL_AUDIODEVICEADDED,
  audio_device_removed = SDL_AUDIODEVICEREMOVED,

  sensor_update = SDL_SENSORUPDATE,

  render_targets_reset = SDL_RENDER_TARGETS_RESET,
  render_device_reset = SDL_RENDER_DEVICE_RESET,

  user = SDL_USEREVENT
};

/**
 * \brief Indicates whether or not two event type values are the same.
 *
 * \param lhs the left-hand side event type value
 * \param rhs the right-hand side event type value
 *
 * \return `true` if the values are the same; `false` otherwise.
 *
 * \since 3.1.0
 */
[[nodiscard]] constexpr auto operator==(const event_type lhs,
                                        const SDL_EventType rhs) noexcept
    -> bool
{
  return static_cast<SDL_EventType>(lhs) == rhs;
}

/**
 * \copydoc operator==(const event_type, const SDL_EventType)
 */
[[nodiscard]] constexpr auto operator==(const SDL_EventType lhs,
                                        const event_type rhs) noexcept -> bool
{
  return rhs == lhs;
}

/**
 * \brief Indicates whether or not two event type values aren't the same.
 *
 * \param lhs the left-hand side event type value
 * \param rhs the right-hand side event type value
 *
 * \return `true` if the values aren't the same; `false` otherwise.
 *
 * \since 3.1.0
 */
[[nodiscard]] constexpr auto operator!=(const event_type lhs,
                                        const SDL_EventType rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/**
 * \copydoc operator!=(const event_type, const SDL_EventType)
 */
[[nodiscard]] constexpr auto operator!=(const SDL_EventType lhs,
                                        const event_type rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \}

}  // namespace cen

#endif  // CENTURION_EVENT_TYPE_HEADER