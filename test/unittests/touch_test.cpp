#include "touch.hpp"

#include <catch.hpp>

#include "centurion_as_ctn.hpp"

TEST_CASE("device_type enum", "[touch]")
{
  using device_t = ctn::touch::device_type;
  SECTION("Operator ==")
  {
    CHECK(device_t::invalid == SDL_TOUCH_DEVICE_INVALID);
    CHECK(device_t::direct == SDL_TOUCH_DEVICE_DIRECT);
    CHECK(device_t::indirect_absolute == SDL_TOUCH_DEVICE_INDIRECT_ABSOLUTE);
    CHECK(device_t::indirect_relative == SDL_TOUCH_DEVICE_INDIRECT_RELATIVE);

    CHECK(SDL_TOUCH_DEVICE_INVALID == device_t::invalid);
    CHECK(SDL_TOUCH_DEVICE_DIRECT == device_t::direct);
    CHECK(SDL_TOUCH_DEVICE_INDIRECT_ABSOLUTE == device_t::indirect_absolute);
    CHECK(SDL_TOUCH_DEVICE_INDIRECT_RELATIVE == device_t ::indirect_relative);

    CHECK(!(device_t::indirect_absolute == SDL_TOUCH_DEVICE_DIRECT));
  }

  SECTION("Operator !=")
  {
    CHECK(device_t::invalid != SDL_TOUCH_DEVICE_INDIRECT_ABSOLUTE);
    CHECK(SDL_TOUCH_DEVICE_DIRECT != device_t::invalid);
  }
}

TEST_CASE("touch::num_devices", "[touch]")
{
  CHECK(ctn::touch::num_devices() == SDL_GetNumTouchDevices());
}

TEST_CASE("touch::get_device", "[!mayfail][touch]")
{
  const auto device = ctn::touch::get_device(0);
  CHECK(!device.has_value());
}

TEST_CASE("touch::type_of", "[touch]")
{
  CHECK(ctn::touch::type_of(0) == SDL_GetTouchDeviceType(0));
}

TEST_CASE("touch::num_fingers", "[touch]")
{
  CHECK(ctn::touch::num_fingers(0) == SDL_GetNumTouchFingers(0));
}

TEST_CASE("touch::get_finger", "[touch]")
{
  const auto finger = ctn::touch::get_finger(0, 0);
  CHECK(!finger.has_value());
}

TEST_CASE("touch::touch_mouse_id", "[touch]")
{
  CHECK(ctn::touch::touch_mouse_id() == SDL_TOUCH_MOUSEID);
  CHECK(ctn::touch::touch_mouse_id() != SDL_MOUSE_TOUCHID);
}

TEST_CASE("touch::mouse_touch_id", "[touch]")
{
  CHECK(ctn::touch::mouse_touch_id() == SDL_MOUSE_TOUCHID);
  CHECK(ctn::touch::mouse_touch_id() != SDL_TOUCH_MOUSEID);
}
