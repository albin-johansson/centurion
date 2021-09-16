#ifndef CENTURION_GL_LIBRARY_HEADER
#define CENTURION_GL_LIBRARY_HEADER

#ifndef CENTURION_NO_OPENGL

#include <SDL.h>

#include <cassert>  // assert

#include "../../compiler/features.hpp"
#include "../../core/exception.hpp"
#include "../../core/not_null.hpp"
#include "../../core/str.hpp"

namespace cen {

/// \addtogroup video
/// \{

/**
 * \class gl_library
 *
 * \brief Manages the initialization and de-initialization of an OpenGL library.
 *
 * \since 6.0.0
 */
class gl_library final
{
 public:
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
  CENTURION_NODISCARD_CTOR explicit gl_library(const str path = nullptr)
  {
    if (SDL_GL_LoadLibrary(path) == -1) {
      throw sdl_error{};
    }
  }

  gl_library(const gl_library&) = delete;
  gl_library(gl_library&&) = delete;

  auto operator=(const gl_library&) -> gl_library& = delete;
  auto operator=(gl_library&&) -> gl_library& = delete;

  ~gl_library() noexcept
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
  [[nodiscard]] auto address_of(const not_null<str> function) const noexcept // NOLINT
      -> void*
  {
    assert(function);
    return SDL_GL_GetProcAddress(function);
  }

  // clang-format on
};

/// \} End of group video

}  // namespace cen

#endif  // CENTURION_NO_OPENGL
#endif  // CENTURION_GL_LIBRARY_HEADER
