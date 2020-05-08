#ifndef CENTURION_PATHS_SOURCE
#define CENTURION_PATHS_SOURCE

#include "paths.h"

#include <SDL.h>

#include "centurion_utils.h"

namespace centurion {

CENTURION_DEF
AppPath::AppPath() noexcept : m_path{SDL_GetBasePath()}
{}

CENTURION_DEF
AppPath::~AppPath() noexcept
{
  if (m_path) {
    SDL_free(m_path);
  }
}

CENTURION_DEF
AppPath::operator bool() const noexcept
{
  return m_path;
}

CENTURION_DEF
std::unique_ptr<AppPath> AppPath::unique()
{
  return centurion::make_unique<AppPath>();
}

CENTURION_DEF
std::shared_ptr<AppPath> AppPath::shared()
{
  return std::make_shared<AppPath>();
}

CENTURION_DEF
PrefPath::PrefPath(const std::string& org, const std::string& app)
    : m_path{SDL_GetPrefPath(org.c_str(), app.c_str())}
{}

CENTURION_DEF
PrefPath::~PrefPath() noexcept
{
  if (m_path) {
    SDL_free(m_path);
  }
}

CENTURION_DEF
std::unique_ptr<PrefPath> PrefPath::unique(const std::string& org,
                                           const std::string& app)
{
  return centurion::make_unique<PrefPath>(org, app);
}

CENTURION_DEF
std::shared_ptr<PrefPath> PrefPath::shared(const std::string& org,
                                           const std::string& app)
{
  return std::make_shared<PrefPath>(org, app);
}

}  // namespace centurion

#endif  // CENTURION_PATHS_SOURCE