#ifndef CENTURION_ENDIAN_HPP_
#define CENTURION_ENDIAN_HPP_

#include <SDL.h>

namespace cen {

/** Swaps the byte order of the specified value. */
[[nodiscard]] inline auto SwapByteOrder(const Uint16 value) noexcept -> Uint16
{
  return SDL_Swap16(value);
}

[[nodiscard]] inline auto SwapByteOrder(const Uint32 value) noexcept -> Uint32
{
  return SDL_Swap32(value);
}

[[nodiscard]] inline auto SwapByteOrder(const Uint64 value) noexcept -> Uint64
{
  return SDL_Swap64(value);
}

[[nodiscard]] inline auto SwapByteOrder(const float value) noexcept -> float
{
  return SDL_SwapFloat(value);
}

/* Swaps a big endian value to a little endian value. */
[[nodiscard]] inline auto SwapBigEndian(const Uint16 value) noexcept -> Uint16
{
  return SDL_SwapBE16(value);
}

[[nodiscard]] inline auto SwapBigEndian(const Uint32 value) noexcept -> Uint32
{
  return SDL_SwapBE32(value);
}

[[nodiscard]] inline auto SwapBigEndian(const Uint64 value) noexcept -> Uint64
{
  return SDL_SwapBE64(value);
}

[[nodiscard]] inline auto SwapBigEndian(const float value) noexcept -> float
{
  return SDL_SwapFloatBE(value);
}

/* Swaps a little endian value to a big endian value. */
[[nodiscard]] inline auto SwapLittleEndian(const Uint16 value) noexcept -> Uint16
{
  return SDL_SwapLE16(value);
}

[[nodiscard]] inline auto SwapLittleEndian(const Uint32 value) noexcept -> Uint32
{
  return SDL_SwapLE32(value);
}

[[nodiscard]] inline auto SwapLittleEndian(const Uint64 value) noexcept -> Uint64
{
  return SDL_SwapLE64(value);
}

[[nodiscard]] inline auto SwapLittleEndian(const float value) noexcept -> float
{
  return SDL_SwapFloatLE(value);
}

}  // namespace cen

#endif  // CENTURION_ENDIAN_HPP_
