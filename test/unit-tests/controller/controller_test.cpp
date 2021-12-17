#include "input/controller.hpp"

#include <gtest/gtest.h>

TEST(Controller, PointerConstructor)
{
  ASSERT_THROW(cen::Controller{nullptr}, cen::Error);
}

TEST(Controller, IndexConstructor)
{
  ASSERT_THROW(cen::Controller{}, cen::SDLError);
}

TEST(Controller, FromJoystick)
{
  ASSERT_THROW(cen::Controller::FromJoystick(0), cen::SDLError);
}

TEST(Controller, LoadControllerMappings)
{
  const auto path = "resources/controllers.txt";
  ASSERT_GT(cen::LoadControllerMappings(path), 0);
  ASSERT_FALSE(cen::LoadControllerMappings("foobar").has_value());
}

TEST(Controller, GetNumControllerMappings)
{
  ASSERT_EQ(SDL_GameControllerNumMappings(), cen::GetNumControllerMappings());
}

TEST(Controller, GetAmount)
{
  int amount = 0;
  for (auto i = 0, count = cen::Joystick::GetAmount().value(); i < count; ++i) {
    if (SDL_IsGameController(i)) {
      ++amount;
    }
  }

  ASSERT_EQ(amount, cen::Controller::GetAmount());
}

#if SDL_VERSION_ATLEAST(2, 0, 12)

TEST(Controller, FromIndex)
{
  ASSERT_THROW(cen::Controller::FromIndex(0), cen::SDLError);
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)
