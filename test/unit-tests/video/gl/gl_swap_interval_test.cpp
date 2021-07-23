#include <gtest/gtest.h>

#include <iostream>  // cout

#include "core/to_underlying.hpp"
#include "video/opengl/gl_core.hpp"

TEST(GLSwapInterval, Values)
{
  ASSERT_EQ(0, cen::to_underlying(cen::gl_swap_interval::immediate));
  ASSERT_EQ(1, cen::to_underlying(cen::gl_swap_interval::synchronized));
  ASSERT_EQ(-1, cen::to_underlying(cen::gl_swap_interval::late_immediate));
}

TEST(GLSwapInterval, ToString)
{
  ASSERT_EQ("immediate", cen::to_string(cen::gl_swap_interval::immediate));
  ASSERT_EQ("synchronized", cen::to_string(cen::gl_swap_interval::synchronized));
  ASSERT_EQ("late_immediate", cen::to_string(cen::gl_swap_interval::late_immediate));

  std::cout << "OpenGL swap interval example: " << cen::gl_swap_interval::synchronized
            << '\n';
}