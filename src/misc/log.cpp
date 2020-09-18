#include "log.hpp"

namespace cen::log {

void reset_priorities() noexcept
{
  SDL_LogResetPriorities();
}

void set_priority(category category, priority prio) noexcept
{
  SDL_LogSetPriority(static_cast<int>(category),
                     static_cast<SDL_LogPriority>(prio));
}

void set_priority(priority prio) noexcept
{
  const auto p = static_cast<SDL_LogPriority>(prio);
  SDL_LogSetAllPriority(p);

  // Apparently not set by SDL
  SDL_LogSetPriority(SDL_LOG_CATEGORY_TEST, p);
}

auto get_priority(category category) noexcept -> priority
{
  return static_cast<priority>(SDL_LogGetPriority(static_cast<int>(category)));
}

}  // namespace cen::log
