#include <gtest/gtest.h>

#include "event.hpp"
#include "keyboard.hpp"

TEST(KeyboardEvent, Defaults)
{
  const cen::KeyboardEvent event;
  ASSERT_GT(event.GetTimestamp(), 0u);
  ASSERT_EQ(cen::EventType::KeyDown, event.GetType());
}

TEST(KeyboardEvent, SetScanCode)
{
  cen::KeyboardEvent event;

  event.SetScanCode(cen::scancodes::b);
  ASSERT_EQ(cen::scancodes::b, event.GetScanCode());
}

TEST(KeyboardEvent, SetKeyCode)
{
  cen::KeyboardEvent event;

  event.SetKeyCode(cen::keycodes::n);
  ASSERT_EQ(cen::keycodes::n, event.GetKeyCode());
}

TEST(KeyboardEvent, SetModifier)
{
  cen::KeyboardEvent event;

  const auto shift = cen::KeyMod::LShift;
  const auto caps = cen::KeyMod::Caps;

  event.SetModifier(shift, true);
  ASSERT_TRUE(event.IsActive(shift));

  event.SetModifier(caps, true);
  ASSERT_TRUE(event.IsActive(shift));
  ASSERT_TRUE(event.IsActive(caps));

  event.SetModifier(shift, false);
  ASSERT_FALSE(event.IsActive(shift));
  ASSERT_TRUE(event.IsActive(caps));
}

TEST(KeyboardEvent, SetRepeated)
{
  cen::KeyboardEvent event;

  event.SetRepeated(true);
  ASSERT_TRUE(event.IsRepeated());

  event.SetRepeated(false);
  ASSERT_FALSE(event.IsRepeated());
}

TEST(KeyboardEvent, SetWindowID)
{
  cen::KeyboardEvent event;

  event.SetWindowID(79);
  ASSERT_EQ(79u, event.GetWindowID());
}

TEST(KeyboardEvent, SetButtonState)
{
  cen::KeyboardEvent event;

  event.SetButtonState(cen::ButtonState::Pressed);
  ASSERT_EQ(cen::ButtonState::Pressed, event.GetState());
  ASSERT_TRUE(event.IsPressed());
  ASSERT_FALSE(event.IsReleased());

  event.SetButtonState(cen::ButtonState::Released);
  ASSERT_EQ(cen::ButtonState::Released, event.GetState());
  ASSERT_TRUE(event.IsReleased());
  ASSERT_FALSE(event.IsPressed());
}

TEST(KeyboardEvent, IsActive)
{
  cen::KeyboardEvent event;
  event.SetScanCode(cen::scancodes::q);
  event.SetKeyCode(cen::keycodes::d);

  ASSERT_TRUE(event.IsActive(cen::scancodes::q));
  ASSERT_TRUE(event.IsActive(cen::keycodes::d));

  ASSERT_FALSE(event.IsActive(cen::scancodes::o));
  ASSERT_FALSE(event.IsActive(cen::keycodes::x));
}

TEST(KeyboardEvent, IsOnlyActive)
{
  cen::KeyboardEvent event;
  ASSERT_TRUE(event.IsActive(cen::KeyMod::None));
  ASSERT_TRUE(event.IsOnlyActive(cen::KeyMod::None));
  ASSERT_FALSE(event.IsActive(cen::KeyMod::Shift));
  ASSERT_FALSE(event.IsOnlyActive(cen::KeyMod::Shift));

  event.SetModifier(cen::KeyMod::Shift, true);
  ASSERT_FALSE(event.IsActive(cen::KeyMod::None));
  ASSERT_FALSE(event.IsOnlyActive(cen::KeyMod::None));
  ASSERT_TRUE(event.IsActive(cen::KeyMod::Shift));
  ASSERT_TRUE(event.IsOnlyActive(cen::KeyMod::Shift));
  ASSERT_FALSE(event.IsOnlyActive(cen::KeyMod::LShift));
  ASSERT_FALSE(event.IsOnlyActive(cen::KeyMod::RShift));

  event.SetModifier(cen::KeyMod::Alt, true);
  ASSERT_FALSE(event.IsActive(cen::KeyMod::None));
  ASSERT_FALSE(event.IsOnlyActive(cen::KeyMod::None));
  ASSERT_TRUE(event.IsActive(cen::KeyMod::Shift));
  ASSERT_TRUE(event.IsActive(cen::KeyMod::Alt));
  ASSERT_FALSE(event.IsOnlyActive(cen::KeyMod::Shift));
  ASSERT_FALSE(event.IsOnlyActive(cen::KeyMod::Alt));

  event.SetModifier(cen::KeyMod::Alt, false);
  event.SetModifier(cen::KeyMod::RShift, false);
  ASSERT_FALSE(event.IsActive(cen::KeyMod::None));
  ASSERT_FALSE(event.IsOnlyActive(cen::KeyMod::None));
  ASSERT_TRUE(event.IsActive(cen::KeyMod::Shift));
  ASSERT_TRUE(event.IsActive(cen::KeyMod::LShift));
  ASSERT_FALSE(event.IsActive(cen::KeyMod::RShift));
  ASSERT_FALSE(event.IsOnlyActive(cen::KeyMod::Shift));
  ASSERT_TRUE(event.IsOnlyActive(cen::KeyMod::LShift));
  ASSERT_FALSE(event.IsOnlyActive(cen::KeyMod::RShift));
}

TEST(KeyboardEvent, IsOnlyAnyOfActive)
{
  cen::KeyboardEvent event;
  ASSERT_TRUE(event.IsActive(cen::KeyMod::None));
  ASSERT_TRUE(event.IsOnlyActive(cen::KeyMod::None));
  ASSERT_TRUE(event.IsOnlyAnyOfActive(cen::KeyMod::None));
  ASSERT_FALSE(event.IsActive(cen::KeyMod::Shift));
  ASSERT_FALSE(event.IsOnlyActive(cen::KeyMod::Shift));
  ASSERT_FALSE(event.IsOnlyAnyOfActive(cen::KeyMod::Shift));

  event.SetModifier(cen::KeyMod::LShift, true);
  ASSERT_TRUE(event.IsActive(cen::KeyMod::Shift));
  ASSERT_FALSE(event.IsOnlyActive(cen::KeyMod::Shift));
  ASSERT_TRUE(event.IsOnlyAnyOfActive(cen::KeyMod::Shift));
  ASSERT_TRUE(event.IsOnlyAnyOfActive(cen::KeyMod::LShift));

  event.SetModifier(cen::KeyMod::RGui, true);
  ASSERT_TRUE(event.IsActive(cen::KeyMod::Shift));
  ASSERT_FALSE(event.IsOnlyActive(cen::KeyMod::Shift));
  ASSERT_FALSE(event.IsOnlyAnyOfActive(cen::KeyMod::Shift));

  ASSERT_TRUE(event.IsOnlyActive(cen::KeyMod::LShift | cen::KeyMod::RGui));
  ASSERT_TRUE(event.IsOnlyAnyOfActive(cen::KeyMod::LShift | cen::KeyMod::RGui));
  ASSERT_TRUE(event.IsOnlyAnyOfActive(cen::KeyMod::Shift | cen::KeyMod::Gui));
}

TEST(KeyboardEvent, IsActiveModifier)
{
  SDL_KeyboardEvent sdl{};

  SDL_Keysym keysym{};
  keysym.mod = KMOD_LALT | KMOD_CAPS;

  sdl.keysym = keysym;

  const cen::KeyboardEvent event{sdl};

  // Check that multiple key modifiers can be active at the same time
  ASSERT_TRUE(event.IsActive(cen::KeyMod::LAlt));
  ASSERT_TRUE(event.IsActive(cen::KeyMod::Caps));
}

TEST(KeyboardEvent, AsSDLEvent)
{
  const cen::KeyboardEvent event;
  const auto underlying = cen::AsSDLEvent(event);

  ASSERT_EQ(underlying.key.type, cen::ToUnderlying(event.GetType()));
  ASSERT_EQ(underlying.key.timestamp, event.GetTimestamp());
}
