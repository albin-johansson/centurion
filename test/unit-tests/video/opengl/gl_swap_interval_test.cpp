#include <gtest/gtest.h>

#include <iostream>  // cout

#include "opengl.hpp"

TEST(GLSwapInterval, Values)
{
  ASSERT_EQ(-1, to_underlying(cen::gl_swap_interval::late_immediate));
  ASSERT_EQ(0, to_underlying(cen::gl_swap_interval::immediate));
  ASSERT_EQ(1, to_underlying(cen::gl_swap_interval::synchronized));
}

TEST(GLSwapInterval, ToString)
{
  ASSERT_THROW(to_string(cen::gl_swap_interval{1'000}), cen::exception);

  ASSERT_EQ("immediate", to_string(cen::gl_swap_interval::immediate));
  ASSERT_EQ("synchronized", to_string(cen::gl_swap_interval::synchronized));
  ASSERT_EQ("late_immediate", to_string(cen::gl_swap_interval::late_immediate));

  std::cout << "gl_swap_interval::synchronized == " << cen::gl_swap_interval::synchronized
            << '\n';
}
