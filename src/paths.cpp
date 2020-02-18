#ifndef CENTURION_PATHS_SOURCE
#define CENTURION_PATHS_SOURCE

#include "paths.h"

#include <SDL.h>

#include "centurion_utils.h"

namespace centurion {

CENTURION_DEF AppPath::AppPath() noexcept : path{SDL_GetBasePath()} {}

CENTURION_DEF AppPath::~AppPath() noexcept
{
  if (path) {
    SDL_free(path);
  }
}

CENTURION_DEF AppPath::operator bool() const noexcept { return path; }

CENTURION_DEF std::unique_ptr<AppPath> AppPath::unique()
{
#ifdef CENTURION_HAS_MAKE_UNIQUE
  return std::make_unique<AppPath>();
#else
  return make_unique<AppPath>();
#endif
}

CENTURION_DEF std::shared_ptr<AppPath> AppPath::shared()
{
  return std::make_shared<AppPath>();
}

CENTURION_DEF PrefPath::PrefPath(const std::string& org, const std::string& app)
    : path{SDL_GetPrefPath(org.c_str(), app.c_str())}
{}

CENTURION_DEF PrefPath::~PrefPath() noexcept
{
  if (path) {
    SDL_free(path);
  }
}

CENTURION_DEF std::unique_ptr<PrefPath> PrefPath::unique(const std::string& org,
                                                         const std::string& app)
{
#ifdef CENTURION_HAS_MAKE_UNIQUE
  return std::make_unique<PrefPath>(org, app);
#else
  return make_unique<PrefPath>(org, app);
#endif
}

CENTURION_DEF std::shared_ptr<PrefPath> PrefPath::shared(const std::string& org,
                                                         const std::string& app)
{
  return std::make_shared<PrefPath>(org, app);
}

}  // namespace centurion

#endif  // CENTURION_PATHS_SOURCE