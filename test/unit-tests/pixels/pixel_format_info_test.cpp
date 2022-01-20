#include <gtest/gtest.h>

#include <iostream>  // cout
#include <memory>    // unique_ptr

#include "centurion/color.hpp"
#include "centurion/pixels.hpp"

class PixelFormatInfoTest : public testing::Test {
 protected:
  static void SetUpTestSuite()
  {
    info = std::make_unique<cen::pixel_format_info>(cen::pixel_format::rgba8888);
  }

  static void TearDownTestSuite() { info.reset(); }

  inline static std::unique_ptr<cen::pixel_format_info> info;
};

TEST_F(PixelFormatInfoTest, PointerConstructor)
{
  static_assert(!noexcept(cen::pixel_format_info{nullptr}));
  static_assert(noexcept(cen::pixel_format_info_handle{nullptr}));

  ASSERT_THROW(cen::pixel_format_info{nullptr}, cen::exception);
  ASSERT_NO_THROW(cen::pixel_format_info_handle{nullptr});
}

TEST_F(PixelFormatInfoTest, FormatConstructor)
{
  const auto invalid = static_cast<cen::pixel_format>(0xFFFFFFFF);
  ASSERT_THROW(cen::pixel_format_info{invalid}, cen::sdl_error);
}

TEST_F(PixelFormatInfoTest, HandleFromOwner)
{
  const cen::pixel_format_info_handle handle{*info};
  ASSERT_TRUE(handle);
}

TEST_F(PixelFormatInfoTest, GetFormat)
{
  ASSERT_EQ(cen::pixel_format::rgba8888, info->format());
}

TEST_F(PixelFormatInfoTest, GetName)
{
  ASSERT_STREQ(SDL_GetPixelFormatName(info->get()->format), info->name());
}

TEST_F(PixelFormatInfoTest, RGBToPixel)
{
  const auto color = cen::colors::hot_pink;
  ASSERT_EQ(SDL_MapRGB(info->get(), color.red(), color.green(), color.blue()),
            info->rgb_to_pixel(color));
}

TEST_F(PixelFormatInfoTest, RGBAToPixel)
{
  const auto color = cen::colors::honey_dew;
  ASSERT_EQ(SDL_MapRGBA(info->get(), color.red(), color.green(), color.blue(), color.alpha()),
            info->rgba_to_pixel(color));
}

TEST_F(PixelFormatInfoTest, PixelToRGB)
{
  const auto color = cen::colors::hot_pink;
  const auto pixel = static_cast<Uint32>((color.red() << 24u) | (color.green() << 16u) |
                                         (color.blue() << 8u));
  ASSERT_EQ(color, info->pixel_to_rgb(pixel));
}

TEST_F(PixelFormatInfoTest, PixelToRGBA)
{
  const auto color = cen::colors::aquamarine;
  const Uint32 pixel = (color.red() << 24u) | (color.green() << 16u) | (color.blue() << 8u) |
                       (color.alpha() << 0u);
  ASSERT_EQ(color, info->pixel_to_rgba(pixel));
}

TEST_F(PixelFormatInfoTest, ToString)
{
  std::cout << *info << '\n';
}
