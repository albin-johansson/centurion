#include "input/controller.hpp"

#include <fff.h>
#include <gtest/gtest.h>

#include <array>  // array

#include "core/exception.hpp"
#include "core/integers.hpp"
#include "core_mocks.hpp"
#include "video/colors.hpp"

using namespace cen::literals;

// clang-format off
extern "C" {
FAKE_VOID_FUNC(SDL_GameControllerUpdate)
FAKE_VOID_FUNC(SDL_GameControllerSetPlayerIndex, SDL_GameController*, int)

FAKE_VALUE_FUNC(Uint16, SDL_GameControllerGetProduct, SDL_GameController*)
FAKE_VALUE_FUNC(Uint16, SDL_GameControllerGetVendor, SDL_GameController*)
FAKE_VALUE_FUNC(Uint16, SDL_GameControllerGetProductVersion, SDL_GameController*)
FAKE_VALUE_FUNC(const char*, SDL_GameControllerGetSerial, SDL_GameController*)

FAKE_VALUE_FUNC(int, SDL_GameControllerGetPlayerIndex, SDL_GameController*)
FAKE_VALUE_FUNC(int, SDL_GameControllerRumble, SDL_GameController*, Uint16, Uint16, Uint32)
FAKE_VALUE_FUNC(int, SDL_GameControllerRumbleTriggers, SDL_GameController*, Uint16, Uint16, Uint32)

FAKE_VALUE_FUNC(SDL_bool, SDL_GameControllerGetAttached, SDL_GameController*)
FAKE_VALUE_FUNC(SDL_bool, SDL_IsGameController, int)

#if SDL_VERSION_ATLEAST(2, 0, 12)
FAKE_VALUE_FUNC(SDL_GameControllerType, SDL_GameControllerGetType, SDL_GameController*)
FAKE_VALUE_FUNC(SDL_GameControllerType, SDL_GameControllerTypeForIndex, int)
#endif // SDL_VERSION_ATLEAST(2, 0, 12)

FAKE_VALUE_FUNC(Uint8, SDL_GameControllerGetButton, SDL_GameController*, SDL_GameControllerButton)
FAKE_VALUE_FUNC(const char*, SDL_GameControllerName, SDL_GameController*)

FAKE_VALUE_FUNC(SDL_GameControllerAxis, SDL_GameControllerGetAxisFromString, const char*)
FAKE_VALUE_FUNC(Sint16, SDL_GameControllerGetAxis, SDL_GameController*, SDL_GameControllerAxis)
FAKE_VALUE_FUNC(SDL_bool, SDL_GameControllerHasAxis, SDL_GameController*, SDL_GameControllerAxis)
FAKE_VALUE_FUNC(SDL_bool, SDL_GameControllerHasButton, SDL_GameController*, SDL_GameControllerButton)

FAKE_VALUE_FUNC(SDL_GameControllerButton, SDL_GameControllerGetButtonFromString, const char*)

FAKE_VALUE_FUNC(const char*, SDL_GameControllerGetStringForAxis, SDL_GameControllerAxis)
FAKE_VALUE_FUNC(const char*, SDL_GameControllerGetStringForButton, SDL_GameControllerButton)

FAKE_VALUE_FUNC(SDL_GameControllerButtonBind, SDL_GameControllerGetBindForAxis, SDL_GameController*, SDL_GameControllerAxis)
FAKE_VALUE_FUNC(SDL_GameControllerButtonBind, SDL_GameControllerGetBindForButton, SDL_GameController*, SDL_GameControllerButton)

FAKE_VALUE_FUNC(SDL_Joystick*, SDL_GameControllerGetJoystick, SDL_GameController*)
FAKE_VALUE_FUNC(int, SDL_GameControllerGetNumTouchpads, SDL_GameController*)
FAKE_VALUE_FUNC(int, SDL_GameControllerGetNumTouchpadFingers, SDL_GameController*, int)
FAKE_VALUE_FUNC(int, SDL_GameControllerGetTouchpadFinger, SDL_GameController*, int, int, Uint8*, float*, float*, float*)

FAKE_VALUE_FUNC(int, SDL_GameControllerAddMapping, const char*)
FAKE_VALUE_FUNC(int, SDL_GameControllerAddMappingsFromRW, SDL_RWops*, int)

FAKE_VALUE_FUNC(char*, SDL_GameControllerMapping, SDL_GameController*)
FAKE_VALUE_FUNC(char*, SDL_GameControllerMappingForDeviceIndex, int)
FAKE_VALUE_FUNC(char*, SDL_GameControllerMappingForGUID, SDL_JoystickGUID)
FAKE_VALUE_FUNC(char*, SDL_GameControllerMappingForIndex, int)

FAKE_VALUE_FUNC(int, SDL_GameControllerEventState, int)
FAKE_VALUE_FUNC(int, SDL_GameControllerSetSensorEnabled, SDL_GameController*, SDL_SensorType, SDL_bool)
FAKE_VALUE_FUNC(SDL_bool, SDL_GameControllerHasSensor, SDL_GameController*, SDL_SensorType)
FAKE_VALUE_FUNC(SDL_bool, SDL_GameControllerIsSensorEnabled, SDL_GameController*, SDL_SensorType)
FAKE_VALUE_FUNC(int, SDL_GameControllerGetSensorData, SDL_GameController*, SDL_SensorType, float*, int)
FAKE_VALUE_FUNC(int, SDL_GameControllerSetLED, SDL_GameController*, Uint8, Uint8, Uint8)
FAKE_VALUE_FUNC(SDL_bool, SDL_GameControllerHasLED, SDL_GameController*)
}
// clang-format on

class ControllerTest : public testing::Test
{
 protected:
  void SetUp() override
  {
    mocks::reset_core();

    RESET_FAKE(SDL_GameControllerUpdate);
    RESET_FAKE(SDL_GameControllerSetPlayerIndex);
    RESET_FAKE(SDL_GameControllerGetProduct);
    RESET_FAKE(SDL_GameControllerGetVendor);
    RESET_FAKE(SDL_GameControllerGetProductVersion);
    RESET_FAKE(SDL_GameControllerGetSerial);
    RESET_FAKE(SDL_GameControllerGetPlayerIndex);
    RESET_FAKE(SDL_GameControllerRumble);
    RESET_FAKE(SDL_GameControllerRumbleTriggers);
    RESET_FAKE(SDL_GameControllerGetAttached);
    RESET_FAKE(SDL_IsGameController);
    RESET_FAKE(SDL_GameControllerGetButton);
    RESET_FAKE(SDL_GameControllerName);
    RESET_FAKE(SDL_GameControllerGetAxis);
    RESET_FAKE(SDL_GameControllerHasAxis);
    RESET_FAKE(SDL_GameControllerHasButton);
    RESET_FAKE(SDL_GameControllerGetAxisFromString);
    RESET_FAKE(SDL_GameControllerGetButtonFromString);
    RESET_FAKE(SDL_GameControllerGetStringForAxis);
    RESET_FAKE(SDL_GameControllerGetStringForButton);
    RESET_FAKE(SDL_GameControllerGetBindForAxis);
    RESET_FAKE(SDL_GameControllerGetBindForButton);
    RESET_FAKE(SDL_GameControllerGetJoystick);
    RESET_FAKE(SDL_GameControllerGetNumTouchpads);
    RESET_FAKE(SDL_GameControllerGetNumTouchpadFingers);
    RESET_FAKE(SDL_GameControllerGetTouchpadFinger);
    RESET_FAKE(SDL_GameControllerAddMapping);
    RESET_FAKE(SDL_GameControllerAddMappingsFromRW);
    RESET_FAKE(SDL_GameControllerMapping);
    RESET_FAKE(SDL_GameControllerMappingForDeviceIndex);
    RESET_FAKE(SDL_GameControllerMappingForGUID);
    RESET_FAKE(SDL_GameControllerMappingForIndex);
    RESET_FAKE(SDL_GameControllerEventState);
    RESET_FAKE(SDL_GameControllerSetSensorEnabled);
    RESET_FAKE(SDL_GameControllerHasSensor);
    RESET_FAKE(SDL_GameControllerIsSensorEnabled);
    RESET_FAKE(SDL_GameControllerGetSensorData);
    RESET_FAKE(SDL_GameControllerSetLED);
    RESET_FAKE(SDL_GameControllerHasLED);

#if SDL_VERSION_ATLEAST(2, 0, 12)
    RESET_FAKE(SDL_GameControllerGetType);
    RESET_FAKE(SDL_GameControllerTypeForIndex);
#endif  // SDL_VERSION_ATLEAST(2, 0, 12)
  }

  /**
   * We use a `controller_handle` because it doesn't throw when the pointer is
   * null, this doesn't matter that much since they share implementations of all
   * relevant functions.
   */
  cen::controller_handle m_controller{nullptr};
};

using namespace cen::literals;

TEST_F(ControllerTest, Rumble)
{
  m_controller.rumble(0, 10, 1_ms);
  ASSERT_EQ(1, SDL_GameControllerRumble_fake.call_count);
}

TEST_F(ControllerTest, StopRumble)
{
  m_controller.stop_rumble();
  ASSERT_EQ(0, SDL_GameControllerRumble_fake.arg1_val);
  ASSERT_EQ(0, SDL_GameControllerRumble_fake.arg2_val);
  ASSERT_EQ(0, SDL_GameControllerRumble_fake.arg3_val);
}

TEST_F(ControllerTest, Product)
{
  std::array values{0_u16, 3_u16};
  SET_RETURN_SEQ(SDL_GameControllerGetProduct, values.data(), cen::isize(values));

  ASSERT_FALSE(m_controller.product().has_value());
  ASSERT_EQ(3, m_controller.product().value());
}

TEST_F(ControllerTest, Vendor)
{
  std::array values{0_u16, 7_u16};
  SET_RETURN_SEQ(SDL_GameControllerGetVendor, values.data(), cen::isize(values));

  ASSERT_FALSE(m_controller.vendor().has_value());
  ASSERT_EQ(7, m_controller.vendor().value());
}

TEST_F(ControllerTest, ProductVersion)
{
  std::array values{0_u16, 4_u16};
  SET_RETURN_SEQ(SDL_GameControllerGetProductVersion, values.data(), cen::isize(values));

  ASSERT_FALSE(m_controller.product_version().has_value());
  ASSERT_EQ(4, m_controller.product_version().value());
}

TEST_F(ControllerTest, Index)
{
  std::array values{-1, 6};
  SET_RETURN_SEQ(SDL_GameControllerGetPlayerIndex, values.data(), cen::isize(values));

  ASSERT_FALSE(m_controller.index().has_value());
  ASSERT_EQ(6, m_controller.index().value());
}

TEST_F(ControllerTest, IsConnected)
{
  std::array values{SDL_FALSE, SDL_TRUE};
  SET_RETURN_SEQ(SDL_GameControllerGetAttached, values.data(), cen::isize(values));

  ASSERT_FALSE(m_controller.is_connected());
  ASSERT_TRUE(m_controller.is_connected());
}

TEST_F(ControllerTest, Name)
{
  std::array<cen::czstring, 2> values{nullptr, "foobar"};
  SET_RETURN_SEQ(SDL_GameControllerName, values.data(), cen::isize(values));

  ASSERT_EQ(nullptr, m_controller.name());
  ASSERT_STREQ("foobar", m_controller.name());
}

TEST_F(ControllerTest, GetState)
{
  std::array<Uint8, 2> values{SDL_RELEASED, SDL_PRESSED};
  SET_RETURN_SEQ(SDL_GameControllerGetButton, values.data(), cen::isize(values));

  ASSERT_EQ(cen::button_state::released,
            m_controller.get_state(cen::controller_button::a));
  ASSERT_EQ(cen::button_state::pressed,
            m_controller.get_state(cen::controller_button::a));
}

TEST_F(ControllerTest, IsPressed)
{
  std::array<Uint8, 2> values{SDL_RELEASED, SDL_PRESSED};
  SET_RETURN_SEQ(SDL_GameControllerGetButton, values.data(), cen::isize(values));

  ASSERT_FALSE(m_controller.is_pressed(cen::controller_button::a));
  ASSERT_TRUE(m_controller.is_pressed(cen::controller_button::a));
}

TEST_F(ControllerTest, IsReleased)
{
  std::array<Uint8, 2> values{SDL_RELEASED, SDL_PRESSED};
  SET_RETURN_SEQ(SDL_GameControllerGetButton, values.data(), cen::isize(values));

  ASSERT_TRUE(m_controller.is_released(cen::controller_button::a));
  ASSERT_FALSE(m_controller.is_released(cen::controller_button::a));
}

TEST_F(ControllerTest, GetAxisFromString)
{
  std::array values{SDL_CONTROLLER_AXIS_INVALID, SDL_CONTROLLER_AXIS_RIGHTX};
  SET_RETURN_SEQ(SDL_GameControllerGetAxisFromString, values.data(), cen::isize(values));

  ASSERT_EQ(cen::controller_axis::invalid, cen::controller::get_axis(""));
  ASSERT_EQ(cen::controller_axis::right_x, cen::controller::get_axis(""));

  using namespace std::string_literals;
  ASSERT_EQ(cen::controller_axis::right_x, cen::controller::get_axis(""s));
}

TEST_F(ControllerTest, GetAxis)
{
  std::array values{123_i16, 321_i16};
  SET_RETURN_SEQ(SDL_GameControllerGetAxis, values.data(), cen::isize(values));

  ASSERT_EQ(123, m_controller.get_axis(cen::controller_axis::left_x));
  ASSERT_EQ(321, m_controller.get_axis(cen::controller_axis::left_x));
}

TEST_F(ControllerTest, GetJoystick)
{
  ASSERT_NO_THROW(m_controller.get_joystick());
}

TEST_F(ControllerTest, AddMapping)
{
  std::array values{1, 0, -1};
  SET_RETURN_SEQ(SDL_GameControllerAddMapping, values.data(), cen::isize(values));

  ASSERT_EQ(cen::controller_handle::mapping_result::added,
            m_controller.add_mapping("foo"));

  ASSERT_EQ(cen::controller_handle::mapping_result::updated,
            m_controller.add_mapping("foo"));

  ASSERT_EQ(cen::controller_handle::mapping_result::error,
            m_controller.add_mapping("foo"));

  using namespace std::string_literals;
  ASSERT_EQ(cen::controller_handle::mapping_result::error,
            m_controller.add_mapping("foo"s));
}

TEST_F(ControllerTest, LoadMappings)
{
  std::array values{-1, 7};
  SET_RETURN_SEQ(SDL_GameControllerAddMappingsFromRW, values.data(), cen::isize(values));

  ASSERT_FALSE(cen::controller::load_mappings("foo").has_value());
  ASSERT_EQ(7, cen::controller::load_mappings("foo"));

  using namespace std::string_literals;
  ASSERT_EQ(7, cen::controller::load_mappings("foo"s));
}

TEST_F(ControllerTest, Mapping)
{
  ASSERT_EQ(nullptr, m_controller.mapping().get());
}

TEST_F(ControllerTest, MappingJoystickIndex)
{
  ASSERT_EQ(nullptr, m_controller.mapping(0).get());
}

TEST_F(ControllerTest, MappingJoystickGUID)
{
  SDL_JoystickGUID id{};
  ASSERT_EQ(nullptr, m_controller.mapping(id).get());
}

TEST_F(ControllerTest, MappingByIndex)
{
  ASSERT_EQ(nullptr, m_controller.mapping_by_index(0).get());
}

TEST_F(ControllerTest, GetButton)
{
  std::array values{SDL_CONTROLLER_BUTTON_INVALID, SDL_CONTROLLER_BUTTON_B};
  SET_RETURN_SEQ(SDL_GameControllerGetButtonFromString,
                 values.data(),
                 cen::isize(values));

  ASSERT_EQ(cen::controller_button::invalid, cen::controller::get_button(""));
  ASSERT_EQ(cen::controller_button::b, cen::controller::get_button(""));

  using namespace std::string_literals;
  ASSERT_EQ(cen::controller_button::b, cen::controller::get_button(""s));
}

TEST_F(ControllerTest, StringifyWithAxis)
{
  std::array<const char*, 2> values{nullptr, "foo"};
  SET_RETURN_SEQ(SDL_GameControllerGetStringForAxis, values.data(), cen::isize(values));

  ASSERT_EQ(nullptr, cen::controller::stringify(cen::controller_axis::left_y));
  ASSERT_STREQ("foo", cen::controller::stringify(cen::controller_axis::left_y));
}

TEST_F(ControllerTest, StringifyWithButton)
{
  std::array<const char*, 2> values{nullptr, "foo"};
  SET_RETURN_SEQ(SDL_GameControllerGetStringForButton, values.data(), cen::isize(values));

  ASSERT_EQ(nullptr, cen::controller::stringify(cen::controller_button::x));
  ASSERT_STREQ("foo", cen::controller::stringify(cen::controller_button::x));
}

TEST_F(ControllerTest, GetBindingWithAxis)
{
  SDL_GameControllerButtonBind first{};
  first.bindType = SDL_CONTROLLER_BINDTYPE_NONE;

  SDL_GameControllerButtonBind second{};
  second.bindType = SDL_CONTROLLER_BINDTYPE_AXIS;

  std::array values{first, second};
  SET_RETURN_SEQ(SDL_GameControllerGetBindForAxis, values.data(), cen::isize(values));

  ASSERT_FALSE(m_controller.get_binding(cen::controller_axis::right_x).has_value());
  ASSERT_TRUE(m_controller.get_binding(cen::controller_axis::right_x).has_value());
}

TEST_F(ControllerTest, GetBindingWithButton)
{
  SDL_GameControllerButtonBind first{};
  first.bindType = SDL_CONTROLLER_BINDTYPE_NONE;

  SDL_GameControllerButtonBind second{};
  second.bindType = SDL_CONTROLLER_BINDTYPE_AXIS;

  std::array values{first, second};
  SET_RETURN_SEQ(SDL_GameControllerGetBindForButton, values.data(), cen::isize(values));

  ASSERT_FALSE(m_controller.get_binding(cen::controller_button::x).has_value());
  ASSERT_TRUE(m_controller.get_binding(cen::controller_button::x).has_value());
}

TEST_F(ControllerTest, Update)
{
  cen::controller::update();
  ASSERT_EQ(1, SDL_GameControllerUpdate_fake.call_count);
}

TEST_F(ControllerTest, IsSupported)
{
  const auto supported = cen::controller::is_supported(0);
  ASSERT_EQ(1, SDL_IsGameController_fake.call_count);
}

TEST_F(ControllerTest, SetPolling)
{
  cen::controller::set_polling(true);
  ASSERT_EQ(1, SDL_GameControllerEventState_fake.call_count);
  ASSERT_EQ(SDL_TRUE, SDL_GameControllerEventState_fake.arg0_val);

  cen::controller::set_polling(false);
  ASSERT_EQ(2, SDL_GameControllerEventState_fake.call_count);
  ASSERT_EQ(SDL_FALSE, SDL_GameControllerEventState_fake.arg0_val);
}

TEST_F(ControllerTest, IsPolling)
{
  std::array<int, 2> values{SDL_FALSE, SDL_TRUE};
  SET_RETURN_SEQ(SDL_GameControllerEventState, values.data(), cen::isize(values));

  ASSERT_FALSE(cen::controller::is_polling());
  ASSERT_EQ(SDL_QUERY, SDL_GameControllerEventState_fake.arg0_val);

  ASSERT_TRUE(cen::controller::is_polling());
  ASSERT_EQ(SDL_QUERY, SDL_GameControllerEventState_fake.arg0_val);
}

#if SDL_VERSION_ATLEAST(2, 0, 12)

TEST_F(ControllerTest, SetPlayerIndex)
{
  m_controller.set_player_index(7);
  ASSERT_EQ(1, SDL_GameControllerSetPlayerIndex_fake.call_count);
  ASSERT_EQ(7, SDL_GameControllerSetPlayerIndex_fake.arg1_val);
}

TEST_F(ControllerTest, Type)
{
  std::array values{SDL_CONTROLLER_TYPE_UNKNOWN,
                    SDL_CONTROLLER_TYPE_XBOX360,
                    SDL_CONTROLLER_TYPE_PS4};
  SET_RETURN_SEQ(SDL_GameControllerGetType, values.data(), cen::isize(values));

  ASSERT_EQ(cen::controller_type::unknown, m_controller.type());
  ASSERT_EQ(cen::controller_type::xbox_360, m_controller.type());
  ASSERT_EQ(cen::controller_type::ps4, m_controller.type());
}

TEST_F(ControllerTest, TypeWithIndex)
{
  std::array values{SDL_CONTROLLER_TYPE_UNKNOWN, SDL_CONTROLLER_TYPE_XBOXONE};
  SET_RETURN_SEQ(SDL_GameControllerTypeForIndex, values.data(), cen::isize(values));

  ASSERT_EQ(cen::controller_type::unknown, cen::controller::type(0));
  ASSERT_EQ(cen::controller_type::xbox_one, cen::controller::type(0));
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

#if SDL_VERSION_ATLEAST(2, 0, 14)

TEST_F(ControllerTest, RumbleTriggers)
{
  m_controller.rumble_triggers(0, 10, 1_ms);
  ASSERT_EQ(1, SDL_GameControllerRumbleTriggers_fake.call_count);
}

TEST_F(ControllerTest, Serial)
{
  const auto serial [[maybe_unused]] = m_controller.serial();
  ASSERT_EQ(1, SDL_GameControllerGetSerial_fake.call_count);
}

TEST_F(ControllerTest, HasAxis)
{
  std::array values{SDL_FALSE, SDL_TRUE};
  SET_RETURN_SEQ(SDL_GameControllerHasAxis, values.data(), cen::isize(values));

  ASSERT_FALSE(m_controller.has_axis(cen::controller_axis::left_x));
  ASSERT_TRUE(m_controller.has_axis(cen::controller_axis::left_x));
  ASSERT_EQ(2, SDL_GameControllerHasAxis_fake.call_count);
}

TEST_F(ControllerTest, HasButton)
{
  std::array values{SDL_FALSE, SDL_TRUE};
  SET_RETURN_SEQ(SDL_GameControllerHasButton, values.data(), cen::isize(values));

  ASSERT_FALSE(m_controller.has_button(cen::controller_button::x));
  ASSERT_TRUE(m_controller.has_button(cen::controller_button::x));
  ASSERT_EQ(2, SDL_GameControllerHasButton_fake.call_count);
}

TEST_F(ControllerTest, TouchpadCount)
{
  const auto count [[maybe_unused]] = m_controller.touchpad_count();
  ASSERT_EQ(1, SDL_GameControllerGetNumTouchpads_fake.call_count);
}

TEST_F(ControllerTest, TouchpadFingerCapacity)
{
  const auto capacity [[maybe_unused]] = m_controller.touchpad_finger_capacity(0);
  ASSERT_EQ(1, SDL_GameControllerGetNumTouchpadFingers_fake.call_count);
}

TEST_F(ControllerTest, TouchpadFingerState)
{
  std::array values{-1, 0};
  SET_RETURN_SEQ(SDL_GameControllerGetTouchpadFinger, values.data(), cen::isize(values));

  ASSERT_FALSE(m_controller.touchpad_finger_state(0, 0));
  ASSERT_TRUE(m_controller.touchpad_finger_state(0, 0));
  ASSERT_EQ(2, SDL_GameControllerGetTouchpadFinger_fake.call_count);
}

TEST_F(ControllerTest, SetSensorEnabled)
{
  std::array values{-1, 0};
  SET_RETURN_SEQ(SDL_GameControllerSetSensorEnabled, values.data(), cen::isize(values));

  const auto type = cen::sensor_type::gyroscope;
  ASSERT_FALSE(m_controller.set_sensor_enabled(type, true));
  ASSERT_TRUE(m_controller.set_sensor_enabled(type, true));
  ASSERT_EQ(2, SDL_GameControllerSetSensorEnabled_fake.call_count);
}

TEST_F(ControllerTest, HasSensor)
{
  std::array values{SDL_FALSE, SDL_TRUE};
  SET_RETURN_SEQ(SDL_GameControllerHasSensor, values.data(), cen::isize(values));

  ASSERT_FALSE(m_controller.has_sensor(cen::sensor_type::gyroscope));
  ASSERT_TRUE(m_controller.has_sensor(cen::sensor_type::gyroscope));
  ASSERT_EQ(2, SDL_GameControllerHasSensor_fake.call_count);
}

TEST_F(ControllerTest, IsSensorEnabled)
{
  std::array values{SDL_FALSE, SDL_TRUE};
  SET_RETURN_SEQ(SDL_GameControllerIsSensorEnabled, values.data(), cen::isize(values));

  ASSERT_FALSE(m_controller.is_sensor_enabled(cen::sensor_type::gyroscope));
  ASSERT_TRUE(m_controller.is_sensor_enabled(cen::sensor_type::gyroscope));
  ASSERT_EQ(2, SDL_GameControllerIsSensorEnabled_fake.call_count);
}

TEST_F(ControllerTest, GetSensorData)
{
  std::array values{-1, 0};
  SET_RETURN_SEQ(SDL_GameControllerGetSensorData, values.data(), cen::isize(values));

  ASSERT_FALSE(m_controller.get_sensor_data<3>(cen::sensor_type::gyroscope));
  ASSERT_TRUE(m_controller.get_sensor_data<3>(cen::sensor_type::gyroscope));
  ASSERT_EQ(2, SDL_GameControllerGetSensorData_fake.call_count);
}

TEST_F(ControllerTest, SetLED)
{
  std::array values{-1, 0};
  SET_RETURN_SEQ(SDL_GameControllerSetLED, values.data(), cen::isize(values));

  ASSERT_FALSE(m_controller.set_led(cen::colors::red));
  ASSERT_TRUE(m_controller.set_led(cen::colors::red));
  ASSERT_EQ(2, SDL_GameControllerSetLED_fake.call_count);
}

TEST_F(ControllerTest, HasLED)
{
  std::array values{SDL_FALSE, SDL_TRUE};
  SET_RETURN_SEQ(SDL_GameControllerHasLED, values.data(), cen::isize(values));

  ASSERT_FALSE(m_controller.has_led());
  ASSERT_TRUE(m_controller.has_led());
  ASSERT_EQ(2, SDL_GameControllerHasLED_fake.call_count);
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)
