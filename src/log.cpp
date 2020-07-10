#ifndef CENTURION_LOG_SOURCE
#define CENTURION_LOG_SOURCE

#include "log.hpp"

namespace centurion::log {

CENTURION_DEF
void reset_priorities() noexcept
{
  SDL_LogResetPriorities();
}

CENTURION_DEF
void set_priority(category category, priority prio) noexcept
{
  SDL_LogSetPriority(static_cast<int>(category),
                     static_cast<SDL_LogPriority>(prio));
}

CENTURION_DEF
void set_priority(priority prio) noexcept
{
  const auto p = static_cast<SDL_LogPriority>(prio);
  SDL_LogSetAllPriority(p);

  // Apparently not set by SDL
  SDL_LogSetPriority(SDL_LOG_CATEGORY_TEST, p);
}

CENTURION_DEF
auto get_priority(category category) noexcept -> priority
{
  return static_cast<priority>(SDL_LogGetPriority(static_cast<int>(category)));
}

}  // namespace centurion::log

#endif  // CENTURION_LOG_SOURCE