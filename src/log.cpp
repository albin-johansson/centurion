#ifndef CENTURION_LOG_SOURCE
#define CENTURION_LOG_SOURCE

#include "log.h"

namespace centurion {

CENTURION_DEF
void Log::reset_priorities() noexcept
{
  SDL_LogResetPriorities();
}

CENTURION_DEF
void Log::set_priority(Log::Category category, Log::Priority prio) noexcept
{
  SDL_LogSetPriority(static_cast<int>(category),
                     static_cast<SDL_LogPriority>(prio));
}

CENTURION_DEF
void Log::set_priority(Log::Priority prio) noexcept
{
  const auto p = static_cast<SDL_LogPriority>(prio);
  SDL_LogSetAllPriority(p);
  SDL_LogSetPriority(SDL_LOG_CATEGORY_TEST, p);  // Apparently not set by SDL
}

CENTURION_DEF
Log::Priority Log::priority(Log::Category category) noexcept
{
  return static_cast<Log::Priority>(
      SDL_LogGetPriority(static_cast<int>(category)));
}

CENTURION_DEF
bool operator==(Log::Category lhs, SDL_LogCategory rhs) noexcept
{
  return static_cast<SDL_LogCategory>(lhs) == rhs;
}

CENTURION_DEF
bool operator==(SDL_LogCategory lhs, Log::Category rhs) noexcept
{
  return lhs == static_cast<SDL_LogCategory>(rhs);
}

CENTURION_DEF
bool operator!=(Log::Category lhs, SDL_LogCategory rhs) noexcept
{
  return !(lhs == rhs);
}

CENTURION_DEF
bool operator!=(SDL_LogCategory lhs, Log::Category rhs) noexcept
{
  return !(lhs == rhs);
}

CENTURION_DEF
bool operator==(Log::Priority lhs, SDL_LogPriority rhs) noexcept
{
  return static_cast<SDL_LogPriority>(lhs) == rhs;
}

CENTURION_DEF
bool operator==(SDL_LogPriority lhs, Log::Priority rhs) noexcept
{
  return lhs == static_cast<SDL_LogPriority>(rhs);
}

CENTURION_DEF
bool operator!=(Log::Priority lhs, SDL_LogPriority rhs) noexcept
{
  return !(lhs == rhs);
}

CENTURION_DEF
bool operator!=(SDL_LogPriority lhs, Log::Priority rhs) noexcept
{
  return !(lhs == rhs);
}

}  // namespace centurion

#endif  // CENTURION_LOG_SOURCE