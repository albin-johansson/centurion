#ifndef CENTURION_PIXEL_FORMAT_HEADER
#define CENTURION_PIXEL_FORMAT_HEADER

#include <SDL.h>

#include "../core/integers.hpp"

namespace cen {

/// \addtogroup video
/// \{

/**
 * \enum pixel_format
 *
 * \brief Represents different pixel formats.
 *
 * \see `SDL_PixelFormatEnum`
 *
 * \since 3.1.0
 */
enum class pixel_format : u32
{
  unknown = SDL_PIXELFORMAT_UNKNOWN,

  index1lsb = SDL_PIXELFORMAT_INDEX1LSB,
  index1msb = SDL_PIXELFORMAT_INDEX1MSB,
  index4lsb = SDL_PIXELFORMAT_INDEX4LSB,
  index4msb = SDL_PIXELFORMAT_INDEX4MSB,
  index8 = SDL_PIXELFORMAT_INDEX8,

#if SDL_VERSION_ATLEAST(2, 0, 14)
  xrgb4444 = SDL_PIXELFORMAT_XRGB4444,
  xbgr4444 = SDL_PIXELFORMAT_XBGR4444,

  xrgb1555 = SDL_PIXELFORMAT_XRGB1555,
  xbgr1555 = SDL_PIXELFORMAT_XBGR1555,

  xrgb8888 = SDL_PIXELFORMAT_XRGB8888,
  xbgr8888 = SDL_PIXELFORMAT_XBGR8888,
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  rgb332 = SDL_PIXELFORMAT_RGB332,
  rgb444 = SDL_PIXELFORMAT_RGB444,

#if SDL_VERSION_ATLEAST(2, 0, 12)
  bgr444 = SDL_PIXELFORMAT_BGR444,
#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

  rgb555 = SDL_PIXELFORMAT_RGB555,
  bgr555 = SDL_PIXELFORMAT_BGR555,

  argb4444 = SDL_PIXELFORMAT_ARGB4444,
  rgba4444 = SDL_PIXELFORMAT_RGBA4444,
  abgr4444 = SDL_PIXELFORMAT_ABGR4444,
  bgra4444 = SDL_PIXELFORMAT_BGRA4444,

  argb1555 = SDL_PIXELFORMAT_ARGB1555,
  rgba5551 = SDL_PIXELFORMAT_RGBA5551,
  abgr1555 = SDL_PIXELFORMAT_ABGR1555,
  bgra5551 = SDL_PIXELFORMAT_BGRA5551,

  rgb565 = SDL_PIXELFORMAT_RGB565,
  bgr565 = SDL_PIXELFORMAT_BGR565,

  rgb24 = SDL_PIXELFORMAT_RGB24,
  bgr24 = SDL_PIXELFORMAT_BGR24,

  rgb888 = SDL_PIXELFORMAT_RGB888,
  rgbx8888 = SDL_PIXELFORMAT_RGBX8888,
  bgr888 = SDL_PIXELFORMAT_BGR888,
  bgrx8888 = SDL_PIXELFORMAT_BGRX8888,

  argb8888 = SDL_PIXELFORMAT_ARGB8888,
  rgba8888 = SDL_PIXELFORMAT_RGBA8888,
  abgr8888 = SDL_PIXELFORMAT_ABGR8888,
  bgra8888 = SDL_PIXELFORMAT_BGRA8888,

  argb2101010 = SDL_PIXELFORMAT_ARGB2101010,

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
  rgba32 = SDL_PIXELFORMAT_RGBA8888,
  argb32 = SDL_PIXELFORMAT_ARGB8888,
  bgra32 = SDL_PIXELFORMAT_BGRA8888,
  abgr32 = SDL_PIXELFORMAT_ABGR8888,
#else
  rgba32 = SDL_PIXELFORMAT_ABGR8888,
  argb32 = SDL_PIXELFORMAT_BGRA8888,
  bgra32 = SDL_PIXELFORMAT_ARGB8888,
  abgr32 = SDL_PIXELFORMAT_RGBA8888,
#endif

  yv12 = SDL_PIXELFORMAT_YV12,
  iyuv = SDL_PIXELFORMAT_IYUV,
  yuy2 = SDL_PIXELFORMAT_YUY2,
  uyvy = SDL_PIXELFORMAT_UYVY,
  yvyu = SDL_PIXELFORMAT_YVYU,
  nv12 = SDL_PIXELFORMAT_NV12,
  nv21 = SDL_PIXELFORMAT_NV21,
  external_oes = SDL_PIXELFORMAT_EXTERNAL_OES
};

/// \name Pixel format comparison operators
/// \{

/**
 * \brief Indicates whether or not the two pixel format values are the same.
 *
 * \param lhs the left-hand side pixel format value.
 * \param rhs the right-hand side pixel format value.
 *
 * \return `true` if the pixel format values are the same; `false` otherwise.
 *
 * \since 3.1.0
 */
[[nodiscard]] constexpr auto operator==(const pixel_format lhs,
                                        const SDL_PixelFormatEnum rhs) noexcept -> bool
{
  return static_cast<SDL_PixelFormatEnum>(lhs) == rhs;
}

/// \copydoc operator==(pixel_format, SDL_PixelFormatEnum)
[[nodiscard]] constexpr auto operator==(const SDL_PixelFormatEnum lhs,
                                        const pixel_format rhs) noexcept -> bool
{
  return rhs == lhs;
}

/**
 * \brief Indicates whether or not the two pixel format values aren't the same.
 *
 * \param lhs the left-hand side pixel format value.
 * \param rhs the right-hand side pixel format value.
 *
 * \return `true` if the pixel format values aren't the same; `false` otherwise.
 *
 * \since 3.1.0
 */
[[nodiscard]] constexpr auto operator!=(const pixel_format lhs,
                                        const SDL_PixelFormatEnum rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \copydoc operator!=(pixel_format, SDL_PixelFormatEnum)
[[nodiscard]] constexpr auto operator!=(const SDL_PixelFormatEnum lhs,
                                        const pixel_format rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \} End of pixel format comparison operators

/// \} End of group video

}  // namespace cen

#endif  // CENTURION_PIXEL_FORMAT_HEADER
