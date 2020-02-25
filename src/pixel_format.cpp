#ifndef CENTURION_PIXEL_FORMAT_SOURCE
#define CENTURION_PIXEL_FORMAT_SOURCE

#include "pixel_format.h"

namespace centurion {
namespace video {

CENTURION_DEF
bool operator==(PixelFormat lhs, SDL_PixelFormatEnum rhs) noexcept
{
  return static_cast<SDL_PixelFormatEnum>(lhs) == rhs;
}

CENTURION_DEF
bool operator==(SDL_PixelFormatEnum lhs, PixelFormat rhs) noexcept
{
  return lhs == static_cast<SDL_PixelFormatEnum>(rhs);
}

CENTURION_DEF
bool operator!=(PixelFormat lhs, SDL_PixelFormatEnum rhs) noexcept
{
  return static_cast<SDL_PixelFormatEnum>(lhs) != rhs;
}

CENTURION_DEF
bool operator!=(SDL_PixelFormatEnum lhs, PixelFormat rhs) noexcept
{
  return lhs != static_cast<SDL_PixelFormatEnum>(rhs);
}

}  // namespace video
}  // namespace centurion

#endif  // CENTURION_PIXEL_FORMAT_SOURCE