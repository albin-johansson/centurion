#ifndef CENTURION_TIMER_SOURCE
#define CENTURION_TIMER_SOURCE

#include "timer.hpp"

namespace centurion {

CENTURION_DEF
void Timer::delay(Uint32 ms) noexcept
{
  SDL_Delay(ms);
}

CENTURION_DEF
Uint64 Timer::high_res_freq() noexcept
{
  return SDL_GetPerformanceFrequency();
}

}  // namespace centurion

#endif  // CENTURION_TIMER_SOURCE