#include "drop_event.h"

#include <catch.hpp>

using namespace centurion::event;

TEST_CASE("DropEventType values", "[DropEvent]")
{
  using DET = DropEventType;
  CHECK(static_cast<SDL_EventType>(DET::Begin) == SDL_DROPBEGIN);
  CHECK(static_cast<SDL_EventType>(DET::File) == SDL_DROPFILE);
  CHECK(static_cast<SDL_EventType>(DET::Text) == SDL_DROPTEXT);
  CHECK(static_cast<SDL_EventType>(DET::Complete) == SDL_DROPCOMPLETE);
}

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
  CHECK_NOTHROW([] {
    DropEvent event;
    event.set_file(nullptr);
  });

  CHECK_NOTHROW([] {
    DropEvent event;

    // This is the only time in the test that a DropEvent should free the file,
    // check the code coverage reports in order to see if it's freed.
    auto* file = static_cast<char*>(SDL_malloc(sizeof(char)));
    event.set_file(file);
  });
}

TEST_CASE("DropEvent::set_window_id", "[DropEvent]")
{
  DropEvent event;

  const auto id = 84;
  event.set_window_id(id);

  CHECK(event.window_id() == id);
}

TEST_CASE("DropEvent::set_type", "[DropEvent]")
{
  DropEvent event;

  const auto type = DropEventType::File;
  event.set_type(type);

  CHECK(event.type() == type);
}

TEST_CASE("DropEvent::will_free_file", "[DropEvent]")
{
  DropEvent event;
  CHECK(event.will_free_file());
}

TEST_CASE("DropEvent::file", "[DropEvent]")
{
  char file = '1';  // pretend this is some raw data
  SDL_DropEvent sdlEvent;
  sdlEvent.file = &file;  // shouldn't be deleted, otherwise we're in trouble

  DropEvent event{sdlEvent};
  event.set_will_free_file(false);

  CHECK(event.file());
  CHECK(*event.file() == file);
}

TEST_CASE("DropEvent::window_id", "[DropEvent]")
{
  SDL_DropEvent sdlEvent;
  sdlEvent.windowID = 32;

  DropEvent event{sdlEvent};

  CHECK(event.window_id() == sdlEvent.windowID);
}

TEST_CASE("DropEvent::type", "[DropEvent]")
{
  SDL_DropEvent sdlEvent;
  sdlEvent.type = SDL_DROPCOMPLETE;
  DropEvent event{sdlEvent};

  CHECK(event.type() == DropEventType::Complete);
}