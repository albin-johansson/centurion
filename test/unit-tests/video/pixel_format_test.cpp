#include "video/pixel_format.hpp"

#include <gtest/gtest.h>

#include <memory>  // unique_ptr

#include "system/cpu.hpp"
#include "video/colors.hpp"

class PixelFormatInfoTest : public testing::Test
{
 protected:
  static void SetUpTestSuite()
  {
    constexpr auto format = cen::pixel_format::rgba8888;  // Arbitrary
    m_info = std::make_unique<cen::pixel_format_info>(format);
  }

  static void TearDownTestSuite()
  {
    m_info.reset();
  }

  inline static std::unique_ptr<cen::pixel_format_info> m_info;
};

TEST_F(PixelFormatInfoTest, PointerConstructor)
{
  static_assert(!noexcept(cen::pixel_format_info{nullptr}));
  static_assert(noexcept(cen::pixel_format_info_handle{nullptr}));

  ASSERT_THROW(cen::pixel_format_info{nullptr}, cen::cen_error);
  ASSERT_NO_THROW(cen::pixel_format_info_handle{nullptr});
}

TEST_F(PixelFormatInfoTest, HandleFromOwner)
{
  const cen::pixel_format_info_handle handle{*m_info};
  ASSERT_TRUE(handle);
}

TEST_F(PixelFormatInfoTest, Format)
{
  ASSERT_EQ(cen::pixel_format::rgba8888, m_info->format());
}

TEST_F(PixelFormatInfoTest, Name)
{
  ASSERT_STREQ(SDL_GetPixelFormatName(m_info->get()->format), m_info->name());
}

TEST_F(PixelFormatInfoTest, RGBToPixel)
{
  constexpr auto color = cen::colors::hot_pink;
  ASSERT_EQ(SDL_MapRGB(m_info->get(), color.red(), color.green(), color.blue()),
            m_info->rgb_to_pixel(color));
}

TEST_F(PixelFormatInfoTest, RGBAToPixel)
{
  constexpr auto color = cen::colors::honey_dew;
  ASSERT_EQ(
      SDL_MapRGBA(m_info->get(), color.red(), color.green(), color.blue(), color.alpha()),
      m_info->rgba_to_pixel(color));
}

TEST_F(PixelFormatInfoTest, PixelToRGB)
{
  constexpr auto color = cen::colors::hot_pink;
  const cen::u32 pixel =
      (color.red() << 24u) | (color.green() << 16u) | (color.blue() << 8u);
  ASSERT_EQ(color, m_info->pixel_to_rgb(pixel));
}

TEST_F(PixelFormatInfoTest, PixelToRGBA)
{
  constexpr auto color = cen::colors::aquamarine;
  const cen::u32 pixel = (color.red() << 24u) | (color.green() << 16u) |
                         (color.blue() << 8u) | (color.alpha() << 0u);
  ASSERT_EQ(color, m_info->pixel_to_rgba(pixel));
}

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
