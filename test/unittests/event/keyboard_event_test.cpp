#include <gtest/gtest.h>

#include "event.hpp"

TEST(KeyboardEvent, SetScanCode)
{
  cen::keyboard_event event;

  event.set_scan_code(cen::scancodes::b);
  EXPECT_EQ(cen::scancodes::b, event.get_scan_code());
}

TEST(KeyboardEvent, SetKeyCode)
{
  cen::keyboard_event event;

  event.set_key_code(cen::keycodes::n);
  EXPECT_EQ(cen::keycodes::n, event.get_key_code());
}

TEST(KeyboardEvent, SetModifier)
{
  cen::keyboard_event event;

  constexpr auto shift = cen::key_modifier::left_shift;
  constexpr auto caps = cen::key_modifier::caps;

  event.set_modifier(shift, true);
  EXPECT_TRUE(event.modifier_active(shift));

  event.set_modifier(caps, true);
  EXPECT_TRUE(event.modifier_active(shift));
  EXPECT_TRUE(event.modifier_active(caps));

  event.set_modifier(shift, false);
  EXPECT_FALSE(event.modifier_active(shift));
  EXPECT_TRUE(event.modifier_active(caps));
}

TEST(KeyboardEvent, SetRepeated)
{
  cen::keyboard_event event;

  event.set_repeated(true);
  EXPECT_TRUE(event.repeated());

  event.set_repeated(false);
  EXPECT_FALSE(event.repeated());
}

TEST(KeyboardEvent, SetWindowId)
{
  cen::keyboard_event event;

  constexpr auto id = 79;
  event.set_window_id(id);

  EXPECT_EQ(id, event.window_id());
}

TEST(KeyboardEvent, IsActive)
{
  SDL_KeyboardEvent sdl{};
  sdl.keysym.scancode = SDL_SCANCODE_Q;
  sdl.keysym.sym = SDLK_d;

  const cen::keyboard_event event{sdl};

  EXPECT_TRUE(event.is_active(cen::keycodes::d));
  EXPECT_TRUE(event.is_active(cen::scancodes::q));

  EXPECT_FALSE(event.is_active(cen::keycodes::x));
  EXPECT_FALSE(event.is_active(cen::scancodes::o));
}

TEST(KeyboardEvent, ModifierActive)
{
  SDL_KeyboardEvent sdl{};

  SDL_Keysym keysym{};
  keysym.mod = KMOD_LALT | KMOD_CAPS;

  sdl.keysym = keysym;

  const cen::keyboard_event event{sdl};

  // Check that multiple key modifiers can be active at the same time
  EXPECT_TRUE(event.modifier_active(cen::key_modifier::left_alt));
  EXPECT_TRUE(event.modifier_active(cen::key_modifier::caps));
}

TEST(KeyboardEvent, ShiftActive)
{
  {  // No modifiers
    const cen::keyboard_event event;
    EXPECT_FALSE(event.shift_active());
  }

  {  // One modifier (Both LSHIFT and RSHIFT)
    SDL_KeyboardEvent sdl{};

    SDL_Keysym keysym{};
    keysym.mod = KMOD_SHIFT;

    sdl.keysym = keysym;

    const cen::keyboard_event event{sdl};
    EXPECT_TRUE(event.shift_active());
  }

  {  // With other modifiers
    SDL_KeyboardEvent sdl{};

    SDL_Keysym keysym{};
    keysym.mod = KMOD_RSHIFT | KMOD_CAPS | KMOD_LGUI;

    sdl.keysym = keysym;

    const cen::keyboard_event event{sdl};
    EXPECT_TRUE(event.shift_active());
  }
}

TEST(KeyboardEvent, CtrlActive)
{
  {  // No modifiers
    const cen::keyboard_event event;
    EXPECT_FALSE(event.ctrl_active());
  }

  {  // One modifier (Both LCTRL and RCTRL)
    SDL_KeyboardEvent sdl{};

    SDL_Keysym keysym{};
    keysym.mod = KMOD_CTRL;

    sdl.keysym = keysym;

    const cen::keyboard_event event{sdl};
    EXPECT_TRUE(event.ctrl_active());
  }

  {  // With other modifiers
    SDL_KeyboardEvent sdl{};

    SDL_Keysym keysym{};
    keysym.mod = KMOD_LCTRL | KMOD_ALT | KMOD_LGUI;

    sdl.keysym = keysym;

    const cen::keyboard_event event{sdl};
    EXPECT_TRUE(event.ctrl_active());
  }
}

TEST(KeyboardEvent, AltActive)
{
  {  // No modifiers
    const cen::keyboard_event event;
    EXPECT_FALSE(event.alt_active());
  }

  {  // One modifier (Both LALT and RALT)
    SDL_KeyboardEvent sdl{};

    SDL_Keysym keysym{};
    keysym.mod = KMOD_ALT;

    sdl.keysym = keysym;

    const cen::keyboard_event event{sdl};
    EXPECT_TRUE(event.alt_active());
  }

  {  // With other modifiers
    SDL_KeyboardEvent sdl{};

    SDL_Keysym keysym{};
    keysym.mod = KMOD_RALT | KMOD_RSHIFT | KMOD_CAPS;

    sdl.keysym = keysym;

    const cen::keyboard_event event{sdl};
    EXPECT_TRUE(event.alt_active());
  }
}

TEST(KeyboardEvent, GuiActive)
{
  {  // No modifiers
    const cen::keyboard_event event;
    EXPECT_FALSE(event.gui_active());
  }

  {  // One modifier (Both LGUI and RGUI)
    SDL_KeyboardEvent sdl{};

    SDL_Keysym keysym{};
    keysym.mod = KMOD_GUI;

    sdl.keysym = keysym;

    const cen::keyboard_event event{sdl};
    EXPECT_TRUE(event.gui_active());
  }

  {  // With other modifiers
    SDL_KeyboardEvent sdl{};

    SDL_Keysym keysym{};
    keysym.mod = KMOD_LGUI | KMOD_RSHIFT | KMOD_CAPS;

    sdl.keysym = keysym;

    const cen::keyboard_event event{sdl};
    EXPECT_TRUE(event.gui_active());
  }
}

TEST(KeyboardEvent, CapsActive)
{
  {  // No modifiers
    const cen::keyboard_event event;
    EXPECT_FALSE(event.caps_active());
  }

  {  // One modifier
    SDL_KeyboardEvent sdl{};

    SDL_Keysym keysym{};
    keysym.mod = KMOD_CAPS;

    sdl.keysym = keysym;

    const cen::keyboard_event event{sdl};
    EXPECT_TRUE(event.caps_active());
  }

  {  // With other modifiers
    SDL_KeyboardEvent sdl{};

    SDL_Keysym keysym{};
    keysym.mod = KMOD_CAPS | KMOD_RSHIFT | KMOD_LCTRL;

    sdl.keysym = keysym;

    const cen::keyboard_event event{sdl};
    EXPECT_TRUE(event.caps_active());
  }
}

TEST(KeyboardEvent, NumActive)
{
  {  // No modifiers
    const cen::keyboard_event event;
    EXPECT_FALSE(event.num_active());
  }

  {  // One modifier
    SDL_KeyboardEvent sdl{};

    SDL_Keysym keysym{};
    keysym.mod = KMOD_NUM;

    sdl.keysym = keysym;

    const cen::keyboard_event event{sdl};
    EXPECT_TRUE(event.num_active());
  }

  {  // With other modifiers
    SDL_KeyboardEvent sdl{};

    SDL_Keysym keysym{};
    keysym.mod = KMOD_NUM | KMOD_RSHIFT | KMOD_LCTRL;

    sdl.keysym = keysym;

    const cen::keyboard_event event{sdl};
    EXPECT_TRUE(event.num_active());
  }
}

TEST(KeyboardEvent, Repeated)
{
  const auto createEvent = [](const int repeats) noexcept {
    SDL_KeyboardEvent sdl{};
    sdl.repeat = repeats;
    return cen::keyboard_event{sdl};
  };

  const auto noRepeat = createEvent(0);
  const auto oneRepeat = createEvent(1);
  const auto twoRepeats = createEvent(2);

  EXPECT_FALSE(noRepeat.repeated());
  EXPECT_TRUE(oneRepeat.repeated());
  EXPECT_TRUE(twoRepeats.repeated());
}

TEST(KeyboardEvent, State)
{
  {  // Default button state
    const cen::keyboard_event event;
    EXPECT_EQ(cen::button_state::released, event.state());
  }

  {  // Check valid state
    SDL_KeyboardEvent sdl{};

    sdl.keysym.sym = SDLK_ESCAPE;
    sdl.state = SDL_PRESSED;

    const cen::keyboard_event event{sdl};
    EXPECT_EQ(cen::button_state::pressed, event.state());
  }
}

TEST(KeyboardEvent, Released)
{
  {  // Released
    SDL_KeyboardEvent sdl{};
    sdl.state = SDL_RELEASED;

    const cen::keyboard_event event{sdl};
    EXPECT_TRUE(event.released());
    EXPECT_EQ(cen::button_state::released, event.state());
  }

  {  // Not released
    SDL_KeyboardEvent sdl{};
    sdl.state = SDL_PRESSED;

    const cen::keyboard_event event{sdl};
    EXPECT_FALSE(event.released());
  }
}

TEST(KeyboardEvent, Pressed)
{
  {  // Pressed
    SDL_KeyboardEvent sdl{};
    sdl.state = SDL_PRESSED;

    const cen::keyboard_event event{sdl};
    EXPECT_TRUE(event.pressed());
    EXPECT_EQ(cen::button_state::pressed, event.state());
  }

  {  // Not pressed
    SDL_KeyboardEvent sdl{};
    sdl.state = SDL_RELEASED;

    const cen::keyboard_event event{sdl};
    EXPECT_FALSE(event.pressed());
  }
}

TEST(KeyboardEvent, GetScanCode)
{
  cen::keyboard_event event;

  constexpr auto code = cen::scancodes::q;
  event.set_scan_code(code);

  EXPECT_EQ(code, event.get_scan_code());
}

TEST(KeyboardEvent, GetKeyCode)
{
  cen::keyboard_event event;

  constexpr auto code = cen::keycodes::x;
  event.set_key_code(code);

  EXPECT_EQ(code, event.get_key_code());
}

TEST(KeyboardEvent, WindowId)
{
  SDL_KeyboardEvent sdl{};
  sdl.windowID = 72;

  const cen::keyboard_event event{sdl};
  EXPECT_EQ(sdl.windowID, event.window_id());
}
