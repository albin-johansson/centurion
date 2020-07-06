#include "error.hpp"

#include <catch.hpp>

using namespace centurion::detail;

TEST_CASE("Error::from_core", "[Error]")
{
  const std::string expected = "Core message! Error: SDL error";

  SDL_SetError("SDL error");
  auto err = Error::from_core("Core message!");
  SDL_ClearError();

  CHECK_THAT(expected, Catch::Equals(err.what()));
}

TEST_CASE("Error::from_image", "[Error]")
{
  const std::string expected = "IMG message! Error: SDL_image error";

  SDL_SetError("SDL_image error");
  auto err = Error::from_image("IMG message!");
  SDL_ClearError();

  CHECK_THAT(expected, Catch::Equals(err.what()));
}

TEST_CASE("Error::from_ttf", "[Error]")
{
  const std::string expected = "TTF message! Error: SDL_ttf error";

  SDL_SetError("SDL_ttf error");
  auto err = Error::from_ttf("TTF message!");
  SDL_ClearError();

  CHECK_THAT(expected, Catch::Equals(err.what()));
}

TEST_CASE("Error::from_mixer", "[Error]")
{
  const std::string expected = "MIX message! Error: SDL_mixer error";

  SDL_SetError("SDL_mixer error");
  auto err = Error::from_mixer("MIX message!");
  SDL_ClearError();

  CHECK_THAT(expected, Catch::Equals(err.what()));
}