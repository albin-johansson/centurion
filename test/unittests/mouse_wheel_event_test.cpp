#include <catch.hpp>

#include "event.h"
#include "window.h"

using namespace centurion;
using namespace centurion::event;
using namespace centurion::video;

TEST_CASE("MouseWheelEvent(SDL_MouseWheelEvent)", "[MouseWheelEvent]")
{
  SDL_MouseWheelEvent sdlEvent{};
  CHECK_NOTHROW(MouseWheelEvent{sdlEvent});
}

TEST_CASE("MouseWheelEvent::get_horizontal_scroll", "[MouseWheelEvent]")
{
  const auto horizontalScroll = 75;
  const auto event = [horizontalScroll]() noexcept {
    SDL_MouseWheelEvent sdlEvent{};
    sdlEvent.x = horizontalScroll;
    return MouseWheelEvent{sdlEvent};
  }();
  CHECK(event.get_horizontal_scroll() == horizontalScroll);
}

TEST_CASE("MouseWheelEvent::get_vertical_scroll", "[MouseWheelEvent]")
{
  const auto verticalScroll = -46;
  const auto event = [verticalScroll]() noexcept {
    SDL_MouseWheelEvent sdlEvent{};
    sdlEvent.y = verticalScroll;
    return MouseWheelEvent{sdlEvent};
  }();
  CHECK(event.get_vertical_scroll() == verticalScroll);
}

TEST_CASE("MouseWheelEvent::get_wheel_direction", "[MouseWheelEvent]")
{
  const auto mk_event = [](uint32_t direction) noexcept {
    SDL_MouseWheelEvent sdlEvent{};
    sdlEvent.direction = direction;
    return MouseWheelEvent{sdlEvent};
  };

  SECTION("Normal")
  {
    const auto event = mk_event(SDL_MOUSEWHEEL_NORMAL);
    CHECK(event.get_wheel_direction() == MouseWheelDirection::Normal);
  }

  SECTION("Flipped")
  {
    const auto event = mk_event(SDL_MOUSEWHEEL_FLIPPED);
    CHECK(event.get_wheel_direction() == MouseWheelDirection::Flipped);
  }
}

TEST_CASE("MouseWheelEvent::was_touch", "[MouseWheelEvent]")
{
  const auto mk_event = [](uint32_t which) noexcept {
    SDL_MouseWheelEvent sdlEvent{};
    sdlEvent.which = which;
    return MouseWheelEvent{sdlEvent};
  };

  SECTION("Was touch")
  {
    const auto event = mk_event(SDL_TOUCH_MOUSEID);
    CHECK(event.was_touch());
  }

  SECTION("Wasn't touch")
  {
    const auto event = mk_event(0);
    CHECK(!event.was_touch());
  }
}

TEST_CASE("MouseWheelEvent::get_window_id", "[MouseWheelEvent]")
{
  Window window;
  const auto windowID = window.get_id();
  const auto event = [windowID]() noexcept {
    SDL_MouseWheelEvent sdlEvent{};
    sdlEvent.windowID = windowID;
    return MouseWheelEvent{sdlEvent};
  }();
  CHECK(event.get_window_id() == windowID);
}

TEST_CASE("MouseWheelEvent::get_time", "[MouseWheelEvent]")
{
  const auto time = 83914U;
  const auto event = [time]() noexcept {
    SDL_MouseWheelEvent sdlEvent{};
    sdlEvent.timestamp = time;
    return MouseWheelEvent{sdlEvent};
  }();
  CHECK(event.get_time() == time);
}