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
  CHECK(ctn::event_type::quit == SDL_EventType::SDL_QUIT);
  CHECK(ctn::event_type::app_terminating == SDL_APP_TERMINATING);
  CHECK(ctn::event_type::app_low_memory == SDL_APP_LOWMEMORY);
  CHECK(ctn::event_type::app_will_enter_background ==
        SDL_APP_WILLENTERBACKGROUND);
  CHECK(ctn::event_type::app_did_enter_background ==
        SDL_APP_DIDENTERBACKGROUND);
  CHECK(ctn::event_type::app_did_enter_foreground ==
        SDL_APP_DIDENTERFOREGROUND);
  CHECK(ctn::event_type::display == SDL_DISPLAYEVENT);
  CHECK(ctn::event_type::window == SDL_WINDOWEVENT);
  CHECK(ctn::event_type::system == SDL_SYSWMEVENT);
  CHECK(ctn::event_type::key_down == SDL_KEYDOWN);
  CHECK(ctn::event_type::key_up == SDL_KEYUP);
  CHECK(ctn::event_type::text_editing == SDL_TEXTEDITING);
  CHECK(ctn::event_type::text_input == SDL_TEXTINPUT);
  CHECK(ctn::event_type::keymap_changed == SDL_KEYMAPCHANGED);
  CHECK(ctn::event_type::mouse_motion == SDL_MOUSEMOTION);
  CHECK(ctn::event_type::mouse_button_down == SDL_MOUSEBUTTONDOWN);
  CHECK(ctn::event_type::mouse_button_up == SDL_MOUSEBUTTONUP);
  CHECK(ctn::event_type::mouse_wheel == SDL_MOUSEWHEEL);
  CHECK(ctn::event_type::joystick_axis_motion == SDL_JOYAXISMOTION);
  CHECK(ctn::event_type::joystick_ball_motion == SDL_JOYBALLMOTION);
  CHECK(ctn::event_type::joystick_hat_motion == SDL_JOYHATMOTION);
  CHECK(ctn::event_type::joystick_button_down == SDL_JOYBUTTONDOWN);
  CHECK(ctn::event_type::joystick_button_up == SDL_JOYBUTTONUP);
  CHECK(ctn::event_type::joystick_device_added == SDL_JOYDEVICEADDED);
  CHECK(ctn::event_type::joystick_device_removed == SDL_JOYDEVICEREMOVED);
  CHECK(ctn::event_type::controller_axis_motion == SDL_CONTROLLERAXISMOTION);
  CHECK(ctn::event_type::controller_button_down == SDL_CONTROLLERBUTTONDOWN);
  CHECK(ctn::event_type::controller_button_up == SDL_CONTROLLERBUTTONUP);
  CHECK(ctn::event_type::controller_device_added == SDL_CONTROLLERDEVICEADDED);
  CHECK(ctn::event_type::controller_device_removed ==
        SDL_CONTROLLERDEVICEREMOVED);
  CHECK(ctn::event_type::controller_device_remapped ==
        SDL_CONTROLLERDEVICEREMAPPED);
  CHECK(ctn::event_type::touch_down == SDL_FINGERDOWN);
  CHECK(ctn::event_type::touch_up == SDL_FINGERUP);
  CHECK(ctn::event_type::touch_motion == SDL_FINGERMOTION);
  CHECK(ctn::event_type::dollar_gesture == SDL_DOLLARGESTURE);
  CHECK(ctn::event_type::dollar_record == SDL_DOLLARRECORD);
  CHECK(ctn::event_type::multi_gesture == SDL_MULTIGESTURE);
  CHECK(ctn::event_type::clipboard_update == SDL_CLIPBOARDUPDATE);
  CHECK(ctn::event_type::drop_file == SDL_DROPFILE);
  CHECK(ctn::event_type::drop_text == SDL_DROPTEXT);
  CHECK(ctn::event_type::drop_begin == SDL_DROPBEGIN);
  CHECK(ctn::event_type::drop_complete == SDL_DROPCOMPLETE);
  CHECK(ctn::event_type::audio_device_added == SDL_AUDIODEVICEADDED);
  CHECK(ctn::event_type::audio_device_removed == SDL_AUDIODEVICEREMOVED);
  CHECK(ctn::event_type::sensor_update == SDL_SENSORUPDATE);
  CHECK(ctn::event_type::render_targets_reset == SDL_RENDER_TARGETS_RESET);
  CHECK(ctn::event_type::render_device_reset == SDL_RENDER_DEVICE_RESET);
  CHECK(ctn::event_type::user == SDL_USEREVENT);

  CHECK(SDL_QUIT == ctn::event_type::quit);
  CHECK(SDL_APP_TERMINATING == ctn::event_type::app_terminating);
  CHECK(SDL_APP_LOWMEMORY == ctn::event_type::app_low_memory);
  CHECK(SDL_APP_WILLENTERBACKGROUND ==
        ctn::event_type::app_will_enter_background);
  CHECK(SDL_APP_DIDENTERBACKGROUND ==
        ctn::event_type::app_did_enter_background);
  CHECK(SDL_APP_DIDENTERFOREGROUND ==
        ctn::event_type::app_did_enter_foreground);
  CHECK(SDL_DISPLAYEVENT == ctn::event_type::display);
  CHECK(SDL_WINDOWEVENT == ctn::event_type::window);
  CHECK(SDL_SYSWMEVENT == ctn::event_type::system);
  CHECK(SDL_KEYDOWN == ctn::event_type::key_down);
  CHECK(SDL_KEYUP == ctn::event_type::key_up);
  CHECK(SDL_TEXTEDITING == ctn::event_type::text_editing);
  CHECK(SDL_TEXTINPUT == ctn::event_type::text_input);
  CHECK(SDL_KEYMAPCHANGED == ctn::event_type::keymap_changed);
  CHECK(SDL_MOUSEMOTION == ctn::event_type::mouse_motion);
  CHECK(SDL_MOUSEBUTTONDOWN == ctn::event_type::mouse_button_down);
  CHECK(SDL_MOUSEBUTTONUP == ctn::event_type::mouse_button_up);
  CHECK(SDL_MOUSEWHEEL == ctn::event_type::mouse_wheel);
  CHECK(SDL_JOYAXISMOTION == ctn::event_type::joystick_axis_motion);
  CHECK(SDL_JOYBALLMOTION == ctn::event_type::joystick_ball_motion);
  CHECK(SDL_JOYHATMOTION == ctn::event_type::joystick_hat_motion);
  CHECK(SDL_JOYBUTTONDOWN == ctn::event_type::joystick_button_down);
  CHECK(SDL_JOYBUTTONUP == ctn::event_type::joystick_button_up);
  CHECK(SDL_JOYDEVICEADDED == ctn::event_type::joystick_device_added);
  CHECK(SDL_JOYDEVICEREMOVED == ctn::event_type::joystick_device_removed);
  CHECK(SDL_CONTROLLERAXISMOTION == ctn::event_type::controller_axis_motion);
  CHECK(SDL_CONTROLLERBUTTONDOWN == ctn::event_type::controller_button_down);
  CHECK(SDL_CONTROLLERBUTTONUP == ctn::event_type::controller_button_up);
  CHECK(SDL_CONTROLLERDEVICEADDED == ctn::event_type::controller_device_added);
  CHECK(SDL_CONTROLLERDEVICEREMOVED ==
        ctn::event_type::controller_device_removed);
  CHECK(SDL_CONTROLLERDEVICEREMAPPED ==
        ctn::event_type::controller_device_remapped);
  CHECK(SDL_FINGERDOWN == ctn::event_type::touch_down);
  CHECK(SDL_FINGERUP == ctn::event_type::touch_up);
  CHECK(SDL_FINGERMOTION == ctn::event_type::touch_motion);
  CHECK(SDL_DOLLARGESTURE == ctn::event_type::dollar_gesture);
  CHECK(SDL_DOLLARRECORD == ctn::event_type::dollar_record);
  CHECK(SDL_MULTIGESTURE == ctn::event_type::multi_gesture);
  CHECK(SDL_CLIPBOARDUPDATE == ctn::event_type::clipboard_update);
  CHECK(SDL_DROPFILE == ctn::event_type::drop_file);
  CHECK(SDL_DROPTEXT == ctn::event_type::drop_text);
  CHECK(SDL_DROPBEGIN == ctn::event_type::drop_begin);
  CHECK(SDL_DROPCOMPLETE == ctn::event_type::drop_complete);
  CHECK(SDL_AUDIODEVICEADDED == ctn::event_type::audio_device_added);
  CHECK(SDL_AUDIODEVICEREMOVED == ctn::event_type::audio_device_removed);
  CHECK(SDL_SENSORUPDATE == ctn::event_type::sensor_update);
  CHECK(SDL_RENDER_TARGETS_RESET == ctn::event_type::render_targets_reset);
  CHECK(SDL_RENDER_DEVICE_RESET == ctn::event_type::render_device_reset);
  CHECK(SDL_USEREVENT == ctn::event_type::user);
}

TEST_CASE("event_type operator!=", "[event_type]")
{
  CHECK(ctn::event_type::dollar_gesture != SDL_RENDER_DEVICE_RESET);
  CHECK(SDL_MOUSEMOTION != ctn::event_type::controller_device_removed);
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
  CHECK(event.type() == ctn::event_type::key_down);
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

  REQUIRE(event.type() == ctn::event_type::mouse_motion);
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

  const auto type = ctn::event_type::touch_motion;
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
