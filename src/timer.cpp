#ifndef CENTURION_TIMER_SOURCE
#define CENTURION_TIMER_SOURCE

#include "timer.h"

#include <SDL.h>

namespace centurion {

CENTURION_DEF void Timer::sleep(uint32_t ms) noexcept
{
  SDL_Delay(ms);
}

CENTURION_DEF uint64_t Timer::high_res() noexcept
{
  return SDL_GetPerformanceCounter();
}

CENTURION_DEF uint64_t Timer::high_res_freq() noexcept
{
  return SDL_GetPerformanceFrequency();
}

CENTURION_DEF uint32_t Timer::millis() noexcept
{
  return SDL_GetTicks();
}

}  // namespace centurion

#endif  // CENTURION_TIMER_SOURCE