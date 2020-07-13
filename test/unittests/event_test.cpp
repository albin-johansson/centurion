#include "event.hpp"

#include <catch.hpp>

using namespace centurion;

namespace {

[[nodiscard]] auto create_event(u32 type) -> event
{
  SDL_Event sdlEvent;
  sdlEvent.type = type;
  return {sdlEvent};
}

}  // namespace

TEST_CASE("EventType operator==", "[EventType]")
{
  CHECK(event_type::Quit == SDL_EventType::SDL_QUIT);
  CHECK(event_type::AppTerminating == SDL_APP_TERMINATING);
  CHECK(event_type::AppLowMemory == SDL_APP_LOWMEMORY);
  CHECK(event_type::AppWillEnterBackground == SDL_APP_WILLENTERBACKGROUND);
  CHECK(event_type::AppDidEnterBackground == SDL_APP_DIDENTERBACKGROUND);
  CHECK(event_type::AppDidEnterForeground == SDL_APP_DIDENTERFOREGROUND);
  CHECK(event_type::Display == SDL_DISPLAYEVENT);
  CHECK(event_type::Window == SDL_WINDOWEVENT);
  CHECK(event_type::System == SDL_SYSWMEVENT);
  CHECK(event_type::KeyDown == SDL_KEYDOWN);
  CHECK(event_type::KeyUp == SDL_KEYUP);
  CHECK(event_type::TextEditing == SDL_TEXTEDITING);
  CHECK(event_type::TextInput == SDL_TEXTINPUT);
  CHECK(event_type::KeymapChanged == SDL_KEYMAPCHANGED);
  CHECK(event_type::MouseMotion == SDL_MOUSEMOTION);
  CHECK(event_type::MouseButtonDown == SDL_MOUSEBUTTONDOWN);
  CHECK(event_type::MouseButtonUp == SDL_MOUSEBUTTONUP);
  CHECK(event_type::MouseWheel == SDL_MOUSEWHEEL);
  CHECK(event_type::JoystickAxisMotion == SDL_JOYAXISMOTION);
  CHECK(event_type::JoystickBallMotion == SDL_JOYBALLMOTION);
  CHECK(event_type::JoystickHatMotion == SDL_JOYHATMOTION);
  CHECK(event_type::JoystickButtonDown == SDL_JOYBUTTONDOWN);
  CHECK(event_type::JoystickButtonUp == SDL_JOYBUTTONUP);
  CHECK(event_type::JoystickDeviceAdded == SDL_JOYDEVICEADDED);
  CHECK(event_type::JoystickDeviceRemoved == SDL_JOYDEVICEREMOVED);
  CHECK(event_type::ControllerAxisMotion == SDL_CONTROLLERAXISMOTION);
  CHECK(event_type::ControllerButtonDown == SDL_CONTROLLERBUTTONDOWN);
  CHECK(event_type::ControllerButtonUp == SDL_CONTROLLERBUTTONUP);
  CHECK(event_type::ControllerDeviceAdded == SDL_CONTROLLERDEVICEADDED);
  CHECK(event_type::ControllerDeviceRemoved == SDL_CONTROLLERDEVICEREMOVED);
  CHECK(event_type::ControllerDeviceRemapped == SDL_CONTROLLERDEVICEREMAPPED);
  CHECK(event_type::TouchDown == SDL_FINGERDOWN);
  CHECK(event_type::TouchUp == SDL_FINGERUP);
  CHECK(event_type::TouchMotion == SDL_FINGERMOTION);
  CHECK(event_type::DollarGesture == SDL_DOLLARGESTURE);
  CHECK(event_type::DollarRecord == SDL_DOLLARRECORD);
  CHECK(event_type::MultiGesture == SDL_MULTIGESTURE);
  CHECK(event_type::ClipboardUpdate == SDL_CLIPBOARDUPDATE);
  CHECK(event_type::DropFile == SDL_DROPFILE);
  CHECK(event_type::DropText == SDL_DROPTEXT);
  CHECK(event_type::DropBegin == SDL_DROPBEGIN);
  CHECK(event_type::DropComplete == SDL_DROPCOMPLETE);
  CHECK(event_type::AudioDeviceAdded == SDL_AUDIODEVICEADDED);
  CHECK(event_type::AudioDeviceRemoved == SDL_AUDIODEVICEREMOVED);
  CHECK(event_type::SensorUpdate == SDL_SENSORUPDATE);
  CHECK(event_type::RenderTargetsReset == SDL_RENDER_TARGETS_RESET);
  CHECK(event_type::RenderDeviceReset == SDL_RENDER_DEVICE_RESET);
  CHECK(event_type::User == SDL_USEREVENT);

  CHECK(SDL_QUIT == event_type::Quit);
  CHECK(SDL_APP_TERMINATING == event_type::AppTerminating);
  CHECK(SDL_APP_LOWMEMORY == event_type::AppLowMemory);
  CHECK(SDL_APP_WILLENTERBACKGROUND == event_type::AppWillEnterBackground);
  CHECK(SDL_APP_DIDENTERBACKGROUND == event_type::AppDidEnterBackground);
  CHECK(SDL_APP_DIDENTERFOREGROUND == event_type::AppDidEnterForeground);
  CHECK(SDL_DISPLAYEVENT == event_type::Display);
  CHECK(SDL_WINDOWEVENT == event_type::Window);
  CHECK(SDL_SYSWMEVENT == event_type::System);
  CHECK(SDL_KEYDOWN == event_type::KeyDown);
  CHECK(SDL_KEYUP == event_type::KeyUp);
  CHECK(SDL_TEXTEDITING == event_type::TextEditing);
  CHECK(SDL_TEXTINPUT == event_type::TextInput);
  CHECK(SDL_KEYMAPCHANGED == event_type::KeymapChanged);
  CHECK(SDL_MOUSEMOTION == event_type::MouseMotion);
  CHECK(SDL_MOUSEBUTTONDOWN == event_type::MouseButtonDown);
  CHECK(SDL_MOUSEBUTTONUP == event_type::MouseButtonUp);
  CHECK(SDL_MOUSEWHEEL == event_type::MouseWheel);
  CHECK(SDL_JOYAXISMOTION == event_type::JoystickAxisMotion);
  CHECK(SDL_JOYBALLMOTION == event_type::JoystickBallMotion);
  CHECK(SDL_JOYHATMOTION == event_type::JoystickHatMotion);
  CHECK(SDL_JOYBUTTONDOWN == event_type::JoystickButtonDown);
  CHECK(SDL_JOYBUTTONUP == event_type::JoystickButtonUp);
  CHECK(SDL_JOYDEVICEADDED == event_type::JoystickDeviceAdded);
  CHECK(SDL_JOYDEVICEREMOVED == event_type::JoystickDeviceRemoved);
  CHECK(SDL_CONTROLLERAXISMOTION == event_type::ControllerAxisMotion);
  CHECK(SDL_CONTROLLERBUTTONDOWN == event_type::ControllerButtonDown);
  CHECK(SDL_CONTROLLERBUTTONUP == event_type::ControllerButtonUp);
  CHECK(SDL_CONTROLLERDEVICEADDED == event_type::ControllerDeviceAdded);
  CHECK(SDL_CONTROLLERDEVICEREMOVED == event_type::ControllerDeviceRemoved);
  CHECK(SDL_CONTROLLERDEVICEREMAPPED == event_type::ControllerDeviceRemapped);
  CHECK(SDL_FINGERDOWN == event_type::TouchDown);
  CHECK(SDL_FINGERUP == event_type::TouchUp);
  CHECK(SDL_FINGERMOTION == event_type::TouchMotion);
  CHECK(SDL_DOLLARGESTURE == event_type::DollarGesture);
  CHECK(SDL_DOLLARRECORD == event_type::DollarRecord);
  CHECK(SDL_MULTIGESTURE == event_type::MultiGesture);
  CHECK(SDL_CLIPBOARDUPDATE == event_type::ClipboardUpdate);
  CHECK(SDL_DROPFILE == event_type::DropFile);
  CHECK(SDL_DROPTEXT == event_type::DropText);
  CHECK(SDL_DROPBEGIN == event_type::DropBegin);
  CHECK(SDL_DROPCOMPLETE == event_type::DropComplete);
  CHECK(SDL_AUDIODEVICEADDED == event_type::AudioDeviceAdded);
  CHECK(SDL_AUDIODEVICEREMOVED == event_type::AudioDeviceRemoved);
  CHECK(SDL_SENSORUPDATE == event_type::SensorUpdate);
  CHECK(SDL_RENDER_TARGETS_RESET == event_type::RenderTargetsReset);
  CHECK(SDL_RENDER_DEVICE_RESET == event_type::RenderDeviceReset);
  CHECK(SDL_USEREVENT == event_type::User);
}

TEST_CASE("EventType operator!=", "[EventType]")
{
  CHECK(event_type::DollarGesture != SDL_RENDER_DEVICE_RESET);
  CHECK(SDL_MOUSEMOTION != event_type::ControllerDeviceRemoved);
}

TEST_CASE("Event move constructor", "[Event]")
{
  CHECK_NOTHROW(event{{}});
}

TEST_CASE("Event::refresh", "[Event]")
{
  CHECK_NOTHROW(event::refresh());
}

TEST_CASE("Event::push", "[Event]")
{
  event::flush_all();
  {
    SDL_Event sdlEvent{};
    sdlEvent.type = SDL_KEYDOWN;
    event event{sdlEvent};
    event::push(event);
  }

  event event;
  CHECK(event.poll());
  CHECK(event.type() == event_type::KeyDown);
}

TEST_CASE("Event::flush", "[Event]")
{
  event::refresh();
  event::flush();

  event event;
  CHECK(!event.poll());
}

TEST_CASE("Event::flush_all", "[Event]")
{
  event::flush_all();

  event event;
  CHECK(!event.poll());
}

TEST_CASE("Event::poll", "[Event]")
{
  SDL_Event sdlEvent{};
  sdlEvent.type = SDL_MOUSEMOTION;
  sdlEvent.motion.x = 839;
  sdlEvent.motion.y = 351;

  event::flush();
  SDL_PushEvent(&sdlEvent);

  event event;
  CHECK(event.poll());

  REQUIRE(event.type() == event_type::MouseMotion);
  REQUIRE(event.is<mouse_motion_event>());

  auto& motionEvent = event.get<mouse_motion_event>();

  CHECK(motionEvent.x() == sdlEvent.motion.x);
  CHECK(motionEvent.y() == sdlEvent.motion.y);

  event::flush_all();
}

TEST_CASE("Event::type", "[Event]")
{
  const auto create_sdl_event = [](event_type type) noexcept {
    SDL_Event event{};
    event.type = static_cast<u32>(type);
    return event;
  };

  const auto type = event_type::TouchMotion;
  auto sdlEvent = create_sdl_event(type);

  event::flush_all();
  SDL_PushEvent(&sdlEvent);

  event event;
  CHECK(event.poll());
  CHECK(event.type() == type);

  event::flush_all();
}

TEST_CASE("Event::empty", "[Event]")
{
  SECTION("Empty")
  {
    event event;
    CHECK(event.empty());
  }

  SECTION("Not empty")
  {
    const auto event = create_event(SDL_AUDIODEVICEADDED);
    CHECK(!event.empty());
  }
}

TEST_CASE("Event::is", "[Event]")
{
  SECTION("AudioDeviceEvent")
  {
    const auto added = create_event(SDL_AUDIODEVICEADDED);
    const auto removed = create_event(SDL_AUDIODEVICEREMOVED);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(added.is<audio_device_event>());
    CHECK(removed.is<audio_device_event>());
    CHECK(!wrong.is<audio_device_event>());
  }

  SECTION("ControllerAxisEvent")
  {
    const auto event = create_event(SDL_CONTROLLERAXISMOTION);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(event.is<controller_axis_event>());
    CHECK(!wrong.is<controller_axis_event>());
  }

  SECTION("ControllerButtonEvent")
  {
    const auto up = create_event(SDL_CONTROLLERBUTTONUP);
    const auto down = create_event(SDL_CONTROLLERBUTTONDOWN);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(up.is<controller_button_event>());
    CHECK(down.is<controller_button_event>());
    CHECK(!wrong.is<controller_button_event>());
  }

  SECTION("ControllerDeviceEvent")
  {
    const auto added = create_event(SDL_CONTROLLERDEVICEADDED);
    const auto removed = create_event(SDL_CONTROLLERDEVICEREMOVED);
    const auto remapped = create_event(SDL_CONTROLLERDEVICEREMAPPED);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(added.is<controller_device_event>());
    CHECK(removed.is<controller_device_event>());
    CHECK(remapped.is<controller_device_event>());
    CHECK(!wrong.is<controller_device_event>());
  }

  SECTION("DollarGestureEvent")
  {
    const auto gesture = create_event(SDL_DOLLARGESTURE);
    const auto record = create_event(SDL_DOLLARRECORD);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(gesture.is<dollar_gesture_event>());
    CHECK(record.is<dollar_gesture_event>());
    CHECK(!wrong.is<dollar_gesture_event>());
  }

  SECTION("DropEvent")
  {
    const auto begin = create_event(SDL_DROPBEGIN);
    const auto complete = create_event(SDL_DROPCOMPLETE);
    const auto file = create_event(SDL_DROPFILE);
    const auto text = create_event(SDL_DROPTEXT);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(begin.is<drop_event>());
    CHECK(complete.is<drop_event>());
    CHECK(file.is<drop_event>());
    CHECK(text.is<drop_event>());
    CHECK(!wrong.is<drop_event>());
  }

  SECTION("JoyAxisEvent")
  {
    const auto motion = create_event(SDL_JOYAXISMOTION);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(motion.is<joy_axis_event>());
    CHECK(!wrong.is<joy_axis_event>());
  }

  SECTION("JoyBallEvent")
  {
    const auto motion = create_event(SDL_JOYBALLMOTION);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(motion.is<joy_ball_event>());
    CHECK(!wrong.is<joy_ball_event>());
  }

  SECTION("JoyButtonEvent")
  {
    const auto up = create_event(SDL_JOYBUTTONUP);
    const auto down = create_event(SDL_JOYBUTTONDOWN);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(up.is<joy_button_event>());
    CHECK(down.is<joy_button_event>());
    CHECK(!wrong.is<joy_button_event>());
  }

  SECTION("JoyDeviceEvent")
  {
    const auto added = create_event(SDL_JOYDEVICEADDED);
    const auto removed = create_event(SDL_JOYDEVICEREMOVED);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(added.is<joy_device_event>());
    CHECK(removed.is<joy_device_event>());
    CHECK(!wrong.is<joy_device_event>());
  }

  SECTION("JoyHatEvent")
  {
    const auto motion = create_event(SDL_JOYHATMOTION);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(motion.is<joy_hat_event>());
    CHECK(!wrong.is<joy_hat_event>());
  }

  SECTION("KeyboardEvent")
  {
    const auto up = create_event(SDL_KEYUP);
    const auto down = create_event(SDL_KEYDOWN);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(up.is<keyboard_event>());
    CHECK(down.is<keyboard_event>());
    CHECK(!wrong.is<keyboard_event>());
  }

  SECTION("MouseButtonEvent")
  {
    const auto up = create_event(SDL_MOUSEBUTTONUP);
    const auto down = create_event(SDL_MOUSEBUTTONDOWN);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(up.is<mouse_button_event>());
    CHECK(down.is<mouse_button_event>());
    CHECK(!wrong.is<mouse_button_event>());
  }

  SECTION("MouseMotionEvent")
  {
    const auto motion = create_event(SDL_MOUSEMOTION);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(motion.is<mouse_motion_event>());
    CHECK(!wrong.is<mouse_button_event>());
  }

  SECTION("MouseWheelEvent")
  {
    const auto wheel = create_event(SDL_MOUSEWHEEL);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(wheel.is<mouse_wheel_event>());
    CHECK(!wrong.is<mouse_wheel_event>());
  }

  SECTION("MultiGestureEvent")
  {
    const auto gesture = create_event(SDL_MULTIGESTURE);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(gesture.is<multi_gesture_event>());
    CHECK(!wrong.is<multi_gesture_event>());
  }

  SECTION("QuitEvent")
  {
    const auto quit = create_event(SDL_QUIT);
    const auto wrong = create_event(SDL_KEYUP);

    CHECK(quit.is<quit_event>());
    CHECK(!wrong.is<quit_event>());
  }

  SECTION("TextEditingEvent")
  {
    const auto editing = create_event(SDL_TEXTEDITING);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(editing.is<text_editing_event>());
    CHECK(!wrong.is<text_editing_event>());
  }

  SECTION("TextInputEvent")
  {
    const auto input = create_event(SDL_TEXTINPUT);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(input.is<text_input_event>());
    CHECK(!wrong.is<text_input_event>());
  }

  SECTION("TouchFingerEvent")
  {
    const auto motion = create_event(SDL_FINGERMOTION);
    const auto up = create_event(SDL_FINGERUP);
    const auto down = create_event(SDL_FINGERDOWN);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(motion.is<touch_finger_event>());
    CHECK(up.is<touch_finger_event>());
    CHECK(down.is<touch_finger_event>());
    CHECK(!wrong.is<touch_finger_event>());
  }

  SECTION("WindowEvent")
  {
    const auto window = create_event(SDL_WINDOWEVENT);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(window.is<window_event>());
    CHECK(!wrong.is<window_event>());
  }
}

TEST_CASE("Event::get", "[Event]")
{
  SECTION("Const")
  {
    const auto quit = create_event(SDL_QUIT);

    CHECK_NOTHROW(quit.get<quit_event>());
    CHECK_THROWS(quit.get<window_event>());
  }

  SECTION("Non-const")
  {
    auto quit = create_event(SDL_QUIT);

    CHECK_NOTHROW(quit.get<quit_event>());
    CHECK_THROWS(quit.get<window_event>());
  }
}

TEST_CASE("Event::try_get", "[Event]")
{
  SECTION("Const")
  {
    const auto event = create_event(SDL_MOUSEMOTION);

    CHECK(event.try_get<mouse_motion_event>());
    CHECK(!event.try_get<window_event>());
  }

  SECTION("Non-const")
  {
    auto event = create_event(SDL_MULTIGESTURE);

    CHECK(event.try_get<multi_gesture_event>());
    CHECK(!event.try_get<joy_hat_event>());
  }
}
