#include "paths.hpp"

#include <catch.hpp>

#include "centurion_as_ctn.hpp"

TEST_CASE("base_path()", "[base_path]")
{
  CHECK_NOTHROW(ctn::base_path{});
}

TEST_CASE("base_path(base_path&&)", "[base_path]")
{
  ctn::base_path path;
  ctn::base_path other{std::move(path)};

  CHECK(!path.get());
  CHECK(other.get());
}

TEST_CASE("base_path::operator=(base_path&&)", "[base_path]")
{
  SECTION("Self-assignment")
  {
    ctn::base_path path;
    path = std::move(path);
    CHECK(path.get());
  }

  SECTION("Normal usage")
  {
    ctn::base_path path;
    ctn::base_path other;

    other = std::move(path);

    CHECK(!path.get());
    CHECK(other.get());
  }
}

TEST_CASE("base_path::unique", "[base_path]")
{
  const auto path = ctn::base_path::unique();
  CHECK(path);
}

TEST_CASE("base_path::shared", "[base_path]")
{
  const auto path = ctn::base_path::shared();
  CHECK(path);
}

TEST_CASE("base_path::operator bool", "[base_path]")
{
  const ctn::base_path path;
  CHECK(path);
}

TEST_CASE("base_path::get", "[base_path]")
{
  const ctn::base_path path;
  CHECK(path.get());
}

TEST_CASE("pref_path(string&, string&)", "[pref_path]")
{
  CHECK_NOTHROW(ctn::pref_path{"centurion", "tests"});
}

TEST_CASE("pref_path(pref_path&&)", "[pref_path]")
{
  ctn::pref_path path{"centurion", "tests"};
  ctn::pref_path other{std::move(path)};

  CHECK(!path.get());
  CHECK(other.get());
}

TEST_CASE("pref_path::operator=(pref_path&&)", "[pref_path]")
{
  SECTION("Self-assignment")
  {
    ctn::pref_path path{"centurion", "tests"};
    path = std::move(path);
    CHECK(path.get());
  }

  SECTION("Normal usage")
  {
    ctn::pref_path path{"centurion", "tests"};
    ctn::pref_path other{"centurion", "tests"};

    other = std::move(path);

    CHECK(!path.get());
    CHECK(other.get());
  }
}

TEST_CASE("pref_path::unique", "[pref_path]")
{
  CHECK(ctn::pref_path::unique("centurion", "tests"));
}

TEST_CASE("pref_path::shared", "[pref_path]")
{
  CHECK(ctn::pref_path::shared("centurion", "tests"));
}

TEST_CASE("pref_path::operator bool", "[pref_path]")
{
  const ctn::pref_path pref_path{"centurion", "tests"};
  CHECK(pref_path);
}

TEST_CASE("pref_path::get", "[pref_path]")
{
  const ctn::pref_path pref_path{"centurion", "tests"};
  CHECK(pref_path.get());
}