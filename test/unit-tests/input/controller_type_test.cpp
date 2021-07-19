#include "input/controller_type.hpp"

#include <gtest/gtest.h>

#if SDL_VERSION_ATLEAST(2, 0, 12)

TEST(ControllerType, Values)
{
  using type = cen::controller_type;

  ASSERT_EQ(type::unknown, SDL_CONTROLLER_TYPE_UNKNOWN);
  ASSERT_EQ(type::xbox_360, SDL_CONTROLLER_TYPE_XBOX360);
  ASSERT_EQ(type::xbox_one, SDL_CONTROLLER_TYPE_XBOXONE);
  ASSERT_EQ(type::ps3, SDL_CONTROLLER_TYPE_PS3);
  ASSERT_EQ(type::ps4, SDL_CONTROLLER_TYPE_PS4);
  ASSERT_EQ(type::nintendo_switch_pro, SDL_CONTROLLER_TYPE_NINTENDO_SWITCH_PRO);

  ASSERT_EQ(SDL_CONTROLLER_TYPE_UNKNOWN, type::unknown);
  ASSERT_EQ(SDL_CONTROLLER_TYPE_XBOX360, type::xbox_360);
  ASSERT_EQ(SDL_CONTROLLER_TYPE_XBOXONE, type::xbox_one);
  ASSERT_EQ(SDL_CONTROLLER_TYPE_PS3, type::ps3);
  ASSERT_EQ(SDL_CONTROLLER_TYPE_PS4, type::ps4);
  ASSERT_EQ(SDL_CONTROLLER_TYPE_NINTENDO_SWITCH_PRO, type::nintendo_switch_pro);

#if SDL_VERSION_ATLEAST(2, 0, 14)
  ASSERT_EQ(type::ps5, SDL_CONTROLLER_TYPE_PS5);
  ASSERT_EQ(type::virt, SDL_CONTROLLER_TYPE_VIRTUAL);

  ASSERT_EQ(SDL_CONTROLLER_TYPE_PS5, type::ps5);
  ASSERT_EQ(SDL_CONTROLLER_TYPE_VIRTUAL, type::virt);
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  ASSERT_NE(type::ps4, SDL_CONTROLLER_TYPE_NINTENDO_SWITCH_PRO);
  ASSERT_NE(SDL_CONTROLLER_TYPE_XBOX360, type::unknown);
}

TEST(ControllerType, ToString)
{
  ASSERT_EQ("unknown", cen::to_string(cen::controller_type::unknown));
  ASSERT_EQ("nintendo_switch_pro",
            cen::to_string(cen::controller_type::nintendo_switch_pro));
  ASSERT_EQ("xbox_360", cen::to_string(cen::controller_type::xbox_360));
  ASSERT_EQ("xbox_one", cen::to_string(cen::controller_type::xbox_one));
  ASSERT_EQ("ps3", cen::to_string(cen::controller_type::ps3));
  ASSERT_EQ("ps4", cen::to_string(cen::controller_type::ps4));

#if SDL_VERSION_ATLEAST(2, 0, 14)
  ASSERT_EQ("ps5", cen::to_string(cen::controller_type::ps5));
  ASSERT_EQ("virt", cen::to_string(cen::controller_type::virt));
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)
