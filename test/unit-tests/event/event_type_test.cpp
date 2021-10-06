#include <gtest/gtest.h>

#include <iostream>  // clog

#include "events/event.hpp"

using type = cen::event_type;

TEST(EventType, Values)
{
  ASSERT_EQ(type::quit, SDL_QUIT);

  ASSERT_EQ(type::app_terminating, SDL_APP_TERMINATING);
  ASSERT_EQ(type::app_low_memory, SDL_APP_LOWMEMORY);
  ASSERT_EQ(type::app_will_enter_background, SDL_APP_WILLENTERBACKGROUND);
  ASSERT_EQ(type::app_did_enter_background, SDL_APP_DIDENTERBACKGROUND);
  ASSERT_EQ(type::app_did_enter_foreground, SDL_APP_DIDENTERFOREGROUND);

#if SDL_VERSION_ATLEAST(2, 0, 14)
  ASSERT_EQ(type::locale_changed, SDL_LOCALECHANGED);
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  ASSERT_EQ(type::display, SDL_DISPLAYEVENT);

  ASSERT_EQ(type::window, SDL_WINDOWEVENT);
  ASSERT_EQ(type::system, SDL_SYSWMEVENT);

  ASSERT_EQ(type::key_down, SDL_KEYDOWN);
  ASSERT_EQ(type::key_up, SDL_KEYUP);
  ASSERT_EQ(type::text_editing, SDL_TEXTEDITING);
  ASSERT_EQ(type::text_input, SDL_TEXTINPUT);
  ASSERT_EQ(type::keymap_changed, SDL_KEYMAPCHANGED);

  ASSERT_EQ(type::mouse_motion, SDL_MOUSEMOTION);
  ASSERT_EQ(type::mouse_button_down, SDL_MOUSEBUTTONDOWN);
  ASSERT_EQ(type::mouse_button_up, SDL_MOUSEBUTTONUP);
  ASSERT_EQ(type::mouse_wheel, SDL_MOUSEWHEEL);

  ASSERT_EQ(type::joystick_axis_motion, SDL_JOYAXISMOTION);
  ASSERT_EQ(type::joystick_ball_motion, SDL_JOYBALLMOTION);
  ASSERT_EQ(type::joystick_hat_motion, SDL_JOYHATMOTION);
  ASSERT_EQ(type::joystick_button_down, SDL_JOYBUTTONDOWN);
  ASSERT_EQ(type::joystick_button_up, SDL_JOYBUTTONUP);
  ASSERT_EQ(type::joystick_device_added, SDL_JOYDEVICEADDED);
  ASSERT_EQ(type::joystick_device_removed, SDL_JOYDEVICEREMOVED);

  ASSERT_EQ(type::controller_axis_motion, SDL_CONTROLLERAXISMOTION);
  ASSERT_EQ(type::controller_button_down, SDL_CONTROLLERBUTTONDOWN);
  ASSERT_EQ(type::controller_button_up, SDL_CONTROLLERBUTTONUP);
  ASSERT_EQ(type::controller_device_added, SDL_CONTROLLERDEVICEADDED);
  ASSERT_EQ(type::controller_device_removed, SDL_CONTROLLERDEVICEREMOVED);
  ASSERT_EQ(type::controller_device_remapped, SDL_CONTROLLERDEVICEREMAPPED);

#if SDL_VERSION_ATLEAST(2, 0, 14)
  ASSERT_EQ(type::controller_touchpad_down, SDL_CONTROLLERTOUCHPADDOWN);
  ASSERT_EQ(type::controller_touchpad_up, SDL_CONTROLLERTOUCHPADUP);
  ASSERT_EQ(type::controller_touchpad_motion, SDL_CONTROLLERTOUCHPADMOTION);
  ASSERT_EQ(type::controller_sensor_update, SDL_CONTROLLERSENSORUPDATE);
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  ASSERT_EQ(type::touch_down, SDL_FINGERDOWN);
  ASSERT_EQ(type::touch_up, SDL_FINGERUP);
  ASSERT_EQ(type::touch_motion, SDL_FINGERMOTION);

  ASSERT_EQ(type::dollar_gesture, SDL_DOLLARGESTURE);
  ASSERT_EQ(type::dollar_record, SDL_DOLLARRECORD);
  ASSERT_EQ(type::multi_gesture, SDL_MULTIGESTURE);

  ASSERT_EQ(type::clipboard_update, SDL_CLIPBOARDUPDATE);

  ASSERT_EQ(type::drop_file, SDL_DROPFILE);
  ASSERT_EQ(type::drop_text, SDL_DROPTEXT);
  ASSERT_EQ(type::drop_begin, SDL_DROPBEGIN);
  ASSERT_EQ(type::drop_complete, SDL_DROPCOMPLETE);

  ASSERT_EQ(type::audio_device_added, SDL_AUDIODEVICEADDED);
  ASSERT_EQ(type::audio_device_removed, SDL_AUDIODEVICEREMOVED);

  ASSERT_EQ(type::sensor_update, SDL_SENSORUPDATE);

  ASSERT_EQ(type::render_targets_reset, SDL_RENDER_TARGETS_RESET);
  ASSERT_EQ(type::render_device_reset, SDL_RENDER_DEVICE_RESET);

  ASSERT_EQ(type::user, SDL_USEREVENT);

  ASSERT_NE(type::dollar_gesture, SDL_RENDER_DEVICE_RESET);
  ASSERT_NE(SDL_MOUSEMOTION, type::controller_device_removed);
}

TEST(EventType, ToString)
{
  ASSERT_EQ("quit", cen::to_string(type::quit));

  ASSERT_EQ("app_terminating", cen::to_string(type::app_terminating));
  ASSERT_EQ("app_low_memory", cen::to_string(type::app_low_memory));
  ASSERT_EQ("app_will_enter_background", cen::to_string(type::app_will_enter_background));
  ASSERT_EQ("app_did_enter_background", cen::to_string(type::app_did_enter_background));
  ASSERT_EQ("app_did_enter_foreground", cen::to_string(type::app_did_enter_foreground));

#if SDL_VERSION_ATLEAST(2, 0, 14)
  ASSERT_EQ("locale_changed", cen::to_string(type::locale_changed));
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  ASSERT_EQ("display", cen::to_string(type::display));
  ASSERT_EQ("window", cen::to_string(type::window));
  ASSERT_EQ("system", cen::to_string(type::system));

  ASSERT_EQ("key_down", cen::to_string(type::key_down));
  ASSERT_EQ("key_up", cen::to_string(type::key_up));
  ASSERT_EQ("text_editing", cen::to_string(type::text_editing));
  ASSERT_EQ("text_input", cen::to_string(type::text_input));
  ASSERT_EQ("keymap_changed", cen::to_string(type::keymap_changed));

  ASSERT_EQ("mouse_motion", cen::to_string(type::mouse_motion));
  ASSERT_EQ("mouse_button_down", cen::to_string(type::mouse_button_down));
  ASSERT_EQ("mouse_button_up", cen::to_string(type::mouse_button_up));
  ASSERT_EQ("mouse_wheel", cen::to_string(type::mouse_wheel));

  ASSERT_EQ("joystick_axis_motion", cen::to_string(type::joystick_axis_motion));
  ASSERT_EQ("joystick_ball_motion", cen::to_string(type::joystick_ball_motion));
  ASSERT_EQ("joystick_hat_motion", cen::to_string(type::joystick_hat_motion));
  ASSERT_EQ("joystick_button_down", cen::to_string(type::joystick_button_down));
  ASSERT_EQ("joystick_button_up", cen::to_string(type::joystick_button_up));
  ASSERT_EQ("joystick_device_added", cen::to_string(type::joystick_device_added));
  ASSERT_EQ("joystick_device_removed", cen::to_string(type::joystick_device_removed));

  ASSERT_EQ("controller_axis_motion", cen::to_string(type::controller_axis_motion));
  ASSERT_EQ("controller_button_down", cen::to_string(type::controller_button_down));
  ASSERT_EQ("controller_button_up", cen::to_string(type::controller_button_up));
  ASSERT_EQ("controller_device_added", cen::to_string(type::controller_device_added));
  ASSERT_EQ("controller_device_removed", cen::to_string(type::controller_device_removed));
  ASSERT_EQ("controller_device_remapped", cen::to_string(type::controller_device_remapped));

#if SDL_VERSION_ATLEAST(2, 0, 14)
  ASSERT_EQ("controller_touchpad_down", to_string(type::controller_touchpad_down));
  ASSERT_EQ("controller_touchpad_up", to_string(type::controller_touchpad_up));
  ASSERT_EQ("controller_touchpad_motion", to_string(type::controller_touchpad_motion));
  ASSERT_EQ("controller_sensor_update", to_string(type::controller_sensor_update));
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  ASSERT_EQ("touch_down", cen::to_string(type::touch_down));
  ASSERT_EQ("touch_up", cen::to_string(type::touch_up));
  ASSERT_EQ("touch_motion", cen::to_string(type::touch_motion));

  ASSERT_EQ("dollar_gesture", cen::to_string(type::dollar_gesture));
  ASSERT_EQ("dollar_record", cen::to_string(type::dollar_record));
  ASSERT_EQ("multi_gesture", cen::to_string(type::multi_gesture));

  ASSERT_EQ("clipboard_update", cen::to_string(type::clipboard_update));

  ASSERT_EQ("drop_file", cen::to_string(type::drop_file));
  ASSERT_EQ("drop_text", cen::to_string(type::drop_text));
  ASSERT_EQ("drop_begin", cen::to_string(type::drop_begin));
  ASSERT_EQ("drop_complete", cen::to_string(type::drop_complete));

  ASSERT_EQ("audio_device_added", cen::to_string(type::audio_device_added));
  ASSERT_EQ("audio_device_removed", cen::to_string(type::audio_device_removed));

  ASSERT_EQ("sensor_update", cen::to_string(type::sensor_update));

  ASSERT_EQ("render_targets_reset", cen::to_string(type::render_targets_reset));
  ASSERT_EQ("render_device_reset", cen::to_string(type::render_device_reset));

  ASSERT_EQ("user", cen::to_string(type::user));

  std::clog << "Event type example: " << type::app_low_memory << '\n';
}
