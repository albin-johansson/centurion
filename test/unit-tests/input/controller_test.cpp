#include "input/controller.hpp"

#include <gtest/gtest.h>

TEST(Controller, PointerConstructor)
{
  ASSERT_THROW(cen::controller{nullptr}, cen::cen_error);
}

TEST(Controller, IndexConstructor)
{
  ASSERT_THROW(cen::controller{}, cen::sdl_error);
}

TEST(Controller, FromJoystick)
{
  ASSERT_THROW(cen::controller::from_joystick(0), cen::sdl_error);
}

TEST(Controller, LoadMappings)
{
  const auto path = "resources/controllers.txt";
  ASSERT_GT(cen::controller::load_mappings(path), 0);
  ASSERT_FALSE(cen::controller::load_mappings("foobar").has_value());
}

TEST(Controller, MappingCount)
{
  ASSERT_EQ(SDL_GameControllerNumMappings(), cen::controller::mapping_count());
}

TEST(Controller, Count)
{
  auto nControllers = 0;
  for (auto i = 0, count = cen::joystick::count().value(); i < count; ++i) {
    if (SDL_IsGameController(i)) {
      ++nControllers;
    }
  }

  ASSERT_EQ(nControllers, cen::controller::count());
}

#if SDL_VERSION_ATLEAST(2, 0, 12)

TEST(Controller, FromIndex)
{
  ASSERT_THROW(cen::controller::from_index(0), cen::sdl_error);
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)
