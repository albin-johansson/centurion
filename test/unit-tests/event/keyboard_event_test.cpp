#include <gtest/gtest.h>

#include "events/event.hpp"
#include "keyboard.hpp"

TEST(KeyboardEvent, Defaults)
{
  cen::keyboard_event event;
  ASSERT_GT(event.time(), 0u);
  ASSERT_EQ(cen::event_type::key_down, event.type());
}

TEST(KeyboardEvent, SetScanCode)
{
  cen::keyboard_event event;

  event.set_scan_code(cen::scancodes::b);
  ASSERT_EQ(cen::scancodes::b, event.get_scan_code());
}

TEST(KeyboardEvent, SetKeyCode)
{
  cen::keyboard_event event;

  event.set_key_code(cen::keycodes::n);
  ASSERT_EQ(cen::keycodes::n, event.get_key_code());
}

TEST(KeyboardEvent, SetModifier)
{
  cen::keyboard_event event;

  constexpr auto Shift = cen::KeyMod::LShift;
  constexpr auto caps = cen::KeyMod::Caps;

  event.set_modifier(Shift, true);
  ASSERT_TRUE(event.is_active(Shift));

  event.set_modifier(caps, true);
  ASSERT_TRUE(event.is_active(Shift));
  ASSERT_TRUE(event.is_active(caps));

  event.set_modifier(Shift, false);
  ASSERT_FALSE(event.is_active(Shift));
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

TEST(KeyboardEvent, SetWindowId)
{
  cen::keyboard_event event;

  constexpr Uint32 id = 79;
  event.set_window_id(id);

  ASSERT_EQ(id, event.window_id());
}

TEST(KeyboardEvent, SetButtonState)
{
  cen::keyboard_event event;

  event.set_button_state(cen::ButtonState::Pressed);
  ASSERT_TRUE(event.pressed());
  ASSERT_FALSE(event.released());
  ASSERT_EQ(cen::ButtonState::Pressed, event.state());

  event.set_button_state(cen::ButtonState::Released);
  ASSERT_TRUE(event.released());
  ASSERT_FALSE(event.pressed());
  ASSERT_EQ(cen::ButtonState::Released, event.state());
}

TEST(KeyboardEvent, IsActive)
{
  SDL_KeyboardEvent sdl{};
  sdl.keysym.scancode = SDL_SCANCODE_Q;
  sdl.keysym.sym = SDLK_d;

  const cen::keyboard_event event{sdl};

  ASSERT_TRUE(event.is_active(cen::keycodes::d));
  ASSERT_TRUE(event.is_active(cen::scancodes::q));

  ASSERT_FALSE(event.is_active(cen::keycodes::x));
  ASSERT_FALSE(event.is_active(cen::scancodes::o));
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

TEST(KeyboardEvent, Repeated)
{
  cen::keyboard_event event;
  ASSERT_FALSE(event.repeated());

  event.set_repeated(true);
  ASSERT_TRUE(event.repeated());
}

TEST(KeyboardEvent, State)
{
  {  // Default button state
    const cen::keyboard_event event;
    ASSERT_EQ(cen::ButtonState::Released, event.state());
  }

  {  // Check valid state
    SDL_KeyboardEvent sdl{};

    sdl.keysym.sym = SDLK_ESCAPE;
    sdl.state = SDL_PRESSED;

    const cen::keyboard_event event{sdl};
    ASSERT_EQ(cen::ButtonState::Pressed, event.state());
  }
}

TEST(KeyboardEvent, Released)
{
  {  // Released
    SDL_KeyboardEvent sdl{};
    sdl.state = SDL_RELEASED;

    const cen::keyboard_event event{sdl};
    ASSERT_TRUE(event.released());
    ASSERT_EQ(cen::ButtonState::Released, event.state());
  }

  {  // Not released
    SDL_KeyboardEvent sdl{};
    sdl.state = SDL_PRESSED;

    const cen::keyboard_event event{sdl};
    ASSERT_FALSE(event.released());
  }
}

TEST(KeyboardEvent, Pressed)
{
  {  // Pressed
    SDL_KeyboardEvent sdl{};
    sdl.state = SDL_PRESSED;

    const cen::keyboard_event event{sdl};
    ASSERT_TRUE(event.pressed());
    ASSERT_EQ(cen::ButtonState::Pressed, event.state());
  }

  {  // Not pressed
    SDL_KeyboardEvent sdl{};
    sdl.state = SDL_RELEASED;

    const cen::keyboard_event event{sdl};
    ASSERT_FALSE(event.pressed());
  }
}

TEST(KeyboardEvent, GetScanCode)
{
  cen::keyboard_event event;

  constexpr auto code = cen::scancodes::q;
  event.set_scan_code(code);

  ASSERT_EQ(code, event.get_scan_code());
}

TEST(KeyboardEvent, GetKeyCode)
{
  cen::keyboard_event event;

  constexpr auto code = cen::keycodes::x;
  event.set_key_code(code);

  ASSERT_EQ(code, event.get_key_code());
}

TEST(KeyboardEvent, WindowId)
{
  SDL_KeyboardEvent sdl{};
  sdl.windowID = 72;

  const cen::keyboard_event event{sdl};
  ASSERT_EQ(sdl.windowID, event.window_id());
}

TEST(KeyboardEvent, AsSDLEvent)
{
  const cen::keyboard_event event;
  const auto sdl = cen::as_sdl_event(event);

  ASSERT_EQ(sdl.key.type, cen::ToUnderlying(event.type()));
  ASSERT_EQ(sdl.key.timestamp, event.time());
}
