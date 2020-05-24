#include "renderer.h"

#include <catch.hpp>
#include <utility>

#include "centurion_exception.h"
#include "colors.h"
#include "font.h"
#include "log.h"
#include "rect.h"
#include "texture.h"
#include "window.h"

using namespace centurion;

static constexpr auto* texturePath = "resources/panda.png";

TEST_CASE("Renderer(SDL_Renderer*)", "[Renderer]")
{
  CHECK_THROWS_AS(Renderer{nullptr}, CenturionException);

  Window window;
  SDL_Renderer* ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
  CHECK_NOTHROW(Renderer{ren});
}

TEST_CASE("Renderer(const Window&, SDL_RendererFlags)", "[Renderer]")
{
  Window window;
  Renderer renderer{window};

  SECTION("Check default flags")
  {
    const Uint32 flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    const auto correctFlags = renderer.flags() & flags;
    CHECK(correctFlags);
  }
}

TEST_CASE("Renderer(Renderer&&)", "[Renderer]")
{
  const Window window;

  Renderer renderer{window};
  Renderer other{std::move(renderer)};

  CHECK(!renderer.get());
  CHECK(other.get());
}

TEST_CASE("Renderer::operator=(Renderer&&)", "[Renderer]")
{
  SECTION("Self-assignment")
  {
    const Window window;
    Renderer renderer{window};

    renderer = std::move(renderer);
    CHECK(renderer.get());
  }

  SECTION("Normal usage")
  {
    const Window firstWindow;
    const Window secondWindow;
    Renderer renderer{firstWindow};
    Renderer other{secondWindow};

    other = std::move(renderer);

    CHECK(!renderer.get());
    CHECK(other.get());
  }
}

TEST_CASE("Renderer::unique(SDL_Renderer*)", "[Renderer]")
{
  CHECK_THROWS_AS(Renderer::unique(nullptr), CenturionException);

  Window window;
  SDL_Renderer* ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

  CHECK_NOTHROW(Renderer::unique(ren));
}

TEST_CASE("Renderer::unique(const Window&, SDL_RendererFlags)", "[Renderer]")
{
  Window window;
  auto renderer = Renderer::unique(window);

  SECTION("Check default flags")
  {
    const Uint32 flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    const auto correctFlags = renderer->flags() & flags;
    CHECK(correctFlags);
  }
}

TEST_CASE("Renderer::shared(SDL_Renderer*)", "[Renderer]")
{
  CHECK_THROWS_AS(Renderer::shared(nullptr), CenturionException);

  Window window;
  SDL_Renderer* ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

  CHECK_NOTHROW(Renderer::shared(ren));
}

TEST_CASE("Renderer::shared(const Window&, SDL_RendererFlags)", "[Renderer]")
{
  Window window;
  auto renderer = Renderer::shared(window);

  SECTION("Check default flags")
  {
    const Uint32 flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    const auto correctFlags = renderer->flags() & flags;
    CHECK(correctFlags);
  }
}

TEST_CASE("Renderer::clear", "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  CHECK_NOTHROW(renderer.clear());
}

TEST_CASE("Renderer::present", "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  CHECK_NOTHROW(renderer.present());
}

TEST_CASE("Renderer::add_font(const std::string&, const SharedPtr<Font>&)",
          "[Renderer]")
{
  Window window;
  Renderer renderer{window};

  SECTION("Bad arguments") { CHECK_NOTHROW(renderer.add_font("", nullptr)); }

  SECTION("Normal arguments")
  {
    auto font = Font::shared("resources/daniel.ttf", 12);
    const auto fontName = font->family_name();

    renderer.add_font(fontName, font);
    CHECK(renderer.has_font(fontName));
    CHECK_NOTHROW(renderer.add_font(fontName, font));
    CHECK(renderer.has_font(fontName));
  }
}

TEST_CASE("Renderer::add_font(const SharedPtr<Font>&)", "[Renderer]")
{
  Window window;
  Renderer renderer{window};

  SECTION("Bad arguments")
  {
    CHECK_NOTHROW(renderer.add_font(nullptr));
    CHECK(!renderer.add_font(nullptr));
  }

  SECTION("Normal arguments")
  {
    auto font = Font::shared("resources/daniel.ttf", 12);
    const auto fontName = font->family_name();

    const auto name = renderer.add_font(font);
    CHECK(name);
    CHECK(*name == fontName);

    CHECK(!renderer.add_font(font));
  }
}

TEST_CASE("Renderer::remove_font", "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  const std::string name = "foo";
  const auto font = Font::shared("resources/daniel.ttf", 12);

  CHECK_NOTHROW(renderer.remove_font(""));

  renderer.add_font(name, font);
  CHECK(renderer.has_font(name));

  renderer.remove_font(name);
  CHECK(!renderer.has_font(name));
}

TEST_CASE("Renderer::draw_rect", "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  CHECK_NOTHROW(renderer.draw_rect({}));
}

TEST_CASE("Renderer::fill_rect", "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  CHECK_NOTHROW(renderer.fill_rect({}));
}

TEST_CASE("Renderer::draw_rect_f", "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  CHECK_NOTHROW(renderer.draw_rect_f({}));
}

TEST_CASE("Renderer::fill_rect_f", "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  CHECK_NOTHROW(renderer.fill_rect_f({}));
}

TEST_CASE("Renderer::draw_rect_t", "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  CHECK_NOTHROW(renderer.draw_rect_t({}));
}

TEST_CASE("Renderer::fill_rect_t", "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  CHECK_NOTHROW(renderer.fill_rect_t({}));
}

TEST_CASE("Renderer::draw_rect_tf", "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  CHECK_NOTHROW(renderer.draw_rect_tf({}));
}

TEST_CASE("Renderer::fill_rect_tf", "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  CHECK_NOTHROW(renderer.fill_rect_tf({}));
}

TEST_CASE("Renderer::draw_line", "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  CHECK_NOTHROW(renderer.draw_line({}, {}));
}

TEST_CASE("Renderer::draw_line_f", "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  CHECK_NOTHROW(renderer.draw_line_f({}, {}));
}

TEST_CASE("Renderer::draw_lines", "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  const std::vector<IPoint> points{{4, 5}, {50, 2}, {-10, 7}};
  CHECK_NOTHROW(renderer.draw_lines(points));
}

TEST_CASE("Renderer::render(Texture&, IPoint)", "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  Texture texture{renderer, texturePath};
  CHECK_NOTHROW(renderer.render(texture, IPoint{-5, 410}));
}

TEST_CASE("Renderer::render(Texture&, IRect&)", "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  Texture texture{renderer, texturePath};
  CHECK_NOTHROW(renderer.render(texture, IRect{65, -35, 124, 99}));
}

TEST_CASE("Renderer::render(Texture&, IRect&, IRect&)", "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  Texture texture{renderer, texturePath};
  CHECK_NOTHROW(
      renderer.render(texture, IRect{10, 15, 20, 20}, IRect{35, 92, 15, 23}));
}

TEST_CASE("Renderer::render(Texture&, IRect&, IRect&, double)", "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  Texture texture{renderer, texturePath};
  CHECK_NOTHROW(renderer.render(
      texture, IRect{10, 15, 20, 20}, IRect{35, 92, 15, 23}, 17));
}

TEST_CASE("Renderer::render(Texture&, IRect&, IRect&, double, IPoint&)",
          "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  Texture texture{renderer, texturePath};
  CHECK_NOTHROW(renderer.render(
      texture, IRect{10, 15, 20, 20}, IRect{35, 92, 15, 23}, 17, IPoint{5, 9}));
}

TEST_CASE("Renderer::render(Texture&, IRect&, IRect&, SDL_RendererFlip)",
          "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  Texture texture{renderer, texturePath};
  CHECK_NOTHROW(renderer.render(texture,
                                IRect{10, 15, 20, 20},
                                IRect{35, 92, 15, 23},
                                SDL_FLIP_HORIZONTAL));
}

TEST_CASE(
    "Renderer::render(Texture&, IRect&, IRect&, double, "
    "IPoint&,SDL_RendererFlip)",
    "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  Texture texture{renderer, texturePath};
  CHECK_NOTHROW(renderer.render_t(texture,
                                  IRect{10, 15, 20, 20},
                                  IRect{35, 92, 15, 23},
                                  -5,
                                  IPoint{5, 5},
                                  SDL_FLIP_HORIZONTAL));
}

TEST_CASE("Renderer::render_f(Texture&, FPoint)", "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  Texture texture{renderer, texturePath};
  CHECK_NOTHROW(renderer.render_f(texture, FPoint{83.6f, 523.3f}));
}

TEST_CASE("Renderer::render_f(Texture&, FRect&)", "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  Texture texture{renderer, texturePath};
  CHECK_NOTHROW(renderer.render_f(texture, FRect{146, 34, 99, 58}));
}

TEST_CASE("Renderer::render_f(Texture&, IRect&, FRect&)", "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  Texture texture{renderer, texturePath};
  CHECK_NOTHROW(
      renderer.render_f(texture, IRect{5, 8, 15, 15}, FRect{77, 23, 100, 59}));
}

TEST_CASE("Renderer::render_f(Texture&, IRect&, FRect&, double)", "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  Texture texture{renderer, texturePath};
  CHECK_NOTHROW(renderer.render_f(
      texture, IRect{1, 2, 5, 8}, FRect{774, 413, 99, 224}, 123));
}

TEST_CASE("Renderer::render_f(Texture&, IRect&, FRect&, double, FPoint&)",
          "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  Texture texture{renderer, texturePath};
  CHECK_NOTHROW(renderer.render_f(texture,
                                  IRect{10, 15, 20, 20},
                                  FRect{99, 35, 185, 23},
                                  56,
                                  FPoint{-2.4f, 14.3f}));
}

TEST_CASE("Renderer::render_f(Texture&, IRect&, FRect&, SDL_RendererFlip)",
          "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  Texture texture{renderer, texturePath};
  CHECK_NOTHROW(renderer.render_f(texture,
                                  IRect{10, 15, 20, 20},
                                  FRect{-67, 3, 93, 110.5f},
                                  SDL_FLIP_HORIZONTAL));
}

TEST_CASE(
    "Renderer::render_f(Texture&, IRect&, FRect&, double, "
    "FPoint&, SDL_RendererFlip)",
    "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  Texture texture{renderer, texturePath};
  CHECK_NOTHROW(renderer.render_f(texture,
                                  IRect{10, 8, 8, 9},
                                  FRect{4.0f, -34, 88, 105.9f},
                                  89,
                                  FPoint{5, 5},
                                  SDL_FLIP_VERTICAL));
}

TEST_CASE("Renderer::render_t(Texture&, IPoint)", "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  Texture texture{renderer, texturePath};
  CHECK_NOTHROW(renderer.render_t(texture, IPoint{-5, 410}));
}

TEST_CASE("Renderer::render_t(Texture&, IRect&)", "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  Texture texture{renderer, texturePath};
  CHECK_NOTHROW(renderer.render_t(texture, IRect{65, -35, 124, 99}));
}

TEST_CASE("Renderer::render_t(Texture&, IRect&, IRect&)", "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  Texture texture{renderer, texturePath};
  CHECK_NOTHROW(
      renderer.render_t(texture, IRect{10, 15, 20, 20}, IRect{35, 92, 15, 23}));
}

TEST_CASE("Renderer::render_t(Texture&, IRect&, IRect&, double)", "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  Texture texture{renderer, texturePath};
  CHECK_NOTHROW(renderer.render_t(
      texture, IRect{10, 15, 20, 20}, IRect{35, 92, 15, 23}, 17));
}

TEST_CASE("Renderer::render_t(Texture&, IRect&, IRect&, double, IPoint&)",
          "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  Texture texture{renderer, texturePath};
  CHECK_NOTHROW(renderer.render_t(
      texture, IRect{10, 15, 20, 20}, IRect{35, 92, 15, 23}, 17, IPoint{5, 9}));
}

TEST_CASE("Renderer::render_t(Texture&, IRect&, IRect&, SDL_RendererFlip)",
          "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  Texture texture{renderer, texturePath};
  CHECK_NOTHROW(renderer.render_t(texture,
                                  IRect{10, 15, 20, 20},
                                  IRect{35, 92, 15, 23},
                                  SDL_FLIP_HORIZONTAL));
}

TEST_CASE(
    "Renderer::render_t(Texture&, IRect&, IRect&, double, "
    "IPoint&,SDL_RendererFlip)",
    "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  Texture texture{renderer, texturePath};
  CHECK_NOTHROW(renderer.render_t(texture,
                                  IRect{10, 15, 20, 20},
                                  IRect{35, 92, 15, 23},
                                  -5,
                                  IPoint{5, 5},
                                  SDL_FLIP_HORIZONTAL));
}

TEST_CASE("Renderer::render_tf(Texture&, FPoint)", "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  Texture texture{renderer, texturePath};
  CHECK_NOTHROW(renderer.render_tf(texture, FPoint{83.6f, 523.3f}));
}

TEST_CASE("Renderer::render_tf(Texture&, FRect&)", "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  Texture texture{renderer, texturePath};
  CHECK_NOTHROW(renderer.render_tf(texture, FRect{146, 34, 99, 58}));
}

TEST_CASE("Renderer::render_tf(Texture&, IRect&, FRect&)", "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  Texture texture{renderer, texturePath};
  CHECK_NOTHROW(
      renderer.render_tf(texture, IRect{5, 8, 15, 15}, FRect{77, 23, 100, 59}));
}

TEST_CASE("Renderer::render_tf(Texture&, IRect&, FRect&, double)", "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  Texture texture{renderer, texturePath};
  CHECK_NOTHROW(renderer.render_tf(
      texture, IRect{1, 2, 5, 8}, FRect{774, 413, 99, 224}, 123));
}

TEST_CASE("Renderer::render_tf(Texture&, IRect&, FRect&, double, FPoint&)",
          "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  Texture texture{renderer, texturePath};
  CHECK_NOTHROW(renderer.render_tf(texture,
                                   IRect{10, 15, 20, 20},
                                   FRect{99, 35, 185, 23},
                                   56,
                                   FPoint{-2.4f, 14.3f}));
}

TEST_CASE("Renderer::render_tf(Texture&, IRect&, FRect&, SDL_RendererFlip)",
          "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  Texture texture{renderer, texturePath};
  CHECK_NOTHROW(renderer.render_tf(texture,
                                   IRect{10, 15, 20, 20},
                                   FRect{-67, 3, 93, 110.5f},
                                   SDL_FLIP_HORIZONTAL));
}

TEST_CASE("Renderer::render_tf(Texture&, IRect&, FRect&, double, ",
          "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  Texture texture{renderer, texturePath};
  CHECK_NOTHROW(renderer.render_tf(texture,
                                   IRect{10, 8, 8, 9},
                                   FRect{4.0f, -34, 88, 105.9f},
                                   89,
                                   FPoint{5, 5},
                                   SDL_FLIP_VERTICAL));
}

TEST_CASE("Renderer::set_color", "[Renderer]")
{
  Window window;
  Renderer renderer{window};

  const auto& color = color::pale_violet_red;
  renderer.set_color(color);

  CHECK(color == renderer.color());
}

TEST_CASE("Renderer::set_viewport", "[Renderer]")
{
  Window window;
  Renderer renderer{window};

  const auto viewport = IRect{50, 33, 768, 453};
  renderer.set_viewport(viewport);

  CHECK(viewport == renderer.viewport());
}

TEST_CASE("Renderer::set_logical_size", "[Renderer]")
{
  Window window;
  Renderer renderer{window};

  const auto w = 842;
  const auto h = 253;
  const Area size{w, h};

  renderer.set_logical_size(size);

  CHECK(renderer.logical_width() == w);
  CHECK(renderer.logical_height() == h);
}

TEST_CASE("Renderer::set_scale", "[Renderer]")
{
  Window window;
  Renderer renderer{window};

  const auto xScale = 0.8f;
  const auto yScale = 0.4f;
  renderer.set_scale(xScale, yScale);

  CHECK(renderer.x_scale() == xScale);
  CHECK(renderer.y_scale() == yScale);
}

TEST_CASE("Renderer::x_scale", "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  CHECK(renderer.x_scale() == 1);
}

TEST_CASE("Renderer::y_scale", "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  CHECK(renderer.y_scale() == 1);
}

TEST_CASE("Renderer::logical_width", "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  CHECK(renderer.logical_width() == 0);
}

TEST_CASE("Renderer::logical_height", "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  CHECK(renderer.logical_height() == 0);
}

TEST_CASE("Renderer::info", "[Renderer]")
{
  Window window;
  Renderer renderer{window};

  auto maybeInfo = renderer.info();
  CHECK(maybeInfo);

  if (maybeInfo) {
    auto info = *maybeInfo;

    SDL_RendererInfo sdlInfo;
    SDL_GetRendererInfo(renderer, &sdlInfo);

    CHECK_THAT(info.name, Catch::Equals(sdlInfo.name));
    CHECK(info.flags == sdlInfo.flags);

    for (int i = 0; i < 16; ++i) {
      CHECK(info.texture_formats[i] == sdlInfo.texture_formats[i]);
    }

    CHECK(info.max_texture_width == sdlInfo.max_texture_width);
    CHECK(info.max_texture_height == sdlInfo.max_texture_height);
  }
}

TEST_CASE("Renderer::output_width", "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  CHECK(renderer.output_width() == window.width());
}

TEST_CASE("Renderer::output_height", "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  CHECK(renderer.output_height() == window.height());
}

TEST_CASE("Renderer::output_size", "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  const auto [width, height] = renderer.output_size();
  CHECK(width == window.width());
  CHECK(height == window.height());
}

TEST_CASE("Renderer::blend_mode", "[Renderer]")
{
  Window window;
  Renderer renderer{window};

  const auto mode = renderer.blend_mode();

  SDL_BlendMode sdlMode;
  SDL_GetRenderDrawBlendMode(renderer, &sdlMode);

  CHECK(mode == sdlMode);
}

TEST_CASE("Renderer::vsync_enabled", "[Renderer]")
{
  Window window;
  Renderer renderer{window};

  const bool vsync = renderer.flags() & SDL_RENDERER_PRESENTVSYNC;
  CHECK(vsync == renderer.vsync_enabled());
}

TEST_CASE("Renderer::accelerated", "[Renderer]")
{
  Window window;
  Renderer renderer{window};

  const bool accelerated = renderer.flags() & SDL_RENDERER_ACCELERATED;
  CHECK(accelerated == renderer.accelerated());
}

TEST_CASE("Renderer::software_based", "[Renderer]")
{
  Window window;
  Renderer renderer{window};

  const bool software = renderer.flags() & SDL_RENDERER_SOFTWARE;
  CHECK(software == renderer.software_based());
}

TEST_CASE("Renderer::supports_target_textures", "[Renderer]")
{
  Window window;
  Renderer renderer{window};

  const bool targettexture = renderer.flags() & SDL_RENDERER_TARGETTEXTURE;
  CHECK(targettexture == renderer.supports_target_textures());
}

TEST_CASE("Renderer::using_integer_logical_scaling", "[Renderer]")
{
  Window window;
  Renderer renderer{window};

  CHECK(!renderer.using_integer_logical_scaling());

  renderer.set_logical_integer_scale(true);

  CHECK(renderer.using_integer_logical_scaling());
}

TEST_CASE("Renderer::color", "[Renderer]")
{
  Window window;
  Renderer renderer{window};

  const auto color = renderer.color();
  CHECK(color.red() == 0);
  CHECK(color.green() == 0);
  CHECK(color.blue() == 0);
  CHECK(color.alpha() == 0xFF);
}

TEST_CASE("Renderer::text_blended", "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  Font font{"resources/daniel.ttf", 12};

  CHECK(!renderer.text_blended(nullptr, font));
  CHECK(!renderer.text_blended("", font));
  CHECK(renderer.text_blended("Hello", font));
}

TEST_CASE("Renderer::text_blended_wrapped", "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  Font font{"resources/daniel.ttf", 12};

  CHECK(!renderer.text_blended_wrapped(nullptr, 500, font));
  CHECK(!renderer.text_blended_wrapped("", 500, font));
  CHECK(renderer.text_blended_wrapped("Hello", 500, font));
}

TEST_CASE("Renderer::text_shaded", "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  Font font{"resources/daniel.ttf", 12};

  CHECK(!renderer.text_shaded(nullptr, color::black, font));
  CHECK(!renderer.text_shaded("", color::black, font));
  CHECK(renderer.text_shaded("Hello", color::black, font));
}

TEST_CASE("Renderer::text_solid", "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  Font font{"resources/daniel.ttf", 12};

  CHECK(!renderer.text_solid(nullptr, font));
  CHECK(!renderer.text_solid("", font));
  CHECK(renderer.text_solid("Hello", font));
}

TEST_CASE("Renderer::font", "[Renderer]")
{
  const std::string name = "bar";

  Window window;
  Renderer renderer{window};

  CHECK(!renderer.font(name));

  auto font = Font::shared("resources/daniel.ttf", 12);
  renderer.add_font(name, font);

  CHECK(renderer.font(name));

  auto storedFont = renderer.font(name);
  CHECK(storedFont);
  CHECK(font == storedFont);
}

TEST_CASE("Renderer::viewport", "[Renderer]")
{
  Window window;
  Renderer renderer{window};

  const auto viewport = renderer.viewport();
  CHECK(viewport.width() == window.width());
  CHECK(viewport.height() == window.height());
}

TEST_CASE("Renderer::set_translation_viewport", "[Renderer]")
{
  Window window;
  Renderer renderer{window};

  const auto viewport = FRect{123, 523, 845, 541};
  renderer.set_translation_viewport(viewport);

  const auto rendererViewport = renderer.translation_viewport();

  CHECK(rendererViewport.x() == viewport.x());
  CHECK(rendererViewport.y() == viewport.y());
  CHECK(rendererViewport.width() == viewport.width());
  CHECK(rendererViewport.height() == viewport.height());
}

TEST_CASE("Renderer::translation_viewport", "[Renderer]")
{
  Window window;
  Renderer renderer{window};

  const auto viewport = renderer.translation_viewport();

  CHECK(viewport.x() == 0);
  CHECK(viewport.y() == 0);
  CHECK(viewport.width() == 0);
  CHECK(viewport.height() == 0);
}

TEST_CASE("Renderer clipping", "[Renderer]")
{
  Window window;
  Renderer renderer{window};

  SECTION("Default values")
  {
    CHECK(!renderer.clipping_enabled());
    const auto clip = renderer.clip();
    CHECK(!clip);
  }

  CHECK_NOTHROW(renderer.set_clip(tl::nullopt));

  const auto clip = IRect{5, 2, 75, 93};

  renderer.set_clip(clip);
  CHECK(renderer.clipping_enabled());
  CHECK(renderer.clip());

  const auto rendererClip = *renderer.clip();

  CHECK(clip.x() == rendererClip.x());
  CHECK(clip.y() == rendererClip.y());
  CHECK(clip.width() == rendererClip.width());
  CHECK(clip.height() == rendererClip.height());
}

TEST_CASE("Renderer::set_target", "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  CHECK_NOTHROW(renderer.set_target(nullptr));
}

TEST_CASE("Renderer::to_string", "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  Log::info(Log::Category::Test, "%s", renderer.to_string().c_str());
}

TEST_CASE("Renderer::render_drivers", "[Renderer]")
{
  CHECK(Renderer::render_drivers() == SDL_GetNumRenderDrivers());
}

TEST_CASE("Renderer::video_drivers", "[Renderer]")
{
  CHECK(Renderer::video_drivers() == SDL_GetNumVideoDrivers());
}

TEST_CASE("Renderer::driver_info", "[Renderer]")
{
  CHECK(!Renderer::driver_info(-1));
  CHECK(!Renderer::driver_info(Renderer::render_drivers()));
  CHECK(Renderer::driver_info(0));
}

TEST_CASE("Renderer::get", "[Renderer]")
{
  Window window;
  Renderer renderer{window};
  CHECK(renderer.get());
}

TEST_CASE("Renderer to SDL_Renderer*", "[Renderer]")
{
  SECTION("Const")
  {
    Window window;
    const Renderer renderer{window};
    const SDL_Renderer* sdlRenderer = renderer;
    CHECK(sdlRenderer);
  }

  SECTION("Non-const")
  {
    Window window;
    Renderer renderer{window};
    SDL_Renderer* sdlRenderer = renderer;
    CHECK(sdlRenderer);
  }
}
