#ifndef CENTURION_ERROR_SOURCE
#define CENTURION_ERROR_SOURCE

#include "error.hpp"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

namespace centurion {
namespace detail {

CENTURION_DEF
centurion_exception Error::from_core(std::string message)
{
  return centurion_exception{message + " Error: " + SDL_GetError()};
}

CENTURION_DEF
centurion_exception Error::from_image(std::string message)
{
  return centurion_exception{message + " Error: " + IMG_GetError()};
}

CENTURION_DEF
centurion_exception Error::from_ttf(std::string message)
{
  return centurion_exception{message + " Error: " + TTF_GetError()};
}

CENTURION_DEF
centurion_exception Error::from_mixer(std::string message)
{
  return centurion_exception{message + " Error: " + Mix_GetError()};
}

}  // namespace detail
}  // namespace centurion

#endif  // CENTURION_ERROR_SOURCE
