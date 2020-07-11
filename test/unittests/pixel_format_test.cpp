#include "pixel_format.hpp"

#include <catch.hpp>

using namespace centurion;

TEST_CASE("PixelFormat enum values", "[PixelFormat]")
{
  SECTION("CTN left and SDL right")
  {
    CHECK(pixel_format::unknown == SDL_PIXELFORMAT_UNKNOWN);
    CHECK(pixel_format::index1lsb == SDL_PIXELFORMAT_INDEX1LSB);
    CHECK(pixel_format::index1msb == SDL_PIXELFORMAT_INDEX1MSB);
    CHECK(pixel_format::index4lsb == SDL_PIXELFORMAT_INDEX4LSB);
    CHECK(pixel_format::index4msb == SDL_PIXELFORMAT_INDEX4MSB);
    CHECK(pixel_format::index8 == SDL_PIXELFORMAT_INDEX8);

    CHECK(pixel_format::rgb332 == SDL_PIXELFORMAT_RGB332);
    CHECK(pixel_format::rgb444 == SDL_PIXELFORMAT_RGB444);
    CHECK(pixel_format::rgb555 == SDL_PIXELFORMAT_RGB555);
    CHECK(pixel_format::bgr555 == SDL_PIXELFORMAT_BGR555);

    CHECK(pixel_format::argb4444 == SDL_PIXELFORMAT_ARGB4444);
    CHECK(pixel_format::rgba4444 == SDL_PIXELFORMAT_RGBA4444);
    CHECK(pixel_format::abgr4444 == SDL_PIXELFORMAT_ABGR4444);
    CHECK(pixel_format::bgra4444 == SDL_PIXELFORMAT_BGRA4444);

    CHECK(pixel_format::argb1555 == SDL_PIXELFORMAT_ARGB1555);
    CHECK(pixel_format::rgba5551 == SDL_PIXELFORMAT_RGBA5551);
    CHECK(pixel_format::abgr1555 == SDL_PIXELFORMAT_ABGR1555);
    CHECK(pixel_format::bgra5551 == SDL_PIXELFORMAT_BGRA5551);

    CHECK(pixel_format::rgb565 == SDL_PIXELFORMAT_RGB565);
    CHECK(pixel_format::bgr565 == SDL_PIXELFORMAT_BGR565);

    CHECK(pixel_format::rgb24 == SDL_PIXELFORMAT_RGB24);
    CHECK(pixel_format::bgr24 == SDL_PIXELFORMAT_BGR24);

    CHECK(pixel_format::rgb888 == SDL_PIXELFORMAT_RGB888);
    CHECK(pixel_format::rgbx8888 == SDL_PIXELFORMAT_RGBX8888);
    CHECK(pixel_format::bgr888 == SDL_PIXELFORMAT_BGR888);
    CHECK(pixel_format::bgrx8888 == SDL_PIXELFORMAT_BGRX8888);

    CHECK(pixel_format::argb8888 == SDL_PIXELFORMAT_ARGB8888);
    CHECK(pixel_format::rgba8888 == SDL_PIXELFORMAT_RGBA8888);
    CHECK(pixel_format::abgr8888 == SDL_PIXELFORMAT_ABGR8888);
    CHECK(pixel_format::bgra8888 == SDL_PIXELFORMAT_BGRA8888);

    CHECK(pixel_format::argb2101010 == SDL_PIXELFORMAT_ARGB2101010);

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    CHECK(PixelFormat::RGBA32 == SDL_PIXELFORMAT_RGBA8888);
    CHECK(PixelFormat::ARGB32 == SDL_PIXELFORMAT_ARGB8888);
    CHECK(PixelFormat::BGRA32 == SDL_PIXELFORMAT_BGRA8888);
    CHECK(PixelFormat::ABGR32 == SDL_PIXELFORMAT_ABGR8888);
#else
    CHECK(pixel_format::rgba32 == SDL_PIXELFORMAT_ABGR8888);
    CHECK(pixel_format::argb32 == SDL_PIXELFORMAT_BGRA8888);
    CHECK(pixel_format::bgra32 == SDL_PIXELFORMAT_ARGB8888);
    CHECK(pixel_format::abgr32 == SDL_PIXELFORMAT_RGBA8888);
#endif

    CHECK(pixel_format::yv12 == SDL_PIXELFORMAT_YV12);
    CHECK(pixel_format::iyuv == SDL_PIXELFORMAT_IYUV);
    CHECK(pixel_format::yuy2 == SDL_PIXELFORMAT_YUY2);
    CHECK(pixel_format::uyvy == SDL_PIXELFORMAT_UYVY);
    CHECK(pixel_format::yvyu == SDL_PIXELFORMAT_YVYU);
    CHECK(pixel_format::nv12 == SDL_PIXELFORMAT_NV12);
    CHECK(pixel_format::nv21 == SDL_PIXELFORMAT_NV21);
    CHECK(pixel_format::external_oes == SDL_PIXELFORMAT_EXTERNAL_OES);
  }

  SECTION("CTN right and SDL left")
  {
    CHECK(SDL_PIXELFORMAT_UNKNOWN == pixel_format::unknown);
    CHECK(SDL_PIXELFORMAT_INDEX1LSB == pixel_format::index1lsb);
    CHECK(SDL_PIXELFORMAT_INDEX1MSB == pixel_format::index1msb);
    CHECK(SDL_PIXELFORMAT_INDEX4LSB == pixel_format::index4lsb);
    CHECK(SDL_PIXELFORMAT_INDEX4MSB == pixel_format::index4msb);
    CHECK(SDL_PIXELFORMAT_INDEX8 == pixel_format::index8);

    CHECK(SDL_PIXELFORMAT_RGB332 == pixel_format::rgb332);
    CHECK(SDL_PIXELFORMAT_RGB444 == pixel_format::rgb444);
    CHECK(SDL_PIXELFORMAT_RGB555 == pixel_format::rgb555);
    CHECK(SDL_PIXELFORMAT_BGR555 == pixel_format::bgr555);

    CHECK(SDL_PIXELFORMAT_ARGB4444 == pixel_format::argb4444);
    CHECK(SDL_PIXELFORMAT_RGBA4444 == pixel_format::rgba4444);
    CHECK(SDL_PIXELFORMAT_ABGR4444 == pixel_format::abgr4444);
    CHECK(SDL_PIXELFORMAT_BGRA4444 == pixel_format::bgra4444);

    CHECK(SDL_PIXELFORMAT_ARGB1555 == pixel_format::argb1555);
    CHECK(SDL_PIXELFORMAT_RGBA5551 == pixel_format::rgba5551);
    CHECK(SDL_PIXELFORMAT_ABGR1555 == pixel_format::abgr1555);
    CHECK(SDL_PIXELFORMAT_BGRA5551 == pixel_format::bgra5551);

    CHECK(SDL_PIXELFORMAT_RGB565 == pixel_format::rgb565);
    CHECK(SDL_PIXELFORMAT_BGR565 == pixel_format::bgr565);

    CHECK(SDL_PIXELFORMAT_RGB24 == pixel_format::rgb24);
    CHECK(SDL_PIXELFORMAT_BGR24 == pixel_format::bgr24);

    CHECK(SDL_PIXELFORMAT_RGB888 == pixel_format::rgb888);
    CHECK(SDL_PIXELFORMAT_RGBX8888 == pixel_format::rgbx8888);
    CHECK(SDL_PIXELFORMAT_BGR888 == pixel_format::bgr888);
    CHECK(SDL_PIXELFORMAT_BGRX8888 == pixel_format::bgrx8888);

    CHECK(SDL_PIXELFORMAT_ARGB8888 == pixel_format::argb8888);
    CHECK(SDL_PIXELFORMAT_RGBA8888 == pixel_format::rgba8888);
    CHECK(SDL_PIXELFORMAT_ABGR8888 == pixel_format::abgr8888);
    CHECK(SDL_PIXELFORMAT_BGRA8888 == pixel_format::bgra8888);

    CHECK(SDL_PIXELFORMAT_ARGB2101010 == pixel_format::argb2101010);

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    CHECK(SDL_PIXELFORMAT_RGBA8888 == PixelFormat::RGBA32);
    CHECK(SDL_PIXELFORMAT_ARGB8888 == PixelFormat::ARGB32);
    CHECK(SDL_PIXELFORMAT_BGRA8888 == PixelFormat::BGRA32);
    CHECK(SDL_PIXELFORMAT_ABGR8888 == PixelFormat::ABGR32);
#else
    CHECK(SDL_PIXELFORMAT_ABGR8888 == pixel_format::rgba32);
    CHECK(SDL_PIXELFORMAT_BGRA8888 == pixel_format::argb32);
    CHECK(SDL_PIXELFORMAT_ARGB8888 == pixel_format::bgra32);
    CHECK(SDL_PIXELFORMAT_RGBA8888 == pixel_format::abgr32);
#endif

    CHECK(SDL_PIXELFORMAT_YV12 == pixel_format::yv12);
    CHECK(SDL_PIXELFORMAT_IYUV == pixel_format::iyuv);
    CHECK(SDL_PIXELFORMAT_YUY2 == pixel_format::yuy2);
    CHECK(SDL_PIXELFORMAT_UYVY == pixel_format::uyvy);
    CHECK(SDL_PIXELFORMAT_YVYU == pixel_format::yvyu);
    CHECK(SDL_PIXELFORMAT_NV12 == pixel_format::nv12);
    CHECK(SDL_PIXELFORMAT_NV21 == pixel_format::nv21);
    CHECK(SDL_PIXELFORMAT_EXTERNAL_OES == pixel_format::external_oes);
  }

  CHECK(pixel_format::yv12 != SDL_PIXELFORMAT_BGR555);
  CHECK(SDL_PIXELFORMAT_INDEX4LSB != pixel_format::abgr8888);
}