#include <gtest/gtest.h>

#include <iostream>  // cout

#include "video.hpp"

TEST(Orientation, Values)
{
  ASSERT_EQ(SDL_ORIENTATION_UNKNOWN, to_underlying(cen::orientation::unknown));

  ASSERT_EQ(SDL_ORIENTATION_LANDSCAPE, to_underlying(cen::orientation::landscape));

  ASSERT_EQ(SDL_ORIENTATION_LANDSCAPE_FLIPPED,
            to_underlying(cen::orientation::landscape_flipped));

  ASSERT_EQ(SDL_ORIENTATION_PORTRAIT, to_underlying(cen::orientation::portrait));

  ASSERT_EQ(SDL_ORIENTATION_PORTRAIT_FLIPPED,
            to_underlying(cen::orientation::portrait_flipped));
}

TEST(Orientation, ToString)
{
  ASSERT_THROW(to_string(static_cast<cen::orientation>(6)), cen::exception);

  ASSERT_EQ("unknown", to_string(cen::orientation::unknown));
  ASSERT_EQ("landscape", to_string(cen::orientation::landscape));
  ASSERT_EQ("landscape_flipped", to_string(cen::orientation::landscape_flipped));
  ASSERT_EQ("portrait", to_string(cen::orientation::portrait));
  ASSERT_EQ("portrait_flipped", to_string(cen::orientation::portrait_flipped));

  std::cout << "orientation::portrait == " << cen::orientation::portrait << '\n';
}
