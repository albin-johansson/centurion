#include "paths.hpp"

#include <SDL.h>

#include "centurion_exception.hpp"
#include "centurion_utils.hpp"

namespace centurion {

base_path::base_path() noexcept : m_path{SDL_GetBasePath()}
{}

base_path::base_path(base_path&& other) noexcept
{
  move(std::move(other));
}

auto base_path::operator=(base_path&& other) noexcept -> base_path&
{
  if (this != &other) {
    move(std::move(other));
  }
  return *this;
}

base_path::~base_path() noexcept
{
  destroy();
}

void base_path::destroy() noexcept
{
  if (m_path) {
    SDL_free(m_path);
  }
}

void base_path::move(base_path&& other) noexcept
{
  destroy();
  m_path = other.m_path;
  other.m_path = nullptr;
}

auto base_path::unique() -> std::unique_ptr<base_path>
{
  return std::make_unique<base_path>();
}

auto base_path::shared() -> std::shared_ptr<base_path>
{
  return std::make_shared<base_path>();
}

pref_path::pref_path(czstring org, czstring app) noexcept
    : m_path{SDL_GetPrefPath(org, app)}
{
  if (base_path path; path) {
    std::cout << path.get() << '\n';
  }
}

pref_path::pref_path(pref_path&& other) noexcept
{
  move(std::move(other));
}

auto pref_path::operator=(pref_path&& other) noexcept -> pref_path&
{
  if (this != &other) {
    move(std::move(other));
  }
  return *this;
}

pref_path::~pref_path() noexcept
{
  destroy();
}

void pref_path::destroy() noexcept
{
  if (m_path) {
    SDL_free(m_path);
  }
}

void pref_path::move(pref_path&& other) noexcept
{
  destroy();
  m_path = other.m_path;
  other.m_path = nullptr;
}

auto pref_path::unique(czstring org, czstring app) noexcept
    -> std::unique_ptr<pref_path>
{
  return std::make_unique<pref_path>(org, app);
}

auto pref_path::shared(czstring org, czstring app) noexcept
    -> std::shared_ptr<pref_path>
{
  return std::make_shared<pref_path>(org, app);
}

}  // namespace centurion
