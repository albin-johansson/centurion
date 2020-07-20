#include "touch.hpp"

#include <catch.hpp>

using namespace centurion;
using namespace touch;

TEST_CASE("DeviceType enum", "[Touch]")
{
  SECTION("Operator ==")
  {
    CHECK(device_type::invalid == SDL_TOUCH_DEVICE_INVALID);
    CHECK(device_type::direct == SDL_TOUCH_DEVICE_DIRECT);
    CHECK(device_type::indirect_absolute == SDL_TOUCH_DEVICE_INDIRECT_ABSOLUTE);
    CHECK(device_type::indirect_relative == SDL_TOUCH_DEVICE_INDIRECT_RELATIVE);

    CHECK(SDL_TOUCH_DEVICE_INVALID == device_type::invalid);
    CHECK(SDL_TOUCH_DEVICE_DIRECT == device_type::direct);
    CHECK(SDL_TOUCH_DEVICE_INDIRECT_ABSOLUTE == device_type::indirect_absolute);
    CHECK(SDL_TOUCH_DEVICE_INDIRECT_RELATIVE == device_type::indirect_relative);

    CHECK(!(device_type::indirect_absolute == SDL_TOUCH_DEVICE_DIRECT));
  }

  SECTION("Operator !=")
  {
    CHECK(device_type::invalid != SDL_TOUCH_DEVICE_INDIRECT_ABSOLUTE);
    CHECK(SDL_TOUCH_DEVICE_DIRECT != device_type::invalid);
  }
}

TEST_CASE("touch::num_devices", "[Touch]")
{
  CHECK(num_devices() == SDL_GetNumTouchDevices());
}

TEST_CASE("touch::get_device", "[!mayfail][Touch]")
{
  const auto device = get_device(0);
  CHECK(!device.has_value());
}

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
