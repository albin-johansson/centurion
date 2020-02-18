#include "system.h"

#include <SDL.h>

#include <string>

#include "catch.hpp"

using namespace centurion;

TEST_CASE("System::get_platform", "[System]")
{
  CHECK_NOTHROW(system::get_platform());
}

#ifdef CENTURION_HAS_OPTIONAL

TEST_CASE("System::get_platform_name", "[System]")
{
  const auto name = system::get_platform_name();
  const auto sdlName = std::string{SDL_GetPlatform()};
  CHECK(name == sdlName);
}

#endif