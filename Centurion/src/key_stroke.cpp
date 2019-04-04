#include "key_stroke.h"
#include <memory>
#include <stdexcept>
#include "action.h"

using centurion::events::Action;
using std::invalid_argument;
using std::shared_ptr;

namespace centurion {
namespace events {

KeyStroke::KeyStroke(Keycode keycode, shared_ptr<Action> action,
                     KeyTrigger trigger) {
  if (action == nullptr) {
    throw invalid_argument("Null action parameter when creating KeyStroke!");
  } else {
    this->keycode = keycode;
    this->action = action;
    this->trigger = trigger;
    isRepeatable = false;
  }
}

KeyStroke::~KeyStroke() = default;

bool KeyStroke::ShouldExecute(const Event& e) {
  SDL_KeyboardEvent keyInfo = e.GetKeyInfo();

  if (!isRepeatable && keyInfo.repeat) {
    return false;
  }

  bool isKeyEvent =
      (keyInfo.type == SDL_KEYUP) || (keyInfo.type == SDL_KEYDOWN);

  bool match = (keyInfo.keysym.sym == keycode) && (keyInfo.type == trigger);

  return isKeyEvent && match;
}

void KeyStroke::Update(const Event& e) {
  if (ShouldExecute(e)) {
    action->Execute();
  }
}

void KeyStroke::Trigger() { action->Execute(); }

void KeyStroke::SetRepeatable(bool isRepeatable) {
  this->isRepeatable = isRepeatable;
}

}  // namespace events
}  // namespace centurion