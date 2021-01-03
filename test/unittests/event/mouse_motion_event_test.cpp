#include <gtest/gtest.h>

#include "event.hpp"

TEST(MouseMotionEvent, SetWindowId)
{
  cen::mouse_motion_event event;

  constexpr auto id = 8;
  event.set_window_id(id);

  EXPECT_EQ(id, event.window_id());
}

TEST(MouseMotionEvent, SetWhich)
{
  cen::mouse_motion_event event;

  constexpr auto which = 65;
  event.set_which(which);

  EXPECT_EQ(which, event.which());
}

TEST(MouseMotionEvent, SetState)
{
  cen::mouse_motion_event event;

  constexpr auto state = SDL_BUTTON_LMASK | SDL_BUTTON_RMASK;
  event.set_state(state);

  EXPECT_EQ(state, event.state());
}

TEST(MouseMotionEvent, SetX)
{
  cen::mouse_motion_event event;

  constexpr auto x = 745;
  event.set_x(x);

  EXPECT_EQ(x, event.x());
}

TEST(MouseMotionEvent, SetY)
{
  cen::mouse_motion_event event;

  constexpr auto y = 123;
  event.set_y(y);

  EXPECT_EQ(y, event.y());
}

TEST(MouseMotionEvent, SetDx)
{
  cen::mouse_motion_event event;

  constexpr auto dx = -456;
  event.set_dx(dx);

  EXPECT_EQ(dx, event.dx());
}

TEST(MouseMotionEvent, SetDy)
{
  cen::mouse_motion_event event;

  constexpr auto dy = 835;
  event.set_dy(dy);

  EXPECT_EQ(dy, event.dy());
}

TEST(MouseMotionEvent, Pressed)
{
  cen::mouse_motion_event event;
  event.set_state(SDL_BUTTON_LMASK | SDL_BUTTON_MMASK);

  EXPECT_TRUE(event.pressed(cen::mouse_button::left));
  EXPECT_TRUE(event.pressed(cen::mouse_button::middle));

  EXPECT_FALSE(event.pressed(cen::mouse_button::right));
  EXPECT_FALSE(event.pressed(cen::mouse_button::x1));
  EXPECT_FALSE(event.pressed(cen::mouse_button::x2));
}

TEST(MouseMotionEvent, WindowId)
{
  SDL_MouseMotionEvent sdl;
  sdl.windowID = 45;

  const cen::mouse_motion_event event{sdl};
  EXPECT_EQ(sdl.windowID, event.window_id());
}

TEST(MouseMotionEvent, Which)
{
  SDL_MouseMotionEvent sdl;
  sdl.which = 77;

  const cen::mouse_motion_event event{sdl};
  EXPECT_EQ(sdl.which, event.which());
}

TEST(MouseMotionEvent, State)
{
  SDL_MouseMotionEvent sdl;
  sdl.state = SDL_BUTTON_LMASK;

  const cen::mouse_motion_event event{sdl};
  EXPECT_EQ(sdl.state, event.state());
}

TEST(MouseMotionEvent, X)
{
  SDL_MouseMotionEvent sdl;
  sdl.x = 1'867;

  const cen::mouse_motion_event event{sdl};
  EXPECT_EQ(sdl.x, event.x());
}

TEST(MouseMotionEvent, Y)
{
  SDL_MouseMotionEvent sdl;
  sdl.y = 454;

  const cen::mouse_motion_event event{sdl};
  EXPECT_EQ(sdl.y, event.y());
}

TEST(MouseMotionEvent, Dx)
{
  SDL_MouseMotionEvent sdl;
  sdl.xrel = 78;

  const cen::mouse_motion_event event{sdl};
  EXPECT_EQ(sdl.xrel, event.dx());
}

TEST(MouseMotionEvent, Dy)
{
  SDL_MouseMotionEvent sdl;
  sdl.yrel = -564;

  const cen::mouse_motion_event event{sdl};
  EXPECT_EQ(sdl.yrel, event.dy());
}
