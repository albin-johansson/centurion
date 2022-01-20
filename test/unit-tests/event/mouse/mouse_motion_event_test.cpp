#include <gtest/gtest.h>

#include "mouse_events.hpp"

TEST(MouseMotionEvent, Defaults)
{
  const cen::mouse_motion_event event;
  ASSERT_EQ(cen::event_type::mouse_motion, event.type());
}

TEST(MouseMotionEvent, SetWindowID)
{
  cen::mouse_motion_event event;

  const cen::uint32 id = 8;
  event.set_window_id(id);

  ASSERT_EQ(id, event.window_id());
}

TEST(MouseMotionEvent, SetWhich)
{
  cen::mouse_motion_event event;

  const cen::uint32 which = 65;
  event.set_which(which);

  ASSERT_EQ(which, event.which());
}

TEST(MouseMotionEvent, SetState)
{
  cen::mouse_motion_event event;

  event.set_state(SDL_BUTTON_LMASK | SDL_BUTTON_MMASK);
  ASSERT_EQ(Uint32{SDL_BUTTON_LMASK | SDL_BUTTON_MMASK}, event.state());

  ASSERT_TRUE(event.pressed(cen::mouse_button::left));
  ASSERT_TRUE(event.pressed(cen::mouse_button::middle));

  ASSERT_FALSE(event.pressed(cen::mouse_button::right));
  ASSERT_FALSE(event.pressed(cen::mouse_button::x1));
  ASSERT_FALSE(event.pressed(cen::mouse_button::x2));
}

TEST(MouseMotionEvent, SetX)
{
  cen::mouse_motion_event event;

  const cen::int32 x = 745;
  event.set_x(x);

  ASSERT_EQ(x, event.x());
}

TEST(MouseMotionEvent, SetY)
{
  cen::mouse_motion_event event;

  const cen::int32 y = 123;
  event.set_y(y);

  ASSERT_EQ(y, event.y());
}

TEST(MouseMotionEvent, SetDX)
{
  cen::mouse_motion_event event;

  const cen::int32 dx = -456;
  event.set_dx(dx);

  ASSERT_EQ(dx, event.dx());
}

TEST(MouseMotionEvent, SetDY)
{
  cen::mouse_motion_event event;

  const cen::int32 dy = 835;
  event.set_dy(dy);

  ASSERT_EQ(dy, event.dy());
}

TEST(MouseMotionEvent, AsSDLEvent)
{
  const cen::mouse_motion_event event;
  const auto sdl = cen::as_sdl_event(event);

  ASSERT_EQ(sdl.motion.type, cen::to_underlying(event.type()));
  ASSERT_EQ(sdl.motion.timestamp, event.timestamp().count());
}
