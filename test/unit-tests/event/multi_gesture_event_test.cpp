#include <gtest/gtest.h>

#include "events/event.hpp"

TEST(MultiGestureEvent, Defaults)
{
  cen::multi_gesture_event event;
  ASSERT_GT(event.time(), 0u);
  ASSERT_EQ(cen::event_type::multi_gesture, event.type());
}

TEST(MultiGestureEvent, SetTouchId)
{
  cen::multi_gesture_event event;

  constexpr auto id = 3;
  event.set_touch_id(id);

  ASSERT_EQ(id, event.touch_id());
}

TEST(MultiGestureEvent, SetDeltaTheta)
{
  cen::multi_gesture_event event;

  constexpr auto dTheta = 65;
  event.set_delta_theta(dTheta);

  ASSERT_EQ(dTheta, event.delta_theta());
}

TEST(MultiGestureEvent, SetDeltaDistance)
{
  cen::multi_gesture_event event;

  constexpr auto dDistance = -79;
  event.set_delta_distance(dDistance);

  ASSERT_EQ(dDistance, event.delta_distance());
}

TEST(MultiGestureEvent, SetCenterX)
{
  cen::multi_gesture_event event;

  constexpr auto centerX = 154;
  event.set_center_x(centerX);

  ASSERT_EQ(centerX, event.center_x());
}

TEST(MultiGestureEvent, SetCenterY)
{
  cen::multi_gesture_event event;

  constexpr auto centerY = 867;
  event.set_center_y(centerY);

  ASSERT_EQ(centerY, event.center_y());
}

TEST(MultiGestureEvent, SetFingerCount)
{
  cen::multi_gesture_event event;

  event.set_finger_count(3);
  ASSERT_EQ(3, event.finger_count());
}

TEST(MultiGestureEvent, TouchId)
{
  SDL_MultiGestureEvent sdl;
  sdl.touchId = 54;

  const cen::multi_gesture_event event{sdl};
  ASSERT_EQ(sdl.touchId, event.touch_id());
}

TEST(MultiGestureEvent, DeltaTheta)
{
  SDL_MultiGestureEvent sdl;
  sdl.dTheta = 98;

  const cen::multi_gesture_event event{sdl};
  ASSERT_EQ(sdl.dTheta, event.delta_theta());
}

TEST(MultiGestureEvent, DeltaDistance)
{
  SDL_MultiGestureEvent sdl;
  sdl.dDist = -87;

  const cen::multi_gesture_event event{sdl};
  ASSERT_EQ(sdl.dDist, event.delta_distance());
}

TEST(MultiGestureEvent, CenterX)
{
  SDL_MultiGestureEvent sdl;
  sdl.x = 564;

  const cen::multi_gesture_event event{sdl};
  ASSERT_EQ(sdl.x, event.center_x());
}

TEST(MultiGestureEvent, CenterY)
{
  SDL_MultiGestureEvent sdl;
  sdl.y = 913;

  const cen::multi_gesture_event event{sdl};
  ASSERT_EQ(sdl.y, event.center_y());
}

TEST(MultiGestureEvent, FingerCount)
{
  SDL_MultiGestureEvent sdl;
  sdl.numFingers = 2;

  const cen::multi_gesture_event event{sdl};
  ASSERT_EQ(sdl.numFingers, event.finger_count());
}

TEST(MultiGestureEvent, AsSDLEvent)
{
  const cen::multi_gesture_event event;
  const auto sdl = cen::as_sdl_event(event);

  ASSERT_EQ(sdl.mgesture.type, cen::to_underlying(event.type()));
  ASSERT_EQ(sdl.mgesture.timestamp, event.time());
}
