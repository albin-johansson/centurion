#include "ctn_key_stroke.h"
#include <memory>
#include <stdexcept>
#include "ctn_action.h"

namespace centurion {
namespace events {

KeyStroke::KeyStroke(SDL_Keycode keycode, IAction_sptr action,
                     KeyTrigger trigger) {
  if (action == nullptr) {
    throw std::invalid_argument("Null action parameter!");
  } else {
    this->keycode = keycode;
    this->action = action;
    this->trigger = trigger;
    isRepeatable = false;
  }
}

KeyStroke::~KeyStroke() = default;

bool KeyStroke::ShouldExecute(const Event& e) {
  KeyEvent kEvent = e.GetKeyboardInfo();

  if (!isRepeatable && kEvent.IsRepeated()) {
    return false;
  }
  // TODO fix repeatable issue when one key is held and another one is then
  // pressed
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

void KeyStroke::SetRepeatable(bool isRepeatable) noexcept {
  this->isRepeatable = isRepeatable;
}

IKeyStroke_sptr KeyStroke::CreateShared(SDL_Keycode keycode,
                                        IAction_sptr action,
                                        KeyTrigger trigger) {
  return std::make_shared<KeyStroke>(keycode, action, trigger);
}

IKeyStroke_uptr KeyStroke::CreateUnique(SDL_Keycode keycode,
                                        IAction_sptr action,
                                        KeyTrigger trigger) {
  return std::make_unique<KeyStroke>(keycode, action, trigger);
}

}  // namespace events
}  // namespace centurion