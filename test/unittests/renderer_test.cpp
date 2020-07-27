#include "renderer.hpp"

#include <catch.hpp>
#include <iostream>

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

TEST_CASE("renderer:: ctor(nn_owner<SDL_Renderer*>)", "[renderer]")
{
  ctn::window window;
  auto* ren = SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_SOFTWARE);
  CHECK_NOTHROW(ctn::renderer{ren});
}

TEST_CASE("renderer:: ctor(const window&, SDL_RendererFlags)", "[renderer]")
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

TEST_CASE("renderer::operator=(renderer&&)", "[renderer]")
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
    const ctn::window firstwindow;
    const ctn::window secondwindow;
    ctn::renderer renderer{firstwindow};
    ctn::renderer other{secondwindow};

    other = std::move(renderer);

    CHECK(other.get());
  }
}

TEST_CASE("Renderer smart pointer factory methods", "[renderer]")
{
  SECTION("Unique")
  {
    ctn::window window;
    auto* ren = SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_SOFTWARE);
    CHECK_NOTHROW(ctn::renderer::unique(ren));
  }

  SECTION("Shared")
  {
    ctn::window window;
    auto* ren = SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_SOFTWARE);
    CHECK_NOTHROW(ctn::renderer::shared(ren));
  }
}

TEST_CASE("renderer::clear", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    CHECK_NOTHROW(renderer.clear());
  });
}

TEST_CASE("renderer::clear_with", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    const auto selectedColor = ctn::colors::pink;
    renderer.set_color(selectedColor);

    CHECK_NOTHROW(renderer.clear_with(ctn::colors::medium_aqua_marine));
    CHECK(renderer.get_color() == selectedColor);
  });
}

TEST_CASE("renderer::present", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    CHECK_NOTHROW(renderer.present());
  });
}

TEST_CASE("renderer::add_font", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    using namespace std::string_literals;

    constexpr auto id = "foo"_hs;

    renderer.add_font(id, ctn::font{"resources/daniel.ttf", 12});

    CHECK(renderer.has_font(id));
    CHECK(renderer.get_font(id).family_name() == "Daniel"s);

    CHECK_NOTHROW(
        renderer.add_font(id, ctn::font{"resources/type_writer.ttf", 12}));

    CHECK(renderer.has_font(id));
    CHECK(renderer.get_font(id).family_name() == "Type Writer"s);
  });
}

TEST_CASE("renderer::emplace_font", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    using namespace std::string_literals;

    constexpr auto id = "foo"_hs;

    renderer.emplace_font(id, "resources/daniel.ttf", 12);

    CHECK(renderer.has_font(id));
    CHECK(renderer.get_font(id).family_name() == "Daniel"s);

    CHECK_NOTHROW(renderer.emplace_font(id, "resources/type_writer.ttf", 12));

    CHECK(renderer.has_font(id));
    CHECK(renderer.get_font(id).family_name() == "Type Writer"s);
  });
}

TEST_CASE("renderer::remove_font", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    constexpr auto name = "daniel"_hs;

    CHECK_NOTHROW(renderer.remove_font(""_hs));

    renderer.add_font(name, ctn::font{"resources/daniel.ttf", 12});
    CHECK(renderer.has_font(name));

    renderer.remove_font(name);
    CHECK(!renderer.has_font(name));
  });
}

TEST_CASE("renderer::draw_rect", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    const ctn::irect irect{{1, 2}, {3, 4}};
    const ctn::frect frect{{11.3f, 34.2f}, {54.2f, 91.3f}};

    CHECK_NOTHROW(renderer.draw_rect(irect));
    CHECK_NOTHROW(renderer.draw_rect(frect));
  });
}

TEST_CASE("renderer::fill_rect", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    const ctn::irect irect{{14, 23}, {331, 487}};
    const ctn::frect frect{{11.3f, 34.2f}, {54.2f, 91.3f}};

    CHECK_NOTHROW(renderer.fill_rect(irect));
    CHECK_NOTHROW(renderer.fill_rect(frect));
  });
}

TEST_CASE("renderer::draw_rect_t", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    const ctn::irect irect{{14, 23}, {331, 487}};
    const ctn::frect frect{{11.3f, 34.2f}, {54.2f, 91.3f}};

    CHECK_NOTHROW(renderer.draw_rect_t(irect));
    CHECK_NOTHROW(renderer.draw_rect_t(frect));
  });
}

TEST_CASE("renderer::fill_rect_t", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    const ctn::irect irect{{14, 23}, {331, 487}};
    const ctn::frect frect{{11.3f, 34.2f}, {54.2f, 91.3f}};

    CHECK_NOTHROW(renderer.fill_rect_t(irect));
    CHECK_NOTHROW(renderer.fill_rect_t(frect));
  });
}

TEST_CASE("renderer::draw_line", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    CHECK_NOTHROW(renderer.draw_line(ctn::ipoint{4, 5}, ctn::ipoint{12, 94}));
    CHECK_NOTHROW(
        renderer.draw_line(ctn::fpoint{6.2f, 8.3f}, ctn::fpoint{21.6f, 17.8f}));
  });
}

TEST_CASE("renderer::draw_lines", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    const std::vector<ctn::ipoint> points_i{{4, 5}, {50, 2}, {-10, 7}};
    const std::vector<ctn::fpoint> points_f{
        {8.3f, 3.4f}, {54.4f, 86.3f}, {-10.9f, 67.2f}};

    CHECK_NOTHROW(renderer.draw_lines(points_i));
    CHECK_NOTHROW(renderer.draw_lines(points_f));
  });
}

TEST_CASE("render: texture at point", "[renderer]")
{
  texture_test([](ctn::renderer& renderer, const ctn::texture& texture) {
    const ctn::ipoint position_i{3, 57};
    const ctn::fpoint position_f{26.4f, 68.2f};

    CHECK_NOTHROW(renderer.render(texture, position_i));
    CHECK_NOTHROW(renderer.render(texture, position_f));
  });
}

TEST_CASE("render: texture according to rectangle", "[renderer]")
{
  texture_test([](ctn::renderer& renderer, const ctn::texture& texture) {
    const ctn::irect irect{{12, 57}, {175, 218}};
    const ctn::frect frect{{23.7f, 36.3f}, {317.3f, 348.3f}};

    CHECK_NOTHROW(renderer.render(texture, irect));
    CHECK_NOTHROW(renderer.render(texture, frect));
  });
}

TEST_CASE("render: src/dst rectangles", "[renderer]")
{
  texture_test([](ctn::renderer& renderer, const ctn::texture& texture) {
    const ctn::irect src{{10, 15}, {20, 20}};

    const ctn::irect dst_i{{35, 92}, {15, 23}};
    const ctn::frect dst_f{{77.9f, 45.6f}, {512.1f, 375.2f}};

    CHECK_NOTHROW(renderer.render(texture, src, dst_i));
    CHECK_NOTHROW(renderer.render(texture, src, dst_f));
  });
}

TEST_CASE("render: src/dst rectangles and rotation", "[renderer]")
{
  texture_test([](ctn::renderer& renderer, const ctn::texture& texture) {
    const ctn::irect src{{10, 15}, {20, 20}};
    const auto angle = 182;

    const ctn::irect dst_i{{35, 92}, {15, 23}};
    const ctn::frect dst_f{{21.4f, 47.3f}, {338.3f, 177.3f}};

    CHECK_NOTHROW(renderer.render(texture, src, dst_i, angle));
    CHECK_NOTHROW(renderer.render(texture, src, dst_f, angle));
  });
}

TEST_CASE("render: src/dst rectangles, rotation and center-of-rotation",
          "[renderer]")
{
  texture_test([](ctn::renderer& renderer, const ctn::texture& texture) {
    const ctn::irect src{{16, 11}, {37, 77}};
    const auto angle = 359;

    const ctn::irect dst_i{{22, 76}, {245, 112}};
    const ctn::frect dst_f{{54.5f, 25.6f}, {136.5f, 387.8f}};

    const ctn::ipoint center_i{44, 12};
    const ctn::fpoint center_f{12.3f, 45.2f};

    CHECK_NOTHROW(renderer.render(texture, src, dst_i, angle, center_i));
    CHECK_NOTHROW(renderer.render(texture, src, dst_f, angle, center_f));
  });
}

TEST_CASE("render: src/dst rectangles and flip", "[renderer]")
{
  texture_test([](ctn::renderer& renderer, const ctn::texture& texture) {
    CHECK_NOTHROW(renderer.render(texture,
                                  ctn::irect{{10, 15}, {20, 20}},
                                  ctn::irect{{35, 92}, {15, 23}},
                                  SDL_FLIP_HORIZONTAL));
  });
}

TEST_CASE("render: src/dst rectangles, rotation, center-of-rotation and flip",
          "[renderer]")
{
  texture_test([](ctn::renderer& renderer, const ctn::texture& texture) {
    CHECK_NOTHROW(renderer.render(texture,
                                  {{10, 15}, {20, 20}},
                                  ctn::irect{{35, 92}, {15, 23}},
                                  -5,
                                  ctn::ipoint{5, 5},
                                  SDL_FLIP_HORIZONTAL));
  });
}

TEST_CASE("render_t: texture at point", "[renderer]")
{
  texture_test([](ctn::renderer& renderer, const ctn::texture& texture) {
    const ctn::ipoint pos_i{-5, 66};
    const ctn::fpoint pos_f{3.8f, 43.3f};

    CHECK_NOTHROW(renderer.render_t(texture, pos_i));
    CHECK_NOTHROW(renderer.render_t(texture, pos_f));
  });
}

TEST_CASE("render_t: texture according to rectangle", "[renderer]")
{
  texture_test([](ctn::renderer& renderer, const ctn::texture& texture) {
    const ctn::irect irect{{12, 7}, {115, 876}};
    const ctn::frect frect{{7.4f, 2.3f}, {175.3f, 412.8f}};

    CHECK_NOTHROW(renderer.render_t(texture, irect));
    CHECK_NOTHROW(renderer.render_t(texture, frect));
  });
}

TEST_CASE("render_t: src/dst rectangles", "[renderer]")
{
  texture_test([](ctn::renderer& renderer, const ctn::texture& texture) {
    const ctn::irect src{{123, 444}, {467, 221}};

    const ctn::irect dst_i{{5, 34}, {123, 321}};
    const ctn::frect dst_f{{73.1f, 22.3f}, {116.4f, 443.4f}};

    CHECK_NOTHROW(renderer.render_t(texture, src, dst_i));
    CHECK_NOTHROW(renderer.render_t(texture, src, dst_f));
  });
}

TEST_CASE("render_t: src/dst rectangles and rotation", "[renderer]")
{
  texture_test([](ctn::renderer& renderer, const ctn::texture& texture) {
    const ctn::irect src{{10, 15}, {20, 20}};
    const auto angle = 17;

    const ctn::irect dst_i{{35, 92}, {15, 23}};
    const ctn::frect dst_f{{67.1f, 43.3f}, {77.4f, 23.4f}};

    CHECK_NOTHROW(renderer.render_t(texture, src, dst_i, angle));
    CHECK_NOTHROW(renderer.render_t(texture, src, dst_f, angle));
  });
}

TEST_CASE("render_t: src/dst rectangles, rotation and center-of-rotation",
          "[renderer]")
{
  texture_test([](ctn::renderer& renderer, const ctn::texture& texture) {
    const ctn::irect src{{10, 15}, {20, 20}};
    const auto angle = 23;

    const ctn::irect dst_i{{35, 92}, {15, 23}};
    const ctn::frect dst_f{{14.5f, 23.6f}, {126.5f, 327.8f}};

    const ctn::ipoint center_i{5, 9};
    const ctn::fpoint center_f{16.3f, 34.7f};

    CHECK_NOTHROW(renderer.render_t(texture, src, dst_i, angle, center_i));
    CHECK_NOTHROW(renderer.render_t(texture, src, dst_f, angle, center_f));
  });
}

TEST_CASE("render_t: src/dst rectangles and flip", "[renderer]")
{
  texture_test([](ctn::renderer& renderer, const ctn::texture& texture) {
    const ctn::irect src{{10, 15}, {20, 20}};
    const SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;

    const ctn::irect dst_i{{35, 92}, {15, 23}};
    const ctn::frect dst_f{{382.3f, 12.4f}, {35.6f, 238.9f}};

    CHECK_NOTHROW(renderer.render_t(texture, src, dst_i, flip));
    CHECK_NOTHROW(renderer.render_t(texture, src, dst_f, flip));
  });
}

TEST_CASE("render_t: src/dst rectangles, rotation, center-of-rotation and flip",
          "[renderer]")
{
  texture_test([](ctn::renderer& renderer, const ctn::texture& texture) {
    const ctn::irect src{{10, 15}, {20, 20}};
    const SDL_RendererFlip flip = SDL_FLIP_VERTICAL;
    const auto angle = 126;

    const ctn::irect dst_i{{35, 92}, {15, 23}};
    const ctn::frect dst_f{{382.3f, 12.4f}, {35.6f, 238.9f}};

    const ctn::ipoint center_i{5, 5};
    const ctn::fpoint center_f{74.3f, 930.3f};

    CHECK_NOTHROW(
        renderer.render_t(texture, src, dst_i, angle, center_i, flip));

    CHECK_NOTHROW(
        renderer.render_t(texture, src, dst_f, angle, center_f, flip));
  });
}

TEST_CASE("renderer::set_color", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    const auto& color = ctn::colors::pale_violet_red;

    renderer.set_color(color);
    CHECK(color == renderer.get_color());
  });
}

TEST_CASE("renderer::set_viewport", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    const ctn::irect viewport{{50, 33}, {768, 453}};

    renderer.set_viewport(viewport);
    CHECK(viewport == renderer.viewport());
  });
}

TEST_CASE("renderer::set_logical_size", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    const ctn::iarea size{842, 253};

    renderer.set_logical_size(size);

    CHECK(renderer.logical_width() == size.width);
    CHECK(renderer.logical_height() == size.height);
  });
}

TEST_CASE("renderer::set_scale", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    const auto xScale = 0.8f;
    const auto yScale = 0.4f;
    renderer.set_scale(xScale, yScale);

    CHECK(renderer.x_scale() == xScale);
    CHECK(renderer.y_scale() == yScale);
  });
}

TEST_CASE("renderer::x_scale", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    CHECK(renderer.x_scale() == 1);
  });
}

TEST_CASE("renderer::y_scale", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    CHECK(renderer.y_scale() == 1);
  });
}

TEST_CASE("renderer::logical_width", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    CHECK(renderer.logical_width() == 0);
  });
}

TEST_CASE("renderer::logical_height", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    CHECK(renderer.logical_height() == 0);
  });
}

TEST_CASE("renderer::logical_size", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    const ctn::iarea size{732, 156};

    renderer.set_logical_size(size);

    const auto [width, height] = renderer.logical_size();
    CHECK(width == size.width);
    CHECK(height == size.height);
  });
}

TEST_CASE("renderer::info", "[renderer]")
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

TEST_CASE("renderer::output_width", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    CHECK(renderer.output_width() == window.width());
  });
}

TEST_CASE("renderer::output_height", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    CHECK(renderer.output_height() == window.height());
  });
}

TEST_CASE("renderer::output_size", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    const auto [width, height] = renderer.output_size();
    CHECK(width == window.width());
    CHECK(height == window.height());
  });
}

TEST_CASE("renderer::blend_mode", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    const auto mode = renderer.blend_mode();

    SDL_BlendMode sdlMode;
    SDL_GetRenderDrawBlendMode(renderer.get(), &sdlMode);

    CHECK(mode == sdlMode);
  });
}

TEST_CASE("renderer::is_vsync_enabled", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    const bool vsync = renderer.flags() & SDL_RENDERER_PRESENTVSYNC;
    CHECK(vsync == renderer.is_vsync_enabled());
  });
}

TEST_CASE("renderer::is_accelerated", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    const bool accelerated = renderer.flags() & SDL_RENDERER_ACCELERATED;
    CHECK(accelerated == renderer.is_accelerated());
  });
}

TEST_CASE("renderer::is_software_based", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    const bool software = renderer.flags() & SDL_RENDERER_SOFTWARE;
    CHECK(software == renderer.is_software_based());
  });
}

TEST_CASE("renderer::supports_target_textures", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    const bool targetTexture = renderer.flags() & SDL_RENDERER_TARGETTEXTURE;
    CHECK(targetTexture == renderer.supports_target_textures());
  });
}

TEST_CASE("renderer::using_integer_logical_scaling", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    CHECK(!renderer.is_using_integer_logical_scaling());

    renderer.set_logical_integer_scale(true);

    CHECK(renderer.is_using_integer_logical_scaling());
  });
}

TEST_CASE("renderer::color", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    const auto color = renderer.get_color();
    CHECK(color.red() == 0);
    CHECK(color.green() == 0);
    CHECK(color.blue() == 0);
    CHECK(color.alpha() == 0xFF);
  });
}

TEST_CASE("renderer::get_font", "[renderer]")
{
  test([](const ctn::window& window, ctn::renderer& renderer) {
    constexpr auto name = "daniel"_hs;

    CHECK_THROWS(renderer.get_font(name));

    renderer.add_font(name, ctn::font{"resources/daniel.ttf", 12});

    CHECK_NOTHROW(renderer.get_font(name));

    auto& font = renderer.get_font(name);

    using namespace std::string_literals;
    CHECK(font.family_name() == "Daniel"s);
  });
}

TEST_CASE("renderer::viewport", "[renderer]")
{
  ctn::window window;
  ctn::renderer renderer{window};

  const auto viewport = renderer.viewport();
  CHECK(viewport.width() == window.width());
  CHECK(viewport.height() == window.height());
}

TEST_CASE("renderer::set_translation_viewport", "[renderer]")
{
  ctn::window window;
  ctn::renderer renderer{window};

  const ctn::frect viewport{{123, 523}, {845, 541}};
  renderer.set_translation_viewport(viewport);

  const auto rendererViewport = renderer.translation_viewport();

  CHECK(rendererViewport.x() == viewport.x());
  CHECK(rendererViewport.y() == viewport.y());
  CHECK(rendererViewport.width() == viewport.width());
  CHECK(rendererViewport.height() == viewport.height());
}

TEST_CASE("renderer::translation_viewport", "[renderer]")
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
    CHECK(!renderer.is_clipping_enabled());
    const auto clip = renderer.clip();
    CHECK(!clip);
  }

  CHECK_NOTHROW(renderer.set_clip(ctn::nothing));

  const ctn::irect clip{{5, 2}, {75, 93}};

  renderer.set_clip(clip);
  CHECK(renderer.is_clipping_enabled());
  CHECK(renderer.clip());

  const auto rendererClip = *renderer.clip();

  CHECK(clip.x() == rendererClip.x());
  CHECK(clip.y() == rendererClip.y());
  CHECK(clip.width() == rendererClip.width());
  CHECK(clip.height() == rendererClip.height());
}

TEST_CASE("renderer::set_target", "[renderer]")
{
  ctn::window window;
  ctn::renderer renderer{window};
  CHECK_NOTHROW(renderer.set_target(nullptr));
}

TEST_CASE("num_render_drivers", "[renderer]")
{
  CHECK(ctn::num_render_drivers() == SDL_GetNumRenderDrivers());
}

TEST_CASE("num_video_drivers", "[renderer]")
{
  CHECK(ctn::num_video_drivers() == SDL_GetNumVideoDrivers());
}

TEST_CASE("renderer::get_render_driver_info", "[renderer]")
{
  CHECK(!ctn::get_render_driver_info(-1));
  CHECK(!ctn::get_render_driver_info(ctn::num_render_drivers()));
}

TEST_CASE("renderer::get", "[renderer]")
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

TEST_CASE("renderer to_string", "[renderer]")
{
  ctn::window window;
  ctn::renderer renderer{window};

  ctn::log::put(ctn::to_string(renderer));
}

TEST_CASE("renderer stream operator", "[renderer]")
{
  ctn::window window;
  ctn::renderer renderer{window};

  std::cout << "COUT: " << renderer << '\n';
}