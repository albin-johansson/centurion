#include "input/controller.hpp"

#include <fff.h>
#include <gtest/gtest.h>

#include <array>  // array

#include "core/common.hpp"
#include "core/exception.hpp"
#include "core_mocks.hpp"
#include "color.hpp"

using namespace cen::literals;

extern "C"
{
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
  FAKE_VALUE_FUNC(Sint16,
                  SDL_GameControllerGetAxis,
                  SDL_GameController*,
                  SDL_GameControllerAxis)
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
  }

  /**
   * We use a `controller_handle` because it doesn't throw when the pointer is
   * null, this doesn't matter that much since they share implementations of all
   * relevant functions.
   */
  cen::ControllerHandle controller{nullptr};
};

using namespace cen::literals;

TEST_F(ControllerTest, Rumble)
{
  controller.Rumble(0, 10, 1_ms);
  ASSERT_EQ(1u, SDL_GameControllerRumble_fake.call_count);
}

TEST_F(ControllerTest, StopRumble)
{
  controller.StopRumble();
  ASSERT_EQ(0u, SDL_GameControllerRumble_fake.arg1_val);
  ASSERT_EQ(0u, SDL_GameControllerRumble_fake.arg2_val);
  ASSERT_EQ(0u, SDL_GameControllerRumble_fake.arg3_val);
}

TEST_F(ControllerTest, GetProduct)
{
  std::array values{0_u16, 3_u16};
  SET_RETURN_SEQ(SDL_GameControllerGetProduct, values.data(), cen::isize(values));

  ASSERT_FALSE(controller.GetProduct().has_value());
  ASSERT_EQ(3, controller.GetProduct().value());
}

TEST_F(ControllerTest, GetVendor)
{
  std::array values{0_u16, 7_u16};
  SET_RETURN_SEQ(SDL_GameControllerGetVendor, values.data(), cen::isize(values));

  ASSERT_FALSE(controller.GetVendor().has_value());
  ASSERT_EQ(7, controller.GetVendor().value());
}

TEST_F(ControllerTest, ProductVersion)
{
  std::array values{0_u16, 4_u16};
  SET_RETURN_SEQ(SDL_GameControllerGetProductVersion, values.data(), cen::isize(values));

  ASSERT_FALSE(controller.GetProductVersion().has_value());
  ASSERT_EQ(4, controller.GetProductVersion().value());
}

TEST_F(ControllerTest, GetIndex)
{
  std::array values{-1, 6};
  SET_RETURN_SEQ(SDL_GameControllerGetPlayerIndex, values.data(), cen::isize(values));

  ASSERT_FALSE(controller.GetIndex().has_value());
  ASSERT_EQ(6, controller.GetIndex().value());
}

TEST_F(ControllerTest, IsConnected)
{
  std::array values{SDL_FALSE, SDL_TRUE};
  SET_RETURN_SEQ(SDL_GameControllerGetAttached, values.data(), cen::isize(values));

  ASSERT_FALSE(controller.IsConnected());
  ASSERT_TRUE(controller.IsConnected());
}

TEST_F(ControllerTest, GetName)
{
  std::array<const char*, 2> values{nullptr, "foobar"};
  SET_RETURN_SEQ(SDL_GameControllerName, values.data(), cen::isize(values));

  ASSERT_EQ(nullptr, controller.GetName());
  ASSERT_STREQ("foobar", controller.GetName());
}

TEST_F(ControllerTest, GetState)
{
  std::array<Uint8, 2> values{SDL_RELEASED, SDL_PRESSED};
  SET_RETURN_SEQ(SDL_GameControllerGetButton, values.data(), cen::isize(values));

  ASSERT_EQ(cen::ButtonState::Released, controller.GetState(cen::ControllerButton::a));
  ASSERT_EQ(cen::ButtonState::Pressed, controller.GetState(cen::ControllerButton::a));
}

TEST_F(ControllerTest, IsPressed)
{
  std::array<Uint8, 2> values{SDL_RELEASED, SDL_PRESSED};
  SET_RETURN_SEQ(SDL_GameControllerGetButton, values.data(), cen::isize(values));

  ASSERT_FALSE(controller.IsPressed(cen::ControllerButton::a));
  ASSERT_TRUE(controller.IsPressed(cen::ControllerButton::a));
}

TEST_F(ControllerTest, IsReleased)
{
  std::array<Uint8, 2> values{SDL_RELEASED, SDL_PRESSED};
  SET_RETURN_SEQ(SDL_GameControllerGetButton, values.data(), cen::isize(values));

  ASSERT_TRUE(controller.IsReleased(cen::ControllerButton::a));
  ASSERT_FALSE(controller.IsReleased(cen::ControllerButton::a));
}

TEST_F(ControllerTest, GetAxisFromString)
{
  std::array values{SDL_CONTROLLER_AXIS_INVALID, SDL_CONTROLLER_AXIS_RIGHTX};
  SET_RETURN_SEQ(SDL_GameControllerGetAxisFromString, values.data(), cen::isize(values));

  ASSERT_EQ(cen::ControllerAxis::invalid, cen::Controller::GetAxis(""));
  ASSERT_EQ(cen::ControllerAxis::right_x, cen::Controller::GetAxis(""));

  using namespace std::string_literals;
  ASSERT_EQ(cen::ControllerAxis::right_x, cen::Controller::GetAxis(""s));
}

TEST_F(ControllerTest, GetAxis)
{
  std::array values{123_i16, 321_i16};
  SET_RETURN_SEQ(SDL_GameControllerGetAxis, values.data(), cen::isize(values));

  ASSERT_EQ(123, controller.GetAxis(cen::ControllerAxis::left_x));
  ASSERT_EQ(321, controller.GetAxis(cen::ControllerAxis::left_x));
}

TEST_F(ControllerTest, GetJoystick)
{
  ASSERT_NO_THROW(controller.GetJoystick());
}

TEST_F(ControllerTest, AddControllerMapping)
{
  std::array values{1, 0, -1};
  SET_RETURN_SEQ(SDL_GameControllerAddMapping, values.data(), cen::isize(values));

  ASSERT_EQ(cen::ControllerMappingResult::Added, cen::AddControllerMapping("foo"));

  ASSERT_EQ(cen::ControllerMappingResult::Updated, cen::AddControllerMapping("foo"));

  ASSERT_EQ(cen::ControllerMappingResult::Error, cen::AddControllerMapping("foo"));

  using namespace std::string_literals;
  ASSERT_EQ(cen::ControllerMappingResult::Error, cen::AddControllerMapping("foo"s));
}

TEST_F(ControllerTest, LoadControllerMappings)
{
  std::array values{-1, 7};
  SET_RETURN_SEQ(SDL_GameControllerAddMappingsFromRW, values.data(), cen::isize(values));

  ASSERT_FALSE(cen::LoadControllerMappings("foo").has_value());
  ASSERT_EQ(7, cen::LoadControllerMappings("foo"));

  using namespace std::string_literals;
  ASSERT_EQ(7, cen::LoadControllerMappings("foo"s));
}

TEST_F(ControllerTest, GetMapping)
{
  ASSERT_EQ(nullptr, controller.GetMapping().get());
}

TEST_F(ControllerTest, GetMappingJoystickIndex)
{
  ASSERT_EQ(nullptr, controller.GetMapping(0).get());
}

TEST_F(ControllerTest, GetMappingJoystickGUID)
{
  SDL_JoystickGUID id{};
  ASSERT_EQ(nullptr, controller.GetMapping(id).get());
}

TEST_F(ControllerTest, GetMappingByIndex)
{
  ASSERT_EQ(nullptr, controller.GetMappingByIndex(0).get());
}

TEST_F(ControllerTest, GetButton)
{
  std::array values{SDL_CONTROLLER_BUTTON_INVALID, SDL_CONTROLLER_BUTTON_B};
  SET_RETURN_SEQ(SDL_GameControllerGetButtonFromString, values.data(), cen::isize(values));

  ASSERT_EQ(cen::ControllerButton::invalid, cen::Controller::GetButton(""));
  ASSERT_EQ(cen::ControllerButton::b, cen::Controller::GetButton(""));

  using namespace std::string_literals;
  ASSERT_EQ(cen::ControllerButton::b, cen::Controller::GetButton(""s));
}

TEST_F(ControllerTest, StringifyWithAxis)
{
  std::array<const char*, 2> values{nullptr, "foo"};
  SET_RETURN_SEQ(SDL_GameControllerGetStringForAxis, values.data(), cen::isize(values));

  ASSERT_EQ(nullptr, cen::Controller::Stringify(cen::ControllerAxis::left_y));
  ASSERT_STREQ("foo", cen::Controller::Stringify(cen::ControllerAxis::left_y));
}

TEST_F(ControllerTest, StringifyWithButton)
{
  std::array<const char*, 2> values{nullptr, "foo"};
  SET_RETURN_SEQ(SDL_GameControllerGetStringForButton, values.data(), cen::isize(values));

  ASSERT_EQ(nullptr, cen::Controller::Stringify(cen::ControllerButton::x));
  ASSERT_STREQ("foo", cen::Controller::Stringify(cen::ControllerButton::x));
}

TEST_F(ControllerTest, GetBindingWithAxis)
{
  SDL_GameControllerButtonBind first{};
  first.bindType = SDL_CONTROLLER_BINDTYPE_NONE;

  SDL_GameControllerButtonBind second{};
  second.bindType = SDL_CONTROLLER_BINDTYPE_AXIS;

  std::array values{first, second};
  SET_RETURN_SEQ(SDL_GameControllerGetBindForAxis, values.data(), cen::isize(values));

  ASSERT_FALSE(controller.GetBinding(cen::ControllerAxis::right_x).has_value());
  ASSERT_TRUE(controller.GetBinding(cen::ControllerAxis::right_x).has_value());
}

TEST_F(ControllerTest, GetBindingWithButton)
{
  SDL_GameControllerButtonBind first{};
  first.bindType = SDL_CONTROLLER_BINDTYPE_NONE;

  SDL_GameControllerButtonBind second{};
  second.bindType = SDL_CONTROLLER_BINDTYPE_AXIS;

  std::array values{first, second};
  SET_RETURN_SEQ(SDL_GameControllerGetBindForButton, values.data(), cen::isize(values));

  ASSERT_FALSE(controller.GetBinding(cen::ControllerButton::x).has_value());
  ASSERT_TRUE(controller.GetBinding(cen::ControllerButton::x).has_value());
}

TEST_F(ControllerTest, Update)
{
  cen::Controller::Update();
  ASSERT_EQ(1u, SDL_GameControllerUpdate_fake.call_count);
}

TEST_F(ControllerTest, IsSupported)
{
  const auto supported = cen::Controller::IsSupported(0);
  ASSERT_EQ(1u, SDL_IsGameController_fake.call_count);
}

TEST_F(ControllerTest, SetPolling)
{
  cen::Controller::SetPolling(true);
  ASSERT_EQ(1u, SDL_GameControllerEventState_fake.call_count);
  ASSERT_EQ(SDL_TRUE, SDL_GameControllerEventState_fake.arg0_val);

  cen::Controller::SetPolling(false);
  ASSERT_EQ(2u, SDL_GameControllerEventState_fake.call_count);
  ASSERT_EQ(SDL_FALSE, SDL_GameControllerEventState_fake.arg0_val);
}

TEST_F(ControllerTest, IsPolling)
{
  std::array<int, 2> values{SDL_FALSE, SDL_TRUE};
  SET_RETURN_SEQ(SDL_GameControllerEventState, values.data(), cen::isize(values));

  ASSERT_FALSE(cen::Controller::IsPolling());
  ASSERT_EQ(SDL_QUERY, SDL_GameControllerEventState_fake.arg0_val);

  ASSERT_TRUE(cen::Controller::IsPolling());
  ASSERT_EQ(SDL_QUERY, SDL_GameControllerEventState_fake.arg0_val);
}

TEST_F(ControllerTest, ToString)
{
  std::clog << controller << '\n';
}

#if SDL_VERSION_ATLEAST(2, 0, 12)

TEST_F(ControllerTest, SetPlayerIndex)
{
  controller.SetPlayerIndex(7);
  ASSERT_EQ(1u, SDL_GameControllerSetPlayerIndex_fake.call_count);
  ASSERT_EQ(7, SDL_GameControllerSetPlayerIndex_fake.arg1_val);
}

TEST_F(ControllerTest, GetType)
{
  std::array values{SDL_CONTROLLER_TYPE_UNKNOWN,
                    SDL_CONTROLLER_TYPE_XBOX360,
                    SDL_CONTROLLER_TYPE_PS4};
  SET_RETURN_SEQ(SDL_GameControllerGetType, values.data(), cen::isize(values));

  ASSERT_EQ(cen::ControllerType::unknown, controller.GetType());
  ASSERT_EQ(cen::ControllerType::xbox_360, controller.GetType());
  ASSERT_EQ(cen::ControllerType::ps4, controller.GetType());
}

TEST_F(ControllerTest, GetTypeWithIndex)
{
  std::array values{SDL_CONTROLLER_TYPE_UNKNOWN, SDL_CONTROLLER_TYPE_XBOXONE};
  SET_RETURN_SEQ(SDL_GameControllerTypeForIndex, values.data(), cen::isize(values));

  ASSERT_EQ(cen::ControllerType::unknown, cen::Controller::GetType(0));
  ASSERT_EQ(cen::ControllerType::xbox_one, cen::Controller::GetType(0));
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

#if SDL_VERSION_ATLEAST(2, 0, 14)

TEST_F(ControllerTest, RumbleTriggers)
{
  controller.RumbleTriggers(0, 10, 1_ms);
  ASSERT_EQ(1u, SDL_GameControllerRumbleTriggers_fake.call_count);
}

TEST_F(ControllerTest, GetSerial)
{
  const auto serial [[maybe_unused]] = controller.GetSerial();
  ASSERT_EQ(1u, SDL_GameControllerGetSerial_fake.call_count);
}

TEST_F(ControllerTest, HasAxis)
{
  std::array values{SDL_FALSE, SDL_TRUE};
  SET_RETURN_SEQ(SDL_GameControllerHasAxis, values.data(), cen::isize(values));

  ASSERT_FALSE(controller.HasAxis(cen::ControllerAxis::left_x));
  ASSERT_TRUE(controller.HasAxis(cen::ControllerAxis::left_x));
  ASSERT_EQ(2u, SDL_GameControllerHasAxis_fake.call_count);
}

TEST_F(ControllerTest, HasButton)
{
  std::array values{SDL_FALSE, SDL_TRUE};
  SET_RETURN_SEQ(SDL_GameControllerHasButton, values.data(), cen::isize(values));

  ASSERT_FALSE(controller.HasButton(cen::ControllerButton::x));
  ASSERT_TRUE(controller.HasButton(cen::ControllerButton::x));
  ASSERT_EQ(2u, SDL_GameControllerHasButton_fake.call_count);
}

TEST_F(ControllerTest, TouchpadCount)
{
  const auto count [[maybe_unused]] = controller.GetNumTouchpads();
  ASSERT_EQ(1u, SDL_GameControllerGetNumTouchpads_fake.call_count);
}

TEST_F(ControllerTest, TouchpadFingerCapacity)
{
  const auto capacity [[maybe_unused]] = controller.GetTouchpadFingerCapacity(0);
  ASSERT_EQ(1u, SDL_GameControllerGetNumTouchpadFingers_fake.call_count);
}

TEST_F(ControllerTest, TouchpadFingerState)
{
  std::array values{-1, 0};
  SET_RETURN_SEQ(SDL_GameControllerGetTouchpadFinger, values.data(), cen::isize(values));

  ASSERT_FALSE(controller.GetTouchpadFingerState(0, 0));
  ASSERT_TRUE(controller.GetTouchpadFingerState(0, 0));
  ASSERT_EQ(2u, SDL_GameControllerGetTouchpadFinger_fake.call_count);
}

TEST_F(ControllerTest, SetSensorEnabled)
{
  std::array values{-1, 0};
  SET_RETURN_SEQ(SDL_GameControllerSetSensorEnabled, values.data(), cen::isize(values));

  const auto type = cen::sensor_type::gyroscope;
  ASSERT_FALSE(controller.SetSensorEnabled(type, true));
  ASSERT_TRUE(controller.SetSensorEnabled(type, true));
  ASSERT_EQ(2u, SDL_GameControllerSetSensorEnabled_fake.call_count);
}

TEST_F(ControllerTest, HasSensor)
{
  std::array values{SDL_FALSE, SDL_TRUE};
  SET_RETURN_SEQ(SDL_GameControllerHasSensor, values.data(), cen::isize(values));

  ASSERT_FALSE(controller.HasSensor(cen::sensor_type::gyroscope));
  ASSERT_TRUE(controller.HasSensor(cen::sensor_type::gyroscope));
  ASSERT_EQ(2u, SDL_GameControllerHasSensor_fake.call_count);
}

TEST_F(ControllerTest, IsSensorEnabled)
{
  std::array values{SDL_FALSE, SDL_TRUE};
  SET_RETURN_SEQ(SDL_GameControllerIsSensorEnabled, values.data(), cen::isize(values));

  ASSERT_FALSE(controller.IsSensorEnabled(cen::sensor_type::gyroscope));
  ASSERT_TRUE(controller.IsSensorEnabled(cen::sensor_type::gyroscope));
  ASSERT_EQ(2u, SDL_GameControllerIsSensorEnabled_fake.call_count);
}

TEST_F(ControllerTest, GetSensorData)
{
  std::array values{-1, 0};
  SET_RETURN_SEQ(SDL_GameControllerGetSensorData, values.data(), cen::isize(values));

  ASSERT_FALSE(controller.GetSensorData<3>(cen::sensor_type::gyroscope));
  ASSERT_TRUE(controller.GetSensorData<3>(cen::sensor_type::gyroscope));
  ASSERT_EQ(2u, SDL_GameControllerGetSensorData_fake.call_count);
}

TEST_F(ControllerTest, SetLED)
{
  std::array values{-1, 0};
  SET_RETURN_SEQ(SDL_GameControllerSetLED, values.data(), cen::isize(values));

  ASSERT_FALSE(controller.SetLED(cen::colors::red));
  ASSERT_TRUE(controller.SetLED(cen::colors::red));
  ASSERT_EQ(2u, SDL_GameControllerSetLED_fake.call_count);
}

TEST_F(ControllerTest, HasLED)
{
  std::array values{SDL_FALSE, SDL_TRUE};
  SET_RETURN_SEQ(SDL_GameControllerHasLED, values.data(), cen::isize(values));

  ASSERT_FALSE(controller.HasLED());
  ASSERT_TRUE(controller.HasLED());
  ASSERT_EQ(2u, SDL_GameControllerHasLED_fake.call_count);
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

#if SDL_VERSION_ATLEAST(2, 0, 16)

TEST_F(ControllerTest, GetSensorDataRate)
{
  std::array values{0.0f, 45.3f};
  SET_RETURN_SEQ(SDL_GameControllerGetSensorDataRate, values.data(), cen::isize(values));

  ASSERT_EQ(0.0f, controller.GetSensorDataRate(cen::sensor_type::gyroscope));
  ASSERT_EQ(SDL_SENSOR_GYRO, SDL_GameControllerGetSensorDataRate_fake.arg1_val);

  ASSERT_EQ(45.3f, controller.GetSensorDataRate(cen::sensor_type::accelerometer));
  ASSERT_EQ(SDL_SENSOR_ACCEL, SDL_GameControllerGetSensorDataRate_fake.arg1_val);
}

TEST_F(ControllerTest, SendEffect)
{
  std::array values{-1, 0};
  SET_RETURN_SEQ(SDL_GameControllerSendEffect, values.data(), cen::isize(values));

  ASSERT_FALSE(controller.SendEffect(nullptr, 12));
  ASSERT_EQ(1u, SDL_GameControllerSendEffect_fake.call_count);
  ASSERT_EQ(12, SDL_GameControllerSendEffect_fake.arg2_val);

  ASSERT_TRUE(controller.SendEffect(nullptr, 27));
  ASSERT_EQ(2u, SDL_GameControllerSendEffect_fake.call_count);
  ASSERT_EQ(27, SDL_GameControllerSendEffect_fake.arg2_val);
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 16)
