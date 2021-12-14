#include "video/blend_mode.hpp"

#include <gtest/gtest.h>

#include <iostream>  // clog

#include "core/common.hpp"

TEST(BlendMode, Values)
{
  ASSERT_EQ(cen::ToUnderlying(cen::BlendMode::none), SDL_BLENDMODE_NONE);
  ASSERT_EQ(cen::ToUnderlying(cen::BlendMode::blend), SDL_BLENDMODE_BLEND);
  ASSERT_EQ(cen::ToUnderlying(cen::BlendMode::add), SDL_BLENDMODE_ADD);
  ASSERT_EQ(cen::ToUnderlying(cen::BlendMode::mod), SDL_BLENDMODE_MOD);
  ASSERT_EQ(cen::ToUnderlying(cen::BlendMode::invalid), SDL_BLENDMODE_INVALID);

#if SDL_VERSION_ATLEAST(2, 0, 12)
  ASSERT_EQ(cen::ToUnderlying(cen::BlendMode::mul), SDL_BLENDMODE_MUL);
#endif  // SDL_VERSION_ATLEAST(2, 0, 12)
}

TEST(BlendMode, ToString)
{
  ASSERT_THROW(cen::to_string(static_cast<cen::BlendMode>(SDL_BLENDMODE_INVALID - 1)),
               cen::Error);

  ASSERT_EQ("none", cen::to_string(cen::BlendMode::none));
  ASSERT_EQ("blend", cen::to_string(cen::BlendMode::blend));
  ASSERT_EQ("add", cen::to_string(cen::BlendMode::add));
  ASSERT_EQ("mod", cen::to_string(cen::BlendMode::mod));
  ASSERT_EQ("invalid", cen::to_string(cen::BlendMode::invalid));

#if SDL_VERSION_ATLEAST(2, 0, 12)
  ASSERT_EQ("mul", cen::to_string(cen::BlendMode::mul));
#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

  std::clog << "Blend mode example: " << cen::BlendMode::blend << '\n';
}