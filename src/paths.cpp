#include "paths.hpp"

#include <SDL.h>

#include "centurion_utils.hpp"

namespace centurion {

base_path::base_path() : m_path{SDL_GetBasePath()}
{}

auto base_path::unique() -> uptr
{
  return std::make_unique<base_path>();
}

auto base_path::shared() -> sptr
{
  return std::make_shared<base_path>();
}

pref_path::pref_path(nn_czstring org, nn_czstring app)
    : m_path{SDL_GetPrefPath(org, app)}
{}

auto pref_path::unique(nn_czstring org, nn_czstring app) -> uptr
{
  return std::make_unique<pref_path>(org, app);
}

auto pref_path::shared(nn_czstring org, nn_czstring app) -> sptr
{
  return std::make_shared<pref_path>(org, app);
}

}  // namespace centurion
