#ifndef CENTURION_BYTE_ORDER_HEADER
#define CENTURION_BYTE_ORDER_HEADER

#include <SDL.h>

#include "../core/integers.hpp"

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

/// \copydoc swap_byte_order()
[[nodiscard]] inline auto swap_byte_order(const u32 value) noexcept -> u32
{
  return SDL_Swap32(value);
}

/// \copydoc swap_byte_order()
[[nodiscard]] inline auto swap_byte_order(const u64 value) noexcept -> u64
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
[[nodiscard]] inline auto swap_big_endian(const u16 value) noexcept -> u16
{
  return SDL_SwapBE16(value);
}

/// \copydoc swap_big_endian()
[[nodiscard]] inline auto swap_big_endian(const u32 value) noexcept -> u32
{
  return SDL_SwapBE32(value);
}

/// \copydoc swap_big_endian()
[[nodiscard]] inline auto swap_big_endian(const u64 value) noexcept -> u64
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
[[nodiscard]] inline auto swap_little_endian(const u16 value) noexcept -> u16
{
  return SDL_SwapLE16(value);
}

/// \copydoc swap_little_endian()
[[nodiscard]] inline auto swap_little_endian(const u32 value) noexcept -> u32
{
  return SDL_SwapLE32(value);
}

/// \copydoc swap_little_endian()
[[nodiscard]] inline auto swap_little_endian(const u64 value) noexcept -> u64
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

#endif  // CENTURION_BYTE_ORDER_HEADER
