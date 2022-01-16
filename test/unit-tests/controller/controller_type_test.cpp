#include <gtest/gtest.h>

#include <iostream>  // clog

#include "common.hpp"
#include "input/controller.hpp"

#if SDL_VERSION_ATLEAST(2, 0, 12)

using Type = cen::ControllerType;

TEST(ControllerType, Values)
{
  ASSERT_EQ(to_underlying(Type::Unknown), SDL_CONTROLLER_TYPE_UNKNOWN);
  ASSERT_EQ(to_underlying(Type::Xbox360), SDL_CONTROLLER_TYPE_XBOX360);
  ASSERT_EQ(to_underlying(Type::XboxOne), SDL_CONTROLLER_TYPE_XBOXONE);
  ASSERT_EQ(to_underlying(Type::PS3), SDL_CONTROLLER_TYPE_PS3);
  ASSERT_EQ(to_underlying(Type::PS4), SDL_CONTROLLER_TYPE_PS4);
  ASSERT_EQ(to_underlying(Type::NintendoSwitchPro), SDL_CONTROLLER_TYPE_NINTENDO_SWITCH_PRO);

#if SDL_VERSION_ATLEAST(2, 0, 14)
  ASSERT_EQ(to_underlying(Type::PS5), SDL_CONTROLLER_TYPE_PS5);
  ASSERT_EQ(to_underlying(Type::Virtual), SDL_CONTROLLER_TYPE_VIRTUAL);
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

#if SDL_VERSION_ATLEAST(2, 0, 16)
  ASSERT_EQ(to_underlying(Type::AmazonLuna), SDL_CONTROLLER_TYPE_AMAZON_LUNA);
  ASSERT_EQ(to_underlying(Type::GoogleStadia), SDL_CONTROLLER_TYPE_GOOGLE_STADIA);
#endif  // SDL_VERSION_ATLEAST(2, 0, 16)
}

TEST(ControllerType, ToString)
{
  ASSERT_THROW(ToString(static_cast<Type>(10)), cen::exception);

  ASSERT_EQ("Unknown", ToString(Type::Unknown));
  ASSERT_EQ("NintendoSwitchPro", ToString(Type::NintendoSwitchPro));
  ASSERT_EQ("Xbox360", ToString(Type::Xbox360));
  ASSERT_EQ("XboxOne", ToString(Type::XboxOne));
  ASSERT_EQ("PS3", ToString(Type::PS3));
  ASSERT_EQ("PS4", ToString(Type::PS4));

#if SDL_VERSION_ATLEAST(2, 0, 14)
  ASSERT_EQ("PS5", ToString(Type::PS5));
  ASSERT_EQ("Virtual", ToString(Type::Virtual));
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

#if SDL_VERSION_ATLEAST(2, 0, 16)
  ASSERT_EQ("AmazonLuna", ToString(Type::AmazonLuna));
  ASSERT_EQ("GoogleStadia", ToString(Type::GoogleStadia));
#endif  // SDL_VERSION_ATLEAST(2, 0, 16)

  std::clog << "Controller Type example: " << Type::PS4 << '\n';
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)
