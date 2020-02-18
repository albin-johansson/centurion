#include <utility>

#include "catch.hpp"
#include "event.h"
#include "window.h"

using namespace centurion;
using namespace centurion::event;
using namespace centurion::video;

namespace {

std::pair<KeyEvent, KeyEvent> get_events_one_mod_active(
    KeyModifier leftMod, KeyModifier rightMod) noexcept
{
  const auto left = [leftMod]() noexcept {
    SDL_KeyboardEvent sdlEvent{};
    sdlEvent.keysym.mod = static_cast<int>(leftMod);
    return KeyEvent{sdlEvent};
  }();
  const auto right = [rightMod]() noexcept {
    SDL_KeyboardEvent sdlEvent{};
    sdlEvent.keysym.mod = static_cast<int>(rightMod);
    return KeyEvent{sdlEvent};
  }();
  return {left, right};
}

KeyEvent get_event_mod_flags(int modifierFlags) noexcept
{
  return [modifierFlags]() noexcept {
    SDL_KeyboardEvent sdlEvent{};
    sdlEvent.keysym.mod = modifierFlags;
    return KeyEvent{sdlEvent};
  }();
}

}  // namespace

TEST_CASE("KeyEvent::is_key_active(SDL_Keycode)", "[KeyEvent]")
{
  const SDL_Keycode kcode = SDLK_DOLLAR;
  const auto makeKeyboardEvent = [kcode]() noexcept {
    SDL_KeyboardEvent keyboardEvent{};
    keyboardEvent.keysym = {SDL_SCANCODE_UNKNOWN, kcode};
    return keyboardEvent;
  };
  const KeyEvent event{makeKeyboardEvent()};

  CHECK(event.is_key_active(kcode));
  CHECK(!event.is_key_active(kcode + 1));
}

TEST_CASE("KeyEvent::is_key_active(SDL_Scancode)", "[KeyEvent]")
{
  const SDL_Scancode scode = SDL_SCANCODE_L;
  const auto makeKeyboardEvent = [scode]() noexcept {
    SDL_KeyboardEvent keyboardEvent{};
    keyboardEvent.keysym = {scode};
    return keyboardEvent;
  };
  const KeyEvent event{makeKeyboardEvent()};

  CHECK(event.is_key_active(scode));
  CHECK(!event.is_key_active(scode + 1));
}

TEST_CASE("KeyEvent::is_modifier_active", "[KeyEvent]")
{
  const auto makeKeyboardEvent = []() noexcept {
    SDL_KeyboardEvent keyboardEvent{};
    SDL_Keysym keysym{};
    keysym.mod = KMOD_LALT | KMOD_CAPS;
    keyboardEvent.keysym = keysym;
    return keyboardEvent;
  };
  const KeyEvent event{makeKeyboardEvent()};

  SECTION("Check that multiple key modifiers can be active at the same time")
  {
    CHECK(event.is_modifier_active(KeyModifier::LeftAlt));
    CHECK(event.is_modifier_active(KeyModifier::Caps));
  }
}

TEST_CASE("KeyEvent::is_control_active", "[KeyEvent]")
{
  SECTION("No modifiers")
  {
    const KeyEvent event{{}};
    CHECK(!event.is_control_active());
  }

  SECTION("One active modifier")
  {
    const auto [left, right] = get_events_one_mod_active(
        KeyModifier::LeftControl, KeyModifier::RightControl);
    CHECK(left.is_control_active());
    CHECK(right.is_control_active());
  }

  SECTION("Both modifiers active")
  {
    const KeyEvent event = get_event_mod_flags(KMOD_LCTRL | KMOD_RCTRL);
    CHECK(event.is_control_active());
  }

  SECTION("With noise (other modifiers)")
  {
    const KeyEvent event =
        get_event_mod_flags(KMOD_LCTRL | KMOD_RCTRL | KMOD_CAPS | KMOD_LSHIFT);
    CHECK(event.is_control_active());
  }
}

TEST_CASE("KeyEvent::is_shift_active", "[KeyEvent]")
{
  SECTION("No modifiers")
  {
    const KeyEvent event{{}};
    CHECK(!event.is_shift_active());
  }

  SECTION("One active modifier")
  {
    const auto [left, right] = get_events_one_mod_active(
        KeyModifier::LeftShift, KeyModifier::RightShift);
    CHECK(left.is_shift_active());
    CHECK(right.is_shift_active());
  }

  SECTION("Both modifiers active")
  {
    const KeyEvent event = get_event_mod_flags(KMOD_LSHIFT | KMOD_RSHIFT);
    CHECK(event.is_shift_active());
  }

  SECTION("With noise (other modifiers)")
  {
    const KeyEvent event =
        get_event_mod_flags(KMOD_LSHIFT | KMOD_RSHIFT | KMOD_CAPS | KMOD_LGUI);
    CHECK(event.is_shift_active());
  }
}

TEST_CASE("KeyEvent::is_alt_active", "[KeyEvent]")
{
  SECTION("No modifiers")
  {
    const KeyEvent event{{}};
    CHECK(!event.is_alt_active());
  }

  SECTION("One active modifier")
  {
    const auto [left, right] =
        get_events_one_mod_active(KeyModifier::LeftAlt, KeyModifier::RightAlt);
    CHECK(left.is_alt_active());
    CHECK(right.is_alt_active());
  }

  SECTION("Both modifiers active")
  {
    const KeyEvent event = get_event_mod_flags(KMOD_LALT | KMOD_RALT);
    CHECK(event.is_alt_active());
  }

  SECTION("With noise (other modifiers)")
  {
    const KeyEvent event =
        get_event_mod_flags(KMOD_LALT | KMOD_RALT | KMOD_RCTRL | KMOD_RGUI);
    CHECK(event.is_alt_active());
  }
}

TEST_CASE("KeyEvent::is_gui_active", "[KeyEvent]")
{
  SECTION("No modifiers")
  {
    const KeyEvent event{{}};
    CHECK(!event.is_gui_active());
  }

  SECTION("One active modifier")
  {
    const auto [left, right] =
        get_events_one_mod_active(KeyModifier::LeftGUI, KeyModifier::RightGUI);
    CHECK(left.is_gui_active());
    CHECK(right.is_gui_active());
  }

  SECTION("Both modifiers active")
  {
    const KeyEvent event = get_event_mod_flags(KMOD_LGUI | KMOD_RGUI);
    CHECK(event.is_gui_active());
  }

  SECTION("With noise (other modifiers)")
  {
    const KeyEvent event =
        get_event_mod_flags(KMOD_LGUI | KMOD_RGUI | KMOD_RCTRL | KMOD_RSHIFT);
    CHECK(event.is_gui_active());
  }
}

TEST_CASE("KeyEvent::is_repeated", "[KeyEvent]")
{
  const auto event_no_repeat = KeyEvent{{}};
  const auto event_one_repeat = []() noexcept {
    SDL_KeyboardEvent sdlEvent{};
    sdlEvent.repeat = 1;
    return KeyEvent{sdlEvent};
  }();
  const auto event_two_repeats = []() noexcept {
    SDL_KeyboardEvent sdlEvent{};
    sdlEvent.repeat = 2;
    return KeyEvent{sdlEvent};
  }();
  CHECK(!event_no_repeat.is_repeated());
  CHECK(event_one_repeat.is_repeated());
  CHECK(event_two_repeats.is_repeated());
}

TEST_CASE("KeyEvent::get_state", "[KeyEvent]")
{
  SECTION("Check valid state")
  {
    const auto event = []() noexcept {
      SDL_KeyboardEvent sdlEvent{};

      sdlEvent.keysym.sym = SDLK_ESCAPE;
      sdlEvent.state = SDL_PRESSED;

      return KeyEvent{sdlEvent};
    }();
    CHECK(event.get_state() == ButtonState::Pressed);
  }

  SECTION("Default button state")
  {
    const KeyEvent event{{}};
    CHECK(event.get_state() == ButtonState::Released);
  }
}

TEST_CASE("KeyEvent::get_window_id", "[KeyEvent]")
{
  const Window window;
  const uint32_t windowID = static_cast<uint32_t>(window.get_id());
  const auto event = [windowID]() noexcept {
    SDL_KeyboardEvent sdlEvent{};
    sdlEvent.windowID = windowID;
    return KeyEvent{sdlEvent};
  }();
  CHECK(event.get_window_id() == windowID);
}

TEST_CASE("KeyEvent::get_time", "[KeyEvent]")
{
  const auto time = SDL_GetTicks();
  const auto event = [time]() noexcept {
    SDL_KeyboardEvent sdlEvent{};
    sdlEvent.timestamp = time;
    return KeyEvent{sdlEvent};
  }();

  CHECK(event.get_time() == time);
}