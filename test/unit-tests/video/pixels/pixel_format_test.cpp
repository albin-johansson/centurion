/*
 * MIT License
 *
 * Copyright (c) 2019-2022 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <gtest/gtest.h>

#include <iostream>  // clog

#include "centurion/system.hpp"
#include "centurion/video/pixels.hpp"

using format = cen::pixel_format;

TEST(PixelFormat, Values)
{
  ASSERT_EQ(to_underlying(format::unknown), SDL_PIXELFORMAT_UNKNOWN);
  ASSERT_EQ(to_underlying(format::index1_lsb), SDL_PIXELFORMAT_INDEX1LSB);
  ASSERT_EQ(to_underlying(format::index1_msb), SDL_PIXELFORMAT_INDEX1MSB);
  ASSERT_EQ(to_underlying(format::index4_lsb), SDL_PIXELFORMAT_INDEX4LSB);
  ASSERT_EQ(to_underlying(format::index4_msb), SDL_PIXELFORMAT_INDEX4MSB);
  ASSERT_EQ(to_underlying(format::index8), SDL_PIXELFORMAT_INDEX8);

#if SDL_VERSION_ATLEAST(2, 0, 14)
  ASSERT_EQ(to_underlying(format::xrgb4444), SDL_PIXELFORMAT_XRGB4444);
  ASSERT_EQ(to_underlying(format::xbgr4444), SDL_PIXELFORMAT_XBGR4444);
  ASSERT_EQ(to_underlying(format::xrgb1555), SDL_PIXELFORMAT_XRGB1555);
  ASSERT_EQ(to_underlying(format::xbgr1555), SDL_PIXELFORMAT_XBGR1555);
  ASSERT_EQ(to_underlying(format::xrgb8888), SDL_PIXELFORMAT_XRGB8888);
  ASSERT_EQ(to_underlying(format::xbgr8888), SDL_PIXELFORMAT_XBGR8888);
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  ASSERT_EQ(to_underlying(format::rgb332), SDL_PIXELFORMAT_RGB332);
  ASSERT_EQ(to_underlying(format::rgb444), SDL_PIXELFORMAT_RGB444);
  ASSERT_EQ(to_underlying(format::rgb555), SDL_PIXELFORMAT_RGB555);
  ASSERT_EQ(to_underlying(format::bgr555), SDL_PIXELFORMAT_BGR555);

#if SDL_VERSION_ATLEAST(2, 0, 12)
  ASSERT_EQ(to_underlying(format::bgr444), SDL_PIXELFORMAT_BGR444);
#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

  ASSERT_EQ(to_underlying(format::argb4444), SDL_PIXELFORMAT_ARGB4444);
  ASSERT_EQ(to_underlying(format::rgba4444), SDL_PIXELFORMAT_RGBA4444);
  ASSERT_EQ(to_underlying(format::abgr4444), SDL_PIXELFORMAT_ABGR4444);
  ASSERT_EQ(to_underlying(format::bgra4444), SDL_PIXELFORMAT_BGRA4444);

  ASSERT_EQ(to_underlying(format::argb1555), SDL_PIXELFORMAT_ARGB1555);
  ASSERT_EQ(to_underlying(format::rgba5551), SDL_PIXELFORMAT_RGBA5551);
  ASSERT_EQ(to_underlying(format::abgr1555), SDL_PIXELFORMAT_ABGR1555);
  ASSERT_EQ(to_underlying(format::bgra5551), SDL_PIXELFORMAT_BGRA5551);

  ASSERT_EQ(to_underlying(format::rgb565), SDL_PIXELFORMAT_RGB565);
  ASSERT_EQ(to_underlying(format::bgr565), SDL_PIXELFORMAT_BGR565);

  ASSERT_EQ(to_underlying(format::rgb24), SDL_PIXELFORMAT_RGB24);
  ASSERT_EQ(to_underlying(format::bgr24), SDL_PIXELFORMAT_BGR24);

  ASSERT_EQ(to_underlying(format::rgb888), SDL_PIXELFORMAT_RGB888);
  ASSERT_EQ(to_underlying(format::rgbx8888), SDL_PIXELFORMAT_RGBX8888);
  ASSERT_EQ(to_underlying(format::bgr888), SDL_PIXELFORMAT_BGR888);
  ASSERT_EQ(to_underlying(format::bgrx8888), SDL_PIXELFORMAT_BGRX8888);

  ASSERT_EQ(to_underlying(format::argb8888), SDL_PIXELFORMAT_ARGB8888);
  ASSERT_EQ(to_underlying(format::rgba8888), SDL_PIXELFORMAT_RGBA8888);
  ASSERT_EQ(to_underlying(format::abgr8888), SDL_PIXELFORMAT_ABGR8888);
  ASSERT_EQ(to_underlying(format::bgra8888), SDL_PIXELFORMAT_BGRA8888);

  ASSERT_EQ(to_underlying(format::argb2101010), SDL_PIXELFORMAT_ARGB2101010);

  ASSERT_EQ(to_underlying(format::rgba32), SDL_PIXELFORMAT_RGBA32);
  ASSERT_EQ(to_underlying(format::argb32), SDL_PIXELFORMAT_ARGB32);
  ASSERT_EQ(to_underlying(format::bgra32), SDL_PIXELFORMAT_BGRA32);
  ASSERT_EQ(to_underlying(format::abgr32), SDL_PIXELFORMAT_ABGR32);

  ASSERT_EQ(to_underlying(format::yv12), SDL_PIXELFORMAT_YV12);
  ASSERT_EQ(to_underlying(format::iyuv), SDL_PIXELFORMAT_IYUV);
  ASSERT_EQ(to_underlying(format::yuy2), SDL_PIXELFORMAT_YUY2);
  ASSERT_EQ(to_underlying(format::uyvy), SDL_PIXELFORMAT_UYVY);
  ASSERT_EQ(to_underlying(format::yvyu), SDL_PIXELFORMAT_YVYU);
  ASSERT_EQ(to_underlying(format::nv12), SDL_PIXELFORMAT_NV12);
  ASSERT_EQ(to_underlying(format::nv21), SDL_PIXELFORMAT_NV21);
  ASSERT_EQ(to_underlying(format::external_oes), SDL_PIXELFORMAT_EXTERNAL_OES);
}

TEST(PixelFormat, ToString)
{
  ASSERT_THROW(to_string(static_cast<format>(0xFFFFFFFF)), cen::exception);

  ASSERT_EQ("unknown", to_string(format::unknown));
  ASSERT_EQ("index1_lsb", to_string(format::index1_lsb));
  ASSERT_EQ("index1_msb", to_string(format::index1_msb));
  ASSERT_EQ("index4_lsb", to_string(format::index4_lsb));
  ASSERT_EQ("index4_msb", to_string(format::index4_msb));
  ASSERT_EQ("index8", to_string(format::index8));

  ASSERT_EQ("rgb332", to_string(format::rgb332));

  ASSERT_EQ("argb4444", to_string(format::argb4444));
  ASSERT_EQ("rgba4444", to_string(format::rgba4444));
  ASSERT_EQ("abgr4444", to_string(format::abgr4444));
  ASSERT_EQ("bgra4444", to_string(format::bgra4444));

  ASSERT_EQ("argb1555", to_string(format::argb1555));
  ASSERT_EQ("rgba5551", to_string(format::rgba5551));
  ASSERT_EQ("abgr1555", to_string(format::abgr1555));
  ASSERT_EQ("bgra5551", to_string(format::bgra5551));

  ASSERT_EQ("rgb565", to_string(format::rgb565));
  ASSERT_EQ("bgr565", to_string(format::bgr565));

  ASSERT_EQ("rgb24", to_string(format::rgb24));
  ASSERT_EQ("bgr24", to_string(format::bgr24));

  ASSERT_EQ("rgbx8888", to_string(format::rgbx8888));
  ASSERT_EQ("bgrx8888", to_string(format::bgrx8888));
  ASSERT_EQ("argb8888", to_string(format::argb8888));
  ASSERT_EQ("rgba8888", to_string(format::rgba8888));
  ASSERT_EQ("abgr8888", to_string(format::abgr8888));
  ASSERT_EQ("bgra8888", to_string(format::bgra8888));

  ASSERT_EQ("argb2101010", to_string(format::argb2101010));

  ASSERT_EQ("yv12", to_string(format::yv12));
  ASSERT_EQ("iyuv", to_string(format::iyuv));
  ASSERT_EQ("yuy2", to_string(format::yuy2));
  ASSERT_EQ("uyvy", to_string(format::uyvy));
  ASSERT_EQ("yvyu", to_string(format::yvyu));

  ASSERT_EQ("nv12", to_string(format::nv12));
  ASSERT_EQ("nv21", to_string(format::nv21));

  ASSERT_EQ("external_oes", to_string(format::external_oes));

#if SDL_VERSION_ATLEAST(2, 0, 14)

  ASSERT_EQ("xrgb4444", to_string(format::xrgb4444));
  ASSERT_EQ("xbgr4444", to_string(format::xbgr4444));
  ASSERT_EQ("xrgb1555", to_string(format::xrgb1555));
  ASSERT_EQ("xbgr1555", to_string(format::xbgr1555));
  ASSERT_EQ("xrgb8888", to_string(format::xrgb8888));
  ASSERT_EQ("xbgr8888", to_string(format::xbgr8888));

#elif SDL_VERSION_ATLEAST(2, 0, 12)

  ASSERT_EQ("bgr444", to_string(format::bgr444));

#endif

  std::cout << "pixel_format::rgba8888 == " << format::rgba8888 << '\n';
}
