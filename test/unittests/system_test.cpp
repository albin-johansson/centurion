#include "catch.hpp"
#include <string>
#include <SDL.h>
#include "system.h"

using namespace centurion;

TEST_CASE("System::get_platform", "[System]") {
  CHECK_NOTHROW(System::get_platform());
}

#ifdef CENTURION_HAS_OPTIONAL

TEST_CASE("System::get_platform_name", "[System]") {
  const auto name = System::get_platform_name();
  const auto sdlName = std::string{SDL_GetPlatform()};
  CHECK(name == sdlName);
}

#endif