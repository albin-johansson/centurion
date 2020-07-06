#include "mouse_button.hpp"

#include <catch.hpp>

using namespace centurion;

TEST_CASE("MouseButton enum values", "[MouseButton]")
{
  CHECK(static_cast<Uint32>(MouseButton::Left) == SDL_BUTTON_LEFT);
  CHECK(static_cast<Uint32>(MouseButton::Middle) == SDL_BUTTON_MIDDLE);
  CHECK(static_cast<Uint32>(MouseButton::Right) == SDL_BUTTON_RIGHT);
  CHECK(static_cast<Uint32>(MouseButton::X1) == SDL_BUTTON_X1);
  CHECK(static_cast<Uint32>(MouseButton::X2) == SDL_BUTTON_X2);
}
