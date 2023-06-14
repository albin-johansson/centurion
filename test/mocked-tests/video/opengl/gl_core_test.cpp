/*
 * MIT License
 *
 * Copyright (c) 2019-2023 Albin Johansson
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

#include <array>   // array
#include <string>  // string

#include "centurion/video/opengl.hpp"
#include "core_mocks.hpp"

using namespace std::string_literals;

extern "C" {
FAKE_VOID_FUNC(SDL_GL_SwapWindow, SDL_Window*)
FAKE_VOID_FUNC(SDL_GL_GetDrawableSize, SDL_Window*, int*, int*)
FAKE_VOID_FUNC(SDL_GL_ResetAttributes)
FAKE_VOID_FUNC(SDL_GL_DeleteContext, void*)
FAKE_VALUE_FUNC(int, SDL_GL_SetSwapInterval, int)
FAKE_VALUE_FUNC(int, SDL_GL_GetSwapInterval)
FAKE_VALUE_FUNC(int, SDL_GL_SetAttribute, SDL_GLattr, int)
FAKE_VALUE_FUNC(int, SDL_GL_GetAttribute, SDL_GLattr, int*)
FAKE_VALUE_FUNC(SDL_Window*, SDL_GL_GetCurrentWindow)
FAKE_VALUE_FUNC(void*, SDL_GL_GetCurrentContext)
FAKE_VALUE_FUNC(SDL_bool, SDL_GL_ExtensionSupported, const char*)
FAKE_VALUE_FUNC(int, SDL_GL_BindTexture, SDL_Texture*, float*, float*)
FAKE_VALUE_FUNC(int, SDL_GL_UnbindTexture, SDL_Texture*)
}

class OpenGLTest : public testing::Test {
 protected:
  void SetUp() override
  {
    mocks::reset_core();

    RESET_FAKE(SDL_GL_SwapWindow)
    RESET_FAKE(SDL_GL_GetDrawableSize)
    RESET_FAKE(SDL_GL_ResetAttributes)
    RESET_FAKE(SDL_GL_DeleteContext)
    RESET_FAKE(SDL_GL_SetSwapInterval)
    RESET_FAKE(SDL_GL_GetSwapInterval)
    RESET_FAKE(SDL_GL_SetAttribute)
    RESET_FAKE(SDL_GL_GetAttribute)
    RESET_FAKE(SDL_GL_GetCurrentWindow)
    RESET_FAKE(SDL_GL_GetCurrentContext)
    RESET_FAKE(SDL_GL_ExtensionSupported)
    RESET_FAKE(SDL_GL_BindTexture)
    RESET_FAKE(SDL_GL_UnbindTexture)
  }

  cen::window_handle m_window {nullptr};
};

TEST_F(OpenGLTest, Swap)
{
  std::array flags {Uint32 {SDL_WINDOW_OPENGL}};
  SET_RETURN_SEQ(SDL_GetWindowFlags, flags.data(), cen::isize(flags));

  ASSERT_NO_FATAL_FAILURE(cen::gl::swap(m_window));
  ASSERT_EQ(1u, SDL_GL_SwapWindow_fake.call_count);
}

TEST_F(OpenGLTest, DrawableSize)
{
  std::array flags {Uint32 {SDL_WINDOW_OPENGL}};
  SET_RETURN_SEQ(SDL_GetWindowFlags, flags.data(), cen::isize(flags));

  ASSERT_NO_FATAL_FAILURE(cen::gl::drawable_size(m_window));
  ASSERT_EQ(1u, SDL_GL_GetDrawableSize_fake.call_count);
}

TEST_F(OpenGLTest, ResetAttributes)
{
  cen::gl::reset_attributes();
  ASSERT_EQ(1u, SDL_GL_ResetAttributes_fake.call_count);
}

TEST_F(OpenGLTest, Set)
{
  std::array values {-1, 0};
  SET_RETURN_SEQ(SDL_GL_SetAttribute, values.data(), cen::isize(values));

  ASSERT_EQ(cen::failure, cen::gl::set(cen::gl_attribute::buffer_size, 42));
  ASSERT_EQ(cen::success, cen::gl::set(cen::gl_attribute::buffer_size, 42));
  ASSERT_EQ(2u, SDL_GL_SetAttribute_fake.call_count);
}

TEST_F(OpenGLTest, Get)
{
  std::array values {-1, 0};
  SET_RETURN_SEQ(SDL_GL_GetAttribute, values.data(), cen::isize(values));

  ASSERT_FALSE(cen::gl::get(cen::gl_attribute::buffer_size));
  ASSERT_TRUE(cen::gl::get(cen::gl_attribute::buffer_size));
  ASSERT_EQ(2u, SDL_GL_GetAttribute_fake.call_count);
}

TEST_F(OpenGLTest, SetSwapInterval)
{
  std::array values {-1, 0};
  SET_RETURN_SEQ(SDL_GL_SetSwapInterval, values.data(), cen::isize(values));

  ASSERT_FALSE(cen::gl::set_swap_interval(cen::gl_swap_interval::immediate));
  ASSERT_TRUE(cen::gl::set_swap_interval(cen::gl_swap_interval::immediate));
  ASSERT_EQ(2u, SDL_GL_SetSwapInterval_fake.call_count);
}

TEST_F(OpenGLTest, SwapInterval)
{
  std::array values {0, 1, -1};
  SET_RETURN_SEQ(SDL_GL_GetSwapInterval, values.data(), cen::isize(values));

  ASSERT_EQ(cen::gl_swap_interval::immediate, cen::gl::swap_interval());
  ASSERT_EQ(cen::gl_swap_interval::synchronized, cen::gl::swap_interval());
  ASSERT_EQ(cen::gl_swap_interval::late_immediate, cen::gl::swap_interval());
  ASSERT_EQ(3u, SDL_GL_GetSwapInterval_fake.call_count);
}

TEST_F(OpenGLTest, GetWindow)
{
  const auto window [[maybe_unused]] = cen::gl::get_window();
  ASSERT_EQ(1u, SDL_GL_GetCurrentWindow_fake.call_count);
}

TEST_F(OpenGLTest, GetContext)
{
  const auto context [[maybe_unused]] = cen::gl::get_context();
  ASSERT_EQ(1u, SDL_GL_GetCurrentContext_fake.call_count);
}

TEST_F(OpenGLTest, IsExtensionSupported)
{
  std::array values {SDL_FALSE, SDL_TRUE};
  SET_RETURN_SEQ(SDL_GL_ExtensionSupported, values.data(), cen::isize(values));

  ASSERT_FALSE(cen::gl::is_extension_supported("foo"s));
  ASSERT_TRUE(cen::gl::is_extension_supported("foo"s));

  ASSERT_EQ(2u, SDL_GL_ExtensionSupported_fake.call_count);
}

TEST_F(OpenGLTest, Bind)
{
  std::array values {-1, 0};
  SET_RETURN_SEQ(SDL_GL_BindTexture, values.data(), cen::isize(values));

  cen::texture_handle texture {nullptr};
  ASSERT_FALSE(cen::gl::bind(texture));
  ASSERT_TRUE(cen::gl::bind(texture));
  ASSERT_EQ(2u, SDL_GL_BindTexture_fake.call_count);
}

TEST_F(OpenGLTest, Unbind)
{
  std::array values {-1, 0};
  SET_RETURN_SEQ(SDL_GL_UnbindTexture, values.data(), cen::isize(values));

  cen::texture_handle texture {nullptr};
  ASSERT_FALSE(cen::gl::unbind(texture));
  ASSERT_TRUE(cen::gl::unbind(texture));
  ASSERT_EQ(2u, SDL_GL_UnbindTexture_fake.call_count);
}
