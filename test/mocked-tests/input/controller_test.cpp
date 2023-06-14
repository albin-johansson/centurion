/*
 * MIT License
 *
 * Copyright (c) 2019-2022 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "centurion/controller.hpp"

#include <fff.h>
#include <gtest/gtest.h>

#include <array>     // array
#include <iostream>  // cout

#include "centurion/video/color.hpp"
#include "core_mocks.hpp"

using namespace cen::literals;

extern "C" {
FAKE_VOID_FUNC(SDL_GameControllerUpdate)
FAKE_VOID_FUNC(SDL_GameControllerSetPlayerIndex, SDL_GameController*, int)

FAKE_VALUE_FUNC(Uint16, SDL_GameControllerGetProduct, SDL_GameController*)
FAKE_VALUE_FUNC(Uint16, SDL_GameControllerGetVendor, SDL_GameController*)
FAKE_VALUE_FUNC(Uint16, SDL_GameControllerGetProductVersion, SDL_GameController*)
FAKE_VALUE_FUNC(const char*, SDL_GameControllerGetSerial, SDL_GameController*)

FAKE_VALUE_FUNC(int, SDL_GameControllerGetPlayerIndex, SDL_GameController*)
FAKE_VALUE_FUNC(int, SDL_GameControllerRumble, SDL_GameController*, Uint16, Uint16, Uint32)
FAKE_VALUE_FUNC(int,
                SDL_GameControllerRumbleTriggers,
                SDL_GameController*,
                Uint16,
                Uint16,
                Uint32)

FAKE_VALUE_FUNC(SDL_bool, SDL_GameControllerGetAttached, SDL_GameController*)
FAKE_VALUE_FUNC(SDL_bool, SDL_IsGameController, int)

FAKE_VALUE_FUNC(Uint8,
                SDL_GameControllerGetButton,
                SDL_GameController*,
                SDL_GameControllerButton)
FAKE_VALUE_FUNC(const char*, SDL_GameControllerName, SDL_GameController*)

FAKE_VALUE_FUNC(SDL_GameControllerAxis, SDL_GameControllerGetAxisFromString, const char*)
FAKE_VALUE_FUNC(Sint16, SDL_GameControllerGetAxis, SDL_GameController*, SDL_GameControllerAxis)
FAKE_VALUE_FUNC(SDL_bool,
                SDL_GameControllerHasAxis,
                SDL_GameController*,
                SDL_GameControllerAxis)
FAKE_VALUE_FUNC(SDL_bool,
                SDL_GameControllerHasButton,
                SDL_GameController*,
                SDL_GameControllerButton)

FAKE_VALUE_FUNC(SDL_GameControllerButton, SDL_GameControllerGetButtonFromString, const char*)

FAKE_VALUE_FUNC(const char*, SDL_GameControllerGetStringForAxis, SDL_GameControllerAxis)
FAKE_VALUE_FUNC(const char*, SDL_GameControllerGetStringForButton, SDL_GameControllerButton)

FAKE_VALUE_FUNC(SDL_GameControllerButtonBind,
                SDL_GameControllerGetBindForAxis,
                SDL_GameController*,
                SDL_GameControllerAxis)
FAKE_VALUE_FUNC(SDL_GameControllerButtonBind,
                SDL_GameControllerGetBindForButton,
                SDL_GameController*,
                SDL_GameControllerButton)

FAKE_VALUE_FUNC(SDL_Joystick*, SDL_GameControllerGetJoystick, SDL_GameController*)
FAKE_VALUE_FUNC(int, SDL_GameControllerGetNumTouchpads, SDL_GameController*)
FAKE_VALUE_FUNC(int, SDL_GameControllerGetNumTouchpadFingers, SDL_GameController*, int)
FAKE_VALUE_FUNC(int,
                SDL_GameControllerGetTouchpadFinger,
                SDL_GameController*,
                int,
                int,
                Uint8*,
                float*,
                float*,
                float*)

FAKE_VALUE_FUNC(int, SDL_GameControllerAddMapping, const char*)
FAKE_VALUE_FUNC(int, SDL_GameControllerAddMappingsFromRW, SDL_RWops*, int)

FAKE_VALUE_FUNC(char*, SDL_GameControllerMapping, SDL_GameController*)
FAKE_VALUE_FUNC(char*, SDL_GameControllerMappingForDeviceIndex, int)
FAKE_VALUE_FUNC(char*, SDL_GameControllerMappingForGUID, SDL_JoystickGUID)
FAKE_VALUE_FUNC(char*, SDL_GameControllerMappingForIndex, int)

FAKE_VALUE_FUNC(int, SDL_GameControllerEventState, int)
FAKE_VALUE_FUNC(int,
                SDL_GameControllerSetSensorEnabled,
                SDL_GameController*,
                SDL_SensorType,
                SDL_bool)
FAKE_VALUE_FUNC(SDL_bool, SDL_GameControllerHasSensor, SDL_GameController*, SDL_SensorType)
FAKE_VALUE_FUNC(SDL_bool,
                SDL_GameControllerIsSensorEnabled,
                SDL_GameController*,
                SDL_SensorType)
FAKE_VALUE_FUNC(int,
                SDL_GameControllerGetSensorData,
                SDL_GameController*,
                SDL_SensorType,
                float*,
                int)
FAKE_VALUE_FUNC(int, SDL_GameControllerSetLED, SDL_GameController*, Uint8, Uint8, Uint8)
FAKE_VALUE_FUNC(SDL_bool, SDL_GameControllerHasLED, SDL_GameController*)

#if SDL_VERSION_ATLEAST(2, 0, 12)
FAKE_VALUE_FUNC(SDL_GameControllerType, SDL_GameControllerGetType, SDL_GameController*)
FAKE_VALUE_FUNC(SDL_GameControllerType, SDL_GameControllerTypeForIndex, int)
#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

#if SDL_VERSION_ATLEAST(2, 0, 16)
FAKE_VALUE_FUNC(float,
                SDL_GameControllerGetSensorDataRate,
                SDL_GameController*,
                SDL_SensorType)
FAKE_VALUE_FUNC(int, SDL_GameControllerSendEffect, SDL_GameController*, const void*, int)
#endif  // SDL_VERSION_ATLEAST(2, 0, 16)

#if SDL_VERSION_ATLEAST(2, 0, 18)
FAKE_VALUE_FUNC(SDL_bool, SDL_GameControllerHasRumble, SDL_GameController*)
FAKE_VALUE_FUNC(SDL_bool, SDL_GameControllerHasRumbleTriggers, SDL_GameController*)
FAKE_VALUE_FUNC(const char*,
                SDL_GameControllerGetAppleSFSymbolsNameForButton,
                SDL_GameController*,
                SDL_GameControllerButton)
FAKE_VALUE_FUNC(const char*,
                SDL_GameControllerGetAppleSFSymbolsNameForAxis,
                SDL_GameController*,
                SDL_GameControllerAxis)
#endif  // SDL_VERSION_ATLEAST(2, 0, 18)

#if SDL_VERSION_ATLEAST(2, 24, 0)
FAKE_VALUE_FUNC(const char*, SDL_GameControllerPath, SDL_GameController*)
FAKE_VALUE_FUNC(Uint16, SDL_GameControllerGetFirmwareVersion, SDL_GameController*)
#endif  // SDL_VERSION_ATLEAST(2, 24, 0)
}

class ControllerTest : public testing::Test {
 protected:
  void SetUp() override
  {
    mocks::reset_core();

    RESET_FAKE(SDL_GameControllerUpdate)
    RESET_FAKE(SDL_GameControllerSetPlayerIndex)
    RESET_FAKE(SDL_GameControllerGetProduct)
    RESET_FAKE(SDL_GameControllerGetVendor)
    RESET_FAKE(SDL_GameControllerGetProductVersion)
    RESET_FAKE(SDL_GameControllerGetSerial)
    RESET_FAKE(SDL_GameControllerGetPlayerIndex)
    RESET_FAKE(SDL_GameControllerRumble)
    RESET_FAKE(SDL_GameControllerRumbleTriggers)
    RESET_FAKE(SDL_GameControllerGetAttached)
    RESET_FAKE(SDL_IsGameController)
    RESET_FAKE(SDL_GameControllerGetButton)
    RESET_FAKE(SDL_GameControllerName)
    RESET_FAKE(SDL_GameControllerGetAxis)
    RESET_FAKE(SDL_GameControllerHasAxis)
    RESET_FAKE(SDL_GameControllerHasButton)
    RESET_FAKE(SDL_GameControllerGetAxisFromString)
    RESET_FAKE(SDL_GameControllerGetButtonFromString)
    RESET_FAKE(SDL_GameControllerGetStringForAxis)
    RESET_FAKE(SDL_GameControllerGetStringForButton)
    RESET_FAKE(SDL_GameControllerGetBindForAxis)
    RESET_FAKE(SDL_GameControllerGetBindForButton)
    RESET_FAKE(SDL_GameControllerGetJoystick)
    RESET_FAKE(SDL_GameControllerGetNumTouchpads)
    RESET_FAKE(SDL_GameControllerGetNumTouchpadFingers)
    RESET_FAKE(SDL_GameControllerGetTouchpadFinger)
    RESET_FAKE(SDL_GameControllerAddMapping)
    RESET_FAKE(SDL_GameControllerAddMappingsFromRW)
    RESET_FAKE(SDL_GameControllerMapping)
    RESET_FAKE(SDL_GameControllerMappingForDeviceIndex)
    RESET_FAKE(SDL_GameControllerMappingForGUID)
    RESET_FAKE(SDL_GameControllerMappingForIndex)
    RESET_FAKE(SDL_GameControllerEventState)
    RESET_FAKE(SDL_GameControllerSetSensorEnabled)
    RESET_FAKE(SDL_GameControllerHasSensor)
    RESET_FAKE(SDL_GameControllerIsSensorEnabled)
    RESET_FAKE(SDL_GameControllerGetSensorData)
    RESET_FAKE(SDL_GameControllerSetLED)
    RESET_FAKE(SDL_GameControllerHasLED)

#if SDL_VERSION_ATLEAST(2, 0, 12)
    RESET_FAKE(SDL_GameControllerGetType)
    RESET_FAKE(SDL_GameControllerTypeForIndex)
#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

#if SDL_VERSION_ATLEAST(2, 0, 16)
    RESET_FAKE(SDL_GameControllerGetSensorDataRate)
    RESET_FAKE(SDL_GameControllerSendEffect)
#endif  // SDL_VERSION_ATLEAST(2, 0, 16)

#if SDL_VERSION_ATLEAST(2, 0, 18)
    RESET_FAKE(SDL_GameControllerHasRumble)
    RESET_FAKE(SDL_GameControllerHasRumbleTriggers)
    RESET_FAKE(SDL_GameControllerGetAppleSFSymbolsNameForButton)
    RESET_FAKE(SDL_GameControllerGetAppleSFSymbolsNameForAxis)
#endif  // SDL_VERSION_ATLEAST(2, 0, 18)

#if SDL_VERSION_ATLEAST(2, 24, 0)
    RESET_FAKE(SDL_GameControllerPath)
    RESET_FAKE(SDL_GameControllerGetFirmwareVersion)
#endif  // SDL_VERSION_ATLEAST(2, 24, 0)
  }

  /**
   * We use a `controller_handle` because it doesn't throw when the pointer is
   * null, this doesn't matter that much since they share implementations of all
   * relevant functions.
   */
  cen::controller_handle controller {nullptr};
};

using namespace cen::literals;

TEST_F(ControllerTest, Rumble)
{
  controller.rumble(0, 10, 1_ms);
  ASSERT_EQ(1u, SDL_GameControllerRumble_fake.call_count);
}

TEST_F(ControllerTest, StopRumble)
{
  controller.stop_rumble();
  ASSERT_EQ(0u, SDL_GameControllerRumble_fake.arg1_val);
  ASSERT_EQ(0u, SDL_GameControllerRumble_fake.arg2_val);
  ASSERT_EQ(0u, SDL_GameControllerRumble_fake.arg3_val);
}

TEST_F(ControllerTest, Product)
{
  std::array<Uint16, 2> values {0, 3};
  SET_RETURN_SEQ(SDL_GameControllerGetProduct, values.data(), cen::isize(values));

  ASSERT_FALSE(controller.product().has_value());
  ASSERT_EQ(3, controller.product().value());
}

TEST_F(ControllerTest, Vendor)
{
  std::array<Uint16, 2> values {0, 7};
  SET_RETURN_SEQ(SDL_GameControllerGetVendor, values.data(), cen::isize(values));

  ASSERT_FALSE(controller.vendor().has_value());
  ASSERT_EQ(7, controller.vendor().value());
}

TEST_F(ControllerTest, ProductVersion)
{
  std::array<Uint16, 2> values {0, 4};
  SET_RETURN_SEQ(SDL_GameControllerGetProductVersion, values.data(), cen::isize(values));

  ASSERT_FALSE(controller.product_version().has_value());
  ASSERT_EQ(4, controller.product_version().value());
}

TEST_F(ControllerTest, Index)
{
  std::array values {-1, 6};
  SET_RETURN_SEQ(SDL_GameControllerGetPlayerIndex, values.data(), cen::isize(values));

  ASSERT_FALSE(controller.index().has_value());
  ASSERT_EQ(6, controller.index().value());
}

TEST_F(ControllerTest, Connected)
{
  std::array values {SDL_FALSE, SDL_TRUE};
  SET_RETURN_SEQ(SDL_GameControllerGetAttached, values.data(), cen::isize(values));

  ASSERT_FALSE(controller.connected());
  ASSERT_TRUE(controller.connected());
}

TEST_F(ControllerTest, Name)
{
  std::array<const char*, 2> values {nullptr, "foobar"};
  SET_RETURN_SEQ(SDL_GameControllerName, values.data(), cen::isize(values));

  ASSERT_EQ(nullptr, controller.name());
  ASSERT_STREQ("foobar", controller.name());
}

TEST_F(ControllerTest, State)
{
  std::array<Uint8, 2> values {SDL_RELEASED, SDL_PRESSED};
  SET_RETURN_SEQ(SDL_GameControllerGetButton, values.data(), cen::isize(values));

  ASSERT_EQ(cen::button_state::released, controller.state(cen::controller_button::a));
  ASSERT_EQ(cen::button_state::pressed, controller.state(cen::controller_button::a));
}

TEST_F(ControllerTest, Pressed)
{
  std::array<Uint8, 2> values {SDL_RELEASED, SDL_PRESSED};
  SET_RETURN_SEQ(SDL_GameControllerGetButton, values.data(), cen::isize(values));

  ASSERT_FALSE(controller.pressed(cen::controller_button::a));
  ASSERT_TRUE(controller.pressed(cen::controller_button::a));
}

TEST_F(ControllerTest, Released)
{
  std::array<Uint8, 2> values {SDL_RELEASED, SDL_PRESSED};
  SET_RETURN_SEQ(SDL_GameControllerGetButton, values.data(), cen::isize(values));

  ASSERT_TRUE(controller.released(cen::controller_button::a));
  ASSERT_FALSE(controller.released(cen::controller_button::a));
}

TEST_F(ControllerTest, AxisFromString)
{
  std::array values {SDL_CONTROLLER_AXIS_INVALID, SDL_CONTROLLER_AXIS_RIGHTX};
  SET_RETURN_SEQ(SDL_GameControllerGetAxisFromString, values.data(), cen::isize(values));

  ASSERT_EQ(cen::controller_axis::invalid, cen::controller::axis(""));
  ASSERT_EQ(cen::controller_axis::right_x, cen::controller::axis(""));

  using namespace std::string_literals;
  ASSERT_EQ(cen::controller_axis::right_x, cen::controller::axis(""s));
}

TEST_F(ControllerTest, Axis)
{
  std::array<Sint16, 2> values {123, 321};
  SET_RETURN_SEQ(SDL_GameControllerGetAxis, values.data(), cen::isize(values));

  ASSERT_EQ(123, controller.axis(cen::controller_axis::left_x));
  ASSERT_EQ(321, controller.axis(cen::controller_axis::left_x));
}

TEST_F(ControllerTest, GetJoystick)
{
  ASSERT_NO_THROW(controller.get_joystick());
}

TEST_F(ControllerTest, AddControllerMapping)
{
  std::array values {1, 0, -1};
  SET_RETURN_SEQ(SDL_GameControllerAddMapping, values.data(), cen::isize(values));

  ASSERT_EQ(cen::controller_mapping_result::added, cen::add_controller_mapping("foo"));

  ASSERT_EQ(cen::controller_mapping_result::updated, cen::add_controller_mapping("foo"));

  ASSERT_EQ(cen::controller_mapping_result::error, cen::add_controller_mapping("foo"));

  using namespace std::string_literals;
  ASSERT_EQ(cen::controller_mapping_result::error, cen::add_controller_mapping("foo"s));
}

TEST_F(ControllerTest, LoadControllerMappings)
{
  std::array values {-1, 7};
  SET_RETURN_SEQ(SDL_GameControllerAddMappingsFromRW, values.data(), cen::isize(values));

  ASSERT_FALSE(cen::load_controller_mappings("foo").has_value());
  ASSERT_EQ(7, cen::load_controller_mappings("foo"));

  using namespace std::string_literals;
  ASSERT_EQ(7, cen::load_controller_mappings("foo"s));
}

TEST_F(ControllerTest, Mapping)
{
  ASSERT_EQ(nullptr, controller.mapping().get());
}

TEST_F(ControllerTest, MappingJoystickIndex)
{
  ASSERT_EQ(nullptr, controller.mapping(0).get());
}

TEST_F(ControllerTest, MappingJoystickGUID)
{
  SDL_JoystickGUID id {};
  ASSERT_EQ(nullptr, controller.mapping(id).get());
}

TEST_F(ControllerTest, MappingByIndex)
{
  ASSERT_EQ(nullptr, controller.mapping_by_index(0).get());
}

TEST_F(ControllerTest, Button)
{
  std::array values {SDL_CONTROLLER_BUTTON_INVALID, SDL_CONTROLLER_BUTTON_B};
  SET_RETURN_SEQ(SDL_GameControllerGetButtonFromString, values.data(), cen::isize(values));

  ASSERT_EQ(cen::controller_button::invalid, cen::controller::button(""));
  ASSERT_EQ(cen::controller_button::b, cen::controller::button(""));

  using namespace std::string_literals;
  ASSERT_EQ(cen::controller_button::b, cen::controller::button(""s));
}

TEST_F(ControllerTest, StringifyWithAxis)
{
  std::array<const char*, 2> values {nullptr, "foo"};
  SET_RETURN_SEQ(SDL_GameControllerGetStringForAxis, values.data(), cen::isize(values));

  ASSERT_EQ(nullptr, cen::controller::stringify(cen::controller_axis::left_y));
  ASSERT_STREQ("foo", cen::controller::stringify(cen::controller_axis::left_y));
}

TEST_F(ControllerTest, StringifyWithButton)
{
  std::array<const char*, 2> values {nullptr, "foo"};
  SET_RETURN_SEQ(SDL_GameControllerGetStringForButton, values.data(), cen::isize(values));

  ASSERT_EQ(nullptr, cen::controller::stringify(cen::controller_button::x));
  ASSERT_STREQ("foo", cen::controller::stringify(cen::controller_button::x));
}

TEST_F(ControllerTest, BindingWithAxis)
{
  SDL_GameControllerButtonBind first {};
  first.bindType = SDL_CONTROLLER_BINDTYPE_NONE;

  SDL_GameControllerButtonBind second {};
  second.bindType = SDL_CONTROLLER_BINDTYPE_AXIS;

  std::array values {first, second};
  SET_RETURN_SEQ(SDL_GameControllerGetBindForAxis, values.data(), cen::isize(values));

  ASSERT_FALSE(controller.binding(cen::controller_axis::right_x).has_value());
  ASSERT_TRUE(controller.binding(cen::controller_axis::right_x).has_value());
}

TEST_F(ControllerTest, BindingWithButton)
{
  SDL_GameControllerButtonBind first {};
  first.bindType = SDL_CONTROLLER_BINDTYPE_NONE;

  SDL_GameControllerButtonBind second {};
  second.bindType = SDL_CONTROLLER_BINDTYPE_AXIS;

  std::array values {first, second};
  SET_RETURN_SEQ(SDL_GameControllerGetBindForButton, values.data(), cen::isize(values));

  ASSERT_FALSE(controller.binding(cen::controller_button::x).has_value());
  ASSERT_TRUE(controller.binding(cen::controller_button::x).has_value());
}

TEST_F(ControllerTest, Update)
{
  cen::controller::update();
  ASSERT_EQ(1u, SDL_GameControllerUpdate_fake.call_count);
}

TEST_F(ControllerTest, Supported)
{
  const auto supported [[maybe_unused]] = cen::controller::supported(0);
  ASSERT_EQ(1u, SDL_IsGameController_fake.call_count);
}

TEST_F(ControllerTest, SetPolling)
{
  cen::controller::set_polling(true);
  ASSERT_EQ(1u, SDL_GameControllerEventState_fake.call_count);
  ASSERT_EQ(SDL_TRUE, SDL_GameControllerEventState_fake.arg0_val);

  cen::controller::set_polling(false);
  ASSERT_EQ(2u, SDL_GameControllerEventState_fake.call_count);
  ASSERT_EQ(SDL_FALSE, SDL_GameControllerEventState_fake.arg0_val);
}

TEST_F(ControllerTest, Polling)
{
  std::array<int, 2> values {SDL_FALSE, SDL_TRUE};
  SET_RETURN_SEQ(SDL_GameControllerEventState, values.data(), cen::isize(values));

  ASSERT_FALSE(cen::controller::polling());
  ASSERT_EQ(SDL_QUERY, SDL_GameControllerEventState_fake.arg0_val);

  ASSERT_TRUE(cen::controller::polling());
  ASSERT_EQ(SDL_QUERY, SDL_GameControllerEventState_fake.arg0_val);
}

TEST_F(ControllerTest, ToString)
{
  std::cout << controller << '\n';
}

#if SDL_VERSION_ATLEAST(2, 0, 12)

TEST_F(ControllerTest, SetPlayerIndex)
{
  controller.set_player_index(7);
  ASSERT_EQ(1u, SDL_GameControllerSetPlayerIndex_fake.call_count);
  ASSERT_EQ(7, SDL_GameControllerSetPlayerIndex_fake.arg1_val);
}

TEST_F(ControllerTest, Type)
{
  std::array values {SDL_CONTROLLER_TYPE_UNKNOWN,
                     SDL_CONTROLLER_TYPE_XBOX360,
                     SDL_CONTROLLER_TYPE_PS4};
  SET_RETURN_SEQ(SDL_GameControllerGetType, values.data(), cen::isize(values));

  ASSERT_EQ(cen::controller_type::unknown, controller.type());
  ASSERT_EQ(cen::controller_type::xbox_360, controller.type());
  ASSERT_EQ(cen::controller_type::ps4, controller.type());
}

TEST_F(ControllerTest, TypeWithIndex)
{
  std::array values {SDL_CONTROLLER_TYPE_UNKNOWN, SDL_CONTROLLER_TYPE_XBOXONE};
  SET_RETURN_SEQ(SDL_GameControllerTypeForIndex, values.data(), cen::isize(values));

  ASSERT_EQ(cen::controller_type::unknown, cen::controller::type(0));
  ASSERT_EQ(cen::controller_type::xbox_one, cen::controller::type(0));
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

#if SDL_VERSION_ATLEAST(2, 0, 14)

TEST_F(ControllerTest, RumbleTriggers)
{
  controller.rumble_triggers(0, 10, 1_ms);
  ASSERT_EQ(1u, SDL_GameControllerRumbleTriggers_fake.call_count);
}

TEST_F(ControllerTest, Serial)
{
  const auto serial [[maybe_unused]] = controller.serial();
  ASSERT_EQ(1u, SDL_GameControllerGetSerial_fake.call_count);
}

TEST_F(ControllerTest, HasAxis)
{
  std::array values {SDL_FALSE, SDL_TRUE};
  SET_RETURN_SEQ(SDL_GameControllerHasAxis, values.data(), cen::isize(values));

  ASSERT_FALSE(controller.has_axis(cen::controller_axis::left_x));
  ASSERT_TRUE(controller.has_axis(cen::controller_axis::left_x));
  ASSERT_EQ(2u, SDL_GameControllerHasAxis_fake.call_count);
}

TEST_F(ControllerTest, HasButton)
{
  std::array values {SDL_FALSE, SDL_TRUE};
  SET_RETURN_SEQ(SDL_GameControllerHasButton, values.data(), cen::isize(values));

  ASSERT_FALSE(controller.has_button(cen::controller_button::x));
  ASSERT_TRUE(controller.has_button(cen::controller_button::x));
  ASSERT_EQ(2u, SDL_GameControllerHasButton_fake.call_count);
}

TEST_F(ControllerTest, TouchpadCount)
{
  const auto count [[maybe_unused]] = controller.touchpad_count();
  ASSERT_EQ(1u, SDL_GameControllerGetNumTouchpads_fake.call_count);
}

TEST_F(ControllerTest, TouchpadFingerCapacity)
{
  const auto capacity [[maybe_unused]] = controller.touchpad_finger_capacity(0);
  ASSERT_EQ(1u, SDL_GameControllerGetNumTouchpadFingers_fake.call_count);
}

TEST_F(ControllerTest, TouchpadFingerState)
{
  std::array values {-1, 0};
  SET_RETURN_SEQ(SDL_GameControllerGetTouchpadFinger, values.data(), cen::isize(values));

  ASSERT_FALSE(controller.touchpad_finger_state(0, 0));
  ASSERT_TRUE(controller.touchpad_finger_state(0, 0));
  ASSERT_EQ(2u, SDL_GameControllerGetTouchpadFinger_fake.call_count);
}

TEST_F(ControllerTest, SetSensor)
{
  std::array values {-1, 0};
  SET_RETURN_SEQ(SDL_GameControllerSetSensorEnabled, values.data(), cen::isize(values));

  const auto type = cen::sensor_type::gyroscope;
  ASSERT_FALSE(controller.set_sensor(type, true));
  ASSERT_TRUE(controller.set_sensor(type, true));
  ASSERT_EQ(2u, SDL_GameControllerSetSensorEnabled_fake.call_count);
}

TEST_F(ControllerTest, HasSensor)
{
  std::array values {SDL_FALSE, SDL_TRUE};
  SET_RETURN_SEQ(SDL_GameControllerHasSensor, values.data(), cen::isize(values));

  ASSERT_FALSE(controller.has_sensor(cen::sensor_type::gyroscope));
  ASSERT_TRUE(controller.has_sensor(cen::sensor_type::gyroscope));
  ASSERT_EQ(2u, SDL_GameControllerHasSensor_fake.call_count);
}

TEST_F(ControllerTest, IsSensorEnabled)
{
  std::array values {SDL_FALSE, SDL_TRUE};
  SET_RETURN_SEQ(SDL_GameControllerIsSensorEnabled, values.data(), cen::isize(values));

  ASSERT_FALSE(controller.is_sensor_enabled(cen::sensor_type::gyroscope));
  ASSERT_TRUE(controller.is_sensor_enabled(cen::sensor_type::gyroscope));
  ASSERT_EQ(2u, SDL_GameControllerIsSensorEnabled_fake.call_count);
}

TEST_F(ControllerTest, SensorData)
{
  std::array values {-1, 0};
  SET_RETURN_SEQ(SDL_GameControllerGetSensorData, values.data(), cen::isize(values));

  ASSERT_FALSE(controller.sensor_data<3>(cen::sensor_type::gyroscope));
  ASSERT_TRUE(controller.sensor_data<3>(cen::sensor_type::gyroscope));
  ASSERT_EQ(2u, SDL_GameControllerGetSensorData_fake.call_count);
}

TEST_F(ControllerTest, SetLED)
{
  std::array values {-1, 0};
  SET_RETURN_SEQ(SDL_GameControllerSetLED, values.data(), cen::isize(values));

  ASSERT_FALSE(controller.set_led(cen::colors::red));
  ASSERT_TRUE(controller.set_led(cen::colors::red));
  ASSERT_EQ(2u, SDL_GameControllerSetLED_fake.call_count);
}

TEST_F(ControllerTest, HasLED)
{
  std::array values {SDL_FALSE, SDL_TRUE};
  SET_RETURN_SEQ(SDL_GameControllerHasLED, values.data(), cen::isize(values));

  ASSERT_FALSE(controller.has_led());
  ASSERT_TRUE(controller.has_led());
  ASSERT_EQ(2u, SDL_GameControllerHasLED_fake.call_count);
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

#if SDL_VERSION_ATLEAST(2, 0, 16)

TEST_F(ControllerTest, SensorDataRate)
{
  std::array values {0.0f, 45.3f};
  SET_RETURN_SEQ(SDL_GameControllerGetSensorDataRate, values.data(), cen::isize(values));

  ASSERT_EQ(0.0f, controller.sensor_data_rate(cen::sensor_type::gyroscope));
  ASSERT_EQ(SDL_SENSOR_GYRO, SDL_GameControllerGetSensorDataRate_fake.arg1_val);

  ASSERT_EQ(45.3f, controller.sensor_data_rate(cen::sensor_type::accelerometer));
  ASSERT_EQ(SDL_SENSOR_ACCEL, SDL_GameControllerGetSensorDataRate_fake.arg1_val);
}

TEST_F(ControllerTest, SendEffect)
{
  std::array values {-1, 0};
  SET_RETURN_SEQ(SDL_GameControllerSendEffect, values.data(), cen::isize(values));

  ASSERT_FALSE(controller.send_effect(nullptr, 12));
  ASSERT_EQ(1u, SDL_GameControllerSendEffect_fake.call_count);
  ASSERT_EQ(12, SDL_GameControllerSendEffect_fake.arg2_val);

  ASSERT_TRUE(controller.send_effect(nullptr, 27));
  ASSERT_EQ(2u, SDL_GameControllerSendEffect_fake.call_count);
  ASSERT_EQ(27, SDL_GameControllerSendEffect_fake.arg2_val);
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 16)

#if SDL_VERSION_ATLEAST(2, 0, 18)

TEST_F(ControllerTest, HasRumble)
{
  std::array values {SDL_FALSE, SDL_TRUE};
  SET_RETURN_SEQ(SDL_GameControllerHasRumble, values.data(), cen::isize(values));

  ASSERT_FALSE(controller.has_rumble());
  ASSERT_TRUE(controller.has_rumble());

  ASSERT_EQ(2u, SDL_GameControllerHasRumble_fake.call_count);
}

TEST_F(ControllerTest, HasRumbleTriggers)
{
  std::array values {SDL_FALSE, SDL_TRUE};
  SET_RETURN_SEQ(SDL_GameControllerHasRumbleTriggers, values.data(), cen::isize(values));

  ASSERT_FALSE(controller.has_rumble_triggers());
  ASSERT_TRUE(controller.has_rumble_triggers());

  ASSERT_EQ(2u, SDL_GameControllerHasRumbleTriggers_fake.call_count);
}

TEST_F(ControllerTest, AppleSFSymbolsNameForButton)
{
  std::array<const char*, 2> values {nullptr, "foo"};
  SET_RETURN_SEQ(SDL_GameControllerGetAppleSFSymbolsNameForButton,
                 values.data(),
                 cen::isize(values));

  ASSERT_FALSE(controller.apple_sf_symbols_name(cen::controller_button::x));
  ASSERT_STREQ("foo", controller.apple_sf_symbols_name(cen::controller_button::x));

  ASSERT_EQ(2u, SDL_GameControllerGetAppleSFSymbolsNameForButton_fake.call_count);
}

TEST_F(ControllerTest, AppleSFSymbolsNameForAxis)
{
  std::array<const char*, 2> values {nullptr, "bar"};
  SET_RETURN_SEQ(SDL_GameControllerGetAppleSFSymbolsNameForAxis,
                 values.data(),
                 cen::isize(values));

  ASSERT_FALSE(controller.apple_sf_symbols_name(cen::controller_axis::left_x));
  ASSERT_STREQ("bar", controller.apple_sf_symbols_name(cen::controller_axis::left_x));

  ASSERT_EQ(2u, SDL_GameControllerGetAppleSFSymbolsNameForAxis_fake.call_count);
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 18)

#if SDL_VERSION_ATLEAST(2, 24, 0)

TEST_F(ControllerTest, Path)
{
  const char* path [[maybe_unused]] = controller.path();
  ASSERT_EQ(1u, SDL_GameControllerPath_fake.call_count);
}

TEST_F(ControllerTest, FirmwareVersion)
{
  std::array<Uint16, 2> values {0, 42};
  SET_RETURN_SEQ(SDL_GameControllerGetFirmwareVersion, values.data(), cen::isize(values));

  ASSERT_FALSE(controller.firmware_version().has_value());
  ASSERT_EQ(42, controller.firmware_version());

  ASSERT_EQ(2u, SDL_GameControllerGetFirmwareVersion_fake.call_count);
}

#endif  // SDL_VERSION_ATLEAST(2, 24, 0)
