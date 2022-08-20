/*
 * MIT License
 *
 * Copyright (c) 2019-2022 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <gtest/gtest.h>

#include "centurion/event.hpp"

TEST(TouchFingerEvent, Defaults)
{
  cen::touch_finger_event event;
  ASSERT_EQ(cen::event_type::finger_down, event.type());
}

TEST(TouchFingerEvent, SetTouchId)
{
  cen::touch_finger_event event;

  constexpr auto id = 8;
  event.set_touch_id(id);

  ASSERT_EQ(id, event.touch_id());
}

TEST(TouchFingerEvent, SetFingerId)
{
  cen::touch_finger_event event;

  constexpr auto id = 14;
  event.set_finger_id(id);

  ASSERT_EQ(id, event.finger_id());
}

#if SDL_VERSION_ATLEAST(2, 0, 12)

TEST(TouchFingerEvent, SetWindowId)
{
  cen::touch_finger_event event;

  constexpr Uint32 id = 32;
  event.set_window_id(id);

  ASSERT_EQ(id, event.window_id());
}

TEST(TouchFingerEvent, WindowId)
{
  SDL_TouchFingerEvent sdl{};
  sdl.windowID = 7;

  const cen::touch_finger_event event{sdl};
  ASSERT_EQ(sdl.windowID, event.window_id());
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

TEST(TouchFingerEvent, SetX)
{
  cen::touch_finger_event event;

  {  // Overflow
    event.set_x(1.1f);
    ASSERT_EQ(1, event.x());
  }

  {  // Underflow
    event.set_x(-0.1f);
    ASSERT_EQ(0, event.x());
  }

  {  // Good value
    constexpr auto x = 0.4f;
    event.set_x(x);

    ASSERT_EQ(x, event.x());
  }
}

TEST(TouchFingerEvent, SetY)
{
  cen::touch_finger_event event;

  {  // Overflow
    event.set_y(1.1f);
    ASSERT_EQ(1, event.y());
  }

  {  // Underflow
    event.set_y(-0.1f);
    ASSERT_EQ(0, event.y());
  }

  {  // Good value
    constexpr auto y = 0.9f;
    event.set_y(y);

    ASSERT_EQ(y, event.y());
  }
}

TEST(TouchFingerEvent, SetDx)
{
  cen::touch_finger_event event;

  {  // Overflow
    event.set_dx(1.1f);
    ASSERT_EQ(1, event.dx());
  }

  {  // Underflow
    event.set_dx(-1.1f);
    ASSERT_EQ(-1, event.dx());
  }

  {  // Good value
    constexpr auto dx = -0.4f;
    event.set_dx(dx);

    ASSERT_EQ(dx, event.dx());
  }
}

TEST(TouchFingerEvent, SetDy)
{
  cen::touch_finger_event event;

  {  // Overflow
    event.set_dy(1.1f);
    ASSERT_EQ(1, event.dy());
  }

  {  // Underflow
    event.set_dy(-1.1f);
    ASSERT_EQ(-1, event.dy());
  }

  {  // Good value
    constexpr auto dy = 0.75f;
    event.set_dy(dy);

    ASSERT_EQ(dy, event.dy());
  }
}

TEST(TouchFingerEvent, SetPressure)
{
  cen::touch_finger_event event;

  {  // Overflow
    event.set_pressure(1.1f);
    ASSERT_EQ(1, event.pressure());
  }

  {  // Underflow
    event.set_pressure(-0.1f);
    ASSERT_EQ(0, event.pressure());
  }

  {  // Good value
    constexpr auto pressure = 0.75f;
    event.set_pressure(pressure);

    ASSERT_EQ(pressure, event.pressure());
  }
}

TEST(TouchFingerEvent, TouchId)
{
  SDL_TouchFingerEvent sdl{};
  sdl.touchId = 4;

  const cen::touch_finger_event event{sdl};
  ASSERT_EQ(sdl.touchId, event.touch_id());
}

TEST(TouchFingerEvent, FingerId)
{
  SDL_TouchFingerEvent sdl{};
  sdl.fingerId = 18;

  const cen::touch_finger_event event{sdl};
  ASSERT_EQ(sdl.fingerId, event.finger_id());
}

TEST(TouchFingerEvent, X)
{
  SDL_TouchFingerEvent sdl{};
  sdl.x = 0.4f;

  const cen::touch_finger_event event{sdl};
  ASSERT_EQ(sdl.x, event.x());
}

TEST(TouchFingerEvent, Y)
{
  SDL_TouchFingerEvent sdl{};
  sdl.y = 0.8f;

  const cen::touch_finger_event event{sdl};
  ASSERT_EQ(sdl.y, event.y());
}

TEST(TouchFingerEvent, Dx)
{
  SDL_TouchFingerEvent sdl{};
  sdl.dx = -0.9f;

  const cen::touch_finger_event event{sdl};
  ASSERT_EQ(sdl.dx, event.dx());
}

TEST(TouchFingerEvent, Dy)
{
  SDL_TouchFingerEvent sdl{};
  sdl.dy = 0.2f;

  const cen::touch_finger_event event{sdl};
  ASSERT_EQ(sdl.dy, event.dy());
}

TEST(TouchFingerEvent, Pressure)
{
  SDL_TouchFingerEvent sdl{};
  sdl.pressure = 0.6f;

  const cen::touch_finger_event event{sdl};
  ASSERT_EQ(sdl.pressure, event.pressure());
}

TEST(TouchFingerEvent, AsSDLEvent)
{
  const cen::touch_finger_event event;
  const auto sdl = cen::as_sdl_event(event);

  ASSERT_EQ(sdl.tfinger.type, cen::to_underlying(event.type()));
  ASSERT_EQ(sdl.tfinger.timestamp, event.timestamp().count());
}
