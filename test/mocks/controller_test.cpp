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
FAKE_VALUE_FUNC(SDL_GameControllerType, SDL_GameControllerTypeForIndex, int)

FAKE_VALUE_FUNC(Uint8, SDL_GameControllerGetButton, SDL_GameController*, SDL_GameControllerButton)
FAKE_VALUE_FUNC(const char*, SDL_GameControllerName, SDL_GameController*)

FAKE_VALUE_FUNC(SDL_GameControllerAxis, SDL_GameControllerGetAxisFromString, const char*)
FAKE_VALUE_FUNC(Sint16, SDL_GameControllerGetAxis, SDL_GameController*, SDL_GameControllerAxis)

FAKE_VALUE_FUNC(SDL_GameControllerButton, SDL_GameControllerGetButtonFromString, const char*)

FAKE_VALUE_FUNC(const char*, SDL_GameControllerGetStringForAxis, SDL_GameControllerAxis)
FAKE_VALUE_FUNC(const char*, SDL_GameControllerGetStringForButton, SDL_GameControllerButton)

FAKE_VALUE_FUNC(SDL_GameControllerButtonBind, SDL_GameControllerGetBindForAxis, SDL_GameController*, SDL_GameControllerAxis)
FAKE_VALUE_FUNC(SDL_GameControllerButtonBind, SDL_GameControllerGetBindForButton, SDL_GameController*, SDL_GameControllerButton)

FAKE_VALUE_FUNC(SDL_Joystick*, SDL_GameControllerGetJoystick, SDL_GameController*)

FAKE_VALUE_FUNC(int, SDL_GameControllerAddMapping, const char*)
FAKE_VALUE_FUNC(int, SDL_GameControllerAddMappingsFromRW, SDL_RWops*, int)

FAKE_VALUE_FUNC(char*, SDL_GameControllerMapping, SDL_GameController*)
FAKE_VALUE_FUNC(char*, SDL_GameControllerMappingForDeviceIndex, int)
FAKE_VALUE_FUNC(char*, SDL_GameControllerMappingForGUID, SDL_JoystickGUID)
FAKE_VALUE_FUNC(char*, SDL_GameControllerMappingForIndex, int)

FAKE_VALUE_FUNC(int, SDL_GameControllerEventState, int)

FAKE_VALUE_FUNC(SDL_RWops*, SDL_RWFromFile, const char*, const char*)

FAKE_VALUE_FUNC(const char*, SDL_GetError)
FAKE_VOID_FUNC(SDL_free, void*)

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
    RESET_FAKE(SDL_GameControllerTypeForIndex);

    RESET_FAKE(SDL_GameControllerGetButton);
    RESET_FAKE(SDL_GameControllerName);

    RESET_FAKE(SDL_GameControllerGetAxis);
    RESET_FAKE(SDL_GameControllerGetAxisFromString);

    RESET_FAKE(SDL_GameControllerGetButtonFromString);

    RESET_FAKE(SDL_GameControllerGetStringForAxis);
    RESET_FAKE(SDL_GameControllerGetStringForButton);

    RESET_FAKE(SDL_GameControllerGetBindForAxis);
    RESET_FAKE(SDL_GameControllerGetBindForButton);

    RESET_FAKE(SDL_GameControllerGetJoystick);

    RESET_FAKE(SDL_GameControllerAddMapping);
    RESET_FAKE(SDL_GameControllerAddMappingsFromRW);

    RESET_FAKE(SDL_GameControllerMapping);
    RESET_FAKE(SDL_GameControllerMappingForDeviceIndex);
    RESET_FAKE(SDL_GameControllerMappingForGUID);
    RESET_FAKE(SDL_GameControllerMappingForIndex);

    RESET_FAKE(SDL_GameControllerEventState);

    RESET_FAKE(SDL_RWFromFile);

    RESET_FAKE(SDL_GetError);
    RESET_FAKE(SDL_free);
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

TEST_F(ControllerTest, TypeWithIndex)
{
  std::array<SDL_GameControllerType, 2> values{SDL_CONTROLLER_TYPE_UNKNOWN,
                                               SDL_CONTROLLER_TYPE_XBOXONE};
  SET_RETURN_SEQ(SDL_GameControllerTypeForIndex, values.data(), values.size());

  EXPECT_EQ(cen::controller_type::unknown, cen::controller::type(0));
  EXPECT_EQ(cen::controller_type::xbox_one, cen::controller::type(0));
}

TEST_F(ControllerTest, GetState)
{
  std::array<Uint8, 2> values{SDL_RELEASED, SDL_PRESSED};
  SET_RETURN_SEQ(SDL_GameControllerGetButton, values.data(), values.size());

  EXPECT_EQ(cen::button_state::released,
            m_handle.get_state(cen::controller_button::a));
  EXPECT_EQ(cen::button_state::pressed,
            m_handle.get_state(cen::controller_button::a));
}

TEST_F(ControllerTest, IsPressed)
{
  std::array<Uint8, 2> values{SDL_RELEASED, SDL_PRESSED};
  SET_RETURN_SEQ(SDL_GameControllerGetButton, values.data(), values.size());

  EXPECT_FALSE(m_handle.is_pressed(cen::controller_button::a));
  EXPECT_TRUE(m_handle.is_pressed(cen::controller_button::a));
}

TEST_F(ControllerTest, IsReleased)
{
  std::array<Uint8, 2> values{SDL_RELEASED, SDL_PRESSED};
  SET_RETURN_SEQ(SDL_GameControllerGetButton, values.data(), values.size());

  EXPECT_TRUE(m_handle.is_released(cen::controller_button::a));
  EXPECT_FALSE(m_handle.is_released(cen::controller_button::a));
}

TEST_F(ControllerTest, GetAxisFromString)
{
  std::array<SDL_GameControllerAxis, 2> values{SDL_CONTROLLER_AXIS_INVALID,
                                               SDL_CONTROLLER_AXIS_RIGHTX};
  SET_RETURN_SEQ(SDL_GameControllerGetAxisFromString,
                 values.data(),
                 values.size());

  EXPECT_EQ(cen::controller_axis::invalid, cen::controller::get_axis(""));
  EXPECT_EQ(cen::controller_axis::right_x, cen::controller::get_axis(""));
}

TEST_F(ControllerTest, GetAxis)
{
  std::array<Sint16, 2> values{123, 321};
  SET_RETURN_SEQ(SDL_GameControllerGetAxis, values.data(), values.size());

  EXPECT_EQ(123, m_handle.get_axis(cen::controller_axis::left_x));
  EXPECT_EQ(321, m_handle.get_axis(cen::controller_axis::left_x));
}

TEST_F(ControllerTest, GetJoystick)
{
  EXPECT_NO_THROW(m_handle.get_joystick());
}

TEST_F(ControllerTest, AddMapping)
{
  std::array<int, 3> values{1, 0, -1};
  SET_RETURN_SEQ(SDL_GameControllerAddMapping, values.data(), values.size());

  EXPECT_TRUE(m_handle.add_mapping("foo"));
  EXPECT_FALSE(m_handle.add_mapping("foo"));

  SDL_GetError_fake.return_val = "";
  EXPECT_THROW(m_handle.add_mapping("foo"), cen::sdl_error);
}

TEST_F(ControllerTest, LoadMappings)
{
  std::array<int, 3> values{-1, 7};
  SET_RETURN_SEQ(SDL_GameControllerAddMappingsFromRW,
                 values.data(),
                 values.size());

  SDL_GetError_fake.return_val = "";
  EXPECT_THROW(cen::controller::load_mappings("foo"), cen::sdl_error);
  EXPECT_EQ(7, cen::controller::load_mappings("foo"));
}

TEST_F(ControllerTest, Mapping)
{
  EXPECT_EQ(nullptr, m_handle.mapping().get());
}

TEST_F(ControllerTest, MappingJoystickIndex)
{
  EXPECT_EQ(nullptr, m_handle.mapping(0).get());
}

TEST_F(ControllerTest, MappingJoystickGUID)
{
  SDL_JoystickGUID id{};
  EXPECT_EQ(nullptr, m_handle.mapping(id).get());
}

TEST_F(ControllerTest, MappingByIndex)
{
  EXPECT_EQ(nullptr, m_handle.mapping_by_index(0).get());
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

TEST_F(ControllerTest, StringifyWithButton)
{
  std::array<const char*, 2> values{nullptr, "foo"};
  SET_RETURN_SEQ(SDL_GameControllerGetStringForButton,
                 values.data(),
                 values.size());

  EXPECT_EQ(nullptr, cen::controller::stringify(cen::controller_button::x));
  EXPECT_STREQ("foo", cen::controller::stringify(cen::controller_button::x));
}

TEST_F(ControllerTest, GetBindingWithAxis)
{
  SDL_GameControllerButtonBind first{};
  first.bindType = SDL_CONTROLLER_BINDTYPE_NONE;

  SDL_GameControllerButtonBind second{};
  second.bindType = SDL_CONTROLLER_BINDTYPE_AXIS;

  std::array<SDL_GameControllerButtonBind, 2> values{first, second};
  SET_RETURN_SEQ(SDL_GameControllerGetBindForAxis,
                 values.data(),
                 values.size());

  EXPECT_FALSE(m_handle.get_binding(cen::controller_axis::right_x).has_value());
  EXPECT_TRUE(m_handle.get_binding(cen::controller_axis::right_x).has_value());
}

TEST_F(ControllerTest, GetBindingWithButton)
{
  SDL_GameControllerButtonBind first{};
  first.bindType = SDL_CONTROLLER_BINDTYPE_NONE;

  SDL_GameControllerButtonBind second{};
  second.bindType = SDL_CONTROLLER_BINDTYPE_AXIS;

  std::array<SDL_GameControllerButtonBind, 2> values{first, second};
  SET_RETURN_SEQ(SDL_GameControllerGetBindForButton,
                 values.data(),
                 values.size());

  EXPECT_FALSE(m_handle.get_binding(cen::controller_button::x).has_value());
  EXPECT_TRUE(m_handle.get_binding(cen::controller_button::x).has_value());
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

TEST_F(ControllerTest, SetPolling)
{
  cen::controller::set_polling(true);
  EXPECT_EQ(1, SDL_GameControllerEventState_fake.call_count);
  EXPECT_EQ(SDL_TRUE, SDL_GameControllerEventState_fake.arg0_val);

  cen::controller::set_polling(false);
  EXPECT_EQ(2, SDL_GameControllerEventState_fake.call_count);
  EXPECT_EQ(SDL_FALSE, SDL_GameControllerEventState_fake.arg0_val);
}

TEST_F(ControllerTest, IsPolling)
{
  std::array<int, 2> values{SDL_FALSE, SDL_TRUE};
  SET_RETURN_SEQ(SDL_GameControllerEventState, values.data(), values.size());

  EXPECT_FALSE(cen::controller::is_polling());
  EXPECT_EQ(SDL_QUERY, SDL_GameControllerEventState_fake.arg0_val);

  EXPECT_TRUE(cen::controller::is_polling());
  EXPECT_EQ(SDL_QUERY, SDL_GameControllerEventState_fake.arg0_val);
}