#include <gtest/gtest.h>

#include "event.hpp"

TEST(MultiGestureEvent, Defaults)
{
  cen::multi_gesture_event event;
  EXPECT_GT(event.time(), 0u);
  EXPECT_EQ(cen::event_type::multi_gesture, event.type());
}

TEST(MultiGestureEvent, SetTouchId)
{
  cen::multi_gesture_event event;

  constexpr auto id = 3;
  event.set_touch_id(id);

  EXPECT_EQ(id, event.touch_id());
}

TEST(MultiGestureEvent, SetDeltaTheta)
{
  cen::multi_gesture_event event;

  constexpr auto dTheta = 65;
  event.set_delta_theta(dTheta);

  EXPECT_EQ(dTheta, event.delta_theta());
}

TEST(MultiGestureEvent, SetDeltaDistance)
{
  cen::multi_gesture_event event;

  constexpr auto dDistance = -79;
  event.set_delta_distance(dDistance);

  EXPECT_EQ(dDistance, event.delta_distance());
}

TEST(MultiGestureEvent, SetCenterX)
{
  cen::multi_gesture_event event;

  constexpr auto centerX = 154;
  event.set_center_x(centerX);

  EXPECT_EQ(centerX, event.center_x());
}

TEST(MultiGestureEvent, SetCenterY)
{
  cen::multi_gesture_event event;

  constexpr auto centerY = 867;
  event.set_center_y(centerY);

  EXPECT_EQ(centerY, event.center_y());
}

TEST(MultiGestureEvent, SetFingers)
{
  cen::multi_gesture_event event;

  constexpr auto fingers = 3;
  event.set_fingers(fingers);

  EXPECT_EQ(fingers, event.fingers());
}

TEST(MultiGestureEvent, TouchId)
{
  SDL_MultiGestureEvent sdl;
  sdl.touchId = 54;

  const cen::multi_gesture_event event{sdl};
  EXPECT_EQ(sdl.touchId, event.touch_id());
}

TEST(MultiGestureEvent, DeltaTheta)
{
  SDL_MultiGestureEvent sdl;
  sdl.dTheta = 98;

  const cen::multi_gesture_event event{sdl};
  EXPECT_EQ(sdl.dTheta, event.delta_theta());
}

TEST(MultiGestureEvent, DeltaDistance)
{
  SDL_MultiGestureEvent sdl;
  sdl.dDist = -87;

  const cen::multi_gesture_event event{sdl};
  EXPECT_EQ(sdl.dDist, event.delta_distance());
}

TEST(MultiGestureEvent, CenterX)
{
  SDL_MultiGestureEvent sdl;
  sdl.x = 564;

  const cen::multi_gesture_event event{sdl};
  EXPECT_EQ(sdl.x, event.center_x());
}

TEST(MultiGestureEvent, CenterY)
{
  SDL_MultiGestureEvent sdl;
  sdl.y = 913;

  const cen::multi_gesture_event event{sdl};
  EXPECT_EQ(sdl.y, event.center_y());
}

TEST(MultiGestureEvent, Fingers)
{
  SDL_MultiGestureEvent sdl;
  sdl.numFingers = 2;

  const cen::multi_gesture_event event{sdl};
  EXPECT_EQ(sdl.numFingers, event.fingers());
}

TEST(MultiGestureEvent, AsSDLEvent)
{
  const cen::multi_gesture_event event;
  const auto sdl = cen::as_sdl_event(event);

  EXPECT_EQ(sdl.mgesture.type, static_cast<cen::u32>(event.type()));
  EXPECT_EQ(sdl.mgesture.timestamp, event.time());
}
