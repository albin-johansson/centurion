#include "event.h"

#include <catch.hpp>

using namespace centurion::event;

TEST_CASE("EventType operator==", "[EventType]")
{
  CHECK(EventType::Quit == SDL_EventType::SDL_QUIT);
  CHECK(EventType::AppTerminating == SDL_APP_TERMINATING);
  CHECK(EventType::AppLowMemory == SDL_APP_LOWMEMORY);
  CHECK(EventType::AppWillEnterBackground == SDL_APP_WILLENTERBACKGROUND);
  CHECK(EventType::AppDidEnterBackground == SDL_APP_DIDENTERBACKGROUND);
  CHECK(EventType::AppDidEnterForeground == SDL_APP_DIDENTERFOREGROUND);
  CHECK(EventType::Display == SDL_DISPLAYEVENT);
  CHECK(EventType::Window == SDL_WINDOWEVENT);
  CHECK(EventType::System == SDL_SYSWMEVENT);
  CHECK(EventType::KeyDown == SDL_KEYDOWN);
  CHECK(EventType::KeyUp == SDL_KEYUP);
  CHECK(EventType::TextEditing == SDL_TEXTEDITING);
  CHECK(EventType::TextInput == SDL_TEXTINPUT);
  CHECK(EventType::KeymapChanged == SDL_KEYMAPCHANGED);
  CHECK(EventType::MouseMotion == SDL_MOUSEMOTION);
  CHECK(EventType::MouseButtonDown == SDL_MOUSEBUTTONDOWN);
  CHECK(EventType::MouseButtonUp == SDL_MOUSEBUTTONUP);
  CHECK(EventType::MouseWheel == SDL_MOUSEWHEEL);
  CHECK(EventType::JoystickAxisMotion == SDL_JOYAXISMOTION);
  CHECK(EventType::JoystickBallMotion == SDL_JOYBALLMOTION);
  CHECK(EventType::JoystickHatMotion == SDL_JOYHATMOTION);
  CHECK(EventType::JoystickButtonDown == SDL_JOYBUTTONDOWN);
  CHECK(EventType::JoystickButtonUp == SDL_JOYBUTTONUP);
  CHECK(EventType::JoystickDeviceAdded == SDL_JOYDEVICEADDED);
  CHECK(EventType::JoystickDeviceRemoved == SDL_JOYDEVICEREMOVED);
  CHECK(EventType::ControllerAxisMotion == SDL_CONTROLLERAXISMOTION);
  CHECK(EventType::ControllerButtonDown == SDL_CONTROLLERBUTTONDOWN);
  CHECK(EventType::ControllerButtonUp == SDL_CONTROLLERBUTTONUP);
  CHECK(EventType::ControllerDeviceAdded == SDL_CONTROLLERDEVICEADDED);
  CHECK(EventType::ControllerDeviceRemoved == SDL_CONTROLLERDEVICEREMOVED);
  CHECK(EventType::ControllerDeviceRemapped == SDL_CONTROLLERDEVICEREMAPPED);
  CHECK(EventType::TouchDown == SDL_FINGERDOWN);
  CHECK(EventType::TouchUp == SDL_FINGERUP);
  CHECK(EventType::TouchMotion == SDL_FINGERMOTION);
  CHECK(EventType::DollarGesture == SDL_DOLLARGESTURE);
  CHECK(EventType::DollarRecord == SDL_DOLLARRECORD);
  CHECK(EventType::MultiGesture == SDL_MULTIGESTURE);
  CHECK(EventType::ClipboardUpdate == SDL_CLIPBOARDUPDATE);
  CHECK(EventType::DropFile == SDL_DROPFILE);
  CHECK(EventType::DropText == SDL_DROPTEXT);
  CHECK(EventType::DropBegin == SDL_DROPBEGIN);
  CHECK(EventType::DropComplete == SDL_DROPCOMPLETE);
  CHECK(EventType::AudioDeviceAdded == SDL_AUDIODEVICEADDED);
  CHECK(EventType::AudioDeviceRemoved == SDL_AUDIODEVICEREMOVED);
  CHECK(EventType::SensorUpdate == SDL_SENSORUPDATE);
  CHECK(EventType::RenderTargetsReset == SDL_RENDER_TARGETS_RESET);
  CHECK(EventType::RenderDeviceReset == SDL_RENDER_DEVICE_RESET);
  CHECK(EventType::User == SDL_USEREVENT);

  CHECK(SDL_QUIT == EventType::Quit);
  CHECK(SDL_APP_TERMINATING == EventType::AppTerminating);
  CHECK(SDL_APP_LOWMEMORY == EventType::AppLowMemory);
  CHECK(SDL_APP_WILLENTERBACKGROUND == EventType::AppWillEnterBackground);
  CHECK(SDL_APP_DIDENTERBACKGROUND == EventType::AppDidEnterBackground);
  CHECK(SDL_APP_DIDENTERFOREGROUND == EventType::AppDidEnterForeground);
  CHECK(SDL_DISPLAYEVENT == EventType::Display);
  CHECK(SDL_WINDOWEVENT == EventType::Window);
  CHECK(SDL_SYSWMEVENT == EventType::System);
  CHECK(SDL_KEYDOWN == EventType::KeyDown);
  CHECK(SDL_KEYUP == EventType::KeyUp);
  CHECK(SDL_TEXTEDITING == EventType::TextEditing);
  CHECK(SDL_TEXTINPUT == EventType::TextInput);
  CHECK(SDL_KEYMAPCHANGED == EventType::KeymapChanged);
  CHECK(SDL_MOUSEMOTION == EventType::MouseMotion);
  CHECK(SDL_MOUSEBUTTONDOWN == EventType::MouseButtonDown);
  CHECK(SDL_MOUSEBUTTONUP == EventType::MouseButtonUp);
  CHECK(SDL_MOUSEWHEEL == EventType::MouseWheel);
  CHECK(SDL_JOYAXISMOTION == EventType::JoystickAxisMotion);
  CHECK(SDL_JOYBALLMOTION == EventType::JoystickBallMotion);
  CHECK(SDL_JOYHATMOTION == EventType::JoystickHatMotion);
  CHECK(SDL_JOYBUTTONDOWN == EventType::JoystickButtonDown);
  CHECK(SDL_JOYBUTTONUP == EventType::JoystickButtonUp);
  CHECK(SDL_JOYDEVICEADDED == EventType::JoystickDeviceAdded);
  CHECK(SDL_JOYDEVICEREMOVED == EventType::JoystickDeviceRemoved);
  CHECK(SDL_CONTROLLERAXISMOTION == EventType::ControllerAxisMotion);
  CHECK(SDL_CONTROLLERBUTTONDOWN == EventType::ControllerButtonDown);
  CHECK(SDL_CONTROLLERBUTTONUP == EventType::ControllerButtonUp);
  CHECK(SDL_CONTROLLERDEVICEADDED == EventType::ControllerDeviceAdded);
  CHECK(SDL_CONTROLLERDEVICEREMOVED == EventType::ControllerDeviceRemoved);
  CHECK(SDL_CONTROLLERDEVICEREMAPPED == EventType::ControllerDeviceRemapped);
  CHECK(SDL_FINGERDOWN == EventType::TouchDown);
  CHECK(SDL_FINGERUP == EventType::TouchUp);
  CHECK(SDL_FINGERMOTION == EventType::TouchMotion);
  CHECK(SDL_DOLLARGESTURE == EventType::DollarGesture);
  CHECK(SDL_DOLLARRECORD == EventType::DollarRecord);
  CHECK(SDL_MULTIGESTURE == EventType::MultiGesture);
  CHECK(SDL_CLIPBOARDUPDATE == EventType::ClipboardUpdate);
  CHECK(SDL_DROPFILE == EventType::DropFile);
  CHECK(SDL_DROPTEXT == EventType::DropText);
  CHECK(SDL_DROPBEGIN == EventType::DropBegin);
  CHECK(SDL_DROPCOMPLETE == EventType::DropComplete);
  CHECK(SDL_AUDIODEVICEADDED == EventType::AudioDeviceAdded);
  CHECK(SDL_AUDIODEVICEREMOVED == EventType::AudioDeviceRemoved);
  CHECK(SDL_SENSORUPDATE == EventType::SensorUpdate);
  CHECK(SDL_RENDER_TARGETS_RESET == EventType::RenderTargetsReset);
  CHECK(SDL_RENDER_DEVICE_RESET == EventType::RenderDeviceReset);
  CHECK(SDL_USEREVENT == EventType::User);
}

TEST_CASE("EventType operator!=", "[EventType]")
{
  CHECK(EventType::DollarGesture != SDL_RENDER_DEVICE_RESET);
  CHECK(SDL_MOUSEMOTION != EventType::ControllerDeviceRemoved);
}

TEST_CASE("Event::refresh", "[Event]")
{
  //  CHECK_NOTHROW(Event::refresh());
}

TEST_CASE("Event::push", "[Event]")
{
  //  Event::flush_all();

  //  {
  //    SDL_Event sdlEvent{};
  //    sdlEvent.type = SDL_KEYDOWN;
  //    Event event{sdlEvent};
  //    Event::push(event);
  //  }
  //
  //  Event event;
  //  CHECK(event.poll());
  //  CHECK(event.type() == EventType::KeyDown);
}

// TEST_CASE("Event::flush", "[Event]") {
//  Event::refresh();
//  Event::flush();
//  Event event;
//  CHECK(!event.poll());
//}
//
// TEST_CASE("Event::flush_all", "[Event]") {
//  Event::flush_all();
//  Event event;
//
//  CHECK(!event.poll());
//}
//
// TEST_CASE("Event::poll", "[Event]") {
//  SDL_Event sdlEvent{};
//  sdlEvent.type = SDL_MOUSEMOTION;
//  sdlEvent.motion.x = 839;
//  sdlEvent.motion.y = 351;
//
//  Event::flush();
//  SDL_PushEvent(&sdlEvent);
//
//  Event event;
//  CHECK(event.poll());
//  CHECK(event.type() == static_cast<EventType>(sdlEvent.type));
//
//  auto motionEvent = event.as_mouse_motion_event();
//  REQUIRE(motionEvent);
//  CHECK(motionEvent->x() == sdlEvent.motion.x);
//  CHECK(motionEvent->y() == sdlEvent.motion.y);
//
//  Event::flush_all();
//}
//
// TEST_CASE("Event::type", "[Event]") {
//  const auto type = EventType::DropFile;
//  auto sdlEvent = [type]() noexcept {
//    SDL_Event sdlEvent{};
//    sdlEvent.type = static_cast<unsigned>(type);
//    return sdlEvent;
//  }();
//
//  Event::flush_all();
//  SDL_PushEvent(&sdlEvent);
//
//  Event event;
//  CHECK(event.poll());
//  CHECK(event.type() == type);
//
//  Event::flush_all();
//}

TEST_CASE("Event::as_audio_device_event", "[Event]")
{
  SECTION("SDL_AUDIODEVICEADDED")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_AUDIODEVICEADDED;
    Event event{sdlEvent};

    CHECK(event.as_audio_device_event());
  }

  SECTION("SDL_AUDIODEVICEREMOVED")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_AUDIODEVICEREMOVED;
    Event event{sdlEvent};

    CHECK(event.as_audio_device_event());
  }

  SECTION("Wrong type")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_QUIT;
    Event event{sdlEvent};

    CHECK(!event.as_audio_device_event());
  }
}

TEST_CASE("Event::as_controller_axis_event", "[Event]")
{
  SECTION("SDL_CONTROLLERAXISMOTION")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_CONTROLLERAXISMOTION;
    Event event{sdlEvent};

    CHECK(event.as_controller_axis_event());
  }

  SECTION("Wrong type")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_MOUSEWHEEL;
    Event event{sdlEvent};

    CHECK(!event.as_controller_axis_event());
  }
}

TEST_CASE("Event::as_controller_button_event", "[Event]")
{
  SECTION("SDL_CONTROLLERBUTTONUP")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_CONTROLLERBUTTONUP;
    Event event{sdlEvent};

    CHECK(event.as_controller_button_event());
  }

  SECTION("SDL_CONTROLLERBUTTONDOWN")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_CONTROLLERBUTTONDOWN;
    Event event{sdlEvent};

    CHECK(event.as_controller_button_event());
  }

  SECTION("Wrong type")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_FINGERDOWN;
    Event event{sdlEvent};

    CHECK(!event.as_controller_button_event());
  }
}

TEST_CASE("Event::as_controller_device_event", "[Event]")
{
  SECTION("SDL_CONTROLLERDEVICEADDED")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_CONTROLLERDEVICEADDED;
    Event event{sdlEvent};

    CHECK(event.as_controller_device_event());
  }

  SECTION("SDL_CONTROLLERDEVICEREMOVED")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_CONTROLLERDEVICEREMOVED;
    Event event{sdlEvent};

    CHECK(event.as_controller_device_event());
  }

  SECTION("SDL_CONTROLLERDEVICEREMAPPED")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_CONTROLLERDEVICEREMAPPED;
    Event event{sdlEvent};

    CHECK(event.as_controller_device_event());
  }

  SECTION("Wrong type")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_DOLLARGESTURE;
    Event event{sdlEvent};

    CHECK(!event.as_controller_device_event());
  }
}

TEST_CASE("Event::as_dollar_gesture_event", "[Event]")
{
  SECTION("SDL_DOLLARGESTURE")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_DOLLARGESTURE;
    Event event{sdlEvent};

    CHECK(event.as_dollar_gesture_event());
  }

  SECTION("SDL_DOLLARRECORD")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_DOLLARRECORD;
    Event event{sdlEvent};

    CHECK(event.as_dollar_gesture_event());
  }

  SECTION("Wrong type")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_WINDOWEVENT;
    Event event{sdlEvent};

    CHECK(!event.as_dollar_gesture_event());
  }
}

TEST_CASE("Event::as_drop_event", "[Event]")
{
  SECTION("SDL_DROPBEGIN")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_DROPBEGIN;
    Event event{sdlEvent};

    CHECK(event.as_drop_event());
  }

  SECTION("SDL_DROPCOMPLETE")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_DROPCOMPLETE;
    Event event{sdlEvent};

    CHECK(event.as_drop_event());
  }

  SECTION("SDL_DROPFILE")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_DROPFILE;
    Event event{sdlEvent};

    CHECK(event.as_drop_event());
  }

  SECTION("SDL_DROPTEXT")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_DROPTEXT;
    Event event{sdlEvent};

    CHECK(event.as_drop_event());
  }

  SECTION("Wrong type")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_MOUSEWHEEL;
    Event event{sdlEvent};

    CHECK(!event.as_drop_event());
  }
}

TEST_CASE("Event::as_joy_axis_event", "[Event]")
{
  SECTION("SDL_JOYAXISMOTION")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_JOYAXISMOTION;
    Event event{sdlEvent};

    CHECK(event.as_joy_axis_event());
  }

  SECTION("Wrong type")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_FINGERUP;
    Event event{sdlEvent};

    CHECK(!event.as_joy_axis_event());
  }
}

TEST_CASE("Event::as_joy_ball_event", "[Event]")
{
  SECTION("SDL_JOYBALLMOTION")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_JOYBALLMOTION;
    Event event{sdlEvent};

    CHECK(event.as_joy_ball_event());
  }

  SECTION("Wrong type")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_WINDOWEVENT;
    Event event{sdlEvent};

    CHECK(!event.as_joy_ball_event());
  }
}

TEST_CASE("Event::as_joy_button_event", "[Event]")
{
  SECTION("SDL_JOYBUTTONUP")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_JOYBUTTONUP;
    Event event{sdlEvent};

    CHECK(event.as_joy_button_event());
  }

  SECTION("SDL_JOYBUTTONDOWN")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_JOYBUTTONDOWN;
    Event event{sdlEvent};

    CHECK(event.as_joy_button_event());
  }

  SECTION("Wrong type")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_KEYMAPCHANGED;
    Event event{sdlEvent};

    CHECK(!event.as_joy_button_event());
  }
}

TEST_CASE("Event::as_joy_device_event", "[Event]")
{
  SECTION("SDL_JOYDEVICEADDED")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_JOYDEVICEADDED;
    Event event{sdlEvent};

    CHECK(event.as_joy_device_event());
  }

  SECTION("SDL_JOYDEVICEREMOVED")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_JOYDEVICEREMOVED;
    Event event{sdlEvent};

    CHECK(event.as_joy_device_event());
  }

  SECTION("Wrong type")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_MOUSEMOTION;
    Event event{sdlEvent};

    CHECK(!event.as_joy_device_event());
  }
}

TEST_CASE("Event::as_joy_hat_event", "[Event]")
{
  SECTION("SDL_JOYHATMOTION")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_JOYHATMOTION;
    Event event{sdlEvent};

    CHECK(event.as_joy_hat_event());
  }

  SECTION("Wrong type")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_DOLLARGESTURE;
    Event event{sdlEvent};

    CHECK(!event.as_joy_hat_event());
  }
}

TEST_CASE("Event::as_keyboard_event", "[Event]")
{
  SECTION("SDL_KEYUP")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_KEYUP;
    Event event{sdlEvent};

    CHECK(event.as_keyboard_event());
  }

  SECTION("SDL_KEYDOWN")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_KEYDOWN;
    Event event{sdlEvent};

    CHECK(event.as_keyboard_event());
  }

  SECTION("Wrong type")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_JOYBALLMOTION;
    Event event{sdlEvent};

    CHECK(!event.as_keyboard_event());
  }
}

TEST_CASE("Event::as_mouse_button_event", "[Event]")
{
  SECTION("SDL_MOUSEBUTTONUP")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_MOUSEBUTTONUP;
    Event event{sdlEvent};

    CHECK(event.as_mouse_button_event());
  }

  SECTION("SDL_MOUSEBUTTONDOWN")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_MOUSEBUTTONDOWN;
    Event event{sdlEvent};

    CHECK(event.as_mouse_button_event());
  }

  SECTION("Wrong type")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_SENSORUPDATE;
    Event event{sdlEvent};

    CHECK(!event.as_mouse_button_event());
  }
}

TEST_CASE("Event::as_mouse_motion_event", "[Event]")
{
  SECTION("SDL_MOUSEMOTION")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_MOUSEMOTION;
    Event event{sdlEvent};

    CHECK(event.as_mouse_motion_event());
  }

  SECTION("Wrong type")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_SYSWMEVENT;
    Event event{sdlEvent};

    CHECK(!event.as_mouse_motion_event());
  }
}

TEST_CASE("Event::as_mouse_wheel_event", "[Event]")
{
  SECTION("SDL_MOUSEWHEEL")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_MOUSEWHEEL;
    Event event{sdlEvent};

    CHECK(event.as_mouse_wheel_event());
  }

  SECTION("Wrong type")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_FINGERMOTION;
    Event event{sdlEvent};

    CHECK(!event.as_mouse_wheel_event());
  }
}

TEST_CASE("Event::as_multi_gesture_event", "[Event]")
{
  SECTION("SDL_MULTIGESTURE")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_MULTIGESTURE;
    Event event{sdlEvent};

    CHECK(event.as_multi_gesture_event());
  }

  SECTION("Wrong type")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_MOUSEBUTTONUP;
    Event event{sdlEvent};

    CHECK(!event.as_multi_gesture_event());
  }
}

TEST_CASE("Event::as_quit_event", "[Event]")
{
  SECTION("SDL_QUIT")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_QUIT;
    Event event{sdlEvent};

    CHECK(event.as_quit_event());
  }

  SECTION("Wrong type")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_APP_WILLENTERFOREGROUND;
    Event event{sdlEvent};

    CHECK(!event.as_quit_event());
  }
}

TEST_CASE("Event::as_text_editing_event", "[Event]")
{
  SECTION("SDL_TEXTEDITING")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_TEXTEDITING;
    Event event{sdlEvent};

    CHECK(event.as_text_editing_event());
  }

  SECTION("Wrong type")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_KEYMAPCHANGED;
    Event event{sdlEvent};

    CHECK(!event.as_text_editing_event());
  }
}

TEST_CASE("Event::as_text_input_event", "[Event]")
{
  SECTION("SDL_TEXTINPUT")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_TEXTINPUT;
    Event event{sdlEvent};

    CHECK(event.as_text_input_event());
  }

  SECTION("Wrong type")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_CONTROLLERBUTTONUP;
    Event event{sdlEvent};

    CHECK(!event.as_text_input_event());
  }
}

TEST_CASE("Event::as_touch_finger_event", "[Event]")
{
  SECTION("SDL_FINGERMOTION")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_FINGERMOTION;
    Event event{sdlEvent};

    CHECK(event.as_touch_finger_event());
  }

  SECTION("SDL_FINGERDOWN")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_FINGERDOWN;
    Event event{sdlEvent};

    CHECK(event.as_touch_finger_event());
  }

  SECTION("SDL_FINGERUP")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_FINGERUP;
    Event event{sdlEvent};

    CHECK(event.as_touch_finger_event());
  }

  SECTION("Wrong type")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_DISPLAYEVENT;
    Event event{sdlEvent};

    CHECK(!event.as_touch_finger_event());
  }
}

TEST_CASE("Event::as_window_event", "[Event]")
{
  SECTION("SDL_WINDOWEVENT")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_WINDOWEVENT;
    Event event{sdlEvent};

    CHECK(event.as_window_event());
  }

  SECTION("Wrong type")
  {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_AUDIODEVICEADDED;
    Event event{sdlEvent};

    CHECK(!event.as_window_event());
  }
}