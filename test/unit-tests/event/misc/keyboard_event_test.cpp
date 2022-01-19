#include <gtest/gtest.h>

#include "misc_events.hpp"

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

  const auto shift = cen::KeyMod::LShift;
  const auto caps = cen::KeyMod::Caps;

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

  event.set_state(cen::ButtonState::Pressed);
  ASSERT_EQ(cen::ButtonState::Pressed, event.state());
  ASSERT_TRUE(event.pressed());
  ASSERT_FALSE(event.released());

  event.set_state(cen::ButtonState::Released);
  ASSERT_EQ(cen::ButtonState::Released, event.state());
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
  ASSERT_TRUE(event.is_active(cen::KeyMod::None));
  ASSERT_TRUE(event.is_only_active(cen::KeyMod::None));
  ASSERT_FALSE(event.is_active(cen::KeyMod::Shift));
  ASSERT_FALSE(event.is_only_active(cen::KeyMod::Shift));

  event.set_modifier(cen::KeyMod::Shift, true);
  ASSERT_FALSE(event.is_active(cen::KeyMod::None));
  ASSERT_FALSE(event.is_only_active(cen::KeyMod::None));
  ASSERT_TRUE(event.is_active(cen::KeyMod::Shift));
  ASSERT_TRUE(event.is_only_active(cen::KeyMod::Shift));
  ASSERT_FALSE(event.is_only_active(cen::KeyMod::LShift));
  ASSERT_FALSE(event.is_only_active(cen::KeyMod::RShift));

  event.set_modifier(cen::KeyMod::Alt, true);
  ASSERT_FALSE(event.is_active(cen::KeyMod::None));
  ASSERT_FALSE(event.is_only_active(cen::KeyMod::None));
  ASSERT_TRUE(event.is_active(cen::KeyMod::Shift));
  ASSERT_TRUE(event.is_active(cen::KeyMod::Alt));
  ASSERT_FALSE(event.is_only_active(cen::KeyMod::Shift));
  ASSERT_FALSE(event.is_only_active(cen::KeyMod::Alt));

  event.set_modifier(cen::KeyMod::Alt, false);
  event.set_modifier(cen::KeyMod::RShift, false);
  ASSERT_FALSE(event.is_active(cen::KeyMod::None));
  ASSERT_FALSE(event.is_only_active(cen::KeyMod::None));
  ASSERT_TRUE(event.is_active(cen::KeyMod::Shift));
  ASSERT_TRUE(event.is_active(cen::KeyMod::LShift));
  ASSERT_FALSE(event.is_active(cen::KeyMod::RShift));
  ASSERT_FALSE(event.is_only_active(cen::KeyMod::Shift));
  ASSERT_TRUE(event.is_only_active(cen::KeyMod::LShift));
  ASSERT_FALSE(event.is_only_active(cen::KeyMod::RShift));
}

TEST(KeyboardEvent, IsOnlyAnyOfActive)
{
  cen::keyboard_event event;
  ASSERT_TRUE(event.is_active(cen::KeyMod::None));
  ASSERT_TRUE(event.is_only_active(cen::KeyMod::None));
  ASSERT_TRUE(event.is_only_any_of_active(cen::KeyMod::None));
  ASSERT_FALSE(event.is_active(cen::KeyMod::Shift));
  ASSERT_FALSE(event.is_only_active(cen::KeyMod::Shift));
  ASSERT_FALSE(event.is_only_any_of_active(cen::KeyMod::Shift));

  event.set_modifier(cen::KeyMod::LShift, true);
  ASSERT_TRUE(event.is_active(cen::KeyMod::Shift));
  ASSERT_FALSE(event.is_only_active(cen::KeyMod::Shift));
  ASSERT_TRUE(event.is_only_any_of_active(cen::KeyMod::Shift));
  ASSERT_TRUE(event.is_only_any_of_active(cen::KeyMod::LShift));

  event.set_modifier(cen::KeyMod::RGui, true);
  ASSERT_TRUE(event.is_active(cen::KeyMod::Shift));
  ASSERT_FALSE(event.is_only_active(cen::KeyMod::Shift));
  ASSERT_FALSE(event.is_only_any_of_active(cen::KeyMod::Shift));

  ASSERT_TRUE(event.is_only_active(cen::KeyMod::LShift | cen::KeyMod::RGui));
  ASSERT_TRUE(event.is_only_any_of_active(cen::KeyMod::LShift | cen::KeyMod::RGui));
  ASSERT_TRUE(event.is_only_any_of_active(cen::KeyMod::Shift | cen::KeyMod::Gui));
}

TEST(KeyboardEvent, IsActiveModifier)
{
  SDL_KeyboardEvent sdl{};

  SDL_Keysym keysym{};
  keysym.mod = KMOD_LALT | KMOD_CAPS;

  sdl.keysym = keysym;

  const cen::keyboard_event event{sdl};

  // Check that multiple key modifiers can be active at the same time
  ASSERT_TRUE(event.is_active(cen::KeyMod::LAlt));
  ASSERT_TRUE(event.is_active(cen::KeyMod::Caps));
}

TEST(keyboard_event, AsSDLEvent)
{
  const cen::keyboard_event event;
  const auto underlying = cen::as_sdl_event(event);

  ASSERT_EQ(underlying.key.type, cen::to_underlying(event.type()));
  ASSERT_EQ(underlying.key.timestamp, event.timestamp().count());
}
