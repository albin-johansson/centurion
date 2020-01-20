#include "paths.h"
#include <SDL.h>

namespace centurion {

AppPath::AppPath() noexcept : path{SDL_GetBasePath()} {}

AppPath::~AppPath() noexcept {
  if (path) {
    SDL_free(path);
  }
}

AppPath::operator bool() const noexcept {
  return path;
}

std::unique_ptr<AppPath> AppPath::unique() {
  return std::make_unique<AppPath>();
}

std::shared_ptr<AppPath> AppPath::shared() {
  return std::make_shared<AppPath>();
}

PrefPath::PrefPath(const std::string& org, const std::string& app)
    : path{SDL_GetPrefPath(org.c_str(), app.c_str())} {}

PrefPath::~PrefPath() noexcept {
  if (path) {
    SDL_free(path);
  }
}

std::unique_ptr<PrefPath> PrefPath::unique(const std::string& org, const std::string& app) {
  return std::make_unique<PrefPath>(org, app);
}

std::shared_ptr<PrefPath> PrefPath::shared(const std::string& org, const std::string& app) {
  return std::make_shared<PrefPath>(org, app);
}

}
