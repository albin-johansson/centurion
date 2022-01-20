#include <gtest/gtest.h>

#include "centurion/mouse_events.hpp"

TEST(MouseWheelEvent, Defaults)
{
  const cen::mouse_wheel_event event;
  ASSERT_EQ(cen::event_type::mouse_wheel, event.type());
}

TEST(MouseWheelEvent, SetWindowID)
{
  cen::mouse_wheel_event event;

  const cen::uint32 id = 32;
  event.set_window_id(id);

  ASSERT_EQ(id, event.window_id());
}

TEST(MouseWheelEvent, SetWhich)
{
  cen::mouse_wheel_event event;

  const cen::uint32 which = 65;
  event.set_which(which);

  ASSERT_EQ(which, event.which());
}

TEST(MouseWheelEvent, SetX)
{
  cen::mouse_wheel_event event;

  const cen::int32 x = -545;
  event.set_x(x);

  ASSERT_EQ(x, event.x());
}

TEST(MouseWheelEvent, SetY)
{
  cen::mouse_wheel_event event;

  const cen::int32 y = 725;
  event.set_y(y);

  ASSERT_EQ(y, event.y());
}

TEST(MouseWheelEvent, SetDirection)
{
  cen::mouse_wheel_event event;

  event.set_direction(cen::mouse_wheel_direction::flipped);
  ASSERT_EQ(cen::mouse_wheel_direction::flipped, event.direction());
}

TEST(MouseWheelEvent, AsSDLEvent)
{
  const cen::mouse_wheel_event event;
  const auto sdl = cen::as_sdl_event(event);

  ASSERT_EQ(sdl.wheel.type, cen::to_underlying(event.type()));
  ASSERT_EQ(sdl.wheel.timestamp, event.timestamp().count());
}
