#include "experimental/unicode_string.hpp"

#include <catch.hpp>

#include "centurion_as_ctn.hpp"

namespace centurion {

using namespace centurion::experimental;

}

TEST_CASE("unicode_string default constructor", "[unicode_string]")
{
  const ctn::unicode_string str;
  CHECK(str.size() == 0);  // NOLINT
  CHECK(str.empty());

  CHECK(str.at(0) == 0);  // null-terminator
}

TEST_CASE("unicode_string from std::initializer_list", "[unicode_string]")
{
  const ctn::unicode_string str = {'a', 'b', 'c'};
  CHECK(str.size() == 3);
  CHECK_FALSE(str.empty());

  CHECK(str.at(0) == 'a');
  CHECK(str.at(1) == 'b');
  CHECK(str.at(2) == 'c');
  CHECK(str.at(3) == 0);  // null-terminator

  CHECK(str[0] == 'a');
  CHECK(str[1] == 'b');
  CHECK(str[2] == 'c');
}

TEST_CASE("unicode_string iteration", "[unicode_string]")
{
  const ctn::unicode_string str = {'a', 'b', 'c'};

  REQUIRE(str.end() - str.begin() == 3);

  int count = 0;
  for (const auto ch : str) {
    CHECK(ch != 0);
    ++count;
  }

  CHECK(count == 3);
  CHECK(str.at(3) == 0);  // null-terminator
}