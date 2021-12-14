#include <gtest/gtest.h>

#include <iostream>  // clog

#include "core/common.hpp"
#include "video.hpp"

TEST(BlendFactor, Values)
{
  ASSERT_EQ(SDL_BLENDFACTOR_ZERO, cen::ToUnderlying(cen::blend_factor::zero));
  ASSERT_EQ(SDL_BLENDFACTOR_ONE, cen::ToUnderlying(cen::blend_factor::one));

  ASSERT_EQ(SDL_BLENDFACTOR_SRC_COLOR, cen::ToUnderlying(cen::blend_factor::src_color));
  ASSERT_EQ(SDL_BLENDFACTOR_ONE_MINUS_SRC_COLOR,
            cen::ToUnderlying(cen::blend_factor::one_minus_src_color));

  ASSERT_EQ(SDL_BLENDFACTOR_SRC_ALPHA, cen::ToUnderlying(cen::blend_factor::src_alpha));
  ASSERT_EQ(SDL_BLENDFACTOR_ONE_MINUS_SRC_ALPHA,
            cen::ToUnderlying(cen::blend_factor::one_minus_src_alpha));

  ASSERT_EQ(SDL_BLENDFACTOR_DST_COLOR, cen::ToUnderlying(cen::blend_factor::dst_color));
  ASSERT_EQ(SDL_BLENDFACTOR_ONE_MINUS_DST_COLOR,
            cen::ToUnderlying(cen::blend_factor::one_minus_dst_color));

  ASSERT_EQ(SDL_BLENDFACTOR_DST_ALPHA, cen::ToUnderlying(cen::blend_factor::dst_alpha));
  ASSERT_EQ(SDL_BLENDFACTOR_ONE_MINUS_DST_ALPHA,
            cen::ToUnderlying(cen::blend_factor::one_minus_dst_alpha));
}

TEST(BlendFactor, ToString)
{
  ASSERT_THROW(cen::to_string(static_cast<cen::blend_factor>(100)), cen::Error);

  ASSERT_EQ("zero", cen::to_string(cen::blend_factor::zero));
  ASSERT_EQ("one", cen::to_string(cen::blend_factor::one));

  ASSERT_EQ("src_color", cen::to_string(cen::blend_factor::src_color));
  ASSERT_EQ("one_minus_src_color", cen::to_string(cen::blend_factor::one_minus_src_color));

  ASSERT_EQ("src_alpha", cen::to_string(cen::blend_factor::src_alpha));
  ASSERT_EQ("one_minus_src_alpha", cen::to_string(cen::blend_factor::one_minus_src_alpha));

  ASSERT_EQ("dst_color", cen::to_string(cen::blend_factor::dst_color));
  ASSERT_EQ("one_minus_dst_color", cen::to_string(cen::blend_factor::one_minus_dst_color));

  ASSERT_EQ("dst_alpha", cen::to_string(cen::blend_factor::dst_alpha));
  ASSERT_EQ("one_minus_dst_alpha", cen::to_string(cen::blend_factor::one_minus_dst_alpha));

  std::clog << "Blend factor example: " << cen::blend_factor::src_color << '\n';
}
