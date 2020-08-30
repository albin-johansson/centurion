#include "exception.hpp"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

namespace centurion {

using namespace std::string_literals;

sdl_error::sdl_error(std::string_view what)
{
  set_what(what.data() + ": "s + SDL_GetError());
}

img_error::img_error(std::string_view what)
{
  set_what(what.data() + ": "s + IMG_GetError());
}

ttf_error::ttf_error(std::string_view what)
{
  set_what(what.data() + ": "s + TTF_GetError());
}

mix_error::mix_error(std::string_view what)
{
  set_what(what.data() + ": "s + Mix_GetError());
}

}  // namespace centurion
