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

#include "centurion/sensor.hpp"

#include <fff.h>
#include <gtest/gtest.h>

#include <array>     // array
#include <iostream>  // cout

#include "core_mocks.hpp"

extern "C" {
FAKE_VOID_FUNC(SDL_SensorUpdate)
FAKE_VOID_FUNC(SDL_LockSensors)
FAKE_VOID_FUNC(SDL_UnlockSensors)
FAKE_VALUE_FUNC(int, SDL_NumSensors)
FAKE_VALUE_FUNC(int, SDL_SensorGetData, SDL_Sensor*, float*, int)

FAKE_VALUE_FUNC(SDL_SensorID, SDL_SensorGetInstanceID, SDL_Sensor*)
FAKE_VALUE_FUNC(SDL_SensorID, SDL_SensorGetDeviceInstanceID, int)

FAKE_VALUE_FUNC(SDL_SensorType, SDL_SensorGetType, SDL_Sensor*)
FAKE_VALUE_FUNC(SDL_SensorType, SDL_SensorGetDeviceType, int)

FAKE_VALUE_FUNC(int, SDL_SensorGetNonPortableType, SDL_Sensor*)
FAKE_VALUE_FUNC(int, SDL_SensorGetDeviceNonPortableType, int)

FAKE_VALUE_FUNC(const char*, SDL_SensorGetName, SDL_Sensor*)
FAKE_VALUE_FUNC(const char*, SDL_SensorGetDeviceName, int)
}

class SensorTest : public testing::Test {
 public:
  void SetUp() override
  {
    mocks::reset_core();

    RESET_FAKE(SDL_SensorUpdate)
    RESET_FAKE(SDL_LockSensors)
    RESET_FAKE(SDL_UnlockSensors)
    RESET_FAKE(SDL_NumSensors)
    RESET_FAKE(SDL_SensorGetData)
    RESET_FAKE(SDL_SensorGetInstanceID)
    RESET_FAKE(SDL_SensorGetDeviceInstanceID)
    RESET_FAKE(SDL_SensorGetType)
    RESET_FAKE(SDL_SensorGetDeviceType)
    RESET_FAKE(SDL_SensorGetNonPortableType)
    RESET_FAKE(SDL_SensorGetDeviceNonPortableType)
    RESET_FAKE(SDL_SensorGetName)
    RESET_FAKE(SDL_SensorGetDeviceName)
  }

  cen::sensor_handle m_sensor {nullptr};
};

TEST_F(SensorTest, ID)
{
  const auto id [[maybe_unused]] = m_sensor.id();
  ASSERT_EQ(1u, SDL_SensorGetInstanceID_fake.call_count);
}

TEST_F(SensorTest, Name)
{
  const auto name [[maybe_unused]] = m_sensor.name();
  ASSERT_EQ(1u, SDL_SensorGetName_fake.call_count);
}

TEST_F(SensorTest, Type)
{
  const auto type [[maybe_unused]] = m_sensor.type();
  ASSERT_EQ(1u, SDL_SensorGetType_fake.call_count);
}

TEST_F(SensorTest, NonPortableType)
{
  const auto type [[maybe_unused]] = m_sensor.non_portable_type();
  ASSERT_EQ(1u, SDL_SensorGetNonPortableType_fake.call_count);
}

TEST_F(SensorTest, Data)
{
  std::array values {-1, 0};
  SET_RETURN_SEQ(SDL_SensorGetData, values.data(), cen::isize(values));

  ASSERT_FALSE(m_sensor.data<3>());
  ASSERT_TRUE(m_sensor.data<3>());
  ASSERT_EQ(2u, SDL_SensorGetData_fake.call_count);
}

TEST_F(SensorTest, IDFromIndex)
{
  std::array values {-1, 0};
  SET_RETURN_SEQ(SDL_SensorGetDeviceInstanceID, values.data(), cen::isize(values));

  ASSERT_FALSE(cen::sensor::id(0));
  ASSERT_TRUE(cen::sensor::id(0));
  ASSERT_EQ(2u, SDL_SensorGetDeviceInstanceID_fake.call_count);
}

TEST_F(SensorTest, NameFromIndex)
{
  const auto name [[maybe_unused]] = cen::sensor::name(0);
  ASSERT_EQ(1u, SDL_SensorGetDeviceName_fake.call_count);
}

TEST_F(SensorTest, TypeFromIndex)
{
  const auto type [[maybe_unused]] = cen::sensor::type(0);
  ASSERT_EQ(1u, SDL_SensorGetDeviceType_fake.call_count);
}

TEST_F(SensorTest, NonPortableTypeFromIndex)
{
  std::array values {-1, 0};
  SET_RETURN_SEQ(SDL_SensorGetDeviceNonPortableType, values.data(), cen::isize(values));

  ASSERT_FALSE(cen::sensor::non_portable_type(0));
  ASSERT_TRUE(cen::sensor::non_portable_type(0));
  ASSERT_EQ(2u, SDL_SensorGetDeviceNonPortableType_fake.call_count);
}

TEST_F(SensorTest, Update)
{
  cen::sensor::update();
  ASSERT_EQ(1u, SDL_SensorUpdate_fake.call_count);
}

TEST_F(SensorTest, Count)
{
  const auto count [[maybe_unused]] = cen::sensor::count();
  ASSERT_EQ(1u, SDL_NumSensors_fake.call_count);
}

TEST_F(SensorTest, StreamOperator)
{
  std::cout << m_sensor << '\n';
}

#if SDL_VERSION_ATLEAST(2, 0, 14)

TEST_F(SensorTest, Lock)
{
  cen::sensor::lock();
  ASSERT_EQ(1u, SDL_LockSensors_fake.call_count);
}

TEST_F(SensorTest, Unlock)
{
  cen::sensor::unlock();
  ASSERT_EQ(1u, SDL_UnlockSensors_fake.call_count);
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)
