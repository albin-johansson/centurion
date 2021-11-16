#ifndef CENTURION_RAM_HEADER
#define CENTURION_RAM_HEADER

#include <SDL.h>

namespace cen {

/// \addtogroup system
/// \{

/// \name RAM functions
/// \{

/**
 * \brief Returns the total amount of system RAM, in megabytes.
 *
 * \return the amount of RAM.
 *
 * \since 3.0.0
 */
[[nodiscard]] inline auto memory_mb() noexcept -> int
{
  return SDL_GetSystemRAM();
}

/**
 * \brief Returns the total amount of system RAM, in gigabytes.
 *
 * \return the amount of RAM.
 *
 * \since 3.0.0
 */
[[nodiscard]] inline auto memory_gb() noexcept -> int
{
  return memory_mb() / 1'000;
}

/// \} End of RAM functions

/// \} End of group system

}  // namespace cen

#endif  // CENTURION_RAM_HEADER