#include <gtest/gtest.h>

#include "centurion/event.hpp"

namespace {

template <typename Event>
void check(const SDL_EventType type)
{
  SDL_Event event{};
  event.type = type;

  cen::event_handler::flush_all();
  SDL_PushEvent(&event);

  cen::event_handler handler;
  ASSERT_TRUE(handler.poll());

  const auto strong = static_cast<cen::event_type>(type);

  ASSERT_EQ(type, handler.raw_type());
  ASSERT_EQ(strong, handler.type());

  ASSERT_TRUE(handler.is(strong));
  ASSERT_TRUE(handler.is<Event>());
}

}  // namespace

#if SDL_VERSION_ATLEAST(2, 0, 14)

TEST(EventHandlerTypeChecks, DisplayEvent)
{
  check<cen::display_event>(SDL_DISPLAYEVENT);
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

TEST(EventHandlerTypeChecks, WindowEvent)
{
  check<cen::window_event>(SDL_WINDOWEVENT);
}

TEST(EventHandlerTypeChecks, KeyboardEvent)
{
  check<cen::keyboard_event>(SDL_KEYDOWN);
  check<cen::keyboard_event>(SDL_KEYUP);
}

TEST(EventHandlerTypeChecks, TextEditingEvent)
{
  check<cen::text_editing_event>(SDL_TEXTEDITING);
}

TEST(EventHandlerTypeChecks, TextInputEvent)
{
  check<cen::text_input_event>(SDL_TEXTINPUT);
}

TEST(EventHandlerTypeChecks, MouseMotionEvent)
{
  check<cen::mouse_motion_event>(SDL_MOUSEMOTION);
}

TEST(EventHandlerTypeChecks, MouseButtonEvent)
{
  check<cen::mouse_button_event>(SDL_MOUSEBUTTONDOWN);
  check<cen::mouse_button_event>(SDL_MOUSEBUTTONUP);
}

TEST(EventHandlerTypeChecks, MouseWheelEvent)
{
  check<cen::mouse_wheel_event>(SDL_MOUSEWHEEL);
}

TEST(EventHandlerTypeChecks, JoyAxisEvent)
{
  check<cen::joy_axis_event>(SDL_JOYAXISMOTION);
}

TEST(EventHandlerTypeChecks, JoyBallEvent)
{
  check<cen::joy_ball_event>(SDL_JOYBALLMOTION);
}

TEST(EventHandlerTypeChecks, JoyHatEvent)
{
  check<cen::joy_hat_event>(SDL_JOYHATMOTION);
}

TEST(EventHandlerTypeChecks, JoyButtonEvent)
{
  check<cen::joy_button_event>(SDL_JOYBUTTONDOWN);
  check<cen::joy_button_event>(SDL_JOYBUTTONUP);
}

TEST(EventHandlerTypeChecks, JoyDeviceEvent)
{
  check<cen::joy_device_event>(SDL_JOYDEVICEADDED);
  check<cen::joy_device_event>(SDL_JOYDEVICEREMOVED);
}

TEST(EventHandlerTypeChecks, ControllerAxisEvent)
{
  check<cen::controller_axis_event>(SDL_CONTROLLERAXISMOTION);
}

TEST(EventHandlerTypeChecks, ControllerButtonEvent)
{
  check<cen::controller_button_event>(SDL_CONTROLLERBUTTONDOWN);
  check<cen::controller_button_event>(SDL_CONTROLLERBUTTONUP);
}

TEST(EventHandlerTypeChecks, ControllerDeviceEvent)
{
  check<cen::controller_device_event>(SDL_CONTROLLERDEVICEADDED);
  check<cen::controller_device_event>(SDL_CONTROLLERDEVICEREMAPPED);
  check<cen::controller_device_event>(SDL_CONTROLLERDEVICEREMOVED);
}

#if SDL_VERSION_ATLEAST(2, 0, 14)

TEST(EventHandlerTypeChecks, ControllerTouchpadEvent)
{
  check<cen::controller_touchpad_event>(SDL_CONTROLLERTOUCHPADDOWN);
  check<cen::controller_touchpad_event>(SDL_CONTROLLERTOUCHPADMOTION);
  check<cen::controller_touchpad_event>(SDL_CONTROLLERTOUCHPADUP);
}

TEST(EventHandlerTypeChecks, ControllerSensorEvent)
{
  check<cen::controller_sensor_event>(SDL_CONTROLLERSENSORUPDATE);
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

TEST(EventHandlerTypeChecks, AudioDeviceEvent)
{
  check<cen::audio_device_event>(SDL_AUDIODEVICEADDED);
  check<cen::audio_device_event>(SDL_AUDIODEVICEREMOVED);
}

TEST(EventHandlerTypeChecks, TouchFingerEvent)
{
  check<cen::touch_finger_event>(SDL_FINGERMOTION);
  check<cen::touch_finger_event>(SDL_FINGERDOWN);
  check<cen::touch_finger_event>(SDL_FINGERUP);
}

TEST(EventHandlerTypeChecks, MultiGestureEvent)
{
  check<cen::multi_gesture_event>(SDL_MULTIGESTURE);
}

TEST(EventHandlerTypeChecks, DollarGestureEvent)
{
  check<cen::dollar_gesture_event>(SDL_DOLLARGESTURE);
  check<cen::dollar_gesture_event>(SDL_DOLLARRECORD);
}

TEST(EventHandlerTypeChecks, DropEvent)
{
  check<cen::drop_event>(SDL_DROPBEGIN);
  check<cen::drop_event>(SDL_DROPFILE);
  check<cen::drop_event>(SDL_DROPTEXT);
  check<cen::drop_event>(SDL_DROPCOMPLETE);
}

TEST(EventHandlerTypeChecks, SensorEvent)
{
  check<cen::sensor_event>(SDL_SENSORUPDATE);
}

TEST(EventHandlerTypeChecks, QuitEvent)
{
  check<cen::quit_event>(SDL_QUIT);
}

TEST(EventHandlerTypeChecks, UserEvent)
{
  check<cen::user_event>(SDL_USEREVENT);
  check<cen::user_event>(static_cast<SDL_EventType>(SDL_USEREVENT + 1));
  check<cen::user_event>(static_cast<SDL_EventType>(SDL_USEREVENT + 2));
  check<cen::user_event>(static_cast<SDL_EventType>(SDL_USEREVENT + 42));
  check<cen::user_event>(static_cast<SDL_EventType>(SDL_LASTEVENT - 2));
  check<cen::user_event>(static_cast<SDL_EventType>(SDL_LASTEVENT - 1));
}

TEST(EventHandlerTypeChecks, SysWMEvent)
{
  // TODO check<cen::sys_wm_event>(SDL_SYSWMEVENT);
}