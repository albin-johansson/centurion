#include <gtest/gtest.h>

#include <iostream>  // cout

#include "centurion/video.hpp"

TEST(BlendFactor, Values)
{
  ASSERT_EQ(SDL_BLENDFACTOR_ZERO, to_underlying(cen::blend_factor::zero));
  ASSERT_EQ(SDL_BLENDFACTOR_ONE, to_underlying(cen::blend_factor::one));

  ASSERT_EQ(SDL_BLENDFACTOR_SRC_COLOR, to_underlying(cen::blend_factor::src_color));
  ASSERT_EQ(SDL_BLENDFACTOR_ONE_MINUS_SRC_COLOR,
            to_underlying(cen::blend_factor::one_minus_src_color));

  ASSERT_EQ(SDL_BLENDFACTOR_SRC_ALPHA, to_underlying(cen::blend_factor::src_alpha));
  ASSERT_EQ(SDL_BLENDFACTOR_ONE_MINUS_SRC_ALPHA,
            to_underlying(cen::blend_factor::one_minus_src_alpha));

  ASSERT_EQ(SDL_BLENDFACTOR_DST_COLOR, to_underlying(cen::blend_factor::dst_color));
  ASSERT_EQ(SDL_BLENDFACTOR_ONE_MINUS_DST_COLOR,
            to_underlying(cen::blend_factor::one_minus_dst_color));

  ASSERT_EQ(SDL_BLENDFACTOR_DST_ALPHA, to_underlying(cen::blend_factor::dst_alpha));
  ASSERT_EQ(SDL_BLENDFACTOR_ONE_MINUS_DST_ALPHA,
            to_underlying(cen::blend_factor::one_minus_dst_alpha));
}

TEST(BlendFactor, ToString)
{
  ASSERT_THROW(to_string(static_cast<cen::blend_factor>(100)), cen::exception);

  ASSERT_EQ("zero", to_string(cen::blend_factor::zero));
  ASSERT_EQ("one", to_string(cen::blend_factor::one));

  ASSERT_EQ("src_color", to_string(cen::blend_factor::src_color));
  ASSERT_EQ("one_minus_src_color", to_string(cen::blend_factor::one_minus_src_color));

  ASSERT_EQ("src_alpha", to_string(cen::blend_factor::src_alpha));
  ASSERT_EQ("one_minus_src_alpha", to_string(cen::blend_factor::one_minus_src_alpha));

  ASSERT_EQ("dst_color", to_string(cen::blend_factor::dst_color));
  ASSERT_EQ("one_minus_dst_color", to_string(cen::blend_factor::one_minus_dst_color));

  ASSERT_EQ("dst_alpha", to_string(cen::blend_factor::dst_alpha));
  ASSERT_EQ("one_minus_dst_alpha", to_string(cen::blend_factor::one_minus_dst_alpha));

  std::cout << "blend_factor::src_color == " << cen::blend_factor::src_color << '\n';
}
