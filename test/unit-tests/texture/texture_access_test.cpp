#include <gtest/gtest.h>

#include <iostream>  // cout

#include "common.hpp"
#include "render.hpp"

TEST(TextureAccess, Values)
{
  ASSERT_EQ(SDL_TEXTUREACCESS_STATIC, to_underlying(cen::texture_access::non_lockable));
  ASSERT_EQ(SDL_TEXTUREACCESS_STREAMING, to_underlying(cen::texture_access::streaming));
  ASSERT_EQ(SDL_TEXTUREACCESS_TARGET, to_underlying(cen::texture_access::target));
}

TEST(TextureAccess, ToString)
{
  ASSERT_THROW(to_string(static_cast<cen::texture_access>(4)), cen::exception);

  ASSERT_EQ("non_lockable", to_string(cen::texture_access::non_lockable));
  ASSERT_EQ("streaming", to_string(cen::texture_access::streaming));
  ASSERT_EQ("target", to_string(cen::texture_access::target));

  std::cout << "texture_access == " << cen::texture_access::streaming << '\n';
}
