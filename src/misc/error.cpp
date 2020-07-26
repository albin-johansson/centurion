#include "error.hpp"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include <string>

namespace centurion::detail {

using namespace std::string_literals;

auto core_error(std::string_view message) -> centurion_exception
{
  return centurion_exception{message.data() + " Error: "s + SDL_GetError()};
}

auto img_error(std::string_view message) -> centurion_exception
{
  return centurion_exception{message.data() + " Error: "s + IMG_GetError()};
}

auto ttf_error(std::string_view message) -> centurion_exception
{
  return centurion_exception{message.data() + " Error: "s + TTF_GetError()};
}

auto mix_error(std::string_view message) -> centurion_exception
{
  return centurion_exception{message.data() + " Error: "s + Mix_GetError()};
}

}  // namespace centurion::detail
