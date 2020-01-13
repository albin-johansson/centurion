#include "catch.hpp"
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

TEST_CASE("Image::GetFormat", "[Image]") {
  Window window;
  Renderer renderer{window};
  Image img{renderer, path};
  SDL_Texture* texture = img.get_texture();

  uint32_t format = 0;
  SDL_QueryTexture(texture, &format, nullptr, nullptr, nullptr);

  CHECK(img.get_format() == format);
}

TEST_CASE("Image::GetAccess", "[Image]") {
  Window window;
  Renderer renderer{window};
  Image img{renderer, path};
  SDL_Texture* texture = img.get_texture();

  int access = 0;
  SDL_QueryTexture(texture, nullptr, &access, nullptr, nullptr);

  CHECK(img.get_access() == access);
}

TEST_CASE("Image::GetWidth", "[Image]") {
  Window window;
  Renderer renderer{window};
  Image img(renderer, path);
  SDL_Texture* texture = img.get_texture();

  CHECK(img.get_width() == 108);

  int width = 0;
  SDL_QueryTexture(texture, nullptr, nullptr, &width, nullptr);
  CHECK(img.get_width() == width);
}

TEST_CASE("Image::GetHeight", "[Image]") {
  Window window;
  Renderer renderer{window};
  Image img{renderer, path};
  SDL_Texture* texture = img.get_texture();

  CHECK(img.get_height() == 108);

  int height = 0;
  SDL_QueryTexture(texture, nullptr, nullptr, nullptr, &height);
  CHECK(img.get_height() == height);
}