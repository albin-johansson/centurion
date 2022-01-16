#ifndef CENTURION_ENDIAN_HPP_
#define CENTURION_ENDIAN_HPP_

#include <SDL.h>

#include "common.hpp"

namespace cen {

/** Swaps the byte order of the specified value. */
[[nodiscard]] inline auto swap_byte_order(const uint16 value) noexcept -> uint16
{
  return SDL_Swap16(value);
}

[[nodiscard]] inline auto swap_byte_order(const uint32 value) noexcept -> uint32
{
  return SDL_Swap32(value);
}

[[nodiscard]] inline auto swap_byte_order(const uint64 value) noexcept -> uint64
{
  return SDL_Swap64(value);
}

[[nodiscard]] inline auto swap_byte_order(const float value) noexcept -> float
{
  return SDL_SwapFloat(value);
}

/* Swaps a big endian value to a little endian value. */
[[nodiscard]] inline auto swap_big_endian(const uint16 value) noexcept -> uint16
{
  return SDL_SwapBE16(value);
}

[[nodiscard]] inline auto swap_big_endian(const uint32 value) noexcept -> uint32
{
  return SDL_SwapBE32(value);
}

[[nodiscard]] inline auto swap_big_endian(const uint64 value) noexcept -> uint64
{
  return SDL_SwapBE64(value);
}

[[nodiscard]] inline auto swap_big_endian(const float value) noexcept -> float
{
  return SDL_SwapFloatBE(value);
}

/* Swaps a little endian value to a big endian value. */
[[nodiscard]] inline auto swap_little_endian(const uint16 value) noexcept -> uint16
{
  return SDL_SwapLE16(value);
}

[[nodiscard]] inline auto swap_little_endian(const uint32 value) noexcept -> uint32
{
  return SDL_SwapLE32(value);
}

[[nodiscard]] inline auto swap_little_endian(const uint64 value) noexcept -> uint64
{
  return SDL_SwapLE64(value);
}

[[nodiscard]] inline auto swap_little_endian(const float value) noexcept -> float
{
  return SDL_SwapFloatLE(value);
}

}  // namespace cen

#endif  // CENTURION_ENDIAN_HPP_
