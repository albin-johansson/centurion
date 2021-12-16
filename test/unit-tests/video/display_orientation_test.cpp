#include <gtest/gtest.h>

#include <iostream>  // clog

#include "video.hpp"

TEST(DisplayOrientation, Values)
{
  ASSERT_EQ(SDL_ORIENTATION_UNKNOWN, cen::ToUnderlying(cen::DisplayOrientation::Unknown));

  ASSERT_EQ(SDL_ORIENTATION_LANDSCAPE, cen::ToUnderlying(cen::DisplayOrientation::Landscape));

  ASSERT_EQ(SDL_ORIENTATION_LANDSCAPE_FLIPPED,
            cen::ToUnderlying(cen::DisplayOrientation::LandscapeFlipped));

  ASSERT_EQ(SDL_ORIENTATION_PORTRAIT, cen::ToUnderlying(cen::DisplayOrientation::Portrait));

  ASSERT_EQ(SDL_ORIENTATION_PORTRAIT_FLIPPED,
            cen::ToUnderlying(cen::DisplayOrientation::PortraitFlipped));
}

TEST(DisplayOrientation, ToString)
{
  ASSERT_THROW(cen::to_string(static_cast<cen::DisplayOrientation>(6)), cen::Error);

  ASSERT_EQ("Unknown", cen::to_string(cen::DisplayOrientation::Unknown));
  ASSERT_EQ("Landscape", cen::to_string(cen::DisplayOrientation::Landscape));
  ASSERT_EQ("LandscapeFlipped", cen::to_string(cen::DisplayOrientation::LandscapeFlipped));
  ASSERT_EQ("Portrait", cen::to_string(cen::DisplayOrientation::Portrait));
  ASSERT_EQ("PortraitFlipped", cen::to_string(cen::DisplayOrientation::PortraitFlipped));

  std::clog << "Display orientation example: " << cen::DisplayOrientation::Portrait << '\n';
}
