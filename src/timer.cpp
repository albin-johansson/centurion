#include "timer.h"

#include <SDL.h>

namespace centurion {

void Timer::sleep(uint32_t ms) noexcept { SDL_Delay(ms); }

uint64_t Timer::high_res() noexcept { return SDL_GetPerformanceCounter(); }

uint64_t Timer::high_res_freq() noexcept {
  return SDL_GetPerformanceFrequency();
}

uint32_t Timer::millis() noexcept { return SDL_GetTicks(); }

}  // namespace centurion
