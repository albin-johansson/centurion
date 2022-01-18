#include <gtest/gtest.h>

#include <iostream>  // cout

#include "common.hpp"
#include "video.hpp"

TEST(BlendOp, Values)
{
  ASSERT_EQ(SDL_BLENDOPERATION_ADD, to_underlying(cen::blend_op::add));
  ASSERT_EQ(SDL_BLENDOPERATION_SUBTRACT, to_underlying(cen::blend_op::sub));
  ASSERT_EQ(SDL_BLENDOPERATION_REV_SUBTRACT, to_underlying(cen::blend_op::reverse_sub));
  ASSERT_EQ(SDL_BLENDOPERATION_MINIMUM, to_underlying(cen::blend_op::min));
  ASSERT_EQ(SDL_BLENDOPERATION_MAXIMUM, to_underlying(cen::blend_op::max));
}

TEST(BlendOp, ToString)
{
  ASSERT_THROW(to_string(static_cast<cen::blend_op>(42)), cen::exception);

  ASSERT_EQ("add", to_string(cen::blend_op::add));
  ASSERT_EQ("sub", to_string(cen::blend_op::sub));
  ASSERT_EQ("reverse_sub", to_string(cen::blend_op::reverse_sub));
  ASSERT_EQ("min", to_string(cen::blend_op::min));
  ASSERT_EQ("max", to_string(cen::blend_op::max));

  std::cout << "blend_op::add == " << cen::blend_op::add << '\n';
}
