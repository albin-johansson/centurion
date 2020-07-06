#ifndef CENTURION_TOUCH_SOURCE
#define CENTURION_TOUCH_SOURCE

#include "touch.h"

namespace centurion {
namespace touch {

CENTURION_DEF
bool operator==(DeviceType lhs, SDL_TouchDeviceType rhs) noexcept
{
  return static_cast<SDL_TouchDeviceType>(lhs) == rhs;
}

CENTURION_DEF
bool operator==(SDL_TouchDeviceType lhs, DeviceType rhs) noexcept
{
  return rhs == lhs;
}

CENTURION_DEF
bool operator!=(DeviceType lhs, SDL_TouchDeviceType rhs) noexcept
{
  return !(lhs == rhs);
}

CENTURION_DEF
bool operator!=(SDL_TouchDeviceType lhs, DeviceType rhs) noexcept
{
  return !(lhs == rhs);
}

CENTURION_DEF
int num_devices() noexcept
{
  return SDL_GetNumTouchDevices();
}

CENTURION_DEF
Optional<TouchID> get_device(int index) noexcept
{
  const auto device = SDL_GetTouchDevice(index);
  if (device == 0) {
    return nothing;
  } else {
    return device;
  }
}

CENTURION_DEF
DeviceType type_of(centurion::TouchID id) noexcept
{
  return static_cast<DeviceType>(SDL_GetTouchDeviceType(id));
}

CENTURION_DEF
int num_fingers(centurion::TouchID id) noexcept
{
  return SDL_GetNumTouchFingers(id);
}

CENTURION_DEF
Optional<SDL_Finger> get_finger(centurion::TouchID id, int index) noexcept
{
  const auto* finger = SDL_GetTouchFinger(id, index);
  if (finger) {
    return *finger;
  } else {
    return nothing;
  }
}

}  // namespace touch
}  // namespace centurion

#endif  // CENTURION_TOUCH_SOURCE