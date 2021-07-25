#include "video/surface.hpp"

#include <SDL_image.h>
#include <gtest/gtest.h>

#include <iostream>  // clog
#include <memory>    // unique_ptr
#include <type_traits>
#include <utility>  // move

#include "core/exception.hpp"
#include "core/log.hpp"
#include "video/colors.hpp"
#include "video/window.hpp"

static_assert(std::is_copy_constructible_v<cen::surface>);
static_assert(std::is_copy_assignable_v<cen::surface>);

static_assert(std::is_nothrow_move_constructible_v<cen::surface>);
static_assert(std::is_nothrow_move_assignable_v<cen::surface>);

static_assert(std::is_copy_constructible_v<cen::surface_handle>);
static_assert(std::is_copy_assignable_v<cen::surface_handle>);

static_assert(std::is_nothrow_move_constructible_v<cen::surface_handle>);
static_assert(std::is_nothrow_move_assignable_v<cen::surface_handle>);

using namespace std::string_literals;

class SurfaceTest : public testing::Test
{
 protected:
  static void SetUpTestSuite()
  {
    m_surface = std::make_unique<cen::surface>(m_path);
  }

  static void TearDownTestSuite()
  {
    m_surface.reset();
  }

  inline constexpr static auto m_path = "resources/panda.png";
  inline static std::unique_ptr<cen::surface> m_surface;
};

TEST_F(SurfaceTest, PathConstructor)
{
  ASSERT_THROW(cen::surface(""), cen::cen_error);
  ASSERT_THROW(cen::surface(""s), cen::cen_error);
  ASSERT_NO_THROW(cen::surface{m_path});
}

TEST_F(SurfaceTest, FromSDLSurfaceConstructor)
{
  ASSERT_NO_THROW(cen::surface(IMG_Load(m_path)));

  SDL_Surface* ptr{};
  ASSERT_THROW(cen::surface{ptr}, cen::cen_error);
}

TEST_F(SurfaceTest, SizePixelFormatConstructor)
{
  cen::window window;
  cen::surface surface{{10, 10}, window.get_pixel_format()};
  ASSERT_EQ(10, surface.width());
  ASSERT_EQ(10, surface.height());
  ASSERT_EQ(window.get_pixel_format(), surface.format_info().format());
}

TEST_F(SurfaceTest, CopyConstructor)
{
  const cen::surface copy{*m_surface};

  ASSERT_NE(m_surface->get(), copy.get());
  ASSERT_TRUE(m_surface->get());
  ASSERT_TRUE(copy.get());
}

TEST_F(SurfaceTest, MoveConstructor)
{
  cen::surface surface{*m_surface};
  const cen::surface other{std::move(surface)};

  ASSERT_FALSE(surface.get());
  ASSERT_TRUE(other.get());
}

TEST_F(SurfaceTest, CopyAssignment)
{
  cen::surface destination = *m_surface;

  ASSERT_NE(m_surface->get(), destination.get());
  ASSERT_TRUE(m_surface->get());
  ASSERT_TRUE(destination.get());
}

TEST_F(SurfaceTest, MoveSelfAssignment)
{
  *m_surface = std::move(*m_surface);
  ASSERT_TRUE(m_surface->get());
}

TEST_F(SurfaceTest, MoveAssignment)
{
  cen::surface source{*m_surface};
  cen::surface destination = std::move(source);

  ASSERT_FALSE(source.get());
  ASSERT_TRUE(destination.get());
}

TEST_F(SurfaceTest, SaveAsBMP)
{
  ASSERT_TRUE(m_surface->save_as_bmp("surface_as_bmp.bmp"s));
}

TEST_F(SurfaceTest, SaveAsPNG)
{
  ASSERT_TRUE(m_surface->save_as_png("surface_as_png.png"s));
}

TEST_F(SurfaceTest, SaveAsJPG)
{
  ASSERT_TRUE(m_surface->save_as_jpg("surface_as_jpg.jpg"s, 25));
}

TEST_F(SurfaceTest, SetPixel)
{
  constexpr auto color = cen::colors::red;

  ASSERT_NO_THROW(m_surface->set_pixel({-1, 0}, color));
  ASSERT_NO_THROW(m_surface->set_pixel({0, -1}, color));
  ASSERT_NO_THROW(m_surface->set_pixel({m_surface->width(), 0}, color));
  ASSERT_NO_THROW(m_surface->set_pixel({0, m_surface->height()}, color));

  ASSERT_NO_THROW(m_surface->set_pixel({43, 12}, color));
}

TEST_F(SurfaceTest, SetAlpha)
{
  const auto previous = m_surface->alpha();

  constexpr auto alpha = 0xCF;
  m_surface->set_alpha(alpha);

  ASSERT_EQ(alpha, m_surface->alpha());

  m_surface->set_alpha(previous);
}

TEST_F(SurfaceTest, SetColorMod)
{
  const auto previous = m_surface->color_mod();

  constexpr auto color = cen::colors::hot_pink;
  m_surface->set_color_mod(color);

  ASSERT_EQ(color, m_surface->color_mod());

  m_surface->set_color_mod(previous);
}

TEST_F(SurfaceTest, SetBlendMode)
{
  const auto previous = m_surface->get_blend_mode();

  constexpr auto mode = cen::blend_mode::mod;
  m_surface->set_blend_mode(mode);

  ASSERT_EQ(mode, m_surface->get_blend_mode());

  m_surface->set_blend_mode(previous);
}

TEST_F(SurfaceTest, Width)
{
  ASSERT_EQ(200, m_surface->width());
}

TEST_F(SurfaceTest, Height)
{
  ASSERT_EQ(150, m_surface->height());
}

TEST_F(SurfaceTest, Size)
{
  const auto size = m_surface->size();
  ASSERT_EQ(200, size.width);
  ASSERT_EQ(150, size.height);
}

TEST_F(SurfaceTest, Pitch)
{
  ASSERT_EQ(4 * m_surface->width(), m_surface->pitch());
}

TEST_F(SurfaceTest, Clip)
{
  constexpr cen::irect rect{{48, 29}, {34, 89}};

  m_surface->get()->clip_rect = rect.get();
  ASSERT_EQ(rect, m_surface->clip());
}

TEST_F(SurfaceTest, Pixels)
{
  ASSERT_TRUE(m_surface->pixels());

  const auto& cSurface = *m_surface;
  ASSERT_TRUE(cSurface.pixels());
}

TEST_F(SurfaceTest, Data)
{
  ASSERT_TRUE(m_surface->data());

  const auto& cSurface = *m_surface;
  ASSERT_TRUE(cSurface.data());
}

TEST_F(SurfaceTest, Convert)
{
  cen::surface source{m_path};
  source.set_blend_mode(cen::blend_mode::blend);
  source.set_alpha(0xAE);
  source.set_color_mod(cen::colors::red);

  const auto pixelFormat = cen::pixel_format::rgba8888;
  const cen::surface converted = source.convert(pixelFormat);

  ASSERT_EQ(source.get_blend_mode(), converted.get_blend_mode());
  ASSERT_EQ(source.alpha(), converted.alpha());
  ASSERT_EQ(source.color_mod(), converted.color_mod());
}

TEST_F(SurfaceTest, Get)
{
  ASSERT_TRUE(m_surface->get());
}

TEST_F(SurfaceTest, ConvertToPointer)
{
  ASSERT_TRUE(m_surface->operator SDL_Surface*());
  ASSERT_TRUE(m_surface->operator const SDL_Surface*());
}

TEST_F(SurfaceTest, ToString)
{
  cen::log::put(cen::to_string(*m_surface));
}

TEST_F(SurfaceTest, StreamOperator)
{
  std::clog << *m_surface << '\n';
}
