#include "error.hpp"

#include <catch.hpp>

using namespace centurion::detail;

TEST_CASE("core_error", "[error]")
{
  const std::string expected = "Core message! Error: SDL error";

  SDL_SetError("SDL error");
  auto err = core_error("Core message!");
  SDL_ClearError();

  CHECK_THAT(expected, Catch::Equals(err.what()));
}

TEST_CASE("img_error", "[error]")
{
  const std::string expected = "IMG message! Error: SDL_image error";

  SDL_SetError("SDL_image error");
  auto err = img_error("IMG message!");
  SDL_ClearError();

  CHECK_THAT(expected, Catch::Equals(err.what()));
}

TEST_CASE("ttf_error", "[error]")
{
  const std::string expected = "TTF message! Error: SDL_ttf error";

  SDL_SetError("SDL_ttf error");
  auto err = ttf_error("TTF message!");
  SDL_ClearError();

  CHECK_THAT(expected, Catch::Equals(err.what()));
}

TEST_CASE("mix_error", "[error]")
{
  const std::string expected = "MIX message! Error: SDL_mixer error";

  SDL_SetError("SDL_mixer error");
  auto err = mix_error("MIX message!");
  SDL_ClearError();

  CHECK_THAT(expected, Catch::Equals(err.what()));
}