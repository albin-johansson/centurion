#include <gtest/gtest.h>

#include "events/event.hpp"
#include "input/keycodes.hpp"
#include "input/scancodes.hpp"

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

  constexpr auto shift = cen::key_mod::left_shift;
  constexpr auto caps = cen::key_mod::caps;

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

TEST(KeyboardEvent, SetWindowId)
{
  cen::keyboard_event event;

  constexpr auto id = 79;
  event.set_window_id(id);

  ASSERT_EQ(id, event.window_id());
}

TEST(KeyboardEvent, IsActive)
{
  SDL_KeyboardEvent sdl{};
  sdl.keysym.scancode = SDL_SCANCODE_Q;
  sdl.keysym.sym = SDLK_d;
  sdl.keysym.mod = KMOD_LSHIFT | KMOD_RALT;

  const cen::keyboard_event event{sdl};

  ASSERT_TRUE(event.is_active(cen::keycodes::d));
  ASSERT_TRUE(event.is_active(cen::scancodes::q));
  ASSERT_TRUE(event.is_active(cen::key_mod::left_shift));
  ASSERT_TRUE(event.is_active(cen::key_mod::right_alt));

  ASSERT_FALSE(event.is_active(cen::keycodes::x));
  ASSERT_FALSE(event.is_active(cen::scancodes::o));
  ASSERT_FALSE(event.is_active(cen::key_mod::gui));
}

TEST(KeyboardEvent, IsActiveModifier)
{
  SDL_KeyboardEvent sdl{};

  SDL_Keysym keysym{};
  keysym.mod = KMOD_LALT | KMOD_CAPS;

  sdl.keysym = keysym;

  const cen::keyboard_event event{sdl};

  // Check that multiple key modifiers can be active at the same time
  ASSERT_TRUE(event.is_active(cen::key_mod::left_alt));
  ASSERT_TRUE(event.is_active(cen::key_mod::alt));
  ASSERT_TRUE(event.is_active(cen::key_mod::caps));
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
  ASSERT_FALSE(event.is_only_active(cen::key_mod::left_shift));
  ASSERT_FALSE(event.is_only_active(cen::key_mod::right_shift));

  event.set_modifier(cen::key_mod::alt, true);
  ASSERT_FALSE(event.is_active(cen::key_mod::none));
  ASSERT_FALSE(event.is_only_active(cen::key_mod::none));
  ASSERT_TRUE(event.is_active(cen::key_mod::shift));
  ASSERT_TRUE(event.is_active(cen::key_mod::alt));
  ASSERT_FALSE(event.is_only_active(cen::key_mod::shift));
  ASSERT_FALSE(event.is_only_active(cen::key_mod::alt));

  event.set_modifier(cen::key_mod::alt, false);
  event.set_modifier(cen::key_mod::right_shift, false);
  ASSERT_FALSE(event.is_active(cen::key_mod::none));
  ASSERT_FALSE(event.is_only_active(cen::key_mod::none));
  ASSERT_TRUE(event.is_active(cen::key_mod::shift));
  ASSERT_TRUE(event.is_active(cen::key_mod::left_shift));
  ASSERT_FALSE(event.is_active(cen::key_mod::right_shift));
  ASSERT_FALSE(event.is_only_active(cen::key_mod::shift));
  ASSERT_TRUE(event.is_only_active(cen::key_mod::left_shift));
  ASSERT_FALSE(event.is_only_active(cen::key_mod::right_shift));
}

TEST(KeyboardEvent, IsOnlyAnyOfActive)
{
  cen::keyboard_event event;
  ASSERT_TRUE(event.is_active(cen::key_mod::none));
  ASSERT_TRUE(event.is_only_active(cen::key_mod::none));
  ASSERT_TRUE(event.is_only_any_of_active(cen::key_mod::none));
  ASSERT_FALSE(event.is_active(cen::key_mod::shift));
  ASSERT_FALSE(event.is_only_active(cen::key_mod::shift));
  ASSERT_FALSE(event.is_only_any_of_active(cen::key_mod::shift));

  event.set_modifier(cen::key_mod::left_shift, true);
  ASSERT_TRUE(event.is_active(cen::key_mod::shift));
  ASSERT_FALSE(event.is_only_active(cen::key_mod::shift));
  ASSERT_TRUE(event.is_only_any_of_active(cen::key_mod::shift));
  ASSERT_TRUE(event.is_only_any_of_active(cen::key_mod::left_shift));

  event.set_modifier(cen::key_mod::right_gui, true);
  ASSERT_TRUE(event.is_active(cen::key_mod::shift));
  ASSERT_FALSE(event.is_only_active(cen::key_mod::shift));
  ASSERT_FALSE(event.is_only_any_of_active(cen::key_mod::shift));

  ASSERT_TRUE(event.is_only_active(cen::key_mod::left_shift | cen::key_mod::right_gui));
  ASSERT_TRUE(
      event.is_only_any_of_active(cen::key_mod::left_shift | cen::key_mod::right_gui));
  ASSERT_TRUE(event.is_only_any_of_active(cen::key_mod::shift | cen::key_mod::gui));
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
    ASSERT_EQ(cen::button_state::released, event.state());
  }

  {  // Check valid state
    SDL_KeyboardEvent sdl{};

    sdl.keysym.sym = SDLK_ESCAPE;
    sdl.state = SDL_PRESSED;

    const cen::keyboard_event event{sdl};
    ASSERT_EQ(cen::button_state::pressed, event.state());
  }
}

TEST(KeyboardEvent, Released)
{
  {  // Released
    SDL_KeyboardEvent sdl{};
    sdl.state = SDL_RELEASED;

    const cen::keyboard_event event{sdl};
    ASSERT_TRUE(event.released());
    ASSERT_EQ(cen::button_state::released, event.state());
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
    ASSERT_EQ(cen::button_state::pressed, event.state());
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

  ASSERT_EQ(sdl.key.type, cen::to_underlying(event.type()));
  ASSERT_EQ(sdl.key.timestamp, event.time());
}
