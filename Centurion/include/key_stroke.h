#pragma once
#include <SDL_events.h>
#include <memory>
#include "action.h"

namespace centurion {
namespace events {

/**
\brief The Keycode enum is equivalent to the SDL_Keycode enum. It provides the
possible keycode values.
*/
typedef SDL_Keycode Keycode;

/**
\brief The KeyTrigger enum specifies when a KeyStroke is activated.
*/
enum KeyTrigger { IMMEDIATE = SDL_KEYDOWN, RELEASE = SDL_KEYUP };

class KeyStroke {
 private:
  std::shared_ptr<centurion::events::Action> action;
  KeyTrigger trigger;
  Keycode keycode;

  inline bool shouldExecute(const SDL_Event& e) {
    bool isKeyEvent = (e.type == SDL_KEYUP) || (e.type == SDL_KEYDOWN);
    bool isMatching = (e.key.keysym.sym == keycode) && (e.key.type == trigger);
    return isKeyEvent && isMatching;
  }

 public:
  KeyStroke(Keycode keycode, std::shared_ptr<centurion::events::Action> action,
            KeyTrigger trigger);

  ~KeyStroke();

  void Update(const SDL_Event& e);

  void Trigger();
};

}  // namespace events
}  // namespace centurion