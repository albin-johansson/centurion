#include "key_listener_composite.h"

namespace centurion {
namespace input {

KeyListenerComposite::KeyListenerComposite() {
  listeners = std::vector<IKeyListener_sptr>(10);
}

KeyListenerComposite::~KeyListenerComposite() { RemoveChildren(); }

void KeyListenerComposite::StateUpdated(const KeyState& state) {
  for (IKeyListener_sptr kl : listeners) {
    if (kl != nullptr) {
      kl->StateUpdated(state);
    }
  }
}

void KeyListenerComposite::AddChild(IKeyListener_sptr kl) {
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