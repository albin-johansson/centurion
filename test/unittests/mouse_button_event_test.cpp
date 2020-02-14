#include "catch.hpp"
#include "event.h"
#include "window.h"

using namespace centurion;
using namespace centurion::event;
using namespace centurion::video;

TEST_CASE("MouseButtonEvent::get_button", "[MouseButtonEvent]") {
  const auto button = SDL_BUTTON_LEFT;
  const auto event = [button]() noexcept {
    SDL_MouseButtonEvent sdlEvent{};
    sdlEvent.button = button;
    return MouseButtonEvent{sdlEvent};
  }();
  CHECK(event.get_button() == static_cast<MouseButton>(button));
}

TEST_CASE("MouseButtonEvent::get_x", "[MouseButtonEvent]") {
  const auto x = 514;
  const auto event = [x]() noexcept {
    SDL_MouseButtonEvent sdlEvent{};
    sdlEvent.x = x;
    return MouseButtonEvent{sdlEvent};
  }();
  CHECK(x == event.get_x());
}

TEST_CASE("MouseButtonEvent::get_y", "[MouseButtonEvent]") {
  const auto y = 174;
  const auto event = [y]() noexcept {
    SDL_MouseButtonEvent sdlEvent{};
    sdlEvent.y = y;
    return MouseButtonEvent{sdlEvent};
  }();
  CHECK(y == event.get_y());
}

TEST_CASE("MouseButtonEvent::get_state", "[MouseButtonEvent]") {
  const auto state = SDL_PRESSED;
  const auto event = [state]() noexcept {
    SDL_MouseButtonEvent sdlEvent{};
    sdlEvent.state = state;
    return MouseButtonEvent{sdlEvent};
  }();
  CHECK(event.get_state() == static_cast<ButtonState>(state));
}

TEST_CASE("MouseButtonEvent::was_single_click", "[MouseButtonEvent]") {
  const auto nClicks = 1;
  const auto event = [nClicks]() noexcept {
    SDL_MouseButtonEvent sdlEvent{};
    sdlEvent.clicks = nClicks;
    return MouseButtonEvent{sdlEvent};
  }();
  CHECK(event.was_single_click());
  CHECK(!event.was_double_click());
}

TEST_CASE("MouseButtonEvent::was_double_click", "[MouseButtonEvent]") {
  const auto nClicks = 2;
  const auto event = [nClicks]() noexcept {
    SDL_MouseButtonEvent sdlEvent{};
    sdlEvent.clicks = nClicks;
    return MouseButtonEvent{sdlEvent};
  }();
  CHECK(event.was_double_click());
  CHECK(!event.was_single_click());
}

TEST_CASE("MouseButtonEvent::was_touch", "[MouseButtonEvent]") {
  SECTION("Was touch") {
    const auto event = []() noexcept {
      SDL_MouseButtonEvent sdlEvent{};
      sdlEvent.which = SDL_TOUCH_MOUSEID;
      return MouseButtonEvent{sdlEvent};
    }();
    CHECK(event.was_touch());
  }

  SECTION("Wasn't touch") {
    const auto event = []() noexcept {
      SDL_MouseButtonEvent sdlEvent{};
      sdlEvent.which = 0;
      return MouseButtonEvent{sdlEvent};
    }();
    CHECK(!event.was_touch());
  }
}

TEST_CASE("MouseButtonEvent::get_window_id", "[MouseButtonEvent]") {
  Window window;
  const auto windowID = static_cast<uint32_t>(window.get_id());
  const auto event = [windowID]() noexcept {
    SDL_MouseButtonEvent sdlEvent{};
    sdlEvent.windowID = windowID;
    return MouseButtonEvent{sdlEvent};
  }();
  CHECK(windowID == event.get_window_id());
}

TEST_CASE("MouseButtonEvent::get_time", "[MouseButtonEvent]") {
  const auto time = SDL_GetTicks();
  const auto event = [time]() noexcept {
    SDL_MouseButtonEvent sdlEvent{};
    sdlEvent.timestamp = time;
    return MouseButtonEvent{sdlEvent};
  }();
  CHECK(time == event.get_time());
}