#include <gtest/gtest.h>

#include "events/event.hpp"

TEST(MouseWheelEvent, Defaults)
{
  cen::mouse_wheel_event event;
  ASSERT_GT(event.time(), 0u);
  ASSERT_EQ(cen::event_type::mouse_wheel, event.type());
}

TEST(MouseWheelEvent, SetWindowId)
{
  cen::mouse_wheel_event event;

  constexpr Uint32 id = 32;
  event.set_window_id(id);

  ASSERT_EQ(id, event.window_id());
}

TEST(MouseWheelEvent, SetWhich)
{
  cen::mouse_wheel_event event;

  constexpr Uint32 which = 32;
  event.set_which(which);

  ASSERT_EQ(which, event.which());
}

TEST(MouseWheelEvent, SetXScroll)
{
  cen::mouse_wheel_event event;

  constexpr auto xScroll = -545;
  event.set_x_scroll(xScroll);

  ASSERT_EQ(xScroll, event.x_scroll());
}

TEST(MouseWheelEvent, SetYScroll)
{
  cen::mouse_wheel_event event;

  constexpr auto yScroll = 725;
  event.set_y_scroll(yScroll);

  ASSERT_EQ(yScroll, event.y_scroll());
}

TEST(MouseWheelEvent, SetDirection)
{
  cen::mouse_wheel_event event;

  constexpr auto direction = cen::mouse_wheel_direction::flipped;
  event.set_direction(direction);

  ASSERT_EQ(direction, event.direction());
}

TEST(MouseWheelEvent, WindowId)
{
  SDL_MouseWheelEvent sdl;
  sdl.windowID = 12;

  const cen::mouse_wheel_event event{sdl};
  ASSERT_EQ(sdl.windowID, event.window_id());
}

TEST(MouseWheelEvent, Which)
{
  SDL_MouseWheelEvent sdl;
  sdl.windowID = 12;

  const cen::mouse_wheel_event event{sdl};
  ASSERT_EQ(sdl.windowID, event.window_id());
}

TEST(MouseWheelEvent, XScroll)
{
  SDL_MouseWheelEvent sdl;
  sdl.x = 455;

  const cen::mouse_wheel_event event{sdl};
  ASSERT_EQ(sdl.x, event.x_scroll());
}

TEST(MouseWheelEvent, YScroll)
{
  SDL_MouseWheelEvent sdl;
  sdl.y = -123;

  const cen::mouse_wheel_event event{sdl};
  ASSERT_EQ(sdl.y, event.y_scroll());
}

TEST(MouseWheelEvent, Direction)
{
  SDL_MouseWheelEvent sdl;
  sdl.direction = SDL_MOUSEWHEEL_NORMAL;

  const cen::mouse_wheel_event event{sdl};
  ASSERT_EQ(cen::mouse_wheel_direction::normal, event.direction());
}

TEST(MouseWheelEvent, AsSDLEvent)
{
  const cen::mouse_wheel_event event;
  const auto sdl = cen::as_sdl_event(event);

  ASSERT_EQ(sdl.wheel.type, cen::to_underlying(event.type()));
  ASSERT_EQ(sdl.wheel.timestamp, event.time());
}
