#include "error.h"
#include <SDL.h>

namespace centurion {

const char* Error::descriptionf() noexcept {
  const auto* err = SDL_GetError();
  return err ? err : "";
}

std::string Error::description() noexcept {
  return {descriptionf()};
}

std::string Error::msg() noexcept {
  return "Error: " + description();
}

}
