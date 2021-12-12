#include "video/renderer.hpp"

#include <gtest/gtest.h>

#include <iostream>  // clog
#include <memory>    // unique_ptr

#include "core/exception.hpp"
#include "core/logging.hpp"
#include "math/rect.hpp"
#include "video/colors.hpp"
#include "video/font.hpp"
#include "video/graphics_drivers.hpp"
#include "video/window.hpp"

using namespace std::string_literals;

class RendererTest : public testing::Test
{
 protected:
  static void SetUpTestSuite()
  {
    m_font = std::make_unique<cen::font>("resources/daniel.ttf", 12);
    m_window = std::make_unique<cen::window>();

    m_renderer = std::make_unique<cen::renderer>(*m_window);
    m_texture = std::make_unique<cen::texture>(*m_renderer, "resources/panda.png");
  }

  static void TearDownTestSuite()
  {
    m_texture.reset();
    m_renderer.reset();
    m_window.reset();
    m_font.reset();
  }

  inline static std::unique_ptr<cen::font> m_font;
  inline static std::unique_ptr<cen::window> m_window;
  inline static std::unique_ptr<cen::renderer> m_renderer;
  inline static std::unique_ptr<cen::texture> m_texture;
};

TEST_F(RendererTest, PointerConstructor)
{
  SDL_Renderer* renderer{};
  ASSERT_THROW(cen::renderer{renderer}, cen::Error);
}

TEST_F(RendererTest, FlagsConstructor)
{
  // This throws because there is already a renderer associated with the window
  ASSERT_THROW(cen::renderer{*m_window}, cen::SDLError);
}

TEST_F(RendererTest, SetTranslationViewport)
{
  const auto old = m_renderer->translation_viewport();

  constexpr cen::frect viewport{{12, 34}, {56, 78}};

  m_renderer->set_translation_viewport(viewport);
  ASSERT_EQ(viewport, m_renderer->translation_viewport());

  m_renderer->set_translation_viewport(old);
}

TEST_F(RendererTest, TranslationViewport)
{
  const auto viewport = m_renderer->translation_viewport();
  ASSERT_EQ(0, viewport.x());
  ASSERT_EQ(0, viewport.y());
  ASSERT_EQ(0, viewport.width());
  ASSERT_EQ(0, viewport.height());
}

TEST_F(RendererTest, TranslatedDrawRect)
{
  ASSERT_NO_THROW(m_renderer->draw_rect_t<int>({{12, 34}, {56, 78}}));
  ASSERT_NO_THROW(m_renderer->draw_rect_t<float>({{12, 34}, {56, 78}}));
}

TEST_F(RendererTest, TranslatedFillRect)
{
  ASSERT_NO_THROW(m_renderer->fill_rect_t<int>({{12, 34}, {56, 78}}));
  ASSERT_NO_THROW(m_renderer->fill_rect_t<float>({{12, 34}, {56, 78}}));
}

TEST_F(RendererTest, TranslatedRenderWithPoint)
{
  {
    const cen::ipoint pos{12, 34};
    ASSERT_NO_THROW(m_renderer->render_t(*m_texture, pos));
  }

  {
    const cen::fpoint pos{56, 78};
    ASSERT_NO_THROW(m_renderer->render_t(*m_texture, pos));
  }
}

TEST_F(RendererTest, TranslatedRenderWithRectangle)
{
  {
    const cen::irect rect{{12, 34}, {56, 78}};
    ASSERT_NO_THROW(m_renderer->render_t(*m_texture, rect));
  }

  {
    const cen::frect rect{{21, 43}, {65, 87}};
    ASSERT_NO_THROW(m_renderer->render_t(*m_texture, rect));
  }
}

TEST_F(RendererTest, TranslatedRenderWithSourceDestination)
{
  {
    const cen::irect src{{12, 34}, {56, 78}};
    const cen::irect dst{{21, 43}, {65, 87}};

    ASSERT_NO_THROW(m_renderer->render_t(*m_texture, src, dst));
  }

  {
    const cen::irect src{{12, 34}, {56, 78}};
    const cen::frect dst{{21, 43}, {65, 87}};

    ASSERT_NO_THROW(m_renderer->render_t(*m_texture, src, dst));
  }
}

TEST_F(RendererTest, TranslatedRenderWithSourceDestinationAngle)
{
  {
    const cen::irect src{{12, 34}, {56, 78}};
    const cen::irect dst{{21, 43}, {65, 87}};
    const auto angle = 12.3;

    ASSERT_NO_THROW(m_renderer->render_t(*m_texture, src, dst, angle));
  }

  {
    const cen::irect src{{12, 34}, {56, 78}};
    const cen::frect dst{{21, 43}, {65, 87}};
    const auto angle = 12.3;

    ASSERT_NO_THROW(m_renderer->render_t(*m_texture, src, dst, angle));
  }
}

TEST_F(RendererTest, TranslatedRenderWithSourceDestinationAngleCenter)
{
  {
    const cen::irect src{{12, 34}, {56, 78}};
    const cen::irect dst{{21, 43}, {65, 87}};
    const auto angle = 12.3;
    const cen::ipoint center{15, 12};

    ASSERT_NO_THROW(m_renderer->render_t(*m_texture, src, dst, angle, center));
  }

  {
    const cen::irect src{{12, 34}, {56, 78}};
    const cen::frect dst{{21, 43}, {65, 87}};
    const auto angle = 12.3;
    const cen::fpoint center{15, 12};

    ASSERT_NO_THROW(m_renderer->render_t(*m_texture, src, dst, angle, center));
  }
}

TEST_F(RendererTest, TranslatedRenderWithSourceDestinationAngleCenterFlip)
{
  {
    const cen::irect src{{12, 34}, {56, 78}};
    const cen::irect dst{{21, 43}, {65, 87}};
    const auto angle = 12.3;
    const cen::ipoint center{15, 12};
    const auto flip = SDL_FLIP_HORIZONTAL;

    ASSERT_NO_THROW(m_renderer->render_t(*m_texture, src, dst, angle, center, flip));
  }

  {
    const cen::irect src{{12, 34}, {56, 78}};
    const cen::frect dst{{21, 43}, {65, 87}};
    const auto angle = 12.3;
    const cen::fpoint center{15, 12};
    const auto flip = SDL_FLIP_VERTICAL;

    ASSERT_NO_THROW(m_renderer->render_t(*m_texture, src, dst, angle, center, flip));
  }
}

TEST_F(RendererTest, AddFont)
{
  const auto id = 7;
  const auto path = "resources/daniel.ttf";

  m_renderer->add_font(id, cen::font{path, 12});
  ASSERT_NO_THROW(m_renderer->add_font(id, cen::font{path, 12}));

  ASSERT_NO_THROW(m_renderer->get_font(id));
  ASSERT_TRUE(m_renderer->has_font(id));

  m_renderer->remove_font(id);
}

TEST_F(RendererTest, EmplaceFont)
{
  const auto id = 7;
  const auto path = "resources/daniel.ttf";

  m_renderer->emplace_font(id, path, 12);
  ASSERT_NO_THROW(m_renderer->emplace_font(id, path, 12));

  ASSERT_NO_THROW(m_renderer->get_font(id));
  ASSERT_TRUE(m_renderer->has_font(id));

  m_renderer->remove_font(id);
}

TEST_F(RendererTest, RemoveFont)
{
  ASSERT_NO_THROW(m_renderer->remove_font(0));

  m_renderer->emplace_font(12, "resources/daniel.ttf", 12);
  ASSERT_TRUE(m_renderer->has_font(12));

  m_renderer->remove_font(12);
  ASSERT_FALSE(m_renderer->has_font(12));
}

TEST_F(RendererTest, SetColor)
{
  constexpr auto color = cen::colors::magenta;
  m_renderer->set_color(color);

  ASSERT_EQ(color.red(), m_renderer->get_color().red());
  ASSERT_EQ(color.green(), m_renderer->get_color().green());
  ASSERT_EQ(color.blue(), m_renderer->get_color().blue());
  ASSERT_EQ(color.alpha(), m_renderer->get_color().alpha());
}

TEST_F(RendererTest, SetClip)
{
  constexpr cen::irect clip{{12, 34}, {56, 78}};

  m_renderer->set_clip(clip);
  ASSERT_TRUE(m_renderer->clip().has_value());
  ASSERT_EQ(clip, m_renderer->clip().value());

  m_renderer->set_clip(std::nullopt);
  ASSERT_FALSE(m_renderer->clip().has_value());
}

TEST_F(RendererTest, SetViewport)
{
  constexpr cen::irect viewport{{12, 34}, {56, 78}};

  m_renderer->set_viewport(viewport);
  ASSERT_EQ(viewport, m_renderer->viewport());
}

TEST_F(RendererTest, SetBlendMode)
{
  m_renderer->set_blend_mode(cen::blend_mode::blend);
  ASSERT_EQ(cen::blend_mode::blend, m_renderer->get_blend_mode());
}

TEST_F(RendererTest, SetScale)
{
  const auto xScale = 0.8f;
  const auto yScale = 0.6f;
  m_renderer->set_scale(xScale, yScale);

  ASSERT_EQ(xScale, m_renderer->x_scale());
  ASSERT_EQ(yScale, m_renderer->y_scale());

  m_renderer->set_scale(1, 1);
}

TEST_F(RendererTest, SetLogicalSize)
{
  const auto old = m_renderer->logical_size();
  constexpr cen::iarea size{12, 34};

  m_renderer->set_logical_size(size);
  ASSERT_EQ(size.width, m_renderer->logical_width());
  ASSERT_EQ(size.height, m_renderer->logical_height());

  m_renderer->set_logical_size(old);
}

TEST_F(RendererTest, SetLogicalIntegerScaling)
{
  m_renderer->set_logical_integer_scaling(true);
  ASSERT_TRUE(m_renderer->is_using_integer_logical_scaling());

  m_renderer->set_logical_integer_scaling(false);
  ASSERT_FALSE(m_renderer->is_using_integer_logical_scaling());
}

TEST_F(RendererTest, GetRenderTarget)
{
  ASSERT_EQ(nullptr, m_renderer->get_render_target().get());
}

TEST_F(RendererTest, LogicalWidth)
{
  ASSERT_EQ(0, m_renderer->logical_width());
}

TEST_F(RendererTest, LogicalHeight)
{
  ASSERT_EQ(0, m_renderer->logical_height());
}

TEST_F(RendererTest, LogicalSize)
{
  ASSERT_EQ(0, m_renderer->logical_size().width);
  ASSERT_EQ(0, m_renderer->logical_size().height);
}

TEST_F(RendererTest, XScale)
{
  ASSERT_EQ(1, m_renderer->x_scale());
}

TEST_F(RendererTest, YScale)
{
  ASSERT_EQ(1, m_renderer->y_scale());
}

TEST_F(RendererTest, Scale)
{
  ASSERT_EQ(1, m_renderer->scale().first);
  ASSERT_EQ(1, m_renderer->scale().second);
}

TEST_F(RendererTest, Clip)
{
  ASSERT_FALSE(m_renderer->clip().has_value());
}

TEST_F(RendererTest, Capture)
{
  m_window->show();

  m_renderer->clear_with(cen::colors::pink);

  m_renderer->set_color(cen::colors::green);
  m_renderer->fill_rect(cen::rect(20, 20, 150, 100));

  m_renderer->set_color(cen::colors::black);
  m_renderer->draw_circle(cen::point(300.0, 200.0), 30);

  m_renderer->set_color(cen::colors::maroon);
  m_renderer->fill_circle({400, 300}, 35);

  m_renderer->present();

  const auto snapshot = m_renderer->capture(m_window->get_pixel_format());
  ASSERT_TRUE(snapshot.save_as_bmp("snapshot.bmp"));

  {  // We take the opportunity to do some surface tests as well
    ASSERT_NO_THROW(cen::surface::from_bmp("snapshot.bmp"s));
    ASSERT_NO_THROW(cen::surface::with_format("resources/panda.png"s,
                                              m_renderer->get_blend_mode(),
                                              m_window->get_pixel_format()));
  }

  m_window->hide();
}

TEST_F(RendererTest, ToString)
{
  cen::log_info_raw(cen::to_string(*m_renderer));
}

TEST_F(RendererTest, StreamOperator)
{
  std::clog << *m_renderer << '\n';
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