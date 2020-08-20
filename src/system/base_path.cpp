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

auto to_string(const base_path& path) -> std::string
{
  const std::string str = path ? path.get() : "N/A";
  return "[base_path | path: \"" + str + "\"]";
}

auto operator<<(std::ostream& stream, const base_path& path) -> std::ostream&
{
  stream << to_string(path);
  return stream;
}

}  // namespace centurion
