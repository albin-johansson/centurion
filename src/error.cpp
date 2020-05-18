#ifndef CENTURION_ERROR_SOURCE
#define CENTURION_ERROR_SOURCE

#include "error.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

namespace centurion {
namespace detail {

CENTURION_DEF
CenturionException Error::from_core(std::string message)
{
  return CenturionException{message + " Error: " + SDL_GetError()};
}

CENTURION_DEF
CenturionException Error::from_image(std::string message)
{
  return CenturionException{message + " Error: " + IMG_GetError()};
}

CENTURION_DEF
CenturionException Error::from_ttf(std::string message)
{
  return CenturionException{message + " Error: " + TTF_GetError()};
}

CENTURION_DEF
CenturionException Error::from_mixer(std::string message)
{
  return CenturionException{message + " Error: " + Mix_GetError()};
}

}  // namespace detail
}  // namespace centurion

#endif  // CENTURION_ERROR_SOURCE
