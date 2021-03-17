#include "video/scale_mode.hpp"

#include <gtest/gtest.h>

TEST(ScaleMode, EnumValues)
{
  EXPECT_EQ(cen::scale_mode::linear, SDL_ScaleModeLinear);
  EXPECT_EQ(cen::scale_mode::nearest, SDL_ScaleModeNearest);
  EXPECT_EQ(cen::scale_mode::best, SDL_ScaleModeBest);

  EXPECT_EQ(SDL_ScaleModeLinear, cen::scale_mode::linear);
  EXPECT_EQ(SDL_ScaleModeNearest, cen::scale_mode::nearest);
  EXPECT_EQ(SDL_ScaleModeBest, cen::scale_mode::best);

  EXPECT_NE(cen::scale_mode::linear, SDL_ScaleModeNearest);
  EXPECT_NE(SDL_ScaleModeBest, cen::scale_mode::nearest);
}
