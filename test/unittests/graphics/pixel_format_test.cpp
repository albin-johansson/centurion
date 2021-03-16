#include "pixel_format.hpp"

#include <gtest/gtest.h>

#include <memory>  // unique_ptr

#include "colors.hpp"
#include "cpu.hpp"

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

  EXPECT_THROW(cen::pixel_format_info{nullptr}, cen::exception);
  EXPECT_NO_THROW(cen::pixel_format_info_handle{nullptr});
}

TEST_F(PixelFormatInfoTest, HandleFromOwner)
{
  const cen::pixel_format_info_handle handle{*m_info};
  EXPECT_TRUE(handle);
}

TEST_F(PixelFormatInfoTest, Format)
{
  EXPECT_EQ(cen::pixel_format::rgba8888, m_info->format());
}

TEST_F(PixelFormatInfoTest, Name)
{
  EXPECT_STREQ(SDL_GetPixelFormatName(m_info->get()->format), m_info->name());
}

TEST_F(PixelFormatInfoTest, RGBToPixel)
{
  constexpr auto color = cen::colors::hot_pink;
  EXPECT_EQ(SDL_MapRGB(m_info->get(), color.red(), color.green(), color.blue()),
            m_info->rgb_to_pixel(color));
}

TEST_F(PixelFormatInfoTest, RGBAToPixel)
{
  constexpr auto color = cen::colors::honey_dew;
  EXPECT_EQ(SDL_MapRGBA(m_info->get(),
                        color.red(),
                        color.green(),
                        color.blue(),
                        color.alpha()),
            m_info->rgba_to_pixel(color));
}

TEST_F(PixelFormatInfoTest, PixelToRGB)
{
  constexpr auto color = cen::colors::hot_pink;
  const cen::u32 pixel =
      (color.red() << 24u) | (color.green() << 16u) | (color.blue() << 8u);
  EXPECT_EQ(color, m_info->pixel_to_rgb(pixel));
}

TEST_F(PixelFormatInfoTest, PixelToRGBA)
{
  constexpr auto color = cen::colors::aquamarine;
  const cen::u32 pixel = (color.red() << 24u) | (color.green() << 16u) |
                         (color.blue() << 8u) | (color.alpha() << 0u);
  EXPECT_EQ(color, m_info->pixel_to_rgba(pixel));
}

TEST(PixelFormat, Values)
{
  {
    EXPECT_EQ(cen::pixel_format::unknown, SDL_PIXELFORMAT_UNKNOWN);
    EXPECT_EQ(cen::pixel_format::index1lsb, SDL_PIXELFORMAT_INDEX1LSB);
    EXPECT_EQ(cen::pixel_format::index1msb, SDL_PIXELFORMAT_INDEX1MSB);
    EXPECT_EQ(cen::pixel_format::index4lsb, SDL_PIXELFORMAT_INDEX4LSB);
    EXPECT_EQ(cen::pixel_format::index4msb, SDL_PIXELFORMAT_INDEX4MSB);
    EXPECT_EQ(cen::pixel_format::index8, SDL_PIXELFORMAT_INDEX8);

    EXPECT_EQ(cen::pixel_format::xrgb4444, SDL_PIXELFORMAT_XRGB4444);
    EXPECT_EQ(cen::pixel_format::xbgr4444, SDL_PIXELFORMAT_XBGR4444);
    EXPECT_EQ(cen::pixel_format::xrgb1555, SDL_PIXELFORMAT_XRGB1555);
    EXPECT_EQ(cen::pixel_format::xbgr1555, SDL_PIXELFORMAT_XBGR1555);
    EXPECT_EQ(cen::pixel_format::xrgb8888, SDL_PIXELFORMAT_XRGB8888);
    EXPECT_EQ(cen::pixel_format::xbgr8888, SDL_PIXELFORMAT_XBGR8888);

    EXPECT_EQ(cen::pixel_format::rgb332, SDL_PIXELFORMAT_RGB332);
    EXPECT_EQ(cen::pixel_format::rgb444, SDL_PIXELFORMAT_RGB444);
    EXPECT_EQ(cen::pixel_format::bgr444, SDL_PIXELFORMAT_BGR444);
    EXPECT_EQ(cen::pixel_format::rgb555, SDL_PIXELFORMAT_RGB555);
    EXPECT_EQ(cen::pixel_format::bgr555, SDL_PIXELFORMAT_BGR555);

    EXPECT_EQ(cen::pixel_format::argb4444, SDL_PIXELFORMAT_ARGB4444);
    EXPECT_EQ(cen::pixel_format::rgba4444, SDL_PIXELFORMAT_RGBA4444);
    EXPECT_EQ(cen::pixel_format::abgr4444, SDL_PIXELFORMAT_ABGR4444);
    EXPECT_EQ(cen::pixel_format::bgra4444, SDL_PIXELFORMAT_BGRA4444);

    EXPECT_EQ(cen::pixel_format::argb1555, SDL_PIXELFORMAT_ARGB1555);
    EXPECT_EQ(cen::pixel_format::rgba5551, SDL_PIXELFORMAT_RGBA5551);
    EXPECT_EQ(cen::pixel_format::abgr1555, SDL_PIXELFORMAT_ABGR1555);
    EXPECT_EQ(cen::pixel_format::bgra5551, SDL_PIXELFORMAT_BGRA5551);

    EXPECT_EQ(cen::pixel_format::rgb565, SDL_PIXELFORMAT_RGB565);
    EXPECT_EQ(cen::pixel_format::bgr565, SDL_PIXELFORMAT_BGR565);

    EXPECT_EQ(cen::pixel_format::rgb24, SDL_PIXELFORMAT_RGB24);
    EXPECT_EQ(cen::pixel_format::bgr24, SDL_PIXELFORMAT_BGR24);

    EXPECT_EQ(cen::pixel_format::rgb888, SDL_PIXELFORMAT_RGB888);
    EXPECT_EQ(cen::pixel_format::rgbx8888, SDL_PIXELFORMAT_RGBX8888);
    EXPECT_EQ(cen::pixel_format::bgr888, SDL_PIXELFORMAT_BGR888);
    EXPECT_EQ(cen::pixel_format::bgrx8888, SDL_PIXELFORMAT_BGRX8888);

    EXPECT_EQ(cen::pixel_format::argb8888, SDL_PIXELFORMAT_ARGB8888);
    EXPECT_EQ(cen::pixel_format::rgba8888, SDL_PIXELFORMAT_RGBA8888);
    EXPECT_EQ(cen::pixel_format::abgr8888, SDL_PIXELFORMAT_ABGR8888);
    EXPECT_EQ(cen::pixel_format::bgra8888, SDL_PIXELFORMAT_BGRA8888);

    EXPECT_EQ(cen::pixel_format::argb2101010, SDL_PIXELFORMAT_ARGB2101010);

    if constexpr (cen::cpu::is_big_endian())
    {
      EXPECT_EQ(cen::pixel_format::rgba32, SDL_PIXELFORMAT_RGBA8888);
      EXPECT_EQ(cen::pixel_format::argb32, SDL_PIXELFORMAT_ARGB8888);
      EXPECT_EQ(cen::pixel_format::bgra32, SDL_PIXELFORMAT_BGRA8888);
      EXPECT_EQ(cen::pixel_format::abgr32, SDL_PIXELFORMAT_ABGR8888);
    }
    else
    {
      EXPECT_EQ(cen::pixel_format::rgba32, SDL_PIXELFORMAT_ABGR8888);
      EXPECT_EQ(cen::pixel_format::argb32, SDL_PIXELFORMAT_BGRA8888);
      EXPECT_EQ(cen::pixel_format::bgra32, SDL_PIXELFORMAT_ARGB8888);
      EXPECT_EQ(cen::pixel_format::abgr32, SDL_PIXELFORMAT_RGBA8888);
    }

    EXPECT_EQ(cen::pixel_format::yv12, SDL_PIXELFORMAT_YV12);
    EXPECT_EQ(cen::pixel_format::iyuv, SDL_PIXELFORMAT_IYUV);
    EXPECT_EQ(cen::pixel_format::yuy2, SDL_PIXELFORMAT_YUY2);
    EXPECT_EQ(cen::pixel_format::uyvy, SDL_PIXELFORMAT_UYVY);
    EXPECT_EQ(cen::pixel_format::yvyu, SDL_PIXELFORMAT_YVYU);
    EXPECT_EQ(cen::pixel_format::nv12, SDL_PIXELFORMAT_NV12);
    EXPECT_EQ(cen::pixel_format::nv21, SDL_PIXELFORMAT_NV21);
    EXPECT_EQ(cen::pixel_format::external_oes, SDL_PIXELFORMAT_EXTERNAL_OES);
  }

  {
    EXPECT_EQ(SDL_PIXELFORMAT_UNKNOWN, cen::pixel_format::unknown);
    EXPECT_EQ(SDL_PIXELFORMAT_INDEX1LSB, cen::pixel_format::index1lsb);
    EXPECT_EQ(SDL_PIXELFORMAT_INDEX1MSB, cen::pixel_format::index1msb);
    EXPECT_EQ(SDL_PIXELFORMAT_INDEX4LSB, cen::pixel_format::index4lsb);
    EXPECT_EQ(SDL_PIXELFORMAT_INDEX4MSB, cen::pixel_format::index4msb);
    EXPECT_EQ(SDL_PIXELFORMAT_INDEX8, cen::pixel_format::index8);

    EXPECT_EQ(SDL_PIXELFORMAT_XRGB4444, cen::pixel_format::xrgb4444);
    EXPECT_EQ(SDL_PIXELFORMAT_XBGR4444, cen::pixel_format::xbgr4444);
    EXPECT_EQ(SDL_PIXELFORMAT_XRGB1555, cen::pixel_format::xrgb1555);
    EXPECT_EQ(SDL_PIXELFORMAT_XBGR1555, cen::pixel_format::xbgr1555);
    EXPECT_EQ(SDL_PIXELFORMAT_XRGB8888, cen::pixel_format::xrgb8888);
    EXPECT_EQ(SDL_PIXELFORMAT_XBGR8888, cen::pixel_format::xbgr8888);

    EXPECT_EQ(SDL_PIXELFORMAT_RGB332, cen::pixel_format::rgb332);
    EXPECT_EQ(SDL_PIXELFORMAT_RGB444, cen::pixel_format::rgb444);
    EXPECT_EQ(SDL_PIXELFORMAT_BGR444, cen::pixel_format::bgr444);
    EXPECT_EQ(SDL_PIXELFORMAT_RGB555, cen::pixel_format::rgb555);
    EXPECT_EQ(SDL_PIXELFORMAT_BGR555, cen::pixel_format::bgr555);

    EXPECT_EQ(SDL_PIXELFORMAT_ARGB4444, cen::pixel_format::argb4444);
    EXPECT_EQ(SDL_PIXELFORMAT_RGBA4444, cen::pixel_format::rgba4444);
    EXPECT_EQ(SDL_PIXELFORMAT_ABGR4444, cen::pixel_format::abgr4444);
    EXPECT_EQ(SDL_PIXELFORMAT_BGRA4444, cen::pixel_format::bgra4444);

    EXPECT_EQ(SDL_PIXELFORMAT_ARGB1555, cen::pixel_format::argb1555);
    EXPECT_EQ(SDL_PIXELFORMAT_RGBA5551, cen::pixel_format::rgba5551);
    EXPECT_EQ(SDL_PIXELFORMAT_ABGR1555, cen::pixel_format::abgr1555);
    EXPECT_EQ(SDL_PIXELFORMAT_BGRA5551, cen::pixel_format::bgra5551);

    EXPECT_EQ(SDL_PIXELFORMAT_RGB565, cen::pixel_format::rgb565);
    EXPECT_EQ(SDL_PIXELFORMAT_BGR565, cen::pixel_format::bgr565);

    EXPECT_EQ(SDL_PIXELFORMAT_RGB24, cen::pixel_format::rgb24);
    EXPECT_EQ(SDL_PIXELFORMAT_BGR24, cen::pixel_format::bgr24);

    EXPECT_EQ(SDL_PIXELFORMAT_RGB888, cen::pixel_format::rgb888);
    EXPECT_EQ(SDL_PIXELFORMAT_RGBX8888, cen::pixel_format::rgbx8888);
    EXPECT_EQ(SDL_PIXELFORMAT_BGR888, cen::pixel_format::bgr888);
    EXPECT_EQ(SDL_PIXELFORMAT_BGRX8888, cen::pixel_format::bgrx8888);

    EXPECT_EQ(SDL_PIXELFORMAT_ARGB8888, cen::pixel_format::argb8888);
    EXPECT_EQ(SDL_PIXELFORMAT_RGBA8888, cen::pixel_format::rgba8888);
    EXPECT_EQ(SDL_PIXELFORMAT_ABGR8888, cen::pixel_format::abgr8888);
    EXPECT_EQ(SDL_PIXELFORMAT_BGRA8888, cen::pixel_format::bgra8888);

    EXPECT_EQ(SDL_PIXELFORMAT_ARGB2101010, cen::pixel_format::argb2101010);

    if constexpr (cen::cpu::is_big_endian())
    {
      EXPECT_EQ(SDL_PIXELFORMAT_RGBA8888, cen::pixel_format::rgba32);
      EXPECT_EQ(SDL_PIXELFORMAT_ARGB8888, cen::pixel_format::argb32);
      EXPECT_EQ(SDL_PIXELFORMAT_BGRA8888, cen::pixel_format::bgra32);
      EXPECT_EQ(SDL_PIXELFORMAT_ABGR8888, cen::pixel_format::abgr32);
    }
    else
    {
      EXPECT_EQ(SDL_PIXELFORMAT_ABGR8888, cen::pixel_format::rgba32);
      EXPECT_EQ(SDL_PIXELFORMAT_BGRA8888, cen::pixel_format::argb32);
      EXPECT_EQ(SDL_PIXELFORMAT_ARGB8888, cen::pixel_format::bgra32);
      EXPECT_EQ(SDL_PIXELFORMAT_RGBA8888, cen::pixel_format::abgr32);
    }

    EXPECT_EQ(SDL_PIXELFORMAT_YV12, cen::pixel_format::yv12);
    EXPECT_EQ(SDL_PIXELFORMAT_IYUV, cen::pixel_format::iyuv);
    EXPECT_EQ(SDL_PIXELFORMAT_YUY2, cen::pixel_format::yuy2);
    EXPECT_EQ(SDL_PIXELFORMAT_UYVY, cen::pixel_format::uyvy);
    EXPECT_EQ(SDL_PIXELFORMAT_YVYU, cen::pixel_format::yvyu);
    EXPECT_EQ(SDL_PIXELFORMAT_NV12, cen::pixel_format::nv12);
    EXPECT_EQ(SDL_PIXELFORMAT_NV21, cen::pixel_format::nv21);
    EXPECT_EQ(SDL_PIXELFORMAT_EXTERNAL_OES, cen::pixel_format::external_oes);
  }

  EXPECT_NE(cen::pixel_format::yv12, SDL_PIXELFORMAT_BGR555);
  EXPECT_NE(SDL_PIXELFORMAT_INDEX4LSB, cen::pixel_format::abgr8888);
}
