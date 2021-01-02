#include <gtest/gtest.h>

#include "detail/convert_bool.hpp"

TEST(ConvertBool, Conversion)
{
  EXPECT_EQ(cen::detail::convert_bool(true), SDL_TRUE);
  EXPECT_EQ(cen::detail::convert_bool(false), SDL_FALSE);
}
