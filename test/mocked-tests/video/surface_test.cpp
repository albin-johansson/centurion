/*
 * MIT License
 *
 * Copyright (c) 2019-2022 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "centurion/video/surface.hpp"

#include <fff.h>
#include <gtest/gtest.h>

#include <array>  // array

#include "core_mocks.hpp"

extern "C" {
FAKE_VALUE_FUNC(SDL_Surface*, SDL_ConvertSurfaceFormat, SDL_Surface*, Uint32, Uint32)
FAKE_VALUE_FUNC(int, SDL_GetSurfaceBlendMode, SDL_Surface*, SDL_BlendMode*)
FAKE_VALUE_FUNC(int, SDL_SetSurfaceBlendMode, SDL_Surface*, SDL_BlendMode)
FAKE_VALUE_FUNC(int, SDL_SetSurfaceRLE, SDL_Surface*, int)
FAKE_VALUE_FUNC(SDL_bool, SDL_HasSurfaceRLE, SDL_Surface*)
FAKE_VALUE_FUNC(SDL_Surface*, SDL_DuplicateSurface, SDL_Surface*)
}

class SurfaceTest : public testing::Test {
 protected:
  void SetUp() override
  {
    mocks::reset_core();

    RESET_FAKE(SDL_ConvertSurfaceFormat)
    RESET_FAKE(SDL_GetSurfaceBlendMode)
    RESET_FAKE(SDL_SetSurfaceBlendMode)
    RESET_FAKE(SDL_SetSurfaceRLE)
    RESET_FAKE(SDL_HasSurfaceRLE)
    RESET_FAKE(SDL_DuplicateSurface)
  }

  cen::surface m_surface;
};

TEST_F(SurfaceTest, ConvertTo)
{
  ASSERT_THROW(
      { const auto s [[maybe_unused]] = m_surface.convert_to(cen::pixel_format::rgba8888); },
      cen::sdl_error);
  ASSERT_EQ(1u, SDL_ConvertSurfaceFormat_fake.call_count);
}

TEST_F(SurfaceTest, Copy)
{
  cen::surface dst;
  ASSERT_THROW(dst = m_surface, cen::sdl_error);
  ASSERT_EQ(1u, SDL_DuplicateSurface_fake.call_count);
}

TEST_F(SurfaceTest, SetRLEHint)
{
  std::array values {-1, 0};
  SET_RETURN_SEQ(SDL_SetSurfaceRLE, values.data(), cen::isize(values));

  ASSERT_FALSE(m_surface.set_rle(true));
  ASSERT_TRUE(m_surface.set_rle(true));

  ASSERT_EQ(2u, SDL_SetSurfaceRLE_fake.call_count);
}

#if SDL_VERSION_ATLEAST(2, 0, 14)

TEST_F(SurfaceTest, IsRLEEnabled)
{
  std::array values {SDL_FALSE, SDL_TRUE};
  SET_RETURN_SEQ(SDL_HasSurfaceRLE, values.data(), cen::isize(values));

  ASSERT_FALSE(m_surface.has_rle());
  ASSERT_TRUE(m_surface.has_rle());

  ASSERT_EQ(2u, SDL_HasSurfaceRLE_fake.call_count);
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)
