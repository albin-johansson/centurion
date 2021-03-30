#ifndef CENTURION_GL_CONTEXT_HEADER
#define CENTURION_GL_CONTEXT_HEADER

#include <SDL.h>

#include <memory>  // unique_ptr

#include "../../centurion_cfg.hpp"
#include "../../detail/owner_handle_api.hpp"
#include "../../misc/exception.hpp"
#include "../window.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

/// \addtogroup video
/// \addtogroup opengl

namespace cen::gl {

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
  auto make_current(basic_window<U>& window) -> bool
  {
    const auto result = SDL_GL_MakeCurrent(window.get(), m_context.get());
    return result == 0;
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

}  // namespace cen::gl

/// \} End of group opengl
/// \} End of group video

#endif  // CENTURION_GL_CONTEXT_HEADER
