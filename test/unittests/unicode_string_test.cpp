#include "unicode_string.hpp"

#include <catch.hpp>

TEST_CASE("unicode_string default constructor", "[unicode_string]")
{
  const cen::unicode_string str;
  CHECK(str.size() == 0);  // NOLINT
  CHECK(str.empty());

  CHECK(str.at(0) == 0);  // null-terminator
}

TEST_CASE("unicode_string from std::initializer_list", "[unicode_string]")
{
  const cen::unicode_string str = {'a', 'b', 'c'};
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
  const cen::unicode_string str = {'a', 'b', 'c'};

  REQUIRE(str.end() - str.begin() == 3);

  int count = 0;
  for (const auto ch : str) {
    CHECK(ch != 0);
    ++count;
  }

  CHECK(count == 3);
  CHECK(str.at(3) == 0);  // null-terminator
}

TEST_CASE("unicode_string::append", "[unicode_string]")
{
  using namespace cen::literals;

  cen::unicode_string str;

  str.append('A'_uni);

  CHECK(str.size() == 1);
  CHECK(str.at(0) == 'A'_uni);

  str.append(0x1F308_uni);
  CHECK(str.size() == 2);
  CHECK(str.at(1) == 0x1F308_uni);
}

TEST_CASE("unicode_string::variadic append", "[unicode_string]")
{
  using namespace cen::literals;

  cen::unicode_string str;

  str.append('B'_uni, 'A'_uni, 'R'_uni);

  CHECK(str.size() == 3);
  CHECK(str.at(0) == 'B'_uni);
  CHECK(str.at(1) == 'A'_uni);
  CHECK(str.at(2) == 'R'_uni);
}

TEST_CASE("unicode_string::operator +=", "[unicode_string]")
{
  using namespace cen::literals;

  cen::unicode_string str;

  str += 'Z'_uni;

  CHECK(str.size() == 1);
  CHECK(str.at(0) == 'Z'_uni);

  str += 'Q'_uni;

  CHECK(str.size() == 2);
  CHECK(str.at(1) == 'Q'_uni);
}

TEST_CASE("unicode_string::pop_back", "[unicode_string]")
{
  using namespace cen::literals;

  cen::unicode_string str;

  str += 'A'_uni;

  CHECK(!str.empty());
  CHECK(str.size() == 1);

  str.pop_back();

  CHECK(str.empty());
  CHECK(str.size() == 0);  // NOLINT
  CHECK(str.at(0) == 0);   // null-terminator

  CHECK_NOTHROW(str.pop_back());
  CHECK_NOTHROW(str.pop_back());
  CHECK_NOTHROW(str.pop_back());

  CHECK(str.empty());
  CHECK(str.size() == 0);  // NOLINT
  CHECK(str.at(0) == 0);   // null-terminator
}

TEST_CASE("unicode_string::at", "[unicode_string]")
{
  using namespace cen::literals;

  cen::unicode_string str;

  CHECK_NOTHROW(str.at(0));  // null-terminator
  CHECK_THROWS(str.at(-1));
  CHECK_THROWS(str.at(1));

  str += 'T'_uni;
  CHECK(str.at(0) == 'T'_uni);
}

TEST_CASE("unicode_string::data", "[unicode_string]")
{
  using namespace cen::literals;

  cen::unicode_string str;
  const auto& cstr = str;

  REQUIRE(str.data());
  REQUIRE(cstr.data());

  CHECK(*str.data() == 0);

  str += 'b'_uni;

  REQUIRE(str.data());
  CHECK(*str.data() == 'b'_uni);
  CHECK(str.data()[1] == 0);
}

TEST_CASE("unicode_string::empty", "[unicode_string]")
{
  using namespace cen::literals;

  cen::unicode_string str;

  CHECK(str.empty());

  str += 'A'_uni;

  CHECK(!str.empty());
}

TEST_CASE("unicode_string::reserve", "[unicode_string]")
{
  cen::unicode_string str;

  str.reserve(10);
  CHECK(str.capacity() == 10);
}

TEST_CASE("unicode_string::operator==", "[unicode_string]")
{
  SECTION("Self")
  {
    const cen::unicode_string str;
    CHECK(str == str);
  }

  SECTION("Two default constructed strings")
  {
    const cen::unicode_string fst;
    const cen::unicode_string snd;
    CHECK(fst == snd);
    CHECK(snd == fst);
  }

  SECTION("Two equal strings")
  {
    using namespace cen::literals;
    const cen::unicode_string fst{'A'_uni, 'B'_uni, 'C'_uni};
    const cen::unicode_string snd{fst};  // NOLINT

    CHECK(fst == snd);
    CHECK(snd == fst);
  }

  SECTION("Two different strings")
  {
    using namespace cen::literals;
    const cen::unicode_string fst{'F'_uni, 'O'_uni, 'O'_uni};
    const cen::unicode_string snd{'B'_uni, 'A'_uni, 'R'_uni};

    CHECK_FALSE(fst == snd);
    CHECK_FALSE(snd == fst);
  }

  SECTION("Different size strings")
  {
    using namespace cen::literals;
    const cen::unicode_string fst{'A'_uni, 'B'_uni};
    const cen::unicode_string snd{'C'_uni, 'D'_uni, 'E'_uni};

    CHECK_FALSE(fst == snd);
    CHECK_FALSE(snd == fst);
  }
}

TEST_CASE("unicode_string::operator!=", "[unicode_string]")
{
  SECTION("Self")
  {
    const cen::unicode_string str;
    CHECK_FALSE(str != str);
  }

  SECTION("Two default constructed strings")
  {
    const cen::unicode_string fst;
    const cen::unicode_string snd;
    CHECK_FALSE(fst != snd);
    CHECK_FALSE(snd != fst);
  }

  SECTION("Two equal strings")
  {
    using namespace cen::literals;
    const cen::unicode_string fst{'S'_uni, 'A'_uni, 'M'_uni};
    const cen::unicode_string snd{fst};  // NOLINT

    CHECK_FALSE(fst != snd);
    CHECK_FALSE(snd != fst);
  }

  SECTION("Two different strings")
  {
    using namespace cen::literals;
    const cen::unicode_string fst{'F'_uni, 'O'_uni, 'O'_uni};
    const cen::unicode_string snd{'B'_uni, 'A'_uni, 'R'_uni};

    CHECK(fst != snd);
    CHECK(snd != fst);
  }

  SECTION("Different size strings")
  {
    using namespace cen::literals;
    const cen::unicode_string fst{'B'_uni, 'B'_uni};
    const cen::unicode_string snd{'B'_uni, 'B'_uni, 'B'_uni};

    CHECK(fst != snd);
    CHECK(snd != fst);
  }
}