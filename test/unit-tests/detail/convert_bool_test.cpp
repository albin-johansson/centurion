#include "detail/convert_bool.hpp"

#include <gtest/gtest.h>

TEST(ConvertBool, Conversion)
{
  ASSERT_EQ(cen::detail::convert_bool(true), SDL_TRUE);
  ASSERT_EQ(cen::detail::convert_bool(false), SDL_FALSE);
}
