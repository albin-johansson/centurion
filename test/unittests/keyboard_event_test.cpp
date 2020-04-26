#include <SDL.h>

#include <catch.hpp>

#include "event.h"

using namespace centurion;
using namespace event;

namespace {

auto get_events_one_mod_active(KeyModifier leftMod,
                               KeyModifier rightMod) noexcept
{
  const auto createEvent = [](KeyModifier modifier) noexcept {
    SDL_KeyboardEvent sdlEvent{};
    sdlEvent.keysym.mod = static_cast<int>(modifier);
    return KeyboardEvent{sdlEvent};
  };

  const auto left = createEvent(leftMod);
  const auto right = createEvent(rightMod);
  return std::pair<KeyboardEvent, KeyboardEvent>{left, right};
}

KeyboardEvent get_event_mod_flags(int modifierFlags) noexcept
{
  return [modifierFlags]() noexcept {
    SDL_KeyboardEvent sdlEvent{};
    sdlEvent.keysym.mod = modifierFlags;
    return KeyboardEvent{sdlEvent};
  }();
}

}  // namespace

TEST_CASE("KeyboardEvent::is_key_active(SDL_Keycode)", "[KeyboardEvent]")
{
  const auto keycode = SDLK_DOLLAR;
  const auto createEvent = [keycode]() noexcept {
    SDL_KeyboardEvent event{};
    event.keysym = {SDL_SCANCODE_UNKNOWN, keycode};
    return event;
  };
  const KeyboardEvent event{createEvent()};

  CHECK(event.is_key_active(keycode));
  CHECK(!event.is_key_active(keycode + 1));
}

TEST_CASE("KeyboardEvent::is_key_active(SDL_Scancode)", "[KeyboardEvent]")
{
  const auto scancode = SDL_SCANCODE_L;
  const auto createEvent = [scancode]() noexcept {
    SDL_KeyboardEvent keyboardEvent{};
    keyboardEvent.keysym = {scancode};
    return keyboardEvent;
  };

  const KeyboardEvent event{createEvent()};

  CHECK(event.is_key_active(scancode));
  CHECK(!event.is_key_active(scancode + 1));
}

TEST_CASE("KeyboardEvent::modifier_active", "[KeyboardEvent]")
{
  const auto createEvent = []() noexcept {
    SDL_KeyboardEvent event{};
    SDL_Keysym keysym{};
    keysym.mod = KMOD_LALT | KMOD_CAPS;
    event.keysym = keysym;
    return event;
  };

  const KeyboardEvent event{createEvent()};

  SECTION("Check that multiple key modifiers can be active at the same time")
  {
    CHECK(event.modifier_active(KeyModifier::LeftAlt));
    CHECK(event.modifier_active(KeyModifier::Caps));
  }
}

TEST_CASE("KeyboardEvent::ctrl_active", "[KeyboardEvent]")
{
  SECTION("No modifiers")
  {
    const KeyboardEvent event{{}};
    CHECK(!event.ctrl_active());
  }

  SECTION("One active modifier")
  {
    const auto [left, right] = get_events_one_mod_active(
        KeyModifier::LeftControl, KeyModifier::RightControl);
    CHECK(left.ctrl_active());
    CHECK(right.ctrl_active());
  }

  SECTION("Both modifiers active")
  {
    const KeyboardEvent event = get_event_mod_flags(KMOD_LCTRL | KMOD_RCTRL);
    CHECK(event.ctrl_active());
  }

  SECTION("With noise (other modifiers)")
  {
    const KeyboardEvent event =
        get_event_mod_flags(KMOD_LCTRL | KMOD_RCTRL | KMOD_CAPS | KMOD_LSHIFT);
    CHECK(event.ctrl_active());
  }
}

TEST_CASE("KeyboardEvent::shift_active", "[KeyboardEvent]")
{
  SECTION("No modifiers")
  {
    const KeyboardEvent event{{}};
    CHECK(!event.shift_active());
  }

  SECTION("One active modifier")
  {
    const auto [left, right] = get_events_one_mod_active(
        KeyModifier::LeftShift, KeyModifier::RightShift);
    CHECK(left.shift_active());
    CHECK(right.shift_active());
  }

  SECTION("Both modifiers active")
  {
    const KeyboardEvent event = get_event_mod_flags(KMOD_LSHIFT | KMOD_RSHIFT);
    CHECK(event.shift_active());
  }

  SECTION("With noise (other modifiers)")
  {
    const KeyboardEvent event =
        get_event_mod_flags(KMOD_LSHIFT | KMOD_RSHIFT | KMOD_CAPS | KMOD_LGUI);
    CHECK(event.shift_active());
  }
}

TEST_CASE("KeyboardEvent::alt_active", "[KeyboardEvent]")
{
  SECTION("No modifiers")
  {
    const KeyboardEvent event{{}};
    CHECK(!event.alt_active());
  }

  SECTION("One active modifier")
  {
    const auto [left, right] =
        get_events_one_mod_active(KeyModifier::LeftAlt, KeyModifier::RightAlt);
    CHECK(left.alt_active());
    CHECK(right.alt_active());
  }

  SECTION("Both modifiers active")
  {
    const KeyboardEvent event = get_event_mod_flags(KMOD_LALT | KMOD_RALT);
    CHECK(event.alt_active());
  }

  SECTION("With noise (other modifiers)")
  {
    const KeyboardEvent event =
        get_event_mod_flags(KMOD_LALT | KMOD_RALT | KMOD_RCTRL | KMOD_RGUI);
    CHECK(event.alt_active());
  }
}

TEST_CASE("KeyboardEvent::gui_active", "[KeyboardEvent]")
{
  SECTION("No modifiers")
  {
    const KeyboardEvent event{{}};
    CHECK(!event.gui_active());
  }

  SECTION("One active modifier")
  {
    const auto [left, right] =
        get_events_one_mod_active(KeyModifier::LeftGUI, KeyModifier::RightGUI);
    CHECK(left.gui_active());
    CHECK(right.gui_active());
  }

  SECTION("Both modifiers active")
  {
    const KeyboardEvent event = get_event_mod_flags(KMOD_LGUI | KMOD_RGUI);
    CHECK(event.gui_active());
  }

  SECTION("With noise (other modifiers)")
  {
    const KeyboardEvent event =
        get_event_mod_flags(KMOD_LGUI | KMOD_RGUI | KMOD_RCTRL | KMOD_RSHIFT);
    CHECK(event.gui_active());
  }
}

TEST_CASE("KeyboardEvent::caps_active", "[KeyboardEvent]")
{
  SECTION("No modifiers")
  {
    const KeyboardEvent event{{}};
    CHECK(!event.caps_active());
  }

  SECTION("Active")
  {
    // TODO
  }

  SECTION("With noise (other modifiers)")
  {
    const KeyboardEvent event =
        get_event_mod_flags(KMOD_RCTRL | KMOD_RSHIFT | KMOD_CAPS);
    CHECK(event.caps_active());
  }
}

TEST_CASE("KeyboardEvent::repeated", "[KeyboardEvent]")
{
  const auto create_event = [](int repeats) noexcept {
    SDL_KeyboardEvent sdlEvent{};
    sdlEvent.repeat = repeats;
    return KeyboardEvent{sdlEvent};
  };

  const auto event_no_repeat = create_event(0);
  const auto event_one_repeat = create_event(1);
  const auto event_two_repeats = create_event(2);

  CHECK(!event_no_repeat.repeated());
  CHECK(event_one_repeat.repeated());
  CHECK(event_two_repeats.repeated());
}

TEST_CASE("KeyboardEvent::state", "[KeyboardEvent]")
{
  SECTION("Check valid state")
  {
    const auto event = []() noexcept {
      SDL_KeyboardEvent sdlEvent{};

      sdlEvent.keysym.sym = SDLK_ESCAPE;
      sdlEvent.state = SDL_PRESSED;

      return KeyboardEvent{sdlEvent};
    }();
    CHECK(event.state() == ButtonState::Pressed);
  }

  SECTION("Default button state")
  {
    const KeyboardEvent event{{}};
    CHECK(event.state() == ButtonState::Released);
  }
}

TEST_CASE("KeyboardEvent::window_id", "[KeyboardEvent]")
{
  const auto windowID = 72;
  const auto event = [windowID]() noexcept {
    SDL_KeyboardEvent sdlEvent{};
    sdlEvent.windowID = windowID;
    return KeyboardEvent{sdlEvent};
  }();
  CHECK(event.window_id() == windowID);
}

TEST_CASE("KeyboardEvent::get_time", "[KeyboardEvent]")
{
  const auto time = SDL_GetTicks();
  const auto event = [time]() noexcept {
    SDL_KeyboardEvent sdlEvent{};
    sdlEvent.timestamp = time;
    return KeyboardEvent{sdlEvent};
  }();

  CHECK(event.time() == time);
}