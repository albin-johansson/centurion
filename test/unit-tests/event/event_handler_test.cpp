/*
 * MIT License
 *
 * Copyright (c) 2019-2022 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <gtest/gtest.h>

#include <type_traits>

#include "centurion/event.hpp"

namespace {

template <typename T, typename E>
[[nodiscard]] constexpr auto validate() noexcept -> bool
{
  return !std::has_virtual_destructor_v<T> && std::is_nothrow_copy_constructible_v<T> &&
         std::is_nothrow_copy_assignable_v<T> && std::is_nothrow_move_constructible_v<T> &&
         std::is_nothrow_move_assignable_v<T> && std::is_nothrow_constructible_v<T, E> &&
         std::is_final_v<T>;
}

}  // namespace

static_assert(validate<cen::audio_device_event, SDL_AudioDeviceEvent>());

static_assert(validate<cen::controller_axis_event, SDL_ControllerAxisEvent>());
static_assert(validate<cen::controller_button_event, SDL_ControllerButtonEvent>());
static_assert(validate<cen::controller_device_event, SDL_ControllerDeviceEvent>());

static_assert(validate<cen::dollar_gesture_event, SDL_DollarGestureEvent>());
static_assert(validate<cen::multi_gesture_event, SDL_MultiGestureEvent>());

static_assert(validate<cen::drop_event, SDL_DropEvent>());

static_assert(validate<cen::joy_axis_event, SDL_JoyAxisEvent>());
static_assert(validate<cen::joy_ball_event, SDL_JoyBallEvent>());
static_assert(validate<cen::joy_button_event, SDL_JoyButtonEvent>());
static_assert(validate<cen::joy_device_event, SDL_JoyDeviceEvent>());
static_assert(validate<cen::joy_hat_event, SDL_JoyHatEvent>());

static_assert(validate<cen::keyboard_event, SDL_KeyboardEvent>());
static_assert(validate<cen::mouse_button_event, SDL_MouseButtonEvent>());
static_assert(validate<cen::mouse_motion_event, SDL_MouseMotionEvent>());
static_assert(validate<cen::mouse_wheel_event, SDL_MouseWheelEvent>());
static_assert(validate<cen::touch_finger_event, SDL_TouchFingerEvent>());

static_assert(validate<cen::text_editing_event, SDL_TextEditingEvent>());
static_assert(validate<cen::text_input_event, SDL_TextInputEvent>());

static_assert(validate<cen::window_event, SDL_WindowEvent>());
static_assert(validate<cen::sensor_event, SDL_SensorEvent>());
static_assert(validate<cen::user_event, SDL_UserEvent>());

static_assert(validate<cen::quit_event, SDL_QuitEvent>());

#if SDL_VERSION_ATLEAST(2, 0, 14)
static_assert(validate<cen::display_event, SDL_DisplayEvent>());
static_assert(validate<cen::controller_touchpad_event, SDL_ControllerTouchpadEvent>());
static_assert(validate<cen::controller_sensor_event, SDL_ControllerSensorEvent>());
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

TEST(Event, Push)
{
  cen::event_handler::flush_all();

  cen::keyboard_event event;
  event.set_type(cen::event_type::key_up);
  ASSERT_TRUE(cen::event_handler::push(event));

  cen::event_handler handler;
  ASSERT_TRUE(handler.poll());
  ASSERT_EQ(cen::event_type::key_up, handler.type());
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
  SDL_Event sdl {};
  sdl.type = SDL_MOUSEMOTION;
  sdl.motion.x = 839;
  sdl.motion.y = 351;

  cen::event_handler::flush();
  SDL_PushEvent(&sdl);

  cen::event_handler event;
  ASSERT_TRUE(event.poll());

  ASSERT_EQ(cen::event_type::mouse_motion, event.type());
  ASSERT_TRUE(event.is<cen::mouse_motion_event>());

  auto& motionEvent = event.get<cen::mouse_motion_event>();
  ASSERT_EQ(sdl.motion.x, motionEvent.x());
  ASSERT_EQ(sdl.motion.y, motionEvent.y());

  cen::event_handler::flush_all();
}

TEST(Event, QueueCount)
{
  cen::event_handler::flush_all();
  ASSERT_EQ(0, cen::event_handler::queue_count());
  ASSERT_EQ(0, cen::event_handler::queue_count(cen::event_type::quit));

  cen::quit_event event;
  cen::event_handler::push(event);

  ASSERT_EQ(1, cen::event_handler::queue_count());
  ASSERT_EQ(1, cen::event_handler::queue_count(cen::event_type::quit));
  ASSERT_EQ(0, cen::event_handler::queue_count(cen::event_type::window));
}

TEST(Event, InQueue)
{
  cen::event_handler::flush_all();
  ASSERT_FALSE(cen::event_handler::in_queue(cen::event_type::quit));

  cen::quit_event qe;
  cen::event_handler::push(qe);

  ASSERT_TRUE(cen::event_handler::in_queue(cen::event_type::quit));
  ASSERT_FALSE(cen::event_handler::in_queue(cen::event_type::window));

  cen::event_handler::flush_all();
  ASSERT_FALSE(cen::event_handler::in_queue(cen::event_type::quit));
}

TEST(Event, Type)
{
  SDL_Event sdl {};
  sdl.type = SDL_FINGERMOTION;

  cen::event_handler::flush_all();
  SDL_PushEvent(&sdl);

  cen::event_handler event;
  ASSERT_TRUE(event.poll());
  ASSERT_EQ(cen::event_type::finger_motion, event.type());

  cen::event_handler::flush_all();
}

TEST(Event, Get)
{
  cen::event_handler::flush_all();

  cen::quit_event event;
  cen::event_handler::push(event);

  cen::event_handler handler;
  ASSERT_TRUE(handler.poll());

  ASSERT_NO_THROW(handler.get<cen::quit_event>());
  ASSERT_ANY_THROW(handler.get<cen::window_event>());

  const auto& ref = handler;
  ASSERT_NO_THROW(ref.get<cen::quit_event>());
  ASSERT_ANY_THROW(ref.get<cen::window_event>());
}

TEST(Event, TryGet)
{
  cen::event_handler::flush_all();

  cen::mouse_motion_event event;
  cen::event_handler::push(event);

  cen::event_handler handler;
  ASSERT_TRUE(handler.poll());

  ASSERT_TRUE(handler.try_get<cen::mouse_motion_event>());
  ASSERT_FALSE(handler.try_get<cen::window_event>());

  const auto& ref = handler;
  ASSERT_TRUE(ref.try_get<cen::mouse_motion_event>());
  ASSERT_FALSE(ref.try_get<cen::window_event>());
}
