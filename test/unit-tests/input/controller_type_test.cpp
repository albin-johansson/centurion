#include <gtest/gtest.h>

#include <iostream>  // clog

#include "core/common.hpp"
#include "input/controller.hpp"

#if SDL_VERSION_ATLEAST(2, 0, 12)

TEST(ControllerType, Values)
{
  using type = cen::controller_type;

  ASSERT_EQ(cen::to_underlying(type::unknown), SDL_CONTROLLER_TYPE_UNKNOWN);
  ASSERT_EQ(cen::to_underlying(type::xbox_360), SDL_CONTROLLER_TYPE_XBOX360);
  ASSERT_EQ(cen::to_underlying(type::xbox_one), SDL_CONTROLLER_TYPE_XBOXONE);
  ASSERT_EQ(cen::to_underlying(type::ps3), SDL_CONTROLLER_TYPE_PS3);
  ASSERT_EQ(cen::to_underlying(type::ps4), SDL_CONTROLLER_TYPE_PS4);
  ASSERT_EQ(cen::to_underlying(type::nintendo_switch_pro),
            SDL_CONTROLLER_TYPE_NINTENDO_SWITCH_PRO);

#if SDL_VERSION_ATLEAST(2, 0, 14)
  ASSERT_EQ(cen::to_underlying(type::ps5), SDL_CONTROLLER_TYPE_PS5);
  ASSERT_EQ(cen::to_underlying(type::virt), SDL_CONTROLLER_TYPE_VIRTUAL);
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

#if SDL_VERSION_ATLEAST(2, 0, 16)
  ASSERT_EQ(cen::to_underlying(type::amazon_luna), SDL_CONTROLLER_TYPE_AMAZON_LUNA);
  ASSERT_EQ(cen::to_underlying(type::google_stadia), SDL_CONTROLLER_TYPE_GOOGLE_STADIA);
#endif  // SDL_VERSION_ATLEAST(2, 0, 16)
}

TEST(ControllerType, ToString)
{
  ASSERT_THROW(cen::to_string(static_cast<cen::controller_type>(10)), cen::cen_error);

  ASSERT_EQ("unknown", cen::to_string(cen::controller_type::unknown));
  ASSERT_EQ("nintendo_switch_pro", cen::to_string(cen::controller_type::nintendo_switch_pro));
  ASSERT_EQ("xbox_360", cen::to_string(cen::controller_type::xbox_360));
  ASSERT_EQ("xbox_one", cen::to_string(cen::controller_type::xbox_one));
  ASSERT_EQ("ps3", cen::to_string(cen::controller_type::ps3));
  ASSERT_EQ("ps4", cen::to_string(cen::controller_type::ps4));

#if SDL_VERSION_ATLEAST(2, 0, 14)
  ASSERT_EQ("ps5", cen::to_string(cen::controller_type::ps5));
  ASSERT_EQ("virt", cen::to_string(cen::controller_type::virt));
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

#if SDL_VERSION_ATLEAST(2, 0, 16)
  ASSERT_EQ("amazon_luna", cen::to_string(cen::controller_type::amazon_luna));
  ASSERT_EQ("google_stadia", cen::to_string(cen::controller_type::google_stadia));
#endif  // SDL_VERSION_ATLEAST(2, 0, 16)

  std::clog << "Controller type example: " << cen::controller_type::ps4 << '\n';
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)
