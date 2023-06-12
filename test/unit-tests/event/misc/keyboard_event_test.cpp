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

#include "centurion/events/misc_events.hpp"

TEST(KeyboardEvent, Defaults)
{
  const cen::keyboard_event event;
  ASSERT_EQ(cen::event_type::key_down, event.type());
}

TEST(KeyboardEvent, SetScan)
{
  cen::keyboard_event event;

  event.set_scan(cen::scancodes::b);
  ASSERT_EQ(cen::scancodes::b, event.scan());
}

TEST(KeyboardEvent, SetKey)
{
  cen::keyboard_event event;

  event.set_key(cen::keycodes::n);
  ASSERT_EQ(cen::keycodes::n, event.key());
}

TEST(KeyboardEvent, SetModifier)
{
  cen::keyboard_event event;

  const auto shift = cen::key_mod::lshift;
  const auto caps = cen::key_mod::caps;

  event.set_modifier(shift, true);
  ASSERT_TRUE(event.is_active(shift));

  event.set_modifier(caps, true);
  ASSERT_TRUE(event.is_active(shift));
  ASSERT_TRUE(event.is_active(caps));

  event.set_modifier(shift, false);
  ASSERT_FALSE(event.is_active(shift));
  ASSERT_TRUE(event.is_active(caps));
}

TEST(KeyboardEvent, SetRepeated)
{
  cen::keyboard_event event;

  event.set_repeated(true);
  ASSERT_TRUE(event.repeated());

  event.set_repeated(false);
  ASSERT_FALSE(event.repeated());
}

TEST(KeyboardEvent, SetWindowID)
{
  cen::keyboard_event event;

  event.set_window_id(79);
  ASSERT_EQ(79u, event.window_id());
}

TEST(KeyboardEvent, SetState)
{
  cen::keyboard_event event;

  event.set_state(cen::button_state::pressed);
  ASSERT_EQ(cen::button_state::pressed, event.state());
  ASSERT_TRUE(event.pressed());
  ASSERT_FALSE(event.released());

  event.set_state(cen::button_state::released);
  ASSERT_EQ(cen::button_state::released, event.state());
  ASSERT_TRUE(event.released());
  ASSERT_FALSE(event.pressed());
}

TEST(KeyboardEvent, IsActive)
{
  cen::keyboard_event event;
  event.set_scan(cen::scancodes::q);
  event.set_key(cen::keycodes::d);

  ASSERT_TRUE(event.is_active(cen::scancodes::q));
  ASSERT_TRUE(event.is_active(cen::keycodes::d));

  ASSERT_FALSE(event.is_active(cen::scancodes::o));
  ASSERT_FALSE(event.is_active(cen::keycodes::x));
}

TEST(KeyboardEvent, IsOnlyActive)
{
  cen::keyboard_event event;
  ASSERT_TRUE(event.is_active(cen::key_mod::none));
  ASSERT_TRUE(event.is_only_active(cen::key_mod::none));
  ASSERT_FALSE(event.is_active(cen::key_mod::shift));
  ASSERT_FALSE(event.is_only_active(cen::key_mod::shift));

  event.set_modifier(cen::key_mod::shift, true);
  ASSERT_FALSE(event.is_active(cen::key_mod::none));
  ASSERT_FALSE(event.is_only_active(cen::key_mod::none));
  ASSERT_TRUE(event.is_active(cen::key_mod::shift));
  ASSERT_TRUE(event.is_only_active(cen::key_mod::shift));
  ASSERT_FALSE(event.is_only_active(cen::key_mod::lshift));
  ASSERT_FALSE(event.is_only_active(cen::key_mod::rshift));

  event.set_modifier(cen::key_mod::alt, true);
  ASSERT_FALSE(event.is_active(cen::key_mod::none));
  ASSERT_FALSE(event.is_only_active(cen::key_mod::none));
  ASSERT_TRUE(event.is_active(cen::key_mod::shift));
  ASSERT_TRUE(event.is_active(cen::key_mod::alt));
  ASSERT_FALSE(event.is_only_active(cen::key_mod::shift));
  ASSERT_FALSE(event.is_only_active(cen::key_mod::alt));

  event.set_modifier(cen::key_mod::alt, false);
  event.set_modifier(cen::key_mod::rshift, false);
  ASSERT_FALSE(event.is_active(cen::key_mod::none));
  ASSERT_FALSE(event.is_only_active(cen::key_mod::none));
  ASSERT_TRUE(event.is_active(cen::key_mod::shift));
  ASSERT_TRUE(event.is_active(cen::key_mod::lshift));
  ASSERT_FALSE(event.is_active(cen::key_mod::rshift));
  ASSERT_FALSE(event.is_only_active(cen::key_mod::shift));
  ASSERT_TRUE(event.is_only_active(cen::key_mod::lshift));
  ASSERT_FALSE(event.is_only_active(cen::key_mod::rshift));
}

TEST(KeyboardEvent, IsOnlyAnyOfActive)
{
  cen::keyboard_event event;
  ASSERT_TRUE(event.is_active(cen::key_mod::none));
  ASSERT_TRUE(event.is_only_active(cen::key_mod::none));
  ASSERT_TRUE(event.is_only_subset_active(cen::key_mod::none));
  ASSERT_FALSE(event.is_active(cen::key_mod::shift));
  ASSERT_FALSE(event.is_only_active(cen::key_mod::shift));
  ASSERT_FALSE(event.is_only_subset_active(cen::key_mod::shift));

  event.set_modifier(cen::key_mod::lshift, true);
  ASSERT_TRUE(event.is_active(cen::key_mod::shift));
  ASSERT_FALSE(event.is_only_active(cen::key_mod::shift));
  ASSERT_TRUE(event.is_only_subset_active(cen::key_mod::shift));
  ASSERT_TRUE(event.is_only_subset_active(cen::key_mod::lshift));

  event.set_modifier(cen::key_mod::rgui, true);
  ASSERT_TRUE(event.is_active(cen::key_mod::shift));
  ASSERT_FALSE(event.is_only_active(cen::key_mod::shift));
  ASSERT_FALSE(event.is_only_subset_active(cen::key_mod::shift));

  ASSERT_TRUE(event.is_only_active(cen::key_mod::lshift | cen::key_mod::rgui));
  ASSERT_TRUE(event.is_only_subset_active(cen::key_mod::lshift | cen::key_mod::rgui));
  ASSERT_TRUE(event.is_only_subset_active(cen::key_mod::shift | cen::key_mod::gui));
}

TEST(KeyboardEvent, IsActiveModifier)
{
  SDL_KeyboardEvent sdl{};

  SDL_Keysym keysym{};
  keysym.mod = KMOD_LALT | KMOD_CAPS;

  sdl.keysym = keysym;

  const cen::keyboard_event event{sdl};

  // Check that multiple key modifiers can be active at the same time
  ASSERT_TRUE(event.is_active(cen::key_mod::lalt));
  ASSERT_TRUE(event.is_active(cen::key_mod::caps));
}

TEST(keyboard_event, AsSDLEvent)
{
  const cen::keyboard_event event;
  const auto underlying = cen::as_sdl_event(event);

  ASSERT_EQ(underlying.key.type, cen::to_underlying(event.type()));
  ASSERT_EQ(underlying.key.timestamp, event.timestamp().count());
}
