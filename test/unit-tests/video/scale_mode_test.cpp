#include "video/scale_mode.hpp"

#include <gtest/gtest.h>

#if SDL_VERSION_ATLEAST(2, 0, 12)

TEST(ScaleMode, EnumValues)
{
  ASSERT_EQ(cen::scale_mode::linear, SDL_ScaleModeLinear);
  ASSERT_EQ(cen::scale_mode::nearest, SDL_ScaleModeNearest);
  ASSERT_EQ(cen::scale_mode::best, SDL_ScaleModeBest);

  ASSERT_EQ(SDL_ScaleModeLinear, cen::scale_mode::linear);
  ASSERT_EQ(SDL_ScaleModeNearest, cen::scale_mode::nearest);
  ASSERT_EQ(SDL_ScaleModeBest, cen::scale_mode::best);

  ASSERT_NE(cen::scale_mode::linear, SDL_ScaleModeNearest);
  ASSERT_NE(SDL_ScaleModeBest, cen::scale_mode::nearest);
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)