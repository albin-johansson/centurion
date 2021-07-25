#include "video/pixel_format_info.hpp"

#include <gtest/gtest.h>

#include <iostream>  // clog
#include <memory>    // unique_ptr

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

TEST_F(PixelFormatInfoTest, FormatConstructor)
{
  const auto invalid = static_cast<cen::pixel_format>(0xFFFFFFFF);
  ASSERT_THROW(cen::pixel_format_info{invalid}, cen::sdl_error);
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

TEST_F(PixelFormatInfoTest, ToString)
{
  std::clog << *m_info << '\n';
}
