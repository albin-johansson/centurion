#include "video/texture_access.hpp"

#include <gtest/gtest.h>

TEST(TextureAccess, EnumValues)
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
