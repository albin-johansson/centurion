#include "catch.hpp"
#include "event.h"
#include "window.h"

using namespace centurion;
using namespace centurion::event;
using namespace centurion::video;

TEST_CASE("MouseMotionEvent::get_x", "[MouseMotionEvent]")
{
  const auto x = 451;
  const auto event = []() noexcept {
    SDL_MouseMotionEvent sdlEvent{};
    sdlEvent.x = x;
    return MouseMotionEvent{sdlEvent};
  }();

  CHECK(event.get_x() == x);
}

TEST_CASE("MouseMotionEvent::get_y", "[MouseMotionEvent]")
{
  const auto y = 814;
  const auto event = []() noexcept {
    SDL_MouseMotionEvent sdlEvent{};
    sdlEvent.y = y;
    return MouseMotionEvent{sdlEvent};
  }();

  CHECK(event.get_y() == y);
}

TEST_CASE("MouseMotionEvent::get_x_movement", "[MouseMotionEvent]")
{
  const auto dx = -52;
  const auto event = []() noexcept {
    SDL_MouseMotionEvent sdlEvent{};
    sdlEvent.xrel = dx;
    return MouseMotionEvent{sdlEvent};
  }();

  CHECK(event.get_x_movement() == dx);
}

TEST_CASE("MouseMotionEvent::get_y_movement", "[MouseMotionEvent]")
{
  const auto dy = 72;
  const auto event = []() noexcept {
    SDL_MouseMotionEvent sdlEvent{};
    sdlEvent.yrel = dy;
    return MouseMotionEvent{sdlEvent};
  }();

  CHECK(event.get_y_movement() == dy);
}

TEST_CASE("MouseMotionEvent::was_touch", "[MouseMotionEvent]")
{
  SECTION("Caused by touch")
  {
    const auto event = []() noexcept {
      SDL_MouseMotionEvent sdlEvent{};
      sdlEvent.which = SDL_TOUCH_MOUSEID;
      return MouseMotionEvent{sdlEvent};
    }();
    CHECK(event.was_touch());
  }
  SECTION("No touch")
  {
    const auto event = []() noexcept {
      SDL_MouseMotionEvent sdlEvent{};
      sdlEvent.which = 0;
      return MouseMotionEvent{sdlEvent};
    }();
    CHECK(!event.was_touch());
  }
}

TEST_CASE("MouseMotionEvent::is_button_down", "[MouseMotionEvent]")
{
  SECTION("Single button")
  {
    const auto button = SDL_BUTTON_LEFT;
    const auto event = [button]() noexcept {
      SDL_MouseMotionEvent sdlEvent{};
      sdlEvent.state = button;
      return MouseMotionEvent{sdlEvent};
    }();
    CHECK(event.is_button_down(static_cast<MouseButton>(button)));
  }

  SECTION("Multiple buttons")
  {
    const auto firstButton = SDL_BUTTON_LEFT;
    const auto secondButton = SDL_BUTTON_MIDDLE;
    const auto event = [firstButton, secondButton]() noexcept {
      SDL_MouseMotionEvent sdlEvent{};
      sdlEvent.state = firstButton | secondButton;
      return MouseMotionEvent{sdlEvent};
    }();
    CHECK(event.is_button_down(static_cast<MouseButton>(firstButton)));
    CHECK(event.is_button_down(static_cast<MouseButton>(secondButton)));
  }
}

TEST_CASE("MouseMotionEvent::get_window_id", "[MouseMotionEvent]")
{
  Window window;
  const auto windowID = static_cast<uint32_t>(window.get_id());
  const auto event = [windowID]() noexcept {
    SDL_MouseMotionEvent sdlEvent{};
    sdlEvent.windowID = windowID;
    return MouseMotionEvent{sdlEvent};
  }();
  CHECK(windowID == event.get_window_id());
}

TEST_CASE("MouseMotionEvent::get_time", "[MouseMotionEvent]")
{
  const auto time = SDL_GetTicks();
  const auto event = [time]() noexcept {
    SDL_MouseMotionEvent sdlEvent{};
    sdlEvent.timestamp = time;
    return MouseMotionEvent{sdlEvent};
  }();
  CHECK(time == event.get_time());
}