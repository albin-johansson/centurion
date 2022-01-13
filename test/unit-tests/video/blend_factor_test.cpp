#include <gtest/gtest.h>

#include <iostream>  // clog

#include "common.hpp"
#include "video.hpp"

TEST(BlendFactor, Values)
{
  ASSERT_EQ(SDL_BLENDFACTOR_ZERO, cen::ToUnderlying(cen::BlendFactor::Zero));
  ASSERT_EQ(SDL_BLENDFACTOR_ONE, cen::ToUnderlying(cen::BlendFactor::One));

  ASSERT_EQ(SDL_BLENDFACTOR_SRC_COLOR, cen::ToUnderlying(cen::BlendFactor::SrcColor));
  ASSERT_EQ(SDL_BLENDFACTOR_ONE_MINUS_SRC_COLOR,
            cen::ToUnderlying(cen::BlendFactor::OneMinusSrcColor));

  ASSERT_EQ(SDL_BLENDFACTOR_SRC_ALPHA, cen::ToUnderlying(cen::BlendFactor::SrcAlpha));
  ASSERT_EQ(SDL_BLENDFACTOR_ONE_MINUS_SRC_ALPHA,
            cen::ToUnderlying(cen::BlendFactor::OneMinusSrcAlpha));

  ASSERT_EQ(SDL_BLENDFACTOR_DST_COLOR, cen::ToUnderlying(cen::BlendFactor::DstColor));
  ASSERT_EQ(SDL_BLENDFACTOR_ONE_MINUS_DST_COLOR,
            cen::ToUnderlying(cen::BlendFactor::OneMinusDstColor));

  ASSERT_EQ(SDL_BLENDFACTOR_DST_ALPHA, cen::ToUnderlying(cen::BlendFactor::DstAlpha));
  ASSERT_EQ(SDL_BLENDFACTOR_ONE_MINUS_DST_ALPHA,
            cen::ToUnderlying(cen::BlendFactor::OneMinusDstAlpha));
}

TEST(BlendFactor, ToString)
{
  ASSERT_THROW(cen::ToString(static_cast<cen::BlendFactor>(100)), cen::Error);

  ASSERT_EQ("Zero", cen::ToString(cen::BlendFactor::Zero));
  ASSERT_EQ("One", cen::ToString(cen::BlendFactor::One));

  ASSERT_EQ("SrcColor", cen::ToString(cen::BlendFactor::SrcColor));
  ASSERT_EQ("OneMinusSrcColor", cen::ToString(cen::BlendFactor::OneMinusSrcColor));

  ASSERT_EQ("SrcAlpha", cen::ToString(cen::BlendFactor::SrcAlpha));
  ASSERT_EQ("OneMinusSrcAlpha", cen::ToString(cen::BlendFactor::OneMinusSrcAlpha));

  ASSERT_EQ("DstColor", cen::ToString(cen::BlendFactor::DstColor));
  ASSERT_EQ("OneMinusDstColor", cen::ToString(cen::BlendFactor::OneMinusDstColor));

  ASSERT_EQ("DstAlpha", cen::ToString(cen::BlendFactor::DstAlpha));
  ASSERT_EQ("OneMinusDstAlpha", cen::ToString(cen::BlendFactor::OneMinusDstAlpha));

  std::clog << "Blend factor example: " << cen::BlendFactor::SrcColor << '\n';
}
