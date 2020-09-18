#include "event.hpp"

#include <catch.hpp>

namespace {

[[nodiscard]] auto create_event(cen::u32 type) -> cen::event
{
  SDL_Event sdlEvent;
  sdlEvent.type = type;
  return {sdlEvent};
}

}  // namespace

TEST_CASE("event_type operator==", "[event_type]")
{
  CHECK(cen::event_type::quit == SDL_EventType::SDL_QUIT);
  CHECK(cen::event_type::app_terminating == SDL_APP_TERMINATING);
  CHECK(cen::event_type::app_low_memory == SDL_APP_LOWMEMORY);
  CHECK(cen::event_type::app_will_enter_background ==
        SDL_APP_WILLENTERBACKGROUND);
  CHECK(cen::event_type::app_did_enter_background ==
        SDL_APP_DIDENTERBACKGROUND);
  CHECK(cen::event_type::app_did_enter_foreground ==
        SDL_APP_DIDENTERFOREGROUND);
  CHECK(cen::event_type::display == SDL_DISPLAYEVENT);
  CHECK(cen::event_type::window == SDL_WINDOWEVENT);
  CHECK(cen::event_type::system == SDL_SYSWMEVENT);
  CHECK(cen::event_type::key_down == SDL_KEYDOWN);
  CHECK(cen::event_type::key_up == SDL_KEYUP);
  CHECK(cen::event_type::text_editing == SDL_TEXTEDITING);
  CHECK(cen::event_type::text_input == SDL_TEXTINPUT);
  CHECK(cen::event_type::keymap_changed == SDL_KEYMAPCHANGED);
  CHECK(cen::event_type::mouse_motion == SDL_MOUSEMOTION);
  CHECK(cen::event_type::mouse_button_down == SDL_MOUSEBUTTONDOWN);
  CHECK(cen::event_type::mouse_button_up == SDL_MOUSEBUTTONUP);
  CHECK(cen::event_type::mouse_wheel == SDL_MOUSEWHEEL);
  CHECK(cen::event_type::joystick_axis_motion == SDL_JOYAXISMOTION);
  CHECK(cen::event_type::joystick_ball_motion == SDL_JOYBALLMOTION);
  CHECK(cen::event_type::joystick_hat_motion == SDL_JOYHATMOTION);
  CHECK(cen::event_type::joystick_button_down == SDL_JOYBUTTONDOWN);
  CHECK(cen::event_type::joystick_button_up == SDL_JOYBUTTONUP);
  CHECK(cen::event_type::joystick_device_added == SDL_JOYDEVICEADDED);
  CHECK(cen::event_type::joystick_device_removed == SDL_JOYDEVICEREMOVED);
  CHECK(cen::event_type::controller_axis_motion == SDL_CONTROLLERAXISMOTION);
  CHECK(cen::event_type::controller_button_down == SDL_CONTROLLERBUTTONDOWN);
  CHECK(cen::event_type::controller_button_up == SDL_CONTROLLERBUTTONUP);
  CHECK(cen::event_type::controller_device_added == SDL_CONTROLLERDEVICEADDED);
  CHECK(cen::event_type::controller_device_removed ==
        SDL_CONTROLLERDEVICEREMOVED);
  CHECK(cen::event_type::controller_device_remapped ==
        SDL_CONTROLLERDEVICEREMAPPED);
  CHECK(cen::event_type::touch_down == SDL_FINGERDOWN);
  CHECK(cen::event_type::touch_up == SDL_FINGERUP);
  CHECK(cen::event_type::touch_motion == SDL_FINGERMOTION);
  CHECK(cen::event_type::dollar_gesture == SDL_DOLLARGESTURE);
  CHECK(cen::event_type::dollar_record == SDL_DOLLARRECORD);
  CHECK(cen::event_type::multi_gesture == SDL_MULTIGESTURE);
  CHECK(cen::event_type::clipboard_update == SDL_CLIPBOARDUPDATE);
  CHECK(cen::event_type::drop_file == SDL_DROPFILE);
  CHECK(cen::event_type::drop_text == SDL_DROPTEXT);
  CHECK(cen::event_type::drop_begin == SDL_DROPBEGIN);
  CHECK(cen::event_type::drop_complete == SDL_DROPCOMPLETE);
  CHECK(cen::event_type::audio_device_added == SDL_AUDIODEVICEADDED);
  CHECK(cen::event_type::audio_device_removed == SDL_AUDIODEVICEREMOVED);
  CHECK(cen::event_type::sensor_update == SDL_SENSORUPDATE);
  CHECK(cen::event_type::render_targets_reset == SDL_RENDER_TARGETS_RESET);
  CHECK(cen::event_type::render_device_reset == SDL_RENDER_DEVICE_RESET);
  CHECK(cen::event_type::user == SDL_USEREVENT);

  CHECK(SDL_QUIT == cen::event_type::quit);
  CHECK(SDL_APP_TERMINATING == cen::event_type::app_terminating);
  CHECK(SDL_APP_LOWMEMORY == cen::event_type::app_low_memory);
  CHECK(SDL_APP_WILLENTERBACKGROUND ==
        cen::event_type::app_will_enter_background);
  CHECK(SDL_APP_DIDENTERBACKGROUND ==
        cen::event_type::app_did_enter_background);
  CHECK(SDL_APP_DIDENTERFOREGROUND ==
        cen::event_type::app_did_enter_foreground);
  CHECK(SDL_DISPLAYEVENT == cen::event_type::display);
  CHECK(SDL_WINDOWEVENT == cen::event_type::window);
  CHECK(SDL_SYSWMEVENT == cen::event_type::system);
  CHECK(SDL_KEYDOWN == cen::event_type::key_down);
  CHECK(SDL_KEYUP == cen::event_type::key_up);
  CHECK(SDL_TEXTEDITING == cen::event_type::text_editing);
  CHECK(SDL_TEXTINPUT == cen::event_type::text_input);
  CHECK(SDL_KEYMAPCHANGED == cen::event_type::keymap_changed);
  CHECK(SDL_MOUSEMOTION == cen::event_type::mouse_motion);
  CHECK(SDL_MOUSEBUTTONDOWN == cen::event_type::mouse_button_down);
  CHECK(SDL_MOUSEBUTTONUP == cen::event_type::mouse_button_up);
  CHECK(SDL_MOUSEWHEEL == cen::event_type::mouse_wheel);
  CHECK(SDL_JOYAXISMOTION == cen::event_type::joystick_axis_motion);
  CHECK(SDL_JOYBALLMOTION == cen::event_type::joystick_ball_motion);
  CHECK(SDL_JOYHATMOTION == cen::event_type::joystick_hat_motion);
  CHECK(SDL_JOYBUTTONDOWN == cen::event_type::joystick_button_down);
  CHECK(SDL_JOYBUTTONUP == cen::event_type::joystick_button_up);
  CHECK(SDL_JOYDEVICEADDED == cen::event_type::joystick_device_added);
  CHECK(SDL_JOYDEVICEREMOVED == cen::event_type::joystick_device_removed);
  CHECK(SDL_CONTROLLERAXISMOTION == cen::event_type::controller_axis_motion);
  CHECK(SDL_CONTROLLERBUTTONDOWN == cen::event_type::controller_button_down);
  CHECK(SDL_CONTROLLERBUTTONUP == cen::event_type::controller_button_up);
  CHECK(SDL_CONTROLLERDEVICEADDED == cen::event_type::controller_device_added);
  CHECK(SDL_CONTROLLERDEVICEREMOVED ==
        cen::event_type::controller_device_removed);
  CHECK(SDL_CONTROLLERDEVICEREMAPPED ==
        cen::event_type::controller_device_remapped);
  CHECK(SDL_FINGERDOWN == cen::event_type::touch_down);
  CHECK(SDL_FINGERUP == cen::event_type::touch_up);
  CHECK(SDL_FINGERMOTION == cen::event_type::touch_motion);
  CHECK(SDL_DOLLARGESTURE == cen::event_type::dollar_gesture);
  CHECK(SDL_DOLLARRECORD == cen::event_type::dollar_record);
  CHECK(SDL_MULTIGESTURE == cen::event_type::multi_gesture);
  CHECK(SDL_CLIPBOARDUPDATE == cen::event_type::clipboard_update);
  CHECK(SDL_DROPFILE == cen::event_type::drop_file);
  CHECK(SDL_DROPTEXT == cen::event_type::drop_text);
  CHECK(SDL_DROPBEGIN == cen::event_type::drop_begin);
  CHECK(SDL_DROPCOMPLETE == cen::event_type::drop_complete);
  CHECK(SDL_AUDIODEVICEADDED == cen::event_type::audio_device_added);
  CHECK(SDL_AUDIODEVICEREMOVED == cen::event_type::audio_device_removed);
  CHECK(SDL_SENSORUPDATE == cen::event_type::sensor_update);
  CHECK(SDL_RENDER_TARGETS_RESET == cen::event_type::render_targets_reset);
  CHECK(SDL_RENDER_DEVICE_RESET == cen::event_type::render_device_reset);
  CHECK(SDL_USEREVENT == cen::event_type::user);
}

TEST_CASE("event_type operator!=", "[event_type]")
{
  CHECK(cen::event_type::dollar_gesture != SDL_RENDER_DEVICE_RESET);
  CHECK(SDL_MOUSEMOTION != cen::event_type::controller_device_removed);
}

TEST_CASE("event move constructor", "[event]")
{
  CHECK_NOTHROW(cen::event{{}});
}

TEST_CASE("event::refresh", "[event]")
{
  CHECK_NOTHROW(cen::event::refresh());
}

TEST_CASE("event::push", "[event]")
{
  cen::event::flush_all();
  {
    SDL_Event sdlEvent{};
    sdlEvent.type = SDL_KEYDOWN;
    cen::event event{sdlEvent};
    cen::event::push(event);
  }

  cen::event event;
  CHECK(event.poll());
  CHECK(event.type() == cen::event_type::key_down);
}

TEST_CASE("event::flush", "[event]")
{
  cen::event::refresh();
  cen::event::flush();

  cen::event event;
  CHECK(!event.poll());
}

TEST_CASE("event::flush_all", "[event]")
{
  cen::event::flush_all();

  cen::event event;
  CHECK(!event.poll());
}

TEST_CASE("event::poll", "[event]")
{
  SDL_Event sdlEvent{};
  sdlEvent.type = SDL_MOUSEMOTION;
  sdlEvent.motion.x = 839;
  sdlEvent.motion.y = 351;

  cen::event::flush();
  SDL_PushEvent(&sdlEvent);

  cen::event event;
  CHECK(event.poll());

  REQUIRE(event.type() == cen::event_type::mouse_motion);
  REQUIRE(event.is<cen::mouse_motion_event>());

  auto& motionEvent = event.get<cen::mouse_motion_event>();

  CHECK(motionEvent.x() == sdlEvent.motion.x);
  CHECK(motionEvent.y() == sdlEvent.motion.y);

  cen::event::flush_all();
}

TEST_CASE("event::type", "[event]")
{
  const auto create_sdl_event = [](cen::event_type type) noexcept {
    SDL_Event event{};
    event.type = static_cast<cen::u32>(type);
    return event;
  };

  const auto type = cen::event_type::touch_motion;
  auto sdlEvent = create_sdl_event(type);

  cen::event::flush_all();
  SDL_PushEvent(&sdlEvent);

  cen::event event;
  CHECK(event.poll());
  CHECK(event.type() == type);

  cen::event::flush_all();
}

TEST_CASE("event::empty", "[event]")
{
  SECTION("Empty")
  {
    cen::event event;
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

    CHECK(added.is<cen::audio_device_event>());
    CHECK(removed.is<cen::audio_device_event>());
    CHECK(!wrong.is<cen::audio_device_event>());
  }

  SECTION("ControllerAxisEvent")
  {
    const auto event = create_event(SDL_CONTROLLERAXISMOTION);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(event.is<cen::controller_axis_event>());
    CHECK(!wrong.is<cen::controller_axis_event>());
  }

  SECTION("ControllerButtonEvent")
  {
    const auto up = create_event(SDL_CONTROLLERBUTTONUP);
    const auto down = create_event(SDL_CONTROLLERBUTTONDOWN);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(up.is<cen::controller_button_event>());
    CHECK(down.is<cen::controller_button_event>());
    CHECK(!wrong.is<cen::controller_button_event>());
  }

  SECTION("ControllerDeviceEvent")
  {
    const auto added = create_event(SDL_CONTROLLERDEVICEADDED);
    const auto removed = create_event(SDL_CONTROLLERDEVICEREMOVED);
    const auto remapped = create_event(SDL_CONTROLLERDEVICEREMAPPED);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(added.is<cen::controller_device_event>());
    CHECK(removed.is<cen::controller_device_event>());
    CHECK(remapped.is<cen::controller_device_event>());
    CHECK(!wrong.is<cen::controller_device_event>());
  }

  SECTION("DollarGestureEvent")
  {
    const auto gesture = create_event(SDL_DOLLARGESTURE);
    const auto record = create_event(SDL_DOLLARRECORD);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(gesture.is<cen::dollar_gesture_event>());
    CHECK(record.is<cen::dollar_gesture_event>());
    CHECK(!wrong.is<cen::dollar_gesture_event>());
  }

  SECTION("DropEvent")
  {
    const auto begin = create_event(SDL_DROPBEGIN);
    const auto complete = create_event(SDL_DROPCOMPLETE);
    const auto file = create_event(SDL_DROPFILE);
    const auto text = create_event(SDL_DROPTEXT);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(begin.is<cen::drop_event>());
    CHECK(complete.is<cen::drop_event>());
    CHECK(file.is<cen::drop_event>());
    CHECK(text.is<cen::drop_event>());
    CHECK(!wrong.is<cen::drop_event>());
  }

  SECTION("JoyAxisEvent")
  {
    const auto motion = create_event(SDL_JOYAXISMOTION);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(motion.is<cen::joy_axis_event>());
    CHECK(!wrong.is<cen::joy_axis_event>());
  }

  SECTION("JoyBallEvent")
  {
    const auto motion = create_event(SDL_JOYBALLMOTION);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(motion.is<cen::joy_ball_event>());
    CHECK(!wrong.is<cen::joy_ball_event>());
  }

  SECTION("JoyButtonEvent")
  {
    const auto up = create_event(SDL_JOYBUTTONUP);
    const auto down = create_event(SDL_JOYBUTTONDOWN);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(up.is<cen::joy_button_event>());
    CHECK(down.is<cen::joy_button_event>());
    CHECK(!wrong.is<cen::joy_button_event>());
  }

  SECTION("JoyDeviceEvent")
  {
    const auto added = create_event(SDL_JOYDEVICEADDED);
    const auto removed = create_event(SDL_JOYDEVICEREMOVED);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(added.is<cen::joy_device_event>());
    CHECK(removed.is<cen::joy_device_event>());
    CHECK(!wrong.is<cen::joy_device_event>());
  }

  SECTION("JoyHatEvent")
  {
    const auto motion = create_event(SDL_JOYHATMOTION);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(motion.is<cen::joy_hat_event>());
    CHECK(!wrong.is<cen::joy_hat_event>());
  }

  SECTION("KeyboardEvent")
  {
    const auto up = create_event(SDL_KEYUP);
    const auto down = create_event(SDL_KEYDOWN);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(up.is<cen::keyboard_event>());
    CHECK(down.is<cen::keyboard_event>());
    CHECK(!wrong.is<cen::keyboard_event>());
  }

  SECTION("mouse_button_event")
  {
    const auto up = create_event(SDL_MOUSEBUTTONUP);
    const auto down = create_event(SDL_MOUSEBUTTONDOWN);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(up.is<cen::mouse_button_event>());
    CHECK(down.is<cen::mouse_button_event>());
    CHECK(!wrong.is<cen::mouse_button_event>());
  }

  SECTION("MouseMotionEvent")
  {
    const auto motion = create_event(SDL_MOUSEMOTION);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(motion.is<cen::mouse_motion_event>());
    CHECK(!wrong.is<cen::mouse_button_event>());
  }

  SECTION("mouse_wheel_event")
  {
    const auto wheel = create_event(SDL_MOUSEWHEEL);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(wheel.is<cen::mouse_wheel_event>());
    CHECK(!wrong.is<cen::mouse_wheel_event>());
  }

  SECTION("MultiGestureEvent")
  {
    const auto gesture = create_event(SDL_MULTIGESTURE);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(gesture.is<cen::multi_gesture_event>());
    CHECK(!wrong.is<cen::multi_gesture_event>());
  }

  SECTION("QuitEvent")
  {
    const auto quit = create_event(SDL_QUIT);
    const auto wrong = create_event(SDL_KEYUP);

    CHECK(quit.is<cen::quit_event>());
    CHECK(!wrong.is<cen::quit_event>());
  }

  SECTION("TextEditingEvent")
  {
    const auto editing = create_event(SDL_TEXTEDITING);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(editing.is<cen::text_editing_event>());
    CHECK(!wrong.is<cen::text_editing_event>());
  }

  SECTION("TextInputEvent")
  {
    const auto input = create_event(SDL_TEXTINPUT);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(input.is<cen::text_input_event>());
    CHECK(!wrong.is<cen::text_input_event>());
  }

  SECTION("TouchFingerEvent")
  {
    const auto motion = create_event(SDL_FINGERMOTION);
    const auto up = create_event(SDL_FINGERUP);
    const auto down = create_event(SDL_FINGERDOWN);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(motion.is<cen::touch_finger_event>());
    CHECK(up.is<cen::touch_finger_event>());
    CHECK(down.is<cen::touch_finger_event>());
    CHECK(!wrong.is<cen::touch_finger_event>());
  }

  SECTION("WindowEvent")
  {
    const auto window = create_event(SDL_WINDOWEVENT);
    const auto wrong = create_event(SDL_QUIT);

    CHECK(window.is<cen::window_event>());
    CHECK(!wrong.is<cen::window_event>());
  }
}

TEST_CASE("event::get", "[event]")
{
  SECTION("Const")
  {
    const auto quit = create_event(SDL_QUIT);

    CHECK_NOTHROW(quit.get<cen::quit_event>());
    CHECK_THROWS(quit.get<cen::window_event>());
  }

  SECTION("Non-const")
  {
    auto quit = create_event(SDL_QUIT);

    CHECK_NOTHROW(quit.get<cen::quit_event>());
    CHECK_THROWS(quit.get<cen::window_event>());
  }
}

TEST_CASE("event::try_get", "[event]")
{
  SECTION("Const")
  {
    const auto event = create_event(SDL_MOUSEMOTION);

    CHECK(event.try_get<cen::mouse_motion_event>());
    CHECK(!event.try_get<cen::window_event>());
  }

  SECTION("Non-const")
  {
    auto event = create_event(SDL_MULTIGESTURE);

    CHECK(event.try_get<cen::multi_gesture_event>());
    CHECK(!event.try_get<cen::joy_hat_event>());
  }
}
