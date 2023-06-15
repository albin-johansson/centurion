/*
 * MIT License
 *
 * Copyright (c) 2019-2023 Albin Johansson
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

#include "centurion/events/joystick_events.hpp"

TEST(JoyButtonEvent, Defaults)
{
  const cen::joy_button_event event;
  ASSERT_EQ(cen::event_type::joy_button_down, event.type());
}

TEST(JoyButtonEvent, SetWhich)
{
  cen::joy_button_event event;

  const SDL_JoystickID id = 92;
  event.set_which(id);

  ASSERT_EQ(id, event.which());
}

TEST(JoyButtonEvent, SetButton)
{
  cen::joy_button_event event;

  const cen::uint8 button = 44;
  event.set_button(button);

  ASSERT_EQ(button, event.button());
}

TEST(JoyButtonEvent, SetState)
{
  cen::joy_button_event event;

  event.set_state(cen::button_state::pressed);

  ASSERT_EQ(cen::button_state::pressed, event.state());
  ASSERT_TRUE(event.is_pressed());
  ASSERT_FALSE(event.is_released());

  event.set_state(cen::button_state::released);

  ASSERT_EQ(cen::button_state::released, event.state());
  ASSERT_TRUE(event.is_released());
  ASSERT_FALSE(event.is_pressed());
}

TEST(JoyButtonEvent, AsSDLEvent)
{
  const cen::joy_button_event event;
  const auto sdl = cen::as_sdl_event(event);

  ASSERT_EQ(sdl.jbutton.type, cen::to_underlying(event.type()));
  ASSERT_EQ(sdl.jbutton.timestamp, event.timestamp().count());
}
