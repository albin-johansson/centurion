#include "video/button_order.hpp"

#include <gtest/gtest.h>

#include "core/to_underlying.hpp"

#if SDL_VERSION_ATLEAST(2, 0, 12)

TEST(ButtonOrder, Values)
{
  ASSERT_EQ(SDL_MESSAGEBOX_BUTTONS_LEFT_TO_RIGHT,
            cen::to_underlying(cen::button_order::left_to_right));
  ASSERT_EQ(SDL_MESSAGEBOX_BUTTONS_RIGHT_TO_LEFT,
            cen::to_underlying(cen::button_order::right_to_left));
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)
