#ifndef CENTURION_GL_CONTEXT_HEADER
#define CENTURION_GL_CONTEXT_HEADER

#ifndef CENTURION_NO_OPENGL

#include <SDL.h>

#include <cassert>  // assert
#include <memory>   // unique_ptr

#include "../../core/exception.hpp"
#include "../../core/owner.hpp"
#include "../../core/result.hpp"
#include "../../detail/owner_handle_api.hpp"
#include "../window.hpp"

namespace cen::gl {

/// \addtogroup video
/// \{

template <typename T>
class basic_context;

///< An owning OpenGL context.
using context = basic_context<detail::owning_type>;

///< A non-owning OpenGL context.
using context_handle = basic_context<detail::handle_type>;

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
class basic_context final
{
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
  explicit basic_context(maybe_owner<SDL_GLContext> context) noexcept(!detail::is_owning<T>())
      : m_context{context}
  {
    if constexpr (detail::is_owning<T>())
    {
      if (!m_context)
      {
        throw cen_error{"Can't create OpenGL context from null pointer!"};
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
  explicit basic_context(basic_window<U>& window) noexcept(!detail::is_owning<T>())
      : m_context{SDL_GL_CreateContext(window.get())}
  {
    if constexpr (detail::is_owning<T>()) {
      if (!m_context) {
        throw sdl_error{};
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
  auto make_current(basic_window<U>& window) -> result
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
  [[nodiscard]] auto get() const noexcept -> SDL_GLContext
  {
    return m_context.get();
  }

 private:
  struct deleter final
  {
    void operator()(SDL_GLContext context) noexcept
    {
      SDL_GL_DeleteContext(context);
    }
  };

  std::unique_ptr<void, deleter> m_context;
};

/// \} End of group video

}  // namespace cen::gl

namespace cen {

/// \addtogroup video
/// \{

/// Workaround for slight inconsistency where other OpenGL components feature "gl_"-prefix
using gl_context = gl::context;
using gl_context_handle = gl::context_handle;

/// \} End of group video

}  // namespace cen

#endif  // CENTURION_NO_OPENGL
#endif  // CENTURION_GL_CONTEXT_HEADER
