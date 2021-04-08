#include "video/opengl/gl_core.hpp"

#include <gtest/gtest.h>

TEST(GLAttributeEnum, Values)
{
  const auto check = [](int expected, cen::gl::attribute attr) {
    EXPECT_EQ(expected, static_cast<int>(attr));
  };

  // clang-format off

  check(SDL_GL_RED_SIZE, cen::gl::attribute::red_size);
  check(SDL_GL_GREEN_SIZE, cen::gl::attribute::green_size);
  check(SDL_GL_BLUE_SIZE, cen::gl::attribute::blue_size);
  check(SDL_GL_ALPHA_SIZE, cen::gl::attribute::alpha_size);
  check(SDL_GL_BUFFER_SIZE, cen::gl::attribute::buffer_size);

  check(SDL_GL_DOUBLEBUFFER, cen::gl::attribute::double_buffer);

  check(SDL_GL_DEPTH_SIZE, cen::gl::attribute::depth_size);
  check(SDL_GL_STENCIL_SIZE, cen::gl::attribute::stencil_size);

  check(SDL_GL_ACCUM_RED_SIZE, cen::gl::attribute::accum_red_size);
  check(SDL_GL_ACCUM_GREEN_SIZE, cen::gl::attribute::accum_green_size);
  check(SDL_GL_ACCUM_BLUE_SIZE, cen::gl::attribute::accum_blue_size);
  check(SDL_GL_ACCUM_ALPHA_SIZE, cen::gl::attribute::accum_alpha_size);

  check(SDL_GL_STEREO, cen::gl::attribute::stereo);
  check(SDL_GL_MULTISAMPLEBUFFERS, cen::gl::attribute::multisample_buffers);
  check(SDL_GL_MULTISAMPLESAMPLES, cen::gl::attribute::multisample_samples);
  check(SDL_GL_ACCELERATED_VISUAL, cen::gl::attribute::accelerated_visual);
  check(SDL_GL_RETAINED_BACKING, cen::gl::attribute::retained_backing);

  check(SDL_GL_CONTEXT_MAJOR_VERSION, cen::gl::attribute::context_major_version);
  check(SDL_GL_CONTEXT_MINOR_VERSION, cen::gl::attribute::context_minor_version);
  check(SDL_GL_CONTEXT_PROFILE_MASK, cen::gl::attribute::context_profile_mask);
  check(SDL_GL_CONTEXT_RELEASE_BEHAVIOR, cen::gl::attribute::context_release_behaviour);
  check(SDL_GL_CONTEXT_RESET_NOTIFICATION, cen::gl::attribute::context_reset_notification);
  check(SDL_GL_CONTEXT_NO_ERROR, cen::gl::attribute::context_no_error);
  check(SDL_GL_CONTEXT_EGL, cen::gl::attribute::egl);
  check(SDL_GL_CONTEXT_FLAGS, cen::gl::attribute::flags);

  check(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, cen::gl::attribute::share_with_current_context);
  check(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE, cen::gl::attribute::framebuffer_srgb_capable);
  // clang-format on
}
