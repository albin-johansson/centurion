#ifndef CENTURION_GL_CORE_HEADER
#define CENTURION_GL_CORE_HEADER

#ifndef CENTURION_NO_OPENGL

#include <SDL.h>

#include <cassert>      // assert
#include <optional>     // optional
#include <ostream>      // ostream
#include <string>       // string
#include <string_view>  // string_view

#include "../../core/exception.hpp"
#include "../../core/not_null.hpp"
#include "../../core/result.hpp"
#include "../../core/str.hpp"
#include "../../core/to_underlying.hpp"
#include "../../math/area.hpp"
#include "../texture.hpp"
#include "../window.hpp"
#include "gl_attribute.hpp"
#include "gl_context.hpp"

namespace cen {

/// \addtogroup video
/// \{

/**
 * \enum gl_swap_interval
 *
 * \brief Provides identifiers that represent different swap interval modes.
 *
 * \ingroup video
 *
 * \since 6.0.0
 */
enum class gl_swap_interval : int
{
  immediate = 0,       ///< Immediate updates.
  synchronized = 1,    ///< Updates synchronized with vertical retrace (VSync).
  late_immediate = -1  ///< Allow immediate late swaps, instead of waiting for retrace.
};

/// \name String conversions
/// \{

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
      throw cen_error{"Did not recognize swap interval!"};
  }
}

/// \} End of string conversions

/// \name Streaming
/// \{

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

}  // namespace cen

/**
 * \namespace cen::gl
 *
 * \brief Contains OpenGL-related components.
 *
 * \ingroup video
 *
 * \since 6.0.0
 */
namespace cen::gl {

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
inline auto set(const gl_attribute attr, const int value) noexcept -> result
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
inline auto set_swap_interval(const gl_swap_interval interval) noexcept -> result
{
  return SDL_GL_SetSwapInterval(to_underlying(interval)) == 0;
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
[[nodiscard]] inline auto get_context() noexcept -> context_handle
{
  return context_handle{SDL_GL_GetCurrentContext()};
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
[[nodiscard]] inline auto is_extension_supported(const not_null<str> extension) noexcept
    -> bool
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
 * \tparam T the ownership semantics tag.
 *
 * \param texture the texture to unbind.
 *
 * \return `success` if the texture was unbound; `failure` otherwise.
 *
 * \since 6.1.0
 */
template <typename T>
auto unbind(basic_texture<T>& texture) noexcept -> result
{
  return SDL_GL_UnbindTexture(texture.get()) == 0;
}

/// \} End of OpenGL functions

/// \} End of group video

}  // namespace cen::gl

#endif  // CENTURION_NO_OPENGL
#endif  // CENTURION_GL_CORE_HEADER
