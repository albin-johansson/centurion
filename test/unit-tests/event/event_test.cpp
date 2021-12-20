#include "events/event.hpp"

#include <gtest/gtest.h>

#include <type_traits>

namespace {

[[nodiscard]] auto create_event(const Uint32 type) -> cen::Event
{
  SDL_Event sdlEvent;
  sdlEvent.type = type;
  return cen::Event{sdlEvent};
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
  return !std::has_virtual_destructor_v<T> && std::is_nothrow_copy_constructible_v<T> &&
         std::is_nothrow_copy_assignable_v<T> && std::is_nothrow_move_constructible_v<T> &&
         std::is_nothrow_move_assignable_v<T> && std::is_nothrow_constructible_v<T, E> &&
         std::is_final_v<T>;
}

}  // namespace

// clang-format off
static_assert(validate_event<cen::AudioDeviceEvent, SDL_AudioDeviceEvent>());
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
static_assert(validate_event<cen::sensor_event, SDL_SensorEvent>());
static_assert(validate_event<cen::user_event, SDL_UserEvent>());

#if SDL_VERSION_ATLEAST(2, 0, 14)
static_assert(validate_event<cen::display_event, SDL_DisplayEvent>());
static_assert(validate_event<cen::controller_touchpad_event, SDL_ControllerTouchpadEvent>());
static_assert(validate_event<cen::controller_sensor_event, SDL_ControllerSensorEvent>());
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

// clang-format on

TEST(Event, Push)
{
  cen::Event::FlushAll();

  {
    auto event = create_event(SDL_KEYDOWN);
    cen::Event::Push(event);
  }

  cen::Event event;
  ASSERT_TRUE(event.Poll());
  ASSERT_EQ(cen::EventType::KeyDown, event.GetType());

  {
    const cen::window_event windowEvent;
    cen::Event::Push(windowEvent);
  }

  ASSERT_TRUE(event.Poll());
  ASSERT_EQ(cen::EventType::Window, event.GetType());
}

TEST(Event, Flush)
{
  cen::Event::Update();
  cen::Event::Flush();

  cen::Event event;
  ASSERT_FALSE(event.Poll());
}

TEST(Event, FlushAll)
{
  cen::Event::FlushAll();

  cen::Event event;
  ASSERT_FALSE(event.Poll());
}

TEST(Event, Poll)
{
  SDL_Event sdl{};
  sdl.type = SDL_MOUSEMOTION;
  sdl.motion.x = 839;
  sdl.motion.y = 351;

  cen::Event::Flush();
  SDL_PushEvent(&sdl);

  cen::Event event;
  ASSERT_TRUE(event.Poll());

  ASSERT_EQ(cen::EventType::MouseMotion, event.GetType());
  ASSERT_TRUE(event.Is<cen::mouse_motion_event>());

  auto& motionEvent = event.Get<cen::mouse_motion_event>();
  ASSERT_EQ(sdl.motion.x, motionEvent.x());
  ASSERT_EQ(sdl.motion.y, motionEvent.y());

  cen::Event::FlushAll();
}

TEST(Event, GetQueueSize)
{
  cen::Event::FlushAll();
  ASSERT_EQ(0, cen::Event::GetQueueSize());
  ASSERT_EQ(0, cen::Event::GetQueueSize(cen::EventType::Quit));

  auto event = create_event(SDL_QUIT);
  cen::Event::Push(event);

  ASSERT_EQ(1, cen::Event::GetQueueSize());
  ASSERT_EQ(1, cen::Event::GetQueueSize(cen::EventType::Quit));
  ASSERT_EQ(0, cen::Event::GetQueueSize(cen::EventType::Window));
}

TEST(Event, InQueue)
{
  cen::Event::FlushAll();
  ASSERT_FALSE(cen::Event::InQueue(cen::EventType::Quit));

  cen::quit_event qe;
  cen::Event::Push(qe);

  ASSERT_TRUE(cen::Event::InQueue(cen::EventType::Quit));
  ASSERT_FALSE(cen::Event::InQueue(cen::EventType::Window));

  cen::Event::FlushAll();
  ASSERT_FALSE(cen::Event::InQueue(cen::EventType::Quit));
}

TEST(Event, Type)
{
  SDL_Event sdl{};
  sdl.type = SDL_FINGERMOTION;

  cen::Event::FlushAll();
  SDL_PushEvent(&sdl);

  cen::Event event;
  ASSERT_TRUE(event.Poll());
  ASSERT_EQ(cen::EventType::FingerMotion, event.GetType());

  cen::Event::FlushAll();
}

TEST(Event, IsEmpty)
{
  cen::Event empty;
  ASSERT_TRUE(empty.IsEmpty());

  const auto notEmpty = create_event(SDL_AUDIODEVICEADDED);
  ASSERT_FALSE(notEmpty.IsEmpty());
}

TEST(Event, Is)
{
  {  // audio_device_event
    const auto added = create_event(SDL_AUDIODEVICEADDED);
    const auto removed = create_event(SDL_AUDIODEVICEREMOVED);
    const auto wrong = create_event(SDL_QUIT);

    ASSERT_TRUE(added.Is<cen::AudioDeviceEvent>());
    ASSERT_TRUE(removed.Is<cen::AudioDeviceEvent>());
    ASSERT_FALSE(wrong.Is<cen::AudioDeviceEvent>());
  }

  {  // controller_axis_event
    const auto event = create_event(SDL_CONTROLLERAXISMOTION);
    const auto wrong = create_event(SDL_QUIT);

    ASSERT_TRUE(event.Is<cen::controller_axis_event>());
    ASSERT_FALSE(wrong.Is<cen::controller_axis_event>());
  }

  {  // controller_button_event
    const auto up = create_event(SDL_CONTROLLERBUTTONUP);
    const auto down = create_event(SDL_CONTROLLERBUTTONDOWN);
    const auto wrong = create_event(SDL_QUIT);

    ASSERT_TRUE(up.Is<cen::controller_button_event>());
    ASSERT_TRUE(down.Is<cen::controller_button_event>());
    ASSERT_FALSE(wrong.Is<cen::controller_button_event>());
  }

  {  // controller_device_event
    const auto added = create_event(SDL_CONTROLLERDEVICEADDED);
    const auto removed = create_event(SDL_CONTROLLERDEVICEREMOVED);
    const auto remapped = create_event(SDL_CONTROLLERDEVICEREMAPPED);
    const auto wrong = create_event(SDL_QUIT);

    ASSERT_TRUE(added.Is<cen::controller_device_event>());
    ASSERT_TRUE(removed.Is<cen::controller_device_event>());
    ASSERT_TRUE(remapped.Is<cen::controller_device_event>());
    ASSERT_FALSE(wrong.Is<cen::controller_device_event>());
  }

  {  // dollar_gesture_event
    const auto gesture = create_event(SDL_DOLLARGESTURE);
    const auto record = create_event(SDL_DOLLARRECORD);
    const auto wrong = create_event(SDL_QUIT);

    ASSERT_TRUE(gesture.Is<cen::dollar_gesture_event>());
    ASSERT_TRUE(record.Is<cen::dollar_gesture_event>());
    ASSERT_FALSE(wrong.Is<cen::dollar_gesture_event>());
  }

  {  // drop_event
    const auto begin = create_event(SDL_DROPBEGIN);
    const auto complete = create_event(SDL_DROPCOMPLETE);
    const auto file = create_event(SDL_DROPFILE);
    const auto text = create_event(SDL_DROPTEXT);
    const auto wrong = create_event(SDL_QUIT);

    ASSERT_TRUE(begin.Is<cen::drop_event>());
    ASSERT_TRUE(complete.Is<cen::drop_event>());
    ASSERT_TRUE(file.Is<cen::drop_event>());
    ASSERT_TRUE(text.Is<cen::drop_event>());
    ASSERT_FALSE(wrong.Is<cen::drop_event>());
  }

  {  // joy_axis_event
    const auto motion = create_event(SDL_JOYAXISMOTION);
    const auto wrong = create_event(SDL_QUIT);

    ASSERT_TRUE(motion.Is<cen::joy_axis_event>());
    ASSERT_FALSE(wrong.Is<cen::joy_axis_event>());
  }

  {  // joy_ball_event
    const auto motion = create_event(SDL_JOYBALLMOTION);
    const auto wrong = create_event(SDL_QUIT);

    ASSERT_TRUE(motion.Is<cen::joy_ball_event>());
    ASSERT_FALSE(wrong.Is<cen::joy_ball_event>());
  }

  {  // joy_button_event
    const auto up = create_event(SDL_JOYBUTTONUP);
    const auto down = create_event(SDL_JOYBUTTONDOWN);
    const auto wrong = create_event(SDL_QUIT);

    ASSERT_TRUE(up.Is<cen::joy_button_event>());
    ASSERT_TRUE(down.Is<cen::joy_button_event>());
    ASSERT_FALSE(wrong.Is<cen::joy_button_event>());
  }

  {  // joy_device_event
    const auto added = create_event(SDL_JOYDEVICEADDED);
    const auto removed = create_event(SDL_JOYDEVICEREMOVED);
    const auto wrong = create_event(SDL_QUIT);

    ASSERT_TRUE(added.Is<cen::joy_device_event>());
    ASSERT_TRUE(removed.Is<cen::joy_device_event>());
    ASSERT_FALSE(wrong.Is<cen::joy_device_event>());
  }

  {  // joy_hat_event
    const auto motion = create_event(SDL_JOYHATMOTION);
    const auto wrong = create_event(SDL_QUIT);

    ASSERT_TRUE(motion.Is<cen::joy_hat_event>());
    ASSERT_FALSE(wrong.Is<cen::joy_hat_event>());
  }

  {  // keyboard_event
    const auto up = create_event(SDL_KEYUP);
    const auto down = create_event(SDL_KEYDOWN);
    const auto wrong = create_event(SDL_QUIT);

    ASSERT_TRUE(up.Is<cen::keyboard_event>());
    ASSERT_TRUE(down.Is<cen::keyboard_event>());
    ASSERT_FALSE(wrong.Is<cen::keyboard_event>());
  }

  {  // mouse_button_event
    const auto up = create_event(SDL_MOUSEBUTTONUP);
    const auto down = create_event(SDL_MOUSEBUTTONDOWN);
    const auto wrong = create_event(SDL_QUIT);

    ASSERT_TRUE(up.Is<cen::mouse_button_event>());
    ASSERT_TRUE(down.Is<cen::mouse_button_event>());
    ASSERT_FALSE(wrong.Is<cen::mouse_button_event>());
  }

  {  // mouse_motion_event
    const auto motion = create_event(SDL_MOUSEMOTION);
    const auto wrong = create_event(SDL_QUIT);

    ASSERT_TRUE(motion.Is<cen::mouse_motion_event>());
    ASSERT_FALSE(wrong.Is<cen::mouse_button_event>());
  }

  {  // mouse_wheel_event
    const auto wheel = create_event(SDL_MOUSEWHEEL);
    const auto wrong = create_event(SDL_QUIT);

    ASSERT_TRUE(wheel.Is<cen::mouse_wheel_event>());
    ASSERT_FALSE(wrong.Is<cen::mouse_wheel_event>());
  }

  {  // multi_gesture_event
    const auto gesture = create_event(SDL_MULTIGESTURE);
    const auto wrong = create_event(SDL_QUIT);

    ASSERT_TRUE(gesture.Is<cen::multi_gesture_event>());
    ASSERT_FALSE(wrong.Is<cen::multi_gesture_event>());
  }

  {  // quit_event
    const auto quit = create_event(SDL_QUIT);
    const auto wrong = create_event(SDL_KEYUP);

    ASSERT_TRUE(quit.Is<cen::quit_event>());
    ASSERT_FALSE(wrong.Is<cen::quit_event>());
  }

  {  // text_editing_event
    const auto editing = create_event(SDL_TEXTEDITING);
    const auto wrong = create_event(SDL_QUIT);

    ASSERT_TRUE(editing.Is<cen::text_editing_event>());
    ASSERT_FALSE(wrong.Is<cen::text_editing_event>());
  }

  {  // text_input_event
    const auto input = create_event(SDL_TEXTINPUT);
    const auto wrong = create_event(SDL_QUIT);

    ASSERT_TRUE(input.Is<cen::text_input_event>());
    ASSERT_FALSE(wrong.Is<cen::text_input_event>());
  }

  {  // touch_finger_event
    const auto motion = create_event(SDL_FINGERMOTION);
    const auto up = create_event(SDL_FINGERUP);
    const auto down = create_event(SDL_FINGERDOWN);
    const auto wrong = create_event(SDL_QUIT);

    ASSERT_TRUE(motion.Is<cen::touch_finger_event>());
    ASSERT_TRUE(up.Is<cen::touch_finger_event>());
    ASSERT_TRUE(down.Is<cen::touch_finger_event>());
    ASSERT_FALSE(wrong.Is<cen::touch_finger_event>());
  }

  {  // window_event
    const auto window = create_event(SDL_WINDOWEVENT);
    const auto wrong = create_event(SDL_QUIT);

    ASSERT_TRUE(window.Is<cen::window_event>());
    ASSERT_FALSE(wrong.Is<cen::window_event>());
  }
}

TEST(Event, Get)
{
  auto event = create_event(SDL_QUIT);
  ASSERT_NO_THROW(event.Get<cen::quit_event>());
  ASSERT_ANY_THROW(event.Get<cen::window_event>());

  const auto& cEvent = event;
  ASSERT_NO_THROW(cEvent.Get<cen::quit_event>());
  ASSERT_ANY_THROW(cEvent.Get<cen::window_event>());
}

TEST(Event, TryGet)
{
  auto event = create_event(SDL_MOUSEMOTION);
  ASSERT_TRUE(event.TryGet<cen::mouse_motion_event>());
  ASSERT_FALSE(event.TryGet<cen::window_event>());

  const auto& cEvent = event;
  ASSERT_TRUE(cEvent.TryGet<cen::mouse_motion_event>());
  ASSERT_FALSE(cEvent.TryGet<cen::window_event>());
}

TEST(Event, Data)
{
  cen::Event event;
  ASSERT_TRUE(event.data());
}