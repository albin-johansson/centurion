#pragma once
#include <SDL_scancode.h>
#include <memory>
#include "action.h"
#include "key_trigger.h"

namespace centurion {
namespace keys {

class Key {
 private:
  SDL_Scancode scancode;
  centurion::events::KeyTrigger keyTrigger;
  centurion::events::Action_sptr action;

 public:
  Key(SDL_Scancode scancode, centurion::events::Action_sptr action,
      centurion::events::KeyTrigger keyTrigger);

  ~Key();

  void Trigger();

  inline SDL_Scancode GetScancode() const noexcept { return scancode; }

  inline centurion::events::KeyTrigger GetKeyTrigger() const noexcept {
    return keyTrigger;
  }
};

typedef std::shared_ptr<centurion::keys::Key> Key_sptr;
typedef std::unique_ptr<centurion::keys::Key> Key_uptr;
typedef std::weak_ptr<centurion::keys::Key> Key_wptr;

}  // namespace keys
}  // namespace centurion
