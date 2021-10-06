#ifndef CENTURION_TIMER_HEADER
#define CENTURION_TIMER_HEADER

#include <SDL.h>

#include "../core/time.hpp"

/**
 * \namespace cen::counter
 *
 * \brief Provides timing utilities.
 *
 * \since 5.0.0
 */
namespace cen::counter {

/// \addtogroup system
/// \{

/// \name Counter functions
/// \{

/**
 * \brief Returns the frequency of the system high-performance counter.
 *
 * \return the frequency of the system high-performance counter.
 *
 * \since 3.0.0
 */
[[nodiscard]] inline auto frequency() noexcept -> u64
{
  return SDL_GetPerformanceFrequency();
}

/**
 * \brief Returns the current raw value of the system high-performance counter.
 *
 * \note The unit of the returned value is platform dependent.
 *
 * \return the current value of the system high-performance counter.
 *
 * \since 3.0.0
 */
[[nodiscard]] inline auto now() noexcept -> u64
{
  return SDL_GetPerformanceCounter();
}

/**
 * \brief Returns the value of the system high-performance counter in seconds.
 *
 * \tparam T the representation type.
 *
 * \return the value of the system high-performance counter, in seconds.
 *
 * \since 5.0.0
 */
template <typename T>
[[nodiscard]] auto now_in_seconds() noexcept(noexcept(seconds<T>{})) -> seconds<T>
{
  return seconds<T>{static_cast<T>(SDL_GetPerformanceCounter()) / static_cast<T>(frequency())};
}

/**
 * \brief Returns the amount of milliseconds since the library was initialized.
 *
 * \return the amount of milliseconds since the library was initialized.
 *
 * \since 3.0.0
 */
[[nodiscard]] inline auto ticks() noexcept(noexcept(milliseconds<u32>{u32{}}))
    -> milliseconds<u32>
{
  return milliseconds<u32>{SDL_GetTicks()};
}

/// \} End of counter functions

/// \} End of group system

}  // namespace cen::counter

#endif  // CENTURION_TIMER_HEADER