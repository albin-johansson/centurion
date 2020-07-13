#include <catch.hpp>

#include "event.hpp"
#include "centurion_as_ctn.hpp"

TEST_CASE("drop_event move constructor", "[drop_event]")
{
  CHECK_NOTHROW(ctn::drop_event{{}});
}

TEST_CASE("drop_event::set_will_free_file", "[drop_event]")
{
  ctn::drop_event event;

  event.set_will_free_file(true);
  CHECK(event.will_free_file());

  event.set_will_free_file(false);
  CHECK(!event.will_free_file());
}

TEST_CASE("drop_event::set_file", "[drop_event]")
{
  ctn::drop_event event;
  CHECK_NOTHROW(event.set_file(nullptr));

  // This is the only time in the tests that a drop_event should free the file,
  // check the code coverage reports in order to see if it's freed.
  auto* file = static_cast<char*>(SDL_malloc(sizeof(char)));
  event.set_file(file);
  event.set_will_free_file(true);
}

TEST_CASE("drop_event::set_window_id", "[drop_event]")
{
  ctn::drop_event event;

  const auto id = 84;
  event.set_window_id(id);

  CHECK(event.window_id() == id);
}

TEST_CASE("drop_event::will_free_file", "[drop_event]")
{
  ctn::drop_event event;
  CHECK(!event.will_free_file());
}

TEST_CASE("drop_event::file", "[drop_event]")
{
  char file = '1';  // pretend this is some raw data
  SDL_DropEvent sdlEvent;
  sdlEvent.file = &file;  // shouldn't be deleted, otherwise we're in trouble

  ctn::drop_event event{sdlEvent};

  CHECK(event.file());
  CHECK(*event.file() == file);
}

TEST_CASE("drop_event::window_id", "[drop_event]")
{
  SDL_DropEvent sdlEvent{};
  sdlEvent.windowID = 32;
  sdlEvent.file = nullptr;

  ctn::drop_event event{sdlEvent};

  CHECK(event.window_id() == sdlEvent.windowID);
}
