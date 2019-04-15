#pragma once
#include <SDL_events.h>

namespace centurion {
namespace events {

/**
\brief The KeyTrigger enum specifies when a key is activated.
\since 1.0.0
*/
enum class KeyTrigger { IMMEDIATE = SDL_KEYDOWN, RELEASE = SDL_KEYUP };

}  // namespace events
}  // namespace centurion