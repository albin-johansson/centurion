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

#ifndef CENTURION_BYTE_ORDER_HEADER
#define CENTURION_BYTE_ORDER_HEADER

#include <SDL.h>

#include "centurion_cfg.hpp"
#include "integers.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/// \addtogroup system
/// \{

/// \name Byte order swapping
/// \{

/**
 * \brief Swaps the byte order of the specified value and returns the result.
 *
 * \param value the value to swap the byte order of.
 *
 * \return the swapped byte order value.
 *
 * \since 5.3.0
 */
[[nodiscard]] inline auto swap_byte_order(const u16 value) noexcept -> u16
{
  return SDL_Swap16(value);
}

/**
 * \copydoc swap_byte_order()
 */
[[nodiscard]] inline auto swap_byte_order(const u32 value) noexcept -> u32
{
  return SDL_Swap32(value);
}

/**
 * \copydoc swap_byte_order()
 */
[[nodiscard]] inline auto swap_byte_order(const u64 value) noexcept -> u64
{
  return SDL_Swap64(value);
}

/**
 * \copydoc swap_byte_order()
 */
[[nodiscard]] inline auto swap_byte_order(const float value) noexcept -> float
{
  return SDL_SwapFloat(value);
}

/// \} End of byte order swapping

/// \name Swap from big endian to native format
/// \{

/**
 * \brief Swaps the big endian value to a little endian value and returns it.
 *
 * \param value the big endian value that will be swapped.
 *
 * \return the resulting little endian value.
 *
 * \since 5.3.0
 */
[[nodiscard]] inline auto swap_big_endian(const u16 value) noexcept -> u16
{
  return SDL_SwapBE16(value);
}

/**
 * \copydoc swap_big_endian()
 */
[[nodiscard]] inline auto swap_big_endian(const u32 value) noexcept -> u32
{
  return SDL_SwapBE32(value);
}

/**
 * \copydoc swap_big_endian()
 */
[[nodiscard]] inline auto swap_big_endian(const u64 value) noexcept -> u64
{
  return SDL_SwapBE64(value);
}

/**
 * \copydoc swap_big_endian()
 */
[[nodiscard]] inline auto swap_big_endian(const float value) noexcept -> float
{
  return SDL_SwapFloatBE(value);
}

/// \} End of swap from big endian to native format

/// \name Swap from little endian to native format
/// \{

/**
 * \brief Swaps the little endian value to a big endian value and returns it.
 *
 * \param value the little endian value that will be swapped.
 *
 * \return the resulting big endian value.
 *
 * \since 5.3.0
 */
[[nodiscard]] inline auto swap_little_endian(const u16 value) noexcept -> u16
{
  return SDL_SwapLE16(value);
}

/**
 * \copydoc swap_little_endian()
 */
[[nodiscard]] inline auto swap_little_endian(const u32 value) noexcept -> u32
{
  return SDL_SwapLE32(value);
}

/**
 * \copydoc swap_little_endian()
 */
[[nodiscard]] inline auto swap_little_endian(const u64 value) noexcept -> u64
{
  return SDL_SwapLE64(value);
}

/**
 * \copydoc swap_little_endian()
 */
[[nodiscard]] inline auto swap_little_endian(const float value) noexcept
    -> float
{
  return SDL_SwapFloatLE(value);
}

/// \} End of swap from little endian to native format
/// \} End of system group

}  // namespace cen

#endif  // CENTURION_BYTE_ORDER_HEADER
