#include "event.hpp"

#include <gtest/gtest.h>

#include <type_traits>

namespace {

[[nodiscard]] auto CreateEvent(const Uint32 type) -> cen::event_handler
{
  SDL_Event event;
  event.type = type;
  return cen::event_handler{event};
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
static_assert(ValidateEvent<cen::KeyboardEvent, SDL_KeyboardEvent>());
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
static_assert(ValidateEvent<cen::UserEvent, SDL_UserEvent>());

#if SDL_VERSION_ATLEAST(2, 0, 14)
static_assert(ValidateEvent<cen::DisplayEvent, SDL_DisplayEvent>());
static_assert(ValidateEvent<cen::ControllerTouchpadEvent, SDL_ControllerTouchpadEvent>());
static_assert(ValidateEvent<cen::ControllerSensorEvent, SDL_ControllerSensorEvent>());
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

TEST(Event, Push)
{
  cen::event_handler::flush_all();

  {
    auto event = CreateEvent(SDL_KEYDOWN);
    cen::event_handler::push(event);
  }

  cen::event_handler event;
  ASSERT_TRUE(event.poll());
  ASSERT_EQ(cen::EventType::KeyDown, event.type());

  {
    const cen::WindowEvent windowEvent;
    cen::event_handler::push(windowEvent);
  }

  ASSERT_TRUE(event.poll());
  ASSERT_EQ(cen::EventType::Window, event.type());
}

TEST(Event, Flush)
{
  cen::event_handler::update();
  cen::event_handler::flush();

  cen::event_handler event;
  ASSERT_FALSE(event.poll());
}

TEST(Event, FlushAll)
{
  cen::event_handler::flush_all();

  cen::event_handler event;
  ASSERT_FALSE(event.poll());
}

TEST(Event, Poll)
{
  SDL_Event sdl{};
  sdl.type = SDL_MOUSEMOTION;
  sdl.motion.x = 839;
  sdl.motion.y = 351;

  cen::event_handler::flush();
  SDL_PushEvent(&sdl);

  cen::event_handler event;
  ASSERT_TRUE(event.poll());

  ASSERT_EQ(cen::EventType::MouseMotion, event.type());
  ASSERT_TRUE(event.is<cen::MouseMotionEvent>());

  auto& motionEvent = event.get<cen::MouseMotionEvent>();
  ASSERT_EQ(sdl.motion.x, motionEvent.GetX());
  ASSERT_EQ(sdl.motion.y, motionEvent.GetY());

  cen::event_handler::flush_all();
}

TEST(Event, GetQueueSize)
{
  cen::event_handler::flush_all();
  ASSERT_EQ(0, cen::event_handler::queue_count());
  ASSERT_EQ(0, cen::event_handler::queue_count(cen::EventType::Quit));

  auto event = CreateEvent(SDL_QUIT);
  cen::event_handler::push(event);

  ASSERT_EQ(1, cen::event_handler::queue_count());
  ASSERT_EQ(1, cen::event_handler::queue_count(cen::EventType::Quit));
  ASSERT_EQ(0, cen::event_handler::queue_count(cen::EventType::Window));
}

TEST(Event, InQueue)
{
  cen::event_handler::flush_all();
  ASSERT_FALSE(cen::event_handler::in_queue(cen::EventType::Quit));

  cen::quit_event qe;
  cen::event_handler::push(qe);

  ASSERT_TRUE(cen::event_handler::in_queue(cen::EventType::Quit));
  ASSERT_FALSE(cen::event_handler::in_queue(cen::EventType::Window));

  cen::event_handler::flush_all();
  ASSERT_FALSE(cen::event_handler::in_queue(cen::EventType::Quit));
}

TEST(Event, Type)
{
  SDL_Event sdl{};
  sdl.type = SDL_FINGERMOTION;

  cen::event_handler::flush_all();
  SDL_PushEvent(&sdl);

  cen::event_handler event;
  ASSERT_TRUE(event.poll());
  ASSERT_EQ(cen::EventType::FingerMotion, event.type());

  cen::event_handler::flush_all();
}

TEST(Event, IsEmpty)
{
  cen::event_handler empty;
  ASSERT_TRUE(empty.empty());

  const auto notEmpty = CreateEvent(SDL_AUDIODEVICEADDED);
  ASSERT_FALSE(notEmpty.empty());
}

TEST(Event, Is)
{
  {  // audio_device_event
    const auto added = CreateEvent(SDL_AUDIODEVICEADDED);
    const auto removed = CreateEvent(SDL_AUDIODEVICEREMOVED);
    const auto wrong = CreateEvent(SDL_QUIT);

    ASSERT_TRUE(added.is<cen::AudioDeviceEvent>());
    ASSERT_TRUE(removed.is<cen::AudioDeviceEvent>());
    ASSERT_FALSE(wrong.is<cen::AudioDeviceEvent>());
  }

  {  // controller_axis_event
    const auto event = CreateEvent(SDL_CONTROLLERAXISMOTION);
    const auto wrong = CreateEvent(SDL_QUIT);

    ASSERT_TRUE(event.is<cen::ControllerAxisEvent>());
    ASSERT_FALSE(wrong.is<cen::ControllerAxisEvent>());
  }

  {  // controller_button_event
    const auto up = CreateEvent(SDL_CONTROLLERBUTTONUP);
    const auto down = CreateEvent(SDL_CONTROLLERBUTTONDOWN);
    const auto wrong = CreateEvent(SDL_QUIT);

    ASSERT_TRUE(up.is<cen::ControllerButtonEvent>());
    ASSERT_TRUE(down.is<cen::ControllerButtonEvent>());
    ASSERT_FALSE(wrong.is<cen::ControllerButtonEvent>());
  }

  {  // controller_device_event
    const auto added = CreateEvent(SDL_CONTROLLERDEVICEADDED);
    const auto removed = CreateEvent(SDL_CONTROLLERDEVICEREMOVED);
    const auto remapped = CreateEvent(SDL_CONTROLLERDEVICEREMAPPED);
    const auto wrong = CreateEvent(SDL_QUIT);

    ASSERT_TRUE(added.is<cen::ControllerDeviceEvent>());
    ASSERT_TRUE(removed.is<cen::ControllerDeviceEvent>());
    ASSERT_TRUE(remapped.is<cen::ControllerDeviceEvent>());
    ASSERT_FALSE(wrong.is<cen::ControllerDeviceEvent>());
  }

  {  // dollar_gesture_event
    const auto gesture = CreateEvent(SDL_DOLLARGESTURE);
    const auto record = CreateEvent(SDL_DOLLARRECORD);
    const auto wrong = CreateEvent(SDL_QUIT);

    ASSERT_TRUE(gesture.is<cen::dollar_gesture_event>());
    ASSERT_TRUE(record.is<cen::dollar_gesture_event>());
    ASSERT_FALSE(wrong.is<cen::dollar_gesture_event>());
  }

  {  // drop_event
    const auto begin = CreateEvent(SDL_DROPBEGIN);
    const auto complete = CreateEvent(SDL_DROPCOMPLETE);
    const auto file = CreateEvent(SDL_DROPFILE);
    const auto text = CreateEvent(SDL_DROPTEXT);
    const auto wrong = CreateEvent(SDL_QUIT);

    ASSERT_TRUE(begin.is<cen::DropEvent>());
    ASSERT_TRUE(complete.is<cen::DropEvent>());
    ASSERT_TRUE(file.is<cen::DropEvent>());
    ASSERT_TRUE(text.is<cen::DropEvent>());
    ASSERT_FALSE(wrong.is<cen::DropEvent>());
  }

  {  // joy_axis_event
    const auto motion = CreateEvent(SDL_JOYAXISMOTION);
    const auto wrong = CreateEvent(SDL_QUIT);

    ASSERT_TRUE(motion.is<cen::JoyAxisEvent>());
    ASSERT_FALSE(wrong.is<cen::JoyAxisEvent>());
  }

  {  // joy_ball_event
    const auto motion = CreateEvent(SDL_JOYBALLMOTION);
    const auto wrong = CreateEvent(SDL_QUIT);

    ASSERT_TRUE(motion.is<cen::JoyBallEvent>());
    ASSERT_FALSE(wrong.is<cen::JoyBallEvent>());
  }

  {  // joy_button_event
    const auto up = CreateEvent(SDL_JOYBUTTONUP);
    const auto down = CreateEvent(SDL_JOYBUTTONDOWN);
    const auto wrong = CreateEvent(SDL_QUIT);

    ASSERT_TRUE(up.is<cen::JoyButtonEvent>());
    ASSERT_TRUE(down.is<cen::JoyButtonEvent>());
    ASSERT_FALSE(wrong.is<cen::JoyButtonEvent>());
  }

  {  // joy_device_event
    const auto added = CreateEvent(SDL_JOYDEVICEADDED);
    const auto removed = CreateEvent(SDL_JOYDEVICEREMOVED);
    const auto wrong = CreateEvent(SDL_QUIT);

    ASSERT_TRUE(added.is<cen::JoyDeviceEvent>());
    ASSERT_TRUE(removed.is<cen::JoyDeviceEvent>());
    ASSERT_FALSE(wrong.is<cen::JoyDeviceEvent>());
  }

  {  // joy_hat_event
    const auto motion = CreateEvent(SDL_JOYHATMOTION);
    const auto wrong = CreateEvent(SDL_QUIT);

    ASSERT_TRUE(motion.is<cen::JoyHatEvent>());
    ASSERT_FALSE(wrong.is<cen::JoyHatEvent>());
  }

  {  // keyboard_event
    const auto up = CreateEvent(SDL_KEYUP);
    const auto down = CreateEvent(SDL_KEYDOWN);
    const auto wrong = CreateEvent(SDL_QUIT);

    ASSERT_TRUE(up.is<cen::KeyboardEvent>());
    ASSERT_TRUE(down.is<cen::KeyboardEvent>());
    ASSERT_FALSE(wrong.is<cen::KeyboardEvent>());
  }

  {  // mouse_button_event
    const auto up = CreateEvent(SDL_MOUSEBUTTONUP);
    const auto down = CreateEvent(SDL_MOUSEBUTTONDOWN);
    const auto wrong = CreateEvent(SDL_QUIT);

    ASSERT_TRUE(up.is<cen::MouseButtonEvent>());
    ASSERT_TRUE(down.is<cen::MouseButtonEvent>());
    ASSERT_FALSE(wrong.is<cen::MouseButtonEvent>());
  }

  {  // mouse_motion_event
    const auto motion = CreateEvent(SDL_MOUSEMOTION);
    const auto wrong = CreateEvent(SDL_QUIT);

    ASSERT_TRUE(motion.is<cen::MouseMotionEvent>());
    ASSERT_FALSE(wrong.is<cen::MouseButtonEvent>());
  }

  {  // mouse_wheel_event
    const auto wheel = CreateEvent(SDL_MOUSEWHEEL);
    const auto wrong = CreateEvent(SDL_QUIT);

    ASSERT_TRUE(wheel.is<cen::MouseWheelEvent>());
    ASSERT_FALSE(wrong.is<cen::MouseWheelEvent>());
  }

  {  // multi_gesture_event
    const auto gesture = CreateEvent(SDL_MULTIGESTURE);
    const auto wrong = CreateEvent(SDL_QUIT);

    ASSERT_TRUE(gesture.is<cen::multi_gesture_event>());
    ASSERT_FALSE(wrong.is<cen::multi_gesture_event>());
  }

  {  // quit_event
    const auto quit = CreateEvent(SDL_QUIT);
    const auto wrong = CreateEvent(SDL_KEYUP);

    ASSERT_TRUE(quit.is<cen::quit_event>());
    ASSERT_FALSE(wrong.is<cen::quit_event>());
  }

  {  // text_editing_event
    const auto editing = CreateEvent(SDL_TEXTEDITING);
    const auto wrong = CreateEvent(SDL_QUIT);

    ASSERT_TRUE(editing.is<cen::text_editing_event>());
    ASSERT_FALSE(wrong.is<cen::text_editing_event>());
  }

  {  // text_input_event
    const auto input = CreateEvent(SDL_TEXTINPUT);
    const auto wrong = CreateEvent(SDL_QUIT);

    ASSERT_TRUE(input.is<cen::text_input_event>());
    ASSERT_FALSE(wrong.is<cen::text_input_event>());
  }

  {  // touch_finger_event
    const auto motion = CreateEvent(SDL_FINGERMOTION);
    const auto up = CreateEvent(SDL_FINGERUP);
    const auto down = CreateEvent(SDL_FINGERDOWN);
    const auto wrong = CreateEvent(SDL_QUIT);

    ASSERT_TRUE(motion.is<cen::touch_finger_event>());
    ASSERT_TRUE(up.is<cen::touch_finger_event>());
    ASSERT_TRUE(down.is<cen::touch_finger_event>());
    ASSERT_FALSE(wrong.is<cen::touch_finger_event>());
  }

  {  // window_event
    const auto window = CreateEvent(SDL_WINDOWEVENT);
    const auto wrong = CreateEvent(SDL_QUIT);

    ASSERT_TRUE(window.is<cen::WindowEvent>());
    ASSERT_FALSE(wrong.is<cen::WindowEvent>());
  }
}

TEST(Event, Get)
{
  auto event = CreateEvent(SDL_QUIT);
  ASSERT_NO_THROW(event.get<cen::quit_event>());
  ASSERT_ANY_THROW(event.get<cen::WindowEvent>());

  const auto& cEvent = event;
  ASSERT_NO_THROW(cEvent.get<cen::quit_event>());
  ASSERT_ANY_THROW(cEvent.get<cen::WindowEvent>());
}

TEST(Event, TryGet)
{
  auto event = CreateEvent(SDL_MOUSEMOTION);
  ASSERT_TRUE(event.try_get<cen::MouseMotionEvent>());
  ASSERT_FALSE(event.try_get<cen::WindowEvent>());

  const auto& cEvent = event;
  ASSERT_TRUE(cEvent.try_get<cen::MouseMotionEvent>());
  ASSERT_FALSE(cEvent.try_get<cen::WindowEvent>());
}

TEST(Event, Data)
{
  cen::event_handler event;
  ASSERT_TRUE(event.data());
}