#include <gtest/gtest.h>

#include <iostream>  // clog

#include "detail/sdl_version_at_least.hpp"
#include "pixels.hpp"
#include "system.hpp"

TEST(PixelFormat, Values)
{
  ASSERT_EQ(cen::ToUnderlying(cen::PixelFormat::Unknown), SDL_PIXELFORMAT_UNKNOWN);
  ASSERT_EQ(cen::ToUnderlying(cen::PixelFormat::Index1LSB), SDL_PIXELFORMAT_INDEX1LSB);
  ASSERT_EQ(cen::ToUnderlying(cen::PixelFormat::Index1MSB), SDL_PIXELFORMAT_INDEX1MSB);
  ASSERT_EQ(cen::ToUnderlying(cen::PixelFormat::Index4LSB), SDL_PIXELFORMAT_INDEX4LSB);
  ASSERT_EQ(cen::ToUnderlying(cen::PixelFormat::Index4MSB), SDL_PIXELFORMAT_INDEX4MSB);
  ASSERT_EQ(cen::ToUnderlying(cen::PixelFormat::Index8), SDL_PIXELFORMAT_INDEX8);

  if constexpr (cen::detail::sdl_version_at_least(2, 0, 14)) {
    ASSERT_EQ(cen::ToUnderlying(cen::PixelFormat::XRGB4444), SDL_PIXELFORMAT_XRGB4444);
    ASSERT_EQ(cen::ToUnderlying(cen::PixelFormat::XBGR4444), SDL_PIXELFORMAT_XBGR4444);
    ASSERT_EQ(cen::ToUnderlying(cen::PixelFormat::XRGB1555), SDL_PIXELFORMAT_XRGB1555);
    ASSERT_EQ(cen::ToUnderlying(cen::PixelFormat::XBGR1555), SDL_PIXELFORMAT_XBGR1555);
    ASSERT_EQ(cen::ToUnderlying(cen::PixelFormat::XRGB8888), SDL_PIXELFORMAT_XRGB8888);
    ASSERT_EQ(cen::ToUnderlying(cen::PixelFormat::XBGR8888), SDL_PIXELFORMAT_XBGR8888);
  }

  ASSERT_EQ(cen::ToUnderlying(cen::PixelFormat::RGB332), SDL_PIXELFORMAT_RGB332);
  ASSERT_EQ(cen::ToUnderlying(cen::PixelFormat::RGB444), SDL_PIXELFORMAT_RGB444);
  ASSERT_EQ(cen::ToUnderlying(cen::PixelFormat::RGB555), SDL_PIXELFORMAT_RGB555);
  ASSERT_EQ(cen::ToUnderlying(cen::PixelFormat::BGR555), SDL_PIXELFORMAT_BGR555);

  if constexpr (cen::detail::sdl_version_at_least(2, 0, 12)) {
    ASSERT_EQ(cen::ToUnderlying(cen::PixelFormat::BGR444), SDL_PIXELFORMAT_BGR444);
  }

  ASSERT_EQ(cen::ToUnderlying(cen::PixelFormat::ARGB4444), SDL_PIXELFORMAT_ARGB4444);
  ASSERT_EQ(cen::ToUnderlying(cen::PixelFormat::RGBA4444), SDL_PIXELFORMAT_RGBA4444);
  ASSERT_EQ(cen::ToUnderlying(cen::PixelFormat::ABGR4444), SDL_PIXELFORMAT_ABGR4444);
  ASSERT_EQ(cen::ToUnderlying(cen::PixelFormat::BGRA4444), SDL_PIXELFORMAT_BGRA4444);

  ASSERT_EQ(cen::ToUnderlying(cen::PixelFormat::ARGB1555), SDL_PIXELFORMAT_ARGB1555);
  ASSERT_EQ(cen::ToUnderlying(cen::PixelFormat::RGBA5551), SDL_PIXELFORMAT_RGBA5551);
  ASSERT_EQ(cen::ToUnderlying(cen::PixelFormat::ABGR1555), SDL_PIXELFORMAT_ABGR1555);
  ASSERT_EQ(cen::ToUnderlying(cen::PixelFormat::BGRA5551), SDL_PIXELFORMAT_BGRA5551);

  ASSERT_EQ(cen::ToUnderlying(cen::PixelFormat::RGB565), SDL_PIXELFORMAT_RGB565);
  ASSERT_EQ(cen::ToUnderlying(cen::PixelFormat::BGR565), SDL_PIXELFORMAT_BGR565);

  ASSERT_EQ(cen::ToUnderlying(cen::PixelFormat::RGB24), SDL_PIXELFORMAT_RGB24);
  ASSERT_EQ(cen::ToUnderlying(cen::PixelFormat::BGR24), SDL_PIXELFORMAT_BGR24);

  ASSERT_EQ(cen::ToUnderlying(cen::PixelFormat::RGB888), SDL_PIXELFORMAT_RGB888);
  ASSERT_EQ(cen::ToUnderlying(cen::PixelFormat::RGBX8888), SDL_PIXELFORMAT_RGBX8888);
  ASSERT_EQ(cen::ToUnderlying(cen::PixelFormat::BGR888), SDL_PIXELFORMAT_BGR888);
  ASSERT_EQ(cen::ToUnderlying(cen::PixelFormat::BGRX8888), SDL_PIXELFORMAT_BGRX8888);

  ASSERT_EQ(cen::ToUnderlying(cen::PixelFormat::ARGB8888), SDL_PIXELFORMAT_ARGB8888);
  ASSERT_EQ(cen::ToUnderlying(cen::PixelFormat::RGBA8888), SDL_PIXELFORMAT_RGBA8888);
  ASSERT_EQ(cen::ToUnderlying(cen::PixelFormat::ABGR8888), SDL_PIXELFORMAT_ABGR8888);
  ASSERT_EQ(cen::ToUnderlying(cen::PixelFormat::BGRA8888), SDL_PIXELFORMAT_BGRA8888);

  ASSERT_EQ(cen::ToUnderlying(cen::PixelFormat::ARGB2101010), SDL_PIXELFORMAT_ARGB2101010);

  ASSERT_EQ(cen::ToUnderlying(cen::PixelFormat::RGBA32), SDL_PIXELFORMAT_RGBA32);
  ASSERT_EQ(cen::ToUnderlying(cen::PixelFormat::ARGB32), SDL_PIXELFORMAT_ARGB32);
  ASSERT_EQ(cen::ToUnderlying(cen::PixelFormat::BGRA32), SDL_PIXELFORMAT_BGRA32);
  ASSERT_EQ(cen::ToUnderlying(cen::PixelFormat::ABGR32), SDL_PIXELFORMAT_ABGR32);

  ASSERT_EQ(cen::ToUnderlying(cen::PixelFormat::YV12), SDL_PIXELFORMAT_YV12);
  ASSERT_EQ(cen::ToUnderlying(cen::PixelFormat::IYUV), SDL_PIXELFORMAT_IYUV);
  ASSERT_EQ(cen::ToUnderlying(cen::PixelFormat::YUY2), SDL_PIXELFORMAT_YUY2);
  ASSERT_EQ(cen::ToUnderlying(cen::PixelFormat::UYVY), SDL_PIXELFORMAT_UYVY);
  ASSERT_EQ(cen::ToUnderlying(cen::PixelFormat::YVYU), SDL_PIXELFORMAT_YVYU);
  ASSERT_EQ(cen::ToUnderlying(cen::PixelFormat::NV12), SDL_PIXELFORMAT_NV12);
  ASSERT_EQ(cen::ToUnderlying(cen::PixelFormat::NV21), SDL_PIXELFORMAT_NV21);
  ASSERT_EQ(cen::ToUnderlying(cen::PixelFormat::ExternalOES), SDL_PIXELFORMAT_EXTERNAL_OES);
}

TEST(PixelFormat, ToString)
{
  ASSERT_THROW(cen::to_string(static_cast<cen::PixelFormat>(0xFFFFFFFF)), cen::Error);

  ASSERT_EQ("Unknown", cen::to_string(cen::PixelFormat::Unknown));
  ASSERT_EQ("Index1LSB", cen::to_string(cen::PixelFormat::Index1LSB));
  ASSERT_EQ("Index1MSB", cen::to_string(cen::PixelFormat::Index1MSB));
  ASSERT_EQ("Index4LSB", cen::to_string(cen::PixelFormat::Index4LSB));
  ASSERT_EQ("Index4MSB", cen::to_string(cen::PixelFormat::Index4MSB));
  ASSERT_EQ("Index8", cen::to_string(cen::PixelFormat::Index8));

  ASSERT_EQ("RGB332", cen::to_string(cen::PixelFormat::RGB332));

  ASSERT_EQ("ARGB4444", cen::to_string(cen::PixelFormat::ARGB4444));
  ASSERT_EQ("RGBA4444", cen::to_string(cen::PixelFormat::RGBA4444));
  ASSERT_EQ("ABGR4444", cen::to_string(cen::PixelFormat::ABGR4444));
  ASSERT_EQ("BGRA4444", cen::to_string(cen::PixelFormat::BGRA4444));

  ASSERT_EQ("ARGB1555", cen::to_string(cen::PixelFormat::ARGB1555));
  ASSERT_EQ("RGBA5551", cen::to_string(cen::PixelFormat::RGBA5551));
  ASSERT_EQ("ABGR1555", cen::to_string(cen::PixelFormat::ABGR1555));
  ASSERT_EQ("BGRA5551", cen::to_string(cen::PixelFormat::BGRA5551));

  ASSERT_EQ("RGB565", cen::to_string(cen::PixelFormat::RGB565));
  ASSERT_EQ("BGR565", cen::to_string(cen::PixelFormat::BGR565));

  ASSERT_EQ("RGB24", cen::to_string(cen::PixelFormat::RGB24));
  ASSERT_EQ("BGR24", cen::to_string(cen::PixelFormat::BGR24));

  ASSERT_EQ("RGBX8888", cen::to_string(cen::PixelFormat::RGBX8888));
  ASSERT_EQ("BGRX8888", cen::to_string(cen::PixelFormat::BGRX8888));
  ASSERT_EQ("ARGB8888", cen::to_string(cen::PixelFormat::ARGB8888));
  ASSERT_EQ("RGBA8888", cen::to_string(cen::PixelFormat::RGBA8888));
  ASSERT_EQ("ABGR8888", cen::to_string(cen::PixelFormat::ABGR8888));
  ASSERT_EQ("BGRA8888", cen::to_string(cen::PixelFormat::BGRA8888));

  ASSERT_EQ("ARGB2101010", cen::to_string(cen::PixelFormat::ARGB2101010));

  ASSERT_EQ("YV12", cen::to_string(cen::PixelFormat::YV12));
  ASSERT_EQ("IYUV", cen::to_string(cen::PixelFormat::IYUV));
  ASSERT_EQ("YUY2", cen::to_string(cen::PixelFormat::YUY2));
  ASSERT_EQ("UYVY", cen::to_string(cen::PixelFormat::UYVY));
  ASSERT_EQ("YVYU", cen::to_string(cen::PixelFormat::YVYU));

  ASSERT_EQ("NV12", cen::to_string(cen::PixelFormat::NV12));
  ASSERT_EQ("NV21", cen::to_string(cen::PixelFormat::NV21));

  ASSERT_EQ("ExternalOES", cen::to_string(cen::PixelFormat::ExternalOES));

  if constexpr (cen::detail::sdl_version_at_least(2, 0, 14)) {
    ASSERT_EQ("XRGB4444", cen::to_string(cen::PixelFormat::XRGB4444));
    ASSERT_EQ("XBGR4444", cen::to_string(cen::PixelFormat::XBGR4444));
    ASSERT_EQ("XRGB1555", cen::to_string(cen::PixelFormat::XRGB1555));
    ASSERT_EQ("XBGR1555", cen::to_string(cen::PixelFormat::XBGR1555));
    ASSERT_EQ("XRGB8888", cen::to_string(cen::PixelFormat::XRGB8888));
    ASSERT_EQ("XBGR8888", cen::to_string(cen::PixelFormat::XBGR8888));
  }
  else if constexpr (cen::detail::sdl_version_at_least(2, 0, 12)) {
    ASSERT_EQ("BGR444", cen::to_string(cen::PixelFormat::BGR444));
  }

  std::clog << "Pixel format example: " << cen::PixelFormat::RGBA8888 << '\n';
}
