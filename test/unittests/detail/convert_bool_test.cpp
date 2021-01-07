#include "detail/convert_bool.hpp"

#include <gtest/gtest.h>

TEST(ConvertBool, Conversion)
{
  EXPECT_EQ(cen::detail::convert_bool(true), SDL_TRUE);
  EXPECT_EQ(cen::detail::convert_bool(false), SDL_FALSE);
}
