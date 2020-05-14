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
AppPath::AppPath(AppPath&& other) noexcept
{
  move(std::forward<AppPath>(other));
}

CENTURION_DEF
AppPath& AppPath::operator=(AppPath&& other) noexcept
{
  if (this != &other) {
    move(std::forward<AppPath>(other));
  }
  return *this;
}

CENTURION_DEF
AppPath::~AppPath() noexcept
{
  destroy();
}

CENTURION_DEF
void AppPath::destroy() noexcept
{
  if (m_path) {
    SDL_free(m_path);
  }
}

CENTURION_DEF
void AppPath::move(AppPath&& other) noexcept
{
  destroy();
  m_path = other.m_path;
  other.m_path = nullptr;
}

CENTURION_DEF
UniquePtr<AppPath> AppPath::unique()
{
  return centurion::detail::make_unique<AppPath>();
}

CENTURION_DEF
SharedPtr<AppPath> AppPath::shared()
{
  return std::make_shared<AppPath>();
}

CENTURION_DEF
PrefPath::PrefPath(const std::string& org, const std::string& app)
    : m_path{SDL_GetPrefPath(org.c_str(), app.c_str())}
{}

CENTURION_DEF
PrefPath::PrefPath(PrefPath&& other) noexcept
{
  move(std::forward<PrefPath>(other));
}

CENTURION_DEF
PrefPath& PrefPath::operator=(PrefPath&& other) noexcept
{
  if (this != &other) {
    move(std::forward<PrefPath>(other));
  }
  return *this;
}

CENTURION_DEF
PrefPath::~PrefPath() noexcept
{
  destroy();
}

CENTURION_DEF
void PrefPath::destroy() noexcept
{
  if (m_path) {
    SDL_free(m_path);
  }
}

CENTURION_DEF
void PrefPath::move(PrefPath&& other) noexcept
{
  destroy();
  m_path = other.m_path;
  other.m_path = nullptr;
}

CENTURION_DEF
UniquePtr<PrefPath> PrefPath::unique(const std::string& org,
                                     const std::string& app)
{
  return centurion::detail::make_unique<PrefPath>(org, app);
}

CENTURION_DEF
SharedPtr<PrefPath> PrefPath::shared(const std::string& org,
                                     const std::string& app)
{
  return std::make_shared<PrefPath>(org, app);
}

}  // namespace centurion

#endif  // CENTURION_PATHS_SOURCE