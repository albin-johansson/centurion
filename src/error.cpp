#ifndef CENTURION_ERROR_SOURCE
#define CENTURION_ERROR_SOURCE

#include "error.h"

#include <SDL.h>

namespace centurion {

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
