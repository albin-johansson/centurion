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
  ASSERT_THROW(cen::texture{nullptr}, cen::Error);

  cen::texture texture{IMG_LoadTexture(m_renderer->get(), m_path)};
  ASSERT_TRUE(texture.get());
}

TEST_F(TextureTest, PathConstructor)
{
  using namespace std::string_literals;
  ASSERT_THROW(cen::texture(*m_renderer, "badpath"), cen::IMGError);
  ASSERT_THROW(cen::texture(*m_renderer, "badpath"s), cen::IMGError);

  ASSERT_EQ(m_imgWidth, m_texture->width());
  ASSERT_EQ(m_imgHeight, m_texture->height());
}

TEST_F(TextureTest, SurfaceConstructor)
{
  const cen::Surface surface{m_path};
  ASSERT_NO_THROW(cen::texture(*m_renderer, surface));
}

TEST_F(TextureTest, CustomizationConstructor)
{
  constexpr auto format = cen::pixel_format::rgba32;
  constexpr auto access = cen::texture_access::no_lock;
  constexpr auto width = 145;
  constexpr auto height = 85;
  constexpr cen::Area size{width, height};

  const cen::texture texture{*m_renderer, format, access, size};

  ASSERT_EQ(format, texture.format());
  ASSERT_EQ(access, texture.access());
  ASSERT_EQ(size, texture.size());
  ASSERT_EQ(width, texture.width());
  ASSERT_EQ(height, texture.height());
}

TEST_F(TextureTest, Streaming)
{
  using namespace std::string_literals;
  const auto format = m_window->get_pixel_format();

  ASSERT_THROW(cen::texture::streaming(*m_renderer, "abc"s, format), cen::Error);

  auto texture = cen::texture::streaming(*m_renderer, m_path, format);
  ASSERT_EQ(format, texture.format());
  ASSERT_EQ(cen::texture_access::streaming, texture.access());
  ASSERT_TRUE(texture.is_streaming());
}

TEST_F(TextureTest, SetBlendMode)
{
  const auto previous = m_texture->get_blend_mode();

  constexpr auto mode = cen::blend_mode::blend;
  m_texture->set_blend_mode(mode);

  ASSERT_EQ(mode, m_texture->get_blend_mode());

  m_texture->set_blend_mode(previous);
}

TEST_F(TextureTest, SetAlpha)
{
  const auto previous = m_texture->alpha();

  constexpr auto alpha = 0x3A;
  m_texture->set_alpha(alpha);

  ASSERT_EQ(alpha, m_texture->alpha());

  m_texture->set_alpha(previous);
}

TEST_F(TextureTest, SetColorMod)
{
  const auto previous = m_texture->color_mod();

  constexpr auto color = cen::colors::misty_rose;
  m_texture->set_color_mod(color);

  const auto actualColor = m_texture->color_mod();
  ASSERT_EQ(color, actualColor);

  m_texture->set_color_mod(previous);
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
  ASSERT_TRUE(texture.is_no_lock());
}

TEST_F(TextureTest, IsStreaming)
{
  ASSERT_FALSE(m_texture->is_streaming());

  const auto format = m_window->get_pixel_format();
  const cen::texture streamingTexture = cen::texture::streaming(*m_renderer, m_path, format);
  ASSERT_TRUE(streamingTexture.is_streaming());
}

TEST_F(TextureTest, IsTarget)
{
  ASSERT_FALSE(m_texture->is_target());

  const auto format = m_window->get_pixel_format();
  const cen::texture target{*m_renderer, format, cen::texture_access::target, {10, 10}};
  ASSERT_TRUE(target.is_target());
}

TEST_F(TextureTest, Format)
{
  Uint32 format{};
  SDL_QueryTexture(m_texture->get(), &format, nullptr, nullptr, nullptr);

  const auto actual = static_cast<cen::pixel_format>(format);
  ASSERT_EQ(actual, m_texture->format());
}

TEST_F(TextureTest, Access)
{
  int access{};
  SDL_QueryTexture(m_texture->get(), nullptr, &access, nullptr, nullptr);

  const auto actual = static_cast<cen::texture_access>(access);
  ASSERT_EQ(actual, m_texture->access());
}

TEST_F(TextureTest, ColorMod)
{
  ASSERT_EQ(cen::colors::white, m_texture->color_mod());
}

TEST_F(TextureTest, Width)
{
  ASSERT_EQ(m_imgWidth, m_texture->width());

  int width{};
  SDL_QueryTexture(m_texture->get(), nullptr, nullptr, &width, nullptr);

  ASSERT_EQ(width, m_texture->width());
}

TEST_F(TextureTest, Height)
{
  ASSERT_EQ(m_imgHeight, m_texture->height());

  int height{};
  SDL_QueryTexture(m_texture->get(), nullptr, nullptr, nullptr, &height);

  ASSERT_EQ(height, m_texture->height());
}

TEST_F(TextureTest, ConversionToPointer)
{
  ASSERT_TRUE(m_texture->operator SDL_Texture*());
  ASSERT_TRUE(m_texture->operator const SDL_Texture*());
}

TEST_F(TextureTest, Get)
{
  ASSERT_TRUE(m_texture->get());
}

TEST_F(TextureTest, ToString)
{
  cen::log_info_raw(cen::to_string(*m_texture));
}

TEST_F(TextureTest, StreamOperator)
{
  std::clog << *m_texture << '\n';
}

#if SDL_VERSION_ATLEAST(2, 0, 12)

TEST_F(TextureTest, SetScaleMode)
{
  const auto previous = m_texture->get_scale_mode();

  m_texture->set_scale_mode(cen::scale_mode::nearest);
  ASSERT_EQ(cen::scale_mode::nearest, m_texture->get_scale_mode());

  m_texture->set_scale_mode(cen::scale_mode::linear);
  ASSERT_EQ(cen::scale_mode::linear, m_texture->get_scale_mode());

  m_texture->set_scale_mode(cen::scale_mode::best);
  ASSERT_EQ(cen::scale_mode::best, m_texture->get_scale_mode());

  m_texture->set_scale_mode(previous);
}

TEST_F(TextureTest, GetScaleMode)
{
  SDL_ScaleMode mode;
  SDL_GetTextureScaleMode(m_texture->get(), &mode);

  ASSERT_EQ(mode, static_cast<SDL_ScaleMode>(m_texture->get_scale_mode()));
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)
