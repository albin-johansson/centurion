#ifndef CENTURION_JOYSTICK_SOURCE
#define CENTURION_JOYSTICK_SOURCE

#include "joystick.h"

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
Joystick::~Joystick() noexcept
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
SDL_Joystick* Joystick::from_instance_id(JoystickID id) noexcept
{
  return SDL_JoystickFromInstanceID(id);
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
CZString Joystick::name() const noexcept
{
  return SDL_JoystickName(m_joystick);
}

CENTURION_DEF
Joystick::Power Joystick::power() const noexcept
{
  return static_cast<Power>(SDL_JoystickCurrentPowerLevel(m_joystick));
}

}  // namespace centurion

#endif  // CENTURION_JOYSTICK_SOURCE