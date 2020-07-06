#include "touch.h"

#include <catch.hpp>

using namespace centurion;
using namespace touch;

TEST_CASE("DeviceType enum", "[Touch]")
{
  SECTION("Operator ==")
  {
    CHECK(DeviceType::Invalid == SDL_TOUCH_DEVICE_INVALID);
    CHECK(DeviceType::Direct == SDL_TOUCH_DEVICE_DIRECT);
    CHECK(DeviceType::IndirectAbsolute == SDL_TOUCH_DEVICE_INDIRECT_ABSOLUTE);
    CHECK(DeviceType::IndirectRelative == SDL_TOUCH_DEVICE_INDIRECT_RELATIVE);

    CHECK(SDL_TOUCH_DEVICE_INVALID == DeviceType::Invalid);
    CHECK(SDL_TOUCH_DEVICE_DIRECT == DeviceType::Direct);
    CHECK(SDL_TOUCH_DEVICE_INDIRECT_ABSOLUTE == DeviceType::IndirectAbsolute);
    CHECK(SDL_TOUCH_DEVICE_INDIRECT_RELATIVE == DeviceType::IndirectRelative);

    CHECK(!(DeviceType::IndirectAbsolute == SDL_TOUCH_DEVICE_DIRECT));
  }

  SECTION("Operator !=")
  {
    CHECK(DeviceType::Invalid != SDL_TOUCH_DEVICE_INDIRECT_ABSOLUTE);
    CHECK(SDL_TOUCH_DEVICE_DIRECT != DeviceType::Invalid);
  }
}

TEST_CASE("touch::num_devices", "[Touch]")
{
  CHECK(num_devices() == SDL_GetNumTouchDevices());
}

#ifndef TRAVIS_TEST

TEST_CASE("touch::get_device", "[Touch]")
{
  const auto device = get_device(0);
  CHECK(!device.has_value());
}

#endif  // TRAVIS_TEST

TEST_CASE("touch::type_of", "[Touch]")
{
  CHECK(type_of(0) == SDL_GetTouchDeviceType(0));
}

TEST_CASE("touch::num_fingers", "[Touch]")
{
  CHECK(num_fingers(0) == SDL_GetNumTouchFingers(0));
}

TEST_CASE("touch::get_finger", "[Touch]")
{
  const auto finger = get_finger(0, 0);
  CHECK(!finger.has_value());
}

TEST_CASE("touch::touch_mouse_id", "[Touch]")
{
  CHECK(touch_mouse_id() == SDL_TOUCH_MOUSEID);
  CHECK(touch_mouse_id() != SDL_MOUSE_TOUCHID);
}

TEST_CASE("touch::mouse_touch_id", "[Touch]")
{
  CHECK(mouse_touch_id() == SDL_MOUSE_TOUCHID);
  CHECK(mouse_touch_id() != SDL_TOUCH_MOUSEID);
}
