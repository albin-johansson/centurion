#include "surface.hpp"

#include <SDL_image.h>
#include <gtest/gtest.h>

#include <iostream>  // cout
#include <utility>   // move

#include "colors.hpp"
#include "exception.hpp"
#include "log.hpp"

namespace {
inline constexpr auto path = "resources/panda.png";
}

TEST(Surface, PathConstructor)
{
  EXPECT_THROW(cen::surface(""), cen::exception);
  EXPECT_NO_THROW(cen::surface{path});
}

TEST(Surface, FromSDLSurfaceConstructor)
{
  EXPECT_NO_THROW(cen::surface(IMG_Load(path)));

  SDL_Surface* ptr{};
  EXPECT_THROW(cen::surface{ptr}, cen::exception);
}

TEST(Surface, CopyConstructor)
{
  const cen::surface source{path};
  const cen::surface copy{source};

  EXPECT_NE(source.get(), copy.get());
  EXPECT_TRUE(source.get());
  EXPECT_TRUE(copy.get());
}

TEST(Surface, MoveConstructor)
{
  cen::surface surface{path};
  const cen::surface other{std::move(surface)};

  EXPECT_FALSE(surface.get());
  EXPECT_TRUE(other.get());
}

TEST(Surface, CopyAssignment)
{
  const cen::surface source{path};
  cen::surface destination{path};

  destination = source;

  EXPECT_NE(source.get(), destination.get());
  EXPECT_TRUE(source.get());
  EXPECT_TRUE(destination.get());
}

TEST(Surface, MoveSelfAssignment)
{
  cen::surface surface{path};

  surface = std::move(surface);
  EXPECT_TRUE(surface.get());
}

TEST(Surface, MoveAssignment)
{
  cen::surface source{path};
  cen::surface destination{path};

  destination = std::move(source);

  EXPECT_FALSE(source.get());
  EXPECT_TRUE(destination.get());
}

TEST(Surface, SetPixel)
{
  cen::surface surface{path};

  constexpr auto color = cen::colors::red;

  EXPECT_NO_THROW(surface.set_pixel({-1, 0}, color));
  EXPECT_NO_THROW(surface.set_pixel({0, -1}, color));
  EXPECT_NO_THROW(surface.set_pixel({surface.width(), 0}, color));
  EXPECT_NO_THROW(surface.set_pixel({0, surface.height()}, color));

  EXPECT_NO_THROW(surface.set_pixel({43, 12}, color));
}

TEST(Surface, SetAlpha)
{
  cen::surface surface{path};

  constexpr auto alpha = 0xCF;
  surface.set_alpha(alpha);

  EXPECT_EQ(surface.alpha(), alpha);
}

TEST(Surface, SetColorMod)
{
  cen::surface surface{path};

  constexpr auto color = cen::colors::hot_pink;
  surface.set_color_mod(color);

  EXPECT_EQ(surface.color_mod(), color);
}

TEST(Surface, SetBlendMode)
{
  cen::surface surface{path};

  constexpr auto mode = cen::blend_mode::mod;
  surface.set_blend_mode(mode);

  EXPECT_EQ(surface.get_blend_mode(), mode);
}

TEST(Surface, Width)
{
  const cen::surface surface{path};
  EXPECT_EQ(surface.width(), 200);
}

TEST(Surface, Height)
{
  const cen::surface surface{path};
  EXPECT_EQ(surface.height(), 150);
}

TEST(Surface, Pitch)
{
  const cen::surface surface{path};
  EXPECT_EQ(surface.pitch(), 4 * surface.width());
}

TEST(Surface, Clip)
{
  constexpr cen::irect rect{{48, 29}, {34, 89}};

  cen::surface surface{path};
  SDL_Surface* ptr = surface.get();

  ptr->clip_rect = rect.get();
  EXPECT_EQ(surface.clip(), rect);
}

TEST(Surface, Pixels)
{
  cen::surface surface{path};
  EXPECT_TRUE(surface.pixels());

  const auto& cSurface = surface;
  EXPECT_TRUE(cSurface.pixels());
}

TEST(Surface, Convert)
{
  cen::surface source{path};
  source.set_blend_mode(cen::blend_mode::blend);
  source.set_alpha(0xAE);
  source.set_color_mod(cen::colors::red);

  const auto pixelFormat = cen::pixel_format::rgba8888;
  const cen::surface converted = source.convert(pixelFormat);

  EXPECT_EQ(source.get_blend_mode(), converted.get_blend_mode());
  EXPECT_EQ(source.alpha(), converted.alpha());
  EXPECT_EQ(source.color_mod(), converted.color_mod());
}

TEST(Surface, Get)
{
  const cen::surface surface{path};
  EXPECT_TRUE(surface.get());
}

TEST(Surface, ConvertToPointer)
{
  cen::surface surface{path};
  EXPECT_TRUE(surface.operator SDL_Surface*());
  EXPECT_TRUE(surface.operator const SDL_Surface*());
}

TEST(Surface, ToString)
{
  const cen::surface surface{path};
  cen::log::put(cen::to_string(surface));
}

TEST(Surface, StreamOperator)
{
  const cen::surface surface{path};
  std::cout << "COUT: " << surface << '\n';
}
