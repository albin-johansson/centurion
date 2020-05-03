#ifndef CENTURION_EVENT_TYPE_SOURCE
#define CENTURION_EVENT_TYPE_SOURCE

#include "event_type.h"

namespace centurion {
namespace event {

CENTURION_DEF
bool operator==(EventType lhs, SDL_EventType rhs) noexcept
{
  return static_cast<SDL_EventType>(lhs) == rhs;
}

CENTURION_DEF
bool operator==(SDL_EventType lhs, EventType rhs) noexcept
{
  return lhs == static_cast<SDL_EventType>(rhs);
}

CENTURION_DEF
bool operator!=(EventType lhs, SDL_EventType rhs) noexcept
{
  return !(lhs == rhs);
}

CENTURION_DEF
bool operator!=(SDL_EventType lhs, EventType rhs) noexcept
{
  return !(lhs == rhs);
}

}  // namespace event
}  // namespace centurion

#endif  // CENTURION_EVENT_TYPE_SOURCE