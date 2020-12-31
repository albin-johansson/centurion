#include <gtest/gtest.h>

#include "event.hpp"

TEST(TouchFingerEvent, SetTouchId)
{
  cen::touch_finger_event event;

  constexpr auto id = 8;
  event.set_touch_id(id);

  EXPECT_EQ(id, event.touch_id());
}

TEST(TouchFingerEvent, SetFingerId)
{
  cen::touch_finger_event event;

  constexpr auto id = 14;
  event.set_finger_id(id);

  EXPECT_EQ(id, event.finger_id());
}

TEST(TouchFingerEvent, SetWindowId)
{
  cen::touch_finger_event event;

  constexpr auto id = 32;
  event.set_window_id(id);

  EXPECT_EQ(id, event.window_id());
}

TEST(TouchFingerEvent, SetX)
{
  cen::touch_finger_event event;

  {  // Overflow
    event.set_x(1.1f);
    EXPECT_EQ(1, event.x());
  }

  {  // Underflow
    event.set_x(-0.1f);
    EXPECT_EQ(0, event.x());
  }

  {  // Good value
    constexpr auto x = 0.4f;
    event.set_x(x);

    EXPECT_EQ(x, event.x());
  }
}

TEST(TouchFingerEvent, SetY)
{
  cen::touch_finger_event event;

  {  // Overflow
    event.set_y(1.1f);
    EXPECT_EQ(1, event.y());
  }

  {  // Underflow
    event.set_y(-0.1f);
    EXPECT_EQ(0, event.y());
  }

  {  // Good value
    constexpr auto y = 0.9f;
    event.set_y(y);

    EXPECT_EQ(y, event.y());
  }
}

TEST(TouchFingerEvent, SetDx)
{
  cen::touch_finger_event event;

  {  // Overflow
    event.set_dx(1.1f);
    EXPECT_EQ(1, event.dx());
  }

  {  // Underflow
    event.set_dx(-1.1f);
    EXPECT_EQ(-1, event.dx());
  }

  {  // Good value
    constexpr auto dx = -0.4f;
    event.set_dx(dx);

    EXPECT_EQ(dx, event.dx());
  }
}

TEST(TouchFingerEvent, SetDy)
{
  cen::touch_finger_event event;

  {  // Overflow
    event.set_dy(1.1f);
    EXPECT_EQ(1, event.dy());
  }

  {  // Underflow
    event.set_dy(-1.1f);
    EXPECT_EQ(-1, event.dy());
  }

  {  // Good value
    constexpr auto dy = 0.75f;
    event.set_dy(dy);

    EXPECT_EQ(dy, event.dy());
  }
}

TEST(TouchFingerEvent, SetPressure)
{
  cen::touch_finger_event event;

  {  // Overflow
    event.set_pressure(1.1f);
    EXPECT_EQ(1, event.pressure());
  }

  {  // Underflow
    event.set_pressure(-0.1f);
    EXPECT_EQ(0, event.pressure());
  }

  {  // Good value
    constexpr auto pressure = 0.75f;
    event.set_pressure(pressure);

    EXPECT_EQ(pressure, event.pressure());
  }
}

TEST(TouchFingerEvent, TouchId)
{
  SDL_TouchFingerEvent sdl{};
  sdl.touchId = 4;

  const cen::touch_finger_event event{sdl};
  EXPECT_EQ(sdl.touchId, event.touch_id());
}

TEST(TouchFingerEvent, FingerId)
{
  SDL_TouchFingerEvent sdl{};
  sdl.fingerId = 18;

  const cen::touch_finger_event event{sdl};
  EXPECT_EQ(sdl.fingerId, event.finger_id());
}

TEST(TouchFingerEvent, WindowId)
{
  SDL_TouchFingerEvent sdl{};
  sdl.windowID = 7;

  const cen::touch_finger_event event{sdl};
  EXPECT_EQ(sdl.windowID, event.window_id());
}

TEST(TouchFingerEvent, X)
{
  SDL_TouchFingerEvent sdl{};
  sdl.x = 0.4f;

  const cen::touch_finger_event event{sdl};
  EXPECT_EQ(sdl.x, event.x());
}

TEST(TouchFingerEvent, Y)
{
  SDL_TouchFingerEvent sdl{};
  sdl.y = 0.8f;

  const cen::touch_finger_event event{sdl};
  EXPECT_EQ(sdl.y, event.y());
}

TEST(TouchFingerEvent, Dx)
{
  SDL_TouchFingerEvent sdl{};
  sdl.dx = -0.9f;

  const cen::touch_finger_event event{sdl};
  EXPECT_EQ(sdl.dx, event.dx());
}

TEST(TouchFingerEvent, Dy)
{
  SDL_TouchFingerEvent sdl{};
  sdl.dy = 0.2f;

  const cen::touch_finger_event event{sdl};
  EXPECT_EQ(sdl.dy, event.dy());
}

TEST(TouchFingerEvent, Pressure)
{
  SDL_TouchFingerEvent sdl{};
  sdl.pressure = 0.6f;

  const cen::touch_finger_event event{sdl};
  EXPECT_EQ(sdl.pressure, event.pressure());
}
