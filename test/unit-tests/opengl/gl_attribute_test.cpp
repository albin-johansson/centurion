#include <gtest/gtest.h>

#include <iostream>  // clog

#include "common.hpp"
#include "opengl.hpp"

TEST(GLAttribute, Values)
{
  // clang-format off
  ASSERT_EQ(SDL_GL_RED_SIZE, cen::ToUnderlying(cen::gl_attribute::red_size));
  ASSERT_EQ(SDL_GL_GREEN_SIZE, cen::ToUnderlying(cen::gl_attribute::green_size));
  ASSERT_EQ(SDL_GL_BLUE_SIZE, cen::ToUnderlying(cen::gl_attribute::blue_size));
  ASSERT_EQ(SDL_GL_ALPHA_SIZE, cen::ToUnderlying(cen::gl_attribute::alpha_size));
  ASSERT_EQ(SDL_GL_BUFFER_SIZE, cen::ToUnderlying(cen::gl_attribute::buffer_size));

  ASSERT_EQ(SDL_GL_DOUBLEBUFFER, cen::ToUnderlying(cen::gl_attribute::double_buffer));

  ASSERT_EQ(SDL_GL_DEPTH_SIZE, cen::ToUnderlying(cen::gl_attribute::depth_size));
  ASSERT_EQ(SDL_GL_STENCIL_SIZE, cen::ToUnderlying(cen::gl_attribute::stencil_size));

  ASSERT_EQ(SDL_GL_ACCUM_RED_SIZE, cen::ToUnderlying(cen::gl_attribute::accum_red_size));
  ASSERT_EQ(SDL_GL_ACCUM_GREEN_SIZE, cen::ToUnderlying(cen::gl_attribute::accum_green_size));
  ASSERT_EQ(SDL_GL_ACCUM_BLUE_SIZE, cen::ToUnderlying(cen::gl_attribute::accum_blue_size));
  ASSERT_EQ(SDL_GL_ACCUM_ALPHA_SIZE, cen::ToUnderlying(cen::gl_attribute::accum_alpha_size));

  ASSERT_EQ(SDL_GL_STEREO, cen::ToUnderlying(cen::gl_attribute::stereo));
  ASSERT_EQ(SDL_GL_MULTISAMPLEBUFFERS, cen::ToUnderlying(cen::gl_attribute::multisample_buffers));
  ASSERT_EQ(SDL_GL_MULTISAMPLESAMPLES, cen::ToUnderlying(cen::gl_attribute::multisample_samples));
  ASSERT_EQ(SDL_GL_ACCELERATED_VISUAL, cen::ToUnderlying(cen::gl_attribute::accelerated_visual));
  ASSERT_EQ(SDL_GL_RETAINED_BACKING, cen::ToUnderlying(cen::gl_attribute::retained_backing));

  ASSERT_EQ(SDL_GL_CONTEXT_MAJOR_VERSION, cen::ToUnderlying(cen::gl_attribute::context_major_version));
  ASSERT_EQ(SDL_GL_CONTEXT_MINOR_VERSION, cen::ToUnderlying(cen::gl_attribute::context_minor_version));
  ASSERT_EQ(SDL_GL_CONTEXT_PROFILE_MASK, cen::ToUnderlying(cen::gl_attribute::context_profile_mask));
  ASSERT_EQ(SDL_GL_CONTEXT_RELEASE_BEHAVIOR, cen::ToUnderlying(cen::gl_attribute::context_release_behaviour));
  ASSERT_EQ(SDL_GL_CONTEXT_RESET_NOTIFICATION, cen::ToUnderlying(cen::gl_attribute::context_reset_notification));
  ASSERT_EQ(SDL_GL_CONTEXT_NO_ERROR, cen::ToUnderlying(cen::gl_attribute::context_no_error));
  ASSERT_EQ(SDL_GL_CONTEXT_EGL, cen::ToUnderlying(cen::gl_attribute::egl));
  ASSERT_EQ(SDL_GL_CONTEXT_FLAGS, cen::ToUnderlying(cen::gl_attribute::flags));

  ASSERT_EQ(SDL_GL_SHARE_WITH_CURRENT_CONTEXT,cen::ToUnderlying(cen::gl_attribute::share_with_current_context));
  ASSERT_EQ(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE, cen::ToUnderlying(cen::gl_attribute::framebuffer_srgb_capable));
  // clang-format on
}

TEST(GLAttribute, ToString)
{
  // clang-format off
  ASSERT_EQ("red_size", cen::to_string(cen::gl_attribute::red_size));
  ASSERT_EQ("green_size", cen::to_string(cen::gl_attribute::green_size));
  ASSERT_EQ("blue_size", cen::to_string(cen::gl_attribute::blue_size));
  ASSERT_EQ("alpha_size", cen::to_string(cen::gl_attribute::alpha_size));
  ASSERT_EQ("buffer_size", cen::to_string(cen::gl_attribute::buffer_size));

  ASSERT_EQ("double_buffer", cen::to_string(cen::gl_attribute::double_buffer));

  ASSERT_EQ("depth_size", cen::to_string(cen::gl_attribute::depth_size));
  ASSERT_EQ("stencil_size", cen::to_string(cen::gl_attribute::stencil_size));

  ASSERT_EQ("accum_red_size", cen::to_string(cen::gl_attribute::accum_red_size));
  ASSERT_EQ("accum_green_size", cen::to_string(cen::gl_attribute::accum_green_size));
  ASSERT_EQ("accum_blue_size", cen::to_string(cen::gl_attribute::accum_blue_size));
  ASSERT_EQ("accum_alpha_size", cen::to_string(cen::gl_attribute::accum_alpha_size));

  ASSERT_EQ("stereo", cen::to_string(cen::gl_attribute::stereo));
  ASSERT_EQ("multisample_buffers", cen::to_string(cen::gl_attribute::multisample_buffers));
  ASSERT_EQ("multisample_samples", cen::to_string(cen::gl_attribute::multisample_samples));
  ASSERT_EQ("accelerated_visual", cen::to_string(cen::gl_attribute::accelerated_visual));
  ASSERT_EQ("retained_backing", cen::to_string(cen::gl_attribute::retained_backing));

  ASSERT_EQ("context_major_version", cen::to_string(cen::gl_attribute::context_major_version));
  ASSERT_EQ("context_minor_version", cen::to_string(cen::gl_attribute::context_minor_version));
  ASSERT_EQ("context_profile_mask", cen::to_string(cen::gl_attribute::context_profile_mask));
  ASSERT_EQ("context_release_behaviour", cen::to_string(cen::gl_attribute::context_release_behaviour));
  ASSERT_EQ("context_reset_notification", cen::to_string(cen::gl_attribute::context_reset_notification));
  ASSERT_EQ("context_no_error", cen::to_string(cen::gl_attribute::context_no_error));

  ASSERT_EQ("egl", cen::to_string(cen::gl_attribute::egl));
  ASSERT_EQ("flags", cen::to_string(cen::gl_attribute::flags));

  ASSERT_EQ("share_with_current_context", cen::to_string(cen::gl_attribute::share_with_current_context));
  ASSERT_EQ("framebuffer_srgb_capable", cen::to_string(cen::gl_attribute::framebuffer_srgb_capable));
  // clang-format on

  std::clog << "OpenGL attribute example: " << cen::gl_attribute::double_buffer << '\n';
}
