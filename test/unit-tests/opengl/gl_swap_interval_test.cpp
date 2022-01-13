#include <gtest/gtest.h>

#include <iostream>  // clog

#include "common.hpp"
#include "opengl.hpp"

TEST(GLSwapInterval, Values)
{
  ASSERT_EQ(0, ToUnderlying(cen::GLSwapInterval::Immediate));
  ASSERT_EQ(1, ToUnderlying(cen::GLSwapInterval::Synchronized));
  ASSERT_EQ(-1, ToUnderlying(cen::GLSwapInterval::LateImmediate));
}

TEST(GLSwapInterval, ToString)
{
  ASSERT_THROW(ToString(cen::GLSwapInterval{2}), cen::Error);

  ASSERT_EQ("Immediate", ToString(cen::GLSwapInterval::Immediate));
  ASSERT_EQ("Synchronized", ToString(cen::GLSwapInterval::Synchronized));
  ASSERT_EQ("LateImmediate", ToString(cen::GLSwapInterval::LateImmediate));

  std::clog << "OpenGL swap interval example: " << cen::GLSwapInterval::Synchronized << '\n';
}
