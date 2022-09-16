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

#ifndef CENTURION_OPENGL_HPP_
#define CENTURION_OPENGL_HPP_

#ifndef CENTURION_NO_OPENGL

#include <SDL.h>

#include <cassert>      // assert
#include <memory>       // unique_ptr
#include <optional>     // optional
#include <ostream>      // ostream
#include <string>       // string
#include <string_view>  // string_view

#include "common.hpp"
#include "detail/owner_handle_api.hpp"
#include "features.hpp"
#include "math.hpp"
#include "texture.hpp"
#include "window.hpp"

namespace cen {

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
  double_buffer = SDL_GL_DOUBLEBUFFER,
  accelerated_visual = SDL_GL_ACCELERATED_VISUAL,
  retained_backing = SDL_GL_RETAINED_BACKING,
  share_with_current_context = SDL_GL_SHARE_WITH_CURRENT_CONTEXT,
  framebuffer_srgb_capable = SDL_GL_FRAMEBUFFER_SRGB_CAPABLE,

  multisample_buffers = SDL_GL_MULTISAMPLEBUFFERS,
  multisample_samples = SDL_GL_MULTISAMPLESAMPLES,

#if SDL_VERSION_ATLEAST(2, 24, 0)
  float_buffers = SDL_GL_FLOATBUFFERS,
#endif  // SDL_VERSION_ATLEAST(2, 24, 0)

  egl = SDL_GL_CONTEXT_EGL,
  context_flags = SDL_GL_CONTEXT_FLAGS,
  context_major_version = SDL_GL_CONTEXT_MAJOR_VERSION,
  context_minor_version = SDL_GL_CONTEXT_MINOR_VERSION,
  context_profile_mask = SDL_GL_CONTEXT_PROFILE_MASK,
  context_release_behavior = SDL_GL_CONTEXT_RELEASE_BEHAVIOR,
  context_reset_notification = SDL_GL_CONTEXT_RESET_NOTIFICATION,
  context_no_error = SDL_GL_CONTEXT_NO_ERROR
};

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

    case gl_attribute::context_flags:
      return "context_flags";

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

#if SDL_VERSION_ATLEAST(2, 24, 0)

    case gl_attribute::float_buffers:
      return "float_buffers";

#endif  // SDL_VERSION_ATLEAST(2, 24, 0)

    case gl_attribute::context_major_version:
      return "context_major_version";

    case gl_attribute::context_minor_version:
      return "context_minor_version";

    case gl_attribute::context_profile_mask:
      return "context_profile_mask";

    case gl_attribute::context_release_behavior:
      return "context_release_behavior";

    case gl_attribute::context_reset_notification:
      return "context_reset_notification";

    case gl_attribute::context_no_error:
      return "context_no_error";

    default:
      throw exception{"Did not recognize OpenGL attribute!"};
  }
}

inline auto operator<<(std::ostream& stream, const gl_attribute attr) -> std::ostream&
{
  return stream << to_string(attr);
}

enum class gl_swap_interval
{
  late_immediate = -1,
  immediate = 0,
  synchronized = 1,
};

[[nodiscard]] constexpr auto to_string(const gl_swap_interval interval) -> std::string_view
{
  switch (interval) {
    case gl_swap_interval::immediate:
      return "immediate";

    case gl_swap_interval::synchronized:
      return "synchronized";

    case gl_swap_interval::late_immediate:
      return "late_immediate";

    default:
      throw exception{"Did not recognize swap interval!"};
  }
}

inline auto operator<<(std::ostream& stream, const gl_swap_interval interval) -> std::ostream&
{
  return stream << to_string(interval);
}

/**
 * \brief Manages the initialization and de-initialization of an OpenGL library.
 */
class gl_library final
{
 public:
  CENTURION_DISABLE_COPY(gl_library)
  CENTURION_DISABLE_MOVE(gl_library)

  CENTURION_NODISCARD_CTOR explicit gl_library(const char* path = nullptr)
  {
    if (SDL_GL_LoadLibrary(path) == -1) {
      throw sdl_error{};
    }
  }

  ~gl_library() noexcept { SDL_GL_UnloadLibrary(); }

  [[nodiscard]] auto address_of(const char* function) const noexcept  // NOLINT
      -> void*
  {
    assert(function);
    return SDL_GL_GetProcAddress(function);
  }
};

template <typename T>
class basic_gl_context;

using gl_context = basic_gl_context<detail::owner_tag>;
using gl_context_handle = basic_gl_context<detail::handle_tag>;

/**
 * Represents an OpenGL context.
 *
 * \see cen::gl
 * \see gl_context
 * \see gl_context_handle
 */
template <typename T>
class basic_gl_context final
{
 public:
  explicit basic_gl_context(maybe_owner<SDL_GLContext> context) noexcept(detail::is_handle<T>)
      : mContext{context}
  {
    if constexpr (detail::is_owner<T>) {
      if (!mContext) {
        throw exception{"Can't create OpenGL context from null pointer!"};
      }
    }
  }

  template <typename U>
  explicit basic_gl_context(basic_window<U>& window) noexcept(detail::is_handle<T>)
      : mContext{SDL_GL_CreateContext(window.get())}
  {
    if constexpr (detail::is_owner<T>) {
      if (!mContext) {
        throw sdl_error{};
      }
    }
  }

  template <typename U>
  auto make_current(basic_window<U>& window) -> result
  {
    assert(window.is_opengl());
    return SDL_GL_MakeCurrent(window.get(), mContext.get()) == 0;
  }

  [[nodiscard]] auto get() const noexcept -> SDL_GLContext { return mContext.get(); }

 private:
  struct Deleter final
  {
    void operator()(SDL_GLContext context) noexcept { SDL_GL_DeleteContext(context); }
  };

  std::unique_ptr<void, Deleter> mContext;
};

namespace gl {

template <typename T>
void swap(basic_window<T>& window) noexcept
{
  assert(window.is_opengl());
  SDL_GL_SwapWindow(window.get());
}

template <typename T>
[[nodiscard]] auto drawable_size(const basic_window<T>& window) noexcept -> iarea
{
  assert(window.is_opengl());

  int width{};
  int height{};
  SDL_GL_GetDrawableSize(window.get(), &width, &height);

  return {width, height};
}

inline void reset_attributes() noexcept { SDL_GL_ResetAttributes(); }

inline auto set(const gl_attribute attr, const int value) noexcept -> result
{
  return SDL_GL_SetAttribute(static_cast<SDL_GLattr>(attr), value) == 0;
}

inline auto get(const gl_attribute attr) noexcept -> maybe<int>
{
  int value{};
  if (SDL_GL_GetAttribute(static_cast<SDL_GLattr>(attr), &value) == 0) {
    return value;
  }
  else {
    return nothing;
  }
}

inline auto set_swap_interval(const gl_swap_interval interval) noexcept -> result
{
  return SDL_GL_SetSwapInterval(to_underlying(interval)) == 0;
}

[[nodiscard]] inline auto swap_interval() noexcept -> gl_swap_interval
{
  return gl_swap_interval{SDL_GL_GetSwapInterval()};
}

[[nodiscard]] inline auto get_window() noexcept -> window_handle
{
  return window_handle{SDL_GL_GetCurrentWindow()};
}

[[nodiscard]] inline auto get_context() noexcept -> gl_context_handle
{
  return gl_context_handle{SDL_GL_GetCurrentContext()};
}

[[nodiscard]] inline auto is_extension_supported(const char* extension) noexcept -> bool
{
  assert(extension);
  return SDL_GL_ExtensionSupported(extension) == SDL_TRUE;
}

[[nodiscard]] inline auto is_extension_supported(const std::string& extension) noexcept -> bool
{
  return is_extension_supported(extension.c_str());
}

template <typename T>
auto bind(basic_texture<T>& texture) noexcept -> maybe<farea>
{
  float width{};
  float height{};
  if (SDL_GL_BindTexture(texture.get(), &width, &height) == 0) {
    return farea{width, height};
  }
  else {
    return nothing;
  }
}

template <typename T>
auto unbind(basic_texture<T>& texture) noexcept -> result
{
  return SDL_GL_UnbindTexture(texture.get()) == 0;
}

}  // namespace gl
}  // namespace cen

#endif  // CENTURION_NO_OPENGL
#endif  // CENTURION_OPENGL_HPP_
