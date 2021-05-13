#ifndef CENTURION_SCALE_MODE_HEADER
#define CENTURION_SCALE_MODE_HEADER

#include <SDL.h>

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif

namespace cen {

/// \addtogroup video
/// \{

#if SDL_VERSION_ATLEAST(2, 0, 12)

/**
 * \enum scale_mode
 *
 * \brief Represents different texture scale modes.
 *
 * \since 4.0.0
 *
 * \see `SDL_ScaleMode`
 */
enum class scale_mode
{
  nearest = SDL_ScaleModeNearest,  ///< Represents nearest pixel sampling.
  linear = SDL_ScaleModeLinear,    ///< Represents linear filtering.
  best = SDL_ScaleModeBest         ///< Represents anisotropic filtering.
};

/**
 * \brief Indicates whether or not the two scale mode values are the same.
 *
 * \param lhs the lhs scale mode value.
 * \param rhs the rhs scale mode value.
 *
 * \return `true` if the scale mode values are the same; `false` otherwise.
 *
 * \since 4.0.0
 */
[[nodiscard]] constexpr auto operator==(const scale_mode lhs,
                                        const SDL_ScaleMode rhs) noexcept -> bool
{
  return static_cast<SDL_ScaleMode>(lhs) == rhs;
}

/// \copydoc operator==(scale_mode, SDL_ScaleMode)
[[nodiscard]] constexpr auto operator==(const SDL_ScaleMode lhs,
                                        const scale_mode rhs) noexcept -> bool
{
  return rhs == lhs;
}

/**
 * \brief Indicates whether or not the two scale mode values aren't the same.
 *
 * \param lhs the lhs scale mode value.
 * \param rhs the rhs scale mode value.
 *
 * \return `true` if the scale mode values aren't the same; `false` otherwise.
 *
 * \since 4.0.0
 */
[[nodiscard]] constexpr auto operator!=(const scale_mode lhs,
                                        const SDL_ScaleMode rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \copydoc operator!=(scale_mode, SDL_ScaleMode)
[[nodiscard]] constexpr auto operator!=(const SDL_ScaleMode lhs,
                                        const scale_mode rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

/// \}

}  // namespace cen

#endif  // CENTURION_SCALE_MODE_HEADER
