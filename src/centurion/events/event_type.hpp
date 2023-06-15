/*
 * MIT License
 *
 * Copyright (c) 2019-2023 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef CENTURION_EVENTS_EVENT_TYPE_HPP_
#define CENTURION_EVENTS_EVENT_TYPE_HPP_

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view
#include <utility>      // move

#include "../common/errors.hpp"
#include "../common/primitives.hpp"
#include "../common/utils.hpp"

namespace cen {

enum class event_type : uint32 {
  first_event = SDL_FIRSTEVENT,
  last_event = SDL_LASTEVENT,

#if SDL_VERSION_ATLEAST(2, 0, 18)
  poll_sentinel = SDL_POLLSENTINEL,
#endif  // SDL_VERSION_ATLEAST(2, 0, 18)

  quit = SDL_QUIT,

  app_terminating = SDL_APP_TERMINATING,
  app_low_memory = SDL_APP_LOWMEMORY,
  app_will_enter_background = SDL_APP_WILLENTERBACKGROUND,
  app_did_enter_background = SDL_APP_DIDENTERBACKGROUND,
  app_will_enter_foreground = SDL_APP_WILLENTERFOREGROUND,
  app_did_enter_foreground = SDL_APP_DIDENTERFOREGROUND,

#if SDL_VERSION_ATLEAST(2, 0, 14)
  locale_changed = SDL_LOCALECHANGED,
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

#if SDL_VERSION_ATLEAST(2, 0, 14)
  display = SDL_DISPLAYEVENT,
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)
  window = SDL_WINDOWEVENT,
  system = SDL_SYSWMEVENT,

  key_down = SDL_KEYDOWN,
  key_up = SDL_KEYUP,
  text_editing = SDL_TEXTEDITING,
#if SDL_VERSION_ATLEAST(2, 0, 22)
  text_editing_ext = SDL_TEXTEDITING_EXT,
#endif  // SDL_VERSION_ATLEAST(2, 0, 22)
  text_input = SDL_TEXTINPUT,
  keymap_changed = SDL_KEYMAPCHANGED,

  mouse_motion = SDL_MOUSEMOTION,
  mouse_button_down = SDL_MOUSEBUTTONDOWN,
  mouse_button_up = SDL_MOUSEBUTTONUP,
  mouse_wheel = SDL_MOUSEWHEEL,

  joy_axis_motion = SDL_JOYAXISMOTION,
  joy_ball_motion = SDL_JOYBALLMOTION,
  joy_hat_motion = SDL_JOYHATMOTION,
  joy_button_down = SDL_JOYBUTTONDOWN,
  joy_button_up = SDL_JOYBUTTONUP,
  joy_device_added = SDL_JOYDEVICEADDED,
  joy_device_removed = SDL_JOYDEVICEREMOVED,
#if SDL_VERSION_ATLEAST(2, 24, 0)
  joy_battery_updated = SDL_JOYBATTERYUPDATED,
#endif  // SDL_VERSION_ATLEAST(2, 24, 0)

  controller_axis_motion = SDL_CONTROLLERAXISMOTION,
  controller_button_down = SDL_CONTROLLERBUTTONDOWN,
  controller_button_up = SDL_CONTROLLERBUTTONUP,
  controller_device_added = SDL_CONTROLLERDEVICEADDED,
  controller_device_removed = SDL_CONTROLLERDEVICEREMOVED,
  controller_device_remapped = SDL_CONTROLLERDEVICEREMAPPED,

#if SDL_VERSION_ATLEAST(2, 0, 14)
  controller_touchpad_down = SDL_CONTROLLERTOUCHPADDOWN,
  controller_touchpad_motion = SDL_CONTROLLERTOUCHPADMOTION,
  controller_touchpad_up = SDL_CONTROLLERTOUCHPADUP,
  controller_sensor_update = SDL_CONTROLLERSENSORUPDATE,
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  finger_down = SDL_FINGERDOWN,
  finger_up = SDL_FINGERUP,
  finger_motion = SDL_FINGERMOTION,

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

[[nodiscard]] constexpr auto is_user_event(const event_type type) noexcept -> bool
{
  const auto raw = to_underlying(type);
  return raw >= SDL_USEREVENT && raw < SDL_LASTEVENT;
}

[[nodiscard]] constexpr auto to_string(const event_type type) -> std::string_view
{
  if (is_user_event(type)) {
    return "user";
  }

  switch (type) {
    case event_type::first_event:
      return "first_event";

    case event_type::last_event:
      return "last_event";

#if SDL_VERSION_ATLEAST(2, 0, 18)

    case event_type::poll_sentinel:
      return "poll_sentinel";

#endif  // SDL_VERSION_ATLEAST(2, 0, 18)

    case event_type::quit:
      return "quit";

    case event_type::app_terminating:
      return "app_terminating";

    case event_type::app_low_memory:
      return "app_low_memory";

    case event_type::app_will_enter_background:
      return "app_will_enter_background";

    case event_type::app_did_enter_background:
      return "app_did_enter_background";

    case event_type::app_will_enter_foreground:
      return "app_will_enter_foreground";

    case event_type::app_did_enter_foreground:
      return "app_did_enter_foreground";

#if SDL_VERSION_ATLEAST(2, 0, 14)
    case event_type::locale_changed:
      return "locale_changed";
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

#if SDL_VERSION_ATLEAST(2, 0, 14)

    case event_type::display:
      return "display";

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

    case event_type::window:
      return "window";

    case event_type::system:
      return "system";

    case event_type::key_down:
      return "key_down";

    case event_type::key_up:
      return "key_up";

    case event_type::text_editing:
      return "text_editing";

#if SDL_VERSION_ATLEAST(2, 0, 22)

    case event_type::text_editing_ext:
      return "text_editing_ext";

#endif  // SDL_VERSION_ATLEAST(2, 0, 22)

    case event_type::text_input:
      return "text_input";

    case event_type::keymap_changed:
      return "keymap_changed";

    case event_type::mouse_motion:
      return "mouse_motion";

    case event_type::mouse_button_down:
      return "mouse_button_down";

    case event_type::mouse_button_up:
      return "mouse_button_up";

    case event_type::mouse_wheel:
      return "mouse_wheel";

    case event_type::joy_axis_motion:
      return "joy_axis_motion";

    case event_type::joy_ball_motion:
      return "joy_ball_motion";

    case event_type::joy_hat_motion:
      return "joy_hat_motion";

    case event_type::joy_button_down:
      return "joy_button_down";

    case event_type::joy_button_up:
      return "joy_button_up";

    case event_type::joy_device_added:
      return "joy_device_added";

    case event_type::joy_device_removed:
      return "joy_device_removed";

#if SDL_VERSION_ATLEAST(2, 24, 0)

    case event_type::joy_battery_updated:
      return "joy_battery_updated";

#endif  // SDL_VERSION_ATLEAST(2, 24, 0)

    case event_type::controller_axis_motion:
      return "controller_axis_motion";

    case event_type::controller_button_down:
      return "controller_button_down";

    case event_type::controller_button_up:
      return "controller_button_up";

    case event_type::controller_device_added:
      return "controller_device_added";

    case event_type::controller_device_removed:
      return "controller_device_removed";

    case event_type::controller_device_remapped:
      return "controller_device_remapped";

#if SDL_VERSION_ATLEAST(2, 0, 14)
    case event_type::controller_touchpad_down:
      return "controller_touchpad_down";

    case event_type::controller_touchpad_up:
      return "controller_touchpad_up";

    case event_type::controller_touchpad_motion:
      return "controller_touchpad_motion";

    case event_type::controller_sensor_update:
      return "controller_sensor_update";
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

    case event_type::finger_down:
      return "finger_down";

    case event_type::finger_up:
      return "finger_up";

    case event_type::finger_motion:
      return "finger_motion";

    case event_type::dollar_gesture:
      return "dollar_gesture";

    case event_type::dollar_record:
      return "dollar_record";

    case event_type::multi_gesture:
      return "multi_gesture";

    case event_type::clipboard_update:
      return "clipboard_update";

    case event_type::drop_file:
      return "drop_file";

    case event_type::drop_text:
      return "drop_text";

    case event_type::drop_begin:
      return "drop_begin";

    case event_type::drop_complete:
      return "drop_complete";

    case event_type::audio_device_added:
      return "audio_device_added";

    case event_type::audio_device_removed:
      return "audio_device_removed";

    case event_type::sensor_update:
      return "sensor_update";

    case event_type::render_targets_reset:
      return "render_targets_reset";

    case event_type::render_device_reset:
      return "render_device_reset";

    case event_type::user:
      return "user";

    default:
      throw exception {"Did not recognize event type!"};
  }
}

inline auto operator<<(std::ostream& stream, const event_type type) -> std::ostream&
{
  return stream << to_string(type);
}

}  // namespace cen

#endif
