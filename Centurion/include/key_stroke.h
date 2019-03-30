#pragma once
#include <SDL_events.h>
#include "action.h"

namespace centurion {
namespace events {

class KeyStroke {
 private:
  SDL_Keycode keycode;
  SDL_EventType eventType;
  centurion::events::Action& action;

 public:
  // TODO enum for key values, enum for event types
  KeyStroke(SDL_Keycode keycode, SDL_EventType type,
            centurion::events::Action& action);

  ~KeyStroke();

  void Check(SDL_Event& e);
};

}  // namespace events
}  // namespace centurion