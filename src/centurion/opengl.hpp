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

/// \addtogroup video
/// \{

/**
 * \defgroup opengl OpenGL
 *
 * \brief Provides utilities related to OpenGL.
 */

/// \addtogroup opengl
/// \{

/**
 * \brief Represents different OpenGL attributes.
 */
enum class gl_attribute {
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

  egl = SDL_GL_CONTEXT_EGL,
  context_flags = SDL_GL_CONTEXT_FLAGS,
  context_major_version = SDL_GL_CONTEXT_MAJOR_VERSION,
  context_minor_version = SDL_GL_CONTEXT_MINOR_VERSION,
  context_profile_mask = SDL_GL_CONTEXT_PROFILE_MASK,
  context_release_behavior = SDL_GL_CONTEXT_RELEASE_BEHAVIOR,
  context_reset_notification = SDL_GL_CONTEXT_RESET_NOTIFICATION,
  context_no_error = SDL_GL_CONTEXT_NO_ERROR
};

/// \name OpenGL attribute functions
/// \{

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

/// \} End of OpenGL attribute functions

/**
 * \brief Represents different swap interval modes.
 */
enum class gl_swap_interval {
  late_immediate = -1,
  immediate = 0,
  synchronized = 1,
};

/// \name OpenGL swap interval functions
/// \{

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

/// \} End of OpenGL swap interva functions

/**
 * \brief Manages the initialization and de-initialization of an OpenGL library.
 */
class gl_library final {
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

using gl_context = basic_gl_context<detail::owner_tag>;          ///< An owning context.
using gl_context_handle = basic_gl_context<detail::handle_tag>;  ///< A non-owning context.

/**
 * \brief Represents an OpenGL context.
 *
 * \ownerhandle `gl_context`/`gl_context_handle`
 *
 * \see `gl_context`
 * \see `gl_context_handle`
 */
template <typename T>
class basic_gl_context final {
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
  struct Deleter final {
    void operator()(SDL_GLContext context) noexcept { SDL_GL_DeleteContext(context); }
  };

  std::unique_ptr<void, Deleter> mContext;
};

/// \} End of group opengl

/// \} End of group video

/// \ingroup opengl
namespace gl {

/// \addtogroup video
/// \{

/// \addtogroup opengl OpenGL
/// \{

/**
 * \brief Swaps the buffers for an OpenGL window.
 *
 * \pre The window must be usable within an OpenGL context.
 *
 * \note This requires that double-buffering is supported.
 *
 * \param window the OpenGL window to swap the buffers for.
 */
template <typename T>
void swap(basic_window<T>& window) noexcept
{
  assert(window.is_opengl());
  SDL_GL_SwapWindow(window.get());
}

/**
 * \brief Returns the drawable size of an OpenGL window.
 *
 * \pre `window` must be an OpenGL window.
 *
 * \param window the OpenGL window that will be queried.
 *
 * \return the drawable size of the window.
 */
template <typename T>
[[nodiscard]] auto drawable_size(const basic_window<T>& window) noexcept -> iarea
{
  assert(window.is_opengl());

  int width{};
  int height{};
  SDL_GL_GetDrawableSize(window.get(), &width, &height);

  return {width, height};
}

/**
 * \brief Resets all OpenGL context attributes to their default values.
 */
inline void reset_attributes() noexcept
{
  SDL_GL_ResetAttributes();
}

/**
 * \brief Sets the value of an OpenGL context attribute.
 *
 * \param attr the attribute that will be set.
 * \param value the new value of the attribute.
 *
 * \return `success` if the attribute was set; `failure` otherwise.
 */
inline auto set(const gl_attribute attr, const int value) noexcept -> result
{
  return SDL_GL_SetAttribute(static_cast<SDL_GLattr>(attr), value) == 0;
}

/**
 * \brief Returns the current value of an OpenGL context attribute.
 *
 * \param attr the attribute to query.
 *
 * \return the value of the specified attribute; an empty optional is returned if the value
 * could not be obtained.
 */
inline auto get(const gl_attribute attr) noexcept -> std::optional<int>
{
  int value{};
  if (SDL_GL_GetAttribute(static_cast<SDL_GLattr>(attr), &value) == 0) {
    return value;
  }
  else {
    return std::nullopt;
  }
}

/**
 * \brief Sets the swap interval strategy that will be used.
 *
 * \param interval the swap interval that will be used.
 *
 * \return `success` if the swap interval set; `failure` if it isn't supported.
 */
inline auto set_swap_interval(const gl_swap_interval interval) noexcept -> result
{
  return SDL_GL_SetSwapInterval(to_underlying(interval)) == 0;
}

/**
 * \brief Returns the swap interval used by the current OpenGL context.
 *
 * \note `immediate` is returned if the swap interval cannot be determined.
 *
 * \return the current swap interval.
 */
[[nodiscard]] inline auto swap_interval() noexcept -> gl_swap_interval
{
  return gl_swap_interval{SDL_GL_GetSwapInterval()};
}

/**
 * \brief Returns a handle to the currently active OpenGL window.
 *
 * \return a potentially empty window handle.
 */
[[nodiscard]] inline auto get_window() noexcept -> window_handle
{
  return window_handle{SDL_GL_GetCurrentWindow()};
}

/**
 * \brief Returns a handle to the currently active OpenGL context.
 *
 * \return a potentially empty OpenGL context handle.
 */
[[nodiscard]] inline auto get_context() noexcept -> gl_context_handle
{
  return gl_context_handle{SDL_GL_GetCurrentContext()};
}

/**
 * \brief Indicates whether a specific extension is supported.
 *
 * \param extension the extension that will be checked.
 *
 * \return `true` if the extension is supported; `false` otherwise.
 */
[[nodiscard]] inline auto is_extension_supported(const char* extension) noexcept -> bool
{
  assert(extension);
  return SDL_GL_ExtensionSupported(extension) == SDL_TRUE;
}

/// \copydoc is_extension_supported()
[[nodiscard]] inline auto is_extension_supported(const std::string& extension) noexcept -> bool
{
  return is_extension_supported(extension.c_str());
}

/**
 * \brief Binds a texture to the current OpenGL context.
 *
 * \param texture the texture to bind.
 *
 * \return the size of the bound texture; an empty optional is returned if something goes
 * wrong.
 */
template <typename T>
auto bind(basic_texture<T>& texture) noexcept -> std::optional<farea>
{
  float width{};
  float height{};
  if (SDL_GL_BindTexture(texture.get(), &width, &height) == 0) {
    return farea{width, height};
  }
  else {
    return std::nullopt;
  }
}

/**
 * \brief Unbinds a texture from the OpenGL context.
 *
 * \param texture the texture to unbind.
 *
 * \return `success` if the texture was unbound; `failure` otherwise.
 */
template <typename T>
auto unbind(basic_texture<T>& texture) noexcept -> result
{
  return SDL_GL_UnbindTexture(texture.get()) == 0;
}

/// \} End of group opengl

/// \} End of group video

}  // namespace gl

}  // namespace cen

#endif  // CENTURION_NO_OPENGL
#endif  // CENTURION_OPENGL_HPP_
