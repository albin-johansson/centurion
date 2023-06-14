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

#include "centurion/input/joystick.hpp"

#include <fff.h>
#include <gtest/gtest.h>

#include <array>  // array

#include "centurion/video/color.hpp"
#include "core_mocks.hpp"

using namespace cen::literals;

extern "C" {
FAKE_VOID_FUNC(SDL_JoystickUpdate)
FAKE_VOID_FUNC(SDL_LockJoysticks)
FAKE_VOID_FUNC(SDL_UnlockJoysticks)

FAKE_VALUE_FUNC(int, SDL_JoystickRumble, SDL_Joystick*, Uint16, Uint16, Uint32)

FAKE_VALUE_FUNC(SDL_Joystick*, SDL_JoystickFromInstanceID, SDL_JoystickID)
FAKE_VALUE_FUNC(SDL_Joystick*, SDL_JoystickFromPlayerIndex, int)

FAKE_VALUE_FUNC(int, SDL_JoystickGetPlayerIndex, SDL_Joystick*)
FAKE_VALUE_FUNC(int, SDL_JoystickGetDevicePlayerIndex, int)

FAKE_VALUE_FUNC(SDL_JoystickType, SDL_JoystickGetType, SDL_Joystick*)
FAKE_VALUE_FUNC(SDL_JoystickType, SDL_JoystickGetDeviceType, int)

FAKE_VALUE_FUNC(Uint16, SDL_JoystickGetVendor, SDL_Joystick*)
FAKE_VALUE_FUNC(Uint16, SDL_JoystickGetDeviceVendor, int)

FAKE_VALUE_FUNC(Uint16, SDL_JoystickGetProduct, SDL_Joystick*)
FAKE_VALUE_FUNC(Uint16, SDL_JoystickGetDeviceProduct, int)

FAKE_VALUE_FUNC(Uint16, SDL_JoystickGetProductVersion, SDL_Joystick*)
FAKE_VALUE_FUNC(Uint16, SDL_JoystickGetDeviceProductVersion, int)

FAKE_VALUE_FUNC(SDL_JoystickID, SDL_JoystickInstanceID, SDL_Joystick*)
FAKE_VALUE_FUNC(SDL_JoystickID, SDL_JoystickGetDeviceInstanceID, int)

FAKE_VALUE_FUNC(SDL_JoystickGUID, SDL_JoystickGetGUID, SDL_Joystick*)
FAKE_VALUE_FUNC(SDL_JoystickGUID, SDL_JoystickGetDeviceGUID, int)

FAKE_VALUE_FUNC(int, SDL_NumJoysticks)
FAKE_VALUE_FUNC(int, SDL_JoystickGetBall, SDL_Joystick*, int, int*, int*)
FAKE_VALUE_FUNC(int, SDL_JoystickSetLED, SDL_Joystick*, Uint8, Uint8, Uint8)
FAKE_VALUE_FUNC(int, SDL_JoystickNumHats, SDL_Joystick*)
FAKE_VALUE_FUNC(int, SDL_JoystickNumAxes, SDL_Joystick*)
FAKE_VALUE_FUNC(int, SDL_JoystickNumBalls, SDL_Joystick*)
FAKE_VALUE_FUNC(int, SDL_JoystickNumButtons, SDL_Joystick*)
FAKE_VALUE_FUNC(Sint16, SDL_JoystickGetAxis, SDL_Joystick*, int)
FAKE_VALUE_FUNC(Uint8, SDL_JoystickGetButton, SDL_Joystick*, int)
FAKE_VALUE_FUNC(Uint8, SDL_JoystickGetHat, SDL_Joystick*, int)
FAKE_VALUE_FUNC(SDL_bool, SDL_JoystickGetAxisInitialState, SDL_Joystick*, int, Sint16*)
FAKE_VALUE_FUNC(SDL_bool, SDL_JoystickGetAttached, SDL_Joystick*)
FAKE_VALUE_FUNC(SDL_bool, SDL_JoystickHasLED, SDL_Joystick*)
FAKE_VALUE_FUNC(SDL_JoystickPowerLevel, SDL_JoystickCurrentPowerLevel, SDL_Joystick*)
FAKE_VALUE_FUNC(const char*, SDL_JoystickName, SDL_Joystick*)
FAKE_VALUE_FUNC(int, SDL_JoystickEventState, int)
FAKE_VALUE_FUNC(SDL_JoystickGUID, SDL_JoystickGetGUIDFromString, const char*)

#if SDL_VERSION_ATLEAST(2, 0, 12)
FAKE_VOID_FUNC(SDL_JoystickSetPlayerIndex, SDL_Joystick*, int)
#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

#if SDL_VERSION_ATLEAST(2, 0, 14)
FAKE_VALUE_FUNC(int, SDL_JoystickRumbleTriggers, SDL_Joystick*, Uint16, Uint16, Uint32)
FAKE_VALUE_FUNC(const char*, SDL_JoystickGetSerial, SDL_Joystick*)
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

#if SDL_VERSION_ATLEAST(2, 0, 16)
FAKE_VALUE_FUNC(int, SDL_JoystickSendEffect, SDL_Joystick*, const void*, int)
#endif  // SDL_VERSION_ATLEAST(2, 0, 16)

#if SDL_VERSION_ATLEAST(2, 0, 18)
FAKE_VALUE_FUNC(SDL_bool, SDL_JoystickHasRumble, SDL_Joystick*)
FAKE_VALUE_FUNC(SDL_bool, SDL_JoystickHasRumbleTriggers, SDL_Joystick*)
#endif  // SDL_VERSION_ATLEAST(2, 0, 16)

#if SDL_VERSION_ATLEAST(2, 24, 0)
FAKE_VALUE_FUNC(const char*, SDL_JoystickPath, SDL_Joystick*)
FAKE_VALUE_FUNC(const char*, SDL_JoystickPathForIndex, int)
FAKE_VALUE_FUNC(Uint16, SDL_JoystickGetFirmwareVersion, SDL_Joystick*)
#endif  // SDL_VERSION_ATLEAST(2, 24, 0)
}

using namespace cen::literals;

class JoystickTest : public testing::Test {
 protected:
  void SetUp() override
  {
    mocks::reset_core();

    RESET_FAKE(SDL_JoystickUpdate)
    RESET_FAKE(SDL_LockJoysticks)
    RESET_FAKE(SDL_UnlockJoysticks)
    RESET_FAKE(SDL_JoystickRumble)

    RESET_FAKE(SDL_JoystickFromInstanceID)

    RESET_FAKE(SDL_JoystickGetPlayerIndex)
    RESET_FAKE(SDL_JoystickGetDevicePlayerIndex)

    RESET_FAKE(SDL_JoystickGetType)
    RESET_FAKE(SDL_JoystickGetDeviceType)

    RESET_FAKE(SDL_JoystickGetVendor)
    RESET_FAKE(SDL_JoystickGetDeviceVendor)

    RESET_FAKE(SDL_JoystickGetProduct)
    RESET_FAKE(SDL_JoystickGetDeviceProduct)

    RESET_FAKE(SDL_JoystickGetProductVersion)
    RESET_FAKE(SDL_JoystickGetDeviceProductVersion)

    RESET_FAKE(SDL_JoystickInstanceID)
    RESET_FAKE(SDL_JoystickGetDeviceInstanceID)

    RESET_FAKE(SDL_JoystickGetGUID)
    RESET_FAKE(SDL_JoystickGetDeviceGUID)

    RESET_FAKE(SDL_NumJoysticks)
    RESET_FAKE(SDL_JoystickGetBall)

    RESET_FAKE(SDL_JoystickGetAxis)
    RESET_FAKE(SDL_JoystickGetHat)
    RESET_FAKE(SDL_JoystickGetButton)
    RESET_FAKE(SDL_JoystickGetAxisInitialState)
    RESET_FAKE(SDL_JoystickGetAttached)
    RESET_FAKE(SDL_JoystickCurrentPowerLevel)
    RESET_FAKE(SDL_JoystickNumHats)
    RESET_FAKE(SDL_JoystickNumAxes)
    RESET_FAKE(SDL_JoystickNumBalls)
    RESET_FAKE(SDL_JoystickNumButtons)
    RESET_FAKE(SDL_JoystickName)
    RESET_FAKE(SDL_JoystickEventState)
    RESET_FAKE(SDL_JoystickGetGUIDFromString)

#if SDL_VERSION_ATLEAST(2, 0, 12)
    RESET_FAKE(SDL_JoystickSetPlayerIndex)
    RESET_FAKE(SDL_JoystickFromPlayerIndex)
#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

#if SDL_VERSION_ATLEAST(2, 0, 14)
    RESET_FAKE(SDL_JoystickRumbleTriggers)
    RESET_FAKE(SDL_JoystickGetSerial)
    RESET_FAKE(SDL_JoystickSetLED)
    RESET_FAKE(SDL_JoystickHasLED)
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

#if SDL_VERSION_ATLEAST(2, 0, 16)
    RESET_FAKE(SDL_JoystickSendEffect)
#endif  // SDL_VERSION_ATLEAST(2, 0, 16)

#if SDL_VERSION_ATLEAST(2, 0, 18)
    RESET_FAKE(SDL_JoystickHasRumble)
    RESET_FAKE(SDL_JoystickHasRumbleTriggers)
#endif  // SDL_VERSION_ATLEAST(2, 0, 18)

#if SDL_VERSION_ATLEAST(2, 24, 0)
    RESET_FAKE(SDL_JoystickPath)
    RESET_FAKE(SDL_JoystickPathForIndex)
    RESET_FAKE(SDL_JoystickGetFirmwareVersion)
#endif  // SDL_VERSION_ATLEAST(2, 24, 0)
  }

  cen::joystick_handle joystick {nullptr};
};

TEST_F(JoystickTest, FromID)
{
  const auto handle [[maybe_unused]] = cen::joystick_handle::from_id(0);

  ASSERT_EQ(1u, SDL_JoystickFromInstanceID_fake.call_count);
}

TEST_F(JoystickTest, Rumble)
{
  joystick.rumble(10, 20, 5_ms);
  ASSERT_EQ(1u, SDL_JoystickRumble_fake.call_count);
  ASSERT_EQ(10u, SDL_JoystickRumble_fake.arg1_val);
  ASSERT_EQ(20u, SDL_JoystickRumble_fake.arg2_val);
  ASSERT_EQ(5u, SDL_JoystickRumble_fake.arg3_val);
}

TEST_F(JoystickTest, PlayerIndex)
{
  std::array values {-1, 7};
  SET_RETURN_SEQ(SDL_JoystickGetPlayerIndex, values.data(), cen::isize(values));

  ASSERT_FALSE(joystick.player_index().has_value());
  ASSERT_EQ(7, joystick.player_index());

  ASSERT_EQ(2u, SDL_JoystickGetPlayerIndex_fake.call_count);
}

TEST_F(JoystickTest, PlayerIndexStatic)
{
  std::array values {-1, 42};
  SET_RETURN_SEQ(SDL_JoystickGetDevicePlayerIndex, values.data(), cen::isize(values));

  ASSERT_FALSE(cen::joystick::player_index(0).has_value());
  ASSERT_EQ(42, cen::joystick::player_index(0));

  ASSERT_EQ(2u, SDL_JoystickGetDevicePlayerIndex_fake.call_count);
}

TEST_F(JoystickTest, Type)
{
  const auto type [[maybe_unused]] = joystick.type();
  ASSERT_EQ(1u, SDL_JoystickGetType_fake.call_count);
}

TEST_F(JoystickTest, TypeStatic)
{
  const auto type [[maybe_unused]] = cen::joystick::type(0);
  ASSERT_EQ(1u, SDL_JoystickGetDeviceType_fake.call_count);
}

TEST_F(JoystickTest, Vendor)
{
  std::array<Uint16, 2> values {0, 4};
  SET_RETURN_SEQ(SDL_JoystickGetVendor, values.data(), cen::isize(values));

  ASSERT_FALSE(joystick.vendor().has_value());
  ASSERT_EQ(4, joystick.vendor());

  ASSERT_EQ(2u, SDL_JoystickGetVendor_fake.call_count);
}

TEST_F(JoystickTest, VendorStatic)
{
  std::array<Uint16, 2> values {0, 4};
  SET_RETURN_SEQ(SDL_JoystickGetDeviceVendor, values.data(), cen::isize(values));

  ASSERT_FALSE(cen::joystick::vendor(0).has_value());
  ASSERT_EQ(4, cen::joystick::vendor(0));

  ASSERT_EQ(2u, SDL_JoystickGetDeviceVendor_fake.call_count);
}

TEST_F(JoystickTest, Product)
{
  std::array<Uint16, 2> values {0, 6};
  SET_RETURN_SEQ(SDL_JoystickGetProduct, values.data(), cen::isize(values));

  ASSERT_FALSE(joystick.product().has_value());
  ASSERT_EQ(6, joystick.product());

  ASSERT_EQ(2u, SDL_JoystickGetProduct_fake.call_count);
}

TEST_F(JoystickTest, ProductStatic)
{
  std::array<Uint16, 2> values {0, 8};
  SET_RETURN_SEQ(SDL_JoystickGetDeviceProduct, values.data(), cen::isize(values));

  ASSERT_FALSE(cen::joystick::product(0).has_value());
  ASSERT_EQ(8, cen::joystick::product(0));

  ASSERT_EQ(2u, SDL_JoystickGetDeviceProduct_fake.call_count);
}

TEST_F(JoystickTest, ProductVersion)
{
  std::array<Uint16, 2> values {0, 54};
  SET_RETURN_SEQ(SDL_JoystickGetProductVersion, values.data(), cen::isize(values));

  ASSERT_FALSE(joystick.product_version().has_value());
  ASSERT_EQ(54, joystick.product_version());

  ASSERT_EQ(2u, SDL_JoystickGetProductVersion_fake.call_count);
}

TEST_F(JoystickTest, ProductVersionStatic)
{
  std::array<Uint16, 2> values {0, 12};
  SET_RETURN_SEQ(SDL_JoystickGetDeviceProductVersion, values.data(), cen::isize(values));

  ASSERT_FALSE(cen::joystick::product_version(0).has_value());
  ASSERT_EQ(12, cen::joystick::product_version(0));

  ASSERT_EQ(2u, SDL_JoystickGetDeviceProductVersion_fake.call_count);
}

TEST_F(JoystickTest, BallAxisDelta)
{
  std::array values {-1, 0};
  SET_RETURN_SEQ(SDL_JoystickGetBall, values.data(), cen::isize(values));

  ASSERT_FALSE(joystick.get_ball_axis_delta(0).has_value());
  ASSERT_TRUE(joystick.get_ball_axis_delta(0).has_value());

  ASSERT_EQ(2u, SDL_JoystickGetBall_fake.call_count);
}

TEST_F(JoystickTest, QueryAxis)
{
  std::array<Sint16, 2> values {0, 123};
  SET_RETURN_SEQ(SDL_JoystickGetAxis, values.data(), cen::isize(values));

  ASSERT_EQ(0, joystick.query_axis(0));
  ASSERT_EQ(123, joystick.query_axis(0));
  ASSERT_EQ(2u, SDL_JoystickGetAxis_fake.call_count);
}

TEST_F(JoystickTest, AxisInitialState)
{
  std::array values {SDL_FALSE, SDL_TRUE};
  SET_RETURN_SEQ(SDL_JoystickGetAxisInitialState, values.data(), cen::isize(values));

  ASSERT_FALSE(joystick.axis_initial_state(0).has_value());
  ASSERT_TRUE(joystick.axis_initial_state(0).has_value());

  ASSERT_EQ(2u, SDL_JoystickGetAxisInitialState_fake.call_count);
}

TEST_F(JoystickTest, Attached)
{
  const auto attached [[maybe_unused]] = joystick.attached();
  ASSERT_EQ(1u, SDL_JoystickGetAttached_fake.call_count);
}

TEST_F(JoystickTest, HatCount)
{
  const auto count [[maybe_unused]] = joystick.hat_count();
  ASSERT_EQ(1u, SDL_JoystickNumHats_fake.call_count);
}

TEST_F(JoystickTest, AxisCount)
{
  const auto count [[maybe_unused]] = joystick.axis_count();
  ASSERT_EQ(1u, SDL_JoystickNumAxes_fake.call_count);
}

TEST_F(JoystickTest, TrackballCount)
{
  const auto count [[maybe_unused]] = joystick.trackball_count();
  ASSERT_EQ(1u, SDL_JoystickNumBalls_fake.call_count);
}

TEST_F(JoystickTest, ButtonCount)
{
  const auto count [[maybe_unused]] = joystick.button_count();
  ASSERT_EQ(1u, SDL_JoystickNumButtons_fake.call_count);
}

TEST_F(JoystickTest, ID)
{
  const auto id [[maybe_unused]] = joystick.id();
  ASSERT_EQ(1u, SDL_JoystickInstanceID_fake.call_count);
}

TEST_F(JoystickTest, IDStatic)
{
  std::array values {-1, 3};
  SET_RETURN_SEQ(SDL_JoystickGetDeviceInstanceID, values.data(), cen::isize(values));

  ASSERT_FALSE(cen::joystick::id(0).has_value());
  ASSERT_EQ(3, cen::joystick::id(0));

  ASSERT_EQ(2u, SDL_JoystickGetDeviceInstanceID_fake.call_count);
}

TEST_F(JoystickTest, GUID)
{
  const auto id [[maybe_unused]] = joystick.guid();
  ASSERT_EQ(1u, SDL_JoystickGetGUID_fake.call_count);
}

TEST_F(JoystickTest, GUIDStatic)
{
  const auto name [[maybe_unused]] = cen::joystick::guid(0);
  ASSERT_EQ(1u, SDL_JoystickGetDeviceGUID_fake.call_count);
}

TEST_F(JoystickTest, Name)
{
  const auto name [[maybe_unused]] = joystick.name();
  ASSERT_EQ(1u, SDL_JoystickName_fake.call_count);
}

TEST_F(JoystickTest, Power)
{
  const auto power [[maybe_unused]] = joystick.power();
  ASSERT_EQ(1u, SDL_JoystickCurrentPowerLevel_fake.call_count);
}

TEST_F(JoystickTest, QueryButton)
{
  const auto state [[maybe_unused]] = joystick.query_button(0);
  ASSERT_EQ(1u, SDL_JoystickGetButton_fake.call_count);
}

TEST_F(JoystickTest, QueryHat)
{
  const auto state [[maybe_unused]] = joystick.query_hat(0);
  ASSERT_EQ(1u, SDL_JoystickGetHat_fake.call_count);
}

TEST_F(JoystickTest, Update)
{
  cen::joystick::update();
  ASSERT_EQ(1u, SDL_JoystickUpdate_fake.call_count);
}

TEST_F(JoystickTest, Lock)
{
  cen::joystick::lock();
  ASSERT_EQ(1u, SDL_LockJoysticks_fake.call_count);
}

TEST_F(JoystickTest, Unlock)
{
  cen::joystick::unlock();
  ASSERT_EQ(1u, SDL_UnlockJoysticks_fake.call_count);
}

TEST_F(JoystickTest, SetPolling)
{
  cen::joystick::set_polling(true);
  ASSERT_EQ(SDL_ENABLE, SDL_JoystickEventState_fake.arg0_val);

  cen::joystick::set_polling(false);
  ASSERT_EQ(SDL_DISABLE, SDL_JoystickEventState_fake.arg0_val);

  ASSERT_EQ(2u, SDL_JoystickEventState_fake.call_count);
}

TEST_F(JoystickTest, Polling)
{
  const auto isPolling [[maybe_unused]] = cen::joystick::polling();

  ASSERT_EQ(SDL_QUERY, SDL_JoystickEventState_fake.arg0_val);
  ASSERT_EQ(1u, SDL_JoystickEventState_fake.call_count);
}

TEST_F(JoystickTest, Count)
{
  std::array values {-1, 7};
  SET_RETURN_SEQ(SDL_NumJoysticks, values.data(), cen::isize(values));

  ASSERT_FALSE(cen::joystick::count().has_value());
  ASSERT_EQ(7, cen::joystick::count());

  ASSERT_EQ(2u, SDL_NumJoysticks_fake.call_count);
}

TEST_F(JoystickTest, ToGuid)
{
  {
    const auto id [[maybe_unused]] = cen::joystick::to_guid("");
    ASSERT_EQ(1u, SDL_JoystickGetGUIDFromString_fake.call_count);
  }

  {
    using namespace std::string_literals;
    const auto id [[maybe_unused]] = cen::joystick::to_guid(""s);
    ASSERT_EQ(2u, SDL_JoystickGetGUIDFromString_fake.call_count);
  }
}

#if SDL_VERSION_ATLEAST(2, 0, 12)

TEST_F(JoystickTest, FromPlayerIndex)
{
  const auto handle [[maybe_unused]] = cen::joystick_handle::from_player_index(0);

  ASSERT_EQ(1u, SDL_JoystickFromPlayerIndex_fake.call_count);
}

TEST_F(JoystickTest, SetPlayerIndex)
{
  joystick.set_player_index(7);
  ASSERT_EQ(1u, SDL_JoystickSetPlayerIndex_fake.call_count);
  ASSERT_EQ(7, SDL_JoystickSetPlayerIndex_fake.arg1_val);
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

#if SDL_VERSION_ATLEAST(2, 0, 14)

TEST_F(JoystickTest, RumbleTriggers)
{
  std::array values {-1, 0};
  SET_RETURN_SEQ(SDL_JoystickRumbleTriggers, values.data(), cen::isize(values));

  ASSERT_FALSE(joystick.rumble_triggers(12, 34, 56_ms));
  ASSERT_TRUE(joystick.rumble_triggers(12, 34, 56_ms));

  ASSERT_EQ(12u, SDL_JoystickRumbleTriggers_fake.arg1_val);
  ASSERT_EQ(34u, SDL_JoystickRumbleTriggers_fake.arg2_val);
  ASSERT_EQ(56u, SDL_JoystickRumbleTriggers_fake.arg3_val);

  ASSERT_EQ(2u, SDL_JoystickRumbleTriggers_fake.call_count);
}

TEST_F(JoystickTest, SetLED)
{
  std::array values {-1, 0};
  SET_RETURN_SEQ(SDL_JoystickSetLED, values.data(), cen::isize(values));

  const auto color = cen::colors::magenta;
  ASSERT_FALSE(joystick.set_led(color));
  ASSERT_TRUE(joystick.set_led(color));
  ASSERT_EQ(2u, SDL_JoystickSetLED_fake.call_count);
}

TEST_F(JoystickTest, HasLED)
{
  std::array values {SDL_FALSE, SDL_TRUE};
  SET_RETURN_SEQ(SDL_JoystickHasLED, values.data(), cen::isize(values));

  ASSERT_FALSE(joystick.has_led());
  ASSERT_TRUE(joystick.has_led());
  ASSERT_EQ(2u, SDL_JoystickHasLED_fake.call_count);
}

TEST_F(JoystickTest, Serial)
{
  const auto name [[maybe_unused]] = joystick.serial();
  ASSERT_EQ(1u, SDL_JoystickGetSerial_fake.call_count);
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

#if SDL_VERSION_ATLEAST(2, 0, 16)

TEST_F(JoystickTest, SendEffect)
{
  std::array values {-1, 0};
  SET_RETURN_SEQ(SDL_JoystickSendEffect, values.data(), cen::isize(values));

  ASSERT_FALSE(joystick.send_effect(nullptr, 24));
  ASSERT_EQ(1u, SDL_JoystickSendEffect_fake.call_count);
  ASSERT_EQ(24, SDL_JoystickSendEffect_fake.arg2_val);

  ASSERT_TRUE(joystick.send_effect(nullptr, 42));
  ASSERT_EQ(2u, SDL_JoystickSendEffect_fake.call_count);
  ASSERT_EQ(42, SDL_JoystickSendEffect_fake.arg2_val);
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 16)

#if SDL_VERSION_ATLEAST(2, 0, 18)

TEST_F(JoystickTest, HasRumble)
{
  std::array values {SDL_FALSE, SDL_TRUE};
  SET_RETURN_SEQ(SDL_JoystickHasRumble, values.data(), cen::isize(values));

  ASSERT_FALSE(joystick.has_rumble());
  ASSERT_TRUE(joystick.has_rumble());

  ASSERT_EQ(2u, SDL_JoystickHasRumble_fake.call_count);
}

TEST_F(JoystickTest, HasRumbleTriggers)
{
  std::array values {SDL_FALSE, SDL_TRUE};
  SET_RETURN_SEQ(SDL_JoystickHasRumbleTriggers, values.data(), cen::isize(values));

  ASSERT_FALSE(joystick.has_rumble_triggers());
  ASSERT_TRUE(joystick.has_rumble_triggers());

  ASSERT_EQ(2u, SDL_JoystickHasRumbleTriggers_fake.call_count);
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 18)

#if SDL_VERSION_ATLEAST(2, 24, 0)

TEST_F(JoystickTest, Path)
{
  const char* path [[maybe_unused]] = joystick.path();
  ASSERT_EQ(1u, SDL_JoystickPath_fake.call_count);
}

TEST_F(JoystickTest, PathForIndex)
{
  const char* path [[maybe_unused]] = cen::joystick::path(0);
  ASSERT_EQ(1u, SDL_JoystickPathForIndex_fake.call_count);
}

TEST_F(JoystickTest, FirmwareVersion)
{
  std::array<Uint16, 2> values {0, 42};
  SET_RETURN_SEQ(SDL_JoystickGetFirmwareVersion, values.data(), cen::isize(values));

  ASSERT_FALSE(joystick.firmware_version().has_value());
  ASSERT_EQ(42, joystick.firmware_version());

  ASSERT_EQ(2u, SDL_JoystickGetFirmwareVersion_fake.call_count);
}

#endif  // SDL_VERSION_ATLEAST(2, 24, 0)
