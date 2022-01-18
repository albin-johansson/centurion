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

    renderer = std::make_unique<cen::renderer>(window->create_renderer());
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
  inline static std::unique_ptr<cen::renderer> renderer;
  inline static std::unique_ptr<cen::texture> texture;
};

TEST_F(RendererTest, PointerConstructor)
{
  SDL_Renderer* renderer{};
  ASSERT_THROW(cen::renderer{renderer}, cen::exception);
}

TEST_F(RendererTest, FlagsConstructor)
{
  // This throws because there is already a renderer associated with the window
  ASSERT_THROW(window->create_renderer(), cen::sdl_error);
}

TEST_F(RendererTest, SetColor)
{
  renderer->set_color(cen::colors::magenta);
  ASSERT_EQ(cen::colors::magenta, renderer->get_color());
}

TEST_F(RendererTest, SetClip)
{
  constexpr cen::irect clip{{12, 34}, {56, 78}};

  renderer->set_clip(clip);
  ASSERT_TRUE(renderer->clip().has_value());
  ASSERT_EQ(clip, renderer->clip().value());

  renderer->reset_clip();
  ASSERT_FALSE(renderer->clip().has_value());
}

TEST_F(RendererTest, SetViewport)
{
  constexpr cen::irect viewport{{12, 34}, {56, 78}};

  renderer->set_viewport(viewport);
  ASSERT_EQ(viewport, renderer->viewport());
}

TEST_F(RendererTest, SetBlendMode)
{
  renderer->set_blend_mode(cen::BlendMode::Blend);
  ASSERT_EQ(cen::BlendMode::Blend, renderer->get_blend_mode());
}

TEST_F(RendererTest, SetScale)
{
  const auto xScale = 0.8f;
  const auto yScale = 0.6f;
  renderer->set_scale({xScale, yScale});

  const auto scale = renderer->scale();
  ASSERT_EQ(xScale, scale.x);
  ASSERT_EQ(yScale, scale.y);

  renderer->set_scale({1, 1});
}

TEST_F(RendererTest, SetLogicalSize)
{
  const auto old = renderer->logical_size();
  constexpr cen::iarea size{12, 34};

  renderer->set_logical_size(size);
  ASSERT_EQ(size.width, renderer->logical_size().width);
  ASSERT_EQ(size.height, renderer->logical_size().height);

  renderer->set_logical_size(old);
}

TEST_F(RendererTest, SetLogicalIntegerScaling)
{
  renderer->set_logical_integer_scaling(true);
  ASSERT_TRUE(renderer->using_integer_logical_scaling());

  renderer->set_logical_integer_scaling(false);
  ASSERT_FALSE(renderer->using_integer_logical_scaling());
}

TEST_F(RendererTest, GetTarget)
{
  ASSERT_EQ(nullptr, renderer->get_target().get());
}

TEST_F(RendererTest, LogicalSize)
{
  ASSERT_EQ(0, renderer->logical_size().width);
  ASSERT_EQ(0, renderer->logical_size().height);
}

TEST_F(RendererTest, Scale)
{
  ASSERT_EQ(1, renderer->scale().x);
  ASSERT_EQ(1, renderer->scale().y);
}

TEST_F(RendererTest, Clip)
{
  ASSERT_FALSE(renderer->clip().has_value());
}

TEST_F(RendererTest, Capture)
{
  window->Show();

  renderer->clear_with(cen::colors::pink);

  renderer->set_color(cen::colors::green);
  renderer->fill_rect(cen::irect{20, 20, 150, 100});

  renderer->set_color(cen::colors::black);
  renderer->draw_circle(cen::fpoint{300.0, 200.0}, 30);

  renderer->set_color(cen::colors::maroon);
  renderer->fill_circle(cen::fpoint{400, 300}, 35);

  renderer->present();

  const auto snapshot = renderer->capture(window->GetPixelFormat());
  ASSERT_TRUE(snapshot.save_as_bmp("snapshot.bmp"));

  {  // We take the opportunity to do some surface tests as well
    ASSERT_NO_THROW(cen::surface::from_bmp("snapshot.bmp"s));
    ASSERT_NO_THROW(cen::surface::with_format("resources/panda.png"s,
                                              renderer->get_blend_mode(),
                                              window->GetPixelFormat()));
  }

  window->Hide();
}

TEST_F(RendererTest, ToString)
{
  cen::log_info_raw(cen::to_string(*renderer));
}

TEST_F(RendererTest, StreamOperator)
{
  std::clog << *renderer << '\n';
}

TEST_F(RendererTest, RendererFlagsEnum)
{
  ASSERT_EQ(SDL_RENDERER_ACCELERATED,
            static_cast<SDL_RendererFlags>(cen::renderer::accelerated));
  ASSERT_EQ(SDL_RENDERER_SOFTWARE, static_cast<SDL_RendererFlags>(cen::renderer::software));
  ASSERT_EQ(SDL_RENDERER_TARGETTEXTURE,
            static_cast<SDL_RendererFlags>(cen::renderer::target_textures));
  ASSERT_EQ(SDL_RENDERER_PRESENTVSYNC, static_cast<SDL_RendererFlags>(cen::renderer::vsync));
}