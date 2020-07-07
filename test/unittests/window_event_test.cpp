#include <catch.hpp>

#include "event.hpp"

using namespace centurion::event;

TEST_CASE("WindowEventID operator==", "[WindowEvent]")
{
  using WID = WindowEventID;

  CHECK(WID::None == SDL_WINDOWEVENT_NONE);
  CHECK(WID::Shown == SDL_WINDOWEVENT_SHOWN);
  CHECK(WID::Hidden == SDL_WINDOWEVENT_HIDDEN);
  CHECK(WID::Exposed == SDL_WINDOWEVENT_EXPOSED);
  CHECK(WID::Moved == SDL_WINDOWEVENT_MOVED);
  CHECK(WID::Resized == SDL_WINDOWEVENT_RESIZED);
  CHECK(WID::SizeChanged == SDL_WINDOWEVENT_SIZE_CHANGED);
  CHECK(WID::Minimized == SDL_WINDOWEVENT_MINIMIZED);
  CHECK(WID::Maximized == SDL_WINDOWEVENT_MAXIMIZED);
  CHECK(WID::Restored == SDL_WINDOWEVENT_RESTORED);
  CHECK(WID::Enter == SDL_WINDOWEVENT_ENTER);
  CHECK(WID::Leave == SDL_WINDOWEVENT_LEAVE);
  CHECK(WID::FocusGained == SDL_WINDOWEVENT_FOCUS_GAINED);
  CHECK(WID::FocusLost == SDL_WINDOWEVENT_FOCUS_LOST);
  CHECK(WID::Close == SDL_WINDOWEVENT_CLOSE);
  CHECK(WID::TakeFocus == SDL_WINDOWEVENT_TAKE_FOCUS);
  CHECK(WID::HitTest == SDL_WINDOWEVENT_HIT_TEST);

  CHECK(SDL_WINDOWEVENT_NONE == WID::None);
  CHECK(SDL_WINDOWEVENT_SHOWN == WID::Shown);
  CHECK(SDL_WINDOWEVENT_HIDDEN == WID::Hidden);
  CHECK(SDL_WINDOWEVENT_EXPOSED == WID::Exposed);
  CHECK(SDL_WINDOWEVENT_MOVED == WID::Moved);
  CHECK(SDL_WINDOWEVENT_RESIZED == WID::Resized);
  CHECK(SDL_WINDOWEVENT_SIZE_CHANGED == WID::SizeChanged);
  CHECK(SDL_WINDOWEVENT_MINIMIZED == WID::Minimized);
  CHECK(SDL_WINDOWEVENT_MAXIMIZED == WID::Maximized);
  CHECK(SDL_WINDOWEVENT_RESTORED == WID::Restored);
  CHECK(SDL_WINDOWEVENT_ENTER == WID::Enter);
  CHECK(SDL_WINDOWEVENT_LEAVE == WID::Leave);
  CHECK(SDL_WINDOWEVENT_FOCUS_GAINED == WID::FocusGained);
  CHECK(SDL_WINDOWEVENT_FOCUS_LOST == WID::FocusLost);
  CHECK(SDL_WINDOWEVENT_CLOSE == WID::Close);
  CHECK(SDL_WINDOWEVENT_TAKE_FOCUS == WID::TakeFocus);
  CHECK(SDL_WINDOWEVENT_HIT_TEST == WID::HitTest);
}

TEST_CASE("WindowEventID operator!=", "[WindowEvent]")
{
  using WID = WindowEventID;

  CHECK(WID::Resized != SDL_WINDOWEVENT_FOCUS_GAINED);
  CHECK(!(WID::Leave != SDL_WINDOWEVENT_LEAVE));

  CHECK(SDL_WINDOWEVENT_MINIMIZED != WID::Moved);
  CHECK(!(SDL_WINDOWEVENT_RESTORED != WID::Restored));
}

TEST_CASE("WindowEvent::event_id", "[WindowEvent]")
{
  SDL_WindowEvent sdl{};
  sdl.event = SDL_WINDOWEVENT_FOCUS_GAINED;
  WindowEvent we{sdl};

  CHECK(we.event_id() == WindowEventID::FocusGained);
}

TEST_CASE("WindowEvent constructors", "[WindowEvent]")
{
  CHECK_NOTHROW(WindowEvent{});
  CHECK_NOTHROW(WindowEvent{SDL_WindowEvent{}});
}

TEST_CASE("WindowEvent::data_1", "[WindowEvent]")
{
  const auto width = 75;

  SDL_WindowEvent sdl{};
  sdl.event = SDL_WINDOWEVENT_RESIZED;
  sdl.data1 = width;
  WindowEvent we{sdl};

  CHECK(we.data_1() == width);
}

TEST_CASE("WindowEvent::data_2", "[WindowEvent]")
{
  const auto height = 54;

  SDL_WindowEvent sdl{};
  sdl.event = SDL_WINDOWEVENT_RESIZED;
  sdl.data2 = height;
  WindowEvent we{sdl};

  CHECK(we.data_2() == height);
}