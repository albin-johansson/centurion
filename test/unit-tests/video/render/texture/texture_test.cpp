/*
 * MIT License
 *
 * Copyright (c) 2019-2023 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "centurion/video/texture.hpp"

#include <SDL_image.h>
#include <gtest/gtest.h>

#include <iostream>     // cout
#include <memory>       // unique_ptr
#include <type_traits>  // ...

#include "centurion/video/color.hpp"
#include "centurion/video/window.hpp"

static_assert(std::is_final_v<cen::texture>);

static_assert(std::is_nothrow_move_constructible_v<cen::texture>);
static_assert(std::is_nothrow_move_assignable_v<cen::texture>);

static_assert(!std::is_copy_constructible_v<cen::texture>);
static_assert(!std::is_copy_assignable_v<cen::texture>);

inline constexpr static const char* kImagePath = "resources/panda.png";
inline constexpr static int kImageWidth = 200;
inline constexpr static int kImageHeight = 150;

class TextureTest : public testing::Test {
 protected:
  static void SetUpTestSuite()
  {
    mWindow = std::make_unique<cen::window>();
    mRenderer = std::make_unique<cen::renderer>(mWindow->make_renderer());
    mTexture = std::make_unique<cen::texture>(mRenderer->make_texture(kImagePath));
  }

  static void TearDownTestSuite()
  {
    mTexture.reset();
    mRenderer.reset();
    mWindow.reset();
  }

  inline static std::unique_ptr<cen::window> mWindow;
  inline static std::unique_ptr<cen::renderer> mRenderer;
  inline static std::unique_ptr<cen::texture> mTexture;
};

TEST_F(TextureTest, PointerConstructor)
{
  ASSERT_THROW(cen::texture {nullptr}, cen::exception);

  cen::texture texture {IMG_LoadTexture(mRenderer->get(), kImagePath)};
  ASSERT_TRUE(texture.get());
}

TEST_F(TextureTest, PathConstructor)
{
  using namespace std::string_literals;
  ASSERT_THROW(mRenderer->make_texture("badpath"s), cen::img_error);

  ASSERT_EQ(kImageWidth, mTexture->width());
  ASSERT_EQ(kImageHeight, mTexture->height());
}

TEST_F(TextureTest, SurfaceConstructor)
{
  const cen::surface surface {kImagePath};
  ASSERT_NO_THROW(mRenderer->make_texture(surface));
}

TEST_F(TextureTest, CustomizationConstructor)
{
  constexpr auto format = cen::pixel_format::rgba32;
  constexpr auto access = cen::texture_access::non_lockable;
  constexpr auto width = 145;
  constexpr auto height = 85;
  constexpr cen::iarea size {width, height};

  const auto texture = mRenderer->make_texture(size, format, access);

  ASSERT_EQ(format, texture.format());
  ASSERT_EQ(access, texture.access());
  ASSERT_EQ(size, texture.size());
  ASSERT_EQ(width, texture.width());
  ASSERT_EQ(height, texture.height());
}

TEST_F(TextureTest, SetBlendMode)
{
  const auto previous = mTexture->get_blend_mode();

  constexpr auto mode = cen::blend_mode::blend;
  mTexture->set_blend_mode(mode);

  ASSERT_EQ(mode, mTexture->get_blend_mode());

  mTexture->set_blend_mode(previous);
}

TEST_F(TextureTest, SetAlphaMod)
{
  const auto previous = mTexture->alpha_mod();

  constexpr auto alpha = 0x3A;
  mTexture->set_alpha_mod(alpha);

  ASSERT_EQ(alpha, mTexture->alpha_mod());

  mTexture->set_alpha_mod(previous);
}

TEST_F(TextureTest, SetColorMod)
{
  const auto previous = mTexture->color_mod();

  constexpr auto color = cen::colors::misty_rose;
  mTexture->set_color_mod(color);

  const auto actualColor = mTexture->color_mod();
  ASSERT_EQ(color, actualColor);

  mTexture->set_color_mod(previous);
}

TEST_F(TextureTest, Release)
{
  auto texture = mRenderer->make_texture(kImagePath);

  auto ptr = texture.release();
  ASSERT_TRUE(ptr);

  SDL_DestroyTexture(ptr);
}

TEST_F(TextureTest, IsStatic)
{
  const auto texture =
      mRenderer->make_texture({10, 10}, mWindow->format(), cen::texture_access::non_lockable);
  ASSERT_TRUE(texture.is_static());
}

TEST_F(TextureTest, IsTarget)
{
  ASSERT_FALSE(mTexture->is_target());

  const auto format = mWindow->format();
  const auto target = mRenderer->make_texture({10, 10}, format, cen::texture_access::target);
  ASSERT_TRUE(target.is_target());
}

TEST_F(TextureTest, GetFormat)
{
  Uint32 format {};
  SDL_QueryTexture(mTexture->get(), &format, nullptr, nullptr, nullptr);

  const auto actual = static_cast<cen::pixel_format>(format);
  ASSERT_EQ(actual, mTexture->format());
}

TEST_F(TextureTest, GetAccess)
{
  int access {};
  SDL_QueryTexture(mTexture->get(), nullptr, &access, nullptr, nullptr);

  const auto actual = static_cast<cen::texture_access>(access);
  ASSERT_EQ(actual, mTexture->access());
}

TEST_F(TextureTest, ColorMod)
{
  ASSERT_EQ(cen::colors::white, mTexture->color_mod());
}

TEST_F(TextureTest, GetSize)
{
  const auto size = mTexture->size();
  ASSERT_EQ(kImageWidth, size.width);
  ASSERT_EQ(kImageHeight, size.height);
}

TEST_F(TextureTest, Get)
{
  ASSERT_TRUE(mTexture->get());
}

TEST_F(TextureTest, StreamOperator)
{
  std::cout << *mTexture << '\n';
}

#if SDL_VERSION_ATLEAST(2, 0, 12)

TEST_F(TextureTest, SetScaleMode)
{
  const auto previous = mTexture->get_scale_mode();

  mTexture->set_scale_mode(cen::scale_mode::nearest);
  ASSERT_EQ(cen::scale_mode::nearest, mTexture->get_scale_mode());

  mTexture->set_scale_mode(cen::scale_mode::linear);
  ASSERT_EQ(cen::scale_mode::linear, mTexture->get_scale_mode());

  mTexture->set_scale_mode(cen::scale_mode::best);
  ASSERT_EQ(cen::scale_mode::best, mTexture->get_scale_mode());

  mTexture->set_scale_mode(previous);
}

TEST_F(TextureTest, GetScaleMode)
{
  SDL_ScaleMode mode;
  SDL_GetTextureScaleMode(mTexture->get(), &mode);

  ASSERT_EQ(mode, static_cast<SDL_ScaleMode>(mTexture->get_scale_mode()));
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

#if SDL_VERSION_ATLEAST(2, 0, 18)

TEST_F(TextureTest, UserData)
{
  int i = 42;
  ASSERT_EQ(cen::success, mTexture->set_user_data(&i));

  auto* ptr = reinterpret_cast<int*>(mTexture->user_data());
  ASSERT_TRUE(ptr);
  ASSERT_EQ(i, *ptr);
}

#endif  // #if SDL_VERSION_ATLEAST(2, 0, 18)