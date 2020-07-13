#include "event.hpp"

#include <catch.hpp>

#include "centurion_as_ctn.hpp"

namespace {

[[nodiscard]] auto create_event(ctn::u32 type) -> ctn::event
{
  SDL_Event sdlEvent;
  sdlEvent.type = type;
  return {sdlEvent};
}

}  // namespace

TEST_CASE("event_type operator==", "[event_type]")
{
  CHECK(ctn::event_type::Quit == SDL_EventType::SDL_QUIT);
  CHECK(ctn::event_type::AppTerminating == SDL_APP_TERMINATING);
  CHECK(ctn::event_type::AppLowMemory == SDL_APP_LOWMEMORY);
  CHECK(ctn::event_type::AppWillEnterBackground == SDL_APP_WILLENTERBACKGROUND);
  CHECK(ctn::event_type::AppDidEnterBackground == SDL_APP_DIDENTERBACKGROUND);
  CHECK(ctn::event_type::AppDidEnterForeground == SDL_APP_DIDENTERFOREGROUND);
  CHECK(ctn::event_type::Display == SDL_DISPLAYEVENT);
  CHECK(ctn::event_type::Window == SDL_WINDOWEVENT);
  CHECK(ctn::event_type::System == SDL_SYSWMEVENT);
  CHECK(ctn::event_type::KeyDown == SDL_KEYDOWN);
  CHECK(ctn::event_type::KeyUp == SDL_KEYUP);
  CHECK(ctn::event_type::TextEditing == SDL_TEXTEDITING);
  CHECK(ctn::event_type::TextInput == SDL_TEXTINPUT);
  CHECK(ctn::event_type::KeymapChanged == SDL_KEYMAPCHANGED);
  CHECK(ctn::event_type::MouseMotion == SDL_MOUSEMOTION);
  CHECK(ctn::event_type::MouseButtonDown == SDL_MOUSEBUTTONDOWN);
  CHECK(ctn::event_type::MouseButtonUp == SDL_MOUSEBUTTONUP);
  CHECK(ctn::event_type::MouseWheel == SDL_MOUSEWHEEL);
  CHECK(ctn::event_type::JoystickAxisMotion == SDL_JOYAXISMOTION);
  CHECK(ctn::event_type::JoystickBallMotion == SDL_JOYBALLMOTION);
  CHECK(ctn::event_type::JoystickHatMotion == SDL_JOYHATMOTION);
  CHECK(ctn::event_type::JoystickButtonDown == SDL_JOYBUTTONDOWN);
  CHECK(ctn::event_type::JoystickButtonUp == SDL_JOYBUTTONUP);
  CHECK(ctn::event_type::JoystickDeviceAdded == SDL_JOYDEVICEADDED);
  CHECK(ctn::event_type::JoystickDeviceRemoved == SDL_JOYDEVICEREMOVED);
  CHECK(ctn::event_type::ControllerAxisMotion == SDL_CONTROLLERAXISMOTION);
  CHECK(ctn::event_type::ControllerButtonDown == SDL_CONTROLLERBUTTONDOWN);
  CHECK(ctn::event_type::ControllerButtonUp == SDL_CONTROLLERBUTTONUP);
  CHECK(ctn::event_type::ControllerDeviceAdded == SDL_CONTROLLERDEVICEADDED);
  CHECK(ctn::event_type::ControllerDeviceRemoved ==
        SDL_CONTROLLERDEVICEREMOVED);
  CHECK(ctn::event_type::ControllerDeviceRemapped ==
        SDL_CONTROLLERDEVICEREMAPPED);
  CHECK(ctn::event_type::TouchDown == SDL_FINGERDOWN);
  CHECK(ctn::event_type::TouchUp == SDL_FINGERUP);
  CHECK(ctn::event_type::TouchMotion == SDL_FINGERMOTION);
  CHECK(ctn::event_type::DollarGesture == SDL_DOLLARGESTURE);
  CHECK(ctn::event_type::DollarRecord == SDL_DOLLARRECORD);
  CHECK(ctn::event_type::MultiGesture == SDL_MULTIGESTURE);
  CHECK(ctn::event_type::ClipboardUpdate == SDL_CLIPBOARDUPDATE);
  CHECK(ctn::event_type::DropFile == SDL_DROPFILE);
  CHECK(ctn::event_type::DropText == SDL_DROPTEXT);
  CHECK(ctn::event_type::DropBegin == SDL_DROPBEGIN);
  CHECK(ctn::event_type::DropComplete == SDL_DROPCOMPLETE);
  CHECK(ctn::event_type::AudioDeviceAdded == SDL_AUDIODEVICEADDED);
  CHECK(ctn::event_type::AudioDeviceRemoved == SDL_AUDIODEVICEREMOVED);
  CHECK(ctn::event_type::SensorUpdate == SDL_SENSORUPDATE);
  CHECK(ctn::event_type::RenderTargetsReset == SDL_RENDER_TARGETS_RESET);
  CHECK(ctn::event_type::RenderDeviceReset == SDL_RENDER_DEVICE_RESET);
  CHECK(ctn::event_type::User == SDL_USEREVENT);

  CHECK(SDL_QUIT == ctn::event_type::Quit);
  CHECK(SDL_APP_TERMINATING == ctn::event_type::AppTerminating);
  CHECK(SDL_APP_LOWMEMORY == ctn::event_type::AppLowMemory);
  CHECK(SDL_APP_WILLENTERBACKGROUND == ctn::event_type::AppWillEnterBackground);
  CHECK(SDL_APP_DIDENTERBACKGROUND == ctn::event_type::AppDidEnterBackground);
  CHECK(SDL_APP_DIDENTERFOREGROUND == ctn::event_type::AppDidEnterForeground);
  CHECK(SDL_DISPLAYEVENT == ctn::event_type::Display);
  CHECK(SDL_WINDOWEVENT == ctn::event_type::Window);
  CHECK(SDL_SYSWMEVENT == ctn::event_type::System);
  CHECK(SDL_KEYDOWN == ctn::event_type::KeyDown);
  CHECK(SDL_KEYUP == ctn::event_type::KeyUp);
  CHECK(SDL_TEXTEDITING == ctn::event_type::TextEditing);
  CHECK(SDL_TEXTINPUT == ctn::event_type::TextInput);
  CHECK(SDL_KEYMAPCHANGED == ctn::event_type::KeymapChanged);
  CHECK(SDL_MOUSEMOTION == ctn::event_type::MouseMotion);
  CHECK(SDL_MOUSEBUTTONDOWN == ctn::event_type::MouseButtonDown);
  CHECK(SDL_MOUSEBUTTONUP == ctn::event_type::MouseButtonUp);
  CHECK(SDL_MOUSEWHEEL == ctn::event_type::MouseWheel);
  CHECK(SDL_JOYAXISMOTION == ctn::event_type::JoystickAxisMotion);
  CHECK(SDL_JOYBALLMOTION == ctn::event_type::JoystickBallMotion);
  CHECK(SDL_JOYHATMOTION == ctn::event_type::JoystickHatMotion);
  CHECK(SDL_JOYBUTTONDOWN == ctn::event_type::JoystickButtonDown);
  CHECK(SDL_JOYBUTTONUP == ctn::event_type::JoystickButtonUp);
  CHECK(SDL_JOYDEVICEADDED == ctn::event_type::JoystickDeviceAdded);
  CHECK(SDL_JOYDEVICEREMOVED == ctn::event_type::JoystickDeviceRemoved);
  CHECK(SDL_CONTROLLERAXISMOTION == ctn::event_type::ControllerAxisMotion);
  CHECK(SDL_CONTROLLERBUTTONDOWN == ctn::event_type::ControllerButtonDown);
  CHECK(SDL_CONTROLLERBUTTONUP == ctn::event_type::ControllerButtonUp);
  CHECK(SDL_CONTROLLERDEVICEADDED == ctn::event_type::ControllerDeviceAdded);
  CHECK(SDL_CONTROLLERDEVICEREMOVED ==
        ctn::event_type::ControllerDeviceRemoved);
  CHECK(SDL_CONTROLLERDEVICEREMAPPED ==
        ctn::event_type::ControllerDeviceRemapped);
  CHECK(SDL_FINGERDOWN == ctn::event_type::TouchDown);
  CHECK(SDL_FINGERUP == ctn::event_type::TouchUp);
  CHECK(SDL_FINGERMOTION == ctn::event_type::TouchMotion);
  CHECK(SDL_DOLLARGESTURE == ctn::event_type::DollarGesture);
  CHECK(SDL_DOLLARRECORD == ctn::event_type::DollarRecord);
  CHECK(SDL_MULTIGESTURE == ctn::event_type::MultiGesture);
  CHECK(SDL_CLIPBOARDUPDATE == ctn::event_type::ClipboardUpdate);
  CHECK(SDL_DROPFILE == ctn::event_type::DropFile);
  CHECK(SDL_DROPTEXT == ctn::event_type::DropText);
  CHECK(SDL_DROPBEGIN == ctn::event_type::DropBegin);
  CHECK(SDL_DROPCOMPLETE == ctn::event_type::DropComplete);
  CHECK(SDL_AUDIODEVICEADDED == ctn::event_type::AudioDeviceAdded);
  CHECK(SDL_AUDIODEVICEREMOVED == ctn::event_type::AudioDeviceRemoved);
  CHECK(SDL_SENSORUPDATE == ctn::event_type::SensorUpdate);
  CHECK(SDL_RENDER_TARGETS_RESET == ctn::event_type::RenderTargetsReset);
  CHECK(SDL_RENDER_DEVICE_RESET == ctn::event_type::RenderDeviceReset);
  CHECK(SDL_USEREVENT == ctn::event_type::User);
}

TEST_CASE("event_type operator!=", "[event_type]")
{
  CHECK(ctn::event_type::DollarGesture != SDL_RENDER_DEVICE_RESET);
  CHECK(SDL_MOUSEMOTION != ctn::event_type::ControllerDeviceRemoved);
}

TEST_CASE("event move constructor", "[event]")
{
  CHECK_NOTHROW(ctn::event{{}});
}

TEST_CASE("event::refresh", "[event]")
{
  CHECK_NOTHROW(ctn::event::refresh());
}

TEST_CASE("event::push", "[event]")
{
  ctn::event::flush_all();
  {
    SDL_Event sdlEvent{};
    sdlEvent.type = SDL_KEYDOWN;
    ctn::event event{sdlEvent};
    ctn::event::push(event);
  }

  ctn::event event;
  CHECK(event.poll());
  CHECK(event.type() == ctn::event_type::KeyDown);
}

TEST_CASE("event::flush", "[event]")
{
  ctn::event::refresh();
  ctn::event::flush();

  ctn::event event;
  CHECK(!event.poll());
}

TEST_CASE("event::flush_all", "[event]")
{
  ctn::event::flush_all();

  ctn::event event;
  CHECK(!event.poll());
}

TEST_CASE("event::poll", "[event]")
{
  SDL_Event sdlEvent{};
  sdlEvent.type = SDL_MOUSEMOTION;
  sdlEvent.motion.x = 839;
  sdlEvent.motion.y = 351;

  ctn::event::flush();
  SDL_PushEvent(&sdlEvent);

  ctn::event event;
  CHECK(event.poll());

  REQUIRE(event.type() == ctn::event_type::MouseMotion);
  REQUIRE(event.is<ctn::mouse_motion_event>());

  auto& motionEvent = event.get<ctn::mouse_motion_event>();

  CHECK(motionEvent.x() == sdlEvent.motion.x);
  CHECK(motionEvent.y() == sdlEvent.motion.y);

  ctn::event::flush_all();
}

TEST_CASE("event::type", "[event]")
{
  const auto create_sdl_event = [](ctn::event_type type) noexcept {
    SDL_Event event{};
    event.type = static_cast<ctn::u32>(type);
    return event;
  };

  const auto type = ctn::event_type::TouchMotion;
  auto sdlEvent = create_sdl_event(type);

  ctn::event::flush_all();
  SDL_PushEvent(&sdlEvent);

  ctn::event event;
  CHECK(event.poll());
  CHECK(event.type() == type);

  ctn::event::flush_all();
}

TEST_CASE("event::empty", "[event]")
{
  SECTION("Empty")
  {
    ctn::event event;
    CHECK(event.empty());
  }

  SECTION("Not empty")
  {
    const auto event = create_event(SDL_AUDIODEVICEADDED);
    CHECK(!event.empty());
  }
}

TEST_CASE("event::is", "[event]")
{
  SECTION("AudioDeviceEvent")
  {
    const auto added = create_event(SDL_AUDIODEVICEADDED);
    const auto removed = create_event(SDL_AUDIODEVICEREMOVED);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(added.is<ctn::audio_device_event>());
    CHECK(removed.is<ctn::audio_device_event>());
    CHECK(!wrong.is<ctn::audio_device_event>());
  }

  SECTION("ControllerAxisEvent")
  {
    const auto event = create_event(SDL_CONTROLLERAXISMOTION);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(event.is<ctn::controller_axis_event>());
    CHECK(!wrong.is<ctn::controller_axis_event>());
  }

  SECTION("ControllerButtonEvent")
  {
    const auto up = create_event(SDL_CONTROLLERBUTTONUP);
    const auto down = create_event(SDL_CONTROLLERBUTTONDOWN);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(up.is<ctn::controller_button_event>());
    CHECK(down.is<ctn::controller_button_event>());
    CHECK(!wrong.is<ctn::controller_button_event>());
  }

  SECTION("ControllerDeviceEvent")
  {
    const auto added = create_event(SDL_CONTROLLERDEVICEADDED);
    const auto removed = create_event(SDL_CONTROLLERDEVICEREMOVED);
    const auto remapped = create_event(SDL_CONTROLLERDEVICEREMAPPED);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(added.is<ctn::controller_device_event>());
    CHECK(removed.is<ctn::controller_device_event>());
    CHECK(remapped.is<ctn::controller_device_event>());
    CHECK(!wrong.is<ctn::controller_device_event>());
  }

  SECTION("DollarGestureEvent")
  {
    const auto gesture = create_event(SDL_DOLLARGESTURE);
    const auto record = create_event(SDL_DOLLARRECORD);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(gesture.is<ctn::dollar_gesture_event>());
    CHECK(record.is<ctn::dollar_gesture_event>());
    CHECK(!wrong.is<ctn::dollar_gesture_event>());
  }

  SECTION("DropEvent")
  {
    const auto begin = create_event(SDL_DROPBEGIN);
    const auto complete = create_event(SDL_DROPCOMPLETE);
    const auto file = create_event(SDL_DROPFILE);
    const auto text = create_event(SDL_DROPTEXT);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(begin.is<ctn::drop_event>());
    CHECK(complete.is<ctn::drop_event>());
    CHECK(file.is<ctn::drop_event>());
    CHECK(text.is<ctn::drop_event>());
    CHECK(!wrong.is<ctn::drop_event>());
  }

  SECTION("JoyAxisEvent")
  {
    const auto motion = create_event(SDL_JOYAXISMOTION);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(motion.is<ctn::joy_axis_event>());
    CHECK(!wrong.is<ctn::joy_axis_event>());
  }

  SECTION("JoyBallEvent")
  {
    const auto motion = create_event(SDL_JOYBALLMOTION);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(motion.is<ctn::joy_ball_event>());
    CHECK(!wrong.is<ctn::joy_ball_event>());
  }

  SECTION("JoyButtonEvent")
  {
    const auto up = create_event(SDL_JOYBUTTONUP);
    const auto down = create_event(SDL_JOYBUTTONDOWN);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(up.is<ctn::joy_button_event>());
    CHECK(down.is<ctn::joy_button_event>());
    CHECK(!wrong.is<ctn::joy_button_event>());
  }

  SECTION("JoyDeviceEvent")
  {
    const auto added = create_event(SDL_JOYDEVICEADDED);
    const auto removed = create_event(SDL_JOYDEVICEREMOVED);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(added.is<ctn::joy_device_event>());
    CHECK(removed.is<ctn::joy_device_event>());
    CHECK(!wrong.is<ctn::joy_device_event>());
  }

  SECTION("JoyHatEvent")
  {
    const auto motion = create_event(SDL_JOYHATMOTION);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(motion.is<ctn::joy_hat_event>());
    CHECK(!wrong.is<ctn::joy_hat_event>());
  }

  SECTION("KeyboardEvent")
  {
    const auto up = create_event(SDL_KEYUP);
    const auto down = create_event(SDL_KEYDOWN);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(up.is<ctn::keyboard_event>());
    CHECK(down.is<ctn::keyboard_event>());
    CHECK(!wrong.is<ctn::keyboard_event>());
  }

  SECTION("MouseButtonEvent")
  {
    const auto up = create_event(SDL_MOUSEBUTTONUP);
    const auto down = create_event(SDL_MOUSEBUTTONDOWN);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(up.is<ctn::mouse_button_event>());
    CHECK(down.is<ctn::mouse_button_event>());
    CHECK(!wrong.is<ctn::mouse_button_event>());
  }

  SECTION("MouseMotionEvent")
  {
    const auto motion = create_event(SDL_MOUSEMOTION);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(motion.is<ctn::mouse_motion_event>());
    CHECK(!wrong.is<ctn::mouse_button_event>());
  }

  SECTION("MouseWheelEvent")
  {
    const auto wheel = create_event(SDL_MOUSEWHEEL);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(wheel.is<ctn::mouse_wheel_event>());
    CHECK(!wrong.is<ctn::mouse_wheel_event>());
  }

  SECTION("MultiGestureEvent")
  {
    const auto gesture = create_event(SDL_MULTIGESTURE);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(gesture.is<ctn::multi_gesture_event>());
    CHECK(!wrong.is<ctn::multi_gesture_event>());
  }

  SECTION("QuitEvent")
  {
    const auto quit = create_event(SDL_QUIT);
    const auto wrong = create_event(SDL_KEYUP);

    CHECK(quit.is<ctn::quit_event>());
    CHECK(!wrong.is<ctn::quit_event>());
  }

  SECTION("TextEditingEvent")
  {
    const auto editing = create_event(SDL_TEXTEDITING);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(editing.is<ctn::text_editing_event>());
    CHECK(!wrong.is<ctn::text_editing_event>());
  }

  SECTION("TextInputEvent")
  {
    const auto input = create_event(SDL_TEXTINPUT);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(input.is<ctn::text_input_event>());
    CHECK(!wrong.is<ctn::text_input_event>());
  }

  SECTION("TouchFingerEvent")
  {
    const auto motion = create_event(SDL_FINGERMOTION);
    const auto up = create_event(SDL_FINGERUP);
    const auto down = create_event(SDL_FINGERDOWN);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(motion.is<ctn::touch_finger_event>());
    CHECK(up.is<ctn::touch_finger_event>());
    CHECK(down.is<ctn::touch_finger_event>());
    CHECK(!wrong.is<ctn::touch_finger_event>());
  }

  SECTION("WindowEvent")
  {
    const auto window = create_event(SDL_WINDOWEVENT);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(window.is<ctn::window_event>());
    CHECK(!wrong.is<ctn::window_event>());
  }
}

TEST_CASE("event::get", "[event]")
{
  SECTION("Const")
  {
    const auto quit = create_event(SDL_QUIT);

    CHECK_NOTHROW(quit.get<ctn::quit_event>());
    CHECK_THROWS(quit.get<ctn::window_event>());
  }

  SECTION("Non-const")
  {
    auto quit = create_event(SDL_QUIT);

    CHECK_NOTHROW(quit.get<ctn::quit_event>());
    CHECK_THROWS(quit.get<ctn::window_event>());
  }
}

TEST_CASE("event::try_get", "[event]")
{
  SECTION("Const")
  {
    const auto event = create_event(SDL_MOUSEMOTION);

    CHECK(event.try_get<ctn::mouse_motion_event>());
    CHECK(!event.try_get<ctn::window_event>());
  }

  SECTION("Non-const")
  {
    auto event = create_event(SDL_MULTIGESTURE);

    CHECK(event.try_get<ctn::multi_gesture_event>());
    CHECK(!event.try_get<ctn::joy_hat_event>());
  }
}
