#include "controller.hpp"

#include <fff.h>
#include <gtest/gtest.h>

#include <array>  // array

// clang-format off
extern "C" {
FAKE_VOID_FUNC(SDL_GameControllerUpdate)
FAKE_VOID_FUNC(SDL_GameControllerSetPlayerIndex, SDL_GameController*, int)

FAKE_VALUE_FUNC(Uint16, SDL_GameControllerGetProduct, SDL_GameController*)
FAKE_VALUE_FUNC(Uint16, SDL_GameControllerGetVendor, SDL_GameController*)
FAKE_VALUE_FUNC(int, SDL_GameControllerRumble, SDL_GameController*, Uint16, Uint16, Uint32)
FAKE_VALUE_FUNC(SDL_bool, SDL_IsGameController, int)
}
// clang-format on

class ControllerTest : public testing::Test
{
 protected:
  void SetUp() override
  {
    RESET_FAKE(SDL_GameControllerUpdate);
    RESET_FAKE(SDL_GameControllerSetPlayerIndex);

    RESET_FAKE(SDL_GameControllerGetProduct);
    RESET_FAKE(SDL_GameControllerGetVendor);
    RESET_FAKE(SDL_GameControllerRumble);
    RESET_FAKE(SDL_IsGameController);
  }

  /**
   * We use a `controller_handle` because it doesn't throw when the pointer is
   * null, this doesn't matter that much since they share implementations of all
   * relevant functions.
   */
  cen::controller_handle m_handle{nullptr};
};

TEST_F(ControllerTest, Rumble)
{
  m_handle.rumble(0, 10, cen::milliseconds<cen::u32>{1});
  EXPECT_EQ(1, SDL_GameControllerRumble_fake.call_count);
}

TEST_F(ControllerTest, StopRumble)
{
  m_handle.stop_rumble();
  EXPECT_EQ(0, SDL_GameControllerRumble_fake.arg1_val);
  EXPECT_EQ(0, SDL_GameControllerRumble_fake.arg2_val);
  EXPECT_EQ(0, SDL_GameControllerRumble_fake.arg3_val);
}

TEST_F(ControllerTest, SetPlayerIndex)
{
  m_handle.set_player_index(7);
  EXPECT_EQ(1, SDL_GameControllerSetPlayerIndex_fake.call_count);
  EXPECT_EQ(7, SDL_GameControllerSetPlayerIndex_fake.arg1_val);
}

TEST_F(ControllerTest, Product)
{
  std::array<Uint16, 2> values{0, 3};
  SET_RETURN_SEQ(SDL_GameControllerGetProduct, values.data(), values.size());

  EXPECT_FALSE(m_handle.product().has_value());
  EXPECT_EQ(3, m_handle.product().value());
}

TEST_F(ControllerTest, Vendor)
{
  std::array<Uint16, 2> values{0, 7};
  SET_RETURN_SEQ(SDL_GameControllerGetVendor, values.data(), values.size());

  EXPECT_FALSE(m_handle.vendor().has_value());
  EXPECT_EQ(7, m_handle.vendor().value());
}

TEST_F(ControllerTest, Update)
{
  cen::controller::update();
  EXPECT_EQ(1, SDL_GameControllerUpdate_fake.call_count);
}

TEST_F(ControllerTest, IsSupported)
{
  const auto supported = cen::controller::is_supported(0);
  EXPECT_EQ(1, SDL_IsGameController_fake.call_count);
}