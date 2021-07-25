#include "video/scale_mode.hpp"

#include <gtest/gtest.h>

#include <iostream>  // cout

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

TEST(ScaleMode, ToString)
{
  ASSERT_THROW(cen::to_string(static_cast<cen::scale_mode>(4)), cen::cen_error);

  ASSERT_EQ("nearest", cen::to_string(cen::scale_mode::nearest));
  ASSERT_EQ("linear", cen::to_string(cen::scale_mode::linear));
  ASSERT_EQ("best", cen::to_string(cen::scale_mode::best));

  std::cout << "Scale mode example: " << cen::scale_mode::linear << '\n';
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)