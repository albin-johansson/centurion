#include "touch.hpp"

namespace centurion::touch {

// TODO inline these operators

auto operator==(DeviceType lhs, SDL_TouchDeviceType rhs) noexcept -> bool
{
  return static_cast<SDL_TouchDeviceType>(lhs) == rhs;
}

auto operator==(SDL_TouchDeviceType lhs, DeviceType rhs) noexcept -> bool
{
  return rhs == lhs;
}

auto operator!=(DeviceType lhs, SDL_TouchDeviceType rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

auto operator!=(SDL_TouchDeviceType lhs, DeviceType rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

auto num_devices() noexcept -> int
{
  return SDL_GetNumTouchDevices();
}

auto get_device(int index) noexcept -> std::optional<SDL_TouchID>
{
  const auto device = SDL_GetTouchDevice(index);
  if (device == 0) {
    return nothing;
  } else {
    return device;
  }
}

auto type_of(SDL_TouchID id) noexcept -> DeviceType
{
  return static_cast<DeviceType>(SDL_GetTouchDeviceType(id));
}

auto num_fingers(SDL_TouchID id) noexcept -> int
{
  return SDL_GetNumTouchFingers(id);
}

auto get_finger(SDL_TouchID id, int index) noexcept -> std::optional<SDL_Finger>
{
  const auto* finger = SDL_GetTouchFinger(id, index);
  if (finger) {
    return *finger;
  } else {
    return nothing;
  }
}

}  // namespace centurion::touch
