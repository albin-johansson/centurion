#include "catch.hpp"
#include "paths.h"

using namespace centurion;

TEST_CASE("AppPath()", "[AppPath]") {
  CHECK_NOTHROW(AppPath{});
}

TEST_CASE("AppPath::operator bool", "[AppPath]") {
  const AppPath appPath;
  CHECK(appPath);
}

TEST_CASE("AppPath::unique", "[AppPath]") {
  const auto appPath = AppPath::unique();
  CHECK(appPath);
}

TEST_CASE("AppPath::shared", "[AppPath]") {
  const auto appPath = AppPath::shared();
  CHECK(appPath);
}

TEST_CASE("AppPath::get", "[AppPath]") {
  const AppPath appPath;
  CHECK(appPath.get());
}

TEST_CASE("PrefPath(string&, string&)", "[PrefPath]") {
  CHECK_NOTHROW(PrefPath{"centurion", "tests"});
}

TEST_CASE("PrefPath::unique", "[PrefPath]") {
  CHECK(PrefPath::unique("centurion", "tests"));
}

TEST_CASE("PrefPath::shared", "[PrefPath]") {
  CHECK(PrefPath::shared("centurion", "tests"));
}

TEST_CASE("PrefPath::operator bool", "[PrefPath]") {
  const PrefPath prefPath{"centurion", "tests"};
  CHECK(prefPath);
}

TEST_CASE("PrefPath::get", "[PrefPath]") {
  const PrefPath prefPath{"centurion", "tests"};
  CHECK(prefPath.get());
}