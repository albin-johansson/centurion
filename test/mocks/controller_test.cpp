#include "controller.hpp"

#include <fff.h>
#include <gtest/gtest.h>

extern "C" {

FAKE_VOID_FUNC(SDL_GameControllerUpdate)

FAKE_VALUE_FUNC(SDL_bool, SDL_IsGameController, int)

}

TEST(Controller, Update)
{
  cen::controller::update();
  EXPECT_EQ(1, SDL_GameControllerUpdate_fake.call_count);
}

TEST(Controller, IsSupported)
{
  const auto supported = cen::controller::is_supported(0);
  EXPECT_EQ(1, SDL_IsGameController_fake.call_count);
}