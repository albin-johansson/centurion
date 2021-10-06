#ifndef CENTURION_PIXEL_FORMAT_HEADER
#define CENTURION_PIXEL_FORMAT_HEADER

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../core/exception.hpp"
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

/// \name String conversions
/// \{

/**
 * \brief Returns a textual version of the supplied pixel format.
 *
 * \details This function returns a string that mirrors the name of the enumerator, e.g.
 * `to_string(pixel_format::rgba8888) == "rgba8888"`.
 *
 * \param format the enumerator that will be converted.
 *
 * \return a string that mirrors the name of the enumerator.
 *
 * \throws cen_error if the enumerator is not recognized.
 *
 * \since 6.2.0
 */
[[nodiscard]] constexpr auto to_string(const pixel_format format) -> std::string_view
{
  switch (format) {
    case pixel_format::unknown:
      return "unknown";

    case pixel_format::index1lsb:
      return "index1lsb";

    case pixel_format::index1msb:
      return "index1msb";

    case pixel_format::index4lsb:
      return "index4lsb";

    case pixel_format::index4msb:
      return "index4msb";

    case pixel_format::index8:
      return "index8";

    case pixel_format::rgb332:
      return "rgb332";

    case pixel_format::argb4444:
      return "argb4444";

    case pixel_format::rgba4444:
      return "rgba4444";

    case pixel_format::abgr4444:
      return "abgr4444";

    case pixel_format::bgra4444:
      return "bgra4444";

    case pixel_format::argb1555:
      return "argb1555";

    case pixel_format::rgba5551:
      return "rgba5551";

    case pixel_format::abgr1555:
      return "abgr1555";

    case pixel_format::bgra5551:
      return "bgra5551";

    case pixel_format::rgb565:
      return "rgb565";

    case pixel_format::bgr565:
      return "bgr565";

    case pixel_format::rgb24:
      return "rgb24";

    case pixel_format::bgr24:
      return "bgr24";

    case pixel_format::rgbx8888:
      return "rgbx8888";

    case pixel_format::bgrx8888:
      return "bgrx8888";

    case pixel_format::argb8888:
      return "argb8888";

    case pixel_format::rgba8888:
      return "rgba8888";

    case pixel_format::abgr8888:
      return "abgr8888";

    case pixel_format::bgra8888:
      return "bgra8888";

    case pixel_format::argb2101010:
      return "argb2101010";

    case pixel_format::yv12:
      return "yv12";

    case pixel_format::iyuv:
      return "iyuv";

    case pixel_format::yuy2:
      return "yuy2";

    case pixel_format::uyvy:
      return "uyvy";

    case pixel_format::yvyu:
      return "yvyu";

    case pixel_format::nv12:
      return "nv12";

    case pixel_format::nv21:
      return "nv21";

    case pixel_format::external_oes:
      return "external_oes";

#if SDL_VERSION_ATLEAST(2, 0, 14)

    case pixel_format::xrgb4444:
      return "xrgb4444";

    case pixel_format::xbgr4444:
      return "xbgr4444";

    case pixel_format::xrgb1555:
      return "xrgb1555";

    case pixel_format::xbgr1555:
      return "xbgr1555";

    case pixel_format::xrgb8888:
      return "xrgb8888";

    case pixel_format::xbgr8888:
      return "xbgr8888";

#elif SDL_VERSION_ATLEAST(2, 0, 12)

    case pixel_format::bgr444:  // Equal to xbgr4444
      return "bgr444";

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

    default:
      throw cen_error{"Did not recognize pixel format mode!"};
  }
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of a pixel format enumerator.
 *
 * \param stream the output stream that will be used.
 * \param format the enumerator that will be printed.
 *
 * \see `to_string(pixel_format)`
 *
 * \return the used stream.
 *
 * \since 6.2.0
 */
inline auto operator<<(std::ostream& stream, const pixel_format format) -> std::ostream&
{
  return stream << to_string(format);
}

/// \} End of streaming

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
