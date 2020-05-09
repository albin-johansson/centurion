#include "paths.h"

#include <catch.hpp>

using namespace centurion;

TEST_CASE("AppPath()", "[AppPath]")
{
  CHECK_NOTHROW(AppPath{});
}

TEST_CASE("AppPath(AppPath&&)", "[AppPath]")
{
  AppPath path;
  AppPath other{std::move(path)};

  CHECK(!path.get());
  CHECK(other.get());
}

TEST_CASE("AppPath::operator=(AppPath&&)", "[AppPath]")
{
  SECTION("Self-assignment")
  {
    AppPath path;
    path = std::move(path);
    CHECK(path.get());
  }

  SECTION("Normal usage")
  {
    AppPath path;
    AppPath other;

    other = std::move(path);

    CHECK(!path.get());
    CHECK(other.get());
  }
}

TEST_CASE("AppPath::operator bool", "[AppPath]")
{
  const AppPath appPath;
  CHECK(appPath);
}

TEST_CASE("AppPath::unique", "[AppPath]")
{
  const auto appPath = AppPath::unique();
  CHECK(appPath);
}

TEST_CASE("AppPath::shared", "[AppPath]")
{
  const auto appPath = AppPath::shared();
  CHECK(appPath);
}

TEST_CASE("AppPath::get", "[AppPath]")
{
  const AppPath appPath;
  CHECK(appPath.get());
}

TEST_CASE("PrefPath(string&, string&)", "[PrefPath]")
{
  CHECK_NOTHROW(PrefPath{"centurion", "tests"});
}

TEST_CASE("PrefPath(PrefPath&&)", "[PrefPath]")
{
  PrefPath path{"centurion", "tests"};
  PrefPath other{std::move(path)};

  CHECK(!path.get());
  CHECK(other.get());
}

TEST_CASE("PrefPath::operator=(PrefPath&&)", "[PrefPath]")
{
  SECTION("Self-assignment")
  {
    PrefPath path{"centurion", "tests"};
    path = std::move(path);
    CHECK(path.get());
  }

  SECTION("Normal usage")
  {
    PrefPath path{"centurion", "tests"};
    PrefPath other{"centurion", "tests"};

    other = std::move(path);

    CHECK(!path.get());
    CHECK(other.get());
  }
}

TEST_CASE("PrefPath::unique", "[PrefPath]")
{
  CHECK(PrefPath::unique("centurion", "tests"));
}

TEST_CASE("PrefPath::shared", "[PrefPath]")
{
  CHECK(PrefPath::shared("centurion", "tests"));
}

TEST_CASE("PrefPath::operator bool", "[PrefPath]")
{
  const PrefPath prefPath{"centurion", "tests"};
  CHECK(prefPath);
}

TEST_CASE("PrefPath::get", "[PrefPath]")
{
  const PrefPath prefPath{"centurion", "tests"};
  CHECK(prefPath.get());
}