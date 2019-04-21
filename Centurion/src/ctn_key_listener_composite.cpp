#include "ctn_key_listener_composite.h"

namespace centurion {
namespace input {

KeyListenerComposite::KeyListenerComposite() {
  children = std::vector<IKeyListener_sptr>(10);
}

KeyListenerComposite::~KeyListenerComposite() { RemoveChildren(); }

void KeyListenerComposite::StateUpdated(const KeyState& state) {
  for (IKeyListener_sptr child : children) {
    if (child != nullptr) {
      child->StateUpdated(state);
    }
  }
}

void KeyListenerComposite::AddChild(IKeyListener_sptr kl) {
  if (kl != nullptr) {
    children.push_back(kl);
  }
}

void KeyListenerComposite::RemoveChildren() noexcept { children.clear(); }

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