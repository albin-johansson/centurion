#ifndef CENTURION_TIMER_HEADER
#define CENTURION_TIMER_HEADER

#include <SDL.h>

#include "../core/time.hpp"

/**
 * \namespace cen::counter
 *
 * \brief Provides timing utilities.
 * 
 * \todo Centurion 7: remove the `cen::counter` namespace.
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
 * \deprecated Since 6.4.0, use `ticks64()` instead.
 *
 * \since 3.0.0
 */
[[nodiscard, deprecated]] inline auto ticks() noexcept(noexcept(u32_ms{u32{}})) -> u32_ms
{
  return u32_ms{SDL_GetTicks()};
}

#if SDL_VERSION_ATLEAST(2, 0, 18)

/**
 * \brief Returns the amount of milliseconds since the library was initialized.
 *
 * \return the amount of milliseconds since the library was initialized.
 *
 * \since 6.4.0
 */
[[nodiscard]] inline auto ticks64() noexcept(noexcept(u64_ms{u64{}})) -> u64_ms
{
  return u64_ms{SDL_GetTicks64()};
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 18)

/// \} End of counter functions

/// \} End of group system

}  // namespace cen::counter

#endif  // CENTURION_TIMER_HEADER