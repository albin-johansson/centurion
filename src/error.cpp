#ifndef CENTURION_ERROR_SOURCE
#define CENTURION_ERROR_SOURCE

#include "error.hpp"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

namespace centurion::detail {

CENTURION_DEF
auto Error::from_core(const std::string& message) -> centurion_exception
{
  return centurion_exception{message + " Error: " + SDL_GetError()};
}

CENTURION_DEF
auto Error::from_image(const std::string& message) -> centurion_exception
{
  return centurion_exception{message + " Error: " + IMG_GetError()};
}

CENTURION_DEF
auto Error::from_ttf(const std::string& message) -> centurion_exception
{
  return centurion_exception{message + " Error: " + TTF_GetError()};
}

CENTURION_DEF
auto Error::from_mixer(const std::string& message) -> centurion_exception
{
  return centurion_exception{message + " Error: " + Mix_GetError()};
}

}  // namespace centurion::detail

#endif  // CENTURION_ERROR_SOURCE
