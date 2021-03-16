#include "texture.hpp"

#include <SDL_image.h>
#include <gtest/gtest.h>

#include <iostream>  // cout
#include <memory>    // unique_ptr
#include <type_traits>

#include "colors.hpp"
#include "exception.hpp"
#include "log.hpp"
#include "renderer.hpp"
#include "window.hpp"

static_assert(std::is_final_v<cen::texture>);

static_assert(std::is_nothrow_move_constructible_v<cen::texture>);
static_assert(std::is_nothrow_move_assignable_v<cen::texture>);

static_assert(!std::is_copy_constructible_v<cen::texture>);
static_assert(!std::is_copy_assignable_v<cen::texture>);

class TextureTest : public testing::Test
{
 protected:
  static void SetUpTestSuite()
  {
    m_window = std::make_unique<cen::window>();
    m_renderer = std::make_unique<cen::renderer>(*m_window);
    m_texture = std::make_unique<cen::texture>(*m_renderer, m_path);
  }

  static void TearDownTestSuite()
  {
    m_texture.reset();
    m_renderer.reset();
    m_window.reset();
  }

  inline static std::unique_ptr<cen::window> m_window;
  inline static std::unique_ptr<cen::renderer> m_renderer;
  inline static std::unique_ptr<cen::texture> m_texture;

  inline constexpr static auto m_path = "resources/panda.png";
  inline constexpr static int m_imgWidth = 200;
  inline constexpr static int m_imgHeight = 150;
};

TEST_F(TextureTest, PointerConstructor)
{
  EXPECT_THROW(cen::texture{nullptr}, cen::cen_error);

  cen::texture texture{IMG_LoadTexture(m_renderer->get(), m_path)};
  EXPECT_TRUE(texture.get());
}

TEST_F(TextureTest, PathConstructor)
{
  using namespace std::string_literals;
  EXPECT_THROW(cen::texture(*m_renderer, "badpath"), cen::img_error);
  EXPECT_THROW(cen::texture(*m_renderer, "badpath"s), cen::img_error);

  EXPECT_EQ(m_imgWidth, m_texture->width());
  EXPECT_EQ(m_imgHeight, m_texture->height());
}

TEST_F(TextureTest, SurfaceConstructor)
{
  const cen::surface surface{m_path};
  EXPECT_NO_THROW(cen::texture(*m_renderer, surface));
}

TEST_F(TextureTest, CustomizationConstructor)
{
  constexpr auto format = cen::pixel_format::rgba32;
  constexpr auto access = cen::texture_access::no_lock;
  constexpr auto width = 145;
  constexpr auto height = 85;
  constexpr cen::iarea size{width, height};

  const cen::texture texture{*m_renderer, format, access, size};

  EXPECT_EQ(format, texture.format());
  EXPECT_EQ(access, texture.access());
  EXPECT_EQ(size, texture.size());
  EXPECT_EQ(width, texture.width());
  EXPECT_EQ(height, texture.height());
}

TEST_F(TextureTest, Streaming)
{
  using namespace std::string_literals;
  const auto format = m_window->get_pixel_format();

  EXPECT_THROW(cen::texture::streaming(*m_renderer, "abc"s, format),
               cen::cen_error);

  auto texture = cen::texture::streaming(*m_renderer, m_path, format);
  EXPECT_EQ(format, texture.format());
  EXPECT_EQ(cen::texture_access::streaming, texture.access());
  EXPECT_TRUE(texture.is_streaming());
}

TEST_F(TextureTest, SetPixel)
{
  constexpr auto format = cen::pixel_format::rgba8888;
  constexpr auto color = cen::colors::black;

  auto texture = cen::texture::streaming(*m_renderer, m_path, format);
  const auto [width, height] = texture.size();

  EXPECT_NO_THROW(texture.set_pixel({-1, -1}, color));
  EXPECT_NO_THROW(texture.set_pixel({-1, 0}, color));
  EXPECT_NO_THROW(texture.set_pixel({0, -1}, color));
  EXPECT_NO_THROW(texture.set_pixel({width, 0}, color));
  EXPECT_NO_THROW(texture.set_pixel({0, height}, color));
  EXPECT_NO_THROW(texture.set_pixel({width, height}, color));
  EXPECT_NO_THROW(texture.set_pixel({45, 23}, color));
}

TEST_F(TextureTest, SetBlendMode)
{
  const auto previous = m_texture->get_blend_mode();

  constexpr auto mode = cen::blend_mode::blend;
  m_texture->set_blend_mode(mode);

  EXPECT_EQ(mode, m_texture->get_blend_mode());

  m_texture->set_blend_mode(previous);
}

TEST_F(TextureTest, SetAlpha)
{
  const auto previous = m_texture->alpha();

  constexpr auto alpha = 0x3A;
  m_texture->set_alpha(alpha);

  EXPECT_EQ(alpha, m_texture->alpha());

  m_texture->set_alpha(previous);
}

TEST_F(TextureTest, SetColorMod)
{
  const auto previous = m_texture->color_mod();

  constexpr auto color = cen::colors::misty_rose;
  m_texture->set_color_mod(color);

  const auto actualColor = m_texture->color_mod();
  EXPECT_EQ(color, actualColor);

  m_texture->set_color_mod(previous);
}

TEST_F(TextureTest, SetScaleMode)
{
  const auto previous = m_texture->get_scale_mode();

  m_texture->set_scale_mode(cen::scale_mode::nearest);
  EXPECT_EQ(cen::scale_mode::nearest, m_texture->get_scale_mode());

  m_texture->set_scale_mode(cen::scale_mode::linear);
  EXPECT_EQ(cen::scale_mode::linear, m_texture->get_scale_mode());

  m_texture->set_scale_mode(cen::scale_mode::best);
  EXPECT_EQ(cen::scale_mode::best, m_texture->get_scale_mode());

  m_texture->set_scale_mode(previous);
}

TEST_F(TextureTest, Release)
{
  cen::texture texture{*m_renderer, m_path};

  auto ptr = texture.release();
  ASSERT_TRUE(ptr);

  SDL_DestroyTexture(ptr);
}

TEST_F(TextureTest, IsNoLock)
{
  const cen::texture texture{*m_renderer,
                             m_window->get_pixel_format(),
                             cen::texture_access::no_lock,
                             {10, 10}};
  EXPECT_TRUE(texture.is_no_lock());
}

TEST_F(TextureTest, IsStreaming)
{
  EXPECT_FALSE(m_texture->is_streaming());

  const auto format = m_window->get_pixel_format();
  const cen::texture streamingTexture =
      cen::texture::streaming(*m_renderer, m_path, format);
  EXPECT_TRUE(streamingTexture.is_streaming());
}

TEST_F(TextureTest, IsTarget)
{
  EXPECT_FALSE(m_texture->is_target());

  const auto format = m_window->get_pixel_format();
  const cen::texture target{*m_renderer,
                            format,
                            cen::texture_access::target,
                            {10, 10}};
  EXPECT_TRUE(target.is_target());
}

TEST_F(TextureTest, Format)
{
  cen::u32 format{};
  SDL_QueryTexture(m_texture->get(), &format, nullptr, nullptr, nullptr);

  const auto actual = static_cast<cen::pixel_format>(format);
  EXPECT_EQ(actual, m_texture->format());
}

TEST_F(TextureTest, Access)
{
  int access{};
  SDL_QueryTexture(m_texture->get(), nullptr, &access, nullptr, nullptr);

  const auto actual = static_cast<cen::texture_access>(access);
  EXPECT_EQ(actual, m_texture->access());
}

TEST_F(TextureTest, ColorMod)
{
  EXPECT_EQ(cen::colors::white, m_texture->color_mod());
}

TEST_F(TextureTest, GetScaleMode)
{
  SDL_ScaleMode mode;
  SDL_GetTextureScaleMode(m_texture->get(), &mode);

  EXPECT_EQ(mode, static_cast<SDL_ScaleMode>(m_texture->get_scale_mode()));
}

TEST_F(TextureTest, Width)
{
  EXPECT_EQ(m_imgWidth, m_texture->width());

  int width{};
  SDL_QueryTexture(m_texture->get(), nullptr, nullptr, &width, nullptr);

  EXPECT_EQ(width, m_texture->width());
}

TEST_F(TextureTest, Height)
{
  EXPECT_EQ(m_imgHeight, m_texture->height());

  int height{};
  SDL_QueryTexture(m_texture->get(), nullptr, nullptr, nullptr, &height);

  EXPECT_EQ(height, m_texture->height());
}

TEST_F(TextureTest, ConversionToPointer)
{
  EXPECT_TRUE(m_texture->operator SDL_Texture*());
  EXPECT_TRUE(m_texture->operator const SDL_Texture*());
}

TEST_F(TextureTest, Get)
{
  EXPECT_TRUE(m_texture->get());
}

TEST_F(TextureTest, ToString)
{
  cen::log::put(cen::to_string(*m_texture));
}

TEST_F(TextureTest, StreamOperator)
{
  std::cout << "COUT: " << *m_texture << '\n';
}
