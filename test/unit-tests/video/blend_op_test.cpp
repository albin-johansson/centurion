#include <gtest/gtest.h>

#include <iostream>  // clog

#include "common.hpp"
#include "video.hpp"

TEST(BlendOp, Values)
{
  ASSERT_EQ(SDL_BLENDOPERATION_ADD, cen::ToUnderlying(cen::BlendOp::Add));
  ASSERT_EQ(SDL_BLENDOPERATION_SUBTRACT, cen::ToUnderlying(cen::BlendOp::Sub));
  ASSERT_EQ(SDL_BLENDOPERATION_REV_SUBTRACT, cen::ToUnderlying(cen::BlendOp::ReverseSub));
  ASSERT_EQ(SDL_BLENDOPERATION_MINIMUM, cen::ToUnderlying(cen::BlendOp::Min));
  ASSERT_EQ(SDL_BLENDOPERATION_MAXIMUM, cen::ToUnderlying(cen::BlendOp::Max));
}

TEST(BlendOp, ToString)
{
  ASSERT_THROW(cen::to_string(static_cast<cen::BlendOp>(42)), cen::Error);

  ASSERT_EQ("Add", cen::to_string(cen::BlendOp::Add));
  ASSERT_EQ("Sub", cen::to_string(cen::BlendOp::Sub));
  ASSERT_EQ("ReverseSub", cen::to_string(cen::BlendOp::ReverseSub));
  ASSERT_EQ("Min", cen::to_string(cen::BlendOp::Min));
  ASSERT_EQ("Max", cen::to_string(cen::BlendOp::Max));

  std::clog << "Blend operation example: " << cen::BlendOp::Add << '\n';
}
