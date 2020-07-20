#include "joystick.hpp"

#include <utility>

#include "centurion_exception.hpp"

namespace centurion {

joystick::joystick(int deviceIndex)
{
  if (SDL_NumJoysticks() == 0) {
    throw centurion_exception{"There are no available joysticks!"};
  }

  m_joystick = SDL_JoystickOpen(deviceIndex);
  if (!m_joystick) {
    throw centurion_exception{"Failed to open joystick!"};
  }
}

joystick::joystick(owner<SDL_Joystick*> sdlJoystick) : m_joystick{sdlJoystick}
{
  if (!sdlJoystick) {
    throw centurion_exception{"Cannot create Joystick from null SDL_Joystick!"};
  }
}

joystick::joystick(joystick&& other) noexcept
{
  move(std::move(other));
}

auto joystick::operator=(joystick&& other) noexcept -> joystick&
{
  if (this != &other) {
    move(std::move(other));
  }
  return *this;
}

joystick::~joystick() noexcept
{
  destroy();
}

void joystick::move(joystick&& other) noexcept
{
  destroy();

  m_joystick = other.m_joystick;
  other.m_joystick = nullptr;
}

void joystick::destroy() noexcept
{
  if (SDL_JoystickGetAttached(m_joystick)) {
    SDL_JoystickClose(m_joystick);
  }
}

auto joystick::unique(int deviceIndex) -> std::unique_ptr<joystick>
{
  return std::make_unique<joystick>(deviceIndex);
}

auto joystick::unique(SDL_Joystick* sdlJoystick) -> std::unique_ptr<joystick>
{
  return std::make_unique<joystick>(sdlJoystick);
}

auto joystick::shared(int deviceIndex) -> std::shared_ptr<joystick>
{
  return std::make_shared<joystick>(deviceIndex);
}

auto joystick::shared(SDL_Joystick* sdlJoystick) -> std::shared_ptr<joystick>
{
  return std::make_shared<joystick>(sdlJoystick);
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

auto joystick::polling() noexcept -> bool
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
    return nothing;
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
    return nothing;
  } else {
    return index;
  }
}

auto joystick::vendor(int deviceIndex) noexcept -> std::optional<u16>
{
  const auto vendor = SDL_JoystickGetDeviceVendor(deviceIndex);
  if (vendor == 0) {
    return nothing;
  } else {
    return vendor;
  }
}

auto joystick::product(int deviceIndex) noexcept -> std::optional<u16>
{
  const auto product = SDL_JoystickGetDeviceProduct(deviceIndex);
  if (product == 0) {
    return nothing;
  } else {
    return product;
  }
}

auto joystick::product_version(int deviceIndex) noexcept -> std::optional<u16>
{
  const auto version = SDL_JoystickGetDeviceProductVersion(deviceIndex);
  if (version == 0) {
    return nothing;
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
    return nothing;
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

void joystick::rumble(u16 lowFreq,
                      u16 highFreq,
                      milliseconds<u32> duration) noexcept
{
  SDL_JoystickRumble(m_joystick, lowFreq, highFreq, duration.count());
}

void joystick::set_player_index(int index) noexcept
{
  SDL_JoystickSetPlayerIndex(m_joystick, index);
}

auto joystick::player_index() const noexcept -> std::optional<int>
{
  const auto index = SDL_JoystickGetPlayerIndex(m_joystick);
  if (index == -1) {
    return nothing;
  } else {
    return index;
  }
}

auto joystick::get_type() const noexcept -> joystick::type
{
  return static_cast<type>(SDL_JoystickGetType(m_joystick));
}

auto joystick::vendor() const noexcept -> std::optional<u16>
{
  const auto vendor = SDL_JoystickGetVendor(m_joystick);
  if (vendor == 0) {
    return nothing;
  } else {
    return vendor;
  }
}

auto joystick::product() const noexcept -> std::optional<u16>
{
  const auto product = SDL_JoystickGetProduct(m_joystick);
  if (product == 0) {
    return nothing;
  } else {
    return product;
  }
}

auto joystick::product_version() const noexcept -> std::optional<u16>
{
  const auto version = SDL_JoystickGetProductVersion(m_joystick);
  if (version == 0) {
    return nothing;
  } else {
    return version;
  }
}

auto joystick::get_ball_axis_change(int ball) const noexcept
    -> std::optional<joystick::ball_axis_change>
{
  ball_axis_change change{};
  const auto result =
      SDL_JoystickGetBall(m_joystick, ball, &change.dx, &change.dy);
  if (result == 0) {
    return change;
  } else {
    return nothing;
  }
}

auto joystick::axis_pos(unsigned int axis) const noexcept -> std::optional<i16>
{
  const auto result = SDL_JoystickGetAxis(m_joystick, static_cast<int>(axis));
  if (result == 0) {
    return nothing;
  } else {
    return result;
  }
}

auto joystick::axis_initial_state(unsigned int axis) const noexcept
    -> std::optional<i16>
{
  i16 state{};
  const auto hadInitialState = SDL_JoystickGetAxisInitialState(
      m_joystick, static_cast<int>(axis), &state);
  if (hadInitialState) {
    return state;
  } else {
    return nothing;
  }
}

auto joystick::attached() const noexcept -> bool
{
  return SDL_JoystickGetAttached(m_joystick);
}

auto joystick::num_hats() const noexcept -> int
{
  return SDL_JoystickNumHats(m_joystick);
}

auto joystick::num_axes() const noexcept -> int
{
  return SDL_JoystickNumAxes(m_joystick);
}

auto joystick::num_trackballs() const noexcept -> int
{
  return SDL_JoystickNumBalls(m_joystick);
}

auto joystick::num_buttons() const noexcept -> int
{
  return SDL_JoystickNumButtons(m_joystick);
}

auto joystick::instance_id() const noexcept -> SDL_JoystickID
{
  return SDL_JoystickInstanceID(m_joystick);
}

auto joystick::guid() noexcept -> SDL_JoystickGUID
{
  return SDL_JoystickGetGUID(m_joystick);
}

auto joystick::name() const noexcept -> czstring
{
  return SDL_JoystickName(m_joystick);
}

auto joystick::get_power() const noexcept -> joystick::power
{
  return static_cast<power>(SDL_JoystickCurrentPowerLevel(m_joystick));
}

auto joystick::get_button_state(int button) const noexcept -> button_state
{
  return static_cast<button_state>(SDL_JoystickGetButton(m_joystick, button));
}

auto joystick::get_hat_state(int hat) const noexcept -> joystick::hat_state
{
  return static_cast<hat_state>(SDL_JoystickGetHat(m_joystick, hat));
}

}  // namespace centurion
