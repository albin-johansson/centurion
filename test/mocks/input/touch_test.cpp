#include "input/touch.hpp"

#include <fff.h>
#include <gtest/gtest.h>

#include "core_mocks.hpp"

// clang-format off
extern "C" {
FAKE_VALUE_FUNC(int, SDL_GetNumTouchDevices)
FAKE_VALUE_FUNC(SDL_TouchID, SDL_GetTouchDevice, int)
FAKE_VALUE_FUNC(SDL_TouchDeviceType, SDL_GetTouchDeviceType, SDL_TouchID)
FAKE_VALUE_FUNC(int, SDL_GetNumTouchFingers, SDL_TouchID)
FAKE_VALUE_FUNC(SDL_Finger*, SDL_GetTouchFinger, SDL_TouchID, int)
}
// clang-format on

class TouchTest : public testing::Test
{
 protected:
  void SetUp() override
  {
    mocks::reset_core();

    RESET_FAKE(SDL_GetNumTouchDevices);
    RESET_FAKE(SDL_GetTouchDevice);
    RESET_FAKE(SDL_GetTouchDeviceType);
    RESET_FAKE(SDL_GetNumTouchFingers);
    RESET_FAKE(SDL_GetTouchFinger);
  }
};

TEST_F(TouchTest, DeviceCount)
{
  const auto count [[maybe_unused]] = cen::touch::device_count();
  ASSERT_EQ(1, SDL_GetNumTouchDevices_fake.call_count);
}

TEST_F(TouchTest, GetDevice)
{
  SDL_GetTouchDevice_fake.return_val = 3;
  ASSERT_EQ(3, cen::touch::get_device(7));
  ASSERT_EQ(1, SDL_GetTouchDevice_fake.call_count);
  ASSERT_EQ(7, SDL_GetTouchDevice_fake.arg0_val);

  SDL_GetTouchDevice_fake.return_val = 0;
  ASSERT_FALSE(cen::touch::get_device(0).has_value());
}

TEST_F(TouchTest, TypeOf)
{
  const auto type [[maybe_unused]] = cen::touch::type_of(0);
  ASSERT_EQ(1, SDL_GetTouchDeviceType_fake.call_count);
}

TEST_F(TouchTest, FingerCount)
{
  const auto count [[maybe_unused]] = cen::touch::finger_count(0);
  ASSERT_EQ(1, SDL_GetNumTouchFingers_fake.call_count);
}

TEST_F(TouchTest, GetFinger)
{
  ASSERT_FALSE(cen::touch::get_finger(4, 2).has_value());
  ASSERT_EQ(1, SDL_GetTouchFinger_fake.call_count);
  ASSERT_EQ(4, SDL_GetTouchFinger_fake.arg0_val);
  ASSERT_EQ(2, SDL_GetTouchFinger_fake.arg1_val);

  SDL_Finger finger{};
  SDL_GetTouchFinger_fake.return_val = &finger;
  ASSERT_TRUE(cen::touch::get_finger(3, 6).has_value());
  ASSERT_EQ(3, SDL_GetTouchFinger_fake.arg0_val);
  ASSERT_EQ(6, SDL_GetTouchFinger_fake.arg1_val);
}