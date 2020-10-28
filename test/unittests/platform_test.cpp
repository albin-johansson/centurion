#include "platform.hpp"

#include <catch.hpp>
#include <string>

TEST_CASE("platform::id", "[platform]")
{
  CHECK_NOTHROW(cen::platform::id());

#ifdef __WIN32
  CHECK(cen::platform::id() == cen::platform::platform_id::windows);
#elif __APPLE__
  CHECK(cen::platform::id() == cen::platform::platform_id::mac_osx);
#elif __linux__
  CHECK(cen::platform::id() == cen::platform::platform_id::linuxx);
#elif __ANDROID__
  CHECK(cen::platform::id() == cen::platform::platform_id::android);
#endif
}

TEST_CASE("platform::is_windows", "[platform]")
{
  CHECK(cen::platform::is_windows() ==
        (cen::platform::id() == cen::platform::platform_id::windows));
}

TEST_CASE("platform::is_mac_osx", "[platform]")
{
  CHECK(cen::platform::is_mac_osx() ==
        (cen::platform::id() == cen::platform::platform_id::mac_osx));
}

TEST_CASE("platform::is_linux", "[platform]")
{
  CHECK(cen::platform::is_linux() ==
        (cen::platform::id() == cen::platform::platform_id::linuxx));
}

TEST_CASE("platform::is_ios", "[platform]")
{
  CHECK(cen::platform::is_ios() ==
        (cen::platform::id() == cen::platform::platform_id::ios));
}

TEST_CASE("platform::is_android", "[platform]")
{
  CHECK(cen::platform::is_android() ==
        (cen::platform::id() == cen::platform::platform_id::android));
}

TEST_CASE("platform::name", "[platform]")
{
  CHECK(*cen::platform::name() == std::string{SDL_GetPlatform()});
}
