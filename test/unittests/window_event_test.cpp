#include <catch.hpp>

#include "event.hpp"

using namespace centurion;

TEST_CASE("WindowEventID operator==", "[WindowEvent]")
{
  using WID = window_event_id;

  CHECK(WID::none == SDL_WINDOWEVENT_NONE);
  CHECK(WID::shown == SDL_WINDOWEVENT_SHOWN);
  CHECK(WID::hidden == SDL_WINDOWEVENT_HIDDEN);
  CHECK(WID::exposed == SDL_WINDOWEVENT_EXPOSED);
  CHECK(WID::moved == SDL_WINDOWEVENT_MOVED);
  CHECK(WID::resized == SDL_WINDOWEVENT_RESIZED);
  CHECK(WID::size_changed == SDL_WINDOWEVENT_SIZE_CHANGED);
  CHECK(WID::minimized == SDL_WINDOWEVENT_MINIMIZED);
  CHECK(WID::maximized == SDL_WINDOWEVENT_MAXIMIZED);
  CHECK(WID::restored == SDL_WINDOWEVENT_RESTORED);
  CHECK(WID::enter == SDL_WINDOWEVENT_ENTER);
  CHECK(WID::leave == SDL_WINDOWEVENT_LEAVE);
  CHECK(WID::focus_gained == SDL_WINDOWEVENT_FOCUS_GAINED);
  CHECK(WID::focus_lost == SDL_WINDOWEVENT_FOCUS_LOST);
  CHECK(WID::close == SDL_WINDOWEVENT_CLOSE);
  CHECK(WID::take_focus == SDL_WINDOWEVENT_TAKE_FOCUS);
  CHECK(WID::hit_test == SDL_WINDOWEVENT_HIT_TEST);

  CHECK(SDL_WINDOWEVENT_NONE == WID::none);
  CHECK(SDL_WINDOWEVENT_SHOWN == WID::shown);
  CHECK(SDL_WINDOWEVENT_HIDDEN == WID::hidden);
  CHECK(SDL_WINDOWEVENT_EXPOSED == WID::exposed);
  CHECK(SDL_WINDOWEVENT_MOVED == WID::moved);
  CHECK(SDL_WINDOWEVENT_RESIZED == WID::resized);
  CHECK(SDL_WINDOWEVENT_SIZE_CHANGED == WID::size_changed);
  CHECK(SDL_WINDOWEVENT_MINIMIZED == WID::minimized);
  CHECK(SDL_WINDOWEVENT_MAXIMIZED == WID::maximized);
  CHECK(SDL_WINDOWEVENT_RESTORED == WID::restored);
  CHECK(SDL_WINDOWEVENT_ENTER == WID::enter);
  CHECK(SDL_WINDOWEVENT_LEAVE == WID::leave);
  CHECK(SDL_WINDOWEVENT_FOCUS_GAINED == WID::focus_gained);
  CHECK(SDL_WINDOWEVENT_FOCUS_LOST == WID::focus_lost);
  CHECK(SDL_WINDOWEVENT_CLOSE == WID::close);
  CHECK(SDL_WINDOWEVENT_TAKE_FOCUS == WID::take_focus);
  CHECK(SDL_WINDOWEVENT_HIT_TEST == WID::hit_test);
}

TEST_CASE("WindowEventID operator!=", "[WindowEvent]")
{
  using WID = window_event_id;

  CHECK(WID::resized != SDL_WINDOWEVENT_FOCUS_GAINED);
  CHECK(!(WID::leave != SDL_WINDOWEVENT_LEAVE));

  CHECK(SDL_WINDOWEVENT_MINIMIZED != WID::moved);
  CHECK(!(SDL_WINDOWEVENT_RESTORED != WID::restored));
}

TEST_CASE("WindowEvent::event_id", "[WindowEvent]")
{
  SDL_WindowEvent sdl{};
  sdl.event = SDL_WINDOWEVENT_FOCUS_GAINED;
  window_event we{sdl};

  CHECK(we.event_id() == window_event_id::focus_gained);
}

TEST_CASE("WindowEvent constructors", "[WindowEvent]")
{
  CHECK_NOTHROW(window_event{});
  CHECK_NOTHROW(window_event{SDL_WindowEvent{}});
}

TEST_CASE("WindowEvent::data_1", "[WindowEvent]")
{
  const auto width = 75;

  SDL_WindowEvent sdl{};
  sdl.event = SDL_WINDOWEVENT_RESIZED;
  sdl.data1 = width;
  window_event we{sdl};

  CHECK(we.data_1() == width);
}

TEST_CASE("WindowEvent::data_2", "[WindowEvent]")
{
  const auto height = 54;

  SDL_WindowEvent sdl{};
  sdl.event = SDL_WINDOWEVENT_RESIZED;
  sdl.data2 = height;
  window_event we{sdl};

  CHECK(we.data_2() == height);
}