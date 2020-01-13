#include "paths.h"
#include <SDL.h>

namespace centurion {

AppPath::AppPath() noexcept : path{SDL_GetBasePath()} {}

AppPath::~AppPath() noexcept {
  if (path) {
    SDL_free(path);
  }
}

PrefPath::PrefPath(const std::string& org, const std::string& app)
    : path{SDL_GetPrefPath(org.c_str(), app.c_str())} {}

PrefPath::~PrefPath() noexcept {
  if (path) {
    SDL_free(path);
  }
}

}
