#include <gtest/gtest.h>

#include "event.hpp"

TEST(DollarGestureEvent, Defaults)
{
  cen::dollar_gesture_event event;
  EXPECT_GT(event.time(), 0u);
  EXPECT_EQ(cen::event_type::dollar_gesture, event.type());
}

TEST(DollarGestureEvent, SetTouchId)
{
  cen::dollar_gesture_event event;

  constexpr auto id = 4;
  event.set_touch_id(id);

  EXPECT_EQ(id, event.touch_id());
}

TEST(DollarGestureEvent, SetGestureId)
{
  cen::dollar_gesture_event event;

  constexpr auto id = 81;
  event.set_gesture_id(id);

  EXPECT_EQ(id, event.gesture_id());
}

TEST(DollarGestureEvent, SetFingers)
{
  cen::dollar_gesture_event event;

  constexpr auto fingers = 2;
  event.set_fingers(fingers);

  EXPECT_EQ(fingers, event.fingers());
}

TEST(DollarGestureEvent, SetError)
{
  cen::dollar_gesture_event event;

  constexpr auto error = 5.1f;
  event.set_error(error);

  EXPECT_EQ(error, event.error());
}

TEST(DollarGestureEvent, SetX)
{
  cen::dollar_gesture_event event;

  constexpr auto x = 24.8f;
  event.set_x(x);

  EXPECT_EQ(x, event.x());
}

TEST(DollarGestureEvent, SetY)
{
  cen::dollar_gesture_event event;

  constexpr auto y = -12.9f;
  event.set_y(y);

  EXPECT_EQ(y, event.y());
}

TEST(DollarGestureEvent, TouchId)
{
  SDL_DollarGestureEvent sdl;
  sdl.touchId = 9;

  const cen::dollar_gesture_event event{sdl};
  EXPECT_EQ(sdl.touchId, event.touch_id());
}

TEST(DollarGestureEvent, GestureId)
{
  SDL_DollarGestureEvent sdl;
  sdl.gestureId = 1;

  const cen::dollar_gesture_event event{sdl};
  EXPECT_EQ(sdl.gestureId, event.gesture_id());
}

TEST(DollarGestureEvent, Fingers)
{
  SDL_DollarGestureEvent sdl;
  sdl.numFingers = 3;

  const cen::dollar_gesture_event event{sdl};
  EXPECT_EQ(sdl.numFingers, event.fingers());
}

TEST(DollarGestureEvent, Error)
{
  SDL_DollarGestureEvent sdl;
  sdl.error = 7.4f;

  const cen::dollar_gesture_event event{sdl};
  EXPECT_EQ(sdl.error, event.error());
}

TEST(DollarGestureEvent, X)
{
  SDL_DollarGestureEvent sdl;
  sdl.x = 56.8f;

  const cen::dollar_gesture_event event{sdl};
  EXPECT_EQ(sdl.x, event.x());
}

TEST(DollarGestureEvent, Y)
{
  SDL_DollarGestureEvent sdl;
  sdl.y = 92.3f;

  const cen::dollar_gesture_event event{sdl};
  EXPECT_EQ(sdl.y, event.y());
}

TEST(DollarGestureEvent, AsSDLEvent)
{
  const cen::dollar_gesture_event event;
  const auto sdl = cen::as_sdl_event(event);

  EXPECT_EQ(sdl.dgesture.type, static_cast<cen::u32>(event.type()));
  EXPECT_EQ(sdl.dgesture.timestamp, event.time());
}
