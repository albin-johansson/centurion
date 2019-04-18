#pragma once
#include <SDL_events.h>
#include <SDL_keycode.h>
#include <memory>
#include "action.h"
#include "event.h"
#include "key_trigger.h"

namespace centurion {
namespace events {

class KeyStroke;
typedef std::shared_ptr<KeyStroke> KeyStroke_sptr;
typedef std::unique_ptr<KeyStroke> KeyStroke_uptr;
typedef std::weak_ptr<KeyStroke> KeyStroke_wptr;

/**
\brief The KeyStroke class represents an key controlled action.
\since 1.0.0
*/
class KeyStroke {
 private:
  std::shared_ptr<centurion::events::Action> action;
  centurion::events::KeyTrigger trigger;
  SDL_Keycode keycode;
  bool isRepeatable;

  bool ShouldExecute(const centurion::events::Event& e);

 public:
  /**
  \param keycode - the key code of the key that will trigger the KeyStroke.
  \param action - the Action that will be executed when the related key
  is pressed/released.
  \param trigger - the KeyTrigger value which specifies the
  preferred moment of activation.
  */
  KeyStroke(SDL_Keycode keycode,
            std::shared_ptr<centurion::events::Action> action,
            centurion::events::KeyTrigger trigger);

  ~KeyStroke();

  /**
  \brief Updates this KeyStroke by comparing it to the supplied event.
  \param event - The event that will be checked.
  */
  void Update(const centurion::events::Event& event);

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
  void SetRepeatable(bool isRepeatable) noexcept;

  /**
  \brief Indicates whether or not this KeyStroke is repeatable.
  */
  inline bool IsRepeatable() const noexcept { return isRepeatable; }

  /**
  \brief Creates and returns a shared pointer that points to a KeyStroke
  instance.
  \param keycode - the key code of the key that will trigger the KeyStroke.
  \param action - the Action that will be executed when the related key is
  pressed/released.
  \param trigger - the KeyTrigger value which specifies the preferred moment of
  activation.
  */
  static KeyStroke_sptr CreateShared(SDL_Keycode keycode,
                                     centurion::events::Action_sptr action,
                                     centurion::events::KeyTrigger trigger);
  /**
  \brief Creates and returns a unique pointer that points to a KeyStroke
  instance.
  \param keycode - the key code of the key that will trigger the KeyStroke.
  \param action - the Action that will be executed when the related key is
  pressed/released.
  \param trigger - the KeyTrigger value which specifies the preferred moment of
  activation.
  */
  static KeyStroke_uptr CreateUnique(SDL_Keycode keycode,
                                     centurion::events::Action_sptr action,
                                     centurion::events::KeyTrigger trigger);
  /**
  \brief Creates and returns a weak pointer that points to a KeyStroke
  instance.
  \param keycode - the key code of the key that will trigger the KeyStroke.
  \param action - the Action that will be executed when the related key is
  pressed/released.
  \param trigger - the KeyTrigger value which specifies the preferred moment of
  activation.
  */
  static KeyStroke_wptr CreateWeak(SDL_Keycode keycode,
                                   centurion::events::Action_sptr action,
                                   centurion::events::KeyTrigger trigger);
};

}  // namespace events
}  // namespace centurion