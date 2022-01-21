#include <gtest/gtest.h>

#include <iostream>  // cout

#include "centurion/texture.hpp"

#if SDL_VERSION_ATLEAST(2, 0, 12)

TEST(ScaleMode, Values)
{
  ASSERT_EQ(SDL_ScaleModeLinear, to_underlying(cen::scale_mode::linear));
  ASSERT_EQ(SDL_ScaleModeNearest, to_underlying(cen::scale_mode::nearest));
  ASSERT_EQ(SDL_ScaleModeBest, to_underlying(cen::scale_mode::best));
}

TEST(ScaleMode, ToString)
{
  ASSERT_THROW(to_string(static_cast<cen::scale_mode>(4)), cen::exception);

  ASSERT_EQ("nearest", to_string(cen::scale_mode::nearest));
  ASSERT_EQ("linear", to_string(cen::scale_mode::linear));
  ASSERT_EQ("best", to_string(cen::scale_mode::best));

  std::cout << "scale_mode::linear == " << cen::scale_mode::linear << '\n';
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)