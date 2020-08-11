#include "clipboard.hpp"

#include <catch.hpp>

#include "centurion_as_ctn.hpp"

TEST_CASE("clipboard::has_text", "[clipboard]")
{
  ctn::clipboard::set_text("");
  CHECK(!ctn::clipboard::has_text());

  ctn::clipboard::set_text("foobar");
  CHECK(ctn::clipboard::has_text());
}

TEST_CASE("clipboard::set_text", "[clipboard]")
{
  ctn::clipboard::set_text("foo");
  CHECK(ctn::clipboard::get_text() == "foo");
}