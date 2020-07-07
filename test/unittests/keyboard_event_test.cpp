#include <SDL.h>

#include <catch.hpp>

#include "event.hpp"

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

TEST_CASE("KeyboardEvent::set_key", "[KeyboardEvent]")
{
  KeyboardEvent event;

  event.set_key(SDLK_b, ButtonState::Pressed);
  CHECK(event.key() == Key{SDLK_b});
  CHECK(event.state() == ButtonState::Pressed);

  event.set_key(SDL_SCANCODE_Q, ButtonState::Released);
  CHECK(event.key() == Key{SDL_SCANCODE_Q});
  CHECK(event.state() == ButtonState::Released);
}

TEST_CASE("KeyboardEvent::set_modifier", "[KeyboardEvent]")
{
  KeyboardEvent event;

  const auto shift = KeyModifier::LeftShift;
  const auto caps = KeyModifier::Caps;

  event.set_modifier(shift, true);
  CHECK(event.modifier_active(shift));

  event.set_modifier(caps, true);

  CHECK(event.modifier_active(shift));
  CHECK(event.modifier_active(caps));

  event.set_modifier(shift, false);
  CHECK(!event.modifier_active(shift));
  CHECK(event.modifier_active(caps));
}

TEST_CASE("KeyboardEvent::set_repeated", "[KeyboardEvent]")
{
  KeyboardEvent event;
  event.set_repeated(true);
  CHECK(event.repeated());
  event.set_repeated(false);
  CHECK(!event.repeated());
}

TEST_CASE("KeyboardEvent::set_window_id", "[KeyboardEvent]")
{
  KeyboardEvent event;
  const auto id = 79U;
  event.set_window_id(id);
  CHECK(event.window_id() == id);
}

TEST_CASE("KeyboardEvent::is_active", "[KeyboardEvent]")
{
  const auto createEvent = [](Key key) noexcept {
    SDL_KeyboardEvent keyboardEvent{};
    keyboardEvent.keysym.scancode = key;
    keyboardEvent.keysym.sym = key;
    return keyboardEvent;
  };

  const KeyboardEvent event{createEvent(SDLK_q)};

  CHECK(event.is_active(SDLK_q));
  CHECK(event.is_active(SDL_SCANCODE_Q));

  CHECK(!event.is_active(SDLK_e));
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
    KeyboardEvent event;
    event.set_modifier(KeyModifier::Caps, true);
    CHECK(event.caps_active());
  }

  SECTION("With noise (other modifiers)")
  {
    const KeyboardEvent event =
        get_event_mod_flags(KMOD_RCTRL | KMOD_RSHIFT | KMOD_CAPS);
    CHECK(event.caps_active());
  }
}

TEST_CASE("KeyboardEvent::num_active", "[KeyboardEvent]")
{
  SECTION("No modifiers")
  {
    const KeyboardEvent event{{}};
    CHECK(!event.num_active());
  }

  SECTION("Active")
  {
    KeyboardEvent event;
    event.set_modifier(KeyModifier::Num, true);
    CHECK(event.num_active());
  }

  SECTION("With noise (other modifiers)")
  {
    const KeyboardEvent event =
        get_event_mod_flags(KMOD_RGUI | KMOD_RSHIFT | KMOD_NUM);
    CHECK(event.num_active());
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

TEST_CASE("KeyboardEvent::key", "[KeyboardEvent]")
{
  KeyboardEvent event;
  const Key original = SDLK_b;

  event.set_key(original, ButtonState::Pressed);
  const auto copy = event.key();

  CHECK(original == copy);
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