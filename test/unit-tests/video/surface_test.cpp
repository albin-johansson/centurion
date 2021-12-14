#include "video/surface.hpp"

#include <SDL_image.h>
#include <gtest/gtest.h>

#include <iostream>  // clog
#include <memory>    // unique_ptr
#include <type_traits>
#include <utility>  // move

#include "core/exception.hpp"
#include "core/logging.hpp"
#include "video/colors.hpp"
#include "video/window.hpp"

static_assert(std::is_copy_constructible_v<cen::Surface>);
static_assert(std::is_copy_assignable_v<cen::Surface>);

static_assert(std::is_nothrow_move_constructible_v<cen::Surface>);
static_assert(std::is_nothrow_move_assignable_v<cen::Surface>);

static_assert(std::is_copy_constructible_v<cen::SurfaceHandle>);
static_assert(std::is_copy_assignable_v<cen::SurfaceHandle>);

static_assert(std::is_nothrow_move_constructible_v<cen::SurfaceHandle>);
static_assert(std::is_nothrow_move_assignable_v<cen::SurfaceHandle>);

using namespace std::string_literals;

class SurfaceTest : public testing::Test {
 protected:
  static void SetUpTestSuite() { surface = std::make_unique<cen::Surface>(path); }

  static void TearDownTestSuite() { surface.reset(); }

  inline constexpr static auto path = "resources/panda.png";
  inline static std::unique_ptr<cen::Surface> surface;
};

TEST_F(SurfaceTest, PathConstructor)
{
  ASSERT_THROW(cen::Surface(""), cen::Error);
  ASSERT_THROW(cen::Surface(""s), cen::Error);
  ASSERT_NO_THROW(cen::Surface{path});
}

TEST_F(SurfaceTest, FromSDLSurfaceConstructor)
{
  ASSERT_NO_THROW(cen::Surface(IMG_Load(path)));

  SDL_Surface* ptr{};
  ASSERT_THROW(cen::Surface{ptr}, cen::Error);
}

TEST_F(SurfaceTest, SizePixelFormatConstructor)
{
  cen::window window;
  cen::Surface surface{{10, 10}, window.get_pixel_format()};
  ASSERT_EQ(10, surface.GetWidth());
  ASSERT_EQ(10, surface.GetHeight());
  ASSERT_EQ(window.get_pixel_format(), surface.GetFormatInfo().format());
}

TEST_F(SurfaceTest, CopyConstructor)
{
  const cen::Surface copy{*surface};

  ASSERT_NE(surface->get(), copy.get());
  ASSERT_TRUE(surface->get());
  ASSERT_TRUE(copy.get());
}

TEST_F(SurfaceTest, MoveConstructor)
{
  cen::Surface copy{*surface};
  const cen::Surface moved{std::move(copy)};

  ASSERT_FALSE(copy.get());
  ASSERT_TRUE(moved.get());
}

TEST_F(SurfaceTest, CopyAssignment)
{
  cen::Surface destination = *surface;

  ASSERT_NE(surface->get(), destination.get());
  ASSERT_TRUE(surface->get());
  ASSERT_TRUE(destination.get());
}

TEST_F(SurfaceTest, MoveSelfAssignment)
{
  *surface = std::move(*surface);
  ASSERT_TRUE(surface->get());
}

TEST_F(SurfaceTest, MoveAssignment)
{
  cen::Surface source{*surface};
  cen::Surface destination = std::move(source);

  ASSERT_FALSE(source.get());
  ASSERT_TRUE(destination.get());
}

TEST_F(SurfaceTest, SaveAsBMP)
{
  ASSERT_TRUE(surface->SaveAsBMP("surface_as_bmp.bmp"s));
}

TEST_F(SurfaceTest, SaveAsPNG)
{
  ASSERT_TRUE(surface->SaveAsPNG("surface_as_png.png"s));
}

TEST_F(SurfaceTest, SaveAsJPG)
{
  ASSERT_TRUE(surface->SaveAsJPG("surface_as_jpg.jpg"s, 25));
}

TEST_F(SurfaceTest, SetAlpha)
{
  const auto previous = surface->GetAlpha();

  constexpr auto alpha = 0xCF;
  surface->SetAlphaMod(alpha);

  ASSERT_EQ(alpha, surface->GetAlpha());

  surface->SetAlphaMod(previous);
}

TEST_F(SurfaceTest, SetColorMod)
{
  const auto previous = surface->GetColorMod();
  ASSERT_EQ(cen::colors::white, previous);

  constexpr auto color = cen::colors::hot_pink;
  surface->SetColorMod(color);

  ASSERT_EQ(color, surface->GetColorMod());

  surface->SetColorMod(previous);
}

TEST_F(SurfaceTest, SetBlendMode)
{
  const auto previous = surface->GetBlendMode();

  constexpr auto mode = cen::BlendMode::mod;
  surface->SetBlendMode(mode);

  ASSERT_EQ(mode, surface->GetBlendMode());

  surface->SetBlendMode(previous);
}

TEST_F(SurfaceTest, Width)
{
  ASSERT_EQ(200, surface->GetWidth());
}

TEST_F(SurfaceTest, Height)
{
  ASSERT_EQ(150, surface->GetHeight());
}

TEST_F(SurfaceTest, Size)
{
  const auto size = surface->GetSize();
  ASSERT_EQ(200, size.width);
  ASSERT_EQ(150, size.height);
}

TEST_F(SurfaceTest, Pitch)
{
  ASSERT_EQ(4 * surface->GetWidth(), surface->GetPitch());
}

TEST_F(SurfaceTest, Clip)
{
  constexpr cen::Rect rect{{48, 29}, {34, 89}};

  surface->get()->clip_rect = rect.get();
  ASSERT_EQ(rect, surface->GetClip());
}

TEST_F(SurfaceTest, GetPixelData)
{
  ASSERT_TRUE(surface->GetPixelData());

  const auto& cSurface = *surface;
  ASSERT_TRUE(cSurface.GetPixelData());
}

TEST_F(SurfaceTest, ConvertTo)
{
  cen::Surface source{path};
  source.SetBlendMode(cen::BlendMode::blend);
  source.SetAlphaMod(0xAE);
  source.SetColorMod(cen::colors::red);

  const auto format = cen::pixel_format::rgba8888;
  const cen::Surface converted = source.ConvertTo(format);

  ASSERT_EQ(format, converted.GetFormatInfo().format());
  ASSERT_EQ(source.GetBlendMode(), converted.GetBlendMode());
  ASSERT_EQ(source.GetAlpha(), converted.GetAlpha());
  ASSERT_EQ(source.GetColorMod(), converted.GetColorMod());
}

TEST_F(SurfaceTest, Get)
{
  ASSERT_TRUE(surface->get());
}

TEST_F(SurfaceTest, ToString)
{
  cen::log_info_raw(cen::to_string(*surface));
}

TEST_F(SurfaceTest, StreamOperator)
{
  std::clog << *surface << '\n';
}
