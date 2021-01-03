#include "texture_access.hpp"

#include <gtest/gtest.h>

TEST(TextureAccess, EnumValues)
{
  EXPECT_EQ(cen::texture_access::no_lock, SDL_TEXTUREACCESS_STATIC);
  EXPECT_EQ(cen::texture_access::streaming, SDL_TEXTUREACCESS_STREAMING);
  EXPECT_EQ(cen::texture_access::target, SDL_TEXTUREACCESS_TARGET);

  EXPECT_EQ(SDL_TEXTUREACCESS_STATIC, cen::texture_access::no_lock);
  EXPECT_EQ(SDL_TEXTUREACCESS_STREAMING, cen::texture_access::streaming);
  EXPECT_EQ(SDL_TEXTUREACCESS_TARGET, cen::texture_access::target);

  EXPECT_NE(cen::texture_access::no_lock, SDL_TEXTUREACCESS_STREAMING);
  EXPECT_NE(SDL_TEXTUREACCESS_STREAMING, cen::texture_access::no_lock);
}
