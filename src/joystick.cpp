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
Joystick::Power Joystick::power() const noexcept
{
  return static_cast<Power>(SDL_JoystickCurrentPowerLevel(m_joystick));
}

}  // namespace centurion

#endif  // CENTURION_JOYSTICK_SOURCE