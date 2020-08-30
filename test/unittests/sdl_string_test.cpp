#include "sdl_string.hpp"

#include <catch.hpp>

#include "centurion_as_ctn.hpp"
#include "centurion_types.hpp"

TEST_CASE("sdl_string ctor", "[sdl_string]")
{
  CHECK_NOTHROW(ctn::sdl_string{nullptr});

  const ctn::sdl_string str{nullptr};
  CHECK(!str);
}

TEST_CASE("sdl_string::get", "[sdl_string]")
{
  SDL_SetClipboardText("foo");
  const ctn::sdl_string str{SDL_GetClipboardText()};
  CHECK_THAT(str.get(), Catch::Equals("foo"));
}

TEST_CASE("sdl_string::copy", "[sdl_string]")
{
  SECTION("Valid string")
  {
    SDL_SetClipboardText("bar");
    const ctn::sdl_string str{SDL_GetClipboardText()};
    const auto copy = str.copy();
    CHECK(copy == "bar");
  }

  SECTION("Empty string")
  {
    SDL_SetClipboardText(nullptr);
    const ctn::sdl_string empty{SDL_GetClipboardText()};
    CHECK(empty.copy().empty());
  }
}