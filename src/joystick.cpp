#ifndef CENTURION_JOYSTICK_SOURCE
#define CENTURION_JOYSTICK_SOURCE

#include "joystick.hpp"

#include <utility>

#include "centurion_exception.hpp"

namespace centurion {

CENTURION_DEF
Joystick::Joystick(int deviceIndex)
{
  if (SDL_NumJoysticks() == 0) {
    throw centurion_exception{"There are no available joysticks!"};
  }

  m_joystick = SDL_JoystickOpen(deviceIndex);
  if (!m_joystick) {
    throw centurion_exception{"Failed to open joystick!"};
  }
}

CENTURION_DEF
Joystick::Joystick(owner<SDL_Joystick*> joystick) : m_joystick{joystick}
{
  if (!joystick) {
    throw centurion_exception{"Cannot create Joystick from null SDL_Joystick!"};
  }
}

CENTURION_DEF
Joystick::Joystick(Joystick&& other) noexcept
{
  move(std::move(other));
}

CENTURION_DEF
auto Joystick::operator=(Joystick&& other) noexcept -> Joystick&
{
  if (this != &other) {
    move(std::move(other));
  }
  return *this;
}

CENTURION_DEF
Joystick::~Joystick() noexcept
{
  destroy();
}

CENTURION_DEF
void Joystick::move(Joystick&& other) noexcept
{
  destroy();

  m_joystick = other.m_joystick;
  other.m_joystick = nullptr;
}

CENTURION_DEF
void Joystick::destroy() noexcept
{
  if (SDL_JoystickGetAttached(m_joystick)) {
    SDL_JoystickClose(m_joystick);
  }
}

CENTURION_DEF
auto Joystick::unique(int deviceIndex) -> std::unique_ptr<Joystick>
{
  return std::make_unique<Joystick>(deviceIndex);
}

CENTURION_DEF
auto Joystick::unique(SDL_Joystick* joystick) -> std::unique_ptr<Joystick>
{
  return std::make_unique<Joystick>(joystick);
}

CENTURION_DEF
auto Joystick::shared(int deviceIndex) -> std::shared_ptr<Joystick>
{
  return std::make_shared<Joystick>(deviceIndex);
}

CENTURION_DEF
auto Joystick::shared(SDL_Joystick* joystick) -> std::shared_ptr<Joystick>
{
  return std::make_shared<Joystick>(joystick);
}

CENTURION_DEF
void Joystick::update() noexcept
{
  SDL_JoystickUpdate();
}

CENTURION_DEF
void Joystick::lock() noexcept
{
  SDL_LockJoysticks();
}

CENTURION_DEF
void Joystick::unlock() noexcept
{
  SDL_UnlockJoysticks();
}

CENTURION_DEF
void Joystick::set_polling(bool enabled) noexcept
{
  SDL_JoystickEventState(enabled ? SDL_ENABLE : SDL_DISABLE);
}

CENTURION_DEF
auto Joystick::polling() noexcept -> bool
{
  return SDL_JoystickEventState(SDL_QUERY);
}

CENTURION_DEF
auto Joystick::from_instance_id(SDL_JoystickID id) noexcept -> SDL_Joystick*
{
  return SDL_JoystickFromInstanceID(id);
}

CENTURION_DEF
auto Joystick::from_player_index(int playerIndex) noexcept -> SDL_Joystick*
{
  return SDL_JoystickFromPlayerIndex(playerIndex);
}

CENTURION_DEF
auto Joystick::amount() noexcept -> std::optional<int>
{
  const auto result = SDL_NumJoysticks();
  if (result < 0) {
    return nothing;
  } else {
    return result;
  }
}

CENTURION_DEF
auto Joystick::guid(int deviceIndex) noexcept -> SDL_JoystickGUID
{
  return SDL_JoystickGetDeviceGUID(deviceIndex);
}

CENTURION_DEF
auto Joystick::player_index(int deviceIndex) noexcept -> std::optional<int>
{
  const auto index = SDL_JoystickGetDevicePlayerIndex(deviceIndex);
  if (index == -1) {
    return nothing;
  } else {
    return index;
  }
}

CENTURION_DEF
auto Joystick::vendor(int deviceIndex) noexcept -> std::optional<u16>
{
  const auto vendor = SDL_JoystickGetDeviceVendor(deviceIndex);
  if (vendor == 0) {
    return nothing;
  } else {
    return vendor;
  }
}

CENTURION_DEF
auto Joystick::product(int deviceIndex) noexcept -> std::optional<u16>
{
  const auto product = SDL_JoystickGetDeviceProduct(deviceIndex);
  if (product == 0) {
    return nothing;
  } else {
    return product;
  }
}

CENTURION_DEF
auto Joystick::product_version(int deviceIndex) noexcept -> std::optional<u16>
{
  const auto version = SDL_JoystickGetDeviceProductVersion(deviceIndex);
  if (version == 0) {
    return nothing;
  } else {
    return version;
  }
}

CENTURION_DEF
auto Joystick::type(int deviceIndex) noexcept -> Joystick::Type
{
  return static_cast<Type>(SDL_JoystickGetDeviceType(deviceIndex));
}

CENTURION_DEF
auto Joystick::instance_id(int deviceIndex) noexcept
    -> std::optional<SDL_JoystickID>
{
  const auto id = SDL_JoystickGetDeviceInstanceID(deviceIndex);
  if (id == -1) {
    return nothing;
  } else {
    return id;
  }
}

CENTURION_DEF
auto Joystick::name(int deviceIndex) noexcept -> czstring
{
  return SDL_JoystickNameForIndex(deviceIndex);
}

CENTURION_DEF
auto Joystick::guid_from_string(gsl::not_null<czstring> str) noexcept
    -> SDL_JoystickGUID
{
  return SDL_JoystickGetGUIDFromString(str);
}

CENTURION_DEF
void Joystick::rumble(u16 lowFreq,
                      u16 highFreq,
                      milliseconds<u32> duration) noexcept
{
  SDL_JoystickRumble(m_joystick, lowFreq, highFreq, duration.count());
}

CENTURION_DEF
void Joystick::set_player_index(int index) noexcept
{
  SDL_JoystickSetPlayerIndex(m_joystick, index);
}

CENTURION_DEF
auto Joystick::player_index() const noexcept -> std::optional<int>
{
  const auto index = SDL_JoystickGetPlayerIndex(m_joystick);
  if (index == -1) {
    return nothing;
  } else {
    return index;
  }
}

CENTURION_DEF
auto Joystick::type() const noexcept -> Joystick::Type
{
  return static_cast<Type>(SDL_JoystickGetType(m_joystick));
}

CENTURION_DEF
auto Joystick::vendor() const noexcept -> std::optional<u16>
{
  const auto vendor = SDL_JoystickGetVendor(m_joystick);
  if (vendor == 0) {
    return nothing;
  } else {
    return vendor;
  }
}

CENTURION_DEF
auto Joystick::product() const noexcept -> std::optional<u16>
{
  const auto product = SDL_JoystickGetProduct(m_joystick);
  if (product == 0) {
    return nothing;
  } else {
    return product;
  }
}

CENTURION_DEF
auto Joystick::product_version() const noexcept -> std::optional<u16>
{
  const auto version = SDL_JoystickGetProductVersion(m_joystick);
  if (version == 0) {
    return nothing;
  } else {
    return version;
  }
}

CENTURION_DEF
auto Joystick::ball_axis_change(int ball) const noexcept
    -> std::optional<Joystick::BallAxisChange>
{
  BallAxisChange change{};
  const auto result =
      SDL_JoystickGetBall(m_joystick, ball, &change.dx, &change.dy);
  if (result == 0) {
    return change;
  } else {
    return nothing;
  }
}

CENTURION_DEF
auto Joystick::axis_pos(unsigned int axis) const noexcept -> std::optional<i16>
{
  const auto result = SDL_JoystickGetAxis(m_joystick, static_cast<int>(axis));
  if (result == 0) {
    return nothing;
  } else {
    return result;
  }
}

CENTURION_DEF
auto Joystick::axis_initial_state(unsigned int axis) const noexcept
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

CENTURION_DEF
auto Joystick::attached() const noexcept -> bool
{
  return SDL_JoystickGetAttached(m_joystick);
}

CENTURION_DEF
auto Joystick::num_hats() const noexcept -> int
{
  return SDL_JoystickNumHats(m_joystick);
}

CENTURION_DEF
auto Joystick::num_axes() const noexcept -> int
{
  return SDL_JoystickNumAxes(m_joystick);
}
CENTURION_DEF
auto Joystick::num_trackballs() const noexcept -> int
{
  return SDL_JoystickNumBalls(m_joystick);
}

CENTURION_DEF
auto Joystick::num_buttons() const noexcept -> int
{
  return SDL_JoystickNumButtons(m_joystick);
}

CENTURION_DEF
auto Joystick::instance_id() const noexcept -> SDL_JoystickID
{
  return SDL_JoystickInstanceID(m_joystick);
}

CENTURION_DEF
auto Joystick::guid() noexcept -> SDL_JoystickGUID
{
  return SDL_JoystickGetGUID(m_joystick);
}

CENTURION_DEF
auto Joystick::name() const noexcept -> czstring
{
  return SDL_JoystickName(m_joystick);
}

CENTURION_DEF
auto Joystick::power() const noexcept -> Joystick::Power
{
  return static_cast<Power>(SDL_JoystickCurrentPowerLevel(m_joystick));
}

CENTURION_DEF
auto Joystick::button_state(int button) const noexcept -> enum button_state {
  return static_cast<enum button_state>(SDL_JoystickGetButton(m_joystick,
                                                              button));
}

CENTURION_DEF
auto Joystick::hat_state(int hat) const noexcept -> Joystick::HatState
{
  return static_cast<HatState>(SDL_JoystickGetHat(m_joystick, hat));
}

}  // namespace centurion

#endif  // CENTURION_JOYSTICK_SOURCE
