#include <SDL.h>

#include <type_traits>

#include "paths.hpp"

namespace cen {

static_assert(std::is_default_constructible_v<base_path>);
static_assert(std::is_nothrow_move_constructible_v<base_path>);
static_assert(std::is_nothrow_move_assignable_v<base_path>);
static_assert(!std::is_copy_constructible_v<base_path>);
static_assert(!std::is_copy_assignable_v<base_path>);

base_path::base_path() : m_path{SDL_GetBasePath()}
{}

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

}  // namespace cen
