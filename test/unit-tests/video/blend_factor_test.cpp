#include "video/blend_factor.hpp"

#include <gtest/gtest.h>

#include <iostream>  // clog

TEST(BlendFactor, Values)
{
  ASSERT_EQ(SDL_BLENDFACTOR_ZERO, cen::blend_factor::zero);
  ASSERT_EQ(SDL_BLENDFACTOR_ONE, cen::blend_factor::one);

  ASSERT_EQ(SDL_BLENDFACTOR_SRC_COLOR, cen::blend_factor::src_color);
  ASSERT_EQ(SDL_BLENDFACTOR_ONE_MINUS_SRC_COLOR, cen::blend_factor::one_minus_src_color);

  ASSERT_EQ(SDL_BLENDFACTOR_SRC_ALPHA, cen::blend_factor::src_alpha);
  ASSERT_EQ(SDL_BLENDFACTOR_ONE_MINUS_SRC_ALPHA, cen::blend_factor::one_minus_src_alpha);

  ASSERT_EQ(SDL_BLENDFACTOR_DST_COLOR, cen::blend_factor::dst_color);
  ASSERT_EQ(SDL_BLENDFACTOR_ONE_MINUS_DST_COLOR, cen::blend_factor::one_minus_dst_color);

  ASSERT_EQ(SDL_BLENDFACTOR_DST_ALPHA, cen::blend_factor::dst_alpha);
  ASSERT_EQ(SDL_BLENDFACTOR_ONE_MINUS_DST_ALPHA, cen::blend_factor::one_minus_dst_alpha);

  ASSERT_NE(cen::blend_factor::one, SDL_BLENDFACTOR_SRC_ALPHA);
}

TEST(BlendFactor, ToString)
{
  ASSERT_THROW(cen::to_string(static_cast<cen::blend_factor>(100)), cen::cen_error);

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
