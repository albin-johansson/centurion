#ifndef CENTURION_BLEND_MODE_HEADER
#define CENTURION_BLEND_MODE_HEADER

#include <SDL.h>

#include "centurion_cfg.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/// \addtogroup graphics
/// \{

/**
 * \enum blend_mode
 *
 * \brief Mirrors the `SDL_BlendMode` enum.
 *
 * \since 3.0.0
 *
 * \headerfile blend_mode.hpp
 */
enum class blend_mode
{
  none = SDL_BLENDMODE_NONE,    ///< Represents no blending.
  blend = SDL_BLENDMODE_BLEND,  ///< Represents alpha blending.
  add = SDL_BLENDMODE_ADD,      ///< Represents additive blending.
  mod = SDL_BLENDMODE_MOD,      ///< Represents color modulation.

#if SDL_VERSION_ATLEAST(2, 0, 12)

  mul = SDL_BLENDMODE_MUL,  ///< Represents color multiplication.

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

  invalid = SDL_BLENDMODE_INVALID  ///< Represents an invalid blend mode.
};

/**
 * \brief Indicates whether or not two blend mode values are the same;
 *
 * \param lhs the left-hand side blend mode value.
 * \param rhs the right-hand side blend mode value.
 *
 * \return `true` if the values are the same; `false` otherwise.
 *
 * \since 3.0.0
 */
[[nodiscard]] constexpr auto operator==(const blend_mode lhs,
                                        const SDL_BlendMode rhs) noexcept
    -> bool
{
  return static_cast<SDL_BlendMode>(lhs) == rhs;
}

/**
 * \copydoc operator==(blend_mode, SDL_BlendMode)
 */
[[nodiscard]] constexpr auto operator==(const SDL_BlendMode lhs,
                                        const blend_mode rhs) noexcept -> bool
{
  return rhs == lhs;
}

/**
 * \brief Indicates whether or not two blend mode values aren't the same;
 *
 * \param lhs the left-hand side blend mode value.
 * \param rhs the right-hand side blend mode value.
 *
 * \return `true` if the values aren't the same; `false` otherwise.
 *
 * \since 3.0.0
 */
[[nodiscard]] constexpr auto operator!=(const blend_mode lhs,
                                        const SDL_BlendMode rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/**
 * \copydoc operator!=(blend_mode, SDL_BlendMode)
 */
[[nodiscard]] constexpr auto operator!=(const SDL_BlendMode lhs,
                                        const blend_mode rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \}

}  // namespace cen

#endif  // CENTURION_BLEND_MODE_HEADER
