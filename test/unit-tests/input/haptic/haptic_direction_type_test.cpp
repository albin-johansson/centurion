#include "centurion/input/haptic_direction_type.hpp"

#include <gtest/gtest.h>

#include <iostream>  // cout

TEST(HapticDirectionType, Values)
{
  ASSERT_EQ(SDL_HAPTIC_POLAR, to_underlying(cen::haptic_direction_type::polar));
  ASSERT_EQ(SDL_HAPTIC_CARTESIAN, to_underlying(cen::haptic_direction_type::cartesian));
  ASSERT_EQ(SDL_HAPTIC_SPHERICAL, to_underlying(cen::haptic_direction_type::spherical));
}

TEST(HapticDirectionType, ToString)
{
  ASSERT_THROW(ToString(cen::haptic_direction_type(3)), cen::exception);

  ASSERT_EQ("polar", ToString(cen::haptic_direction_type::polar));
  ASSERT_EQ("cartesian", ToString(cen::haptic_direction_type::cartesian));
  ASSERT_EQ("spherical", ToString(cen::haptic_direction_type::spherical));

  std::cout << "haptic_direction_type::cartesian == " << cen::haptic_direction_type::cartesian
            << '\n';
}
