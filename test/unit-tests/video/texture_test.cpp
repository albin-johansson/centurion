#include "video/texture.hpp"

#include <SDL_image.h>
#include <gtest/gtest.h>

#include <iostream>  // clog
#include <memory>    // unique_ptr
#include <type_traits>

#include "core/exception.hpp"
#include "core/logging.hpp"
#include "video/colors.hpp"
#include "video/renderer.hpp"
#include "video/window.hpp"

static_assert(std::is_final_v<cen::texture>);

static_assert(std::is_nothrow_move_constructible_v<cen::texture>);
static_assert(std::is_nothrow_move_assignable_v<cen::texture>);

static_assert(!std::is_copy_constructible_v<cen::texture>);
static_assert(!std::is_copy_assignable_v<cen::texture>);

class TextureTest : public testing::Test {
 protected:
  static void SetUpTestSuite()
  {
    window = std::make_unique<cen::window>();
    renderer = std::make_unique<cen::Renderer>(*window);
    texture = std::make_unique<cen::texture>(*renderer, path);
  }

  static void TearDownTestSuite()
  {
    texture.reset();
    renderer.reset();
    window.reset();
  }

  inline static std::unique_ptr<cen::window> window;
  inline static std::unique_ptr<cen::Renderer> renderer;
  inline static std::unique_ptr<cen::texture> texture;

  inline constexpr static auto path = "resources/panda.png";
  inline constexpr static int imageWidth = 200;
  inline constexpr static int imageHeight = 150;
};

TEST_F(TextureTest, PointerConstructor)
{
  ASSERT_THROW(cen::texture{nullptr}, cen::Error);

  cen::texture texture{IMG_LoadTexture(renderer->get(), path)};
  ASSERT_TRUE(texture.get());
}

TEST_F(TextureTest, PathConstructor)
{
  using namespace std::string_literals;
  ASSERT_THROW(cen::texture(*renderer, "badpath"s), cen::IMGError);

  ASSERT_EQ(imageWidth, texture->width());
  ASSERT_EQ(imageHeight, texture->height());
}

TEST_F(TextureTest, SurfaceConstructor)
{
  const cen::Surface surface{path};
  ASSERT_NO_THROW(cen::texture(*renderer, surface));
}

TEST_F(TextureTest, CustomizationConstructor)
{
  constexpr auto format = cen::pixel_format::rgba32;
  constexpr auto access = cen::texture_access::no_lock;
  constexpr auto width = 145;
  constexpr auto height = 85;
  constexpr cen::Area size{width, height};

  const cen::texture texture{*renderer, format, access, size};

  ASSERT_EQ(format, texture.format());
  ASSERT_EQ(access, texture.access());
  ASSERT_EQ(size, texture.size());
  ASSERT_EQ(width, texture.width());
  ASSERT_EQ(height, texture.height());
}

TEST_F(TextureTest, Streaming)
{
  using namespace std::string_literals;
  const auto format = window->get_pixel_format();

  ASSERT_THROW(cen::texture::streaming(*renderer, "abc"s, format), cen::Error);

  auto texture = cen::texture::streaming(*renderer, path, format);
  ASSERT_EQ(format, texture.format());
  ASSERT_EQ(cen::texture_access::streaming, texture.access());
  ASSERT_TRUE(texture.is_streaming());
}

TEST_F(TextureTest, SetBlendMode)
{
  const auto previous = texture->get_blend_mode();

  constexpr auto mode = cen::BlendMode::Blend;
  texture->set_blend_mode(mode);

  ASSERT_EQ(mode, texture->get_blend_mode());

  texture->set_blend_mode(previous);
}

TEST_F(TextureTest, SetAlpha)
{
  const auto previous = texture->alpha();

  constexpr auto alpha = 0x3A;
  texture->set_alpha(alpha);

  ASSERT_EQ(alpha, texture->alpha());

  texture->set_alpha(previous);
}

TEST_F(TextureTest, SetColorMod)
{
  const auto previous = texture->color_mod();

  constexpr auto color = cen::colors::misty_rose;
  texture->set_color_mod(color);

  const auto actualColor = texture->color_mod();
  ASSERT_EQ(color, actualColor);

  texture->set_color_mod(previous);
}

TEST_F(TextureTest, Release)
{
  cen::texture texture{*renderer, path};

  auto ptr = texture.release();
  ASSERT_TRUE(ptr);

  SDL_DestroyTexture(ptr);
}

TEST_F(TextureTest, IsNoLock)
{
  const cen::texture texture{*renderer,
                             window->get_pixel_format(),
                             cen::texture_access::no_lock,
                             {10, 10}};
  ASSERT_TRUE(texture.is_no_lock());
}

TEST_F(TextureTest, IsStreaming)
{
  ASSERT_FALSE(texture->is_streaming());

  const auto format = window->get_pixel_format();
  const cen::texture streamingTexture = cen::texture::streaming(*renderer, path, format);
  ASSERT_TRUE(streamingTexture.is_streaming());
}

TEST_F(TextureTest, IsTarget)
{
  ASSERT_FALSE(texture->is_target());

  const auto format = window->get_pixel_format();
  const cen::texture target{*renderer, format, cen::texture_access::target, {10, 10}};
  ASSERT_TRUE(target.is_target());
}

TEST_F(TextureTest, Format)
{
  Uint32 format{};
  SDL_QueryTexture(texture->get(), &format, nullptr, nullptr, nullptr);

  const auto actual = static_cast<cen::pixel_format>(format);
  ASSERT_EQ(actual, texture->format());
}

TEST_F(TextureTest, Access)
{
  int access{};
  SDL_QueryTexture(texture->get(), nullptr, &access, nullptr, nullptr);

  const auto actual = static_cast<cen::texture_access>(access);
  ASSERT_EQ(actual, texture->access());
}

TEST_F(TextureTest, ColorMod)
{
  ASSERT_EQ(cen::colors::white, texture->color_mod());
}

TEST_F(TextureTest, Width)
{
  ASSERT_EQ(imageWidth, texture->width());

  int width{};
  SDL_QueryTexture(texture->get(), nullptr, nullptr, &width, nullptr);

  ASSERT_EQ(width, texture->width());
}

TEST_F(TextureTest, Height)
{
  ASSERT_EQ(imageHeight, texture->height());

  int height{};
  SDL_QueryTexture(texture->get(), nullptr, nullptr, nullptr, &height);

  ASSERT_EQ(height, texture->height());
}

TEST_F(TextureTest, ConversionToPointer)
{
  ASSERT_TRUE(texture->operator SDL_Texture*());
  ASSERT_TRUE(texture->operator const SDL_Texture*());
}

TEST_F(TextureTest, Get)
{
  ASSERT_TRUE(texture->get());
}

TEST_F(TextureTest, ToString)
{
  cen::log_info_raw(cen::to_string(*texture));
}

TEST_F(TextureTest, StreamOperator)
{
  std::clog << *texture << '\n';
}

#if SDL_VERSION_ATLEAST(2, 0, 12)

TEST_F(TextureTest, SetScaleMode)
{
  const auto previous = texture->get_scale_mode();

  texture->set_scale_mode(cen::scale_mode::nearest);
  ASSERT_EQ(cen::scale_mode::nearest, texture->get_scale_mode());

  texture->set_scale_mode(cen::scale_mode::linear);
  ASSERT_EQ(cen::scale_mode::linear, texture->get_scale_mode());

  texture->set_scale_mode(cen::scale_mode::best);
  ASSERT_EQ(cen::scale_mode::best, texture->get_scale_mode());

  texture->set_scale_mode(previous);
}

TEST_F(TextureTest, GetScaleMode)
{
  SDL_ScaleMode mode;
  SDL_GetTextureScaleMode(texture->get(), &mode);

  ASSERT_EQ(mode, static_cast<SDL_ScaleMode>(texture->get_scale_mode()));
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)
