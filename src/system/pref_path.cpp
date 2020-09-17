#include <SDL.h>

#include <type_traits>

#include "paths.hpp"

namespace centurion {

static_assert(std::is_nothrow_move_constructible_v<pref_path>);
static_assert(std::is_nothrow_move_assignable_v<pref_path>);
static_assert(!std::is_copy_constructible_v<pref_path>);
static_assert(!std::is_copy_assignable_v<pref_path>);

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
