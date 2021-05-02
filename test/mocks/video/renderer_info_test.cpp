#include "video/renderer_info.hpp"

#include <fff.h>
#include <gtest/gtest.h>

#include <array>  // array

#include "core_mocks.hpp"

extern "C" {
FAKE_VALUE_FUNC(int, SDL_GetRendererInfo, SDL_Renderer*, SDL_RendererInfo*)
}

inline constexpr auto name = "foobar";
inline constexpr int max_texture_width = 123;
inline constexpr int max_texture_height = 321;
inline constexpr Uint32 flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
inline constexpr Uint32 num_texture_formats = 3;
inline constexpr Uint32 texture_format_0 = SDL_PIXELFORMAT_RGBA8888;
inline constexpr Uint32 texture_format_1 = SDL_PIXELFORMAT_RGBA4444;
inline constexpr Uint32 texture_format_2 = SDL_PIXELFORMAT_RGB444;

auto get_renderer_info(SDL_Renderer*, SDL_RendererInfo* info) -> int
{
  if (info)
  {
    info->name = name;
    info->flags = flags;

    info->max_texture_width = max_texture_width;
    info->max_texture_height = max_texture_height;

    info->num_texture_formats = num_texture_formats;
    info->texture_formats[0] = texture_format_0;
    info->texture_formats[1] = texture_format_1;
    info->texture_formats[2] = texture_format_2;
  }

  return 0;
}

class RendererInfoTest : public testing::Test
{
 protected:
  void SetUp() override
  {
    mocks::reset_core();

    RESET_FAKE(SDL_GetRendererInfo)
  }
};

TEST_F(RendererInfoTest, Foo)
{
  std::array functions{get_renderer_info};
  SET_CUSTOM_FAKE_SEQ(SDL_GetRendererInfo, functions.data(), cen::isize(functions));

  cen::renderer_handle handle{nullptr};

  const auto info = cen::get_info(handle);
  ASSERT_TRUE(info);

  ASSERT_STREQ(name, info->name());

  ASSERT_EQ(flags, info->supported_flags());
  ASSERT_TRUE(info->has_vsync());
  ASSERT_TRUE(info->has_hardware_acceleration());
  ASSERT_FALSE(info->has_target_textures());
  ASSERT_FALSE(info->has_software_renderer());

  ASSERT_EQ(max_texture_width, info->max_texture_width());
  ASSERT_EQ(max_texture_height, info->max_texture_height());
  ASSERT_EQ(max_texture_width, info->max_texture_size().width);
  ASSERT_EQ(max_texture_height, info->max_texture_size().height);

  ASSERT_EQ(num_texture_formats, info->format_count());
  ASSERT_EQ(texture_format_0, static_cast<Uint32>(info->format(0)));
  ASSERT_EQ(texture_format_1, static_cast<Uint32>(info->format(1)));
  ASSERT_EQ(texture_format_2, static_cast<Uint32>(info->format(2)));
}
