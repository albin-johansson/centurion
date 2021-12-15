#include <gtest/gtest.h>

#include <iostream>  // clog

#include "core/common.hpp"
#include "input/joystick.hpp"

TEST(HatState, Values)
{
  ASSERT_EQ(SDL_HAT_CENTERED, cen::ToUnderlying(cen::HatState::Centered));
  ASSERT_EQ(SDL_HAT_UP, cen::ToUnderlying(cen::HatState::Up));
  ASSERT_EQ(SDL_HAT_RIGHT, cen::ToUnderlying(cen::HatState::Right));
  ASSERT_EQ(SDL_HAT_DOWN, cen::ToUnderlying(cen::HatState::Down));
  ASSERT_EQ(SDL_HAT_LEFT, cen::ToUnderlying(cen::HatState::Left));
  ASSERT_EQ(SDL_HAT_RIGHTUP, cen::ToUnderlying(cen::HatState::RightUp));
  ASSERT_EQ(SDL_HAT_RIGHTDOWN, cen::ToUnderlying(cen::HatState::RightDown));
  ASSERT_EQ(SDL_HAT_LEFTUP, cen::ToUnderlying(cen::HatState::LeftUp));
  ASSERT_EQ(SDL_HAT_LEFTDOWN, cen::ToUnderlying(cen::HatState::LeftDown));
}

TEST(HatState, ToString)
{
  ASSERT_THROW(cen::to_string(static_cast<cen::HatState>(0x10)), cen::Error);

  ASSERT_EQ("Centered", cen::to_string(cen::HatState::Centered));
  ASSERT_EQ("Up", cen::to_string(cen::HatState::Up));
  ASSERT_EQ("Right", cen::to_string(cen::HatState::Right));
  ASSERT_EQ("Down", cen::to_string(cen::HatState::Down));
  ASSERT_EQ("Left", cen::to_string(cen::HatState::Left));
  ASSERT_EQ("RightUp", cen::to_string(cen::HatState::RightUp));
  ASSERT_EQ("RightDown", cen::to_string(cen::HatState::RightDown));
  ASSERT_EQ("LeftUp", cen::to_string(cen::HatState::LeftUp));
  ASSERT_EQ("LeftDown", cen::to_string(cen::HatState::LeftDown));

  std::clog << "Hat state example: " << cen::HatState::Centered << '\n';
}
