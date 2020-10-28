#include <catch.hpp>

#include "event.hpp"

TEST_CASE("WindowEventID operator==", "[window_event]")
{
  using wid = cen::window_event_id;

  CHECK(wid::none == SDL_WINDOWEVENT_NONE);
  CHECK(wid::shown == SDL_WINDOWEVENT_SHOWN);
  CHECK(wid::hidden == SDL_WINDOWEVENT_HIDDEN);
  CHECK(wid::exposed == SDL_WINDOWEVENT_EXPOSED);
  CHECK(wid::moved == SDL_WINDOWEVENT_MOVED);
  CHECK(wid::resized == SDL_WINDOWEVENT_RESIZED);
  CHECK(wid::size_changed == SDL_WINDOWEVENT_SIZE_CHANGED);
  CHECK(wid::minimized == SDL_WINDOWEVENT_MINIMIZED);
  CHECK(wid::maximized == SDL_WINDOWEVENT_MAXIMIZED);
  CHECK(wid::restored == SDL_WINDOWEVENT_RESTORED);
  CHECK(wid::enter == SDL_WINDOWEVENT_ENTER);
  CHECK(wid::leave == SDL_WINDOWEVENT_LEAVE);
  CHECK(wid::focus_gained == SDL_WINDOWEVENT_FOCUS_GAINED);
  CHECK(wid::focus_lost == SDL_WINDOWEVENT_FOCUS_LOST);
  CHECK(wid::close == SDL_WINDOWEVENT_CLOSE);
  CHECK(wid::take_focus == SDL_WINDOWEVENT_TAKE_FOCUS);
  CHECK(wid::hit_test == SDL_WINDOWEVENT_HIT_TEST);

  CHECK(SDL_WINDOWEVENT_NONE == wid::none);
  CHECK(SDL_WINDOWEVENT_SHOWN == wid::shown);
  CHECK(SDL_WINDOWEVENT_HIDDEN == wid::hidden);
  CHECK(SDL_WINDOWEVENT_EXPOSED == wid::exposed);
  CHECK(SDL_WINDOWEVENT_MOVED == wid::moved);
  CHECK(SDL_WINDOWEVENT_RESIZED == wid::resized);
  CHECK(SDL_WINDOWEVENT_SIZE_CHANGED == wid::size_changed);
  CHECK(SDL_WINDOWEVENT_MINIMIZED == wid::minimized);
  CHECK(SDL_WINDOWEVENT_MAXIMIZED == wid::maximized);
  CHECK(SDL_WINDOWEVENT_RESTORED == wid::restored);
  CHECK(SDL_WINDOWEVENT_ENTER == wid::enter);
  CHECK(SDL_WINDOWEVENT_LEAVE == wid::leave);
  CHECK(SDL_WINDOWEVENT_FOCUS_GAINED == wid::focus_gained);
  CHECK(SDL_WINDOWEVENT_FOCUS_LOST == wid::focus_lost);
  CHECK(SDL_WINDOWEVENT_CLOSE == wid::close);
  CHECK(SDL_WINDOWEVENT_TAKE_FOCUS == wid::take_focus);
  CHECK(SDL_WINDOWEVENT_HIT_TEST == wid::hit_test);
}

TEST_CASE("WindowEventID operator!=", "[window_event]")
{
  using wid = cen::window_event_id;

  CHECK(wid::resized != SDL_WINDOWEVENT_FOCUS_GAINED);
  CHECK(!(wid::leave != SDL_WINDOWEVENT_LEAVE));

  CHECK(SDL_WINDOWEVENT_MINIMIZED != wid::moved);
  CHECK(!(SDL_WINDOWEVENT_RESTORED != wid::restored));
}

TEST_CASE("window_event::event_id", "[window_event]")
{
  SDL_WindowEvent sdl{};
  sdl.event = SDL_WINDOWEVENT_FOCUS_GAINED;
  cen::window_event we{sdl};

  CHECK(we.event_id() == cen::window_event_id::focus_gained);
}

TEST_CASE("window_event constructors", "[window_event]")
{
  CHECK_NOTHROW(cen::window_event{});
  CHECK_NOTHROW(cen::window_event{SDL_WindowEvent{}});
}

TEST_CASE("window_event::data_1", "[window_event]")
{
  const auto width = 75;

  SDL_WindowEvent sdl{};
  sdl.event = SDL_WINDOWEVENT_RESIZED;
  sdl.data1 = width;
  cen::window_event we{sdl};

  CHECK(we.data_1() == width);
}

TEST_CASE("window_event::data_2", "[window_event]")
{
  const auto height = 54;

  SDL_WindowEvent sdl{};
  sdl.event = SDL_WINDOWEVENT_RESIZED;
  sdl.data2 = height;
  cen::window_event we{sdl};

  CHECK(we.data_2() == height);
}