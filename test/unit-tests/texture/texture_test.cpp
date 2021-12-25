#include <SDL_image.h>
#include <gtest/gtest.h>

#include <iostream>  // clog
#include <memory>    // unique_ptr
#include <type_traits>

#include "color.hpp"
#include "common.hpp"
#include "core/logging.hpp"
#include "render.hpp"
#include "window.hpp"

static_assert(std::is_final_v<cen::Texture>);

static_assert(std::is_nothrow_move_constructible_v<cen::Texture>);
static_assert(std::is_nothrow_move_assignable_v<cen::Texture>);

static_assert(!std::is_copy_constructible_v<cen::Texture>);
static_assert(!std::is_copy_assignable_v<cen::Texture>);

class TextureTest : public testing::Test {
 protected:
  static void SetUpTestSuite()
  {
    window = std::make_unique<cen::Window>();
    renderer = std::make_unique<cen::Renderer>(*window);
    texture = std::make_unique<cen::Texture>(*renderer, path);
  }

  static void TearDownTestSuite()
  {
    texture.reset();
    renderer.reset();
    window.reset();
  }

  inline static std::unique_ptr<cen::Window> window;
  inline static std::unique_ptr<cen::Renderer> renderer;
  inline static std::unique_ptr<cen::Texture> texture;

  inline constexpr static auto path = "resources/panda.png";
  inline constexpr static int imageWidth = 200;
  inline constexpr static int imageHeight = 150;
};

TEST_F(TextureTest, PointerConstructor)
{
  ASSERT_THROW(cen::Texture{nullptr}, cen::Error);

  cen::Texture texture{IMG_LoadTexture(renderer->get(), path)};
  ASSERT_TRUE(texture.get());
}

TEST_F(TextureTest, PathConstructor)
{
  using namespace std::string_literals;
  ASSERT_THROW(cen::Texture(*renderer, "badpath"s), cen::IMGError);

  ASSERT_EQ(imageWidth, texture->GetWidth());
  ASSERT_EQ(imageHeight, texture->GetHeight());
}

TEST_F(TextureTest, SurfaceConstructor)
{
  const cen::Surface surface{path};
  ASSERT_NO_THROW(cen::Texture(*renderer, surface));
}

TEST_F(TextureTest, CustomizationConstructor)
{
  constexpr auto format = cen::PixelFormat::RGBA32;
  constexpr auto access = cen::TextureAccess::Static;
  constexpr auto width = 145;
  constexpr auto height = 85;
  constexpr cen::Area size{width, height};

  const cen::Texture texture{*renderer, format, access, size};

  ASSERT_EQ(format, texture.GetFormat());
  ASSERT_EQ(access, texture.GetAccess());
  ASSERT_EQ(size, texture.GetSize());
  ASSERT_EQ(width, texture.GetWidth());
  ASSERT_EQ(height, texture.GetHeight());
}

TEST_F(TextureTest, SetBlendMode)
{
  const auto previous = texture->GetBlendMode();

  constexpr auto mode = cen::BlendMode::Blend;
  texture->SetBlendMode(mode);

  ASSERT_EQ(mode, texture->GetBlendMode());

  texture->SetBlendMode(previous);
}

TEST_F(TextureTest, SetAlpha)
{
  const auto previous = texture->GetAlpha();

  constexpr auto alpha = 0x3A;
  texture->SetAlpha(alpha);

  ASSERT_EQ(alpha, texture->GetAlpha());

  texture->SetAlpha(previous);
}

TEST_F(TextureTest, SetColorMod)
{
  const auto previous = texture->GetColorMod();

  constexpr auto color = cen::colors::misty_rose;
  texture->SetColorMod(color);

  const auto actualColor = texture->GetColorMod();
  ASSERT_EQ(color, actualColor);

  texture->SetColorMod(previous);
}

TEST_F(TextureTest, Release)
{
  cen::Texture texture{*renderer, path};

  auto ptr = texture.release();
  ASSERT_TRUE(ptr);

  SDL_DestroyTexture(ptr);
}

TEST_F(TextureTest, IsStatic)
{
  const cen::Texture texture{*renderer,
                             window->GetPixelFormat(),
                             cen::TextureAccess::Static,
                             {10, 10}};
  ASSERT_TRUE(texture.IsStatic());
}

TEST_F(TextureTest, IsTarget)
{
  ASSERT_FALSE(texture->IsTarget());

  const auto format = window->GetPixelFormat();
  const cen::Texture target{*renderer, format, cen::TextureAccess::Target, {10, 10}};
  ASSERT_TRUE(target.IsTarget());
}

TEST_F(TextureTest, GetFormat)
{
  Uint32 format{};
  SDL_QueryTexture(texture->get(), &format, nullptr, nullptr, nullptr);

  const auto actual = static_cast<cen::PixelFormat>(format);
  ASSERT_EQ(actual, texture->GetFormat());
}

TEST_F(TextureTest, GetAccess)
{
  int access{};
  SDL_QueryTexture(texture->get(), nullptr, &access, nullptr, nullptr);

  const auto actual = static_cast<cen::TextureAccess>(access);
  ASSERT_EQ(actual, texture->GetAccess());
}

TEST_F(TextureTest, ColorMod)
{
  ASSERT_EQ(cen::colors::white, texture->GetColorMod());
}

TEST_F(TextureTest, GetSize)
{
  const auto size = texture->GetSize();
  ASSERT_EQ(imageWidth, size.width);
  ASSERT_EQ(imageHeight, size.height);
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
  const auto previous = texture->GetScaleMode();

  texture->SetScaleMode(cen::ScaleMode::Nearest);
  ASSERT_EQ(cen::ScaleMode::Nearest, texture->GetScaleMode());

  texture->SetScaleMode(cen::ScaleMode::Linear);
  ASSERT_EQ(cen::ScaleMode::Linear, texture->GetScaleMode());

  texture->SetScaleMode(cen::ScaleMode::Best);
  ASSERT_EQ(cen::ScaleMode::Best, texture->GetScaleMode());

  texture->SetScaleMode(previous);
}

TEST_F(TextureTest, GetScaleMode)
{
  SDL_ScaleMode mode;
  SDL_GetTextureScaleMode(texture->get(), &mode);

  ASSERT_EQ(mode, static_cast<SDL_ScaleMode>(texture->GetScaleMode()));
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)
