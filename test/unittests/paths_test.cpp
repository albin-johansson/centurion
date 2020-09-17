#include "paths.hpp"

#include <catch.hpp>
#include <iostream>

#include "cen.hpp"

TEST_CASE("base_path()", "[path]")
{
  CHECK_NOTHROW(cen::base_path{});
}

TEST_CASE("base_path(base_path&&)", "[path]")
{
  cen::base_path path;
  cen::base_path other{std::move(path)};

  CHECK(!path.get());
  CHECK(other.get());
}

TEST_CASE("base_path::operator=(base_path&&)", "[path]")
{
  SECTION("Self-assignment")
  {
    cen::base_path path;
    path = std::move(path);
    CHECK(path.get());
  }

  SECTION("Normal usage")
  {
    cen::base_path path;
    cen::base_path other;

    other = std::move(path);

    CHECK(!path.get());
    CHECK(other.get());
  }
}

TEST_CASE("base_path::operator bool", "[path]")
{
  const cen::base_path path;
  CHECK(path);
}

TEST_CASE("base_path::get", "[path]")
{
  const cen::base_path path;
  CHECK(path.get());
}

TEST_CASE("base_path to_string", "[path]")
{
  const cen::base_path path;
  std::cout << "COUT: " << cen::to_string(path) << '\n';
}

TEST_CASE("base_path stream operator", "[path]")
{
  const cen::base_path path;
  std::cout << "<<: " << path << '\n';
}

TEST_CASE("pref_path(string&, string&)", "[path]")
{
  CHECK_NOTHROW(cen::pref_path{"centurion", "tests"});
}

TEST_CASE("pref_path(pref_path&&)", "[path]")
{
  cen::pref_path path{"centurion", "tests"};
  cen::pref_path other{std::move(path)};

  CHECK(!path.get());
  CHECK(other.get());
}

TEST_CASE("pref_path::operator=(pref_path&&)", "[path]")
{
  SECTION("Self-assignment")
  {
    cen::pref_path path{"centurion", "tests"};
    path = std::move(path);
    CHECK(path.get());
  }

  SECTION("Normal usage")
  {
    cen::pref_path path{"centurion", "tests"};
    cen::pref_path other{"centurion", "tests"};

    other = std::move(path);

    CHECK(!path.get());
    CHECK(other.get());
  }
}

TEST_CASE("pref_path::operator bool", "[path]")
{
  const cen::pref_path pref_path{"centurion", "tests"};
  CHECK(pref_path);
}

TEST_CASE("pref_path::get", "[path]")
{
  const cen::pref_path pref_path{"centurion", "tests"};
  CHECK(pref_path.get());
}

TEST_CASE("pref_path to_string", "[path]")
{
  const cen::pref_path path{"centurion", "tests"};
  std::cout << "COUT: " << cen::to_string(path) << '\n';
}

TEST_CASE("pref_path stream operator", "[path]")
{
  const cen::pref_path path{"centurion", "tests"};
  std::cout << "<<: " << path << '\n';
}