#include <gtest/gtest.h>

#include "video/opengl/gl_core.hpp"

TEST(GLAttributeEnum, Values)
{
  const auto check = [](int expected, cen::gl_attribute attr) {
    EXPECT_EQ(expected, static_cast<int>(attr));
  };

  // clang-format off

  check(SDL_GL_RED_SIZE, cen::gl_attribute::red_size);
  check(SDL_GL_GREEN_SIZE, cen::gl_attribute::green_size);
  check(SDL_GL_BLUE_SIZE, cen::gl_attribute::blue_size);
  check(SDL_GL_ALPHA_SIZE, cen::gl_attribute::alpha_size);
  check(SDL_GL_BUFFER_SIZE, cen::gl_attribute::buffer_size);

  check(SDL_GL_DOUBLEBUFFER, cen::gl_attribute::double_buffer);

  check(SDL_GL_DEPTH_SIZE, cen::gl_attribute::depth_size);
  check(SDL_GL_STENCIL_SIZE, cen::gl_attribute::stencil_size);

  check(SDL_GL_ACCUM_RED_SIZE, cen::gl_attribute::accum_red_size);
  check(SDL_GL_ACCUM_GREEN_SIZE, cen::gl_attribute::accum_green_size);
  check(SDL_GL_ACCUM_BLUE_SIZE, cen::gl_attribute::accum_blue_size);
  check(SDL_GL_ACCUM_ALPHA_SIZE, cen::gl_attribute::accum_alpha_size);

  check(SDL_GL_STEREO, cen::gl_attribute::stereo);
  check(SDL_GL_MULTISAMPLEBUFFERS, cen::gl_attribute::multisample_buffers);
  check(SDL_GL_MULTISAMPLESAMPLES, cen::gl_attribute::multisample_samples);
  check(SDL_GL_ACCELERATED_VISUAL, cen::gl_attribute::accelerated_visual);
  check(SDL_GL_RETAINED_BACKING, cen::gl_attribute::retained_backing);

  check(SDL_GL_CONTEXT_MAJOR_VERSION, cen::gl_attribute::context_major_version);
  check(SDL_GL_CONTEXT_MINOR_VERSION, cen::gl_attribute::context_minor_version);
  check(SDL_GL_CONTEXT_PROFILE_MASK, cen::gl_attribute::context_profile_mask);
  check(SDL_GL_CONTEXT_RELEASE_BEHAVIOR, cen::gl_attribute::context_release_behaviour);
  check(SDL_GL_CONTEXT_RESET_NOTIFICATION, cen::gl_attribute::context_reset_notification);
  check(SDL_GL_CONTEXT_NO_ERROR, cen::gl_attribute::context_no_error);
  check(SDL_GL_CONTEXT_EGL, cen::gl_attribute::egl);
  check(SDL_GL_CONTEXT_FLAGS, cen::gl_attribute::flags);

  check(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, cen::gl_attribute::share_with_current_context);
  check(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE, cen::gl_attribute::framebuffer_srgb_capable);
  // clang-format on
}
