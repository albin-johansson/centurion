#include <gtest/gtest.h>

#include "events/event.hpp"

TEST(MouseMotionEvent, Defaults)
{
  cen::mouse_motion_event event;
  ASSERT_GT(event.GetTimestamp(), 0u);
  ASSERT_EQ(cen::EventType::MouseMotion, event.GetType());
}

TEST(MouseMotionEvent, SetWindowId)
{
  cen::mouse_motion_event event;

  constexpr Uint32 id = 8;
  event.set_window_id(id);

  ASSERT_EQ(id, event.window_id());
}

TEST(MouseMotionEvent, SetWhich)
{
  cen::mouse_motion_event event;

  constexpr Uint32 which = 65;
  event.set_which(which);

  ASSERT_EQ(which, event.which());
}

TEST(MouseMotionEvent, SetState)
{
  cen::mouse_motion_event event;

  constexpr Uint32 state = SDL_BUTTON_LMASK | SDL_BUTTON_RMASK;
  event.set_state(state);

  ASSERT_EQ(state, event.state());
}

TEST(MouseMotionEvent, SetX)
{
  cen::mouse_motion_event event;

  constexpr auto x = 745;
  event.set_x(x);

  ASSERT_EQ(x, event.x());
}

TEST(MouseMotionEvent, SetY)
{
  cen::mouse_motion_event event;

  constexpr auto y = 123;
  event.set_y(y);

  ASSERT_EQ(y, event.y());
}

TEST(MouseMotionEvent, SetDx)
{
  cen::mouse_motion_event event;

  constexpr auto dx = -456;
  event.set_dx(dx);

  ASSERT_EQ(dx, event.dx());
}

TEST(MouseMotionEvent, SetDy)
{
  cen::mouse_motion_event event;

  constexpr auto dy = 835;
  event.set_dy(dy);

  ASSERT_EQ(dy, event.dy());
}

TEST(MouseMotionEvent, Pressed)
{
  cen::mouse_motion_event event;
  event.set_state(SDL_BUTTON_LMASK | SDL_BUTTON_MMASK);

  ASSERT_TRUE(event.pressed(cen::MouseButton::Left));
  ASSERT_TRUE(event.pressed(cen::MouseButton::Middle));

  ASSERT_FALSE(event.pressed(cen::MouseButton::Right));
  ASSERT_FALSE(event.pressed(cen::MouseButton::X1));
  ASSERT_FALSE(event.pressed(cen::MouseButton::X2));
}

TEST(MouseMotionEvent, WindowId)
{
  SDL_MouseMotionEvent sdl;
  sdl.windowID = 45;

  const cen::mouse_motion_event event{sdl};
  ASSERT_EQ(sdl.windowID, event.window_id());
}

TEST(MouseMotionEvent, Which)
{
  SDL_MouseMotionEvent sdl;
  sdl.which = 77;

  const cen::mouse_motion_event event{sdl};
  ASSERT_EQ(sdl.which, event.which());
}

TEST(MouseMotionEvent, State)
{
  SDL_MouseMotionEvent sdl;
  sdl.state = SDL_BUTTON_LMASK;

  const cen::mouse_motion_event event{sdl};
  ASSERT_EQ(sdl.state, event.state());
}

TEST(MouseMotionEvent, X)
{
  SDL_MouseMotionEvent sdl;
  sdl.x = 1'867;

  const cen::mouse_motion_event event{sdl};
  ASSERT_EQ(sdl.x, event.x());
}

TEST(MouseMotionEvent, Y)
{
  SDL_MouseMotionEvent sdl;
  sdl.y = 454;

  const cen::mouse_motion_event event{sdl};
  ASSERT_EQ(sdl.y, event.y());
}

TEST(MouseMotionEvent, Dx)
{
  SDL_MouseMotionEvent sdl;
  sdl.xrel = 78;

  const cen::mouse_motion_event event{sdl};
  ASSERT_EQ(sdl.xrel, event.dx());
}

TEST(MouseMotionEvent, Dy)
{
  SDL_MouseMotionEvent sdl;
  sdl.yrel = -564;

  const cen::mouse_motion_event event{sdl};
  ASSERT_EQ(sdl.yrel, event.dy());
}

TEST(MouseMotionEvent, AsSDLEvent)
{
  const cen::mouse_motion_event event;
  const auto sdl = cen::AsSDLEvent(event);

  ASSERT_EQ(sdl.motion.type, cen::ToUnderlying(event.GetType()));
  ASSERT_EQ(sdl.motion.timestamp, event.GetTimestamp());
}
