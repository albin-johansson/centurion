#include "video/surface.hpp"

#include <SDL_image.h>
#include <gtest/gtest.h>

#include <iostream>  // cout
#include <memory>    // unique_ptr
#include <type_traits>
#include <utility>  // move

#include "exception.hpp"
#include "video/colors.hpp"
#include "log.hpp"

static_assert(std::is_copy_constructible_v<cen::surface>);
static_assert(std::is_copy_assignable_v<cen::surface>);

static_assert(std::is_nothrow_move_constructible_v<cen::surface>);
static_assert(std::is_nothrow_move_assignable_v<cen::surface>);

static_assert(std::is_copy_constructible_v<cen::surface_handle>);
static_assert(std::is_copy_assignable_v<cen::surface_handle>);

static_assert(std::is_nothrow_move_constructible_v<cen::surface_handle>);
static_assert(std::is_nothrow_move_assignable_v<cen::surface_handle>);

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
  using namespace std::string_literals;
  EXPECT_THROW(cen::surface(""), cen::cen_error);
  EXPECT_THROW(cen::surface(""s), cen::cen_error);
  EXPECT_NO_THROW(cen::surface{m_path});
}

TEST_F(SurfaceTest, FromSDLSurfaceConstructor)
{
  EXPECT_NO_THROW(cen::surface(IMG_Load(m_path)));

  SDL_Surface* ptr{};
  EXPECT_THROW(cen::surface{ptr}, cen::cen_error);
}

TEST_F(SurfaceTest, SizePixelFormatConstructor)
{
  EXPECT_THROW(cen::surface({-1, -1}, cen::pixel_format::rgba8888),
               cen::sdl_error);

  cen::surface surface{{10, 10}, cen::pixel_format::rgba8888};
  EXPECT_EQ(10, surface.width());
  EXPECT_EQ(10, surface.height());
  EXPECT_EQ(cen::pixel_format::rgba8888, surface.format_info().format());
}

TEST_F(SurfaceTest, CopyConstructor)
{
  const cen::surface copy{*m_surface};

  EXPECT_NE(m_surface->get(), copy.get());
  EXPECT_TRUE(m_surface->get());
  EXPECT_TRUE(copy.get());
}

TEST_F(SurfaceTest, MoveConstructor)
{
  cen::surface surface{*m_surface};
  const cen::surface other{std::move(surface)};

  EXPECT_FALSE(surface.get());
  EXPECT_TRUE(other.get());
}

TEST_F(SurfaceTest, CopyAssignment)
{
  cen::surface destination = *m_surface;

  EXPECT_NE(m_surface->get(), destination.get());
  EXPECT_TRUE(m_surface->get());
  EXPECT_TRUE(destination.get());
}

TEST_F(SurfaceTest, MoveSelfAssignment)
{
  *m_surface = std::move(*m_surface);
  EXPECT_TRUE(m_surface->get());
}

TEST_F(SurfaceTest, MoveAssignment)
{
  cen::surface source{*m_surface};
  cen::surface destination = std::move(source);

  EXPECT_FALSE(source.get());
  EXPECT_TRUE(destination.get());
}

TEST_F(SurfaceTest, SetPixel)
{
  constexpr auto color = cen::colors::red;

  EXPECT_NO_THROW(m_surface->set_pixel({-1, 0}, color));
  EXPECT_NO_THROW(m_surface->set_pixel({0, -1}, color));
  EXPECT_NO_THROW(m_surface->set_pixel({m_surface->width(), 0}, color));
  EXPECT_NO_THROW(m_surface->set_pixel({0, m_surface->height()}, color));

  EXPECT_NO_THROW(m_surface->set_pixel({43, 12}, color));
}

TEST_F(SurfaceTest, SetAlpha)
{
  const auto previous = m_surface->alpha();

  constexpr auto alpha = 0xCF;
  m_surface->set_alpha(alpha);

  EXPECT_EQ(alpha, m_surface->alpha());

  m_surface->set_alpha(previous);
}

TEST_F(SurfaceTest, SetColorMod)
{
  const auto previous = m_surface->color_mod();

  constexpr auto color = cen::colors::hot_pink;
  m_surface->set_color_mod(color);

  EXPECT_EQ(color, m_surface->color_mod());

  m_surface->set_color_mod(previous);
}

TEST_F(SurfaceTest, SetBlendMode)
{
  const auto previous = m_surface->get_blend_mode();

  constexpr auto mode = cen::blend_mode::mod;
  m_surface->set_blend_mode(mode);

  EXPECT_EQ(mode, m_surface->get_blend_mode());

  m_surface->set_blend_mode(previous);
}

TEST_F(SurfaceTest, Width)
{
  EXPECT_EQ(200, m_surface->width());
}

TEST_F(SurfaceTest, Height)
{
  EXPECT_EQ(150, m_surface->height());
}

TEST_F(SurfaceTest, Size)
{
  const auto size = m_surface->size();
  EXPECT_EQ(200, size.width);
  EXPECT_EQ(150, size.height);
}

TEST_F(SurfaceTest, Pitch)
{
  EXPECT_EQ(4 * m_surface->width(), m_surface->pitch());
}

TEST_F(SurfaceTest, Clip)
{
  constexpr cen::irect rect{{48, 29}, {34, 89}};

  m_surface->get()->clip_rect = rect.get();
  EXPECT_EQ(rect, m_surface->clip());
}

TEST_F(SurfaceTest, Pixels)
{
  EXPECT_TRUE(m_surface->pixels());

  const auto& cSurface = *m_surface;
  EXPECT_TRUE(cSurface.pixels());
}

TEST_F(SurfaceTest, Data)
{
  EXPECT_TRUE(m_surface->data());

  const auto& cSurface = *m_surface;
  EXPECT_TRUE(cSurface.data());
}

TEST_F(SurfaceTest, Convert)
{
  cen::surface source{m_path};
  source.set_blend_mode(cen::blend_mode::blend);
  source.set_alpha(0xAE);
  source.set_color_mod(cen::colors::red);

  const auto pixelFormat = cen::pixel_format::rgba8888;
  const cen::surface converted = source.convert(pixelFormat);

  EXPECT_EQ(source.get_blend_mode(), converted.get_blend_mode());
  EXPECT_EQ(source.alpha(), converted.alpha());
  EXPECT_EQ(source.color_mod(), converted.color_mod());
}

TEST_F(SurfaceTest, Get)
{
  EXPECT_TRUE(m_surface->get());
}

TEST_F(SurfaceTest, ConvertToPointer)
{
  EXPECT_TRUE(m_surface->operator SDL_Surface*());
  EXPECT_TRUE(m_surface->operator const SDL_Surface*());
}

TEST_F(SurfaceTest, ToString)
{
  cen::log::put(cen::to_string(*m_surface));
}

TEST_F(SurfaceTest, StreamOperator)
{
  std::cout << "COUT: " << *m_surface << '\n';
}
