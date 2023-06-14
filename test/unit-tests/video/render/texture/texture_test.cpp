/*
 * MIT License
 *
 * Copyright (c) 2019-2022 Albin Johansson
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

class TextureTest : public testing::Test {
 protected:
  static void SetUpTestSuite()
  {
    window = std::make_unique<cen::window>();
    renderer = std::make_unique<cen::renderer>(window->make_renderer());
    texture = std::make_unique<cen::texture>(renderer->make_texture(path));
  }

  static void TearDownTestSuite()
  {
    texture.reset();
    renderer.reset();
    window.reset();
  }

  inline static std::unique_ptr<cen::window> window;
  inline static std::unique_ptr<cen::renderer> renderer;
  inline static std::unique_ptr<cen::texture> texture;

  inline constexpr static auto path = "resources/panda.png";
  inline constexpr static int imageWidth = 200;
  inline constexpr static int imageHeight = 150;
};

TEST_F(TextureTest, PointerConstructor)
{
  ASSERT_THROW(cen::texture {nullptr}, cen::exception);

  cen::texture texture {IMG_LoadTexture(renderer->get(), path)};
  ASSERT_TRUE(texture.get());
}

TEST_F(TextureTest, PathConstructor)
{
  using namespace std::string_literals;
  ASSERT_THROW(renderer->make_texture("badpath"s), cen::img_error);

  ASSERT_EQ(imageWidth, texture->width());
  ASSERT_EQ(imageHeight, texture->height());
}

TEST_F(TextureTest, SurfaceConstructor)
{
  const cen::surface surface {path};
  ASSERT_NO_THROW(renderer->make_texture(surface));
}

TEST_F(TextureTest, CustomizationConstructor)
{
  constexpr auto format = cen::pixel_format::rgba32;
  constexpr auto access = cen::texture_access::non_lockable;
  constexpr auto width = 145;
  constexpr auto height = 85;
  constexpr cen::iarea size {width, height};

  const auto texture = renderer->make_texture(size, format, access);

  ASSERT_EQ(format, texture.format());
  ASSERT_EQ(access, texture.access());
  ASSERT_EQ(size, texture.size());
  ASSERT_EQ(width, texture.width());
  ASSERT_EQ(height, texture.height());
}

TEST_F(TextureTest, SetBlendMode)
{
  const auto previous = texture->get_blend_mode();

  constexpr auto mode = cen::blend_mode::blend;
  texture->set_blend_mode(mode);

  ASSERT_EQ(mode, texture->get_blend_mode());

  texture->set_blend_mode(previous);
}

TEST_F(TextureTest, SetAlphaMod)
{
  const auto previous = texture->alpha_mod();

  constexpr auto alpha = 0x3A;
  texture->set_alpha_mod(alpha);

  ASSERT_EQ(alpha, texture->alpha_mod());

  texture->set_alpha_mod(previous);
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
  auto texture = renderer->make_texture(path);

  auto ptr = texture.release();
  ASSERT_TRUE(ptr);

  SDL_DestroyTexture(ptr);
}

TEST_F(TextureTest, IsStatic)
{
  const auto texture =
      renderer->make_texture({10, 10}, window->format(), cen::texture_access::non_lockable);
  ASSERT_TRUE(texture.is_static());
}

TEST_F(TextureTest, IsTarget)
{
  ASSERT_FALSE(texture->is_target());

  const auto format = window->format();
  const auto target = renderer->make_texture({10, 10}, format, cen::texture_access::target);
  ASSERT_TRUE(target.is_target());
}

TEST_F(TextureTest, GetFormat)
{
  Uint32 format {};
  SDL_QueryTexture(texture->get(), &format, nullptr, nullptr, nullptr);

  const auto actual = static_cast<cen::pixel_format>(format);
  ASSERT_EQ(actual, texture->format());
}

TEST_F(TextureTest, GetAccess)
{
  int access {};
  SDL_QueryTexture(texture->get(), nullptr, &access, nullptr, nullptr);

  const auto actual = static_cast<cen::texture_access>(access);
  ASSERT_EQ(actual, texture->access());
}

TEST_F(TextureTest, ColorMod)
{
  ASSERT_EQ(cen::colors::white, texture->color_mod());
}

TEST_F(TextureTest, GetSize)
{
  const auto size = texture->size();
  ASSERT_EQ(imageWidth, size.width);
  ASSERT_EQ(imageHeight, size.height);
}

TEST_F(TextureTest, Get)
{
  ASSERT_TRUE(texture->get());
}

TEST_F(TextureTest, StreamOperator)
{
  std::cout << *texture << '\n';
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

#if SDL_VERSION_ATLEAST(2, 0, 18)

TEST_F(TextureTest, UserData)
{
  int i = 42;
  ASSERT_EQ(cen::success, texture->set_user_data(&i));

  auto* ptr = reinterpret_cast<int*>(texture->user_data());
  ASSERT_TRUE(ptr);
  ASSERT_EQ(i, *ptr);
}

#endif  // #if SDL_VERSION_ATLEAST(2, 0, 18)