#include "clipboard.hpp"

#include <catch.hpp>

#include "cen.hpp"

TEST_CASE("clipboard::has_text", "[clipboard]")
{
  cen::clipboard::set_text("");
  CHECK(!cen::clipboard::has_text());

  cen::clipboard::set_text("foobar");
  CHECK(cen::clipboard::has_text());
}

TEST_CASE("clipboard::set_text", "[clipboard]")
{
  cen::clipboard::set_text("foo");
  CHECK(cen::clipboard::get_text() == "foo");
}