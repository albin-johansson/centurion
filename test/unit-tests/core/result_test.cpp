#include <gtest/gtest.h>

#include <iostream>  // clog

#include "core/common.hpp"

TEST(Result, Values)
{
  ASSERT_EQ(cen::Result{true}, cen::success);
  ASSERT_EQ(cen::Result{false}, cen::failure);

  ASSERT_NE(cen::Result{false}, cen::success);
  ASSERT_NE(cen::Result{true}, cen::failure);

  ASSERT_NE(cen::success, cen::failure);

  ASSERT_TRUE(cen::success);
  ASSERT_FALSE(cen::failure);
}

TEST(Result, ToString)
{
  std::clog << "result (success): \"" << cen::success << "\"\n";
  std::clog << "result (failure): \"" << cen::failure << "\"\n";
}
