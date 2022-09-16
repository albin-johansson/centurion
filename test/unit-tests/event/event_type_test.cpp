/*
 * MIT License
 *
 * Copyright (c) 2019-2022 Albin Johansson
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

#include <gtest/gtest.h>

#include <iostream>  // cout

#include "centurion/event_base.hpp"

using type = cen::event_type;

TEST(EventType, Values)
{
  ASSERT_EQ(SDL_FIRSTEVENT, to_underlying(type::first_event));
  ASSERT_EQ(SDL_LASTEVENT, to_underlying(type::last_event));

#if SDL_VERSION_ATLEAST(2, 0, 18)
  ASSERT_EQ(SDL_POLLSENTINEL, to_underlying(type::poll_sentinel));
#endif  // SDL_VERSION_ATLEAST(2, 0, 18)

  ASSERT_EQ(SDL_QUIT, to_underlying(type::quit));

  ASSERT_EQ(SDL_APP_TERMINATING, to_underlying(type::app_terminating));
  ASSERT_EQ(SDL_APP_LOWMEMORY, to_underlying(type::app_low_memory));
  ASSERT_EQ(SDL_APP_WILLENTERBACKGROUND, to_underlying(type::app_will_enter_background));
  ASSERT_EQ(SDL_APP_DIDENTERBACKGROUND, to_underlying(type::app_did_enter_background));
  ASSERT_EQ(SDL_APP_DIDENTERFOREGROUND, to_underlying(type::app_did_enter_foreground));

#if SDL_VERSION_ATLEAST(2, 0, 14)
  ASSERT_EQ(SDL_DISPLAYEVENT, to_underlying(type::display));
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)
  ASSERT_EQ(SDL_WINDOWEVENT, to_underlying(type::window));
  ASSERT_EQ(SDL_SYSWMEVENT, to_underlying(type::system));

  ASSERT_EQ(SDL_KEYDOWN, to_underlying(type::key_down));
  ASSERT_EQ(SDL_KEYUP, to_underlying(type::key_up));
  ASSERT_EQ(SDL_TEXTEDITING, to_underlying(type::text_editing));
#if SDL_VERSION_ATLEAST(2, 0, 22)
  ASSERT_EQ(SDL_TEXTEDITING_EXT, to_underlying(type::text_editing_ext));
#endif  // SDL_VERSION_ATLEAST(2, 0, 22)
  ASSERT_EQ(SDL_TEXTINPUT, to_underlying(type::text_input));
  ASSERT_EQ(SDL_KEYMAPCHANGED, to_underlying(type::keymap_changed));

  ASSERT_EQ(SDL_MOUSEMOTION, to_underlying(type::mouse_motion));
  ASSERT_EQ(SDL_MOUSEBUTTONDOWN, to_underlying(type::mouse_button_down));
  ASSERT_EQ(SDL_MOUSEBUTTONUP, to_underlying(type::mouse_button_up));
  ASSERT_EQ(SDL_MOUSEWHEEL, to_underlying(type::mouse_wheel));

  ASSERT_EQ(SDL_JOYAXISMOTION, to_underlying(type::joy_axis_motion));
  ASSERT_EQ(SDL_JOYBALLMOTION, to_underlying(type::joy_ball_motion));
  ASSERT_EQ(SDL_JOYHATMOTION, to_underlying(type::joy_hat_motion));
  ASSERT_EQ(SDL_JOYBUTTONDOWN, to_underlying(type::joy_button_down));
  ASSERT_EQ(SDL_JOYBUTTONUP, to_underlying(type::joy_button_up));
  ASSERT_EQ(SDL_JOYDEVICEADDED, to_underlying(type::joy_device_added));
  ASSERT_EQ(SDL_JOYDEVICEREMOVED, to_underlying(type::joy_device_removed));
#if SDL_VERSION_ATLEAST(2, 24, 0)
  ASSERT_EQ(SDL_JOYBATTERYUPDATED, to_underlying(type::joy_battery_updated));
#endif  // SDL_VERSION_ATLEAST(2, 24, 0)

  ASSERT_EQ(SDL_CONTROLLERAXISMOTION, to_underlying(type::controller_axis_motion));
  ASSERT_EQ(SDL_CONTROLLERBUTTONDOWN, to_underlying(type::controller_button_down));
  ASSERT_EQ(SDL_CONTROLLERBUTTONUP, to_underlying(type::controller_button_up));
  ASSERT_EQ(SDL_CONTROLLERDEVICEADDED, to_underlying(type::controller_device_added));
  ASSERT_EQ(SDL_CONTROLLERDEVICEREMOVED, to_underlying(type::controller_device_removed));
  ASSERT_EQ(SDL_CONTROLLERDEVICEREMAPPED, to_underlying(type::controller_device_remapped));

  ASSERT_EQ(SDL_FINGERDOWN, to_underlying(type::finger_down));
  ASSERT_EQ(SDL_FINGERUP, to_underlying(type::finger_up));
  ASSERT_EQ(SDL_FINGERMOTION, to_underlying(type::finger_motion));

  ASSERT_EQ(SDL_DOLLARGESTURE, to_underlying(type::dollar_gesture));
  ASSERT_EQ(SDL_DOLLARRECORD, to_underlying(type::dollar_record));
  ASSERT_EQ(SDL_MULTIGESTURE, to_underlying(type::multi_gesture));

  ASSERT_EQ(SDL_CLIPBOARDUPDATE, to_underlying(type::clipboard_update));

  ASSERT_EQ(SDL_DROPFILE, to_underlying(type::drop_file));
  ASSERT_EQ(SDL_DROPTEXT, to_underlying(type::drop_text));
  ASSERT_EQ(SDL_DROPBEGIN, to_underlying(type::drop_begin));
  ASSERT_EQ(SDL_DROPCOMPLETE, to_underlying(type::drop_complete));

  ASSERT_EQ(SDL_AUDIODEVICEADDED, to_underlying(type::audio_device_added));
  ASSERT_EQ(SDL_AUDIODEVICEREMOVED, to_underlying(type::audio_device_removed));

  ASSERT_EQ(SDL_SENSORUPDATE, to_underlying(type::sensor_update));

  ASSERT_EQ(SDL_RENDER_TARGETS_RESET, to_underlying(type::render_targets_reset));
  ASSERT_EQ(SDL_RENDER_DEVICE_RESET, to_underlying(type::render_device_reset));

  ASSERT_EQ(SDL_USEREVENT, to_underlying(type::user));

#if SDL_VERSION_ATLEAST(2, 0, 14)
  ASSERT_EQ(SDL_LOCALECHANGED, to_underlying(type::locale_changed));

  ASSERT_EQ(SDL_CONTROLLERTOUCHPADDOWN, to_underlying(type::controller_touchpad_down));
  ASSERT_EQ(SDL_CONTROLLERTOUCHPADUP, to_underlying(type::controller_touchpad_up));
  ASSERT_EQ(SDL_CONTROLLERTOUCHPADMOTION, to_underlying(type::controller_touchpad_motion));
  ASSERT_EQ(SDL_CONTROLLERSENSORUPDATE, to_underlying(type::controller_sensor_update));
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)
}

TEST(EventType, ToString)
{
  ASSERT_EQ("first_event", to_string(type::first_event));
  ASSERT_EQ("last_event", to_string(type::last_event));
#if SDL_VERSION_ATLEAST(2, 0, 18)
  ASSERT_EQ("poll_sentinel", to_string(type::poll_sentinel));
#endif  // SDL_VERSION_ATLEAST(2, 0, 18)

  ASSERT_EQ("quit", to_string(type::quit));

  ASSERT_EQ("app_terminating", to_string(type::app_terminating));
  ASSERT_EQ("app_low_memory", to_string(type::app_low_memory));
  ASSERT_EQ("app_will_enter_background", to_string(type::app_will_enter_background));
  ASSERT_EQ("app_did_enter_background", to_string(type::app_did_enter_background));
  ASSERT_EQ("app_did_enter_foreground", to_string(type::app_did_enter_foreground));

#if SDL_VERSION_ATLEAST(2, 0, 14)
  ASSERT_EQ("display", to_string(type::display));
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)
  ASSERT_EQ("window", to_string(type::window));
  ASSERT_EQ("system", to_string(type::system));

  ASSERT_EQ("key_down", to_string(type::key_down));
  ASSERT_EQ("key_up", to_string(type::key_up));
  ASSERT_EQ("text_editing", to_string(type::text_editing));
#if SDL_VERSION_ATLEAST(2, 0, 22)
  ASSERT_EQ("text_editing_ext", to_string(type::text_editing_ext));
#endif  // SDL_VERSION_ATLEAST(2, 0, 22)
  ASSERT_EQ("text_input", to_string(type::text_input));
  ASSERT_EQ("keymap_changed", to_string(type::keymap_changed));

  ASSERT_EQ("mouse_motion", to_string(type::mouse_motion));
  ASSERT_EQ("mouse_button_down", to_string(type::mouse_button_down));
  ASSERT_EQ("mouse_button_up", to_string(type::mouse_button_up));
  ASSERT_EQ("mouse_wheel", to_string(type::mouse_wheel));

  ASSERT_EQ("joy_axis_motion", to_string(type::joy_axis_motion));
  ASSERT_EQ("joy_ball_motion", to_string(type::joy_ball_motion));
  ASSERT_EQ("joy_hat_motion", to_string(type::joy_hat_motion));
  ASSERT_EQ("joy_button_down", to_string(type::joy_button_down));
  ASSERT_EQ("joy_button_up", to_string(type::joy_button_up));
  ASSERT_EQ("joy_device_added", to_string(type::joy_device_added));
  ASSERT_EQ("joy_device_removed", to_string(type::joy_device_removed));
#if SDL_VERSION_ATLEAST(2, 24, 0)
  ASSERT_EQ("joy_battery_updated", to_string(type::joy_battery_updated));
#endif  // SDL_VERSION_ATLEAST(2, 24, 0)

  ASSERT_EQ("controller_axis_motion", to_string(type::controller_axis_motion));
  ASSERT_EQ("controller_button_down", to_string(type::controller_button_down));
  ASSERT_EQ("controller_button_up", to_string(type::controller_button_up));
  ASSERT_EQ("controller_device_added", to_string(type::controller_device_added));
  ASSERT_EQ("controller_device_removed", to_string(type::controller_device_removed));
  ASSERT_EQ("controller_device_remapped", to_string(type::controller_device_remapped));

  ASSERT_EQ("finger_down", to_string(type::finger_down));
  ASSERT_EQ("finger_up", to_string(type::finger_up));
  ASSERT_EQ("finger_motion", to_string(type::finger_motion));

  ASSERT_EQ("dollar_gesture", to_string(type::dollar_gesture));
  ASSERT_EQ("dollar_record", to_string(type::dollar_record));
  ASSERT_EQ("multi_gesture", to_string(type::multi_gesture));

  ASSERT_EQ("clipboard_update", to_string(type::clipboard_update));

  ASSERT_EQ("drop_file", to_string(type::drop_file));
  ASSERT_EQ("drop_text", to_string(type::drop_text));
  ASSERT_EQ("drop_begin", to_string(type::drop_begin));
  ASSERT_EQ("drop_complete", to_string(type::drop_complete));

  ASSERT_EQ("audio_device_added", to_string(type::audio_device_added));
  ASSERT_EQ("audio_device_removed", to_string(type::audio_device_removed));

  ASSERT_EQ("sensor_update", to_string(type::sensor_update));

  ASSERT_EQ("render_targets_reset", to_string(type::render_targets_reset));
  ASSERT_EQ("render_device_reset", to_string(type::render_device_reset));

  ASSERT_EQ("user", to_string(type::user));
  ASSERT_EQ("user", to_string(static_cast<type>(SDL_USEREVENT + 1)));
  ASSERT_EQ("user", to_string(static_cast<type>(SDL_LASTEVENT - 1)));

#if SDL_VERSION_ATLEAST(2, 0, 14)
  ASSERT_EQ("locale_changed", to_string(type::locale_changed));

  ASSERT_EQ("controller_touchpad_down", to_string(type::controller_touchpad_down));
  ASSERT_EQ("controller_touchpad_up", to_string(type::controller_touchpad_up));
  ASSERT_EQ("controller_touchpad_motion", to_string(type::controller_touchpad_motion));
  ASSERT_EQ("controller_sensor_update", to_string(type::controller_sensor_update));
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  std::cout << "event_type::app_low_memory == " << type::app_low_memory << '\n';
}
