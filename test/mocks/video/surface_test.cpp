#include "video/surface.hpp"

#include <fff.h>
#include <gtest/gtest.h>

#include <array>  // array

#include "core_mocks.hpp"

extern "C" {
// clang-format off
FAKE_VALUE_FUNC(SDL_Surface*, SDL_ConvertSurfaceFormat, SDL_Surface*, Uint32, Uint32)
FAKE_VALUE_FUNC(int, SDL_GetSurfaceBlendMode, SDL_Surface*, SDL_BlendMode*)
FAKE_VALUE_FUNC(int, SDL_SetSurfaceBlendMode, SDL_Surface*, SDL_BlendMode)
FAKE_VALUE_FUNC(int, SDL_SetSurfaceRLE, SDL_Surface*, int)
FAKE_VALUE_FUNC(SDL_bool, SDL_HasSurfaceRLE, SDL_Surface*)
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
    RESET_FAKE(SDL_SetSurfaceRLE);
    RESET_FAKE(SDL_HasSurfaceRLE);
    RESET_FAKE(SDL_DuplicateSurface);
  }

  cen::surface m_surface;
};

TEST_F(SurfaceTest, Convert)
{
  EXPECT_THROW(m_surface.convert(cen::pixel_format::rgba8888), cen::sdl_error);
  EXPECT_EQ(1, SDL_ConvertSurfaceFormat_fake.call_count);
}

TEST_F(SurfaceTest, Copy)
{
  cen::surface dst;
  EXPECT_THROW(dst = m_surface, cen::sdl_error);
  EXPECT_EQ(1, SDL_DuplicateSurface_fake.call_count);
}

TEST_F(SurfaceTest, SetRLEHint)
{
  std::array values{-1, 0};
  SET_RETURN_SEQ(SDL_SetSurfaceRLE, values.data(), cen::isize(values));

  EXPECT_FALSE(m_surface.set_rle_hint(true));
  EXPECT_TRUE(m_surface.set_rle_hint(true));

  EXPECT_EQ(2, SDL_SetSurfaceRLE_fake.call_count);
}

#if SDL_VERSION_ATLEAST(2, 0, 14)

TEST_F(SurfaceTest, IsRLEEnabled)
{
  std::array values{SDL_FALSE, SDL_TRUE};
  SET_RETURN_SEQ(SDL_HasSurfaceRLE, values.data(), cen::isize(values));

  EXPECT_FALSE(m_surface.is_rle_enabled());
  EXPECT_TRUE(m_surface.is_rle_enabled());

  EXPECT_EQ(2, SDL_HasSurfaceRLE_fake.call_count);
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)
