#include <gtest/gtest.h>

#include <iostream>  // clog
#include <memory>    // unique_ptr

#include "color.hpp"
#include "common.hpp"
#include "core/logging.hpp"
#include "font.hpp"
#include "math.hpp"
#include "render.hpp"
#include "window.hpp"

using namespace std::string_literals;

class RendererTest : public testing::Test {
 protected:
  static void SetUpTestSuite()
  {
    font = std::make_unique<cen::font>("resources/daniel.ttf", 12);
    window = std::make_unique<cen::Window>();

    renderer = std::make_unique<cen::Renderer>(*window);
    texture = std::make_unique<cen::texture>(*renderer, "resources/panda.png");
  }

  static void TearDownTestSuite()
  {
    texture.reset();
    renderer.reset();
    window.reset();
    font.reset();
  }

  inline static std::unique_ptr<cen::font> font;
  inline static std::unique_ptr<cen::Window> window;
  inline static std::unique_ptr<cen::Renderer> renderer;
  inline static std::unique_ptr<cen::texture> texture;
};

TEST_F(RendererTest, PointerConstructor)
{
  SDL_Renderer* renderer{};
  ASSERT_THROW(cen::Renderer{renderer}, cen::exception);
}

TEST_F(RendererTest, FlagsConstructor)
{
  // This throws because there is already a renderer associated with the window
  ASSERT_THROW(cen::Renderer{*window}, cen::sdl_error);
}

TEST_F(RendererTest, SetColor)
{
  renderer->SetColor(cen::colors::magenta);
  ASSERT_EQ(cen::colors::magenta, renderer->GetColor());
}

TEST_F(RendererTest, SetClip)
{
  constexpr cen::irect clip{{12, 34}, {56, 78}};

  renderer->SetClip(clip);
  ASSERT_TRUE(renderer->GetClip().has_value());
  ASSERT_EQ(clip, renderer->GetClip().value());

  renderer->SetClip(std::nullopt);
  ASSERT_FALSE(renderer->GetClip().has_value());
}

TEST_F(RendererTest, SetViewport)
{
  constexpr cen::irect viewport{{12, 34}, {56, 78}};

  renderer->SetViewport(viewport);
  ASSERT_EQ(viewport, renderer->GetViewport());
}

TEST_F(RendererTest, SetBlendMode)
{
  renderer->SetBlendMode(cen::BlendMode::Blend);
  ASSERT_EQ(cen::BlendMode::Blend, renderer->GetBlendMode());
}

TEST_F(RendererTest, SetScale)
{
  const auto xScale = 0.8f;
  const auto yScale = 0.6f;
  renderer->SetScale(xScale, yScale);

  const auto [x, y] = renderer->GetScale();
  ASSERT_EQ(xScale, x);
  ASSERT_EQ(yScale, y);

  renderer->SetScale(1, 1);
}

TEST_F(RendererTest, SetLogicalSize)
{
  const auto old = renderer->GetLogicalSize();
  constexpr cen::iarea size{12, 34};

  renderer->SetLogicalSize(size);
  ASSERT_EQ(size.width, renderer->GetLogicalSize().width);
  ASSERT_EQ(size.height, renderer->GetLogicalSize().height);

  renderer->SetLogicalSize(old);
}

TEST_F(RendererTest, SetLogicalIntegerScaling)
{
  renderer->SetLogicalIntegerScaling(true);
  ASSERT_TRUE(renderer->IsUsingIntegerLogicalScaling());

  renderer->SetLogicalIntegerScaling(false);
  ASSERT_FALSE(renderer->IsUsingIntegerLogicalScaling());
}

TEST_F(RendererTest, GetRenderTarget)
{
  ASSERT_EQ(nullptr, renderer->GetRenderTarget().get());
}

TEST_F(RendererTest, GetLogicalSize)
{
  ASSERT_EQ(0, renderer->GetLogicalSize().width);
  ASSERT_EQ(0, renderer->GetLogicalSize().height);
}

TEST_F(RendererTest, GetScale)
{
  ASSERT_EQ(1, renderer->GetScale().first);
  ASSERT_EQ(1, renderer->GetScale().second);
}

TEST_F(RendererTest, GetClip)
{
  ASSERT_FALSE(renderer->GetClip().has_value());
}

TEST_F(RendererTest, Capture)
{
  window->Show();

  renderer->ClearWith(cen::colors::pink);

  renderer->SetColor(cen::colors::green);
  renderer->FillRect(cen::irect{20, 20, 150, 100});

  renderer->SetColor(cen::colors::black);
  renderer->DrawCircle(cen::fpoint{300.0, 200.0}, 30);

  renderer->SetColor(cen::colors::maroon);
  renderer->FillCircle({400, 300}, 35);

  renderer->Present();

  const auto snapshot = renderer->Capture(window->GetPixelFormat());
  ASSERT_TRUE(snapshot.SaveAsBMP("snapshot.bmp"));

  {  // We take the opportunity to do some surface tests as well
    ASSERT_NO_THROW(cen::Surface::FromBMP("snapshot.bmp"s));
    ASSERT_NO_THROW(cen::Surface::WithFormat("resources/panda.png"s,
                                             renderer->GetBlendMode(),
                                             window->GetPixelFormat()));
  }

  window->Hide();
}

TEST_F(RendererTest, ToString)
{
  cen::log_info_raw(cen::ToString(*renderer));
}

TEST_F(RendererTest, StreamOperator)
{
  std::clog << *renderer << '\n';
}

TEST_F(RendererTest, RendererFlagsEnum)
{
  ASSERT_EQ(SDL_RENDERER_ACCELERATED,
            static_cast<SDL_RendererFlags>(cen::Renderer::Accelerated));
  ASSERT_EQ(SDL_RENDERER_SOFTWARE, static_cast<SDL_RendererFlags>(cen::Renderer::Software));
  ASSERT_EQ(SDL_RENDERER_TARGETTEXTURE,
            static_cast<SDL_RendererFlags>(cen::Renderer::TargetTextures));
  ASSERT_EQ(SDL_RENDERER_PRESENTVSYNC, static_cast<SDL_RendererFlags>(cen::Renderer::VSync));
}