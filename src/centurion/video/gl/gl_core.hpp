#ifndef CENTURION_GL_CORE_HEADER
#define CENTURION_GL_CORE_HEADER

#ifndef CENTURION_NO_OPENGL

#include <SDL.h>
#include <SDL_opengl.h>

#include <cassert>   // assert
#include <optional>  // optional
#include <string>    // string

#include "../../misc/czstring.hpp"
#include "../../misc/not_null.hpp"
#include "../window.hpp"
#include "gl_attribute.hpp"
#include "gl_context.hpp"

/// \addtogroup video
/// \{

/**
 * \namespace cen::gl
 *
 * \brief Contains OpenGL-related components.
 *
 * \since 6.0.0
 */
namespace cen::gl {

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

template <typename T>
[[nodiscard]] auto drawable_size(const basic_window<T>& window) noexcept
    -> iarea
{
  assert(window.is_opengl());

  int width{};
  int height{};
  SDL_GL_GetDrawableSize(window.get(), &width, &height);

  return {width, height};
}

inline void reset_attributes() noexcept
{
  SDL_GL_ResetAttributes();
}

inline auto set(const gl_attribute attribute, const int value) noexcept -> bool
{
  return SDL_GL_SetAttribute(static_cast<SDL_GLattr>(attribute), value) == 0;
}

inline auto get(const gl_attribute attribute) noexcept -> std::optional<int>
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

inline auto set_swap_interval(const int interval) noexcept -> bool
{
  return SDL_GL_SetSwapInterval(interval) == 0;
}

[[nodiscard]] inline auto swap_interval() noexcept -> int
{
  return SDL_GL_GetSwapInterval();
}

[[nodiscard]] inline auto get_window() noexcept -> window_handle
{
  return window_handle{SDL_GL_GetCurrentWindow()};
}

[[nodiscard]] inline auto get_context() noexcept -> context_handle
{
  return context_handle{SDL_GL_GetCurrentContext()};
}

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

}  // namespace cen::gl

/// \} End of group video

#endif  // CENTURION_NO_OPENGL
#endif  // CENTURION_GL_CORE_HEADER
