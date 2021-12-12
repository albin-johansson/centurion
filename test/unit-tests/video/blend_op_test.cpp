#include <gtest/gtest.h>

#include <iostream>  // clog

#include "video/blend_mode.hpp"

TEST(BlendOp, Values)
{
  ASSERT_EQ(SDL_BLENDOPERATION_ADD, cen::blend_op::add);
  ASSERT_EQ(SDL_BLENDOPERATION_SUBTRACT, cen::blend_op::sub);
  ASSERT_EQ(SDL_BLENDOPERATION_REV_SUBTRACT, cen::blend_op::reverse_sub);
  ASSERT_EQ(SDL_BLENDOPERATION_MINIMUM, cen::blend_op::min);
  ASSERT_EQ(SDL_BLENDOPERATION_MAXIMUM, cen::blend_op::max);

  ASSERT_NE(cen::blend_op::sub, SDL_BLENDOPERATION_MINIMUM);
}

TEST(BlendOp, ToString)
{
  ASSERT_THROW(cen::to_string(static_cast<cen::blend_op>(42)), cen::Error);

  ASSERT_EQ("add", cen::to_string(cen::blend_op::add));
  ASSERT_EQ("sub", cen::to_string(cen::blend_op::sub));
  ASSERT_EQ("reverse_sub", cen::to_string(cen::blend_op::reverse_sub));
  ASSERT_EQ("min", cen::to_string(cen::blend_op::min));
  ASSERT_EQ("max", cen::to_string(cen::blend_op::max));

  std::clog << "Blend operation example: " << cen::blend_op::add << '\n';
}
