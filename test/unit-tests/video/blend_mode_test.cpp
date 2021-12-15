#include <gtest/gtest.h>

#include <iostream>  // clog

#include "core/common.hpp"
#include "video.hpp"

TEST(BlendMode, Values)
{
  ASSERT_EQ(cen::ToUnderlying(cen::BlendMode::None), SDL_BLENDMODE_NONE);
  ASSERT_EQ(cen::ToUnderlying(cen::BlendMode::Blend), SDL_BLENDMODE_BLEND);
  ASSERT_EQ(cen::ToUnderlying(cen::BlendMode::Add), SDL_BLENDMODE_ADD);
  ASSERT_EQ(cen::ToUnderlying(cen::BlendMode::Mod), SDL_BLENDMODE_MOD);
  ASSERT_EQ(cen::ToUnderlying(cen::BlendMode::Invalid), SDL_BLENDMODE_INVALID);

#if SDL_VERSION_ATLEAST(2, 0, 12)
  ASSERT_EQ(cen::ToUnderlying(cen::BlendMode::Mul), SDL_BLENDMODE_MUL);
#endif  // SDL_VERSION_ATLEAST(2, 0, 12)
}

TEST(BlendMode, ToString)
{
  ASSERT_THROW(cen::to_string(static_cast<cen::BlendMode>(SDL_BLENDMODE_INVALID - 1)),
               cen::Error);

  ASSERT_EQ("None", cen::to_string(cen::BlendMode::None));
  ASSERT_EQ("Blend", cen::to_string(cen::BlendMode::Blend));
  ASSERT_EQ("Add", cen::to_string(cen::BlendMode::Add));
  ASSERT_EQ("Mod", cen::to_string(cen::BlendMode::Mod));
  ASSERT_EQ("Invalid", cen::to_string(cen::BlendMode::Invalid));

#if SDL_VERSION_ATLEAST(2, 0, 12)
  ASSERT_EQ("Mul", cen::to_string(cen::BlendMode::Mul));
#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

  std::clog << "Blend mode example: " << cen::BlendMode::Blend << '\n';
}