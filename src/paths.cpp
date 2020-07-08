#ifndef CENTURION_PATHS_SOURCE
#define CENTURION_PATHS_SOURCE

#include "paths.hpp"

#include <SDL.h>

#include "centurion_utils.hpp"

namespace centurion {

CENTURION_DEF
BasePath::BasePath() noexcept : m_path{SDL_GetBasePath()}
{}

CENTURION_DEF
BasePath::BasePath(BasePath&& other) noexcept
{
  move(std::move(other));
}

CENTURION_DEF
BasePath& BasePath::operator=(BasePath&& other) noexcept
{
  if (this != &other) {
    move(std::move(other));
  }
  return *this;
}

CENTURION_DEF
BasePath::~BasePath() noexcept
{
  destroy();
}

CENTURION_DEF
void BasePath::destroy() noexcept
{
  if (m_path) {
    SDL_free(m_path);
  }
}

CENTURION_DEF
void BasePath::move(BasePath&& other) noexcept
{
  destroy();
  m_path = other.m_path;
  other.m_path = nullptr;
}

CENTURION_DEF
UniquePtr<BasePath> BasePath::unique() noexcept
{
  return std::make_unique<BasePath>();
}

CENTURION_DEF
SharedPtr<BasePath> BasePath::shared() noexcept
{
  return std::make_shared<BasePath>();
}

CENTURION_DEF
PrefPath::PrefPath(czstring org, czstring app) noexcept
    : m_path{SDL_GetPrefPath(org, app)}
{}

CENTURION_DEF
PrefPath::PrefPath(PrefPath&& other) noexcept
{
  move(std::move(other));
}

CENTURION_DEF
PrefPath& PrefPath::operator=(PrefPath&& other) noexcept
{
  if (this != &other) {
    move(std::move(other));
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
UniquePtr<PrefPath> PrefPath::unique(czstring org, czstring app) noexcept
{
  return std::make_unique<PrefPath>(org, app);
}

CENTURION_DEF
SharedPtr<PrefPath> PrefPath::shared(czstring org, czstring app) noexcept
{
  return std::make_shared<PrefPath>(org, app);
}

}  // namespace centurion

#endif  // CENTURION_PATHS_SOURCE