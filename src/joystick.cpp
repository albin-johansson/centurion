#ifndef CENTURION_JOYSTICK_SOURCE
#define CENTURION_JOYSTICK_SOURCE

#include "joystick.h"

#include <utility>

#include "centurion_exception.h"

namespace centurion {

CENTURION_DEF
Joystick::Joystick(int deviceIndex)
{
  if (SDL_NumJoysticks() == 0) {
    throw CenturionException{"There are no available joysticks!"};
  }

  m_joystick = SDL_JoystickOpen(deviceIndex);
  if (!m_joystick) {
    throw CenturionException{"Failed to open joystick!"};
  }
}

CENTURION_DEF
Joystick::Joystick(SDL_Joystick* joystick) : m_joystick{joystick}
{
  if (!joystick) {
    throw CenturionException{"Cannot create Joystick from null SDL_Joystick!"};
  }
}

CENTURION_DEF
Joystick::Joystick(Joystick&& other) noexcept
{
  move(std::move(other));
}

CENTURION_DEF
Joystick& Joystick::operator=(Joystick&& other) noexcept
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
UniquePtr<Joystick> Joystick::unique(int deviceIndex)
{
  return detail::make_unique<Joystick>(deviceIndex);
}

CENTURION_DEF
UniquePtr<Joystick> Joystick::unique(SDL_Joystick* joystick)
{
  return detail::make_unique<Joystick>(joystick);
}

CENTURION_DEF
SharedPtr<Joystick> Joystick::shared(int deviceIndex)
{
  return std::make_shared<Joystick>(deviceIndex);
}

CENTURION_DEF
SharedPtr<Joystick> Joystick::shared(SDL_Joystick* joystick)
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
bool Joystick::polling() noexcept
{
  return SDL_JoystickEventState(SDL_QUERY);
}

CENTURION_DEF
SDL_Joystick* Joystick::from_instance_id(JoystickID id) noexcept
{
  return SDL_JoystickFromInstanceID(id);
}

CENTURION_DEF
SDL_Joystick* Joystick::from_player_index(int playerIndex) noexcept
{
  return SDL_JoystickFromPlayerIndex(playerIndex);
}

CENTURION_DEF
Optional<int> Joystick::amount() noexcept
{
  const auto result = SDL_NumJoysticks();
  if (result < 0) {
    return nothing;
  } else {
    return result;
  }
}

CENTURION_DEF
SDL_JoystickGUID Joystick::device_guid(int deviceIndex) noexcept
{
  return SDL_JoystickGetDeviceGUID(deviceIndex);
}

CENTURION_DEF
CZString Joystick::name(int deviceIndex) noexcept
{
  return SDL_JoystickNameForIndex(deviceIndex);
}

CENTURION_DEF
void Joystick::rumble(Uint16 lowFreq, Uint16 highFreq, Uint32 duration) noexcept
{
  SDL_JoystickRumble(m_joystick, lowFreq, highFreq, duration);
}

CENTURION_DEF
void Joystick::set_player_index(int index) noexcept
{
  SDL_JoystickSetPlayerIndex(m_joystick, index);
}

CENTURION_DEF
Optional<int> Joystick::player_index() const noexcept
{
  const auto index = SDL_JoystickGetPlayerIndex(m_joystick);
  if (index == -1) {
    return nothing;
  } else {
    return index;
  }
}

CENTURION_DEF
Joystick::Type Joystick::type() const noexcept
{
  return static_cast<Type>(SDL_JoystickGetType(m_joystick));
}

CENTURION_DEF
Optional<Uint16> Joystick::vendor() const noexcept
{
  const auto vendor = SDL_JoystickGetVendor(m_joystick);
  if (vendor == 0) {
    return nothing;
  } else {
    return vendor;
  }
}

CENTURION_DEF
Optional<Uint16> Joystick::product() const noexcept
{
  const auto product = SDL_JoystickGetProduct(m_joystick);
  if (product == 0) {
    return nothing;
  } else {
    return product;
  }
}

CENTURION_DEF
Optional<Uint16> Joystick::product_version() const noexcept
{
  const auto version = SDL_JoystickGetProductVersion(m_joystick);
  if (version == 0) {
    return nothing;
  } else {
    return version;
  }
}

CENTURION_DEF
Optional<Joystick::BallAxisChange> Joystick::ball_axis_change(
    int ball) const noexcept
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
Optional<Sint16> Joystick::axis_pos(unsigned int axis) const noexcept
{
  const auto result = SDL_JoystickGetAxis(m_joystick, static_cast<int>(axis));
  if (result == 0) {
    return nothing;
  } else {
    return result;
  }
}

CENTURION_DEF
Optional<Sint16> Joystick::axis_initial_state(unsigned int axis) const noexcept
{
  Sint16 state{};
  const auto hadInitialState = SDL_JoystickGetAxisInitialState(
      m_joystick, static_cast<int>(axis), &state);
  if (hadInitialState) {
    return state;
  } else {
    return nothing;
  }
}

CENTURION_DEF
bool Joystick::attached() const noexcept
{
  return SDL_JoystickGetAttached(m_joystick);
}

CENTURION_DEF
int Joystick::num_hats() const noexcept
{
  return SDL_JoystickNumHats(m_joystick);
}

CENTURION_DEF
int Joystick::num_axes() const noexcept
{
  return SDL_JoystickNumAxes(m_joystick);
}
CENTURION_DEF
int Joystick::num_trackballs() const noexcept
{
  return SDL_JoystickNumBalls(m_joystick);
}

CENTURION_DEF
int Joystick::num_buttons() const noexcept
{
  return SDL_JoystickNumButtons(m_joystick);
}

CENTURION_DEF
JoystickID Joystick::id() const noexcept
{
  // Can fail for null joysticks, but that can't happen due to class invariant.
  return SDL_JoystickInstanceID(m_joystick);
}

CENTURION_DEF
SDL_JoystickGUID Joystick::device_guid() noexcept
{
  return SDL_JoystickGetGUID(m_joystick);
}

CENTURION_DEF
CZString Joystick::name() const noexcept
{
  return SDL_JoystickName(m_joystick);
}

CENTURION_DEF
Joystick::Power Joystick::power() const noexcept
{
  return static_cast<Power>(SDL_JoystickCurrentPowerLevel(m_joystick));
}

CENTURION_DEF
ButtonState Joystick::button_state(int button) const noexcept
{
  return static_cast<ButtonState>(SDL_JoystickGetButton(m_joystick, button));
}

CENTURION_DEF
Joystick::HatState Joystick::hat_state(int hat) const noexcept
{
  return static_cast<HatState>(SDL_JoystickGetHat(m_joystick, hat));
}

}  // namespace centurion

#endif  // CENTURION_JOYSTICK_SOURCE