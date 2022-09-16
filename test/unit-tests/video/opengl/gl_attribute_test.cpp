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

#include <gtest/gtest.h>

#include <iostream>  // cout

#include "centurion/opengl.hpp"

using attr = cen::gl_attribute;

TEST(GLAttribute, Values)
{
  ASSERT_EQ(SDL_GL_RED_SIZE, to_underlying(attr::red_size));
  ASSERT_EQ(SDL_GL_GREEN_SIZE, to_underlying(attr::green_size));
  ASSERT_EQ(SDL_GL_BLUE_SIZE, to_underlying(attr::blue_size));
  ASSERT_EQ(SDL_GL_ALPHA_SIZE, to_underlying(attr::alpha_size));
  ASSERT_EQ(SDL_GL_BUFFER_SIZE, to_underlying(attr::buffer_size));

  ASSERT_EQ(SDL_GL_DOUBLEBUFFER, to_underlying(attr::double_buffer));

  ASSERT_EQ(SDL_GL_DEPTH_SIZE, to_underlying(attr::depth_size));
  ASSERT_EQ(SDL_GL_STENCIL_SIZE, to_underlying(attr::stencil_size));

  ASSERT_EQ(SDL_GL_ACCUM_RED_SIZE, to_underlying(attr::accum_red_size));
  ASSERT_EQ(SDL_GL_ACCUM_GREEN_SIZE, to_underlying(attr::accum_green_size));
  ASSERT_EQ(SDL_GL_ACCUM_BLUE_SIZE, to_underlying(attr::accum_blue_size));
  ASSERT_EQ(SDL_GL_ACCUM_ALPHA_SIZE, to_underlying(attr::accum_alpha_size));

  ASSERT_EQ(SDL_GL_STEREO, to_underlying(attr::stereo));
  ASSERT_EQ(SDL_GL_MULTISAMPLEBUFFERS, to_underlying(attr::multisample_buffers));
  ASSERT_EQ(SDL_GL_MULTISAMPLESAMPLES, to_underlying(attr::multisample_samples));
  ASSERT_EQ(SDL_GL_ACCELERATED_VISUAL, to_underlying(attr::accelerated_visual));
  ASSERT_EQ(SDL_GL_RETAINED_BACKING, to_underlying(attr::retained_backing));

  ASSERT_EQ(SDL_GL_CONTEXT_MAJOR_VERSION, to_underlying(attr::context_major_version));
  ASSERT_EQ(SDL_GL_CONTEXT_MINOR_VERSION, to_underlying(attr::context_minor_version));
  ASSERT_EQ(SDL_GL_CONTEXT_PROFILE_MASK, to_underlying(attr::context_profile_mask));
  ASSERT_EQ(SDL_GL_CONTEXT_RELEASE_BEHAVIOR, to_underlying(attr::context_release_behavior));
  ASSERT_EQ(SDL_GL_CONTEXT_RESET_NOTIFICATION,
            to_underlying(attr::context_reset_notification));
  ASSERT_EQ(SDL_GL_CONTEXT_NO_ERROR, to_underlying(attr::context_no_error));
  ASSERT_EQ(SDL_GL_CONTEXT_EGL, to_underlying(attr::egl));
  ASSERT_EQ(SDL_GL_CONTEXT_FLAGS, to_underlying(attr::context_flags));

  ASSERT_EQ(SDL_GL_SHARE_WITH_CURRENT_CONTEXT,
            to_underlying(attr::share_with_current_context));
  ASSERT_EQ(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE, to_underlying(attr::framebuffer_srgb_capable));

#if SDL_VERSION_ATLEAST(2, 24, 0)
  ASSERT_EQ(SDL_GL_FLOATBUFFERS, to_underlying(attr::float_buffers));
#endif  // SDL_VERSION_ATLEAST(2, 24, 0)
}

TEST(GLAttribute, ToString)
{
  ASSERT_EQ("red_size", to_string(attr::red_size));
  ASSERT_EQ("green_size", to_string(attr::green_size));
  ASSERT_EQ("blue_size", to_string(attr::blue_size));
  ASSERT_EQ("alpha_size", to_string(attr::alpha_size));
  ASSERT_EQ("buffer_size", to_string(attr::buffer_size));

  ASSERT_EQ("double_buffer", to_string(attr::double_buffer));

  ASSERT_EQ("depth_size", to_string(attr::depth_size));
  ASSERT_EQ("stencil_size", to_string(attr::stencil_size));

  ASSERT_EQ("accum_red_size", to_string(attr::accum_red_size));
  ASSERT_EQ("accum_green_size", to_string(attr::accum_green_size));
  ASSERT_EQ("accum_blue_size", to_string(attr::accum_blue_size));
  ASSERT_EQ("accum_alpha_size", to_string(attr::accum_alpha_size));

  ASSERT_EQ("stereo", to_string(attr::stereo));
  ASSERT_EQ("multisample_buffers", to_string(attr::multisample_buffers));
  ASSERT_EQ("multisample_samples", to_string(attr::multisample_samples));
  ASSERT_EQ("accelerated_visual", to_string(attr::accelerated_visual));
  ASSERT_EQ("retained_backing", to_string(attr::retained_backing));

  ASSERT_EQ("context_major_version", to_string(attr::context_major_version));
  ASSERT_EQ("context_minor_version", to_string(attr::context_minor_version));
  ASSERT_EQ("context_profile_mask", to_string(attr::context_profile_mask));
  ASSERT_EQ("context_release_behavior", to_string(attr::context_release_behavior));
  ASSERT_EQ("context_reset_notification", to_string(attr::context_reset_notification));
  ASSERT_EQ("context_no_error", to_string(attr::context_no_error));

  ASSERT_EQ("egl", to_string(attr::egl));
  ASSERT_EQ("context_flags", to_string(attr::context_flags));

  ASSERT_EQ("share_with_current_context", to_string(attr::share_with_current_context));
  ASSERT_EQ("framebuffer_srgb_capable", to_string(attr::framebuffer_srgb_capable));

#if SDL_VERSION_ATLEAST(2, 24, 0)
  ASSERT_EQ("float_buffers", to_string(attr::float_buffers));
#endif  // SDL_VERSION_ATLEAST(2, 24, 0)

  std::cout << "gl_attribute::double_buffer == " << attr::double_buffer << '\n';
}
