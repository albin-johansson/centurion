#include <catch.hpp>

#include "centurion_as_ctn.hpp"
#include "event.hpp"

using dummy_t = SDL_QuitEvent;

TEST_CASE("common_event::set_time", "[common_event]")
{
  ctn::common_event<dummy_t> event;

  const auto time = 8934;
  event.set_time(time);

  CHECK(event.time() == time);
}

TEST_CASE("common_event::set_type", "[common_event]")
{
  ctn::common_event<dummy_t> event;

  const auto type = ctn::event_type::AppLowMemory;
  event.set_type(type);

  CHECK(event.type() == type);
}

TEST_CASE("common_event::time", "[common_event]")
{
  const auto time = 735;

  dummy_t dummy;
  dummy.timestamp = time;

  ctn::common_event<dummy_t> event{dummy};

  CHECK(event.time() == time);
}

TEST_CASE("common_event::type", "[common_event]")
{
  dummy_t dummy;
  dummy.type = SDL_MOUSEMOTION;

  ctn::common_event<dummy_t> event{dummy};

  CHECK(event.type() == ctn::event_type::MouseMotion);
}

TEST_CASE("common_event conversions", "[common_event]")
{
  dummy_t dummy;
  dummy.type = SDL_MOUSEMOTION;

  ctn::common_event<dummy_t> event{dummy};
  const auto internal = event.get();

  CHECK(internal.type == dummy.type);
}
