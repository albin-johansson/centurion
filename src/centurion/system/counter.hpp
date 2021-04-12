#ifndef CENTURION_TIMER_HEADER
#define CENTURION_TIMER_HEADER

#include <SDL.h>

#include "../misc/time.hpp"

/// \addtogroup system
/// \{

/**
 * \namespace cen::counter
 *
 * \brief Provides timing utilities.
 *
 * \since 5.0.0
 *
 * \headerfile counter.hpp
 */
namespace cen::counter {

/**
 * \brief Returns the frequency of the system high-performance counter.
 *
 * \return the frequency of the system high-performance counter.
 *
 * \since 3.0.0
 */
[[nodiscard]] inline auto high_res_freq() noexcept -> u64
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
[[nodiscard]] auto now_sec() noexcept -> seconds<T>
{
  const auto freq = static_cast<T>(high_res_freq());
  return seconds<T>{static_cast<T>(SDL_GetPerformanceCounter()) / freq};
}

// clang-format off

/**
 * \brief Returns the amount of milliseconds since the library was
 * initialized.
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

// clang-format on

}  // namespace cen::counter

/// \} End of group system

#endif  // CENTURION_TIMER_HEADER