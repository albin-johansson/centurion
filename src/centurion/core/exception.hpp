#ifndef CENTURION_EXCEPTION_HEADER
#define CENTURION_EXCEPTION_HEADER

#include <SDL.h>

#ifndef CENTURION_NO_SDL_IMAGE
#include <SDL_image.h>
#endif  // CENTURION_NO_SDL_IMAGE

#ifndef CENTURION_NO_SDL_MIXER
#include <SDL_mixer.h>
#endif  // CENTURION_NO_SDL_MIXER

#ifndef CENTURION_NO_SDL_TTF
#include <SDL_ttf.h>
#endif  // CENTURION_NO_SDL_TTF

#include <exception>  // exception

#include "str.hpp"

namespace cen {

/// \addtogroup core
/// \{

/**
 * \class cen_error
 *
 * \brief The base of all exceptions explicitly thrown by the library.
 *
 * \since 3.0.0
 */
class cen_error : public std::exception
{
 public:
  cen_error() noexcept = default;

  /**
   * \param what the message of the exception, can safely be null.
   *
   * \since 3.0.0
   */
  explicit cen_error(const str what) noexcept : m_what{what ? what : m_what}
  {}

  [[nodiscard]] auto what() const noexcept -> str override
  {
    return m_what;
  }

 private:
  str m_what{"n/a"};
};

/**
 * \class sdl_error
 *
 * \brief Represents an error related to the core SDL2 library.
 *
 * \since 5.0.0
 */
class sdl_error final : public cen_error
{
 public:
  /**
   * \brief Creates an `sdl_error` with the error message obtained from `SDL_GetError()`.
   *
   * \since 5.0.0
   */
  sdl_error() noexcept : cen_error{SDL_GetError()}
  {}

  /**
   * \brief Creates an `sdl_error` with the specified error message.
   *
   * \param what the error message that will be used.
   *
   * \since 5.0.0
   */
  explicit sdl_error(const str what) noexcept : cen_error{what}
  {}
};

#ifndef CENTURION_NO_SDL_IMAGE

/**
 * \class img_error
 *
 * \brief Represents an error related to the SDL2_image library.
 *
 * \since 5.0.0
 */
class img_error final : public cen_error
{
 public:
  /**
   * \brief Creates an `img_error` with the error message obtained from `IMG_GetError()`.
   *
   * \since 5.0.0
   */
  img_error() noexcept : cen_error{IMG_GetError()}
  {}

  /**
   * \brief Creates an `img_error` with the specified error message.
   *
   * \param what the error message that will be used.
   *
   * \since 5.0.0
   */
  explicit img_error(const str what) noexcept : cen_error{what}
  {}
};

#endif  // CENTURION_NO_SDL_IMAGE

#ifndef CENTURION_NO_SDL_TTF

/**
 * \class ttf_error
 *
 * \brief Represents an error related to the SDL2_ttf library.
 *
 * \since 5.0.0
 */
class ttf_error final : public cen_error
{
 public:
  /**
   * \brief Creates a `ttf_error` with the error message obtained from `TTF_GetError()`.
   *
   * \since 5.0.0
   */
  ttf_error() noexcept : cen_error{TTF_GetError()}
  {}

  /**
   * \brief Creates a `ttf_error` with the specified error message.
   *
   * \param what the error message that will be used.
   *
   * \since 5.0.0
   */
  explicit ttf_error(const str what) noexcept : cen_error{what}
  {}
};

#endif  // CENTURION_NO_SDL_TTF

#ifndef CENTURION_NO_SDL_MIXER

/**
 * \class mix_error
 *
 * \brief Represents an error related to the SDL2_mixer library.
 *
 * \since 5.0.0
 */
class mix_error final : public cen_error
{
 public:
  /**
   * \brief Creates a `mix_error` with the error message obtained from `Mix_GetError()`.
   *
   * \since 5.0.0
   */
  mix_error() noexcept : cen_error{Mix_GetError()}
  {}

  /**
   * \brief Creates a `mix_error` with the specified error message.
   *
   * \param what the error message that will be used.
   *
   * \since 5.0.0
   */
  explicit mix_error(const str what) noexcept : cen_error{what}
  {}
};

#endif  // CENTURION_NO_SDL_MIXER

/// \} End of group core

}  // namespace cen

#endif  // CENTURION_EXCEPTION_HEADER
