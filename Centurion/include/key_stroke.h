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

/**
\brief The KeyStroke class represents an key controlled action.
*/
class KeyStroke {
 private:
  std::shared_ptr<centurion::events::Action> action;
  KeyTrigger trigger;
  Keycode keycode;
  bool isRepeatable;

  inline bool shouldExecute(const SDL_Event& e) {
    if (!isRepeatable && e.key.repeat) {
      return false;
    }

    bool isKeyEvent = (e.type == SDL_KEYUP) || (e.type == SDL_KEYDOWN);
    bool isMatching = (e.key.keysym.sym == keycode) && (e.key.type == trigger);
    bool b = isRepeatable && e.key.repeat;
    return isKeyEvent && isMatching;
  }

 public:
  /**
  \param keycode - the key code of the key that will trigger the KeyStroke.
  \param action - the Action that will be executed when the related key is
  pressed/released. \param trigger - the KeyTrigger value which specifies the
  preferred moment of activation.
  */
  KeyStroke(Keycode keycode, std::shared_ptr<centurion::events::Action> action,
            KeyTrigger trigger);

  ~KeyStroke();

  /**
  \brief Updates this KeyStroke by comparing it to the supplied event.
  \param e - The event that will be checked.
  */
  void Update(const SDL_Event& e);

  /**
  \brief Programmatically triggers the Action related to this KeyStroke.
  */
  void Trigger();

  /**
  \brief Assigns whether or not this KeyStroke may be continously triggered by
  holding down the related key. This is only applicable if this KeyStroke is
  triggered when the related key is PRESSED. By default, all KeyStrokes have
  this set to FALSE.
  \param isRepeatable - the new value dictating whether this
  KeyStroke is repeatable.
  */
  void SetRepeatable(bool isRepeatable);

  /**
  \brief Indicates whether or not this KeyStroke is repeatable.
  */
  bool IsRepeatable() { return isRepeatable; }
};

}  // namespace events
}  // namespace centurion