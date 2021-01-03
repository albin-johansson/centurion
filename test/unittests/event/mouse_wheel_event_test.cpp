#include <gtest/gtest.h>

#include "event.hpp"

TEST(MouseWheelEvent, SetWindowId)
{
  cen::mouse_wheel_event event;

  constexpr auto id = 32;
  event.set_window_id(id);

  EXPECT_EQ(id, event.window_id());
}

TEST(MouseWheelEvent, SetWhich)
{
  cen::mouse_wheel_event event;

  constexpr auto which = 32;
  event.set_which(which);

  EXPECT_EQ(which, event.which());
}

TEST(MouseWheelEvent, SetXScroll)
{
  cen::mouse_wheel_event event;

  constexpr auto xScroll = -545;
  event.set_x_scroll(xScroll);

  EXPECT_EQ(xScroll, event.x_scroll());
}

TEST(MouseWheelEvent, SetYScroll)
{
  cen::mouse_wheel_event event;

  constexpr auto yScroll = 725;
  event.set_y_scroll(yScroll);

  EXPECT_EQ(yScroll, event.y_scroll());
}

TEST(MouseWheelEvent, SetDirection)
{
  cen::mouse_wheel_event event;

  constexpr auto direction = cen::mouse_wheel_direction::flipped;
  event.set_direction(direction);

  EXPECT_EQ(direction, event.direction());
}

TEST(MouseWheelEvent, WindowId)
{
  SDL_MouseWheelEvent sdl;
  sdl.windowID = 12;

  const cen::mouse_wheel_event event{sdl};
  EXPECT_EQ(sdl.windowID, event.window_id());
}

TEST(MouseWheelEvent, Which)
{
  SDL_MouseWheelEvent sdl;
  sdl.windowID = 12;

  const cen::mouse_wheel_event event{sdl};
  EXPECT_EQ(sdl.windowID, event.window_id());
}

TEST(MouseWheelEvent, XScroll)
{
  SDL_MouseWheelEvent sdl;
  sdl.x = 455;

  const cen::mouse_wheel_event event{sdl};
  EXPECT_EQ(sdl.x, event.x_scroll());
}

TEST(MouseWheelEvent, YScroll)
{
  SDL_MouseWheelEvent sdl;
  sdl.y = -123;

  const cen::mouse_wheel_event event{sdl};
  EXPECT_EQ(sdl.y, event.y_scroll());
}

TEST(MouseWheelEvent, Direction)
{
  SDL_MouseWheelEvent sdl;
  sdl.direction = SDL_MOUSEWHEEL_NORMAL;

  const cen::mouse_wheel_event event{sdl};
  EXPECT_EQ(cen::mouse_wheel_direction::normal, event.direction());
}
