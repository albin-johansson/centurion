#include "paths.h"

#include <catch.hpp>

using namespace centurion;

TEST_CASE("BasePath()", "[BasePath]")
{
  CHECK_NOTHROW(BasePath{});
}

TEST_CASE("BasePath(BasePath&&)", "[BasePath]")
{
  BasePath path;
  BasePath other{std::move(path)};

  CHECK(!path.get());
  CHECK(other.get());
}

TEST_CASE("BasePath::operator=(BasePath&&)", "[BasePath]")
{
  SECTION("Self-assignment")
  {
    BasePath path;
    path = std::move(path);
    CHECK(path.get());
  }

  SECTION("Normal usage")
  {
    BasePath path;
    BasePath other;

    other = std::move(path);

    CHECK(!path.get());
    CHECK(other.get());
  }
}

TEST_CASE("BasePath::unique", "[BasePath]")
{
  const auto path = BasePath::unique();
  CHECK(path);
}

TEST_CASE("BasePath::shared", "[BasePath]")
{
  const auto path = BasePath::shared();
  CHECK(path);
}

TEST_CASE("BasePath::operator bool", "[BasePath]")
{
  const BasePath path;
  CHECK(path);
}

TEST_CASE("BasePath::get", "[BasePath]")
{
  const BasePath path;
  CHECK(path.get());
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