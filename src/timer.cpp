#ifndef CENTURION_TIMER_SOURCE
#define CENTURION_TIMER_SOURCE

#include "timer.hpp"

namespace centurion {

CENTURION_DEF
void Timer::delay(milliseconds<u32> ms) noexcept
{
  SDL_Delay(ms.count());
}

CENTURION_DEF
auto Timer::high_res_freq() noexcept -> u64
{
  return SDL_GetPerformanceFrequency();
}

}  // namespace centurion

#endif  // CENTURION_TIMER_SOURCE