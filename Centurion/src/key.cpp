#include "key.h"

using centurion::events::Action_sptr;
using centurion::events::KeyTrigger;

namespace centurion {
namespace keys {

Key::Key(SDL_Scancode scancode, Action_sptr action, KeyTrigger keyTrigger) {
  this->scancode = scancode;
  this->action = action;
  this->keyTrigger = keyTrigger;
}

Key::~Key() = default;

void Key::Trigger() {
  if (action != nullptr) {
    action->Execute();
  }
}

}  // namespace keys
}  // namespace centurion
