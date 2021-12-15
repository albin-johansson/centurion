#include "video/texture_access.hpp"

#include <gtest/gtest.h>

#include <iostream>  // clog

#include "core/common.hpp"

TEST(TextureAccess, Values)
{
  ASSERT_EQ(cen::ToUnderlying(cen::TextureAccess::Static), SDL_TEXTUREACCESS_STATIC);
  ASSERT_EQ(cen::ToUnderlying(cen::TextureAccess::Streaming), SDL_TEXTUREACCESS_STREAMING);
  ASSERT_EQ(cen::ToUnderlying(cen::TextureAccess::Target), SDL_TEXTUREACCESS_TARGET);
}

TEST(TextureAccess, ToString)
{
  ASSERT_THROW(cen::to_string(static_cast<cen::TextureAccess>(4)), cen::Error);

  ASSERT_EQ("Static", cen::to_string(cen::TextureAccess::Static));
  ASSERT_EQ("Streaming", cen::to_string(cen::TextureAccess::Streaming));
  ASSERT_EQ("Target", cen::to_string(cen::TextureAccess::Target));

  std::clog << "Texture GetAccess example: " << cen::TextureAccess::Streaming << '\n';
}
