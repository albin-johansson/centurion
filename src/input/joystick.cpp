#include "joystick.hpp"

#include <type_traits>

#include "exception.hpp"

namespace centurion {

static_assert(std::is_final_v<joystick>);
static_assert(std::is_nothrow_move_constructible_v<joystick>);
static_assert(std::is_nothrow_move_assignable_v<joystick>);
static_assert(!std::is_copy_constructible_v<joystick>);
static_assert(!std::is_copy_assignable_v<joystick>);

joystick::joystick(nn_owner<SDL_Joystick*> sdlJoystick) noexcept
    : basic_joystick{sdlJoystick}
{}

joystick::joystick(int deviceIndex)
{
  if (SDL_NumJoysticks() == 0) {
    throw exception{"There are no available joysticks!"};
  }

  auto& storage = get_storage();
  storage.reset(SDL_JoystickOpen(deviceIndex));
  if (!storage) {
    throw sdl_error{"Failed to open joystick"};
  }
}

void joystick::update() noexcept
{
  SDL_JoystickUpdate();
}

void joystick::lock() noexcept
{
  SDL_LockJoysticks();
}

void joystick::unlock() noexcept
{
  SDL_UnlockJoysticks();
}

void joystick::set_polling(bool enabled) noexcept
{
  SDL_JoystickEventState(enabled ? SDL_ENABLE : SDL_DISABLE);
}

auto joystick::is_polling() noexcept -> bool
{
  return SDL_JoystickEventState(SDL_QUERY);
}

auto joystick::from_instance_id(SDL_JoystickID id) noexcept -> SDL_Joystick*
{
  return SDL_JoystickFromInstanceID(id);
}

auto joystick::from_player_index(int playerIndex) noexcept -> SDL_Joystick*
{
  return SDL_JoystickFromPlayerIndex(playerIndex);
}

auto joystick::amount() noexcept -> std::optional<int>
{
  const auto result = SDL_NumJoysticks();
  if (result < 0) {
    return std::nullopt;
  } else {
    return result;
  }
}

auto joystick::guid(int deviceIndex) noexcept -> SDL_JoystickGUID
{
  return SDL_JoystickGetDeviceGUID(deviceIndex);
}

auto joystick::player_index(int deviceIndex) noexcept -> std::optional<int>
{
  const auto index = SDL_JoystickGetDevicePlayerIndex(deviceIndex);
  if (index == -1) {
    return std::nullopt;
  } else {
    return index;
  }
}

auto joystick::vendor(int deviceIndex) noexcept -> std::optional<u16>
{
  const auto vendor = SDL_JoystickGetDeviceVendor(deviceIndex);
  if (vendor == 0) {
    return std::nullopt;
  } else {
    return vendor;
  }
}

auto joystick::product(int deviceIndex) noexcept -> std::optional<u16>
{
  const auto product = SDL_JoystickGetDeviceProduct(deviceIndex);
  if (product == 0) {
    return std::nullopt;
  } else {
    return product;
  }
}

auto joystick::product_version(int deviceIndex) noexcept -> std::optional<u16>
{
  const auto version = SDL_JoystickGetDeviceProductVersion(deviceIndex);
  if (version == 0) {
    return std::nullopt;
  } else {
    return version;
  }
}

auto joystick::get_type(int deviceIndex) noexcept -> joystick::type
{
  return static_cast<type>(SDL_JoystickGetDeviceType(deviceIndex));
}

auto joystick::instance_id(int deviceIndex) noexcept
    -> std::optional<SDL_JoystickID>
{
  const auto id = SDL_JoystickGetDeviceInstanceID(deviceIndex);
  if (id == -1) {
    return std::nullopt;
  } else {
    return id;
  }
}

auto joystick::name(int deviceIndex) noexcept -> czstring
{
  return SDL_JoystickNameForIndex(deviceIndex);
}

auto joystick::guid_from_string(nn_czstring str) noexcept -> SDL_JoystickGUID
{
  return SDL_JoystickGetGUIDFromString(str);
}

}  // namespace centurion
