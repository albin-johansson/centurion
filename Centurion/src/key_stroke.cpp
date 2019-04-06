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
  KeyboardEvent kEvent = e.GetKeyboardInfo();

  if (!isRepeatable && kEvent.IsRepeated()) {
    return false;
  }

  bool down = ((trigger == KeyTrigger::IMMEDIATE) &&
               (kEvent.GetKeyEventType() == SDL_KEYDOWN));
  bool up = ((trigger == KeyTrigger::RELEASE) &&
             (kEvent.GetKeyEventType() == SDL_KEYUP));
  bool match = (kEvent.GetKeycode() == keycode) && (down || up);

  return e.IsKeyEvent() && match;
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