/*
 * MIT License
 *
 * Copyright (c) 2019-2020 Albin Johansson
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

#ifndef CENTURION_BLEND_MODE_HEADER
#define CENTURION_BLEND_MODE_HEADER

#include <SDL_blendmode.h>

#include "centurion_api.hpp"

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
  none = SDL_BLENDMODE_NONE,       ///< Represents no blending.
  blend = SDL_BLENDMODE_BLEND,     ///< Represents alpha blending.
  add = SDL_BLENDMODE_ADD,         ///< Represents additive blending.
  mod = SDL_BLENDMODE_MOD,         ///< Represents color modulation.
  mul = SDL_BLENDMODE_MUL,         ///< Represents color multiplication.
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
[[nodiscard]] inline auto operator==(blend_mode lhs, SDL_BlendMode rhs) noexcept
    -> bool
{
  return static_cast<SDL_BlendMode>(lhs) == rhs;
}

/**
 * \copydoc operator==(blend_mode, SDL_BlendMode)
 */
[[nodiscard]] inline auto operator==(SDL_BlendMode lhs, blend_mode rhs) noexcept
    -> bool
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
[[nodiscard]] inline auto operator!=(blend_mode lhs, SDL_BlendMode rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/**
 * \copydoc operator!=(blend_mode, SDL_BlendMode)
 */
[[nodiscard]] inline auto operator!=(SDL_BlendMode lhs, blend_mode rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/// \}

}  // namespace cen

#endif  // CENTURION_BLEND_MODE_HEADER
