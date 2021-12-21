#include "event.hpp"

#include <gtest/gtest.h>

#include <type_traits>

namespace {

[[nodiscard]] auto CreateEvent(const Uint32 type) -> cen::Event
{
  SDL_Event event;
  event.type = type;
  return cen::Event{event};
}

template <typename T, typename E>
[[nodiscard]] constexpr auto ValidateEvent() noexcept -> bool
{
  return !std::has_virtual_destructor_v<T> && std::is_nothrow_copy_constructible_v<T> &&
         std::is_nothrow_copy_assignable_v<T> && std::is_nothrow_move_constructible_v<T> &&
         std::is_nothrow_move_assignable_v<T> && std::is_nothrow_constructible_v<T, E> &&
         std::is_final_v<T>;
}

}  // namespace

static_assert(ValidateEvent<cen::AudioDeviceEvent, SDL_AudioDeviceEvent>());
static_assert(ValidateEvent<cen::ControllerAxisEvent, SDL_ControllerAxisEvent>());
static_assert(ValidateEvent<cen::ControllerButtonEvent, SDL_ControllerButtonEvent>());
static_assert(ValidateEvent<cen::ControllerDeviceEvent, SDL_ControllerDeviceEvent>());
static_assert(ValidateEvent<cen::dollar_gesture_event, SDL_DollarGestureEvent>());
static_assert(ValidateEvent<cen::DropEvent, SDL_DropEvent>());
static_assert(ValidateEvent<cen::JoyAxisEvent, SDL_JoyAxisEvent>());
static_assert(ValidateEvent<cen::JoyBallEvent, SDL_JoyBallEvent>());
static_assert(ValidateEvent<cen::JoyButtonEvent, SDL_JoyButtonEvent>());
static_assert(ValidateEvent<cen::JoyDeviceEvent, SDL_JoyDeviceEvent>());
static_assert(ValidateEvent<cen::JoyHatEvent, SDL_JoyHatEvent>());
static_assert(ValidateEvent<cen::keyboard_event, SDL_KeyboardEvent>());
static_assert(ValidateEvent<cen::MouseButtonEvent, SDL_MouseButtonEvent>());
static_assert(ValidateEvent<cen::MouseMotionEvent, SDL_MouseMotionEvent>());
static_assert(ValidateEvent<cen::MouseWheelEvent, SDL_MouseWheelEvent>());
static_assert(ValidateEvent<cen::multi_gesture_event, SDL_MultiGestureEvent>());
static_assert(ValidateEvent<cen::quit_event, SDL_QuitEvent>());
static_assert(ValidateEvent<cen::text_editing_event, SDL_TextEditingEvent>());
static_assert(ValidateEvent<cen::text_input_event, SDL_TextInputEvent>());
static_assert(ValidateEvent<cen::touch_finger_event, SDL_TouchFingerEvent>());
static_assert(ValidateEvent<cen::WindowEvent, SDL_WindowEvent>());
static_assert(ValidateEvent<cen::sensor_event, SDL_SensorEvent>());
static_assert(ValidateEvent<cen::user_event, SDL_UserEvent>());

#if SDL_VERSION_ATLEAST(2, 0, 14)
static_assert(ValidateEvent<cen::DisplayEvent, SDL_DisplayEvent>());
static_assert(ValidateEvent<cen::ControllerTouchpadEvent, SDL_ControllerTouchpadEvent>());
static_assert(ValidateEvent<cen::ControllerSensorEvent, SDL_ControllerSensorEvent>());
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

TEST(Event, Push)
{
  cen::Event::FlushAll();

  {
    auto event = CreateEvent(SDL_KEYDOWN);
    cen::Event::Push(event);
  }

  cen::Event event;
  ASSERT_TRUE(event.Poll());
  ASSERT_EQ(cen::EventType::KeyDown, event.GetType());

  {
    const cen::WindowEvent windowEvent;
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
  ASSERT_TRUE(event.Is<cen::MouseMotionEvent>());

  auto& motionEvent = event.Get<cen::MouseMotionEvent>();
  ASSERT_EQ(sdl.motion.x, motionEvent.GetX());
  ASSERT_EQ(sdl.motion.y, motionEvent.GetY());

  cen::Event::FlushAll();
}

TEST(Event, GetQueueSize)
{
  cen::Event::FlushAll();
  ASSERT_EQ(0, cen::Event::GetQueueSize());
  ASSERT_EQ(0, cen::Event::GetQueueSize(cen::EventType::Quit));

  auto event = CreateEvent(SDL_QUIT);
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

  const auto notEmpty = CreateEvent(SDL_AUDIODEVICEADDED);
  ASSERT_FALSE(notEmpty.IsEmpty());
}

TEST(Event, Is)
{
  {  // audio_device_event
    const auto added = CreateEvent(SDL_AUDIODEVICEADDED);
    const auto removed = CreateEvent(SDL_AUDIODEVICEREMOVED);
    const auto wrong = CreateEvent(SDL_QUIT);

    ASSERT_TRUE(added.Is<cen::AudioDeviceEvent>());
    ASSERT_TRUE(removed.Is<cen::AudioDeviceEvent>());
    ASSERT_FALSE(wrong.Is<cen::AudioDeviceEvent>());
  }

  {  // controller_axis_event
    const auto event = CreateEvent(SDL_CONTROLLERAXISMOTION);
    const auto wrong = CreateEvent(SDL_QUIT);

    ASSERT_TRUE(event.Is<cen::ControllerAxisEvent>());
    ASSERT_FALSE(wrong.Is<cen::ControllerAxisEvent>());
  }

  {  // controller_button_event
    const auto up = CreateEvent(SDL_CONTROLLERBUTTONUP);
    const auto down = CreateEvent(SDL_CONTROLLERBUTTONDOWN);
    const auto wrong = CreateEvent(SDL_QUIT);

    ASSERT_TRUE(up.Is<cen::ControllerButtonEvent>());
    ASSERT_TRUE(down.Is<cen::ControllerButtonEvent>());
    ASSERT_FALSE(wrong.Is<cen::ControllerButtonEvent>());
  }

  {  // controller_device_event
    const auto added = CreateEvent(SDL_CONTROLLERDEVICEADDED);
    const auto removed = CreateEvent(SDL_CONTROLLERDEVICEREMOVED);
    const auto remapped = CreateEvent(SDL_CONTROLLERDEVICEREMAPPED);
    const auto wrong = CreateEvent(SDL_QUIT);

    ASSERT_TRUE(added.Is<cen::ControllerDeviceEvent>());
    ASSERT_TRUE(removed.Is<cen::ControllerDeviceEvent>());
    ASSERT_TRUE(remapped.Is<cen::ControllerDeviceEvent>());
    ASSERT_FALSE(wrong.Is<cen::ControllerDeviceEvent>());
  }

  {  // dollar_gesture_event
    const auto gesture = CreateEvent(SDL_DOLLARGESTURE);
    const auto record = CreateEvent(SDL_DOLLARRECORD);
    const auto wrong = CreateEvent(SDL_QUIT);

    ASSERT_TRUE(gesture.Is<cen::dollar_gesture_event>());
    ASSERT_TRUE(record.Is<cen::dollar_gesture_event>());
    ASSERT_FALSE(wrong.Is<cen::dollar_gesture_event>());
  }

  {  // drop_event
    const auto begin = CreateEvent(SDL_DROPBEGIN);
    const auto complete = CreateEvent(SDL_DROPCOMPLETE);
    const auto file = CreateEvent(SDL_DROPFILE);
    const auto text = CreateEvent(SDL_DROPTEXT);
    const auto wrong = CreateEvent(SDL_QUIT);

    ASSERT_TRUE(begin.Is<cen::DropEvent>());
    ASSERT_TRUE(complete.Is<cen::DropEvent>());
    ASSERT_TRUE(file.Is<cen::DropEvent>());
    ASSERT_TRUE(text.Is<cen::DropEvent>());
    ASSERT_FALSE(wrong.Is<cen::DropEvent>());
  }

  {  // joy_axis_event
    const auto motion = CreateEvent(SDL_JOYAXISMOTION);
    const auto wrong = CreateEvent(SDL_QUIT);

    ASSERT_TRUE(motion.Is<cen::JoyAxisEvent>());
    ASSERT_FALSE(wrong.Is<cen::JoyAxisEvent>());
  }

  {  // joy_ball_event
    const auto motion = CreateEvent(SDL_JOYBALLMOTION);
    const auto wrong = CreateEvent(SDL_QUIT);

    ASSERT_TRUE(motion.Is<cen::JoyBallEvent>());
    ASSERT_FALSE(wrong.Is<cen::JoyBallEvent>());
  }

  {  // joy_button_event
    const auto up = CreateEvent(SDL_JOYBUTTONUP);
    const auto down = CreateEvent(SDL_JOYBUTTONDOWN);
    const auto wrong = CreateEvent(SDL_QUIT);

    ASSERT_TRUE(up.Is<cen::JoyButtonEvent>());
    ASSERT_TRUE(down.Is<cen::JoyButtonEvent>());
    ASSERT_FALSE(wrong.Is<cen::JoyButtonEvent>());
  }

  {  // joy_device_event
    const auto added = CreateEvent(SDL_JOYDEVICEADDED);
    const auto removed = CreateEvent(SDL_JOYDEVICEREMOVED);
    const auto wrong = CreateEvent(SDL_QUIT);

    ASSERT_TRUE(added.Is<cen::JoyDeviceEvent>());
    ASSERT_TRUE(removed.Is<cen::JoyDeviceEvent>());
    ASSERT_FALSE(wrong.Is<cen::JoyDeviceEvent>());
  }

  {  // joy_hat_event
    const auto motion = CreateEvent(SDL_JOYHATMOTION);
    const auto wrong = CreateEvent(SDL_QUIT);

    ASSERT_TRUE(motion.Is<cen::JoyHatEvent>());
    ASSERT_FALSE(wrong.Is<cen::JoyHatEvent>());
  }

  {  // keyboard_event
    const auto up = CreateEvent(SDL_KEYUP);
    const auto down = CreateEvent(SDL_KEYDOWN);
    const auto wrong = CreateEvent(SDL_QUIT);

    ASSERT_TRUE(up.Is<cen::keyboard_event>());
    ASSERT_TRUE(down.Is<cen::keyboard_event>());
    ASSERT_FALSE(wrong.Is<cen::keyboard_event>());
  }

  {  // mouse_button_event
    const auto up = CreateEvent(SDL_MOUSEBUTTONUP);
    const auto down = CreateEvent(SDL_MOUSEBUTTONDOWN);
    const auto wrong = CreateEvent(SDL_QUIT);

    ASSERT_TRUE(up.Is<cen::MouseButtonEvent>());
    ASSERT_TRUE(down.Is<cen::MouseButtonEvent>());
    ASSERT_FALSE(wrong.Is<cen::MouseButtonEvent>());
  }

  {  // mouse_motion_event
    const auto motion = CreateEvent(SDL_MOUSEMOTION);
    const auto wrong = CreateEvent(SDL_QUIT);

    ASSERT_TRUE(motion.Is<cen::MouseMotionEvent>());
    ASSERT_FALSE(wrong.Is<cen::MouseButtonEvent>());
  }

  {  // mouse_wheel_event
    const auto wheel = CreateEvent(SDL_MOUSEWHEEL);
    const auto wrong = CreateEvent(SDL_QUIT);

    ASSERT_TRUE(wheel.Is<cen::MouseWheelEvent>());
    ASSERT_FALSE(wrong.Is<cen::MouseWheelEvent>());
  }

  {  // multi_gesture_event
    const auto gesture = CreateEvent(SDL_MULTIGESTURE);
    const auto wrong = CreateEvent(SDL_QUIT);

    ASSERT_TRUE(gesture.Is<cen::multi_gesture_event>());
    ASSERT_FALSE(wrong.Is<cen::multi_gesture_event>());
  }

  {  // quit_event
    const auto quit = CreateEvent(SDL_QUIT);
    const auto wrong = CreateEvent(SDL_KEYUP);

    ASSERT_TRUE(quit.Is<cen::quit_event>());
    ASSERT_FALSE(wrong.Is<cen::quit_event>());
  }

  {  // text_editing_event
    const auto editing = CreateEvent(SDL_TEXTEDITING);
    const auto wrong = CreateEvent(SDL_QUIT);

    ASSERT_TRUE(editing.Is<cen::text_editing_event>());
    ASSERT_FALSE(wrong.Is<cen::text_editing_event>());
  }

  {  // text_input_event
    const auto input = CreateEvent(SDL_TEXTINPUT);
    const auto wrong = CreateEvent(SDL_QUIT);

    ASSERT_TRUE(input.Is<cen::text_input_event>());
    ASSERT_FALSE(wrong.Is<cen::text_input_event>());
  }

  {  // touch_finger_event
    const auto motion = CreateEvent(SDL_FINGERMOTION);
    const auto up = CreateEvent(SDL_FINGERUP);
    const auto down = CreateEvent(SDL_FINGERDOWN);
    const auto wrong = CreateEvent(SDL_QUIT);

    ASSERT_TRUE(motion.Is<cen::touch_finger_event>());
    ASSERT_TRUE(up.Is<cen::touch_finger_event>());
    ASSERT_TRUE(down.Is<cen::touch_finger_event>());
    ASSERT_FALSE(wrong.Is<cen::touch_finger_event>());
  }

  {  // window_event
    const auto window = CreateEvent(SDL_WINDOWEVENT);
    const auto wrong = CreateEvent(SDL_QUIT);

    ASSERT_TRUE(window.Is<cen::WindowEvent>());
    ASSERT_FALSE(wrong.Is<cen::WindowEvent>());
  }
}

TEST(Event, Get)
{
  auto event = CreateEvent(SDL_QUIT);
  ASSERT_NO_THROW(event.Get<cen::quit_event>());
  ASSERT_ANY_THROW(event.Get<cen::WindowEvent>());

  const auto& cEvent = event;
  ASSERT_NO_THROW(cEvent.Get<cen::quit_event>());
  ASSERT_ANY_THROW(cEvent.Get<cen::WindowEvent>());
}

TEST(Event, TryGet)
{
  auto event = CreateEvent(SDL_MOUSEMOTION);
  ASSERT_TRUE(event.TryGet<cen::MouseMotionEvent>());
  ASSERT_FALSE(event.TryGet<cen::WindowEvent>());

  const auto& cEvent = event;
  ASSERT_TRUE(cEvent.TryGet<cen::MouseMotionEvent>());
  ASSERT_FALSE(cEvent.TryGet<cen::WindowEvent>());
}

TEST(Event, Data)
{
  cen::Event event;
  ASSERT_TRUE(event.data());
}