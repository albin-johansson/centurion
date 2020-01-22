#include "catch.hpp"
#include <iostream>
#include "colors.h"
#include "image.h"
#include "window.h"
#include "renderer.h"
#include "centurion_exception.h"

using namespace centurion;

static constexpr auto path = "resources/grass.png";

TEST_CASE("Image(string)", "[Image]") {
  Window window;
  Renderer renderer{window};

  CHECK_THROWS_AS(Image(renderer, "badpath"), CenturionException);

  Image img{renderer, path};

  CHECK(img.get_width() == 108);
  CHECK(img.get_height() == 108);
}

TEST_CASE("Image(Image&&)", "[Image]") {
  Window window;
  Renderer renderer{window};
  Image img{renderer, path};

  Image moved_img = std::move(img);

  CHECK(!img.get_texture());
}

TEST_CASE("Image::get_format", "[Image]") {
  Window window;
  Renderer renderer{window};
  Image img{renderer, path};
  SDL_Texture* texture = img.get_texture();

  uint32_t format = 0;
  SDL_QueryTexture(texture, &format, nullptr, nullptr, nullptr);

  CHECK(img.get_format() == format);
}

TEST_CASE("Image::get_access", "[Image]") {
  Window window;
  Renderer renderer{window};
  Image img{renderer, path};
  SDL_Texture* texture = img.get_texture();

  int access = 0;
  SDL_QueryTexture(texture, nullptr, &access, nullptr, nullptr);

  CHECK(img.get_access() == static_cast<TextureAccess>(access));
}

TEST_CASE("Image::get_width", "[Image]") {
  Window window;
  Renderer renderer{window};
  Image img(renderer, path);
  SDL_Texture* texture = img.get_texture();

  CHECK(img.get_width() == 108);

  int width = 0;
  SDL_QueryTexture(texture, nullptr, nullptr, &width, nullptr);
  CHECK(img.get_width() == width);
}

TEST_CASE("Image::get_height", "[Image]") {
  Window window;
  Renderer renderer{window};
  Image img{renderer, path};
  SDL_Texture* texture = img.get_texture();

  CHECK(img.get_height() == 108);

  int height = 0;
  SDL_QueryTexture(texture, nullptr, nullptr, nullptr, &height);
  CHECK(img.get_height() == height);
}

TEST_CASE("Image::set_blend_mode", "[Image]") {
  Window window;
  Renderer renderer{window};
  Image img{renderer, path};

  const auto mode = BlendMode::Blend;
  img.set_blend_mode(mode);

  CHECK(mode == img.get_blend_mode());
}

TEST_CASE("Image::set_alpha", "[Image]") {
  Window window;
  Renderer renderer{window};
  Image img{renderer, path};

  const auto alpha = 0x3A;
  img.set_alpha(alpha);

  CHECK(alpha == img.get_alpha());
}

TEST_CASE("Image::set_color_mod", "[Image]") {
  Window window;
  Renderer renderer{window};
  Image img{renderer, path};

  const auto color = Colors::misty_rose;
  img.set_color_mod(color);

  const auto actual = img.get_color_mod();
  CHECK(color.get_red() == actual.get_red());
  CHECK(color.get_green() == actual.get_green());
  CHECK(color.get_blue() == actual.get_blue());
  CHECK(color.get_alpha() == actual.get_alpha());
}

TEST_CASE("Image::is_static", "[Image]") {
  Window window;
  Renderer renderer{window};
  Image img{renderer, window.get_pixel_format(), TextureAccess::Static, 10, 10};
  CHECK(img.is_static());
}

TEST_CASE("Image::is_streaming", "[Image]") {
  Window window;
  Renderer renderer{window};
  Image img{renderer, window.get_pixel_format(), TextureAccess::Streaming, 10, 10};
  CHECK(img.is_streaming());
}

TEST_CASE("Image::is_target", "[Image]") {
  Window window;
  Renderer renderer{window};
  Image img{renderer, window.get_pixel_format(), TextureAccess::Target, 10, 10};
  CHECK(img.is_target());
}

TEST_CASE("Image << operator", "[Image]") {
  Window window;
  Renderer renderer{window};
  Image img{renderer, path};

  std::cout << img << "\n";
}

TEST_CASE("TextureAccess enum values", "[TextureAccess]") {
  CHECK(TextureAccess::Static == SDL_TEXTUREACCESS_STATIC);
  CHECK(TextureAccess::Streaming == SDL_TEXTUREACCESS_STREAMING);
  CHECK(TextureAccess::Target == SDL_TEXTUREACCESS_TARGET);

  CHECK(SDL_TEXTUREACCESS_STATIC == TextureAccess::Static);
  CHECK(SDL_TEXTUREACCESS_STREAMING == TextureAccess::Streaming);
  CHECK(SDL_TEXTUREACCESS_TARGET == TextureAccess::Target);
}
