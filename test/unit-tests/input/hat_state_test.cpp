#include <gtest/gtest.h>

#include <iostream>  // clog

#include "common.hpp"
#include "input/joystick.hpp"

TEST(HatState, Values)
{
  ASSERT_EQ(SDL_HAT_CENTERED, cen::to_underlying(cen::HatState::Centered));
  ASSERT_EQ(SDL_HAT_UP, cen::to_underlying(cen::HatState::Up));
  ASSERT_EQ(SDL_HAT_RIGHT, cen::to_underlying(cen::HatState::Right));
  ASSERT_EQ(SDL_HAT_DOWN, cen::to_underlying(cen::HatState::Down));
  ASSERT_EQ(SDL_HAT_LEFT, cen::to_underlying(cen::HatState::Left));
  ASSERT_EQ(SDL_HAT_RIGHTUP, cen::to_underlying(cen::HatState::RightUp));
  ASSERT_EQ(SDL_HAT_RIGHTDOWN, cen::to_underlying(cen::HatState::RightDown));
  ASSERT_EQ(SDL_HAT_LEFTUP, cen::to_underlying(cen::HatState::LeftUp));
  ASSERT_EQ(SDL_HAT_LEFTDOWN, cen::to_underlying(cen::HatState::LeftDown));
}

TEST(HatState, ToString)
{
  ASSERT_THROW(cen::ToString(static_cast<cen::HatState>(0x10)), cen::exception);

  ASSERT_EQ("Centered", cen::ToString(cen::HatState::Centered));
  ASSERT_EQ("Up", cen::ToString(cen::HatState::Up));
  ASSERT_EQ("Right", cen::ToString(cen::HatState::Right));
  ASSERT_EQ("Down", cen::ToString(cen::HatState::Down));
  ASSERT_EQ("Left", cen::ToString(cen::HatState::Left));
  ASSERT_EQ("RightUp", cen::ToString(cen::HatState::RightUp));
  ASSERT_EQ("RightDown", cen::ToString(cen::HatState::RightDown));
  ASSERT_EQ("LeftUp", cen::ToString(cen::HatState::LeftUp));
  ASSERT_EQ("LeftDown", cen::ToString(cen::HatState::LeftDown));

  std::clog << "Hat state example: " << cen::HatState::Centered << '\n';
}
