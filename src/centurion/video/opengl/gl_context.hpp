#ifndef CENTURION_GL_CONTEXT_HEADER
#define CENTURION_GL_CONTEXT_HEADER

#ifndef CENTURION_NO_OPENGL

#include <SDL.h>
#include <SDL_opengl.h>

#include <memory>  // unique_ptr

#include "../../core/exception.hpp"
#include "../../core/result.hpp"
#include "../../detail/owner_handle_api.hpp"
#include "../window.hpp"

namespace cen::gl {

/// \addtogroup video
/// \{

// TODO Centurion 6: document and test

template <typename T>
class basic_context;

using context = basic_context<detail::owning_type>;
using context_handle = basic_context<detail::handle_type>;

template <typename T>
class basic_context final
{
 public:
  // clang-format off

  explicit basic_context(SDL_GLContext context) noexcept(!detail::is_owning<T>())
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

  template <typename U>
  explicit basic_context(basic_window<U>& window) noexcept(!detail::is_owning<T>())
      : m_context{SDL_GL_CreateContext(window.get())}
  {
    if constexpr (detail::is_owning<T>())
    {
      if (!m_context)
      {
        throw sdl_error{};
      }
    }
  }

  // clang-format on

  template <typename U>
  auto make_current(basic_window<U>& window) -> result
  {
    return SDL_GL_MakeCurrent(window.get(), m_context.get()) == 0;
  }

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

#endif  // CENTURION_NO_OPENGL
#endif  // CENTURION_GL_CONTEXT_HEADER
