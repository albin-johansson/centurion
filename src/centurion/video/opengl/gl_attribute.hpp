#ifndef CENTURION_GL_ATTRIBUTE_HEADER
#define CENTURION_GL_ATTRIBUTE_HEADER

#ifndef CENTURION_NO_OPENGL

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../../core/exception.hpp"

namespace cen {

/// \addtogroup video
/// \{

/**
 * \enum gl_attribute
 *
 * \brief Provides identifiers for different OpenGL attributes.
 *
 * \since 6.0.0
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

/// \name String conversions
/// \{

/**
 * \brief Returns a textual version of the supplied OpenGL attribute.
 *
 * \details This function returns a string that mirrors the name of the enumerator, e.g.
 * `to_string(gl_attribute::flags) == "flags"`.
 *
 * \param attr the enumerator that will be converted.
 *
 * \return a string that mirrors the name of the enumerator.
 *
 * \throws cen_error if the enumerator is not recognized.
 *
 * \since 6.2.0
 */
[[nodiscard]] constexpr auto to_string(const gl_attribute attr) -> std::string_view
{
  switch (attr) {
    case gl_attribute::red_size:
      return "red_size";

    case gl_attribute::green_size:
      return "green_size";

    case gl_attribute::blue_size:
      return "blue_size";

    case gl_attribute::alpha_size:
      return "alpha_size";

    case gl_attribute::buffer_size:
      return "buffer_size";

    case gl_attribute::depth_size:
      return "depth_size";

    case gl_attribute::stencil_size:
      return "stencil_size";

    case gl_attribute::accum_red_size:
      return "accum_red_size";

    case gl_attribute::accum_green_size:
      return "accum_green_size";

    case gl_attribute::accum_blue_size:
      return "accum_blue_size";

    case gl_attribute::accum_alpha_size:
      return "accum_alpha_size";

    case gl_attribute::stereo:
      return "stereo";

    case gl_attribute::egl:
      return "egl";

    case gl_attribute::flags:
      return "flags";

    case gl_attribute::double_buffer:
      return "double_buffer";

    case gl_attribute::accelerated_visual:
      return "accelerated_visual";

    case gl_attribute::retained_backing:
      return "retained_backing";

    case gl_attribute::share_with_current_context:
      return "share_with_current_context";

    case gl_attribute::framebuffer_srgb_capable:
      return "framebuffer_srgb_capable";

    case gl_attribute::multisample_buffers:
      return "multisample_buffers";

    case gl_attribute::multisample_samples:
      return "multisample_samples";

    case gl_attribute::context_major_version:
      return "context_major_version";

    case gl_attribute::context_minor_version:
      return "context_minor_version";

    case gl_attribute::context_profile_mask:
      return "context_profile_mask";

    case gl_attribute::context_release_behaviour:
      return "context_release_behaviour";

    case gl_attribute::context_reset_notification:
      return "context_reset_notification";

    case gl_attribute::context_no_error:
      return "context_no_error";

    default:
      throw cen_error{"Did not recognize OpenGL attribute!"};
  }
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of an OpenGL attribute enumerator.
 *
 * \param stream the output stream that will be used.
 * \param attr the enumerator that will be printed.
 *
 * \see `to_string(gl_attribute)`
 *
 * \return the used stream.
 *
 * \since 6.2.0
 */
inline auto operator<<(std::ostream& stream, const gl_attribute attr) -> std::ostream&
{
  return stream << to_string(attr);
}

/// \} End of streaming

/// \} End of group video

}  // namespace cen

#endif  // CENTURION_NO_OPENGL
#endif  // CENTURION_GL_ATTRIBUTE_HEADER
