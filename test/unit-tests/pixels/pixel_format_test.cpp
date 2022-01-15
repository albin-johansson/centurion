#include <gtest/gtest.h>

#include <iostream>  // clog

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

#if SDL_VERSION_ATLEAST(2, 0, 14)
  ASSERT_EQ(ToUnderlying(Format::XRGB4444), SDL_PIXELFORMAT_XRGB4444);
  ASSERT_EQ(ToUnderlying(Format::XBGR4444), SDL_PIXELFORMAT_XBGR4444);
  ASSERT_EQ(ToUnderlying(Format::XRGB1555), SDL_PIXELFORMAT_XRGB1555);
  ASSERT_EQ(ToUnderlying(Format::XBGR1555), SDL_PIXELFORMAT_XBGR1555);
  ASSERT_EQ(ToUnderlying(Format::XRGB8888), SDL_PIXELFORMAT_XRGB8888);
  ASSERT_EQ(ToUnderlying(Format::XBGR8888), SDL_PIXELFORMAT_XBGR8888);
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  ASSERT_EQ(ToUnderlying(Format::RGB332), SDL_PIXELFORMAT_RGB332);
  ASSERT_EQ(ToUnderlying(Format::RGB444), SDL_PIXELFORMAT_RGB444);
  ASSERT_EQ(ToUnderlying(Format::RGB555), SDL_PIXELFORMAT_RGB555);
  ASSERT_EQ(ToUnderlying(Format::BGR555), SDL_PIXELFORMAT_BGR555);

#if SDL_VERSION_ATLEAST(2, 0, 12)
  ASSERT_EQ(ToUnderlying(Format::BGR444), SDL_PIXELFORMAT_BGR444);
#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

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
  ASSERT_THROW(ToString(static_cast<Format>(0xFFFFFFFF)), cen::exception);

  ASSERT_EQ("Unknown", ToString(Format::Unknown));
  ASSERT_EQ("Index1LSB", ToString(Format::Index1LSB));
  ASSERT_EQ("Index1MSB", ToString(Format::Index1MSB));
  ASSERT_EQ("Index4LSB", ToString(Format::Index4LSB));
  ASSERT_EQ("Index4MSB", ToString(Format::Index4MSB));
  ASSERT_EQ("Index8", ToString(Format::Index8));

  ASSERT_EQ("RGB332", ToString(Format::RGB332));

  ASSERT_EQ("ARGB4444", ToString(Format::ARGB4444));
  ASSERT_EQ("RGBA4444", ToString(Format::RGBA4444));
  ASSERT_EQ("ABGR4444", ToString(Format::ABGR4444));
  ASSERT_EQ("BGRA4444", ToString(Format::BGRA4444));

  ASSERT_EQ("ARGB1555", ToString(Format::ARGB1555));
  ASSERT_EQ("RGBA5551", ToString(Format::RGBA5551));
  ASSERT_EQ("ABGR1555", ToString(Format::ABGR1555));
  ASSERT_EQ("BGRA5551", ToString(Format::BGRA5551));

  ASSERT_EQ("RGB565", ToString(Format::RGB565));
  ASSERT_EQ("BGR565", ToString(Format::BGR565));

  ASSERT_EQ("RGB24", ToString(Format::RGB24));
  ASSERT_EQ("BGR24", ToString(Format::BGR24));

  ASSERT_EQ("RGBX8888", ToString(Format::RGBX8888));
  ASSERT_EQ("BGRX8888", ToString(Format::BGRX8888));
  ASSERT_EQ("ARGB8888", ToString(Format::ARGB8888));
  ASSERT_EQ("RGBA8888", ToString(Format::RGBA8888));
  ASSERT_EQ("ABGR8888", ToString(Format::ABGR8888));
  ASSERT_EQ("BGRA8888", ToString(Format::BGRA8888));

  ASSERT_EQ("ARGB2101010", ToString(Format::ARGB2101010));

  ASSERT_EQ("YV12", ToString(Format::YV12));
  ASSERT_EQ("IYUV", ToString(Format::IYUV));
  ASSERT_EQ("YUY2", ToString(Format::YUY2));
  ASSERT_EQ("UYVY", ToString(Format::UYVY));
  ASSERT_EQ("YVYU", ToString(Format::YVYU));

  ASSERT_EQ("NV12", ToString(Format::NV12));
  ASSERT_EQ("NV21", ToString(Format::NV21));

  ASSERT_EQ("ExternalOES", ToString(Format::ExternalOES));

#if SDL_VERSION_ATLEAST(2, 0, 14)

  ASSERT_EQ("XRGB4444", ToString(Format::XRGB4444));
  ASSERT_EQ("XBGR4444", ToString(Format::XBGR4444));
  ASSERT_EQ("XRGB1555", ToString(Format::XRGB1555));
  ASSERT_EQ("XBGR1555", ToString(Format::XBGR1555));
  ASSERT_EQ("XRGB8888", ToString(Format::XRGB8888));
  ASSERT_EQ("XBGR8888", ToString(Format::XBGR8888));

#elif SDL_VERSION_ATLEAST(2, 0, 12)

  ASSERT_EQ("BGR444", ToString(Format::BGR444));

#endif

  std::clog << "Pixel format example: " << Format::RGBA8888 << '\n';
}
