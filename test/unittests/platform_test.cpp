#include "platform.hpp"

#include <catch.hpp>
#include <string>

#include "cen.hpp"

TEST_CASE("platform::id", "[platform]")
{
  CHECK_NOTHROW(cen::platform::id());

#ifdef __WIN32
  CHECK(ctn::platform::id() == ctn::platform::platform_id::windows);
#elif __APPLE__
  CHECK(ctn::platform::id() == ctn::platform::platform_id::mac_osx);
#elif __linux__
  CHECK(ctn::platform::id() == ctn::platform::platform_id::linux);
#elif __ANDROID__
  CHECK(ctn::platform::id() == ctn::platform::platform_id::android);
#endif
}

TEST_CASE("platform::name", "[platform]")
{
  CHECK(*cen::platform::name() == std::string{SDL_GetPlatform()});
}
