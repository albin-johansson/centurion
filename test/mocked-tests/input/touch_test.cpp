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

#include "centurion/touch.hpp"

#include <fff.h>
#include <gtest/gtest.h>

#include "core_mocks.hpp"

extern "C"
{
  FAKE_VALUE_FUNC(int, SDL_GetNumTouchDevices)
  FAKE_VALUE_FUNC(SDL_TouchID, SDL_GetTouchDevice, int)
  FAKE_VALUE_FUNC(SDL_TouchDeviceType, SDL_GetTouchDeviceType, SDL_TouchID)
  FAKE_VALUE_FUNC(int, SDL_GetNumTouchFingers, SDL_TouchID)
  FAKE_VALUE_FUNC(SDL_Finger*, SDL_GetTouchFinger, SDL_TouchID, int)
}

class TouchTest : public testing::Test {
 protected:
  void SetUp() override
  {
    mocks::reset_core();

    RESET_FAKE(SDL_GetNumTouchDevices)
    RESET_FAKE(SDL_GetTouchDevice)
    RESET_FAKE(SDL_GetTouchDeviceType)
    RESET_FAKE(SDL_GetNumTouchFingers)
    RESET_FAKE(SDL_GetTouchFinger)
  }
};

TEST_F(TouchTest, TouchDeviceCount)
{
  const auto count [[maybe_unused]] = cen::touch_device_count();
  ASSERT_EQ(1u, SDL_GetNumTouchDevices_fake.call_count);
}

TEST_F(TouchTest, GetTouchDevice)
{
  SDL_GetTouchDevice_fake.return_val = 3;
  ASSERT_EQ(3, cen::get_touch_device(7));
  ASSERT_EQ(1u, SDL_GetTouchDevice_fake.call_count);
  ASSERT_EQ(7, SDL_GetTouchDevice_fake.arg0_val);

  SDL_GetTouchDevice_fake.return_val = 0;
  ASSERT_FALSE(cen::get_touch_device(0).has_value());
}

TEST_F(TouchTest, GetTouchType)
{
  const auto type [[maybe_unused]] = cen::get_touch_type(0);
  ASSERT_EQ(1u, SDL_GetTouchDeviceType_fake.call_count);
}

TEST_F(TouchTest, GetTouchFingerCount)
{
  const auto count [[maybe_unused]] = cen::get_touch_finger_count(0);
  ASSERT_EQ(1u, SDL_GetNumTouchFingers_fake.call_count);
}

TEST_F(TouchTest, Finger)
{
  ASSERT_FALSE(cen::finger::find(4, 2).has_value());
  ASSERT_EQ(1u, SDL_GetTouchFinger_fake.call_count);
  ASSERT_EQ(4, SDL_GetTouchFinger_fake.arg0_val);
  ASSERT_EQ(2, SDL_GetTouchFinger_fake.arg1_val);

  SDL_Finger expected;
  expected.id = 12;
  expected.x = 42;
  expected.y = 28;
  expected.pressure = 0.8f;
  SDL_GetTouchFinger_fake.return_val = &expected;

  const auto finger = cen::finger::find(1, 2);
  ASSERT_EQ(1, SDL_GetTouchFinger_fake.arg0_val);
  ASSERT_EQ(2, SDL_GetTouchFinger_fake.arg1_val);

  ASSERT_TRUE(finger.has_value());
  ASSERT_EQ(expected.id, finger->id());
  ASSERT_EQ(expected.x, finger->x());
  ASSERT_EQ(expected.y, finger->y());
  ASSERT_EQ(expected.pressure, finger->pressure());
}