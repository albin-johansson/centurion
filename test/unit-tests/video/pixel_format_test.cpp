#include "video/pixel_format.hpp"

#include <gtest/gtest.h>

#include <iostream>  // cout

#include "system/cpu.hpp"

TEST(PixelFormat, Values)
{
  {
    ASSERT_EQ(cen::pixel_format::unknown, SDL_PIXELFORMAT_UNKNOWN);
    ASSERT_EQ(cen::pixel_format::index1lsb, SDL_PIXELFORMAT_INDEX1LSB);
    ASSERT_EQ(cen::pixel_format::index1msb, SDL_PIXELFORMAT_INDEX1MSB);
    ASSERT_EQ(cen::pixel_format::index4lsb, SDL_PIXELFORMAT_INDEX4LSB);
    ASSERT_EQ(cen::pixel_format::index4msb, SDL_PIXELFORMAT_INDEX4MSB);
    ASSERT_EQ(cen::pixel_format::index8, SDL_PIXELFORMAT_INDEX8);

#if SDL_VERSION_ATLEAST(2, 0, 14)
    ASSERT_EQ(cen::pixel_format::xrgb4444, SDL_PIXELFORMAT_XRGB4444);
    ASSERT_EQ(cen::pixel_format::xbgr4444, SDL_PIXELFORMAT_XBGR4444);
    ASSERT_EQ(cen::pixel_format::xrgb1555, SDL_PIXELFORMAT_XRGB1555);
    ASSERT_EQ(cen::pixel_format::xbgr1555, SDL_PIXELFORMAT_XBGR1555);
    ASSERT_EQ(cen::pixel_format::xrgb8888, SDL_PIXELFORMAT_XRGB8888);
    ASSERT_EQ(cen::pixel_format::xbgr8888, SDL_PIXELFORMAT_XBGR8888);
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

    ASSERT_EQ(cen::pixel_format::rgb332, SDL_PIXELFORMAT_RGB332);
    ASSERT_EQ(cen::pixel_format::rgb444, SDL_PIXELFORMAT_RGB444);
#if SDL_VERSION_ATLEAST(2, 0, 12)
    ASSERT_EQ(cen::pixel_format::bgr444, SDL_PIXELFORMAT_BGR444);
#endif  // SDL_VERSION_ATLEAST(2, 0, 12)
    ASSERT_EQ(cen::pixel_format::rgb555, SDL_PIXELFORMAT_RGB555);
    ASSERT_EQ(cen::pixel_format::bgr555, SDL_PIXELFORMAT_BGR555);

    ASSERT_EQ(cen::pixel_format::argb4444, SDL_PIXELFORMAT_ARGB4444);
    ASSERT_EQ(cen::pixel_format::rgba4444, SDL_PIXELFORMAT_RGBA4444);
    ASSERT_EQ(cen::pixel_format::abgr4444, SDL_PIXELFORMAT_ABGR4444);
    ASSERT_EQ(cen::pixel_format::bgra4444, SDL_PIXELFORMAT_BGRA4444);

    ASSERT_EQ(cen::pixel_format::argb1555, SDL_PIXELFORMAT_ARGB1555);
    ASSERT_EQ(cen::pixel_format::rgba5551, SDL_PIXELFORMAT_RGBA5551);
    ASSERT_EQ(cen::pixel_format::abgr1555, SDL_PIXELFORMAT_ABGR1555);
    ASSERT_EQ(cen::pixel_format::bgra5551, SDL_PIXELFORMAT_BGRA5551);

    ASSERT_EQ(cen::pixel_format::rgb565, SDL_PIXELFORMAT_RGB565);
    ASSERT_EQ(cen::pixel_format::bgr565, SDL_PIXELFORMAT_BGR565);

    ASSERT_EQ(cen::pixel_format::rgb24, SDL_PIXELFORMAT_RGB24);
    ASSERT_EQ(cen::pixel_format::bgr24, SDL_PIXELFORMAT_BGR24);

    ASSERT_EQ(cen::pixel_format::rgb888, SDL_PIXELFORMAT_RGB888);
    ASSERT_EQ(cen::pixel_format::rgbx8888, SDL_PIXELFORMAT_RGBX8888);
    ASSERT_EQ(cen::pixel_format::bgr888, SDL_PIXELFORMAT_BGR888);
    ASSERT_EQ(cen::pixel_format::bgrx8888, SDL_PIXELFORMAT_BGRX8888);

    ASSERT_EQ(cen::pixel_format::argb8888, SDL_PIXELFORMAT_ARGB8888);
    ASSERT_EQ(cen::pixel_format::rgba8888, SDL_PIXELFORMAT_RGBA8888);
    ASSERT_EQ(cen::pixel_format::abgr8888, SDL_PIXELFORMAT_ABGR8888);
    ASSERT_EQ(cen::pixel_format::bgra8888, SDL_PIXELFORMAT_BGRA8888);

    ASSERT_EQ(cen::pixel_format::argb2101010, SDL_PIXELFORMAT_ARGB2101010);

    if constexpr (cen::cpu::is_big_endian())
    {
      ASSERT_EQ(cen::pixel_format::rgba32, SDL_PIXELFORMAT_RGBA8888);
      ASSERT_EQ(cen::pixel_format::argb32, SDL_PIXELFORMAT_ARGB8888);
      ASSERT_EQ(cen::pixel_format::bgra32, SDL_PIXELFORMAT_BGRA8888);
      ASSERT_EQ(cen::pixel_format::abgr32, SDL_PIXELFORMAT_ABGR8888);
    }
    else
    {
      ASSERT_EQ(cen::pixel_format::rgba32, SDL_PIXELFORMAT_ABGR8888);
      ASSERT_EQ(cen::pixel_format::argb32, SDL_PIXELFORMAT_BGRA8888);
      ASSERT_EQ(cen::pixel_format::bgra32, SDL_PIXELFORMAT_ARGB8888);
      ASSERT_EQ(cen::pixel_format::abgr32, SDL_PIXELFORMAT_RGBA8888);
    }

    ASSERT_EQ(cen::pixel_format::yv12, SDL_PIXELFORMAT_YV12);
    ASSERT_EQ(cen::pixel_format::iyuv, SDL_PIXELFORMAT_IYUV);
    ASSERT_EQ(cen::pixel_format::yuy2, SDL_PIXELFORMAT_YUY2);
    ASSERT_EQ(cen::pixel_format::uyvy, SDL_PIXELFORMAT_UYVY);
    ASSERT_EQ(cen::pixel_format::yvyu, SDL_PIXELFORMAT_YVYU);
    ASSERT_EQ(cen::pixel_format::nv12, SDL_PIXELFORMAT_NV12);
    ASSERT_EQ(cen::pixel_format::nv21, SDL_PIXELFORMAT_NV21);
    ASSERT_EQ(cen::pixel_format::external_oes, SDL_PIXELFORMAT_EXTERNAL_OES);
  }

  {
    ASSERT_EQ(SDL_PIXELFORMAT_UNKNOWN, cen::pixel_format::unknown);
    ASSERT_EQ(SDL_PIXELFORMAT_INDEX1LSB, cen::pixel_format::index1lsb);
    ASSERT_EQ(SDL_PIXELFORMAT_INDEX1MSB, cen::pixel_format::index1msb);
    ASSERT_EQ(SDL_PIXELFORMAT_INDEX4LSB, cen::pixel_format::index4lsb);
    ASSERT_EQ(SDL_PIXELFORMAT_INDEX4MSB, cen::pixel_format::index4msb);
    ASSERT_EQ(SDL_PIXELFORMAT_INDEX8, cen::pixel_format::index8);

#if SDL_VERSION_ATLEAST(2, 0, 14)
    ASSERT_EQ(SDL_PIXELFORMAT_XRGB4444, cen::pixel_format::xrgb4444);
    ASSERT_EQ(SDL_PIXELFORMAT_XBGR4444, cen::pixel_format::xbgr4444);
    ASSERT_EQ(SDL_PIXELFORMAT_XRGB1555, cen::pixel_format::xrgb1555);
    ASSERT_EQ(SDL_PIXELFORMAT_XBGR1555, cen::pixel_format::xbgr1555);
    ASSERT_EQ(SDL_PIXELFORMAT_XRGB8888, cen::pixel_format::xrgb8888);
    ASSERT_EQ(SDL_PIXELFORMAT_XBGR8888, cen::pixel_format::xbgr8888);
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

    ASSERT_EQ(SDL_PIXELFORMAT_RGB332, cen::pixel_format::rgb332);
    ASSERT_EQ(SDL_PIXELFORMAT_RGB444, cen::pixel_format::rgb444);
#if SDL_VERSION_ATLEAST(2, 0, 12)
    ASSERT_EQ(SDL_PIXELFORMAT_BGR444, cen::pixel_format::bgr444);
#endif  // SDL_VERSION_ATLEAST(2, 0, 12)
    ASSERT_EQ(SDL_PIXELFORMAT_RGB555, cen::pixel_format::rgb555);
    ASSERT_EQ(SDL_PIXELFORMAT_BGR555, cen::pixel_format::bgr555);

    ASSERT_EQ(SDL_PIXELFORMAT_ARGB4444, cen::pixel_format::argb4444);
    ASSERT_EQ(SDL_PIXELFORMAT_RGBA4444, cen::pixel_format::rgba4444);
    ASSERT_EQ(SDL_PIXELFORMAT_ABGR4444, cen::pixel_format::abgr4444);
    ASSERT_EQ(SDL_PIXELFORMAT_BGRA4444, cen::pixel_format::bgra4444);

    ASSERT_EQ(SDL_PIXELFORMAT_ARGB1555, cen::pixel_format::argb1555);
    ASSERT_EQ(SDL_PIXELFORMAT_RGBA5551, cen::pixel_format::rgba5551);
    ASSERT_EQ(SDL_PIXELFORMAT_ABGR1555, cen::pixel_format::abgr1555);
    ASSERT_EQ(SDL_PIXELFORMAT_BGRA5551, cen::pixel_format::bgra5551);

    ASSERT_EQ(SDL_PIXELFORMAT_RGB565, cen::pixel_format::rgb565);
    ASSERT_EQ(SDL_PIXELFORMAT_BGR565, cen::pixel_format::bgr565);

    ASSERT_EQ(SDL_PIXELFORMAT_RGB24, cen::pixel_format::rgb24);
    ASSERT_EQ(SDL_PIXELFORMAT_BGR24, cen::pixel_format::bgr24);

    ASSERT_EQ(SDL_PIXELFORMAT_RGB888, cen::pixel_format::rgb888);
    ASSERT_EQ(SDL_PIXELFORMAT_RGBX8888, cen::pixel_format::rgbx8888);
    ASSERT_EQ(SDL_PIXELFORMAT_BGR888, cen::pixel_format::bgr888);
    ASSERT_EQ(SDL_PIXELFORMAT_BGRX8888, cen::pixel_format::bgrx8888);

    ASSERT_EQ(SDL_PIXELFORMAT_ARGB8888, cen::pixel_format::argb8888);
    ASSERT_EQ(SDL_PIXELFORMAT_RGBA8888, cen::pixel_format::rgba8888);
    ASSERT_EQ(SDL_PIXELFORMAT_ABGR8888, cen::pixel_format::abgr8888);
    ASSERT_EQ(SDL_PIXELFORMAT_BGRA8888, cen::pixel_format::bgra8888);

    ASSERT_EQ(SDL_PIXELFORMAT_ARGB2101010, cen::pixel_format::argb2101010);

    if constexpr (cen::cpu::is_big_endian())
    {
      ASSERT_EQ(SDL_PIXELFORMAT_RGBA8888, cen::pixel_format::rgba32);
      ASSERT_EQ(SDL_PIXELFORMAT_ARGB8888, cen::pixel_format::argb32);
      ASSERT_EQ(SDL_PIXELFORMAT_BGRA8888, cen::pixel_format::bgra32);
      ASSERT_EQ(SDL_PIXELFORMAT_ABGR8888, cen::pixel_format::abgr32);
    }
    else
    {
      ASSERT_EQ(SDL_PIXELFORMAT_ABGR8888, cen::pixel_format::rgba32);
      ASSERT_EQ(SDL_PIXELFORMAT_BGRA8888, cen::pixel_format::argb32);
      ASSERT_EQ(SDL_PIXELFORMAT_ARGB8888, cen::pixel_format::bgra32);
      ASSERT_EQ(SDL_PIXELFORMAT_RGBA8888, cen::pixel_format::abgr32);
    }

    ASSERT_EQ(SDL_PIXELFORMAT_YV12, cen::pixel_format::yv12);
    ASSERT_EQ(SDL_PIXELFORMAT_IYUV, cen::pixel_format::iyuv);
    ASSERT_EQ(SDL_PIXELFORMAT_YUY2, cen::pixel_format::yuy2);
    ASSERT_EQ(SDL_PIXELFORMAT_UYVY, cen::pixel_format::uyvy);
    ASSERT_EQ(SDL_PIXELFORMAT_YVYU, cen::pixel_format::yvyu);
    ASSERT_EQ(SDL_PIXELFORMAT_NV12, cen::pixel_format::nv12);
    ASSERT_EQ(SDL_PIXELFORMAT_NV21, cen::pixel_format::nv21);
    ASSERT_EQ(SDL_PIXELFORMAT_EXTERNAL_OES, cen::pixel_format::external_oes);
  }

  ASSERT_NE(cen::pixel_format::yv12, SDL_PIXELFORMAT_BGR555);
  ASSERT_NE(SDL_PIXELFORMAT_INDEX4LSB, cen::pixel_format::abgr8888);
}

TEST(PixelFormat, ToString)
{
  ASSERT_THROW(cen::to_string(static_cast<cen::pixel_format>(0xFFFFFFFF)),
               cen::cen_error);

  ASSERT_EQ("unknown", cen::to_string(cen::pixel_format::unknown));
  ASSERT_EQ("index1lsb", cen::to_string(cen::pixel_format::index1lsb));
  ASSERT_EQ("index1msb", cen::to_string(cen::pixel_format::index1msb));
  ASSERT_EQ("index4lsb", cen::to_string(cen::pixel_format::index4lsb));
  ASSERT_EQ("index4msb", cen::to_string(cen::pixel_format::index4msb));
  ASSERT_EQ("index8", cen::to_string(cen::pixel_format::index8));

  ASSERT_EQ("rgb332", cen::to_string(cen::pixel_format::rgb332));

  ASSERT_EQ("argb4444", cen::to_string(cen::pixel_format::argb4444));
  ASSERT_EQ("rgba4444", cen::to_string(cen::pixel_format::rgba4444));
  ASSERT_EQ("abgr4444", cen::to_string(cen::pixel_format::abgr4444));
  ASSERT_EQ("bgra4444", cen::to_string(cen::pixel_format::bgra4444));

  ASSERT_EQ("argb1555", cen::to_string(cen::pixel_format::argb1555));
  ASSERT_EQ("rgba5551", cen::to_string(cen::pixel_format::rgba5551));
  ASSERT_EQ("abgr1555", cen::to_string(cen::pixel_format::abgr1555));
  ASSERT_EQ("bgra5551", cen::to_string(cen::pixel_format::bgra5551));

  ASSERT_EQ("rgb565", cen::to_string(cen::pixel_format::rgb565));
  ASSERT_EQ("bgr565", cen::to_string(cen::pixel_format::bgr565));

  ASSERT_EQ("rgb24", cen::to_string(cen::pixel_format::rgb24));
  ASSERT_EQ("bgr24", cen::to_string(cen::pixel_format::bgr24));

  ASSERT_EQ("rgbx8888", cen::to_string(cen::pixel_format::rgbx8888));
  ASSERT_EQ("bgrx8888", cen::to_string(cen::pixel_format::bgrx8888));
  ASSERT_EQ("argb8888", cen::to_string(cen::pixel_format::argb8888));
  ASSERT_EQ("rgba8888", cen::to_string(cen::pixel_format::rgba8888));
  ASSERT_EQ("abgr8888", cen::to_string(cen::pixel_format::abgr8888));
  ASSERT_EQ("bgra8888", cen::to_string(cen::pixel_format::bgra8888));

  ASSERT_EQ("argb2101010", cen::to_string(cen::pixel_format::argb2101010));

  ASSERT_EQ("yv12", cen::to_string(cen::pixel_format::yv12));
  ASSERT_EQ("iyuv", cen::to_string(cen::pixel_format::iyuv));
  ASSERT_EQ("yuy2", cen::to_string(cen::pixel_format::yuy2));
  ASSERT_EQ("uyvy", cen::to_string(cen::pixel_format::uyvy));
  ASSERT_EQ("yvyu", cen::to_string(cen::pixel_format::yvyu));

  ASSERT_EQ("nv12", cen::to_string(cen::pixel_format::nv12));
  ASSERT_EQ("nv21", cen::to_string(cen::pixel_format::nv21));

  ASSERT_EQ("external_oes", cen::to_string(cen::pixel_format::external_oes));

#if SDL_VERSION_ATLEAST(2, 0, 14)

  ASSERT_EQ("xrgb4444", cen::to_string(cen::pixel_format::xrgb4444));
  ASSERT_EQ("xbgr4444", cen::to_string(cen::pixel_format::xbgr4444));
  ASSERT_EQ("xrgb1555", cen::to_string(cen::pixel_format::xrgb1555));
  ASSERT_EQ("xbgr1555", cen::to_string(cen::pixel_format::xbgr1555));
  ASSERT_EQ("xrgb8888", cen::to_string(cen::pixel_format::xrgb8888));
  ASSERT_EQ("xbgr8888", cen::to_string(cen::pixel_format::xbgr8888));

#elif SDL_VERSION_ATLEAST(2, 0, 14)

  ASSERT_EQ("bgr444", cen::to_string(cen::pixel_format::bgr444));

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  std::cout << "Pixel format example: " << cen::pixel_format::rgba8888 << '\n';
}
