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

#include <fff.h>
#include <gtest/gtest.h>

#include <array>  // array

#include "centurion/opengl.hpp"
#include "core_mocks.hpp"

extern "C" {
FAKE_VALUE_FUNC(int, SDL_GL_LoadLibrary, const char*)
FAKE_VALUE_FUNC(void*, SDL_GL_GetProcAddress, const char*)
FAKE_VOID_FUNC(SDL_GL_UnloadLibrary)
}

class OpenGLLibraryTest : public testing::Test {
 protected:
  void SetUp() override
  {
    mocks::reset_core();

    RESET_FAKE(SDL_GL_LoadLibrary)
    RESET_FAKE(SDL_GL_GetProcAddress)
    RESET_FAKE(SDL_GL_UnloadLibrary)
  }
};

TEST_F(OpenGLLibraryTest, Construction)
{
  std::array values {-1, 0};
  SET_RETURN_SEQ(SDL_GL_LoadLibrary, values.data(), cen::isize(values));

  ASSERT_THROW(cen::gl_library library, cen::sdl_error);
  ASSERT_NO_THROW(cen::gl_library library);
}

TEST_F(OpenGLLibraryTest, AddressOf)
{
  std::array values {0};
  SET_RETURN_SEQ(SDL_GL_LoadLibrary, values.data(), cen::isize(values));

  cen::gl_library library;
  const auto* address [[maybe_unused]] = library.address_of("foo");

  ASSERT_EQ(1u, SDL_GL_GetProcAddress_fake.call_count);
}