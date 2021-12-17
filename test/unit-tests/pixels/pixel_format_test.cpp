#include <gtest/gtest.h>

#include <iostream>  // clog

#include "detail/sdl_version_at_least.hpp"
#include "pixels.hpp"
#include "system.hpp"

using Format = cen::PixelFormat;

TEST(PixelFormat, Values)
{
  ASSERT_EQ(ToUnderlying(Format::Unknown), SDL_PIXELFORMAT_UNKNOWN);
  ASSERT_EQ(ToUnderlying(Format::Index1LSB), SDL_PIXELFORMAT_INDEX1LSB);
  ASSERT_EQ(ToUnderlying(Format::Index1MSB), SDL_PIXELFORMAT_INDEX1MSB);
  ASSERT_EQ(ToUnderlying(Format::Index4LSB), SDL_PIXELFORMAT_INDEX4LSB);
  ASSERT_EQ(ToUnderlying(Format::Index4MSB), SDL_PIXELFORMAT_INDEX4MSB);
  ASSERT_EQ(ToUnderlying(Format::Index8), SDL_PIXELFORMAT_INDEX8);

  if constexpr (cen::detail::sdl_version_at_least(2, 0, 14)) {
    ASSERT_EQ(ToUnderlying(Format::XRGB4444), SDL_PIXELFORMAT_XRGB4444);
    ASSERT_EQ(ToUnderlying(Format::XBGR4444), SDL_PIXELFORMAT_XBGR4444);
    ASSERT_EQ(ToUnderlying(Format::XRGB1555), SDL_PIXELFORMAT_XRGB1555);
    ASSERT_EQ(ToUnderlying(Format::XBGR1555), SDL_PIXELFORMAT_XBGR1555);
    ASSERT_EQ(ToUnderlying(Format::XRGB8888), SDL_PIXELFORMAT_XRGB8888);
    ASSERT_EQ(ToUnderlying(Format::XBGR8888), SDL_PIXELFORMAT_XBGR8888);
  }

  ASSERT_EQ(ToUnderlying(Format::RGB332), SDL_PIXELFORMAT_RGB332);
  ASSERT_EQ(ToUnderlying(Format::RGB444), SDL_PIXELFORMAT_RGB444);
  ASSERT_EQ(ToUnderlying(Format::RGB555), SDL_PIXELFORMAT_RGB555);
  ASSERT_EQ(ToUnderlying(Format::BGR555), SDL_PIXELFORMAT_BGR555);

  if constexpr (cen::detail::sdl_version_at_least(2, 0, 12)) {
    ASSERT_EQ(ToUnderlying(Format::BGR444), SDL_PIXELFORMAT_BGR444);
  }

  ASSERT_EQ(ToUnderlying(Format::ARGB4444), SDL_PIXELFORMAT_ARGB4444);
  ASSERT_EQ(ToUnderlying(Format::RGBA4444), SDL_PIXELFORMAT_RGBA4444);
  ASSERT_EQ(ToUnderlying(Format::ABGR4444), SDL_PIXELFORMAT_ABGR4444);
  ASSERT_EQ(ToUnderlying(Format::BGRA4444), SDL_PIXELFORMAT_BGRA4444);

  ASSERT_EQ(ToUnderlying(Format::ARGB1555), SDL_PIXELFORMAT_ARGB1555);
  ASSERT_EQ(ToUnderlying(Format::RGBA5551), SDL_PIXELFORMAT_RGBA5551);
  ASSERT_EQ(ToUnderlying(Format::ABGR1555), SDL_PIXELFORMAT_ABGR1555);
  ASSERT_EQ(ToUnderlying(Format::BGRA5551), SDL_PIXELFORMAT_BGRA5551);

  ASSERT_EQ(ToUnderlying(Format::RGB565), SDL_PIXELFORMAT_RGB565);
  ASSERT_EQ(ToUnderlying(Format::BGR565), SDL_PIXELFORMAT_BGR565);

  ASSERT_EQ(ToUnderlying(Format::RGB24), SDL_PIXELFORMAT_RGB24);
  ASSERT_EQ(ToUnderlying(Format::BGR24), SDL_PIXELFORMAT_BGR24);

  ASSERT_EQ(ToUnderlying(Format::RGB888), SDL_PIXELFORMAT_RGB888);
  ASSERT_EQ(ToUnderlying(Format::RGBX8888), SDL_PIXELFORMAT_RGBX8888);
  ASSERT_EQ(ToUnderlying(Format::BGR888), SDL_PIXELFORMAT_BGR888);
  ASSERT_EQ(ToUnderlying(Format::BGRX8888), SDL_PIXELFORMAT_BGRX8888);

  ASSERT_EQ(ToUnderlying(Format::ARGB8888), SDL_PIXELFORMAT_ARGB8888);
  ASSERT_EQ(ToUnderlying(Format::RGBA8888), SDL_PIXELFORMAT_RGBA8888);
  ASSERT_EQ(ToUnderlying(Format::ABGR8888), SDL_PIXELFORMAT_ABGR8888);
  ASSERT_EQ(ToUnderlying(Format::BGRA8888), SDL_PIXELFORMAT_BGRA8888);

  ASSERT_EQ(ToUnderlying(Format::ARGB2101010), SDL_PIXELFORMAT_ARGB2101010);

  ASSERT_EQ(ToUnderlying(Format::RGBA32), SDL_PIXELFORMAT_RGBA32);
  ASSERT_EQ(ToUnderlying(Format::ARGB32), SDL_PIXELFORMAT_ARGB32);
  ASSERT_EQ(ToUnderlying(Format::BGRA32), SDL_PIXELFORMAT_BGRA32);
  ASSERT_EQ(ToUnderlying(Format::ABGR32), SDL_PIXELFORMAT_ABGR32);

  ASSERT_EQ(ToUnderlying(Format::YV12), SDL_PIXELFORMAT_YV12);
  ASSERT_EQ(ToUnderlying(Format::IYUV), SDL_PIXELFORMAT_IYUV);
  ASSERT_EQ(ToUnderlying(Format::YUY2), SDL_PIXELFORMAT_YUY2);
  ASSERT_EQ(ToUnderlying(Format::UYVY), SDL_PIXELFORMAT_UYVY);
  ASSERT_EQ(ToUnderlying(Format::YVYU), SDL_PIXELFORMAT_YVYU);
  ASSERT_EQ(ToUnderlying(Format::NV12), SDL_PIXELFORMAT_NV12);
  ASSERT_EQ(ToUnderlying(Format::NV21), SDL_PIXELFORMAT_NV21);
  ASSERT_EQ(ToUnderlying(Format::ExternalOES), SDL_PIXELFORMAT_EXTERNAL_OES);
}

TEST(PixelFormat, ToString)
{
  ASSERT_THROW(to_string(static_cast<Format>(0xFFFFFFFF)), cen::Error);

  ASSERT_EQ("Unknown", to_string(Format::Unknown));
  ASSERT_EQ("Index1LSB", to_string(Format::Index1LSB));
  ASSERT_EQ("Index1MSB", to_string(Format::Index1MSB));
  ASSERT_EQ("Index4LSB", to_string(Format::Index4LSB));
  ASSERT_EQ("Index4MSB", to_string(Format::Index4MSB));
  ASSERT_EQ("Index8", to_string(Format::Index8));

  ASSERT_EQ("RGB332", to_string(Format::RGB332));

  ASSERT_EQ("ARGB4444", to_string(Format::ARGB4444));
  ASSERT_EQ("RGBA4444", to_string(Format::RGBA4444));
  ASSERT_EQ("ABGR4444", to_string(Format::ABGR4444));
  ASSERT_EQ("BGRA4444", to_string(Format::BGRA4444));

  ASSERT_EQ("ARGB1555", to_string(Format::ARGB1555));
  ASSERT_EQ("RGBA5551", to_string(Format::RGBA5551));
  ASSERT_EQ("ABGR1555", to_string(Format::ABGR1555));
  ASSERT_EQ("BGRA5551", to_string(Format::BGRA5551));

  ASSERT_EQ("RGB565", to_string(Format::RGB565));
  ASSERT_EQ("BGR565", to_string(Format::BGR565));

  ASSERT_EQ("RGB24", to_string(Format::RGB24));
  ASSERT_EQ("BGR24", to_string(Format::BGR24));

  ASSERT_EQ("RGBX8888", to_string(Format::RGBX8888));
  ASSERT_EQ("BGRX8888", to_string(Format::BGRX8888));
  ASSERT_EQ("ARGB8888", to_string(Format::ARGB8888));
  ASSERT_EQ("RGBA8888", to_string(Format::RGBA8888));
  ASSERT_EQ("ABGR8888", to_string(Format::ABGR8888));
  ASSERT_EQ("BGRA8888", to_string(Format::BGRA8888));

  ASSERT_EQ("ARGB2101010", to_string(Format::ARGB2101010));

  ASSERT_EQ("YV12", to_string(Format::YV12));
  ASSERT_EQ("IYUV", to_string(Format::IYUV));
  ASSERT_EQ("YUY2", to_string(Format::YUY2));
  ASSERT_EQ("UYVY", to_string(Format::UYVY));
  ASSERT_EQ("YVYU", to_string(Format::YVYU));

  ASSERT_EQ("NV12", to_string(Format::NV12));
  ASSERT_EQ("NV21", to_string(Format::NV21));

  ASSERT_EQ("ExternalOES", to_string(Format::ExternalOES));

  if constexpr (cen::detail::sdl_version_at_least(2, 0, 14)) {
    ASSERT_EQ("XRGB4444", to_string(Format::XRGB4444));
    ASSERT_EQ("XBGR4444", to_string(Format::XBGR4444));
    ASSERT_EQ("XRGB1555", to_string(Format::XRGB1555));
    ASSERT_EQ("XBGR1555", to_string(Format::XBGR1555));
    ASSERT_EQ("XRGB8888", to_string(Format::XRGB8888));
    ASSERT_EQ("XBGR8888", to_string(Format::XBGR8888));
  }
  else if constexpr (cen::detail::sdl_version_at_least(2, 0, 12)) {
    ASSERT_EQ("BGR444", to_string(Format::BGR444));
  }

  std::clog << "Pixel format example: " << Format::RGBA8888 << '\n';
}
