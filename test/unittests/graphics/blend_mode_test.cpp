#include "video/blend_mode.hpp"

#include <gtest/gtest.h>

TEST(BlendMode, EqualityOperator)
{
  EXPECT_EQ(cen::blend_mode::none, SDL_BLENDMODE_NONE);
  EXPECT_EQ(cen::blend_mode::blend, SDL_BLENDMODE_BLEND);
  EXPECT_EQ(cen::blend_mode::add, SDL_BLENDMODE_ADD);
  EXPECT_EQ(cen::blend_mode::mod, SDL_BLENDMODE_MOD);
  EXPECT_EQ(cen::blend_mode::mul, SDL_BLENDMODE_MUL);
  EXPECT_EQ(cen::blend_mode::invalid, SDL_BLENDMODE_INVALID);

  EXPECT_EQ(SDL_BLENDMODE_NONE, cen::blend_mode::none);
  EXPECT_EQ(SDL_BLENDMODE_BLEND, cen::blend_mode::blend);
  EXPECT_EQ(SDL_BLENDMODE_ADD, cen::blend_mode::add);
  EXPECT_EQ(SDL_BLENDMODE_MOD, cen::blend_mode::mod);
  EXPECT_EQ(SDL_BLENDMODE_MUL, cen::blend_mode::mul);
  EXPECT_EQ(SDL_BLENDMODE_INVALID, cen::blend_mode::invalid);
}

TEST(BlendMode, InequalityOperator)
{
  EXPECT_NE(cen::blend_mode::none, SDL_BLENDMODE_MOD);
  EXPECT_NE(cen::blend_mode::blend, SDL_BLENDMODE_INVALID);

  EXPECT_NE(SDL_BLENDMODE_ADD, cen::blend_mode::blend);
  EXPECT_NE(SDL_BLENDMODE_MOD, cen::blend_mode::add);
}