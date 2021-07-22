#include <gtest/gtest.h>

#include <iostream>  // cout

#include "core/to_underlying.hpp"
#include "video/screen.hpp"

TEST(ScreenOrientation, Values)
{
  ASSERT_EQ(SDL_ORIENTATION_UNKNOWN,
            cen::to_underlying(cen::screen_orientation::unknown));

  ASSERT_EQ(SDL_ORIENTATION_LANDSCAPE,
            cen::to_underlying(cen::screen_orientation::landscape));

  ASSERT_EQ(SDL_ORIENTATION_LANDSCAPE_FLIPPED,
            cen::to_underlying(cen::screen_orientation::landscape_flipped));

  ASSERT_EQ(SDL_ORIENTATION_PORTRAIT,
            cen::to_underlying(cen::screen_orientation::portrait));

  ASSERT_EQ(SDL_ORIENTATION_PORTRAIT_FLIPPED,
            cen::to_underlying(cen::screen_orientation::portrait_flipped));
}

TEST(ScreenOrientation, ToString)
{
  ASSERT_EQ("unknown", cen::to_string(cen::screen_orientation::unknown));
  ASSERT_EQ("landscape", cen::to_string(cen::screen_orientation::landscape));
  ASSERT_EQ("landscape_flipped",
            cen::to_string(cen::screen_orientation::landscape_flipped));
  ASSERT_EQ("portrait", cen::to_string(cen::screen_orientation::portrait));
  ASSERT_EQ("portrait_flipped",
            cen::to_string(cen::screen_orientation::portrait_flipped));

  std::cout << "Screen orientation example: " << cen::screen_orientation::portrait
            << '\n';
}
