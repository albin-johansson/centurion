#ifndef CENTURION_ERROR_SOURCE
#define CENTURION_ERROR_SOURCE

#include "error.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

namespace centurion {

CENTURION_DEF
Error::Error(std::string message) : m_message{std::move(message)}
{}

CENTURION_DEF
std::string Error::core_message() const
{
  return m_message + " Error: " + SDL_GetError();
}

CENTURION_DEF
std::string Error::img_message() const
{
  return m_message + " Error: " + IMG_GetError();
}

CENTURION_DEF
std::string Error::ttf_message() const
{
  return m_message + " Error: " + TTF_GetError();
}

CENTURION_DEF
std::string Error::mix_message() const
{
  return m_message + " Error: " + Mix_GetError();
}

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

CENTURION_DEF
CZString Error::descriptionf() noexcept
{
  CZString err = SDL_GetError();
  return err ? err : "";
}

CENTURION_DEF
std::string Error::description() noexcept
{
  return {descriptionf()};
}

CENTURION_DEF
std::string Error::msg() noexcept
{
  return "Error: " + description();
}

}  // namespace centurion

#endif  // CENTURION_ERROR_SOURCE
