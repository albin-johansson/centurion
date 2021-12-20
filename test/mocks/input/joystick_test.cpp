#include "input/joystick.hpp"

#include <fff.h>
#include <gtest/gtest.h>

#include <array>  // array

#include "common.hpp"
#include "core_mocks.hpp"
#include "color.hpp"

using namespace cen::literals;

extern "C"
{
  FAKE_VOID_FUNC(SDL_JoystickUpdate)
  FAKE_VOID_FUNC(SDL_LockJoysticks)
  FAKE_VOID_FUNC(SDL_UnlockJoysticks)
  FAKE_VOID_FUNC(SDL_JoystickSetPlayerIndex, SDL_Joystick*, int)

  FAKE_VALUE_FUNC(int, SDL_JoystickRumble, SDL_Joystick*, Uint16, Uint16, Uint32)
  FAKE_VALUE_FUNC(int, SDL_JoystickRumbleTriggers, SDL_Joystick*, Uint16, Uint16, Uint32)

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
  FAKE_VALUE_FUNC(const char*, SDL_JoystickGetSerial, SDL_Joystick*)
  FAKE_VALUE_FUNC(int, SDL_JoystickEventState, int)
  FAKE_VALUE_FUNC(SDL_JoystickGUID, SDL_JoystickGetGUIDFromString, const char*)

#if SDL_VERSION_ATLEAST(2, 0, 16)
  FAKE_VALUE_FUNC(int, SDL_JoystickSendEffect, SDL_Joystick*, const void*, int)
#endif  // SDL_VERSION_ATLEAST(2, 0, 16)
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
    RESET_FAKE(SDL_JoystickRumbleTriggers)
    RESET_FAKE(SDL_JoystickSetPlayerIndex)

    RESET_FAKE(SDL_JoystickFromInstanceID)
    RESET_FAKE(SDL_JoystickFromPlayerIndex)

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
    RESET_FAKE(SDL_JoystickSetLED)
    RESET_FAKE(SDL_JoystickGetAxis)
    RESET_FAKE(SDL_JoystickGetHat)
    RESET_FAKE(SDL_JoystickGetButton)
    RESET_FAKE(SDL_JoystickGetAxisInitialState)
    RESET_FAKE(SDL_JoystickGetAttached)
    RESET_FAKE(SDL_JoystickHasLED)
    RESET_FAKE(SDL_JoystickCurrentPowerLevel)
    RESET_FAKE(SDL_JoystickNumHats)
    RESET_FAKE(SDL_JoystickNumAxes)
    RESET_FAKE(SDL_JoystickNumBalls)
    RESET_FAKE(SDL_JoystickNumButtons)
    RESET_FAKE(SDL_JoystickName)
    RESET_FAKE(SDL_JoystickGetSerial)
    RESET_FAKE(SDL_JoystickEventState)
    RESET_FAKE(SDL_JoystickGetGUIDFromString)

#if SDL_VERSION_ATLEAST(2, 0, 16)
    RESET_FAKE(SDL_JoystickSendEffect)
#endif  // SDL_VERSION_ATLEAST(2, 0, 16)
  }

  cen::JoystickHandle joystick{nullptr};
};

TEST_F(JoystickTest, FromId)
{
  const auto handle [[maybe_unused]] = cen::JoystickHandle::FromID(0);

  ASSERT_EQ(1u, SDL_JoystickFromInstanceID_fake.call_count);
}

TEST_F(JoystickTest, Rumble)
{
  joystick.Rumble(10, 20, 5_ms);
  ASSERT_EQ(1u, SDL_JoystickRumble_fake.call_count);
  ASSERT_EQ(10u, SDL_JoystickRumble_fake.arg1_val);
  ASSERT_EQ(20u, SDL_JoystickRumble_fake.arg2_val);
  ASSERT_EQ(5u, SDL_JoystickRumble_fake.arg3_val);
}

TEST_F(JoystickTest, PlayerIndex)
{
  std::array values{-1, 7};
  SET_RETURN_SEQ(SDL_JoystickGetPlayerIndex, values.data(), cen::isize(values));

  ASSERT_FALSE(joystick.GetPlayerIndex().has_value());
  ASSERT_EQ(7, joystick.GetPlayerIndex());

  ASSERT_EQ(2u, SDL_JoystickGetPlayerIndex_fake.call_count);
}

TEST_F(JoystickTest, PlayerIndexStatic)
{
  std::array values{-1, 42};
  SET_RETURN_SEQ(SDL_JoystickGetDevicePlayerIndex, values.data(), cen::isize(values));

  ASSERT_FALSE(cen::Joystick::GetPlayerIndex(0).has_value());
  ASSERT_EQ(42, cen::Joystick::GetPlayerIndex(0));

  ASSERT_EQ(2u, SDL_JoystickGetDevicePlayerIndex_fake.call_count);
}

TEST_F(JoystickTest, GetType)
{
  const auto type [[maybe_unused]] = joystick.GetType();
  ASSERT_EQ(1u, SDL_JoystickGetType_fake.call_count);
}

TEST_F(JoystickTest, GetTypeStatic)
{
  const auto type [[maybe_unused]] = cen::Joystick::GetType(0);
  ASSERT_EQ(1u, SDL_JoystickGetDeviceType_fake.call_count);
}

TEST_F(JoystickTest, GetVendor)
{
  std::array<Uint16, 2> values{0, 4};
  SET_RETURN_SEQ(SDL_JoystickGetVendor, values.data(), cen::isize(values));

  ASSERT_FALSE(joystick.GetVendor().has_value());
  ASSERT_EQ(4, joystick.GetVendor());

  ASSERT_EQ(2u, SDL_JoystickGetVendor_fake.call_count);
}

TEST_F(JoystickTest, GetVendorStatic)
{
  std::array<Uint16, 2> values{0, 4};
  SET_RETURN_SEQ(SDL_JoystickGetDeviceVendor, values.data(), cen::isize(values));

  ASSERT_FALSE(cen::Joystick::GetVendor(0).has_value());
  ASSERT_EQ(4, cen::Joystick::GetVendor(0));

  ASSERT_EQ(2u, SDL_JoystickGetDeviceVendor_fake.call_count);
}

TEST_F(JoystickTest, GetProduct)
{
  std::array<Uint16, 2> values{0, 6};
  SET_RETURN_SEQ(SDL_JoystickGetProduct, values.data(), cen::isize(values));

  ASSERT_FALSE(joystick.GetProduct().has_value());
  ASSERT_EQ(6, joystick.GetProduct());

  ASSERT_EQ(2u, SDL_JoystickGetProduct_fake.call_count);
}

TEST_F(JoystickTest, GetProductStatic)
{
  std::array<Uint16, 2> values{0, 8};
  SET_RETURN_SEQ(SDL_JoystickGetDeviceProduct, values.data(), cen::isize(values));

  ASSERT_FALSE(cen::Joystick::GetProduct(0).has_value());
  ASSERT_EQ(8, cen::Joystick::GetProduct(0));

  ASSERT_EQ(2u, SDL_JoystickGetDeviceProduct_fake.call_count);
}

TEST_F(JoystickTest, GetProductVersion)
{
  std::array<Uint16, 2> values{0, 54};
  SET_RETURN_SEQ(SDL_JoystickGetProductVersion, values.data(), cen::isize(values));

  ASSERT_FALSE(joystick.GetProductVersion().has_value());
  ASSERT_EQ(54, joystick.GetProductVersion());

  ASSERT_EQ(2u, SDL_JoystickGetProductVersion_fake.call_count);
}

TEST_F(JoystickTest, GetProductVersionStatic)
{
  std::array<Uint16, 2> values{0, 12};
  SET_RETURN_SEQ(SDL_JoystickGetDeviceProductVersion, values.data(), cen::isize(values));

  ASSERT_FALSE(cen::Joystick::GetProductVersion(0).has_value());
  ASSERT_EQ(12, cen::Joystick::GetProductVersion(0));

  ASSERT_EQ(2u, SDL_JoystickGetDeviceProductVersion_fake.call_count);
}

TEST_F(JoystickTest, GetBallAxisChange)
{
  std::array values{-1, 0};
  SET_RETURN_SEQ(SDL_JoystickGetBall, values.data(), cen::isize(values));

  ASSERT_FALSE(joystick.GetBallAxisChange(0).has_value());
  ASSERT_TRUE(joystick.GetBallAxisChange(0).has_value());

  ASSERT_EQ(2u, SDL_JoystickGetBall_fake.call_count);
}

TEST_F(JoystickTest, AxisPos)
{
  std::array<Sint16, 2> values{0, 123};
  SET_RETURN_SEQ(SDL_JoystickGetAxis, values.data(), cen::isize(values));

  ASSERT_EQ(0, joystick.GetAxis(0));
  ASSERT_EQ(123, joystick.GetAxis(0));
  ASSERT_EQ(2u, SDL_JoystickGetAxis_fake.call_count);
}

TEST_F(JoystickTest, GetAxisInitialState)
{
  std::array values{SDL_FALSE, SDL_TRUE};
  SET_RETURN_SEQ(SDL_JoystickGetAxisInitialState, values.data(), cen::isize(values));

  ASSERT_FALSE(joystick.GetAxisInitialState(0).has_value());
  ASSERT_TRUE(joystick.GetAxisInitialState(0).has_value());

  ASSERT_EQ(2u, SDL_JoystickGetAxisInitialState_fake.call_count);
}

TEST_F(JoystickTest, IsAttached)
{
  const auto attached [[maybe_unused]] = joystick.IsAttached();
  ASSERT_EQ(1u, SDL_JoystickGetAttached_fake.call_count);
}

TEST_F(JoystickTest, GetHats)
{
  const auto count [[maybe_unused]] = joystick.GetHats();
  ASSERT_EQ(1u, SDL_JoystickNumHats_fake.call_count);
}

TEST_F(JoystickTest, GetAxes)
{
  const auto count [[maybe_unused]] = joystick.GetAxes();
  ASSERT_EQ(1u, SDL_JoystickNumAxes_fake.call_count);
}

TEST_F(JoystickTest, GetTrackballs)
{
  const auto count [[maybe_unused]] = joystick.GetTrackballs();
  ASSERT_EQ(1u, SDL_JoystickNumBalls_fake.call_count);
}

TEST_F(JoystickTest, GetButtons)
{
  const auto count [[maybe_unused]] = joystick.GetButtons();
  ASSERT_EQ(1u, SDL_JoystickNumButtons_fake.call_count);
}

TEST_F(JoystickTest, GetID)
{
  const auto id [[maybe_unused]] = joystick.GetID();
  ASSERT_EQ(1u, SDL_JoystickInstanceID_fake.call_count);
}

TEST_F(JoystickTest, GetIDStatic)
{
  std::array values{-1, 3};
  SET_RETURN_SEQ(SDL_JoystickGetDeviceInstanceID, values.data(), cen::isize(values));

  ASSERT_FALSE(cen::Joystick::GetID(0).has_value());
  ASSERT_EQ(3, cen::Joystick::GetID(0));

  ASSERT_EQ(2u, SDL_JoystickGetDeviceInstanceID_fake.call_count);
}

TEST_F(JoystickTest, GetGUID)
{
  const auto id [[maybe_unused]] = joystick.GetGUID();
  ASSERT_EQ(1u, SDL_JoystickGetGUID_fake.call_count);
}

TEST_F(JoystickTest, GetGUIDStatic)
{
  const auto name [[maybe_unused]] = cen::Joystick::GetGUID(0);
  ASSERT_EQ(1u, SDL_JoystickGetDeviceGUID_fake.call_count);
}

TEST_F(JoystickTest, GetName)
{
  const auto name [[maybe_unused]] = joystick.GetName();
  ASSERT_EQ(1u, SDL_JoystickName_fake.call_count);
}

TEST_F(JoystickTest, GetPower)
{
  const auto power [[maybe_unused]] = joystick.GetPower();
  ASSERT_EQ(1u, SDL_JoystickCurrentPowerLevel_fake.call_count);
}

TEST_F(JoystickTest, GetButtonState)
{
  const auto state [[maybe_unused]] = joystick.GetButtonState(0);
  ASSERT_EQ(1u, SDL_JoystickGetButton_fake.call_count);
}

TEST_F(JoystickTest, GetHatState)
{
  const auto state [[maybe_unused]] = joystick.GetHatState(0);
  ASSERT_EQ(1u, SDL_JoystickGetHat_fake.call_count);
}

TEST_F(JoystickTest, Update)
{
  cen::Joystick::Update();
  ASSERT_EQ(1u, SDL_JoystickUpdate_fake.call_count);
}

TEST_F(JoystickTest, Lock)
{
  cen::Joystick::Lock();
  ASSERT_EQ(1u, SDL_LockJoysticks_fake.call_count);
}

TEST_F(JoystickTest, Unlock)
{
  cen::Joystick::Unlock();
  ASSERT_EQ(1u, SDL_UnlockJoysticks_fake.call_count);
}

TEST_F(JoystickTest, SetPolling)
{
  cen::Joystick::SetPolling(true);
  ASSERT_EQ(SDL_ENABLE, SDL_JoystickEventState_fake.arg0_val);

  cen::Joystick::SetPolling(false);
  ASSERT_EQ(SDL_DISABLE, SDL_JoystickEventState_fake.arg0_val);

  ASSERT_EQ(2u, SDL_JoystickEventState_fake.call_count);
}

TEST_F(JoystickTest, IsPolling)
{
  const auto isPolling [[maybe_unused]] = cen::Joystick::IsPolling();

  ASSERT_EQ(SDL_QUERY, SDL_JoystickEventState_fake.arg0_val);
  ASSERT_EQ(1u, SDL_JoystickEventState_fake.call_count);
}

TEST_F(JoystickTest, GetAmount)
{
  std::array values{-1, 7};
  SET_RETURN_SEQ(SDL_NumJoysticks, values.data(), cen::isize(values));

  ASSERT_FALSE(cen::Joystick::GetAmount().has_value());
  ASSERT_EQ(7, cen::Joystick::GetAmount());

  ASSERT_EQ(2u, SDL_NumJoysticks_fake.call_count);
}

TEST_F(JoystickTest, GetGuidFromString)
{
  {
    const auto id [[maybe_unused]] = cen::Joystick::GetGUID("");
    ASSERT_EQ(1u, SDL_JoystickGetGUIDFromString_fake.call_count);
  }

  {
    using namespace std::string_literals;
    const auto id [[maybe_unused]] = cen::Joystick::GetGUID(""s);
    ASSERT_EQ(2u, SDL_JoystickGetGUIDFromString_fake.call_count);
  }
}

#if SDL_VERSION_ATLEAST(2, 0, 12)

TEST_F(JoystickTest, FromPlayerIndex)
{
  const auto handle [[maybe_unused]] = cen::JoystickHandle::FromPlayerIndex(0);

  ASSERT_EQ(1u, SDL_JoystickFromPlayerIndex_fake.call_count);
}

TEST_F(JoystickTest, SetPlayerIndex)
{
  joystick.SetPlayerIndex(7);
  ASSERT_EQ(1u, SDL_JoystickSetPlayerIndex_fake.call_count);
  ASSERT_EQ(7, SDL_JoystickSetPlayerIndex_fake.arg1_val);
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

#if SDL_VERSION_ATLEAST(2, 0, 14)

TEST_F(JoystickTest, RumbleTriggers)
{
  std::array values{-1, 0};
  SET_RETURN_SEQ(SDL_JoystickRumbleTriggers, values.data(), cen::isize(values));

  ASSERT_FALSE(joystick.RumbleTriggers(12, 34, 56_ms));
  ASSERT_TRUE(joystick.RumbleTriggers(12, 34, 56_ms));

  ASSERT_EQ(12u, SDL_JoystickRumbleTriggers_fake.arg1_val);
  ASSERT_EQ(34u, SDL_JoystickRumbleTriggers_fake.arg2_val);
  ASSERT_EQ(56u, SDL_JoystickRumbleTriggers_fake.arg3_val);

  ASSERT_EQ(2u, SDL_JoystickRumbleTriggers_fake.call_count);
}

TEST_F(JoystickTest, SetLED)
{
  std::array values{-1, 0};
  SET_RETURN_SEQ(SDL_JoystickSetLED, values.data(), cen::isize(values));

  const auto color = cen::colors::magenta;
  ASSERT_FALSE(joystick.SetLED(color));
  ASSERT_TRUE(joystick.SetLED(color));
  ASSERT_EQ(2u, SDL_JoystickSetLED_fake.call_count);
}

TEST_F(JoystickTest, HasLED)
{
  std::array values{SDL_FALSE, SDL_TRUE};
  SET_RETURN_SEQ(SDL_JoystickHasLED, values.data(), cen::isize(values));

  ASSERT_FALSE(joystick.HasLED());
  ASSERT_TRUE(joystick.HasLED());
  ASSERT_EQ(2u, SDL_JoystickHasLED_fake.call_count);
}

TEST_F(JoystickTest, GetSerial)
{
  const auto name [[maybe_unused]] = joystick.GetSerial();
  ASSERT_EQ(1u, SDL_JoystickGetSerial_fake.call_count);
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

#if SDL_VERSION_ATLEAST(2, 0, 16)

TEST_F(JoystickTest, SendEffect)
{
  std::array values{-1, 0};
  SET_RETURN_SEQ(SDL_JoystickSendEffect, values.data(), cen::isize(values));

  ASSERT_FALSE(joystick.SendEffect(nullptr, 24));
  ASSERT_EQ(1u, SDL_JoystickSendEffect_fake.call_count);
  ASSERT_EQ(24, SDL_JoystickSendEffect_fake.arg2_val);

  ASSERT_TRUE(joystick.SendEffect(nullptr, 42));
  ASSERT_EQ(2u, SDL_JoystickSendEffect_fake.call_count);
  ASSERT_EQ(42, SDL_JoystickSendEffect_fake.arg2_val);
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 16)