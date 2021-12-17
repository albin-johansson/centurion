#include <gtest/gtest.h>

#include <iostream>  // clog

#include "core/common.hpp"
#include "input/controller.hpp"

#if SDL_VERSION_ATLEAST(2, 0, 12)

using Type = cen::ControllerType;

TEST(ControllerType, Values)
{
  ASSERT_EQ(ToUnderlying(Type::Unknown), SDL_CONTROLLER_TYPE_UNKNOWN);
  ASSERT_EQ(ToUnderlying(Type::Xbox360), SDL_CONTROLLER_TYPE_XBOX360);
  ASSERT_EQ(ToUnderlying(Type::XboxOne), SDL_CONTROLLER_TYPE_XBOXONE);
  ASSERT_EQ(ToUnderlying(Type::PS3), SDL_CONTROLLER_TYPE_PS3);
  ASSERT_EQ(ToUnderlying(Type::PS4), SDL_CONTROLLER_TYPE_PS4);
  ASSERT_EQ(ToUnderlying(Type::NintendoSwitchPro), SDL_CONTROLLER_TYPE_NINTENDO_SWITCH_PRO);

#if SDL_VERSION_ATLEAST(2, 0, 14)
  ASSERT_EQ(ToUnderlying(Type::PS5), SDL_CONTROLLER_TYPE_PS5);
  ASSERT_EQ(ToUnderlying(Type::Virtual), SDL_CONTROLLER_TYPE_VIRTUAL);
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

#if SDL_VERSION_ATLEAST(2, 0, 16)
  ASSERT_EQ(ToUnderlying(Type::AmazonLuna), SDL_CONTROLLER_TYPE_AMAZON_LUNA);
  ASSERT_EQ(ToUnderlying(Type::GoogleStadia), SDL_CONTROLLER_TYPE_GOOGLE_STADIA);
#endif  // SDL_VERSION_ATLEAST(2, 0, 16)
}

TEST(ControllerType, ToString)
{
  ASSERT_THROW(to_string(static_cast<Type>(10)), cen::Error);

  ASSERT_EQ("Unknown", to_string(Type::Unknown));
  ASSERT_EQ("NintendoSwitchPro", to_string(Type::NintendoSwitchPro));
  ASSERT_EQ("Xbox360", to_string(Type::Xbox360));
  ASSERT_EQ("XboxOne", to_string(Type::XboxOne));
  ASSERT_EQ("PS3", to_string(Type::PS3));
  ASSERT_EQ("PS4", to_string(Type::PS4));

#if SDL_VERSION_ATLEAST(2, 0, 14)
  ASSERT_EQ("PS5", to_string(Type::PS5));
  ASSERT_EQ("Virtual", to_string(Type::Virtual));
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

#if SDL_VERSION_ATLEAST(2, 0, 16)
  ASSERT_EQ("AmazonLuna", to_string(Type::AmazonLuna));
  ASSERT_EQ("GoogleStadia", to_string(Type::GoogleStadia));
#endif  // SDL_VERSION_ATLEAST(2, 0, 16)

  std::clog << "Controller Type example: " << Type::PS4 << '\n';
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)
