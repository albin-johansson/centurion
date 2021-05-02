#include "core/result.hpp"

#include <gtest/gtest.h>

#include <iostream>  // cout

TEST(Result, Values)
{
  EXPECT_EQ(cen::result{true}, cen::success);
  EXPECT_EQ(cen::result{false}, cen::failure);

  EXPECT_NE(cen::result{false}, cen::success);
  EXPECT_NE(cen::result{true}, cen::failure);

  EXPECT_NE(cen::success, cen::failure);

  EXPECT_TRUE(cen::success);
  EXPECT_FALSE(cen::failure);
}

TEST(Result, ToString)
{
  std::cout << "result (success): \"" << cen::success << "\"\n";
  std::cout << "result (failure): \"" << cen::failure << "\"\n";
}
