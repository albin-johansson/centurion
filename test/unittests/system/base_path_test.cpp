#include "base_path.hpp"

#include <gtest/gtest.h>

#include <iostream>  // cout

#include "log.hpp"

TEST(BasePath, Constructor)
{
  EXPECT_NO_THROW(cen::base_path{});
}

TEST(BasePath, BoolConversion)
{
  const cen::base_path path;
  EXPECT_TRUE(path);
}

TEST(BasePath, Get)
{
  const cen::base_path path;
  EXPECT_TRUE(path.get());
}

TEST(BasePath, ToString)
{
  const cen::base_path path;
  cen::log::put(cen::to_string(path));
}

TEST(BasePath, StreamOperator)
{
  const cen::base_path path;
  std::cout << "COUT: " << path << '\n';
}
