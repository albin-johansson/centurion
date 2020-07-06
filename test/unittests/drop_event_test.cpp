#include "drop_event.hpp"

#include <catch.hpp>

using namespace centurion::event;

TEST_CASE("DropEvent move constructor", "[DropEvent]")
{
  CHECK_NOTHROW(DropEvent{{}});
}

TEST_CASE("DropEvent::set_will_free_file", "[DropEvent]")
{
  DropEvent event;

  event.set_will_free_file(true);
  CHECK(event.will_free_file());

  event.set_will_free_file(false);
  CHECK(!event.will_free_file());
}

TEST_CASE("DropEvent::set_file", "[DropEvent]")
{
  DropEvent event;
  CHECK_NOTHROW(event.set_file(nullptr));

  // This is the only time in the tests that a DropEvent should free the file,
  // check the code coverage reports in order to see if it's freed.
  auto* file = static_cast<char*>(SDL_malloc(sizeof(char)));
  event.set_file(file);
  event.set_will_free_file(true);
}

TEST_CASE("DropEvent::set_window_id", "[DropEvent]")
{
  DropEvent event;

  const auto id = 84;
  event.set_window_id(id);

  CHECK(event.window_id() == id);
}

TEST_CASE("DropEvent::will_free_file", "[DropEvent]")
{
  DropEvent event;
  CHECK(!event.will_free_file());
}

TEST_CASE("DropEvent::file", "[DropEvent]")
{
  char file = '1';  // pretend this is some raw data
  SDL_DropEvent sdlEvent;
  sdlEvent.file = &file;  // shouldn't be deleted, otherwise we're in trouble

  DropEvent event{sdlEvent};

  CHECK(event.file());
  CHECK(*event.file() == file);
}

TEST_CASE("DropEvent::window_id", "[DropEvent]")
{
  SDL_DropEvent sdlEvent{};
  sdlEvent.windowID = 32;
  sdlEvent.file = nullptr;

  DropEvent event{sdlEvent};

  CHECK(event.window_id() == sdlEvent.windowID);
}
