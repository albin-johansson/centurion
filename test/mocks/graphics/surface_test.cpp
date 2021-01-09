#include "surface.hpp"

#include <fff.h>
#include <gtest/gtest.h>

#include "core_mocks.hpp"

extern "C" {
// clang-format off
FAKE_VALUE_FUNC(SDL_Surface*, SDL_ConvertSurfaceFormat, SDL_Surface*, Uint32, Uint32)
FAKE_VALUE_FUNC(int, SDL_GetSurfaceBlendMode, SDL_Surface*, SDL_BlendMode*)
FAKE_VALUE_FUNC(int, SDL_SetSurfaceBlendMode, SDL_Surface*, SDL_BlendMode)
FAKE_VALUE_FUNC(SDL_Surface*, SDL_DuplicateSurface, SDL_Surface*)
// clang-format on
}

class SurfaceTest : public testing::Test
{
 protected:
  void SetUp() override
  {
    mocks::reset_core();

    RESET_FAKE(SDL_ConvertSurfaceFormat);
    RESET_FAKE(SDL_GetSurfaceBlendMode);
    RESET_FAKE(SDL_SetSurfaceBlendMode);
    RESET_FAKE(SDL_DuplicateSurface);
  }
};

TEST_F(SurfaceTest, Convert)
{
  const cen::surface surface;
  EXPECT_THROW(surface.convert(cen::pixel_format::rgba8888), cen::sdl_error);
  EXPECT_EQ(1, SDL_ConvertSurfaceFormat_fake.call_count);
}

TEST_F(SurfaceTest, Copy)
{
  const cen::surface src;
  cen::surface dst;
  EXPECT_THROW(dst = src, cen::sdl_error);
  EXPECT_EQ(1, SDL_DuplicateSurface_fake.call_count);
}


