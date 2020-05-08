#include "platform.h"

#include <catch.hpp>
#include <string>

using namespace centurion;

TEST_CASE("Platform::id", "[Platform]")
{
  CHECK_NOTHROW(Platform::id());

#ifdef __WIN32
  CHECK(Platform::id() == PlatformID::Windows);
#elif __APPLE__
  CHECK(Platform::id() == PlatformID::MacOSX);
#elif __linux__
  CHECK(Platform::id() == PlatformID::Linux);
#elif __ANDROID__
  CHECK(Platform::id() == PlatformID::Android);
#endif
}

TEST_CASE("Platform::name", "[Platform]")
{
  CHECK(*Platform::name() == std::string{SDL_GetPlatform()});
}
