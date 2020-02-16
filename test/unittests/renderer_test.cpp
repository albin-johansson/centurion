#include "renderer.h"

#include <stdexcept>

#include "catch.hpp"
#include "colors.h"
#include "log.h"
#include "window.h"

using namespace centurion;
using namespace centurion::video;

TEST_CASE("Renderer(SDL_Renderer*)", "[Renderer]") {
  CHECK_THROWS_AS(Renderer{nullptr}, std::invalid_argument);

  Window window;
  CHECK_NOTHROW(Renderer{window});
}

TEST_CASE("Renderer(SDL_Window*, uint32_t)", "[Renderer]") {
  Window window;
  Renderer renderer{window};

  SECTION("Check default flags") {
    const uint32_t flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    const auto correctFlags = renderer.get_flags() & flags;
    CHECK(correctFlags);
  }
}

TEST_CASE("Renderer::unique(SDL_Renderer*)", "[Renderer]") {
  CHECK_THROWS_AS(Renderer::unique(nullptr), std::invalid_argument);

  Window window;
  CHECK_NOTHROW(Renderer::unique(window.get_internal()));
}

TEST_CASE("Renderer::unique(SDL_Window*, uint32_t", "[Renderer]") {
  Window window;
  auto renderer = Renderer::unique(window.get_internal());

  SECTION("Check default flags") {
    const uint32_t flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    const auto correctFlags = renderer->get_flags() & flags;
    CHECK(correctFlags);
  }
}

TEST_CASE("Renderer::shared(SDL_Renderer*)", "[Renderer]") {
  CHECK_THROWS_AS(Renderer::shared(nullptr), std::invalid_argument);

  Window window;
  CHECK_NOTHROW(Renderer::shared(window.get_internal()));
}

TEST_CASE("Renderer::shared(SDL_Window*, uint32_t", "[Renderer]") {
  Window window;
  auto renderer = Renderer::shared(window.get_internal());

  SECTION("Check default flags") {
    const uint32_t flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    const auto correctFlags = renderer->get_flags() & flags;
    CHECK(correctFlags);
  }
}

TEST_CASE("Renderer::set_logical_size", "[Renderer]") {
  Window window;
  Renderer renderer{window};

  const auto w = 842;
  const auto h = 253;
  renderer.set_logical_size(w, h);

  CHECK(renderer.get_logical_width() == w);
  CHECK(renderer.get_logical_height() == h);
}

TEST_CASE("Renderer::set_scale", "[Renderer]") {
  Window window;
  Renderer renderer{window};

  const auto xScale = 0.8f;
  const auto yScale = 0.4f;
  renderer.set_scale(xScale, yScale);

  CHECK(renderer.get_x_scale() == xScale);
  CHECK(renderer.get_y_scale() == yScale);
}

TEST_CASE("Renderer::get_x_scale", "[Renderer]") {
  Window window;
  Renderer renderer{window};
  CHECK(renderer.get_x_scale() == 1);
}

TEST_CASE("Renderer::get_y_scale", "[Renderer]") {
  Window window;
  Renderer renderer{window};
  CHECK(renderer.get_y_scale() == 1);
}

TEST_CASE("Renderer::get_logical_width", "[Renderer]") {
  Window window;
  Renderer renderer{window};
  CHECK(renderer.get_logical_width() == 0);
}

TEST_CASE("Renderer::get_logical_height", "[Renderer]") {
  Window window;
  Renderer renderer{window};
  CHECK(renderer.get_logical_height() == 0);
}

TEST_CASE("Renderer::get_output_width", "[Renderer]") {
  Window window;
  Renderer renderer{window};
  CHECK(renderer.get_output_width() == window.get_width());
}

TEST_CASE("Renderer::get_output_height", "[Renderer]") {
  Window window;
  Renderer renderer{window};
  CHECK(renderer.get_output_height() == window.get_height());
}

TEST_CASE("Renderer::get_output_size", "[Renderer]") {
  Window window;
  Renderer renderer{window};
  const auto [width, height] = renderer.get_output_size();
  CHECK(width == window.get_width());
  CHECK(height == window.get_height());
}

TEST_CASE("Renderer::is_vsync_enabled", "[Renderer]") {
  Window window;
  Renderer renderer{window};

  const bool vsync = renderer.get_flags() & SDL_RENDERER_PRESENTVSYNC;
  CHECK(vsync == renderer.is_vsync_enabled());
}

TEST_CASE("Renderer::is_accelerated", "[Renderer]") {
  Window window;
  Renderer renderer{window};

  const bool accelerated = renderer.get_flags() & SDL_RENDERER_ACCELERATED;
  CHECK(accelerated == renderer.is_accelerated());
}

TEST_CASE("Renderer::is_software_based", "[Renderer]") {
  Window window;
  Renderer renderer{window};

  const bool software = renderer.get_flags() & SDL_RENDERER_SOFTWARE;
  CHECK(software == renderer.is_software_based());
}

TEST_CASE("Renderer::is_supporting_target_textures", "[Renderer]") {
  Window window;
  Renderer renderer{window};

  const bool targettexture = renderer.get_flags() & SDL_RENDERER_TARGETTEXTURE;
  CHECK(targettexture == renderer.is_supporting_target_textures());
}

TEST_CASE("Renderer::is_using_integer_logical_scaling", "[Renderer]") {
  Window window;
  Renderer renderer{window};

  CHECK(!renderer.is_using_integer_logical_scaling());

  renderer.set_logical_integer_scale(true);

  CHECK(renderer.is_using_integer_logical_scaling());
}

TEST_CASE("Renderer::get_color", "[Renderer]") {
  Window window;
  Renderer renderer{window};

  const auto color = renderer.get_color();
  CHECK(color.get_red() == 0);
  CHECK(color.get_green() == 0);
  CHECK(color.get_blue() == 0);
  CHECK(color.get_alpha() == 0xFF);
}

TEST_CASE("Renderer::get_viewport", "[Renderer]") {
  Window window;
  Renderer renderer{window};

  const auto viewport = renderer.get_viewport();
  CHECK(viewport.w == window.get_width());
  CHECK(viewport.h == window.get_height());
}

TEST_CASE("Renderer::set_translation_viewport", "[Renderer]") {
  Window window;
  Renderer renderer{window};

  const SDL_FRect tviewport{123, 523, 845, 541};
  renderer.set_translation_viewport(tviewport);

  CHECK(renderer.get_translation_viewport().x == tviewport.x);
  CHECK(renderer.get_translation_viewport().y == tviewport.y);
  CHECK(renderer.get_translation_viewport().w == tviewport.w);
  CHECK(renderer.get_translation_viewport().h == tviewport.h);
}

TEST_CASE("Renderer::get_translation_viewport", "[Renderer]") {
  Window window;
  Renderer renderer{window};

  const auto tviewport = renderer.get_translation_viewport();

  CHECK(tviewport.x == 0);
  CHECK(tviewport.y == 0);
  CHECK(tviewport.w == 0);
  CHECK(tviewport.h == 0);
}

#ifdef CENTURION_HAS_OPTIONAL

TEST_CASE("Renderer clipping", "[Renderer]") {
  Window window;
  Renderer renderer{window};

  SECTION("Default values") {
    CHECK(!renderer.is_clipping_enabled());
    const auto clip = renderer.get_clip();
    CHECK(!clip);
  }

  CHECK_NOTHROW(renderer.set_clip(std::nullopt));

  const SDL_Rect clip{5, 2, 75, 93};
  renderer.set_clip(clip);
  CHECK(renderer.is_clipping_enabled());

  CHECK(renderer.get_clip());
  const auto rclip = *renderer.get_clip();

  CHECK(clip.x == rclip.x);
  CHECK(clip.y == rclip.y);
  CHECK(clip.w == rclip.w);
  CHECK(clip.h == rclip.h);
}

#endif

TEST_CASE("Renderer::set_target", "[Renderer]") {
  Window window;
  Renderer renderer{window};
  CHECK_NOTHROW(renderer.set_target(nullptr));
}

TEST_CASE("Renderer::set_color(uint8_t, uint8_t, uint8_t, uint8_t)",
          "[Renderer]") {
  Window window;
  Renderer renderer{window};

  SECTION("Full parameter list") {
    const uint8_t red = 0xFA;
    const uint8_t green = 0xBB;
    const uint8_t blue = 0x39;
    const uint8_t alpha = 0x1F;
    renderer.set_color(red, green, blue, alpha);

    const auto color = renderer.get_color();

    CHECK(red == color.get_red());
    CHECK(green == color.get_green());
    CHECK(blue == color.get_blue());
    CHECK(alpha == color.get_alpha());
  }

  SECTION("Default alpha value") {
    renderer.set_color(0, 0, 0);
    const auto color = renderer.get_color();
    CHECK(0xFF == color.get_alpha());
  }
}

TEST_CASE("Renderer::to_string", "[Renderer]") {
  Window window;
  Renderer renderer{window};
  Log::msgf(Category::Test, "%s", renderer.to_string().c_str());
}