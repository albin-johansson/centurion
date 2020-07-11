#ifndef CENTURION_TOUCH_SOURCE
#define CENTURION_TOUCH_SOURCE

#include "touch.hpp"

namespace centurion::touch {

CENTURION_DEF
auto operator==(DeviceType lhs, SDL_TouchDeviceType rhs) noexcept -> bool
{
  return static_cast<SDL_TouchDeviceType>(lhs) == rhs;
}

CENTURION_DEF
auto operator==(SDL_TouchDeviceType lhs, DeviceType rhs) noexcept -> bool
{
  return rhs == lhs;
}

CENTURION_DEF
auto operator!=(DeviceType lhs, SDL_TouchDeviceType rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

CENTURION_DEF
auto operator!=(SDL_TouchDeviceType lhs, DeviceType rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

CENTURION_DEF
auto num_devices() noexcept -> int
{
  return SDL_GetNumTouchDevices();
}

CENTURION_DEF
auto get_device(int index) noexcept -> std::optional<TouchID>
{
  const auto device = SDL_GetTouchDevice(index);
  if (device == 0) {
    return nothing;
  } else {
    return device;
  }
}

CENTURION_DEF
auto type_of(centurion::TouchID id) noexcept -> DeviceType
{
  return static_cast<DeviceType>(SDL_GetTouchDeviceType(id));
}

CENTURION_DEF
auto num_fingers(centurion::TouchID id) noexcept -> int
{
  return SDL_GetNumTouchFingers(id);
}

CENTURION_DEF
auto get_finger(centurion::TouchID id, int index) noexcept
    -> std::optional<SDL_Finger>
{
  const auto* finger = SDL_GetTouchFinger(id, index);
  if (finger) {
    return *finger;
  } else {
    return nothing;
  }
}

}  // namespace centurion::touch

#endif  // CENTURION_TOUCH_SOURCE