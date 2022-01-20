#include <gtest/gtest.h>

#include <iostream>  // cout

#include "common.hpp"
#include "video.hpp"

TEST(BlendMode, Values)
{
  ASSERT_EQ(SDL_BLENDMODE_NONE, to_underlying(cen::blend_mode::none));
  ASSERT_EQ(SDL_BLENDMODE_BLEND, to_underlying(cen::blend_mode::blend));
  ASSERT_EQ(SDL_BLENDMODE_ADD, to_underlying(cen::blend_mode::add));
  ASSERT_EQ(SDL_BLENDMODE_MOD, to_underlying(cen::blend_mode::mod));
  ASSERT_EQ(SDL_BLENDMODE_INVALID, to_underlying(cen::blend_mode::invalid));

#if SDL_VERSION_ATLEAST(2, 0, 12)
  ASSERT_EQ(SDL_BLENDMODE_MUL, to_underlying(cen::blend_mode::mul));
#endif  // SDL_VERSION_ATLEAST(2, 0, 12)
}

TEST(BlendMode, ToString)
{
  ASSERT_THROW(to_string(static_cast<cen::blend_mode>(SDL_BLENDMODE_INVALID - 1)),
               cen::exception);

  ASSERT_EQ("none", to_string(cen::blend_mode::none));
  ASSERT_EQ("blend", to_string(cen::blend_mode::blend));
  ASSERT_EQ("add", to_string(cen::blend_mode::add));
  ASSERT_EQ("mod", to_string(cen::blend_mode::mod));
  ASSERT_EQ("invalid", to_string(cen::blend_mode::invalid));

#if SDL_VERSION_ATLEAST(2, 0, 12)
  ASSERT_EQ("mul", to_string(cen::blend_mode::mul));
#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

  std::cout << "blend_mode::blend == " << cen::blend_mode::blend << '\n';
}