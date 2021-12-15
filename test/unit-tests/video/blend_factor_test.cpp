#include <gtest/gtest.h>

#include <iostream>  // clog

#include "core/common.hpp"
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
  ASSERT_THROW(cen::to_string(static_cast<cen::BlendFactor>(100)), cen::Error);

  ASSERT_EQ("Zero", cen::to_string(cen::BlendFactor::Zero));
  ASSERT_EQ("One", cen::to_string(cen::BlendFactor::One));

  ASSERT_EQ("SrcColor", cen::to_string(cen::BlendFactor::SrcColor));
  ASSERT_EQ("OneMinusSrcColor", cen::to_string(cen::BlendFactor::OneMinusSrcColor));

  ASSERT_EQ("SrcAlpha", cen::to_string(cen::BlendFactor::SrcAlpha));
  ASSERT_EQ("OneMinusSrcAlpha", cen::to_string(cen::BlendFactor::OneMinusSrcAlpha));

  ASSERT_EQ("DstColor", cen::to_string(cen::BlendFactor::DstColor));
  ASSERT_EQ("OneMinusDstColor", cen::to_string(cen::BlendFactor::OneMinusDstColor));

  ASSERT_EQ("DstAlpha", cen::to_string(cen::BlendFactor::DstAlpha));
  ASSERT_EQ("OneMinusDstAlpha", cen::to_string(cen::BlendFactor::OneMinusDstAlpha));

  std::clog << "Blend factor example: " << cen::BlendFactor::SrcColor << '\n';
}
