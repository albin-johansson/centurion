#include "catch.hpp"
#include "colors.h"
#include "image.h"
#include "window.h"
#include "renderer.h"
#include "centurion_exception.h"
#include "log.h"
#include "system.h"

using namespace centurion;
using namespace centurion::video;

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

TEST_CASE("Image(gsl::not_null<SDL_Renderer*>, PixelFormat, TextureAccess, int, int)", "[Image]") {
  Window window;
  Renderer renderer{window};
  CHECK_NOTHROW(Image{renderer, PixelFormat::RGBA32, TextureAccess::Static, 50, 50});
}

TEST_CASE("Image::unique", "[Image]") {
  const Window window;
  const Renderer renderer{window};
  CHECK_THROWS_AS(Image::unique(nullptr), CenturionException);
  CHECK(Image::unique(renderer, path));
  CHECK(Image::unique(renderer, window.get_pixel_format(), TextureAccess::Static, 100, 100));
  CHECK(Image::unique(renderer,
                      static_cast<PixelFormat>(window.get_pixel_format()),
                      TextureAccess::Static, 100, 100));
}

TEST_CASE("Image:::shared", "[Image]") {
  const Window window;
  const Renderer renderer{window};
  CHECK_THROWS_AS(Image::shared(nullptr), CenturionException);
  CHECK(Image::shared(renderer, path));
  CHECK(Image::shared(renderer, window.get_pixel_format(), TextureAccess::Static, 100, 100));
  CHECK(Image::shared(renderer,
                      static_cast<PixelFormat>(window.get_pixel_format()),
                      TextureAccess::Static, 100, 100));
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

  const auto color = misty_rose;
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

TEST_CASE("Image::to_string", "[Image]") {
  Window window;
  Renderer renderer{window};
  Image img{renderer, path};
  Log::msgf(Category::Test, "%s", img.to_string().c_str());
}

TEST_CASE("TextureAccess enum values", "[TextureAccess]") {
  CHECK(TextureAccess::Static == SDL_TEXTUREACCESS_STATIC);
  CHECK(TextureAccess::Streaming == SDL_TEXTUREACCESS_STREAMING);
  CHECK(TextureAccess::Target == SDL_TEXTUREACCESS_TARGET);

  CHECK(SDL_TEXTUREACCESS_STATIC == TextureAccess::Static);
  CHECK(SDL_TEXTUREACCESS_STREAMING == TextureAccess::Streaming);
  CHECK(SDL_TEXTUREACCESS_TARGET == TextureAccess::Target);
}

TEST_CASE("PixelFormat enum values", "[PixelFormat]") {
  SECTION("CTN left and SDL right") {
    CHECK(PixelFormat::Unknown == SDL_PIXELFORMAT_UNKNOWN);
    CHECK(PixelFormat::Index1LSB == SDL_PIXELFORMAT_INDEX1LSB);
    CHECK(PixelFormat::Index1MSB == SDL_PIXELFORMAT_INDEX1MSB);
    CHECK(PixelFormat::Index4LSB == SDL_PIXELFORMAT_INDEX4LSB);
    CHECK(PixelFormat::Index4MSB == SDL_PIXELFORMAT_INDEX4MSB);
    CHECK(PixelFormat::Index8 == SDL_PIXELFORMAT_INDEX8);

    CHECK(PixelFormat::RGB332 == SDL_PIXELFORMAT_RGB332);
    CHECK(PixelFormat::RGB444 == SDL_PIXELFORMAT_RGB444);
    CHECK(PixelFormat::RGB555 == SDL_PIXELFORMAT_RGB555);
    CHECK(PixelFormat::BGR555 == SDL_PIXELFORMAT_BGR555);

    CHECK(PixelFormat::ARGB4444 == SDL_PIXELFORMAT_ARGB4444);
    CHECK(PixelFormat::RGBA4444 == SDL_PIXELFORMAT_RGBA4444);
    CHECK(PixelFormat::ABGR4444 == SDL_PIXELFORMAT_ABGR4444);
    CHECK(PixelFormat::BGRA4444 == SDL_PIXELFORMAT_BGRA4444);

    CHECK(PixelFormat::ARGB1555 == SDL_PIXELFORMAT_ARGB1555);
    CHECK(PixelFormat::RGBA5551 == SDL_PIXELFORMAT_RGBA5551);
    CHECK(PixelFormat::ABGR1555 == SDL_PIXELFORMAT_ABGR1555);
    CHECK(PixelFormat::BGRA5551 == SDL_PIXELFORMAT_BGRA5551);

    CHECK(PixelFormat::RGB565 == SDL_PIXELFORMAT_RGB565);
    CHECK(PixelFormat::BGR565 == SDL_PIXELFORMAT_BGR565);

    CHECK(PixelFormat::RGB24 == SDL_PIXELFORMAT_RGB24);
    CHECK(PixelFormat::BGR24 == SDL_PIXELFORMAT_BGR24);

    CHECK(PixelFormat::RGB888 == SDL_PIXELFORMAT_RGB888);
    CHECK(PixelFormat::RGBX8888 == SDL_PIXELFORMAT_RGBX8888);
    CHECK(PixelFormat::BGR888 == SDL_PIXELFORMAT_BGR888);
    CHECK(PixelFormat::BGRX8888 == SDL_PIXELFORMAT_BGRX8888);

    CHECK(PixelFormat::ARGB8888 == SDL_PIXELFORMAT_ARGB8888);
    CHECK(PixelFormat::RGBA8888 == SDL_PIXELFORMAT_RGBA8888);
    CHECK(PixelFormat::ABGR8888 == SDL_PIXELFORMAT_ABGR8888);
    CHECK(PixelFormat::BGRA8888 == SDL_PIXELFORMAT_BGRA8888);

    CHECK(PixelFormat::ARGB2101010 == SDL_PIXELFORMAT_ARGB2101010);

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    CHECK(PixelFormat::RGBA32 == SDL_PIXELFORMAT_RGBA8888);
    CHECK(PixelFormat::ARGB32 == SDL_PIXELFORMAT_ARGB8888);
    CHECK(PixelFormat::BGRA32 == SDL_PIXELFORMAT_BGRA8888);
    CHECK(PixelFormat::ABGR32 == SDL_PIXELFORMAT_ABGR8888);
#else
    CHECK(PixelFormat::RGBA32 == SDL_PIXELFORMAT_ABGR8888);
    CHECK(PixelFormat::ARGB32 == SDL_PIXELFORMAT_BGRA8888);
    CHECK(PixelFormat::BGRA32 == SDL_PIXELFORMAT_ARGB8888);
    CHECK(PixelFormat::ABGR32 == SDL_PIXELFORMAT_RGBA8888);
#endif

    CHECK(PixelFormat::YV12 == SDL_PIXELFORMAT_YV12);
    CHECK(PixelFormat::IYUV == SDL_PIXELFORMAT_IYUV);
    CHECK(PixelFormat::YUY2 == SDL_PIXELFORMAT_YUY2);
    CHECK(PixelFormat::UYVY == SDL_PIXELFORMAT_UYVY);
    CHECK(PixelFormat::YVYU == SDL_PIXELFORMAT_YVYU);
    CHECK(PixelFormat::NV12 == SDL_PIXELFORMAT_NV12);
    CHECK(PixelFormat::NV21 == SDL_PIXELFORMAT_NV21);
    CHECK(PixelFormat::ExternalOES == SDL_PIXELFORMAT_EXTERNAL_OES);
  }

  SECTION("CTN right and SDL left") {
    CHECK(SDL_PIXELFORMAT_UNKNOWN == PixelFormat::Unknown);
    CHECK(SDL_PIXELFORMAT_INDEX1LSB == PixelFormat::Index1LSB);
    CHECK(SDL_PIXELFORMAT_INDEX1MSB == PixelFormat::Index1MSB);
    CHECK(SDL_PIXELFORMAT_INDEX4LSB == PixelFormat::Index4LSB);
    CHECK(SDL_PIXELFORMAT_INDEX4MSB == PixelFormat::Index4MSB);
    CHECK(SDL_PIXELFORMAT_INDEX8 == PixelFormat::Index8);

    CHECK(SDL_PIXELFORMAT_RGB332 == PixelFormat::RGB332);
    CHECK(SDL_PIXELFORMAT_RGB444 == PixelFormat::RGB444);
    CHECK(SDL_PIXELFORMAT_RGB555 == PixelFormat::RGB555);
    CHECK(SDL_PIXELFORMAT_BGR555 == PixelFormat::BGR555);

    CHECK(SDL_PIXELFORMAT_ARGB4444 == PixelFormat::ARGB4444);
    CHECK(SDL_PIXELFORMAT_RGBA4444 == PixelFormat::RGBA4444);
    CHECK(SDL_PIXELFORMAT_ABGR4444 == PixelFormat::ABGR4444);
    CHECK(SDL_PIXELFORMAT_BGRA4444 == PixelFormat::BGRA4444);

    CHECK(SDL_PIXELFORMAT_ARGB1555 == PixelFormat::ARGB1555);
    CHECK(SDL_PIXELFORMAT_RGBA5551 == PixelFormat::RGBA5551);
    CHECK(SDL_PIXELFORMAT_ABGR1555 == PixelFormat::ABGR1555);
    CHECK(SDL_PIXELFORMAT_BGRA5551 == PixelFormat::BGRA5551);

    CHECK(SDL_PIXELFORMAT_RGB565 == PixelFormat::RGB565);
    CHECK(SDL_PIXELFORMAT_BGR565 == PixelFormat::BGR565);

    CHECK(SDL_PIXELFORMAT_RGB24 == PixelFormat::RGB24);
    CHECK(SDL_PIXELFORMAT_BGR24 == PixelFormat::BGR24);

    CHECK(SDL_PIXELFORMAT_RGB888 == PixelFormat::RGB888);
    CHECK(SDL_PIXELFORMAT_RGBX8888 == PixelFormat::RGBX8888);
    CHECK(SDL_PIXELFORMAT_BGR888 == PixelFormat::BGR888);
    CHECK(SDL_PIXELFORMAT_BGRX8888 == PixelFormat::BGRX8888);

    CHECK(SDL_PIXELFORMAT_ARGB8888 == PixelFormat::ARGB8888);
    CHECK(SDL_PIXELFORMAT_RGBA8888 == PixelFormat::RGBA8888);
    CHECK(SDL_PIXELFORMAT_ABGR8888 == PixelFormat::ABGR8888);
    CHECK(SDL_PIXELFORMAT_BGRA8888 == PixelFormat::BGRA8888);

    CHECK(SDL_PIXELFORMAT_ARGB2101010 == PixelFormat::ARGB2101010);

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    CHECK(SDL_PIXELFORMAT_RGBA8888 == PixelFormat::RGBA32);
    CHECK(SDL_PIXELFORMAT_ARGB8888 == PixelFormat::ARGB32);
    CHECK(SDL_PIXELFORMAT_BGRA8888 == PixelFormat::BGRA32);
    CHECK(SDL_PIXELFORMAT_ABGR8888 == PixelFormat::ABGR32);
#else
    CHECK(SDL_PIXELFORMAT_ABGR8888 == PixelFormat::RGBA32);
    CHECK(SDL_PIXELFORMAT_BGRA8888 == PixelFormat::ARGB32);
    CHECK(SDL_PIXELFORMAT_ARGB8888 == PixelFormat::BGRA32);
    CHECK(SDL_PIXELFORMAT_RGBA8888 == PixelFormat::ABGR32);
#endif

    CHECK(SDL_PIXELFORMAT_YV12 == PixelFormat::YV12);
    CHECK(SDL_PIXELFORMAT_IYUV == PixelFormat::IYUV);
    CHECK(SDL_PIXELFORMAT_YUY2 == PixelFormat::YUY2);
    CHECK(SDL_PIXELFORMAT_UYVY == PixelFormat::UYVY);
    CHECK(SDL_PIXELFORMAT_YVYU == PixelFormat::YVYU);
    CHECK(SDL_PIXELFORMAT_NV12 == PixelFormat::NV12);
    CHECK(SDL_PIXELFORMAT_NV21 == PixelFormat::NV21);
    CHECK(SDL_PIXELFORMAT_EXTERNAL_OES == PixelFormat::ExternalOES);
  }
}