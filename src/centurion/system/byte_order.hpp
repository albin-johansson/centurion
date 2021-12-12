#ifndef CENTURION_SYSTEM_BYTE_ORDER_HPP_
#define CENTURION_SYSTEM_BYTE_ORDER_HPP_

#include <SDL.h>

#include "../core/common.hpp"

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
[[nodiscard]] inline auto swap_byte_order(const Uint16 value) noexcept -> Uint16
{
  return SDL_Swap16(value);
}

/// \copydoc swap_byte_order()
[[nodiscard]] inline auto swap_byte_order(const Uint32 value) noexcept -> Uint32
{
  return SDL_Swap32(value);
}

/// \copydoc swap_byte_order()
[[nodiscard]] inline auto swap_byte_order(const Uint64 value) noexcept -> Uint64
{
  return SDL_Swap64(value);
}

/// \copydoc swap_byte_order()
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
[[nodiscard]] inline auto swap_big_endian(const Uint16 value) noexcept -> Uint16
{
  return SDL_SwapBE16(value);
}

/// \copydoc swap_big_endian()
[[nodiscard]] inline auto swap_big_endian(const Uint32 value) noexcept -> Uint32
{
  return SDL_SwapBE32(value);
}

/// \copydoc swap_big_endian()
[[nodiscard]] inline auto swap_big_endian(const Uint64 value) noexcept -> Uint64
{
  return SDL_SwapBE64(value);
}

/// \copydoc swap_big_endian()
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
[[nodiscard]] inline auto swap_little_endian(const Uint16 value) noexcept -> Uint16
{
  return SDL_SwapLE16(value);
}

/// \copydoc swap_little_endian()
[[nodiscard]] inline auto swap_little_endian(const Uint32 value) noexcept -> Uint32
{
  return SDL_SwapLE32(value);
}

/// \copydoc swap_little_endian()
[[nodiscard]] inline auto swap_little_endian(const Uint64 value) noexcept -> Uint64
{
  return SDL_SwapLE64(value);
}

/// \copydoc swap_little_endian()
[[nodiscard]] inline auto swap_little_endian(const float value) noexcept -> float
{
  return SDL_SwapFloatLE(value);
}

/// \} End of swap from little endian to native format

/// \} End of group system

}  // namespace cen

#endif  // CENTURION_SYSTEM_BYTE_ORDER_HPP_
