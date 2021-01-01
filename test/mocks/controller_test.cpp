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
FAKE_VALUE_FUNC(Uint16, SDL_GameControllerGetProductVersion, SDL_GameController*)

FAKE_VALUE_FUNC(int, SDL_GameControllerGetPlayerIndex, SDL_GameController*)
FAKE_VALUE_FUNC(int, SDL_GameControllerRumble, SDL_GameController*, Uint16, Uint16, Uint32)

FAKE_VALUE_FUNC(SDL_bool, SDL_GameControllerGetAttached, SDL_GameController*)
FAKE_VALUE_FUNC(SDL_bool, SDL_IsGameController, int)

FAKE_VALUE_FUNC(SDL_GameControllerType, SDL_GameControllerGetType, SDL_GameController*)
FAKE_VALUE_FUNC(const char*, SDL_GameControllerName, SDL_GameController*)

FAKE_VALUE_FUNC(SDL_GameControllerAxis, SDL_GameControllerGetAxisFromString, const char*)
FAKE_VALUE_FUNC(SDL_GameControllerButton, SDL_GameControllerGetButtonFromString, const char*)

FAKE_VALUE_FUNC(const char*, SDL_GameControllerGetStringForAxis, SDL_GameControllerAxis)
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
    RESET_FAKE(SDL_GameControllerGetProductVersion);

    RESET_FAKE(SDL_GameControllerGetPlayerIndex);
    RESET_FAKE(SDL_GameControllerRumble);

    RESET_FAKE(SDL_GameControllerGetAttached);
    RESET_FAKE(SDL_IsGameController);

    RESET_FAKE(SDL_GameControllerGetType);
    RESET_FAKE(SDL_GameControllerName);

    RESET_FAKE(SDL_GameControllerGetAxisFromString);
    RESET_FAKE(SDL_GameControllerGetButtonFromString);

    RESET_FAKE(SDL_GameControllerGetStringForAxis);
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

TEST_F(ControllerTest, ProductVersion)
{
  std::array<Uint16, 2> values{0, 4};
  SET_RETURN_SEQ(SDL_GameControllerGetProductVersion,
                 values.data(),
                 values.size());

  EXPECT_FALSE(m_handle.product_version().has_value());
  EXPECT_EQ(4, m_handle.product_version().value());
}

TEST_F(ControllerTest, Index)
{
  std::array<int, 2> values{-1, 6};
  SET_RETURN_SEQ(SDL_GameControllerGetPlayerIndex,
                 values.data(),
                 values.size());

  EXPECT_FALSE(m_handle.index().has_value());
  EXPECT_EQ(6, m_handle.index().value());
}

TEST_F(ControllerTest, IsConnected)
{
  std::array<SDL_bool, 2> values{SDL_FALSE, SDL_TRUE};
  SET_RETURN_SEQ(SDL_GameControllerGetAttached, values.data(), values.size());

  EXPECT_FALSE(m_handle.is_connected());
  EXPECT_TRUE(m_handle.is_connected());
}

TEST_F(ControllerTest, Name)
{
  std::array<cen::czstring, 2> values{nullptr, "foobar"};
  SET_RETURN_SEQ(SDL_GameControllerName, values.data(), values.size());

  EXPECT_EQ(nullptr, m_handle.name());
  EXPECT_STREQ("foobar", m_handle.name());
}

TEST_F(ControllerTest, Type)
{
  std::array<SDL_GameControllerType, 3> values{SDL_CONTROLLER_TYPE_UNKNOWN,
                                               SDL_CONTROLLER_TYPE_XBOX360,
                                               SDL_CONTROLLER_TYPE_PS4};
  SET_RETURN_SEQ(SDL_GameControllerGetType, values.data(), values.size());

  EXPECT_EQ(cen::controller_type::unknown, m_handle.type());
  EXPECT_EQ(cen::controller_type::xbox_360, m_handle.type());
  EXPECT_EQ(cen::controller_type::ps4, m_handle.type());
}

TEST_F(ControllerTest, GetAxis)
{
  std::array<SDL_GameControllerAxis, 2> values{SDL_CONTROLLER_AXIS_INVALID,
                                               SDL_CONTROLLER_AXIS_RIGHTX};
  SET_RETURN_SEQ(SDL_GameControllerGetAxisFromString,
                 values.data(),
                 values.size());

  EXPECT_EQ(cen::controller_axis::invalid, cen::controller::get_axis(""));
  EXPECT_EQ(cen::controller_axis::right_x, cen::controller::get_axis(""));
}

TEST_F(ControllerTest, GetButton)
{
  std::array<SDL_GameControllerButton, 2> values{SDL_CONTROLLER_BUTTON_INVALID,
                                                 SDL_CONTROLLER_BUTTON_B};
  SET_RETURN_SEQ(SDL_GameControllerGetButtonFromString,
                 values.data(),
                 values.size());

  EXPECT_EQ(cen::controller_button::invalid, cen::controller::get_button(""));
  EXPECT_EQ(cen::controller_button::b, cen::controller::get_button(""));
}

TEST_F(ControllerTest, StringifyWithAxis)
{
  std::array<const char*, 2> values{nullptr, "foo"};
  SET_RETURN_SEQ(SDL_GameControllerGetStringForAxis,
                 values.data(),
                 values.size());

  EXPECT_EQ(nullptr, cen::controller::stringify(cen::controller_axis::left_y));
  EXPECT_STREQ("foo", cen::controller::stringify(cen::controller_axis::left_y));
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