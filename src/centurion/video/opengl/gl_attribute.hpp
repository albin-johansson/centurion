#ifndef CENTURION_GL_ATTRIBUTE_HEADER
#define CENTURION_GL_ATTRIBUTE_HEADER

#ifndef CENTURION_NO_OPENGL

#include <SDL.h>
#include <SDL_opengl.h>

namespace cen {

/// \addtogroup video
/// \{

/**
 * \enum gl_attribute
 *
 * \brief Provides identifiers for different OpenGL attributes.
 *
 * \since 6.0.0
 *
 * \headerfile gl_attribute.hpp
 */
enum class gl_attribute
{
  red_size = SDL_GL_RED_SIZE,
  green_size = SDL_GL_GREEN_SIZE,
  blue_size = SDL_GL_BLUE_SIZE,
  alpha_size = SDL_GL_ALPHA_SIZE,
  buffer_size = SDL_GL_BUFFER_SIZE,
  depth_size = SDL_GL_DEPTH_SIZE,
  stencil_size = SDL_GL_STENCIL_SIZE,

  accum_red_size = SDL_GL_ACCUM_RED_SIZE,
  accum_green_size = SDL_GL_ACCUM_GREEN_SIZE,
  accum_blue_size = SDL_GL_ACCUM_BLUE_SIZE,
  accum_alpha_size = SDL_GL_ACCUM_ALPHA_SIZE,

  stereo = SDL_GL_STEREO,
  egl = SDL_GL_CONTEXT_EGL,
  flags = SDL_GL_CONTEXT_FLAGS,
  double_buffer = SDL_GL_DOUBLEBUFFER,
  accelerated_visual = SDL_GL_ACCELERATED_VISUAL,
  retained_backing = SDL_GL_RETAINED_BACKING,
  share_with_current_context = SDL_GL_SHARE_WITH_CURRENT_CONTEXT,
  framebuffer_srgb_capable = SDL_GL_FRAMEBUFFER_SRGB_CAPABLE,

  multisample_buffers = SDL_GL_MULTISAMPLEBUFFERS,
  multisample_samples = SDL_GL_MULTISAMPLESAMPLES,

  context_major_version = SDL_GL_CONTEXT_MAJOR_VERSION,
  context_minor_version = SDL_GL_CONTEXT_MINOR_VERSION,
  context_profile_mask = SDL_GL_CONTEXT_PROFILE_MASK,
  context_release_behaviour = SDL_GL_CONTEXT_RELEASE_BEHAVIOR,
  context_reset_notification = SDL_GL_CONTEXT_RESET_NOTIFICATION,
  context_no_error = SDL_GL_CONTEXT_NO_ERROR
};

/// \} End of group video

}  // namespace cen

#endif  // CENTURION_NO_OPENGL
#endif  // CENTURION_GL_ATTRIBUTE_HEADER
