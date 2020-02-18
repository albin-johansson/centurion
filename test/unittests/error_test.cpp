#include "error.h"

#include <SDL.h>

#include <string>

#include "catch.hpp"
#include "log.h"

using namespace centurion;
using namespace Catch;

TEST_CASE("Error::descriptionf", "[Error]")
{
  CHECK(Error::descriptionf());

  const auto* msg = "Test of Error::descriptionf";
  SDL_SetError("%s", msg);
  CHECK_THAT(Error::descriptionf(), Equals(msg));
}

TEST_CASE("Error::description", "[Error]")
{
  CHECK_NOTHROW(Error::description());

  const std::string msg{"Test of Error::description"};
  SDL_SetError("%s", msg.c_str());

  CHECK_THAT(Error::description(), Equals(msg));
}

TEST_CASE("Error::msg", "[Error]")
{
  CHECK_NOTHROW(Error::msg());

  const std::string msg{"Test of Error::msg"};
  SDL_SetError("%s", msg.c_str());

  CHECK_THAT(Error::msg(), Equals("Error: " + msg));
}