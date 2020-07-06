#ifndef CENTURION_RAM_SOURCE
#define CENTURION_RAM_SOURCE

#include "ram.hpp"

namespace centurion {

CENTURION_DEF
int RAM::size_mb() noexcept
{
  return SDL_GetSystemRAM();
}

CENTURION_DEF
int RAM::size_gb() noexcept
{
  return size_mb() / 1000;
}

}  // namespace centurion

#endif  // CENTURION_RAM_SOURCE