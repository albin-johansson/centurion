#include "mouse_button.hpp"

#include <catch.hpp>

#include "centurion_as_ctn.hpp"
#include "centurion_types.hpp"

TEST_CASE("mouse_button enum values", "[mouse_button]")
{
  CHECK(static_cast<ctn::u32>(ctn::mouse_button::left) == SDL_BUTTON_LEFT);
  CHECK(static_cast<ctn::u32>(ctn::mouse_button::middle) == SDL_BUTTON_MIDDLE);
  CHECK(static_cast<ctn::u32>(ctn::mouse_button::right) == SDL_BUTTON_RIGHT);
  CHECK(static_cast<ctn::u32>(ctn::mouse_button::x1) == SDL_BUTTON_X1);
  CHECK(static_cast<ctn::u32>(ctn::mouse_button::x2) == SDL_BUTTON_X2);
}
