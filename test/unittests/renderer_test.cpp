#include "renderer.hpp"

#include <catch.hpp>

#include "centurion_as_ctn.hpp"
#include "centurion_exception.hpp"
#include "colors.hpp"
#include "font.hpp"
#include "log.hpp"
#include "rect.hpp"
#include "window.hpp"

namespace {

template <typename Lambda>
inline void test(Lambda&& lambda)
{
  ctn::window window;
  ctn::renderer renderer{window};
  lambda(window, renderer);
}

template <typename Lambda>
inline void texture_test(Lambda&& lambda)
{
  ctn::window window;
  ctn::renderer renderer{window};
  ctn::texture texture{renderer, "resources/panda.png"};
  lambda(renderer, texture);
}

template <typename Lambda>
inline void font_test(Lambda&& lambda)
{
  ctn::window window;
  ctn::renderer renderer{window};
  ctn::font font{"resources/daniel.ttf", 12};
  lambda(renderer, font);
}

}  // namespace

TEST_CASE("Constructor: (gsl::owner<SDL_Renderer*>)", "[renderer]")
{
  //  CHECK_THROWS_AS(ctn::renderer{nullptr}, ctn::centurion_exception);

  ctn::window window;
  auto* ren = SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_SOFTWARE);
  CHECK_NOTHROW(ctn::renderer{ren});
}

TEST_CASE("Constructor: (const Window&, SDL_RendererFlags)", "[renderer]")
{
  ctn::window window;
  CHECK_NOTHROW(ctn::renderer{window});
}

TEST_CASE("Renderer move constructor", "[renderer]")
{
  const ctn::window window;

  ctn::renderer renderer{window};
  ctn::renderer other{std::move(renderer)};

  CHECK(other.get());
}

TEST_CASE("operator=(Renderer&&)", "[renderer]")
{
  SECTION("Self-assignment")
  {
    const ctn::window window;
    ctn::renderer renderer{window};

    renderer = std::move(renderer);
    CHECK(renderer.get());  // NOLINT
  }

  SECTION("Normal usage")
  {
    const ctn::window firstWindow;
    const ctn::window secondWindow;
    ctn::renderer renderer{firstWindow};
    ctn::renderer other{secondWindow};

    other = std::move(renderer);

    CHECK(other.get());
  }
}

TEST_CASE("Renderer smart pointer factory methods", "[renderer]")
{
  SECTION("Unique")
  {
    //    CHECK_THROWS_AS(ctn::renderer::unique(nullptr),
    //    ctn::centurion_exception);

    ctn::window window;
    SDL_Renderer* ren =
        SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_SOFTWARE);
    CHECK_NOTHROW(ctn::renderer::unique(ren));
  }

  SECTION("Shared")
  {
    //    CHECK_THROWS_AS(ctn::renderer::shared(nullptr),
    //    ctn::centurion_exception);

    ctn::window window;
    SDL_Renderer* ren =
        SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_SOFTWARE);
    CHECK_NOTHROW(ctn::renderer::shared(ren));
  }
}

TEST_CASE("clear", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    CHECK_NOTHROW(renderer.clear());
  });
}

TEST_CASE("clear_with", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    const auto selectedColor = ctn::colors::pink;
    renderer.set_color(selectedColor);

    CHECK_NOTHROW(renderer.clear_with(ctn::colors::medium_aqua_marine));
    CHECK(renderer.get_color() == selectedColor);
  });
}

TEST_CASE("present", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    CHECK_NOTHROW(renderer.present());
  });
}

TEST_CASE("add_font", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    SECTION("Bad arguments")
    {
      CHECK_NOTHROW(renderer.add_font(""_hs, nullptr));
    }

    SECTION("Normal arguments")
    {
      auto font = ctn::font::shared("resources/daniel.ttf", 12);
      const entt::hashed_string fontName{font->family_name()};

      renderer.add_font(fontName, font);
      CHECK(renderer.has_font(fontName));
      CHECK_NOTHROW(renderer.add_font(fontName, font));
      CHECK(renderer.has_font(fontName));
    }
  });
}

TEST_CASE("remove_font", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    const auto name = "daniel"_hs;
    const auto font = ctn::font::shared("resources/daniel.ttf", 12);

    CHECK_NOTHROW(renderer.remove_font(""_hs));

    renderer.add_font(name, font);
    CHECK(renderer.has_font(name));

    renderer.remove_font(name);
    CHECK(!renderer.has_font(name));
  });
}

TEST_CASE("draw_rect", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    const ctn::rect_i rect_i{{1, 2}, {3, 4}};
    const ctn::rect_f rect_f{{11.3f, 34.2f}, {54.2f, 91.3f}};

    CHECK_NOTHROW(renderer.draw_rect(rect_i));
    CHECK_NOTHROW(renderer.draw_rect(rect_f));
  });
}

TEST_CASE("fill_rect", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    const ctn::rect_i rect_i{{14, 23}, {331, 487}};
    const ctn::rect_f rect_f{{11.3f, 34.2f}, {54.2f, 91.3f}};

    CHECK_NOTHROW(renderer.fill_rect(rect_i));
    CHECK_NOTHROW(renderer.fill_rect(rect_f));
  });
}

TEST_CASE("draw_rect_t", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    const ctn::rect_i rect_i{{14, 23}, {331, 487}};
    const ctn::rect_f rect_f{{11.3f, 34.2f}, {54.2f, 91.3f}};

    CHECK_NOTHROW(renderer.draw_rect_t(rect_i));
    CHECK_NOTHROW(renderer.draw_rect_t(rect_f));
  });
}

TEST_CASE("fill_rect_t", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    const ctn::rect_i rect_i{{14, 23}, {331, 487}};
    const ctn::rect_f rect_f{{11.3f, 34.2f}, {54.2f, 91.3f}};

    CHECK_NOTHROW(renderer.fill_rect_t(rect_i));
    CHECK_NOTHROW(renderer.fill_rect_t(rect_f));
  });
}

TEST_CASE("draw_line", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    CHECK_NOTHROW(renderer.draw_line(ctn::point_i{4, 5}, ctn::point_i{12, 94}));
    CHECK_NOTHROW(renderer.draw_line(ctn::point_f{6.2f, 8.3f},
                                     ctn::point_f{21.6f, 17.8f}));
  });
}

TEST_CASE("renderer::draw_lines", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    const std::vector<ctn::point_i> points_i{{4, 5}, {50, 2}, {-10, 7}};
    const std::vector<ctn::point_f> points_f{
        {8.3f, 3.4f}, {54.4f, 86.3f}, {-10.9f, 67.2f}};

    CHECK_NOTHROW(renderer.draw_lines(points_i));
    CHECK_NOTHROW(renderer.draw_lines(points_f));
  });
}

TEST_CASE("render(Texture, Point<T>)", "[renderer]")
{
  texture_test([](ctn::renderer& renderer, const ctn::texture& texture) {
    const ctn::point_i position_i{3, 57};
    const ctn::point_f position_f{26.4f, 68.2f};

    CHECK_NOTHROW(renderer.render(texture, position_i));
    CHECK_NOTHROW(renderer.render(texture, position_f));
  });
}

TEST_CASE("render(Texture, Rect<T>)", "[renderer]")
{
  texture_test([](ctn::renderer& renderer, const ctn::texture& texture) {
    const ctn::rect_i rect_i{{12, 57}, {175, 218}};
    const ctn::rect_f rect_f{{23.7f, 36.3f}, {317.3f, 348.3f}};

    CHECK_NOTHROW(renderer.render(texture, rect_i));
    CHECK_NOTHROW(renderer.render(texture, rect_f));
  });
}

TEST_CASE("render(Texture, IRect, Rect<T>)", "[renderer]")
{
  texture_test([](ctn::renderer& renderer, const ctn::texture& texture) {
    const ctn::rect_i src{{10, 15}, {20, 20}};

    const ctn::rect_i dst_i{{35, 92}, {15, 23}};
    const ctn::rect_f dst_f{{77.9f, 45.6f}, {512.1f, 375.2f}};

    CHECK_NOTHROW(renderer.render(texture, src, dst_i));
    CHECK_NOTHROW(renderer.render(texture, src, dst_f));
  });
}

TEST_CASE("render(Texture, IRect, Rect<T>, double)", "[renderer]")
{
  texture_test([](ctn::renderer& renderer, const ctn::texture& texture) {
    const ctn::rect_i src{{10, 15}, {20, 20}};
    const auto angle = 182;

    const ctn::rect_i dst_i{{35, 92}, {15, 23}};
    const ctn::rect_f dst_f{{21.4f, 47.3f}, {338.3f, 177.3f}};

    CHECK_NOTHROW(renderer.render(texture, src, dst_i, angle));
    CHECK_NOTHROW(renderer.render(texture, src, dst_f, angle));
  });
}

TEST_CASE("render(Texture, IRect, Rect<T>, double, Point<T>)", "[renderer]")
{
  texture_test([](ctn::renderer& renderer, const ctn::texture& texture) {
    const ctn::rect_i src{{16, 11}, {37, 77}};
    const auto angle = 359;

    const ctn::rect_i dst_i{{22, 76}, {245, 112}};
    const ctn::rect_f dst_f{{54.5f, 25.6f}, {136.5f, 387.8f}};

    const ctn::point_i center_i{44, 12};
    const ctn::point_f center_f{12.3f, 45.2f};

    CHECK_NOTHROW(renderer.render(texture, src, dst_i, angle, center_i));
    CHECK_NOTHROW(renderer.render(texture, src, dst_f, angle, center_f));
  });
}

TEST_CASE("render(Texture, IRect, Rect<T>, SDL_RendererFlip)", "[renderer]")
{
  texture_test([](ctn::renderer& renderer, const ctn::texture& texture) {
    CHECK_NOTHROW(renderer.render(texture,
                                  ctn::rect_i{{10, 15}, {20, 20}},
                                  ctn::rect_i{{35, 92}, {15, 23}},
                                  SDL_FLIP_HORIZONTAL));
  });
}

TEST_CASE("render(Texture, IRect, Rect<T>, double, Point<T>, SDL_RendererFlip)",
          "[renderer]")
{
  texture_test([](ctn::renderer& renderer, const ctn::texture& texture) {
    CHECK_NOTHROW(renderer.render(texture,
                                  {{10, 15}, {20, 20}},
                                  {{35, 92}, {15, 23}},
                                  -5,
                                  ctn::point_i{5, 5},
                                  SDL_FLIP_HORIZONTAL));
  });
}

TEST_CASE("render_t(Texture, Point<T>)", "[renderer]")
{
  texture_test([](ctn::renderer& renderer, const ctn::texture& texture) {
    const ctn::point_i pos_i{-5, 66};
    const ctn::point_f pos_f{3.8f, 43.3f};

    CHECK_NOTHROW(renderer.render_t(texture, pos_i));
    CHECK_NOTHROW(renderer.render_t(texture, pos_f));
  });
}

TEST_CASE("render_t(Texture, Rect<T>)", "[renderer]")
{
  texture_test([](ctn::renderer& renderer, const ctn::texture& texture) {
    const ctn::rect_i rect_i{{12, 7}, {115, 876}};
    const ctn::rect_f rect_f{{7.4f, 2.3f}, {175.3f, 412.8f}};

    CHECK_NOTHROW(renderer.render_t(texture, rect_i));
    CHECK_NOTHROW(renderer.render_t(texture, rect_f));
  });
}

TEST_CASE("render_t(Texture, IRect, Rect<T>)", "[renderer]")
{
  texture_test([](ctn::renderer& renderer, const ctn::texture& texture) {
    const ctn::rect_i src{{123, 444}, {467, 221}};

    const ctn::rect_i dst_i{{5, 34}, {123, 321}};
    const ctn::rect_f dst_f{{73.1f, 22.3f}, {116.4f, 443.4f}};

    CHECK_NOTHROW(renderer.render_t(texture, src, dst_i));
    CHECK_NOTHROW(renderer.render_t(texture, src, dst_f));
  });
}

TEST_CASE("render_t(Texture, IRect, Rect<T>, double)", "[renderer]")
{
  texture_test([](ctn::renderer& renderer, const ctn::texture& texture) {
    const ctn::rect_i src{{10, 15}, {20, 20}};
    const auto angle = 17;

    const ctn::rect_i dst_i{{35, 92}, {15, 23}};
    const ctn::rect_f dst_f{{67.1f, 43.3f}, {77.4f, 23.4f}};

    CHECK_NOTHROW(renderer.render_t(texture, src, dst_i, angle));
    CHECK_NOTHROW(renderer.render_t(texture, src, dst_f, angle));
  });
}

TEST_CASE("render_t(Texture, IRect, Rect<T>, double, Point<T>)", "[renderer]")
{
  texture_test([](ctn::renderer& renderer, const ctn::texture& texture) {
    const ctn::rect_i src{{10, 15}, {20, 20}};
    const auto angle = 23;

    const ctn::rect_i dst_i{{35, 92}, {15, 23}};
    const ctn::rect_f dst_f{{14.5f, 23.6f}, {126.5f, 327.8f}};

    const ctn::point_i center_i{5, 9};
    const ctn::point_f center_f{16.3f, 34.7f};

    CHECK_NOTHROW(renderer.render_t(texture, src, dst_i, angle, center_i));
    CHECK_NOTHROW(renderer.render_t(texture, src, dst_f, angle, center_f));
  });
}

TEST_CASE("render_t(Texture, IRect, Rect<T>, SDL_RendererFlip)", "[renderer]")
{
  texture_test([](ctn::renderer& renderer, const ctn::texture& texture) {
    const ctn::rect_i src{{10, 15}, {20, 20}};
    const SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;

    const ctn::rect_i dst_i{{35, 92}, {15, 23}};
    const ctn::rect_f dst_f{{382.3f, 12.4f}, {35.6f, 238.9f}};

    CHECK_NOTHROW(renderer.render_t(texture, src, dst_i, flip));
    CHECK_NOTHROW(renderer.render_t(texture, src, dst_f, flip));
  });
}

TEST_CASE(
    "render_t(Texture, IRect, Rect<T>, double, Point<T>, SDL_RendererFlip)",
    "[renderer]")
{
  texture_test([](ctn::renderer& renderer, const ctn::texture& texture) {
    const ctn::rect_i src{{10, 15}, {20, 20}};
    const SDL_RendererFlip flip = SDL_FLIP_VERTICAL;
    const auto angle = 126;

    const ctn::rect_i dst_i{{35, 92}, {15, 23}};
    const ctn::rect_f dst_f{{382.3f, 12.4f}, {35.6f, 238.9f}};

    const ctn::point_i center_i{5, 5};
    const ctn::point_f center_f{74.3f, 930.3f};

    CHECK_NOTHROW(
        renderer.render_t(texture, src, dst_i, angle, center_i, flip));

    CHECK_NOTHROW(
        renderer.render_t(texture, src, dst_f, angle, center_f, flip));
  });
}

TEST_CASE("set_color", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    const auto& color = ctn::colors::pale_violet_red;

    renderer.set_color(color);
    CHECK(color == renderer.get_color());
  });
}

TEST_CASE("set_viewport", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    const ctn::rect_i viewport{{50, 33}, {768, 453}};

    renderer.set_viewport(viewport);
    CHECK(viewport == renderer.viewport());
  });
}

TEST_CASE("set_logical_size", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    const ctn::area_i size{842, 253};

    renderer.set_logical_size(size);

    CHECK(renderer.logical_width() == size.width);
    CHECK(renderer.logical_height() == size.height);
  });
}

TEST_CASE("set_scale", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    const auto xScale = 0.8f;
    const auto yScale = 0.4f;
    renderer.set_scale(xScale, yScale);

    CHECK(renderer.x_scale() == xScale);
    CHECK(renderer.y_scale() == yScale);
  });
}

TEST_CASE("x_scale", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    CHECK(renderer.x_scale() == 1);
  });
}

TEST_CASE("y_scale", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    CHECK(renderer.y_scale() == 1);
  });
}

TEST_CASE("logical_width", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    CHECK(renderer.logical_width() == 0);
  });
}

TEST_CASE("logical_height", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    CHECK(renderer.logical_height() == 0);
  });
}

TEST_CASE("info", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    const auto optInfo = renderer.info();
    REQUIRE(optInfo);

    const SDL_RendererInfo info = *optInfo;

    SDL_RendererInfo sdlInfo;
    SDL_GetRendererInfo(renderer.get(), &sdlInfo);

    CHECK_THAT(info.name, Catch::Equals(sdlInfo.name));
    CHECK(info.flags == sdlInfo.flags);

    for (int i = 0; i < 16; ++i) {
      CHECK(info.texture_formats[i] == sdlInfo.texture_formats[i]);
    }

    CHECK(info.max_texture_width == sdlInfo.max_texture_width);
    CHECK(info.max_texture_height == sdlInfo.max_texture_height);
  });
}

TEST_CASE("output_width", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    CHECK(renderer.output_width() == window.width());
  });
}

TEST_CASE("output_height", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    CHECK(renderer.output_height() == window.height());
  });
}

TEST_CASE("output_size", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    const auto [width, height] = renderer.output_size();
    CHECK(width == window.width());
    CHECK(height == window.height());
  });
}

TEST_CASE("blend_mode", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    const auto mode = renderer.blend_mode();

    SDL_BlendMode sdlMode;
    SDL_GetRenderDrawBlendMode(renderer.get(), &sdlMode);

    CHECK(mode == sdlMode);
  });
}

TEST_CASE("vsync_enabled", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    const bool vsync = renderer.flags() & SDL_RENDERER_PRESENTVSYNC;
    CHECK(vsync == renderer.vsync_enabled());
  });
}

TEST_CASE("accelerated", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    const bool accelerated = renderer.flags() & SDL_RENDERER_ACCELERATED;
    CHECK(accelerated == renderer.accelerated());
  });
}

TEST_CASE("software_based", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    const bool software = renderer.flags() & SDL_RENDERER_SOFTWARE;
    CHECK(software == renderer.software_based());
  });
}

TEST_CASE("supports_target_textures", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    const bool targetTexture = renderer.flags() & SDL_RENDERER_TARGETTEXTURE;
    CHECK(targetTexture == renderer.supports_target_textures());
  });
}

TEST_CASE("using_integer_logical_scaling", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    CHECK(!renderer.using_integer_logical_scaling());

    renderer.set_logical_integer_scale(true);

    CHECK(renderer.using_integer_logical_scaling());
  });
}

TEST_CASE("color", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    const auto color = renderer.get_color();
    CHECK(color.red() == 0);
    CHECK(color.green() == 0);
    CHECK(color.blue() == 0);
    CHECK(color.alpha() == 0xFF);
  });
}

// FIXME
//TEST_CASE("text_blended", "[renderer]")
//{
//  font_test([](const ctn::renderer& renderer, const ctn::font& font) {
//    CHECK(!renderer.text_blended(nullptr, font));
//    CHECK(!renderer.text_blended("", font));
//    CHECK(renderer.text_blended("Hello", font));
//  });
//}
//
//TEST_CASE("text_blended_wrapped", "[renderer]")
//{
//  font_test([](const ctn::renderer& renderer, const ctn::font& font) {
//    CHECK(!renderer.text_blended_wrapped(nullptr, 500, font));
//    CHECK(!renderer.text_blended_wrapped("", 500, font));
//    CHECK(renderer.text_blended_wrapped("Hello", 500, font));
//  });
//}
//
//TEST_CASE("text_shaded", "[renderer]")
//{
//  font_test([](const ctn::renderer& renderer, const ctn::font& font) {
//    CHECK(!renderer.text_shaded(nullptr, ctn::colors::black, font));
//    CHECK(!renderer.text_shaded("", ctn::colors::black, font));
//    CHECK(renderer.text_shaded("Hello", ctn::colors::black, font));
//  });
//}
//
//TEST_CASE("text_solid", "[renderer]")
//{
//  font_test([](const ctn::renderer& renderer, const ctn::font& font) {
//    CHECK(!renderer.text_solid(nullptr, font));
//    CHECK(!renderer.text_solid("", font));
//    CHECK(renderer.text_solid("Hello", font));
//  });
//}

TEST_CASE("font", "[renderer]")
{
  test([](const ctn::window& window, const ctn::renderer& renderer) {

  });

  const auto name = "daniel"_hs;

  ctn::window window;
  ctn::renderer renderer{window};

  CHECK(!renderer.font(name));

  auto font = ctn::font::shared("resources/daniel.ttf", 12);
  renderer.add_font(name, font);

  CHECK(renderer.font(name));

  auto storedFont = renderer.font(name);
  CHECK(storedFont);
  CHECK(font == storedFont);
}

TEST_CASE("viewport", "[renderer]")
{
  ctn::window window;
  ctn::renderer renderer{window};

  const auto viewport = renderer.viewport();
  CHECK(viewport.width() == window.width());
  CHECK(viewport.height() == window.height());
}

TEST_CASE("set_translation_viewport", "[renderer]")
{
  ctn::window window;
  ctn::renderer renderer{window};

  const ctn::rect_f viewport{{123, 523}, {845, 541}};
  renderer.set_translation_viewport(viewport);

  const auto rendererViewport = renderer.translation_viewport();

  CHECK(rendererViewport.x() == viewport.x());
  CHECK(rendererViewport.y() == viewport.y());
  CHECK(rendererViewport.width() == viewport.width());
  CHECK(rendererViewport.height() == viewport.height());
}

TEST_CASE("translation_viewport", "[renderer]")
{
  ctn::window window;
  ctn::renderer renderer{window};

  const auto viewport = renderer.translation_viewport();

  CHECK(viewport.x() == 0);
  CHECK(viewport.y() == 0);
  CHECK(viewport.width() == 0);
  CHECK(viewport.height() == 0);
}

TEST_CASE("Renderer clipping", "[renderer]")
{
  ctn::window window;
  ctn::renderer renderer{window};

  SECTION("Default values")
  {
    CHECK(!renderer.clipping_enabled());
    const auto clip = renderer.clip();
    CHECK(!clip);
  }

  CHECK_NOTHROW(renderer.set_clip(ctn::nothing));

  const ctn::rect_i clip{{5, 2}, {75, 93}};

  renderer.set_clip(clip);
  CHECK(renderer.clipping_enabled());
  CHECK(renderer.clip());

  const auto rendererClip = *renderer.clip();

  CHECK(clip.x() == rendererClip.x());
  CHECK(clip.y() == rendererClip.y());
  CHECK(clip.width() == rendererClip.width());
  CHECK(clip.height() == rendererClip.height());
}

TEST_CASE("set_target", "[renderer]")
{
  ctn::window window;
  ctn::renderer renderer{window};
  CHECK_NOTHROW(renderer.set_target(nullptr));
}

TEST_CASE("to_string", "[renderer]")
{
  ctn::window window;
  ctn::renderer renderer{window};
  ctn::log::info(ctn::log::category::test, "%s", renderer.to_string().c_str());
}

TEST_CASE("render_drivers", "[renderer]")
{
  CHECK(ctn::renderer::render_drivers() == SDL_GetNumRenderDrivers());
}

TEST_CASE("video_drivers", "[renderer]")
{
  CHECK(ctn::renderer::video_drivers() == SDL_GetNumVideoDrivers());
}

TEST_CASE("driver_info", "[renderer]")
{
  CHECK(!ctn::renderer::driver_info(-1));
  CHECK(!ctn::renderer::driver_info(ctn::renderer::render_drivers()));
  CHECK(ctn::renderer::driver_info(0));
}

TEST_CASE("get", "[renderer]")
{
  ctn::window window;
  ctn::renderer renderer{window};
  CHECK(renderer.get());
}

TEST_CASE("Renderer to SDL_Renderer*", "[renderer]")
{
  SECTION("Const")
  {
    ctn::window window;
    const ctn::renderer renderer{window};
    const auto* sdlRenderer = static_cast<const SDL_Renderer*>(renderer);
    CHECK(sdlRenderer);
  }

  SECTION("Non-const")
  {
    ctn::window window;
    ctn::renderer renderer{window};
    auto* sdlRenderer = static_cast<SDL_Renderer*>(renderer);
    CHECK(sdlRenderer);
  }
}
