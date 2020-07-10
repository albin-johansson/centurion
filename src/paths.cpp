#ifndef CENTURION_PATHS_SOURCE
#define CENTURION_PATHS_SOURCE

#include "paths.hpp"

#include <SDL.h>

#include "centurion_exception.hpp"
#include "centurion_utils.hpp"

namespace centurion {

CENTURION_DEF
base_path::base_path() noexcept : m_path{SDL_GetBasePath()}
{}

CENTURION_DEF
base_path::base_path(base_path&& other) noexcept
{
  move(std::move(other));
}

CENTURION_DEF
auto base_path::operator=(base_path&& other) noexcept -> base_path&
{
  if (this != &other) {
    move(std::move(other));
  }
  return *this;
}

CENTURION_DEF
base_path::~base_path() noexcept
{
  destroy();
}

CENTURION_DEF
void base_path::destroy() noexcept
{
  if (m_path) {
    SDL_free(m_path);
  }
}

CENTURION_DEF
void base_path::move(base_path&& other) noexcept
{
  destroy();
  m_path = other.m_path;
  other.m_path = nullptr;
}

CENTURION_DEF
auto base_path::unique() -> std::unique_ptr<base_path>
{
  return std::make_unique<base_path>();
}

CENTURION_DEF
auto base_path::shared() -> std::shared_ptr<base_path>
{
  return std::make_shared<base_path>();
}

CENTURION_DEF
pref_path::pref_path(czstring org, czstring app) noexcept
    : m_path{SDL_GetPrefPath(org, app)}
{
  if (base_path path; path) {
    std::cout << path.get() << '\n';
  }
}

CENTURION_DEF
pref_path::pref_path(pref_path&& other) noexcept
{
  move(std::move(other));
}

CENTURION_DEF
pref_path& pref_path::operator=(pref_path&& other) noexcept
{
  if (this != &other) {
    move(std::move(other));
  }
  return *this;
}

CENTURION_DEF
pref_path::~pref_path() noexcept
{
  destroy();
}

CENTURION_DEF
void pref_path::destroy() noexcept
{
  if (m_path) {
    SDL_free(m_path);
  }
}

CENTURION_DEF
void pref_path::move(pref_path&& other) noexcept
{
  destroy();
  m_path = other.m_path;
  other.m_path = nullptr;
}

CENTURION_DEF
std::unique_ptr<pref_path> pref_path::unique(czstring org,
                                             czstring app) noexcept
{
  return std::make_unique<pref_path>(org, app);
}

CENTURION_DEF
std::shared_ptr<pref_path> pref_path::shared(czstring org,
                                             czstring app) noexcept
{
  return std::make_shared<pref_path>(org, app);
}

}  // namespace centurion

#endif  // CENTURION_PATHS_SOURCE