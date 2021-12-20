#ifndef CENTURION_CORE_HINTS_HPP_
#define CENTURION_CORE_HINTS_HPP_

#include <SDL.h>

#include <cassert>  // assert

#include "../common.hpp"

namespace cen {

// TODO

/// \addtogroup core
/// \{

enum class hint_priority {
  low = SDL_HINT_DEFAULT,       ///< The lowest possible priority.
  normal = SDL_HINT_NORMAL,     ///< The priority used by default by `set_hint`.
  override = SDL_HINT_OVERRIDE  ///< The highest priority.
};

inline auto set_hint(const char* name,
                     const char* value,
                     const hint_priority priority = hint_priority::normal) noexcept -> Result
{
  assert(name);
  assert(value);
  return SDL_SetHintWithPriority(name, value, static_cast<SDL_HintPriority>(priority));
}

inline auto set_hint(const char* name,
                     const bool value,
                     const hint_priority priority = hint_priority::normal) noexcept -> Result
{
  return set_hint(name, value ? "1" : "0", priority);
}

[[nodiscard]] inline auto hint(const char* name) noexcept -> const char*
{
  assert(name);
  return SDL_GetHint(name);
}

/// \} End of group core

}  // namespace cen

#endif  // CENTURION_CORE_HINTS_HPP_
