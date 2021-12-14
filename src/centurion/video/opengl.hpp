#ifndef CENTURION_VIDEO_OPENGL_HPP_
#define CENTURION_VIDEO_OPENGL_HPP_

#ifndef CENTURION_NO_OPENGL

#include <SDL.h>

#include <cassert>      // assert
#include <memory>       // unique_ptr
#include <optional>     // optional
#include <ostream>      // ostream
#include <string>       // string
#include <string_view>  // string_view

#include "../core/common.hpp"
#include "../core/exception.hpp"
#include "../core/features.hpp"
#include "../detail/owner_handle_api.hpp"
#include "../math.hpp"
#include "texture.hpp"
#include "window.hpp"

namespace cen {

/// \addtogroup video
/// \{

/// \brief Represents different OpenGL attributes.
/// \since 6.0.0
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

/// \brief Represents different swap interval modes.
/// \since 6.0.0
enum class gl_swap_interval {
  immediate = 0,       ///< Immediate updates.
  synchronized = 1,    ///< Updates synchronized with vertical retrace (VSync).
  late_immediate = -1  ///< Allow immediate late swaps, instead of waiting for retrace.
};

/**
 * \class gl_library
 *
 * \brief Manages the initialization and de-initialization of an OpenGL library.
 *
 * \since 6.0.0
 */
class gl_library final {
 public:
  CENTURION_DISABLE_COPY(gl_library)
  CENTURION_DISABLE_MOVE(gl_library)

  /**
   * \brief Loads an OpenGL library.
   *
   * \param path the file path to the OpenGL library that will be used; a null path
   * indicates that the default library will be used.
   *
   * \throws sdl_error if the OpenGL library can't be loaded.
   *
   * \since 6.0.0
   */
  CENTURION_NODISCARD_CTOR explicit gl_library(const char* path = nullptr)
  {
    if (SDL_GL_LoadLibrary(path) == -1) {
      throw SDLError{};
    }
  }

  ~gl_library() noexcept { SDL_GL_UnloadLibrary(); }

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
  [[nodiscard]] auto address_of(const char* function) const noexcept  // NOLINT
      -> void*
  {
    assert(function);
    return SDL_GL_GetProcAddress(function);
  }
};

template <typename T>
class basic_gl_context;

///< An owning OpenGL context.
using gl_context = basic_gl_context<detail::OwnerTag>;

///< A non-owning OpenGL context.
using gl_context_handle = basic_gl_context<detail::HandleTag>;

/**
 * \class basic_context
 *
 * \brief Represents an OpenGL context.
 *
 * \ownerhandle `context`/`context_handle`
 *
 * \since 6.0.0
 */
template <typename T>
class basic_gl_context final {
 public:
  /// \name Construction
  /// \{

  // clang-format off

  /**
   * \brief Creates a context instance from an existing OpenGL context.
   *
   * \param context the existing OpenGL context.
   *
   * \throws cen_error if the context is owning and the supplied pointer is null.
   *
   * \since 6.0.0
   */
  explicit basic_gl_context(MaybeOwner<SDL_GLContext> context) noexcept(detail::is_handle<T>)
      : m_context{context}
  {
    if constexpr (detail::is_owner<T>) {
      if (!m_context) {
        throw Error{"Can't create OpenGL context from null pointer!"};
      }
    }
  }

  // clang-format on

  /**
   * \brief Creates an OpenGL context based on the supplied window.
   *
   * \tparam U the ownership semantics of the window.
   *
   * \param window the OpenGL window.
   *
   * \throws sdl_error if the context has owning semantics and the OpenGL context couldn't
   * be initialized.
   *
   * \since 6.0.0
   */
  template <typename U>
  explicit basic_gl_context(basic_window<U>& window) noexcept(detail::is_handle<T>)
      : m_context{SDL_GL_CreateContext(window.get())}
  {
    if constexpr (detail::is_owner<T>) {
      if (!m_context) {
        throw SDLError{};
      }
    }
  }

  /// \} End of construction

  /**
   * \brief Makes the context the current OpenGL context for an OpenGL window.
   *
   * \pre `window` must be an OpenGL window.
   *
   * \tparam U the ownership semantics of the window.
   *
   * \param window the OpenGL window.
   *
   * \return `success` if the was operation was successful; `failure` otherwise.
   *
   * \since 6.0.0
   */
  template <typename U>
  auto make_current(basic_window<U>& window) -> Result
  {
    assert(window.is_opengl());
    return SDL_GL_MakeCurrent(window.get(), m_context.get()) == 0;
  }

  /**
   * \brief Returns the associated OpenGL context.
   *
   * \return the handle to the associated OpenGL context.
   *
   * \since 6.0.0
   */
  [[nodiscard]] auto get() const noexcept -> SDL_GLContext { return m_context.get(); }

 private:
  struct deleter final {
    void operator()(SDL_GLContext context) noexcept { SDL_GL_DeleteContext(context); }
  };

  std::unique_ptr<void, deleter> m_context;
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
      throw Error{"Did not recognize OpenGL attribute!"};
  }
}

/**
 * \brief Returns a textual version of the supplied swap interval attribute.
 *
 * \details This function returns a string that mirrors the name of the enumerator, e.g.
 * `to_string(gl_swap_interval::synchronized) == "synchronized"`.
 *
 * \param interval the enumerator that will be converted.
 *
 * \return a string that mirrors the name of the enumerator.
 *
 * \throws cen_error if the enumerator is not recognized.
 *
 * \since 6.2.0
 */
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
      throw Error{"Did not recognize swap interval!"};
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

/**
 * \brief Prints a textual representation of a swap interval enumerator.
 *
 * \param stream the output stream that will be used.
 * \param interval the enumerator that will be printed.
 *
 * \see `to_string(gl_swap_interval)`
 *
 * \return the used stream.
 *
 * \since 6.2.0
 */
inline auto operator<<(std::ostream& stream, const gl_swap_interval interval) -> std::ostream&
{
  return stream << to_string(interval);
}

/// \} End of streaming

/// \} End of group video

namespace gl {

/// \addtogroup video
/// \{

/// \name OpenGL functions
/// \{

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

/**
 * \brief Returns the drawable size of an OpenGL window.
 *
 * \pre `window` must be an OpenGL window.
 *
 * \tparam T the ownership semantics of the window.
 *
 * \param window the OpenGL window that will be queried.
 *
 * \return the drawable size of the window.
 *
 * \since 6.0.0
 */
template <typename T>
[[nodiscard]] auto drawable_size(const basic_window<T>& window) noexcept -> Area
{
  assert(window.is_opengl());

  int width{};
  int height{};
  SDL_GL_GetDrawableSize(window.get(), &width, &height);

  return {width, height};
}

/**
 * \brief Resets all OpenGL context attributes to their default values.
 *
 * \since 6.0.0
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
 * \return `success` if the attribute was successfully set; `failure` otherwise.
 *
 * \since 6.0.0
 */
inline auto set(const gl_attribute attr, const int value) noexcept -> Result
{
  return SDL_GL_SetAttribute(static_cast<SDL_GLattr>(attr), value) == 0;
}

/**
 * \brief Returns the current value of an OpenGL context attribute.
 *
 * \param attr the OpenGL context attribute to check.
 *
 * \return the value of the specified attribute; `std::nullopt` if the value could not be
 * obtained.
 *
 * \since 6.0.0
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
 * \return `success` if the swap interval successfully set; `failure` if it isn't
 * supported.
 *
 * \since 6.0.0
 */
inline auto set_swap_interval(const gl_swap_interval interval) noexcept -> Result
{
  return SDL_GL_SetSwapInterval(ToUnderlying(interval)) == 0;
}

/**
 * \brief Returns the swap interval used by the current OpenGL context.
 *
 * \note `gl_swap_interval::immediate` is returned if the swap interval couldn't be
 * determined.
 *
 * \return the current swap interval.
 *
 * \since 6.0.0
 */
[[nodiscard]] inline auto swap_interval() noexcept -> gl_swap_interval
{
  return gl_swap_interval{SDL_GL_GetSwapInterval()};
}

/**
 * \brief Returns a handle to the currently active OpenGL window.
 *
 * \return a potentially invalid handle to the current OpenGL window.
 *
 * \since 6.0.0
 */
[[nodiscard]] inline auto get_window() noexcept -> window_handle
{
  return window_handle{SDL_GL_GetCurrentWindow()};
}

/**
 * \brief Returns a handle to the currently active OpenGL context.
 *
 * \return a potentially invalid handle to the current OpenGL context.
 *
 * \since 6.0.0
 */
[[nodiscard]] inline auto get_context() noexcept -> gl_context_handle
{
  return gl_context_handle{SDL_GL_GetCurrentContext()};
}

/**
 * \brief Indicates whether or not the specified extension is supported.
 *
 * \param extension the extension that will be checked.
 *
 * \return `true` if the specified extension is supported; `false` otherwise.
 *
 * \since 6.0.0
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
 * \tparam T the ownership semantics tag.
 *
 * \param texture the texture to bind.
 *
 * \return the size of the texture if it was successfully bound; `std::nullopt` if
 * something goes wrong.
 *
 * \since 6.1.0
 */
template <typename T>
auto bind(basic_texture<T>& texture) noexcept -> std::optional<FArea>
{
  float width{};
  float height{};
  if (SDL_GL_BindTexture(texture.get(), &width, &height) == 0) {
    return FArea{width, height};
  }
  else {
    return std::nullopt;
  }
}

/**
 * \brief Unbinds a texture from the OpenGL context.
 *
 * \tparam T the ownership semantics tag.
 *
 * \param texture the texture to unbind.
 *
 * \return `success` if the texture was unbound; `failure` otherwise.
 *
 * \since 6.1.0
 */
template <typename T>
auto unbind(basic_texture<T>& texture) noexcept -> Result
{
  return SDL_GL_UnbindTexture(texture.get()) == 0;
}

/// \} End of OpenGL functions

/// \} End of group video

}  // namespace gl
}  // namespace cen

#endif  // CENTURION_NO_OPENGL
#endif  // CENTURION_VIDEO_OPENGL_HPP_
