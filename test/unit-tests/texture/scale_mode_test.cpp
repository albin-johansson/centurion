#include <gtest/gtest.h>

#include <iostream>  // clog

#include "common.hpp"
#include "texture.hpp"

#if SDL_VERSION_ATLEAST(2, 0, 12)

TEST(ScaleMode, EnumValues)
{
  ASSERT_EQ(cen::to_underlying(cen::ScaleMode::Linear), SDL_ScaleModeLinear);
  ASSERT_EQ(cen::to_underlying(cen::ScaleMode::Nearest), SDL_ScaleModeNearest);
  ASSERT_EQ(cen::to_underlying(cen::ScaleMode::Best), SDL_ScaleModeBest);
}

TEST(ScaleMode, ToString)
{
  ASSERT_THROW(cen::ToString(static_cast<cen::ScaleMode>(4)), cen::exception);

  ASSERT_EQ("Nearest", cen::ToString(cen::ScaleMode::Nearest));
  ASSERT_EQ("Linear", cen::ToString(cen::ScaleMode::Linear));
  ASSERT_EQ("Best", cen::ToString(cen::ScaleMode::Best));

  std::clog << "Scale mode example: " << cen::ScaleMode::Linear << '\n';
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)