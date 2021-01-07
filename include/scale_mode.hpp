/*
 * MIT License
 *
 * Copyright (c) 2019-2021 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef CENTURION_SCALE_MODE_HEADER
#define CENTURION_SCALE_MODE_HEADER

#include <SDL.h>

#include "centurion_cfg.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif

namespace cen {

/// \addtogroup graphics
/// \{

/**
 * \enum scale_mode
 *
 * \brief Mirrors the `SDL_ScaleMode` enum.
 *
 * \since 4.0.0
 *
 * \see `SDL_ScaleMode`
 *
 * \headerfile scale_mode.hpp
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
                                        const SDL_ScaleMode rhs) noexcept
    -> bool
{
  return static_cast<SDL_ScaleMode>(lhs) == rhs;
}

/**
 * \copydoc operator==(scale_mode, SDL_ScaleMode)
 */
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
                                        const SDL_ScaleMode rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/**
 * \copydoc operator!=(scale_mode, SDL_ScaleMode)
 */
[[nodiscard]] constexpr auto operator!=(const SDL_ScaleMode lhs,
                                        const scale_mode rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \}

}  // namespace cen

#endif  // CENTURION_SCALE_MODE_HEADER
