#include "mouse_button.hpp"

#include <catch.hpp>

#include "cen.hpp"
#include "types.hpp"

TEST_CASE("mouse_button enum values", "[mouse_button]")
{
  CHECK(static_cast<cen::u32>(cen::mouse_button::left) == SDL_BUTTON_LEFT);
  CHECK(static_cast<cen::u32>(cen::mouse_button::middle) == SDL_BUTTON_MIDDLE);
  CHECK(static_cast<cen::u32>(cen::mouse_button::right) == SDL_BUTTON_RIGHT);
  CHECK(static_cast<cen::u32>(cen::mouse_button::x1) == SDL_BUTTON_X1);
  CHECK(static_cast<cen::u32>(cen::mouse_button::x2) == SDL_BUTTON_X2);
}
