/*
 * MIT License
 *
 * Copyright (c) 2019-2020 Albin Johansson
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

/**
 * @file pixel_format.hpp
 *
 * @brief Provides the `pixel_format` enum.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

#ifndef CENTURION_PIXEL_FORMAT_HEADER
#define CENTURION_PIXEL_FORMAT_HEADER

#include <SDL.h>

#include "centurion_api.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/**
 * @enum pixel_format
 *
 * @ingroup graphics
 *
 * @brief Mirrors the values of the `SDL_PixelFormatEnum`.
 *
 * @see `SDL_PixelFormatEnum`
 *
 * @since 3.1.0
 *
 * @headerfile pixel_format.hpp
 */
enum class pixel_format {
  unknown = SDL_PIXELFORMAT_UNKNOWN,

  index1lsb = SDL_PIXELFORMAT_INDEX1LSB,
  index1msb = SDL_PIXELFORMAT_INDEX1MSB,
  index4lsb = SDL_PIXELFORMAT_INDEX4LSB,
  index4msb = SDL_PIXELFORMAT_INDEX4MSB,
  index8 = SDL_PIXELFORMAT_INDEX8,

  rgb332 = SDL_PIXELFORMAT_RGB332,
  rgb444 = SDL_PIXELFORMAT_RGB444,
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

/**
 * @brief Indicates whether or not the two pixel format values are the same.
 *
 * @ingroup graphics
 *
 * @param lhs the left-hand side pixel format value.
 * @param rhs the right-hand side pixel format value.
 *
 * @return `true` if the pixel format values are the same; `false` otherwise.
 *
 * @since 3.1.0
 */
[[nodiscard]] inline constexpr auto operator==(pixel_format lhs,
                                               SDL_PixelFormatEnum rhs) noexcept
    -> bool
{
  return static_cast<SDL_PixelFormatEnum>(lhs) == rhs;
}

/**
 * @copydoc operator==(pixel_format, SDL_PixelFormatEnum)
 *
 * @ingroup graphics
 */
[[nodiscard]] inline constexpr auto operator==(SDL_PixelFormatEnum lhs,
                                               pixel_format rhs) noexcept
    -> bool
{
  return rhs == lhs;
}

/**
 * @brief Indicates whether or not the two pixel format values aren't the same.
 *
 * @ingroup graphics
 *
 * @param lhs the left-hand side pixel format value.
 * @param rhs the right-hand side pixel format value.
 *
 * @return `true` if the pixel format values aren't the same; `false` otherwise.
 *
 * @since 3.1.0
 */
[[nodiscard]] inline constexpr auto operator!=(pixel_format lhs,
                                               SDL_PixelFormatEnum rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/**
 * @copydoc operator!=(pixel_format, SDL_PixelFormatEnum)
 *
 * @ingroup graphics
 */
[[nodiscard]] inline constexpr auto operator!=(SDL_PixelFormatEnum lhs,
                                               pixel_format rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

}  // namespace cen

#endif  // CENTURION_PIXEL_FORMAT_HEADER