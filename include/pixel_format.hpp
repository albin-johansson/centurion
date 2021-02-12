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

#ifndef CENTURION_PIXEL_FORMAT_HEADER
#define CENTURION_PIXEL_FORMAT_HEADER

#include <SDL.h>

#include <type_traits>  // true_type, false_type

#include "centurion_cfg.hpp"
#include "color.hpp"
#include "czstring.hpp"
#include "detail/owner_handle_api.hpp"
#include "exception.hpp"
#include "integers.hpp"
#include "not_null.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/// \addtogroup graphics
/// \{

/**
 * \enum pixel_format
 *
 * \brief Mirrors the values of the `SDL_PixelFormatEnum`.
 *
 * \see `SDL_PixelFormatEnum`
 *
 * \since 3.1.0
 *
 * \headerfile pixel_format.hpp
 */
enum class pixel_format
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
  bgr444 = SDL_PIXELFORMAT_BGR444,
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

template <typename B>
class basic_pixel_format_info;

/**
 * \typedef pixel_format_info
 *
 * \brief Represents an owning pixel format info instance.
 *
 * \since 5.2.0
 */
using pixel_format_info = basic_pixel_format_info<std::true_type>;

/**
 * \typedef pixel_format_info_handle
 *
 * \brief Represents a non-owning pixel format info instance.
 *
 * \since 5.2.0
 */
using pixel_format_info_handle = basic_pixel_format_info<std::false_type>;

/**
 * \class basic_pixel_format_info
 *
 * \brief Provides information about a pixel format.
 *
 * \details See `pixel_format_info` and `pixel_format_info_handle` for owning
 * and non-owning versions of this class.
 *
 * \note This class is part of the centurion owner/handle framework.
 *
 * \tparam B `std::true_type` for owning semantics; `std::false_type` otherwise.
 *
 * \see pixel_format
 * \see pixel_format_info
 * \see pixel_format_info_handle
 * \see SDL_PixelFormat
 * \see SDL_PixelFormatEnum
 *
 * \since 5.2.0
 *
 * \headerfile pixel_format.hpp
 */
template <typename B>
class basic_pixel_format_info final
{
 public:
  /**
   * \brief Creates a pixel format info instance based on an existing pointer.
   *
   * \note Ownership of the supplied pointer might be claimed, depending on the
   * ownership semantics of the class.
   *
   * \param ptr a pointer to the associated pixel format.
   *
   * \throws exception if the supplied pointer is null *and* the class has
   * owning semantics.
   *
   * \since 5.2.0
   */
  explicit basic_pixel_format_info(SDL_PixelFormat* ptr) noexcept(!B::value)
      : m_format{ptr}
  {
    if constexpr (B::value) {
      if (!m_format) {
        throw exception{"Null pixel format!"};
      }
    }
  }

  /**
   * \brief Creates an owning instance based on a pixel format.
   *
   * \tparam BB dummy template parameter for SFINAE.
   *
   * \param format the associated pixel format.
   *
   * \throws sdl_error if the pixel format info could not be obtained.
   *
   * \since 5.2.0
   */
  template <typename BB = B, detail::is_owner<BB> = true>
  explicit basic_pixel_format_info(const pixel_format format)
      : m_format{SDL_AllocFormat(static_cast<u32>(format))}
  {
    if (!m_format) {
      throw sdl_error{};
    }
  }

  /**
   * \brief Creates a handle based on an owning pixel format info instance.
   *
   * \tparam BB dummy parameter for SFINAE.
   *
   * \param info the associated pixel format info instance.
   *
   * \since 5.2.0
   */
  template <typename BB = B, detail::is_handle<BB> = true>
  explicit basic_pixel_format_info(const pixel_format_info& info) noexcept
      : m_format{info.get()}
  {}

  /**
   * \brief Returns a color that corresponds to a masked pixel value.
   *
   * \param pixel the masked pixel value.
   *
   * \return a color that corresponds to a pixel value, according to the format.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto pixel_to_rgb(const u32 pixel) const noexcept -> color
  {
    u8 red{};
    u8 green{};
    u8 blue{};
    SDL_GetRGB(pixel, m_format, &red, &green, &blue);
    return color{red, green, blue};
  }

  /**
   * \brief Returns a color that corresponds to a masked pixel value.
   *
   * \param pixel the masked pixel value.
   *
   * \return a color that corresponds to a pixel value, according to the format.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto pixel_to_rgba(const u32 pixel) const noexcept -> color
  {
    u8 red{};
    u8 green{};
    u8 blue{};
    u8 alpha{};
    SDL_GetRGBA(pixel, m_format, &red, &green, &blue, &alpha);
    return color{red, green, blue, alpha};
  }

  /**
   * \brief Returns a pixel color value based on the RGB values of a color.
   *
   * \note The alpha component is assumed to be `0xFF`, i.e. fully opaque.
   *
   * \param color the color that will be converted.
   *
   * \return a masked pixel color value, based on the pixel format.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto rgb_to_pixel(const color& color) const noexcept -> u32
  {
    return SDL_MapRGB(m_format, color.red(), color.green(), color.blue());
  }

  /**
   * \brief Returns a pixel color value based on the RGBA values of a color.
   *
   * \param color the color that will be converted.
   *
   * \return a masked pixel color value, based on the pixel format.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto rgba_to_pixel(const color& color) const noexcept -> u32
  {
    return SDL_MapRGBA(m_format,
                       color.red(),
                       color.green(),
                       color.blue(),
                       color.alpha());
  }

  /**
   * \brief Returns the associated pixel format.
   *
   * \return the associated pixel format.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto format() const noexcept -> pixel_format
  {
    return static_cast<pixel_format>(m_format->format);
  }

  /**
   * \brief Returns a human-readable name associated with the format.
   *
   * \details This function never returns a null-pointer, instead it returns
   * "SDL_PIXELFORMAT_UNKNOWN" if the format is ill-formed.
   *
   * \return a human-readable name associated with the format.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto name() const noexcept -> not_null<czstring>
  {
    return SDL_GetPixelFormatName(m_format->format);
  }

  /**
   * \brief Indicates whether or not a handle holds a non-null pointer.
   *
   * \tparam BB dummy template parameter for SFINAE.
   *
   * \return `true` if the handle holds a non-null pointer; `false` otherwise.
   *
   * \since 5.2.0
   */
  template <typename BB = B, detail::is_handle<BB> = true>
  [[nodiscard]] explicit operator bool() const noexcept
  {
    return m_format;
  }

  /**
   * \brief Returns a pointer to the associated pixel format instance.
   *
   * \warning Do not claim ownership of the returned pointer.
   *
   * \return a pointer to the internal pixel format.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto get() const noexcept -> SDL_PixelFormat*
  {
    return m_format.get();
  }

 private:
  struct deleter final
  {
    void operator()(SDL_PixelFormat* format) noexcept
    {
      SDL_FreeFormat(format);
    }
  };
  detail::pointer_manager<B, SDL_PixelFormat, deleter> m_format;
};

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
                                        const SDL_PixelFormatEnum rhs) noexcept
    -> bool
{
  return static_cast<SDL_PixelFormatEnum>(lhs) == rhs;
}

/**
 * \copydoc operator==(pixel_format, SDL_PixelFormatEnum)
 */
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
                                        const SDL_PixelFormatEnum rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/**
 * \copydoc operator!=(pixel_format, SDL_PixelFormatEnum)
 */
[[nodiscard]] constexpr auto operator!=(const SDL_PixelFormatEnum lhs,
                                        const pixel_format rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \}

}  // namespace cen

#endif  // CENTURION_PIXEL_FORMAT_HEADER