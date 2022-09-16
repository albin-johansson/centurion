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

#include "centurion/surface.hpp"

#include <SDL_image.h>
#include <gtest/gtest.h>

#include <iostream>     // cout
#include <memory>       // unique_ptr
#include <type_traits>  // ...
#include <utility>      // move

#include "centurion/color.hpp"
#include "centurion/window.hpp"

static_assert(std::is_copy_constructible_v<cen::surface>);
static_assert(std::is_copy_assignable_v<cen::surface>);

static_assert(std::is_nothrow_move_constructible_v<cen::surface>);
static_assert(std::is_nothrow_move_assignable_v<cen::surface>);

static_assert(std::is_copy_constructible_v<cen::surface_handle>);
static_assert(std::is_copy_assignable_v<cen::surface_handle>);

static_assert(std::is_nothrow_move_constructible_v<cen::surface_handle>);
static_assert(std::is_nothrow_move_assignable_v<cen::surface_handle>);

using namespace std::string_literals;

class SurfaceTest : public testing::Test {
 protected:
  static void SetUpTestSuite() { surface = std::make_unique<cen::surface>(path); }

  static void TearDownTestSuite() { surface.reset(); }

  inline constexpr static auto path = "resources/panda.png";
  inline static std::unique_ptr<cen::surface> surface;
};

TEST_F(SurfaceTest, PathConstructor)
{
  ASSERT_THROW(cen::surface(""), cen::exception);
  ASSERT_THROW(cen::surface(""s), cen::exception);
  ASSERT_NO_THROW(cen::surface{path});
}

TEST_F(SurfaceTest, FromSDLSurfaceConstructor)
{
  ASSERT_NO_THROW(cen::surface(IMG_Load(path)));

  SDL_Surface* ptr{};
  ASSERT_THROW(cen::surface{ptr}, cen::exception);
}

TEST_F(SurfaceTest, SizePixelFormatConstructor)
{
  cen::window window;
  cen::surface image{{10, 10}, window.format()};
  ASSERT_EQ(10, image.width());
  ASSERT_EQ(10, image.height());
  ASSERT_EQ(window.format(), image.format_info().format());
}

TEST_F(SurfaceTest, CopyConstructor)
{
  const cen::surface copy{*surface};

  ASSERT_NE(surface->get(), copy.get());
  ASSERT_TRUE(surface->get());
  ASSERT_TRUE(copy.get());
}

TEST_F(SurfaceTest, MoveConstructor)
{
  cen::surface copy{*surface};
  const cen::surface moved{std::move(copy)};

  ASSERT_FALSE(copy.get());
  ASSERT_TRUE(moved.get());
}

TEST_F(SurfaceTest, CopyAssignment)
{
  cen::surface destination = *surface;

  ASSERT_NE(surface->get(), destination.get());
  ASSERT_TRUE(surface->get());
  ASSERT_TRUE(destination.get());
}

TEST_F(SurfaceTest, MoveSelfAssignment)
{
  *surface = std::move(*surface);
  ASSERT_TRUE(surface->get());
}

TEST_F(SurfaceTest, MoveAssignment)
{
  cen::surface source{*surface};
  cen::surface destination = std::move(source);

  ASSERT_FALSE(source.get());
  ASSERT_TRUE(destination.get());
}

TEST_F(SurfaceTest, SaveAsBMP)
{
  ASSERT_TRUE(surface->save_as_bmp("surface_as_bmp.bmp"s));
}

TEST_F(SurfaceTest, SaveAsPNG)
{
  ASSERT_TRUE(surface->save_as_png("surface_as_png.png"s));
}

TEST_F(SurfaceTest, SaveAsJPG)
{
  ASSERT_TRUE(surface->save_as_jpg("surface_as_jpg.jpg"s, 25));
}

TEST_F(SurfaceTest, SetAlpha)
{
  const auto previous = surface->alpha();

  constexpr auto alpha = 0xCF;
  surface->set_alpha_mod(alpha);

  ASSERT_EQ(alpha, surface->alpha());

  surface->set_alpha_mod(previous);
}

TEST_F(SurfaceTest, SetColorMod)
{
  const auto previous = surface->color_mod();
  ASSERT_EQ(cen::colors::white, previous);

  constexpr auto color = cen::colors::hot_pink;
  surface->set_color_mod(color);

  ASSERT_EQ(color, surface->color_mod());

  surface->set_color_mod(previous);
}

TEST_F(SurfaceTest, SetBlendMode)
{
  const auto previous = surface->get_blend_mode();

  constexpr auto mode = cen::blend_mode::mod;
  surface->set_blend_mode(mode);

  ASSERT_EQ(mode, surface->get_blend_mode());

  surface->set_blend_mode(previous);
}

TEST_F(SurfaceTest, Width)
{
  ASSERT_EQ(200, surface->width());
}

TEST_F(SurfaceTest, Height)
{
  ASSERT_EQ(150, surface->height());
}

TEST_F(SurfaceTest, Size)
{
  const auto size = surface->size();
  ASSERT_EQ(200, size.width);
  ASSERT_EQ(150, size.height);
}

TEST_F(SurfaceTest, Pitch)
{
  ASSERT_EQ(4 * surface->width(), surface->pitch());
}

TEST_F(SurfaceTest, Clip)
{
  constexpr cen::irect rect{{48, 29}, {34, 89}};

  surface->get()->clip_rect = rect.get();
  ASSERT_EQ(rect, surface->clip());
}

TEST_F(SurfaceTest, GetPixelData)
{
  ASSERT_TRUE(surface->pixel_data());

  const auto& cSurface = *surface;
  ASSERT_TRUE(cSurface.pixel_data());
}

TEST_F(SurfaceTest, ConvertTo)
{
  cen::surface source{path};
  source.set_blend_mode(cen::blend_mode::blend);
  source.set_alpha_mod(0xAE);
  source.set_color_mod(cen::colors::red);

  const auto format = cen::pixel_format::rgba8888;
  const cen::surface converted = source.convert_to(format);

  ASSERT_EQ(format, converted.format_info().format());
  ASSERT_EQ(source.get_blend_mode(), converted.get_blend_mode());
  ASSERT_EQ(source.alpha(), converted.alpha());
  ASSERT_EQ(source.color_mod(), converted.color_mod());
}

TEST_F(SurfaceTest, Get)
{
  ASSERT_TRUE(surface->get());
}

TEST_F(SurfaceTest, StreamOperator)
{
  std::cout << *surface << '\n';
}
