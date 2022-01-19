#include <gtest/gtest.h>

#include <iostream>  // clog

#include "common.hpp"
#include "input/controller.hpp"

#if SDL_VERSION_ATLEAST(2, 0, 12)

using type = cen::ControllerType;

TEST(ControllerType, Values)
{
  ASSERT_EQ(to_underlying(type::Unknown), SDL_CONTROLLER_TYPE_UNKNOWN);
  ASSERT_EQ(to_underlying(type::Xbox360), SDL_CONTROLLER_TYPE_XBOX360);
  ASSERT_EQ(to_underlying(type::XboxOne), SDL_CONTROLLER_TYPE_XBOXONE);
  ASSERT_EQ(to_underlying(type::PS3), SDL_CONTROLLER_TYPE_PS3);
  ASSERT_EQ(to_underlying(type::PS4), SDL_CONTROLLER_TYPE_PS4);
  ASSERT_EQ(to_underlying(type::NintendoSwitchPro), SDL_CONTROLLER_TYPE_NINTENDO_SWITCH_PRO);

#if SDL_VERSION_ATLEAST(2, 0, 14)
  ASSERT_EQ(to_underlying(type::PS5), SDL_CONTROLLER_TYPE_PS5);
  ASSERT_EQ(to_underlying(type::Virtual), SDL_CONTROLLER_TYPE_VIRTUAL);
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

#if SDL_VERSION_ATLEAST(2, 0, 16)
  ASSERT_EQ(to_underlying(type::AmazonLuna), SDL_CONTROLLER_TYPE_AMAZON_LUNA);
  ASSERT_EQ(to_underlying(type::GoogleStadia), SDL_CONTROLLER_TYPE_GOOGLE_STADIA);
#endif  // SDL_VERSION_ATLEAST(2, 0, 16)
}

TEST(ControllerType, ToString)
{
  ASSERT_THROW(ToString(static_cast<type>(10)), cen::exception);

  ASSERT_EQ("Unknown", ToString(type::Unknown));
  ASSERT_EQ("NintendoSwitchPro", ToString(type::NintendoSwitchPro));
  ASSERT_EQ("Xbox360", ToString(type::Xbox360));
  ASSERT_EQ("XboxOne", ToString(type::XboxOne));
  ASSERT_EQ("PS3", ToString(type::PS3));
  ASSERT_EQ("PS4", ToString(type::PS4));

#if SDL_VERSION_ATLEAST(2, 0, 14)
  ASSERT_EQ("PS5", ToString(type::PS5));
  ASSERT_EQ("Virtual", ToString(type::Virtual));
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

#if SDL_VERSION_ATLEAST(2, 0, 16)
  ASSERT_EQ("AmazonLuna", ToString(type::AmazonLuna));
  ASSERT_EQ("GoogleStadia", ToString(type::GoogleStadia));
#endif  // SDL_VERSION_ATLEAST(2, 0, 16)

  std::clog << "Controller Type example: " << type::PS4 << '\n';
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)
