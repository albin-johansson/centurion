#include "key_listener_composite.h"

namespace centurion {
namespace input {

KeyListenerComposite::KeyListenerComposite() {
  listeners = std::vector<KeyListener_sptr>(10);
}

KeyListenerComposite::~KeyListenerComposite() { RemoveChildren(); }

void KeyListenerComposite::KeyPressed(const KeyState& state) {
  for (KeyListener_sptr kl : listeners) {
    if (kl != nullptr) {
      kl->KeyPressed(state);
    }
  }
}

void KeyListenerComposite::KeyReleased(const KeyState& state) {
  for (KeyListener_sptr kl : listeners) {
    if (kl != nullptr) {
      kl->KeyReleased(state);
    }
  }
}

void KeyListenerComposite::AddChild(KeyListener_sptr kl) {
  if (kl != nullptr) {
    listeners.push_back(kl);
  }
}

void KeyListenerComposite::RemoveChildren() { listeners.clear(); }

KeyListenerComposite_sptr KeyListenerComposite::CreateShared() {
  return std::make_shared<KeyListenerComposite>();
}

KeyListenerComposite_uptr KeyListenerComposite::CreateUnique() {
  return std::make_unique<KeyListenerComposite>();
}

KeyListenerComposite_wptr KeyListenerComposite::CreateWeak() {
  return CreateShared();
}

}  // namespace input
}  // namespace centurion