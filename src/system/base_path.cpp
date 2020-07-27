#include <SDL.h>

#include "paths.hpp"

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

}  // namespace centurion
