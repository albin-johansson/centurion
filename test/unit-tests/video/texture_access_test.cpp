#include "video/texture_access.hpp"

#include <gtest/gtest.h>

#include <iostream>  // clog

TEST(TextureAccess, Values)
{
  ASSERT_EQ(cen::texture_access::no_lock, SDL_TEXTUREACCESS_STATIC);
  ASSERT_EQ(cen::texture_access::streaming, SDL_TEXTUREACCESS_STREAMING);
  ASSERT_EQ(cen::texture_access::target, SDL_TEXTUREACCESS_TARGET);

  ASSERT_EQ(SDL_TEXTUREACCESS_STATIC, cen::texture_access::no_lock);
  ASSERT_EQ(SDL_TEXTUREACCESS_STREAMING, cen::texture_access::streaming);
  ASSERT_EQ(SDL_TEXTUREACCESS_TARGET, cen::texture_access::target);

  ASSERT_NE(cen::texture_access::no_lock, SDL_TEXTUREACCESS_STREAMING);
  ASSERT_NE(SDL_TEXTUREACCESS_STREAMING, cen::texture_access::no_lock);
}

TEST(TextureAccess, ToString)
{
  ASSERT_THROW(cen::to_string(static_cast<cen::texture_access>(4)), cen::Error);

  ASSERT_EQ("no_lock", cen::to_string(cen::texture_access::no_lock));
  ASSERT_EQ("streaming", cen::to_string(cen::texture_access::streaming));
  ASSERT_EQ("target", cen::to_string(cen::texture_access::target));

  std::clog << "Texture access example: " << cen::texture_access::streaming << '\n';
}
