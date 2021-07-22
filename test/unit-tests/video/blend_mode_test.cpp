#include "video/blend_mode.hpp"

#include <gtest/gtest.h>

#include <iostream>  // cout

TEST(BlendMode, EqualityOperator)
{
  ASSERT_EQ(cen::blend_mode::none, SDL_BLENDMODE_NONE);
  ASSERT_EQ(cen::blend_mode::blend, SDL_BLENDMODE_BLEND);
  ASSERT_EQ(cen::blend_mode::add, SDL_BLENDMODE_ADD);
  ASSERT_EQ(cen::blend_mode::mod, SDL_BLENDMODE_MOD);
  ASSERT_EQ(cen::blend_mode::invalid, SDL_BLENDMODE_INVALID);

  ASSERT_EQ(SDL_BLENDMODE_NONE, cen::blend_mode::none);
  ASSERT_EQ(SDL_BLENDMODE_BLEND, cen::blend_mode::blend);
  ASSERT_EQ(SDL_BLENDMODE_ADD, cen::blend_mode::add);
  ASSERT_EQ(SDL_BLENDMODE_MOD, cen::blend_mode::mod);
  ASSERT_EQ(SDL_BLENDMODE_INVALID, cen::blend_mode::invalid);

#if SDL_VERSION_ATLEAST(2, 0, 12)
  ASSERT_EQ(cen::blend_mode::mul, SDL_BLENDMODE_MUL);

  ASSERT_EQ(SDL_BLENDMODE_MUL, cen::blend_mode::mul);
#endif  // SDL_VERSION_ATLEAST(2, 0, 12)
}

TEST(BlendMode, InequalityOperator)
{
  ASSERT_NE(cen::blend_mode::none, SDL_BLENDMODE_MOD);
  ASSERT_NE(cen::blend_mode::blend, SDL_BLENDMODE_INVALID);

  ASSERT_NE(SDL_BLENDMODE_ADD, cen::blend_mode::blend);
  ASSERT_NE(SDL_BLENDMODE_MOD, cen::blend_mode::add);
}

TEST(BlendMode, ToString)
{
  ASSERT_EQ("none", cen::to_string(cen::blend_mode::none));
  ASSERT_EQ("blend", cen::to_string(cen::blend_mode::blend));
  ASSERT_EQ("add", cen::to_string(cen::blend_mode::add));
  ASSERT_EQ("mod", cen::to_string(cen::blend_mode::mod));
  ASSERT_EQ("invalid", cen::to_string(cen::blend_mode::invalid));

#if SDL_VERSION_ATLEAST(2, 0, 12)

  ASSERT_EQ("mul", cen::to_string(cen::blend_mode::mul));
#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

  std::cout << "Blend mode example: " << cen::blend_mode::blend << '\n';
}