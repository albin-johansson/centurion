#include <gtest/gtest.h>

#include <iostream>  // clog

#include "common.hpp"
#include "event.hpp"

using Position = cen::JoyHatPosition;

TEST(JoyHatPosition, Values)
{
  ASSERT_EQ(ToUnderlying(Position::LeftUp), SDL_HAT_LEFTUP);
  ASSERT_EQ(ToUnderlying(Position::Left), SDL_HAT_LEFT);
  ASSERT_EQ(ToUnderlying(Position::LeftDown), SDL_HAT_LEFTDOWN);
  ASSERT_EQ(ToUnderlying(Position::Up), SDL_HAT_UP);
  ASSERT_EQ(ToUnderlying(Position::Centered), SDL_HAT_CENTERED);
  ASSERT_EQ(ToUnderlying(Position::Down), SDL_HAT_DOWN);
  ASSERT_EQ(ToUnderlying(Position::RightUp), SDL_HAT_RIGHTUP);
  ASSERT_EQ(ToUnderlying(Position::Right), SDL_HAT_RIGHT);
  ASSERT_EQ(ToUnderlying(Position::RightDown), SDL_HAT_RIGHTDOWN);
}

TEST(JoyHatPosition, ToString)
{
  ASSERT_THROW(ToString(static_cast<Position>(SDL_HAT_RIGHTDOWN + 1)), cen::Error);

  ASSERT_EQ("LeftUp", ToString(Position::LeftUp));
  ASSERT_EQ("Left", ToString(Position::Left));
  ASSERT_EQ("LeftDown", ToString(Position::LeftDown));
  ASSERT_EQ("Up", ToString(Position::Up));
  ASSERT_EQ("Centered", ToString(Position::Centered));
  ASSERT_EQ("Down", ToString(Position::Down));
  ASSERT_EQ("RightUp", ToString(Position::RightUp));
  ASSERT_EQ("Right", ToString(Position::Right));
  ASSERT_EQ("RightDown", ToString(Position::RightDown));

  std::clog << "Joystick hat position example: " << Position::Left << '\n';
}
