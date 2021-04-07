#ifndef CENTURION_OPENGL_HEADER
#define CENTURION_OPENGL_HEADER

#ifndef CENTURION_NO_OPENGL

#include <SDL.h>

#include <cassert>   // assert
#include <optional>  // optional
#include <string>    // string

#include "../../misc/czstring.hpp"
#include "../../misc/exception.hpp"
#include "../../misc/not_null.hpp"
#include "../window.hpp"
#include "context.hpp"

namespace cen {

/**
 * \enum gl_attribute
 *
 * \brief Provides identifiers for different OpenGL attributes.
 *
 * \since 6.0.0
 *
 * \headerfile opengl.hpp
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

namespace gl {

/**
 * \class library
 *
 * \brief Manages the initialization and de-initialization of an OpenGL library.
 *
 * \since 6.0.0
 *
 * \headerfile opengl.hpp
 */
class library final
{
 public:
  /**
   * \brief Loads an OpenGL library.
   *
   * \param path the file path to the OpenGL library that will be used; null
   * indicates that the default library will be used.
   *
   * \throws sdl_error if the OpenGL library can't be loaded.
   *
   * \since 6.0.0
   */
  explicit library(const czstring path = nullptr)
  {
    if (SDL_GL_LoadLibrary(path) == -1)
    {
      throw sdl_error{};
    }
  }

  library(const library&) = delete;
  library(library&&) = delete;

  auto operator=(const library&) -> library& = delete;
  auto operator=(library&&) -> library& = delete;

  ~library() noexcept
  {
    SDL_GL_UnloadLibrary();
  }

  // clang-format off

  /**
   * \brief Returns the address of an OpenGL function.
   *
   * \details This function must be used to retrieve OpenGL functions after
   * loading the library at runtime.
   *
   * \note Be sure to declare your function pointers with `APIENTRY` to ensure
   * the correct calling convention on different platforms, which avoids stack
   * corruption.
   *
   * \param function the name of the function to obtain the address of.
   *
   * \return the address of the specified function; null if something went
   * wrong.
   *
   * \since 6.0.0
   */
  [[nodiscard]] auto address_of(const not_null<czstring> function) const noexcept // NOLINT
      -> void*
  {
    assert(function);
    return SDL_GL_GetProcAddress(function);
  }

  // clang-format on
};

// clang-format off

[[nodiscard]] inline auto is_extension_supported(const not_null<czstring> extension) noexcept
    -> bool
{
  assert(extension);
  return SDL_GL_ExtensionSupported(extension) == SDL_TRUE;
}

[[nodiscard]] inline auto is_extension_supported(const std::string& extension) noexcept
    -> bool
{
  return is_extension_supported(extension.c_str());
}

// clang-format on

inline void reset_attributes() noexcept
{
  SDL_GL_ResetAttributes();
}

inline auto set_attribute(const gl_attribute attribute, const int value) -> bool
{
  return SDL_GL_SetAttribute(static_cast<SDL_GLattr>(attribute), value) == 0;
}

inline auto get_attribute(const gl_attribute attribute) noexcept
    -> std::optional<int>
{
  int value{};
  if (SDL_GL_GetAttribute(static_cast<SDL_GLattr>(attribute), &value) == 0)
  {
    return value;
  }
  else
  {
    return std::nullopt;
  }
}

[[nodiscard]] inline auto get_window() noexcept -> window_handle
{
  return window_handle{SDL_GL_GetCurrentWindow()};
}

[[nodiscard]] inline auto get_context() noexcept -> context_handle
{
  return context_handle{SDL_GL_GetCurrentContext()};
}

template <typename T>
[[nodiscard]] auto drawable_size(const basic_window<T>& window) noexcept
    -> iarea
{
  int width{};
  int height{};
  SDL_GL_GetDrawableSize(window.get(), &width, &height);
  return {width, height};
}

inline auto set_swap_interval(const int interval) noexcept -> bool
{
  return SDL_GL_SetSwapInterval(interval) == 0;
}

[[nodiscard]] inline auto swap_interval() noexcept -> int
{
  return SDL_GL_GetSwapInterval();
}

/**
 * \brief Swaps the buffers for an OpenGL window.
 *
 * \pre The window must be usable within an OpenGL context.
 *
 * \note This requires that double-buffering is supported.
 *
 * \param window the OpenGL window to swap the buffers for.
 *
 * \since 6.0.0
 */
template <typename T>
void swap(basic_window<T>& window) noexcept
{
  assert(window.is_opengl());
  SDL_GL_SwapWindow(window.get());
}

}  // namespace gl
}  // namespace cen

#endif  // CENTURION_NO_OPENGL
#endif  // CENTURION_OPENGL_HEADER
