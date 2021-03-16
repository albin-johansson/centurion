#ifndef CENTURION_TIMER_HEADER
#define CENTURION_TIMER_HEADER

#include <SDL.h>

#include "centurion_cfg.hpp"
#include "time.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

/**
 * \namespace cen::counter
 *
 * \ingroup system
 *
 * \brief Provides timing utilities.
 *
 * \since 5.0.0
 *
 * \headerfile counter.hpp
 */
namespace cen::counter {

/// \addtogroup system
/// \{

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

/**
 * \brief Returns the amount of milliseconds since the library was
 * initialized.
 *
 * \return the amount of milliseconds since the library was initialized.
 *
 * \since 3.0.0
 */
[[nodiscard]] inline auto ticks() -> milliseconds<u32>
{
  return milliseconds<u32>{SDL_GetTicks()};
}

/// \} End of group system

}  // namespace cen::counter

#endif  // CENTURION_TIMER_HEADER