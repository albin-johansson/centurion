#include <gtest/gtest.h>

#include <iostream>  // clog

#include "common.hpp"
#include "video.hpp"

TEST(BlendOp, Values)
{
  ASSERT_EQ(SDL_BLENDOPERATION_ADD, cen::to_underlying(cen::BlendOp::Add));
  ASSERT_EQ(SDL_BLENDOPERATION_SUBTRACT, cen::to_underlying(cen::BlendOp::Sub));
  ASSERT_EQ(SDL_BLENDOPERATION_REV_SUBTRACT, cen::to_underlying(cen::BlendOp::ReverseSub));
  ASSERT_EQ(SDL_BLENDOPERATION_MINIMUM, cen::to_underlying(cen::BlendOp::Min));
  ASSERT_EQ(SDL_BLENDOPERATION_MAXIMUM, cen::to_underlying(cen::BlendOp::Max));
}

TEST(BlendOp, ToString)
{
  ASSERT_THROW(cen::ToString(static_cast<cen::BlendOp>(42)), cen::exception);

  ASSERT_EQ("Add", cen::ToString(cen::BlendOp::Add));
  ASSERT_EQ("Sub", cen::ToString(cen::BlendOp::Sub));
  ASSERT_EQ("ReverseSub", cen::ToString(cen::BlendOp::ReverseSub));
  ASSERT_EQ("Min", cen::ToString(cen::BlendOp::Min));
  ASSERT_EQ("Max", cen::ToString(cen::BlendOp::Max));

  std::clog << "Blend operation example: " << cen::BlendOp::Add << '\n';
}
