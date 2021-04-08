#ifndef CENTURION_GL_LIBRARY_HEADER
#define CENTURION_GL_LIBRARY_HEADER

#ifndef CENTURION_NO_OPENGL

#include <SDL.h>
#include <SDL_opengl.h>

#include <cassert>  // assert

#include "../../misc/czstring.hpp"
#include "../../misc/exception.hpp"
#include "../../misc/not_null.hpp"

/// \addtogroup video
/// \{

namespace cen::gl {

/**
 * \class library
 *
 * \brief Manages the initialization and de-initialization of an OpenGL library.
 *
 * \since 6.0.0
 *
 * \headerfile gl_library.hpp
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

}  // namespace cen::gl

/// \} End of group video

#endif  // CENTURION_NO_OPENGL
#endif  // CENTURION_GL_LIBRARY_HEADER
