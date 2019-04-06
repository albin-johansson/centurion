#pragma once
#include <SDL_config.h>
#include <SDL_events.h>
#include "key_trigger.h"

namespace centurion {
namespace events {

class KeyboardEvent {
 private:
  SDL_Event event;

 public:
  explicit KeyboardEvent(SDL_Event event);

  ~KeyboardEvent();

  bool IsRepeated() const;

  bool WasPressed() const;

  bool WasReleased() const;

  SDL_Keycode GetKeycode() const;

  uint32_t GetKeyEventType() const;
};

}  // namespace events
}  // namespace centurion