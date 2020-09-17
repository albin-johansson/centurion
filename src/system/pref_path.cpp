#include <SDL.h>

#include "paths.hpp"

namespace centurion {

pref_path::pref_path(nn_czstring org, nn_czstring app)
    : m_path{SDL_GetPrefPath(org, app)}
{}

auto to_string(const pref_path& path) -> std::string
{
  const std::string str = path ? path.get() : "N/A";
  return "[pref_path | path: \"" + str + "\"]";
}

auto operator<<(std::ostream& stream, const pref_path& path) -> std::ostream&
{
  stream << to_string(path);
  return stream;
}

}  // namespace centurion
