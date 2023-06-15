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

#include "centurion/video/renderer.hpp"

#include <gtest/gtest.h>

#include <iostream>  // cout
#include <memory>    // unique_ptr

#include "centurion/common/math.hpp"
#include "centurion/fonts/font.hpp"
#include "centurion/video/color.hpp"
#include "centurion/video/window.hpp"

using namespace std::string_literals;

class RendererTest : public testing::Test {
 protected:
  static void SetUpTestSuite()
  {
    mFont = std::make_unique<cen::font>("resources/daniel.ttf", 12);
    mWindow = std::make_unique<cen::window>();
    mRenderer = std::make_unique<cen::renderer>(mWindow->make_renderer());
    mTexture = std::make_unique<cen::texture>(mRenderer->make_texture("resources/panda.png"));
  }

  static void TearDownTestSuite()
  {
    mTexture.reset();
    mRenderer.reset();
    mWindow.reset();
    mFont.reset();
  }

  inline static std::unique_ptr<cen::font> mFont;
  inline static std::unique_ptr<cen::window> mWindow;
  inline static std::unique_ptr<cen::renderer> mRenderer;
  inline static std::unique_ptr<cen::texture> mTexture;
};

TEST_F(RendererTest, RendererFlagsEnum)
{
  ASSERT_EQ(SDL_RENDERER_ACCELERATED, to_underlying(cen::renderer::accelerated));
  ASSERT_EQ(SDL_RENDERER_SOFTWARE, to_underlying(cen::renderer::software));
  ASSERT_EQ(SDL_RENDERER_TARGETTEXTURE, to_underlying(cen::renderer::target_textures));
  ASSERT_EQ(SDL_RENDERER_PRESENTVSYNC, to_underlying(cen::renderer::vsync));
}

TEST_F(RendererTest, PointerConstructor)
{
  SDL_Renderer* renderer {};
  ASSERT_THROW(cen::renderer {renderer}, cen::exception);
}

TEST_F(RendererTest, FlagsConstructor)
{
  // This throws because there is already a renderer associated with the window
  ASSERT_THROW(mWindow->make_renderer(), cen::sdl_error);
}

TEST_F(RendererTest, SetColor)
{
  mRenderer->set_color(cen::colors::magenta);
  ASSERT_EQ(cen::colors::magenta, mRenderer->get_color());
}

TEST_F(RendererTest, SetClip)
{
  constexpr cen::irect clip {{12, 34}, {56, 78}};

  mRenderer->set_clip(clip);
  ASSERT_TRUE(mRenderer->clip().has_value());
  ASSERT_EQ(clip, mRenderer->clip().value());

  mRenderer->reset_clip();
  ASSERT_FALSE(mRenderer->clip().has_value());
}

TEST_F(RendererTest, SetViewport)
{
  constexpr cen::irect viewport {{12, 34}, {56, 78}};

  mRenderer->set_viewport(viewport);
  ASSERT_EQ(viewport, mRenderer->viewport());
}

TEST_F(RendererTest, SetBlendMode)
{
  mRenderer->set_blend_mode(cen::blend_mode::blend);
  ASSERT_EQ(cen::blend_mode::blend, mRenderer->get_blend_mode());
}

TEST_F(RendererTest, SetScale)
{
  const auto xScale = 0.8f;
  const auto yScale = 0.6f;
  mRenderer->set_scale({xScale, yScale});

  const auto scale = mRenderer->scale();
  ASSERT_EQ(xScale, scale.x);
  ASSERT_EQ(yScale, scale.y);

  mRenderer->set_scale({1, 1});
}

TEST_F(RendererTest, SetLogicalSize)
{
  const auto old = mRenderer->logical_size();
  constexpr cen::iarea size {12, 34};

  mRenderer->set_logical_size(size);
  ASSERT_EQ(size.width, mRenderer->logical_size().width);
  ASSERT_EQ(size.height, mRenderer->logical_size().height);

  mRenderer->set_logical_size(old);
}

TEST_F(RendererTest, SetLogicalIntegerScaling)
{
  mRenderer->set_logical_integer_scaling(true);
  ASSERT_TRUE(mRenderer->using_integer_logical_scaling());

  mRenderer->set_logical_integer_scaling(false);
  ASSERT_FALSE(mRenderer->using_integer_logical_scaling());
}

TEST_F(RendererTest, GetTarget)
{
  ASSERT_EQ(nullptr, mRenderer->get_target().get());
}

TEST_F(RendererTest, LogicalSize)
{
  ASSERT_EQ(0, mRenderer->logical_size().width);
  ASSERT_EQ(0, mRenderer->logical_size().height);
}

TEST_F(RendererTest, Scale)
{
  ASSERT_EQ(1, mRenderer->scale().x);
  ASSERT_EQ(1, mRenderer->scale().y);
}

TEST_F(RendererTest, Clip)
{
  ASSERT_FALSE(mRenderer->clip().has_value());
}

TEST_F(RendererTest, Capture)
{
  mWindow->show();

  mRenderer->clear_with(cen::colors::pink);

  mRenderer->set_color(cen::colors::green);
  mRenderer->fill_rect(cen::irect {20, 20, 150, 100});

  mRenderer->set_color(cen::colors::black);
  mRenderer->draw_circle(cen::fpoint {300.0, 200.0}, 30);

  mRenderer->set_color(cen::colors::maroon);
  mRenderer->fill_circle(cen::fpoint {400, 300}, 35);

  mRenderer->present();

  const auto snapshot = mRenderer->capture(mWindow->format());
  ASSERT_TRUE(snapshot.save_as_bmp("snapshot.bmp"));

  {  // We take the opportunity to do some surface tests as well
    ASSERT_NO_THROW(cen::surface::from_bmp("snapshot.bmp"s));
    ASSERT_NO_THROW(cen::surface::with_format("resources/panda.png"s,
                                              mRenderer->get_blend_mode(),
                                              mWindow->format()));
  }

  mWindow->hide();
}

TEST_F(RendererTest, StreamOperator)
{
  std::cout << *mRenderer << '\n';
}

#if SDL_VERSION_ATLEAST(2, 0, 18)

TEST_F(RendererTest, ToLogical)
{
  mRenderer->set_logical_size({400, 300});

  const cen::ipoint real {42, 85};

  const auto logical = mRenderer->to_logical(real);
  ASSERT_NE(logical, cen::cast<cen::fpoint>(real));

  ASSERT_EQ(real, mRenderer->from_logical(logical));
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 18)