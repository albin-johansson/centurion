#ifndef CENTURION_PIXEL_FORMAT_HEADER
#define CENTURION_PIXEL_FORMAT_HEADER

#include <SDL.h>

#include "centurion_api.h"

namespace centurion {

/**
 * The PixelFormat enum class mirrors the values of the SDL_PixelFormatEnum.
 *
 * @since 3.1.0
 */
enum class PixelFormat {
  Unknown = SDL_PIXELFORMAT_UNKNOWN,

  Index1LSB = SDL_PIXELFORMAT_INDEX1LSB,
  Index1MSB = SDL_PIXELFORMAT_INDEX1MSB,
  Index4LSB = SDL_PIXELFORMAT_INDEX4LSB,
  Index4MSB = SDL_PIXELFORMAT_INDEX4MSB,
  Index8 = SDL_PIXELFORMAT_INDEX8,

  RGB332 = SDL_PIXELFORMAT_RGB332,
  RGB444 = SDL_PIXELFORMAT_RGB444,
  RGB555 = SDL_PIXELFORMAT_RGB555,
  BGR555 = SDL_PIXELFORMAT_BGR555,

  ARGB4444 = SDL_PIXELFORMAT_ARGB4444,
  RGBA4444 = SDL_PIXELFORMAT_RGBA4444,
  ABGR4444 = SDL_PIXELFORMAT_ABGR4444,
  BGRA4444 = SDL_PIXELFORMAT_BGRA4444,

  ARGB1555 = SDL_PIXELFORMAT_ARGB1555,
  RGBA5551 = SDL_PIXELFORMAT_RGBA5551,
  ABGR1555 = SDL_PIXELFORMAT_ABGR1555,
  BGRA5551 = SDL_PIXELFORMAT_BGRA5551,

  RGB565 = SDL_PIXELFORMAT_RGB565,
  BGR565 = SDL_PIXELFORMAT_BGR565,

  RGB24 = SDL_PIXELFORMAT_RGB24,
  BGR24 = SDL_PIXELFORMAT_BGR24,

  RGB888 = SDL_PIXELFORMAT_RGB888,
  RGBX8888 = SDL_PIXELFORMAT_RGBX8888,
  BGR888 = SDL_PIXELFORMAT_BGR888,
  BGRX8888 = SDL_PIXELFORMAT_BGRX8888,

  ARGB8888 = SDL_PIXELFORMAT_ARGB8888,
  RGBA8888 = SDL_PIXELFORMAT_RGBA8888,
  ABGR8888 = SDL_PIXELFORMAT_ABGR8888,
  BGRA8888 = SDL_PIXELFORMAT_BGRA8888,

  ARGB2101010 = SDL_PIXELFORMAT_ARGB2101010,

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
  RGBA32 = SDL_PIXELFORMAT_RGBA8888,
  ARGB32 = SDL_PIXELFORMAT_ARGB8888,
  BGRA32 = SDL_PIXELFORMAT_BGRA8888,
  ABGR32 = SDL_PIXELFORMAT_ABGR8888,
#else
  RGBA32 = SDL_PIXELFORMAT_ABGR8888,
  ARGB32 = SDL_PIXELFORMAT_BGRA8888,
  BGRA32 = SDL_PIXELFORMAT_ARGB8888,
  ABGR32 = SDL_PIXELFORMAT_RGBA8888,
#endif

  YV12 = SDL_PIXELFORMAT_YV12,
  IYUV = SDL_PIXELFORMAT_IYUV,
  YUY2 = SDL_PIXELFORMAT_YUY2,
  UYVY = SDL_PIXELFORMAT_UYVY,
  YVYU = SDL_PIXELFORMAT_YVYU,
  NV12 = SDL_PIXELFORMAT_NV12,
  NV21 = SDL_PIXELFORMAT_NV21,
  ExternalOES = SDL_PIXELFORMAT_EXTERNAL_OES
};

/**
 * Indicates whether or not the two pixel format values are the same.
 *
 * @param lhs the lhs Centurion pixel format.
 * @param rhs the rhs SDL pixel format.
 * @return true if the pixel format values are the same; false otherwise.
 * @since 3.1.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator==(PixelFormat lhs,
                              SDL_PixelFormatEnum rhs) noexcept;

/**
 * Indicates whether or not the two pixel format values are the same.
 *
 * @param lhs the lhs SDL pixel format.
 * @param rhs the rhs Centurion pixel format.
 * @return true if the pixel format values are the same; false otherwise.
 * @since 3.1.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator==(SDL_PixelFormatEnum lhs,
                              PixelFormat rhs) noexcept;

/**
 * Indicates whether or not the two pixel format values aren't the same.
 *
 * @param lhs the lhs Centurion pixel format.
 * @param rhs the rhs SDL pixel format.
 * @return true if the pixel format values aren't the same; false otherwise.
 * @since 3.1.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator!=(PixelFormat lhs,
                              SDL_PixelFormatEnum rhs) noexcept;

/**
 * Indicates whether or not the two pixel format values aren't the same.
 *
 * @param lhs the lhs SDL pixel format.
 * @param rhs the rhs Centurion pixel format.
 * @return true if the pixel format values aren't the same; false otherwise.
 * @since 3.1.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator!=(SDL_PixelFormatEnum lhs,
                              PixelFormat rhs) noexcept;

}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "pixel_format.cpp"
#endif

#endif  // CENTURION_PIXEL_FORMAT_HEADER