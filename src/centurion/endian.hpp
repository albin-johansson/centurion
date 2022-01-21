#ifndef CENTURION_ENDIAN_HPP_
#define CENTURION_ENDIAN_HPP_

#include <SDL.h>

#include "common.hpp"

namespace cen {

/**
 * \ingroup system
 * \defgroup endian Endian
 *
 * \brief Provides utilities related to the system endianness.
 */

/// \addtogroup endian
/// \{

/**
 * \brief Indicates whether the CPU uses little-endian byte ordering.
 *
 * \return `true` if the CPI is little-endian; `false` otherwise.
 */
[[nodiscard]] constexpr auto is_little_endian() noexcept -> bool
{
  return SDL_BYTEORDER == SDL_LIL_ENDIAN;
}

/**
 * \brief Indicates whether the CPU uses big-endian byte ordering.
 *
 * \return `true` if the CPI is big-endian; `false` otherwise.
 */
[[nodiscard]] constexpr auto is_big_endian() noexcept -> bool
{
  return SDL_BYTEORDER == SDL_BIG_ENDIAN;
}

/**
 * \brief Swaps the byte order of an integer.
 *
 * \param value the value that will be swapped.
 *
 * \return the swapped integer.
 */
[[nodiscard]] inline auto swap_byte_order(const uint16 value) noexcept -> uint16
{
  return SDL_Swap16(value);
}

/// \copydoc swap_byte_order(uint16)
[[nodiscard]] inline auto swap_byte_order(const uint32 value) noexcept -> uint32
{
  return SDL_Swap32(value);
}

/// \copydoc swap_byte_order(uint32)
[[nodiscard]] inline auto swap_byte_order(const uint64 value) noexcept -> uint64
{
  return SDL_Swap64(value);
}

/**
 * \brief Swaps the byte order of a float.
 *
 * \param value the value that will be swapped.
 *
 * \return the swapped float.
 */
[[nodiscard]] inline auto swap_byte_order(const float value) noexcept -> float
{
  return SDL_SwapFloat(value);
}

/**
 * \brief Swaps the byte order from big endian to the native endianness.
 *
 * \param value the value that will be swapped.
 *
 * \return the value in the native endianness.
 */
[[nodiscard]] inline auto swap_big_endian(const uint16 value) noexcept -> uint16
{
  return SDL_SwapBE16(value);
}

/// \copydoc swap_big_endian()
[[nodiscard]] inline auto swap_big_endian(const uint32 value) noexcept -> uint32
{
  return SDL_SwapBE32(value);
}

/// \copydoc swap_big_endian()
[[nodiscard]] inline auto swap_big_endian(const uint64 value) noexcept -> uint64
{
  return SDL_SwapBE64(value);
}

/// \copydoc swap_big_endian()
[[nodiscard]] inline auto swap_big_endian(const float value) noexcept -> float
{
  return SDL_SwapFloatBE(value);
}

/**
 * \brief Swaps the byte order from little endian to the native endianness.
 *
 * \param value the value that will be swapped.
 *
 * \return the value in the native endianness.
 */
[[nodiscard]] inline auto swap_little_endian(const uint16 value) noexcept -> uint16
{
  return SDL_SwapLE16(value);
}

/// \copydoc swap_little_endian()
[[nodiscard]] inline auto swap_little_endian(const uint32 value) noexcept -> uint32
{
  return SDL_SwapLE32(value);
}

/// \copydoc swap_little_endian()
[[nodiscard]] inline auto swap_little_endian(const uint64 value) noexcept -> uint64
{
  return SDL_SwapLE64(value);
}

/// \copydoc swap_little_endian()
[[nodiscard]] inline auto swap_little_endian(const float value) noexcept -> float
{
  return SDL_SwapFloatLE(value);
}

/// \} End of group endian

}  // namespace cen

#endif  // CENTURION_ENDIAN_HPP_
