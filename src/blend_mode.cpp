#include "blend_mode.h"

namespace centurion {

bool operator==(BlendMode a, SDL_BlendMode b) noexcept {
  return static_cast<SDL_BlendMode>(a) == b;
}

bool operator==(SDL_BlendMode a, BlendMode b) noexcept {
  return a == static_cast<SDL_BlendMode>(b);
}

bool operator!=(BlendMode a, SDL_BlendMode b) noexcept {
  return static_cast<SDL_BlendMode>(a) != b;
}

bool operator!=(SDL_BlendMode a, BlendMode b) noexcept {
  return a != static_cast<SDL_BlendMode>(b);
}

}
