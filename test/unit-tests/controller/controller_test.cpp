#include "controller.hpp"

#include <gtest/gtest.h>

TEST(Controller, PointerConstructor)
{
  ASSERT_THROW(cen::controller{nullptr}, cen::exception);
}

TEST(Controller, IndexConstructor)
{
  ASSERT_THROW(cen::controller{}, cen::sdl_error);
}

TEST(Controller, FromJoystick)
{
  ASSERT_THROW(cen::controller::from_joystick(0), cen::sdl_error);
}

TEST(Controller, LoadControllerMappings)
{
  const auto path = "resources/controllers.txt";
  ASSERT_GT(cen::load_controller_mappings(path), 0);
  ASSERT_FALSE(cen::load_controller_mappings("foobar").has_value());
}

TEST(Controller, ControllerMappingCount)
{
  ASSERT_EQ(SDL_GameControllerNumMappings(), cen::controller_mapping_count());
}

TEST(Controller, Count)
{
  int amount = 0;
  for (auto i = 0, count = cen::Joystick::GetAmount().value(); i < count; ++i) {
    if (SDL_IsGameController(i)) {
      ++amount;
    }
  }

  ASSERT_EQ(amount, cen::controller::count());
}

#if SDL_VERSION_ATLEAST(2, 0, 12)

TEST(Controller, FromIndex)
{
  ASSERT_THROW(cen::controller::from_index(0), cen::sdl_error);
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)
