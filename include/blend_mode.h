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

#include "centurion_api.h"

namespace centurion {

/**
 * The BlendMode enum class mirrors the SDL_BlendMode enum.
 *
 * @since 3.0.0
 */
enum class BlendMode {
  None = SDL_BLENDMODE_NONE,
  Blend = SDL_BLENDMODE_BLEND,
  Add = SDL_BLENDMODE_ADD,
  Mod = SDL_BLENDMODE_MOD,
  Mul = SDL_BLENDMODE_MUL,
  Invalid = SDL_BLENDMODE_INVALID
};

/**
 * Indicates whether the two blend mode values represent the same blend mode.
 *
 * @param a the lhs Centurion blend mode.
 * @param b the rhs SDL blend mode.
 * @return true if the values represent the same blend mode; false otherwise.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator==(BlendMode a, SDL_BlendMode b) noexcept;

/**
 * Indicates whether the two blend mode values represent the same blend mode.
 *
 * @param a the lhs SDL blend mode.
 * @param b the rhs Centurion blend mode.
 * @return true if the values represent the same blend mode; false otherwise.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator==(SDL_BlendMode a, BlendMode b) noexcept;

/**
 * Indicates whether the two blend mode values don't represent the same blend
 * mode.
 *
 * @param a the lhs Centurion blend mode.
 * @param b the rhs SDL blend mode.
 * @return true if the values don't represent the same blend mode; false
 * otherwise.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator!=(BlendMode a, SDL_BlendMode b) noexcept;

/**
 * Indicates whether the two blend mode values don't represent the same blend
 * mode.
 *
 * @param a the lhs SDL blend mode.
 * @param b the rhs Centurion blend mode.
 * @return true if the values don't represent the same blend mode; false
 * otherwise.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator!=(SDL_BlendMode a, BlendMode b) noexcept;

}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "blend_mode.cpp"
#endif

#endif  // CENTURION_BLEND_MODE_HEADER
