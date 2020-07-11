#ifndef CENTURION_ERROR_SOURCE
#define CENTURION_ERROR_SOURCE

#include "error.hpp"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include <string>

namespace centurion::detail {

CENTURION_DEF
auto core_error(std::string_view message) -> centurion_exception
{
  using namespace std::string_literals;
  return centurion_exception{message.data() + " Error: "s + SDL_GetError()};
}

CENTURION_DEF
auto img_error(std::string_view message) -> centurion_exception
{
  using namespace std::string_literals;
  return centurion_exception{message.data() + " Error: "s + IMG_GetError()};
}

CENTURION_DEF
auto ttf_error(std::string_view message) -> centurion_exception
{
  using namespace std::string_literals;
  return centurion_exception{message.data() + " Error: "s + TTF_GetError()};
}

CENTURION_DEF
auto mix_error(std::string_view message) -> centurion_exception
{
  using namespace std::string_literals;
  return centurion_exception{message.data() + " Error: "s + Mix_GetError()};
}

}  // namespace centurion::detail

#endif  // CENTURION_ERROR_SOURCE
