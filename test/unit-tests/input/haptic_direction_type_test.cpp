#include "input/haptic_direction_type.hpp"

#include <gtest/gtest.h>

#include <iostream>  // clog

#include "common.hpp"

TEST(HapticDirectionType, Values)
{
  ASSERT_EQ(SDL_HAPTIC_POLAR, cen::to_underlying(cen::haptic_direction_type::polar));
  ASSERT_EQ(SDL_HAPTIC_CARTESIAN, cen::to_underlying(cen::haptic_direction_type::cartesian));
  ASSERT_EQ(SDL_HAPTIC_SPHERICAL, cen::to_underlying(cen::haptic_direction_type::spherical));
}

TEST(HapticDirectionType, ToString)
{
  ASSERT_THROW(cen::ToString(static_cast<cen::haptic_direction_type>(3)), cen::exception);

  ASSERT_EQ("polar", cen::ToString(cen::haptic_direction_type::polar));
  ASSERT_EQ("cartesian", cen::ToString(cen::haptic_direction_type::cartesian));
  ASSERT_EQ("spherical", cen::ToString(cen::haptic_direction_type::spherical));

  std::clog << "Haptic direction type example: " << cen::haptic_direction_type::cartesian
            << '\n';
}
