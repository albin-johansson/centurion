#include <catch.hpp>

#include "event.hpp"

using namespace centurion;

using DummyType = SDL_QuitEvent;

TEST_CASE("CommonEvent::set_time", "[CommonEvent]")
{
  common_event<DummyType> event;

  const auto time = 8934;
  event.set_time(time);

  CHECK(event.time() == time);
}

TEST_CASE("CommonEvent::set_type", "[CommonEvent]")
{
  common_event<DummyType> event;

  const auto type = EventType::AppLowMemory;
  event.set_type(type);

  CHECK(event.type() == type);
}

TEST_CASE("CommonEvent::time", "[CommonEvent]")
{
  const auto time = 735;

  DummyType dummy;
  dummy.timestamp = time;

  common_event<DummyType> event{dummy};

  CHECK(event.time() == time);
}

TEST_CASE("CommonEvent::type", "[CommonEvent]")
{
  DummyType dummy;
  dummy.type = SDL_MOUSEMOTION;

  common_event<DummyType> event{dummy};

  CHECK(event.type() == EventType::MouseMotion);
}

TEST_CASE("CommonEvent conversions", "[CommonEvent]")
{
  DummyType dummy;
  dummy.type = SDL_MOUSEMOTION;

  common_event<DummyType> event{dummy};
  const auto internal = event.get();

  CHECK(internal.type == dummy.type);
}
