#include "input/joystick.hpp"

#include <fff.h>
#include <gtest/gtest.h>

#include <array>  // array

#include "core/integers.hpp"
#include "core_mocks.hpp"
#include "video/colors.hpp"

using namespace cen::literals;

// clang-format off
extern "C" {
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
}
// clang-format on

using namespace cen::literals;

class JoystickTest : public testing::Test
{
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
  }

  cen::joystick_handle m_joystick{nullptr};
};

TEST_F(JoystickTest, FromInstanceId)
{
  const auto handle [[maybe_unused]] = cen::joystick_handle::from_instance_id(0);

  ASSERT_EQ(1, SDL_JoystickFromInstanceID_fake.call_count);
}

TEST_F(JoystickTest, Rumble)
{
  m_joystick.rumble(10, 20, 5_ms);
  ASSERT_EQ(1, SDL_JoystickRumble_fake.call_count);
  ASSERT_EQ(10, SDL_JoystickRumble_fake.arg1_val);
  ASSERT_EQ(20, SDL_JoystickRumble_fake.arg2_val);
  ASSERT_EQ(5, SDL_JoystickRumble_fake.arg3_val);
}

TEST_F(JoystickTest, PlayerIndex)
{
  std::array values{-1, 7};
  SET_RETURN_SEQ(SDL_JoystickGetPlayerIndex, values.data(), cen::isize(values));

  ASSERT_FALSE(m_joystick.player_index().has_value());
  ASSERT_EQ(7, m_joystick.player_index());

  ASSERT_EQ(2, SDL_JoystickGetPlayerIndex_fake.call_count);
}

TEST_F(JoystickTest, PlayerIndexStatic)
{
  std::array values{-1, 42};
  SET_RETURN_SEQ(SDL_JoystickGetDevicePlayerIndex, values.data(), cen::isize(values));

  ASSERT_FALSE(cen::joystick::player_index(0).has_value());
  ASSERT_EQ(42, cen::joystick::player_index(0));

  ASSERT_EQ(2, SDL_JoystickGetDevicePlayerIndex_fake.call_count);
}

TEST_F(JoystickTest, Type)
{
  const auto type [[maybe_unused]] = m_joystick.type();
  ASSERT_EQ(1, SDL_JoystickGetType_fake.call_count);
}

TEST_F(JoystickTest, TypeStatic)
{
  const auto type [[maybe_unused]] = cen::joystick::type(0);
  ASSERT_EQ(1, SDL_JoystickGetDeviceType_fake.call_count);
}

TEST_F(JoystickTest, Vendor)
{
  std::array values{0_u16, 4_u16};
  SET_RETURN_SEQ(SDL_JoystickGetVendor, values.data(), cen::isize(values));

  ASSERT_FALSE(m_joystick.vendor().has_value());
  ASSERT_EQ(4, m_joystick.vendor());

  ASSERT_EQ(2, SDL_JoystickGetVendor_fake.call_count);
}

TEST_F(JoystickTest, VendorStatic)
{
  std::array values{0_u16, 4_u16};
  SET_RETURN_SEQ(SDL_JoystickGetDeviceVendor, values.data(), cen::isize(values));

  ASSERT_FALSE(cen::joystick::vendor(0).has_value());
  ASSERT_EQ(4, cen::joystick::vendor(0));

  ASSERT_EQ(2, SDL_JoystickGetDeviceVendor_fake.call_count);
}

TEST_F(JoystickTest, Product)
{
  std::array values{0_u16, 6_u16};
  SET_RETURN_SEQ(SDL_JoystickGetProduct, values.data(), cen::isize(values));

  ASSERT_FALSE(m_joystick.product().has_value());
  ASSERT_EQ(6, m_joystick.product());

  ASSERT_EQ(2, SDL_JoystickGetProduct_fake.call_count);
}

TEST_F(JoystickTest, ProductStatic)
{
  std::array values{0_u16, 8_u16};
  SET_RETURN_SEQ(SDL_JoystickGetDeviceProduct, values.data(), cen::isize(values));

  ASSERT_FALSE(cen::joystick::product(0).has_value());
  ASSERT_EQ(8, cen::joystick::product(0));

  ASSERT_EQ(2, SDL_JoystickGetDeviceProduct_fake.call_count);
}

TEST_F(JoystickTest, ProductVersion)
{
  std::array values{0_u16, 54_u16};
  SET_RETURN_SEQ(SDL_JoystickGetProductVersion, values.data(), cen::isize(values));

  ASSERT_FALSE(m_joystick.product_version().has_value());
  ASSERT_EQ(54, m_joystick.product_version());

  ASSERT_EQ(2, SDL_JoystickGetProductVersion_fake.call_count);
}

TEST_F(JoystickTest, ProductVersionStatic)
{
  std::array values{0_u16, 12_u16};
  SET_RETURN_SEQ(SDL_JoystickGetDeviceProductVersion, values.data(), cen::isize(values));

  ASSERT_FALSE(cen::joystick::product_version(0).has_value());
  ASSERT_EQ(12, cen::joystick::product_version(0));

  ASSERT_EQ(2, SDL_JoystickGetDeviceProductVersion_fake.call_count);
}

TEST_F(JoystickTest, GetBallAxisChange)
{
  std::array values{-1, 0};
  SET_RETURN_SEQ(SDL_JoystickGetBall, values.data(), cen::isize(values));

  ASSERT_FALSE(m_joystick.get_ball_axis_change(0).has_value());
  ASSERT_TRUE(m_joystick.get_ball_axis_change(0).has_value());

  ASSERT_EQ(2, SDL_JoystickGetBall_fake.call_count);
}

TEST_F(JoystickTest, AxisPos)
{
  std::array values{0_i16, 123_i16};
  SET_RETURN_SEQ(SDL_JoystickGetAxis, values.data(), cen::isize(values));

  ASSERT_EQ(0, m_joystick.axis_pos(0));
  ASSERT_EQ(123, m_joystick.axis_pos(0));
  ASSERT_EQ(2, SDL_JoystickGetAxis_fake.call_count);
}

TEST_F(JoystickTest, AxisInitialState)
{
  std::array values{SDL_FALSE, SDL_TRUE};
  SET_RETURN_SEQ(SDL_JoystickGetAxisInitialState, values.data(), cen::isize(values));

  ASSERT_FALSE(m_joystick.axis_initial_state(0).has_value());
  ASSERT_TRUE(m_joystick.axis_initial_state(0).has_value());

  ASSERT_EQ(2, SDL_JoystickGetAxisInitialState_fake.call_count);
}

TEST_F(JoystickTest, IsAttached)
{
  const auto attached [[maybe_unused]] = m_joystick.is_attached();
  ASSERT_EQ(1, SDL_JoystickGetAttached_fake.call_count);
}

TEST_F(JoystickTest, HatCount)
{
  const auto count [[maybe_unused]] = m_joystick.hat_count();
  ASSERT_EQ(1, SDL_JoystickNumHats_fake.call_count);
}

TEST_F(JoystickTest, AxisCount)
{
  const auto count [[maybe_unused]] = m_joystick.axis_count();
  ASSERT_EQ(1, SDL_JoystickNumAxes_fake.call_count);
}

TEST_F(JoystickTest, TrackballCount)
{
  const auto count [[maybe_unused]] = m_joystick.trackball_count();
  ASSERT_EQ(1, SDL_JoystickNumBalls_fake.call_count);
}

TEST_F(JoystickTest, ButtonCount)
{
  const auto count [[maybe_unused]] = m_joystick.button_count();
  ASSERT_EQ(1, SDL_JoystickNumButtons_fake.call_count);
}

TEST_F(JoystickTest, InstanceId)
{
  const auto id [[maybe_unused]] = m_joystick.instance_id();
  ASSERT_EQ(1, SDL_JoystickInstanceID_fake.call_count);
}

TEST_F(JoystickTest, InstanceIdStatic)
{
  std::array values{-1, 3};
  SET_RETURN_SEQ(SDL_JoystickGetDeviceInstanceID, values.data(), cen::isize(values));

  ASSERT_FALSE(cen::joystick::instance_id(0).has_value());
  ASSERT_EQ(3, cen::joystick::instance_id(0));

  ASSERT_EQ(2, SDL_JoystickGetDeviceInstanceID_fake.call_count);
}

TEST_F(JoystickTest, Guid)
{
  const auto id [[maybe_unused]] = m_joystick.guid();
  ASSERT_EQ(1, SDL_JoystickGetGUID_fake.call_count);
}

TEST_F(JoystickTest, GuidStatic)
{
  const auto name [[maybe_unused]] = cen::joystick::guid(0);
  ASSERT_EQ(1, SDL_JoystickGetDeviceGUID_fake.call_count);
}

TEST_F(JoystickTest, Name)
{
  const auto name [[maybe_unused]] = m_joystick.name();
  ASSERT_EQ(1, SDL_JoystickName_fake.call_count);
}

TEST_F(JoystickTest, GetPower)
{
  const auto power [[maybe_unused]] = m_joystick.get_power();
  ASSERT_EQ(1, SDL_JoystickCurrentPowerLevel_fake.call_count);
}

TEST_F(JoystickTest, GetButtonState)
{
  const auto state [[maybe_unused]] = m_joystick.get_button_state(0);
  ASSERT_EQ(1, SDL_JoystickGetButton_fake.call_count);
}

TEST_F(JoystickTest, GetHatState)
{
  const auto state [[maybe_unused]] = m_joystick.get_hat_state(0);
  ASSERT_EQ(1, SDL_JoystickGetHat_fake.call_count);
}

TEST_F(JoystickTest, Update)
{
  cen::joystick::update();
  ASSERT_EQ(1, SDL_JoystickUpdate_fake.call_count);
}

TEST_F(JoystickTest, Lock)
{
  cen::joystick::lock();
  ASSERT_EQ(1, SDL_LockJoysticks_fake.call_count);
}

TEST_F(JoystickTest, Unlock)
{
  cen::joystick::unlock();
  ASSERT_EQ(1, SDL_UnlockJoysticks_fake.call_count);
}

TEST_F(JoystickTest, SetPolling)
{
  cen::joystick::set_polling(true);
  ASSERT_EQ(SDL_ENABLE, SDL_JoystickEventState_fake.arg0_val);

  cen::joystick::set_polling(false);
  ASSERT_EQ(SDL_DISABLE, SDL_JoystickEventState_fake.arg0_val);

  ASSERT_EQ(2, SDL_JoystickEventState_fake.call_count);
}

TEST_F(JoystickTest, IsPolling)
{
  const auto isPolling [[maybe_unused]] = cen::joystick::is_polling();

  ASSERT_EQ(SDL_QUERY, SDL_JoystickEventState_fake.arg0_val);
  ASSERT_EQ(1, SDL_JoystickEventState_fake.call_count);
}

TEST_F(JoystickTest, Count)
{
  std::array values{-1, 7};
  SET_RETURN_SEQ(SDL_NumJoysticks, values.data(), cen::isize(values));

  ASSERT_FALSE(cen::joystick::count().has_value());
  ASSERT_EQ(7, cen::joystick::count());

  ASSERT_EQ(2, SDL_NumJoysticks_fake.call_count);
}

TEST_F(JoystickTest, GuidFromString)
{
  {
    const auto id [[maybe_unused]] = cen::joystick::guid_from_string("");
    ASSERT_EQ(1, SDL_JoystickGetGUIDFromString_fake.call_count);
  }

  {
    using namespace std::string_literals;
    const auto id [[maybe_unused]] = cen::joystick::guid_from_string(""s);
    ASSERT_EQ(2, SDL_JoystickGetGUIDFromString_fake.call_count);
  }
}

#if SDL_VERSION_ATLEAST(2, 0, 12)

TEST_F(JoystickTest, FromPlayerIndex)
{
  const auto handle [[maybe_unused]] = cen::joystick_handle::from_player_index(0);

  ASSERT_EQ(1, SDL_JoystickFromPlayerIndex_fake.call_count);
}

TEST_F(JoystickTest, SetPlayerIndex)
{
  m_joystick.set_player_index(7);
  ASSERT_EQ(1, SDL_JoystickSetPlayerIndex_fake.call_count);
  ASSERT_EQ(7, SDL_JoystickSetPlayerIndex_fake.arg1_val);
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

#if SDL_VERSION_ATLEAST(2, 0, 14)

TEST_F(JoystickTest, RumbleTriggers)
{
  std::array values{-1, 0};
  SET_RETURN_SEQ(SDL_JoystickRumbleTriggers, values.data(), cen::isize(values));

  ASSERT_FALSE(m_joystick.rumble_triggers(12, 34, 56_ms));
  ASSERT_TRUE(m_joystick.rumble_triggers(12, 34, 56_ms));

  ASSERT_EQ(12, SDL_JoystickRumbleTriggers_fake.arg1_val);
  ASSERT_EQ(34, SDL_JoystickRumbleTriggers_fake.arg2_val);
  ASSERT_EQ(56, SDL_JoystickRumbleTriggers_fake.arg3_val);

  ASSERT_EQ(2, SDL_JoystickRumbleTriggers_fake.call_count);
}

TEST_F(JoystickTest, SetLED)
{
  std::array values{-1, 0};
  SET_RETURN_SEQ(SDL_JoystickSetLED, values.data(), cen::isize(values));

  const auto color = cen::colors::magenta;
  ASSERT_FALSE(m_joystick.set_led(color));
  ASSERT_TRUE(m_joystick.set_led(color));
  ASSERT_EQ(2, SDL_JoystickSetLED_fake.call_count);
}

TEST_F(JoystickTest, HasLED)
{
  std::array values{SDL_FALSE, SDL_TRUE};
  SET_RETURN_SEQ(SDL_JoystickHasLED, values.data(), cen::isize(values));

  ASSERT_FALSE(m_joystick.has_led());
  ASSERT_TRUE(m_joystick.has_led());
  ASSERT_EQ(2, SDL_JoystickHasLED_fake.call_count);
}

TEST_F(JoystickTest, Serial)
{
  const auto name [[maybe_unused]] = m_joystick.serial();
  ASSERT_EQ(1, SDL_JoystickGetSerial_fake.call_count);
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)