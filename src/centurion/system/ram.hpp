#ifndef CENTURION_RAM_HEADER
#define CENTURION_RAM_HEADER

#include <SDL.h>

/// \addtogroup system
/// \{

/**
 * \namespace cen::ram
 *
 * \brief Contains functions related to the system memory.
 *
 * \since 5.0.0
 *
 * \headerfile ram.hpp
 */
namespace cen::ram {

/**
 * \brief Returns the total amount of system RAM in megabytes.
 *
 * \return the total amount of system RAM in megabytes.
 *
 * \since 3.0.0
 */
[[nodiscard]] inline auto amount_mb() noexcept -> int
{
  return SDL_GetSystemRAM();
}

/**
 * \brief Returns the total amount of system RAM in gigabytes.
 *
 * \return the total amount of system RAM in gigabytes.
 *
 * \since 3.0.0
 */
[[nodiscard]] inline auto amount_gb() noexcept -> int
{
  return amount_mb() / 1'000;
}

}  // namespace cen::ram

/// \} End of group system

#endif  // CENTURION_RAM_HEADER