#include "event.hpp"

#include <gtest/gtest.h>

#include <type_traits>

namespace {

[[nodiscard]] auto create_event(cen::u32 type) -> cen::event
{
  SDL_Event sdlEvent;
  sdlEvent.type = type;
  return cen::event{sdlEvent};
}

/**
 * \brief Indicates whether or not a Centurion event type fulfills the event
 * type specification.
 *
 * \ingroup event
 *
 * \tparam T the Centurion event type that will be checked.
 * \tparam E the SDL event type that the Centurion event is mirroring.
 *
 * \return `true` if the supplied event type passed the requirements; `false`
 * otherwise.
 *
 * \since 4.0.0
 */
template <typename T, typename E>
[[nodiscard]] constexpr auto validate_event() noexcept -> bool
{
  return !std::has_virtual_destructor_v<T> &&
         std::is_nothrow_copy_constructible_v<T> &&
         std::is_nothrow_copy_assignable_v<T> &&
         std::is_nothrow_move_constructible_v<T> &&
         std::is_nothrow_move_assignable_v<T> &&
         std::is_nothrow_constructible_v<T, E> && std::is_final_v<T>;
}

}  // namespace

// clang-format off
static_assert(validate_event<cen::audio_device_event, SDL_AudioDeviceEvent>());
static_assert(validate_event<cen::controller_axis_event, SDL_ControllerAxisEvent>());
static_assert(validate_event<cen::controller_button_event, SDL_ControllerButtonEvent>());
static_assert(validate_event<cen::controller_device_event, SDL_ControllerDeviceEvent>());
static_assert(validate_event<cen::dollar_gesture_event, SDL_DollarGestureEvent>());
static_assert(validate_event<cen::drop_event, SDL_DropEvent>());
static_assert(validate_event<cen::joy_axis_event, SDL_JoyAxisEvent>());
static_assert(validate_event<cen::joy_ball_event, SDL_JoyBallEvent>());
static_assert(validate_event<cen::joy_button_event, SDL_JoyButtonEvent>());
static_assert(validate_event<cen::joy_device_event, SDL_JoyDeviceEvent>());
static_assert(validate_event<cen::joy_hat_event, SDL_JoyHatEvent>());
static_assert(validate_event<cen::keyboard_event, SDL_KeyboardEvent>());
static_assert(validate_event<cen::mouse_button_event, SDL_MouseButtonEvent>());
static_assert(validate_event<cen::mouse_motion_event, SDL_MouseMotionEvent>());
static_assert(validate_event<cen::mouse_wheel_event, SDL_MouseWheelEvent>());
static_assert(validate_event<cen::multi_gesture_event, SDL_MultiGestureEvent>());
static_assert(validate_event<cen::quit_event, SDL_QuitEvent>());
static_assert(validate_event<cen::text_editing_event, SDL_TextEditingEvent>());
static_assert(validate_event<cen::text_input_event, SDL_TextInputEvent>());
static_assert(validate_event<cen::touch_finger_event, SDL_TouchFingerEvent>());
static_assert(validate_event<cen::window_event, SDL_WindowEvent>());
// clang-format on

// TODO this class is suitable for mocking tests

TEST(Event, Refresh)
{
  EXPECT_NO_THROW(cen::event::refresh());
}

TEST(Event, Push)
{
  cen::event::flush_all();

  {
    auto event = create_event(SDL_KEYDOWN);
    cen::event::push(event);
  }

  cen::event event;
  EXPECT_TRUE(event.poll());
  EXPECT_EQ(cen::event_type::key_down, event.type());
}

TEST(Event, Flush)
{
  cen::event::refresh();
  cen::event::flush();

  cen::event event;
  EXPECT_FALSE(event.poll());
}

TEST(Event, FlushAll)
{
  cen::event::flush_all();

  cen::event event;
  EXPECT_FALSE(event.poll());
}

TEST(Event, Poll)
{
  SDL_Event sdl{};
  sdl.type = SDL_MOUSEMOTION;
  sdl.motion.x = 839;
  sdl.motion.y = 351;

  cen::event::flush();
  SDL_PushEvent(&sdl);

  cen::event event;
  EXPECT_TRUE(event.poll());

  ASSERT_EQ(cen::event_type::mouse_motion, event.type());
  ASSERT_TRUE(event.is<cen::mouse_motion_event>());

  auto& motionEvent = event.get<cen::mouse_motion_event>();
  EXPECT_EQ(sdl.motion.x, motionEvent.x());
  EXPECT_EQ(sdl.motion.y, motionEvent.y());

  cen::event::flush_all();
}

TEST(Event, NumQueued)
{
  cen::event::flush_all();
  EXPECT_EQ(0, cen::event::num_queued());
  EXPECT_EQ(0, cen::event::num_queued(cen::event_type::quit));

  auto event = create_event(SDL_QUIT);
  cen::event::push(event);

  EXPECT_EQ(1, cen::event::num_queued());
  EXPECT_EQ(1, cen::event::num_queued(cen::event_type::quit));
  EXPECT_EQ(0, cen::event::num_queued(cen::event_type::window));
}

TEST(Event, Type)
{
  SDL_Event sdl{};
  sdl.type = SDL_FINGERMOTION;

  cen::event::flush_all();
  SDL_PushEvent(&sdl);

  cen::event event;
  EXPECT_TRUE(event.poll());
  EXPECT_EQ(cen::event_type::touch_motion, event.type());

  cen::event::flush_all();
}

TEST(Event, Empty)
{
  cen::event empty;
  EXPECT_TRUE(empty.empty());

  const auto notEmpty = create_event(SDL_AUDIODEVICEADDED);
  EXPECT_FALSE(notEmpty.empty());
}

TEST(Event, Is)
{
  {  // audio_device_event
    const auto added = create_event(SDL_AUDIODEVICEADDED);
    const auto removed = create_event(SDL_AUDIODEVICEREMOVED);
    const auto wrong = create_event(SDL_QUIT);

    EXPECT_TRUE(added.is<cen::audio_device_event>());
    EXPECT_TRUE(removed.is<cen::audio_device_event>());
    EXPECT_FALSE(wrong.is<cen::audio_device_event>());
  }

  {  // controller_axis_event
    const auto event = create_event(SDL_CONTROLLERAXISMOTION);
    const auto wrong = create_event(SDL_QUIT);

    EXPECT_TRUE(event.is<cen::controller_axis_event>());
    EXPECT_FALSE(wrong.is<cen::controller_axis_event>());
  }

  {  // controller_button_event
    const auto up = create_event(SDL_CONTROLLERBUTTONUP);
    const auto down = create_event(SDL_CONTROLLERBUTTONDOWN);
    const auto wrong = create_event(SDL_QUIT);

    EXPECT_TRUE(up.is<cen::controller_button_event>());
    EXPECT_TRUE(down.is<cen::controller_button_event>());
    EXPECT_FALSE(wrong.is<cen::controller_button_event>());
  }

  {  // controller_device_event
    const auto added = create_event(SDL_CONTROLLERDEVICEADDED);
    const auto removed = create_event(SDL_CONTROLLERDEVICEREMOVED);
    const auto remapped = create_event(SDL_CONTROLLERDEVICEREMAPPED);
    const auto wrong = create_event(SDL_QUIT);

    EXPECT_TRUE(added.is<cen::controller_device_event>());
    EXPECT_TRUE(removed.is<cen::controller_device_event>());
    EXPECT_TRUE(remapped.is<cen::controller_device_event>());
    EXPECT_FALSE(wrong.is<cen::controller_device_event>());
  }

  {  // dollar_gesture_event
    const auto gesture = create_event(SDL_DOLLARGESTURE);
    const auto record = create_event(SDL_DOLLARRECORD);
    const auto wrong = create_event(SDL_QUIT);

    EXPECT_TRUE(gesture.is<cen::dollar_gesture_event>());
    EXPECT_TRUE(record.is<cen::dollar_gesture_event>());
    EXPECT_FALSE(wrong.is<cen::dollar_gesture_event>());
  }

  {  // drop_event
    const auto begin = create_event(SDL_DROPBEGIN);
    const auto complete = create_event(SDL_DROPCOMPLETE);
    const auto file = create_event(SDL_DROPFILE);
    const auto text = create_event(SDL_DROPTEXT);
    const auto wrong = create_event(SDL_QUIT);

    EXPECT_TRUE(begin.is<cen::drop_event>());
    EXPECT_TRUE(complete.is<cen::drop_event>());
    EXPECT_TRUE(file.is<cen::drop_event>());
    EXPECT_TRUE(text.is<cen::drop_event>());
    EXPECT_FALSE(wrong.is<cen::drop_event>());
  }

  {  // joy_axis_event
    const auto motion = create_event(SDL_JOYAXISMOTION);
    const auto wrong = create_event(SDL_QUIT);

    EXPECT_TRUE(motion.is<cen::joy_axis_event>());
    EXPECT_FALSE(wrong.is<cen::joy_axis_event>());
  }

  {  // joy_ball_event
    const auto motion = create_event(SDL_JOYBALLMOTION);
    const auto wrong = create_event(SDL_QUIT);

    EXPECT_TRUE(motion.is<cen::joy_ball_event>());
    EXPECT_FALSE(wrong.is<cen::joy_ball_event>());
  }

  {  // joy_button_event
    const auto up = create_event(SDL_JOYBUTTONUP);
    const auto down = create_event(SDL_JOYBUTTONDOWN);
    const auto wrong = create_event(SDL_QUIT);

    EXPECT_TRUE(up.is<cen::joy_button_event>());
    EXPECT_TRUE(down.is<cen::joy_button_event>());
    EXPECT_FALSE(wrong.is<cen::joy_button_event>());
  }

  {  // joy_device_event
    const auto added = create_event(SDL_JOYDEVICEADDED);
    const auto removed = create_event(SDL_JOYDEVICEREMOVED);
    const auto wrong = create_event(SDL_QUIT);

    EXPECT_TRUE(added.is<cen::joy_device_event>());
    EXPECT_TRUE(removed.is<cen::joy_device_event>());
    EXPECT_FALSE(wrong.is<cen::joy_device_event>());
  }

  {  // joy_hat_event
    const auto motion = create_event(SDL_JOYHATMOTION);
    const auto wrong = create_event(SDL_QUIT);

    EXPECT_TRUE(motion.is<cen::joy_hat_event>());
    EXPECT_FALSE(wrong.is<cen::joy_hat_event>());
  }

  {  // keyboard_event
    const auto up = create_event(SDL_KEYUP);
    const auto down = create_event(SDL_KEYDOWN);
    const auto wrong = create_event(SDL_QUIT);

    EXPECT_TRUE(up.is<cen::keyboard_event>());
    EXPECT_TRUE(down.is<cen::keyboard_event>());
    EXPECT_FALSE(wrong.is<cen::keyboard_event>());
  }

  {  // mouse_button_event
    const auto up = create_event(SDL_MOUSEBUTTONUP);
    const auto down = create_event(SDL_MOUSEBUTTONDOWN);
    const auto wrong = create_event(SDL_QUIT);

    EXPECT_TRUE(up.is<cen::mouse_button_event>());
    EXPECT_TRUE(down.is<cen::mouse_button_event>());
    EXPECT_FALSE(wrong.is<cen::mouse_button_event>());
  }

  {  // mouse_motion_event
    const auto motion = create_event(SDL_MOUSEMOTION);
    const auto wrong = create_event(SDL_QUIT);

    EXPECT_TRUE(motion.is<cen::mouse_motion_event>());
    EXPECT_FALSE(wrong.is<cen::mouse_button_event>());
  }

  {  // mouse_wheel_event
    const auto wheel = create_event(SDL_MOUSEWHEEL);
    const auto wrong = create_event(SDL_QUIT);

    EXPECT_TRUE(wheel.is<cen::mouse_wheel_event>());
    EXPECT_FALSE(wrong.is<cen::mouse_wheel_event>());
  }

  {  // multi_gesture_event
    const auto gesture = create_event(SDL_MULTIGESTURE);
    const auto wrong = create_event(SDL_QUIT);

    EXPECT_TRUE(gesture.is<cen::multi_gesture_event>());
    EXPECT_FALSE(wrong.is<cen::multi_gesture_event>());
  }

  {  // quit_event
    const auto quit = create_event(SDL_QUIT);
    const auto wrong = create_event(SDL_KEYUP);

    EXPECT_TRUE(quit.is<cen::quit_event>());
    EXPECT_FALSE(wrong.is<cen::quit_event>());
  }

  {  // text_editing_event
    const auto editing = create_event(SDL_TEXTEDITING);
    const auto wrong = create_event(SDL_QUIT);

    EXPECT_TRUE(editing.is<cen::text_editing_event>());
    EXPECT_FALSE(wrong.is<cen::text_editing_event>());
  }

  {  // text_input_event
    const auto input = create_event(SDL_TEXTINPUT);
    const auto wrong = create_event(SDL_QUIT);

    EXPECT_TRUE(input.is<cen::text_input_event>());
    EXPECT_FALSE(wrong.is<cen::text_input_event>());
  }

  {  // touch_finger_event
    const auto motion = create_event(SDL_FINGERMOTION);
    const auto up = create_event(SDL_FINGERUP);
    const auto down = create_event(SDL_FINGERDOWN);
    const auto wrong = create_event(SDL_QUIT);

    EXPECT_TRUE(motion.is<cen::touch_finger_event>());
    EXPECT_TRUE(up.is<cen::touch_finger_event>());
    EXPECT_TRUE(down.is<cen::touch_finger_event>());
    EXPECT_FALSE(wrong.is<cen::touch_finger_event>());
  }

  {  // window_event
    const auto window = create_event(SDL_WINDOWEVENT);
    const auto wrong = create_event(SDL_QUIT);

    EXPECT_TRUE(window.is<cen::window_event>());
    EXPECT_FALSE(wrong.is<cen::window_event>());
  }
}

TEST(Event, Get)
{
  auto event = create_event(SDL_QUIT);
  EXPECT_NO_THROW(event.get<cen::quit_event>());
  EXPECT_ANY_THROW(event.get<cen::window_event>());

  const auto& cEvent = event;
  EXPECT_NO_THROW(cEvent.get<cen::quit_event>());
  EXPECT_ANY_THROW(cEvent.get<cen::window_event>());
}

TEST(Event, TryGet)
{
  auto event = create_event(SDL_MOUSEMOTION);
  EXPECT_TRUE(event.try_get<cen::mouse_motion_event>());
  EXPECT_FALSE(event.try_get<cen::window_event>());

  const auto& cEvent = event;
  EXPECT_TRUE(cEvent.try_get<cen::mouse_motion_event>());
  EXPECT_FALSE(cEvent.try_get<cen::window_event>());
}
