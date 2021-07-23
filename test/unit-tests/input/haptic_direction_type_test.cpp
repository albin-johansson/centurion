#include "input/haptic_direction_type.hpp"

#include <gtest/gtest.h>

#include <iostream>  // cout

#include "core/to_underlying.hpp"

TEST(HapticDirectionType, Values)
{
  ASSERT_EQ(SDL_HAPTIC_POLAR, cen::to_underlying(cen::haptic_direction_type::polar));
  ASSERT_EQ(SDL_HAPTIC_CARTESIAN,
            cen::to_underlying(cen::haptic_direction_type::cartesian));
  ASSERT_EQ(SDL_HAPTIC_SPHERICAL,
            cen::to_underlying(cen::haptic_direction_type::spherical));
}

TEST(HapticDirectionType, ToString)
{
  ASSERT_EQ("polar", cen::to_string(cen::haptic_direction_type::polar));
  ASSERT_EQ("cartesian", cen::to_string(cen::haptic_direction_type::cartesian));
  ASSERT_EQ("spherical", cen::to_string(cen::haptic_direction_type::spherical));

  std::cout << "Haptic direction type example: " << cen::haptic_direction_type::cartesian
            << '\n';
}
