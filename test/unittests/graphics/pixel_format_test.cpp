#include "pixel_format.hpp"

#include <catch.hpp>

TEST_CASE("pixel_format enum values", "[pixel_format]")
{
  SECTION("CEN_ left and SDL right")
  {
    CHECK(cen::pixel_format::unknown == SDL_PIXELFORMAT_UNKNOWN);
    CHECK(cen::pixel_format::index1lsb == SDL_PIXELFORMAT_INDEX1LSB);
    CHECK(cen::pixel_format::index1msb == SDL_PIXELFORMAT_INDEX1MSB);
    CHECK(cen::pixel_format::index4lsb == SDL_PIXELFORMAT_INDEX4LSB);
    CHECK(cen::pixel_format::index4msb == SDL_PIXELFORMAT_INDEX4MSB);
    CHECK(cen::pixel_format::index8 == SDL_PIXELFORMAT_INDEX8);

    CHECK(cen::pixel_format::rgb332 == SDL_PIXELFORMAT_RGB332);
    CHECK(cen::pixel_format::rgb444 == SDL_PIXELFORMAT_RGB444);
    CHECK(cen::pixel_format::rgb555 == SDL_PIXELFORMAT_RGB555);
    CHECK(cen::pixel_format::bgr555 == SDL_PIXELFORMAT_BGR555);

    CHECK(cen::pixel_format::argb4444 == SDL_PIXELFORMAT_ARGB4444);
    CHECK(cen::pixel_format::rgba4444 == SDL_PIXELFORMAT_RGBA4444);
    CHECK(cen::pixel_format::abgr4444 == SDL_PIXELFORMAT_ABGR4444);
    CHECK(cen::pixel_format::bgra4444 == SDL_PIXELFORMAT_BGRA4444);

    CHECK(cen::pixel_format::argb1555 == SDL_PIXELFORMAT_ARGB1555);
    CHECK(cen::pixel_format::rgba5551 == SDL_PIXELFORMAT_RGBA5551);
    CHECK(cen::pixel_format::abgr1555 == SDL_PIXELFORMAT_ABGR1555);
    CHECK(cen::pixel_format::bgra5551 == SDL_PIXELFORMAT_BGRA5551);

    CHECK(cen::pixel_format::rgb565 == SDL_PIXELFORMAT_RGB565);
    CHECK(cen::pixel_format::bgr565 == SDL_PIXELFORMAT_BGR565);

    CHECK(cen::pixel_format::rgb24 == SDL_PIXELFORMAT_RGB24);
    CHECK(cen::pixel_format::bgr24 == SDL_PIXELFORMAT_BGR24);

    CHECK(cen::pixel_format::rgb888 == SDL_PIXELFORMAT_RGB888);
    CHECK(cen::pixel_format::rgbx8888 == SDL_PIXELFORMAT_RGBX8888);
    CHECK(cen::pixel_format::bgr888 == SDL_PIXELFORMAT_BGR888);
    CHECK(cen::pixel_format::bgrx8888 == SDL_PIXELFORMAT_BGRX8888);

    CHECK(cen::pixel_format::argb8888 == SDL_PIXELFORMAT_ARGB8888);
    CHECK(cen::pixel_format::rgba8888 == SDL_PIXELFORMAT_RGBA8888);
    CHECK(cen::pixel_format::abgr8888 == SDL_PIXELFORMAT_ABGR8888);
    CHECK(cen::pixel_format::bgra8888 == SDL_PIXELFORMAT_BGRA8888);

    CHECK(cen::pixel_format::argb2101010 == SDL_PIXELFORMAT_ARGB2101010);

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    CHECK(cen::pixel_format::RGBA32 == SDL_PIXELFORMAT_RGBA8888);
    CHECK(cen::pixel_format::ARGB32 == SDL_PIXELFORMAT_ARGB8888);
    CHECK(cen::pixel_format::BGRA32 == SDL_PIXELFORMAT_BGRA8888);
    CHECK(cen::pixel_format::ABGR32 == SDL_PIXELFORMAT_ABGR8888);
#else
    CHECK(cen::pixel_format::rgba32 == SDL_PIXELFORMAT_ABGR8888);
    CHECK(cen::pixel_format::argb32 == SDL_PIXELFORMAT_BGRA8888);
    CHECK(cen::pixel_format::bgra32 == SDL_PIXELFORMAT_ARGB8888);
    CHECK(cen::pixel_format::abgr32 == SDL_PIXELFORMAT_RGBA8888);
#endif

    CHECK(cen::pixel_format::yv12 == SDL_PIXELFORMAT_YV12);
    CHECK(cen::pixel_format::iyuv == SDL_PIXELFORMAT_IYUV);
    CHECK(cen::pixel_format::yuy2 == SDL_PIXELFORMAT_YUY2);
    CHECK(cen::pixel_format::uyvy == SDL_PIXELFORMAT_UYVY);
    CHECK(cen::pixel_format::yvyu == SDL_PIXELFORMAT_YVYU);
    CHECK(cen::pixel_format::nv12 == SDL_PIXELFORMAT_NV12);
    CHECK(cen::pixel_format::nv21 == SDL_PIXELFORMAT_NV21);
    CHECK(cen::pixel_format::external_oes == SDL_PIXELFORMAT_EXTERNAL_OES);
  }

  SECTION("CEN_ right and SDL left")
  {
    CHECK(SDL_PIXELFORMAT_UNKNOWN == cen::pixel_format::unknown);
    CHECK(SDL_PIXELFORMAT_INDEX1LSB == cen::pixel_format::index1lsb);
    CHECK(SDL_PIXELFORMAT_INDEX1MSB == cen::pixel_format::index1msb);
    CHECK(SDL_PIXELFORMAT_INDEX4LSB == cen::pixel_format::index4lsb);
    CHECK(SDL_PIXELFORMAT_INDEX4MSB == cen::pixel_format::index4msb);
    CHECK(SDL_PIXELFORMAT_INDEX8 == cen::pixel_format::index8);

    CHECK(SDL_PIXELFORMAT_RGB332 == cen::pixel_format::rgb332);
    CHECK(SDL_PIXELFORMAT_RGB444 == cen::pixel_format::rgb444);
    CHECK(SDL_PIXELFORMAT_RGB555 == cen::pixel_format::rgb555);
    CHECK(SDL_PIXELFORMAT_BGR555 == cen::pixel_format::bgr555);

    CHECK(SDL_PIXELFORMAT_ARGB4444 == cen::pixel_format::argb4444);
    CHECK(SDL_PIXELFORMAT_RGBA4444 == cen::pixel_format::rgba4444);
    CHECK(SDL_PIXELFORMAT_ABGR4444 == cen::pixel_format::abgr4444);
    CHECK(SDL_PIXELFORMAT_BGRA4444 == cen::pixel_format::bgra4444);

    CHECK(SDL_PIXELFORMAT_ARGB1555 == cen::pixel_format::argb1555);
    CHECK(SDL_PIXELFORMAT_RGBA5551 == cen::pixel_format::rgba5551);
    CHECK(SDL_PIXELFORMAT_ABGR1555 == cen::pixel_format::abgr1555);
    CHECK(SDL_PIXELFORMAT_BGRA5551 == cen::pixel_format::bgra5551);

    CHECK(SDL_PIXELFORMAT_RGB565 == cen::pixel_format::rgb565);
    CHECK(SDL_PIXELFORMAT_BGR565 == cen::pixel_format::bgr565);

    CHECK(SDL_PIXELFORMAT_RGB24 == cen::pixel_format::rgb24);
    CHECK(SDL_PIXELFORMAT_BGR24 == cen::pixel_format::bgr24);

    CHECK(SDL_PIXELFORMAT_RGB888 == cen::pixel_format::rgb888);
    CHECK(SDL_PIXELFORMAT_RGBX8888 == cen::pixel_format::rgbx8888);
    CHECK(SDL_PIXELFORMAT_BGR888 == cen::pixel_format::bgr888);
    CHECK(SDL_PIXELFORMAT_BGRX8888 == cen::pixel_format::bgrx8888);

    CHECK(SDL_PIXELFORMAT_ARGB8888 == cen::pixel_format::argb8888);
    CHECK(SDL_PIXELFORMAT_RGBA8888 == cen::pixel_format::rgba8888);
    CHECK(SDL_PIXELFORMAT_ABGR8888 == cen::pixel_format::abgr8888);
    CHECK(SDL_PIXELFORMAT_BGRA8888 == cen::pixel_format::bgra8888);

    CHECK(SDL_PIXELFORMAT_ARGB2101010 == cen::pixel_format::argb2101010);

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    CHECK(SDL_PIXELFORMAT_RGBA8888 == cen::pixel_format::RGBA32);
    CHECK(SDL_PIXELFORMAT_ARGB8888 == cen::pixel_format::ARGB32);
    CHECK(SDL_PIXELFORMAT_BGRA8888 == cen::pixel_format::BGRA32);
    CHECK(SDL_PIXELFORMAT_ABGR8888 == cen::pixel_format::ABGR32);
#else
    CHECK(SDL_PIXELFORMAT_ABGR8888 == cen::pixel_format::rgba32);
    CHECK(SDL_PIXELFORMAT_BGRA8888 == cen::pixel_format::argb32);
    CHECK(SDL_PIXELFORMAT_ARGB8888 == cen::pixel_format::bgra32);
    CHECK(SDL_PIXELFORMAT_RGBA8888 == cen::pixel_format::abgr32);
#endif

    CHECK(SDL_PIXELFORMAT_YV12 == cen::pixel_format::yv12);
    CHECK(SDL_PIXELFORMAT_IYUV == cen::pixel_format::iyuv);
    CHECK(SDL_PIXELFORMAT_YUY2 == cen::pixel_format::yuy2);
    CHECK(SDL_PIXELFORMAT_UYVY == cen::pixel_format::uyvy);
    CHECK(SDL_PIXELFORMAT_YVYU == cen::pixel_format::yvyu);
    CHECK(SDL_PIXELFORMAT_NV12 == cen::pixel_format::nv12);
    CHECK(SDL_PIXELFORMAT_NV21 == cen::pixel_format::nv21);
    CHECK(SDL_PIXELFORMAT_EXTERNAL_OES == cen::pixel_format::external_oes);
  }

  CHECK(cen::pixel_format::yv12 != SDL_PIXELFORMAT_BGR555);
  CHECK(SDL_PIXELFORMAT_INDEX4LSB != cen::pixel_format::abgr8888);
}