#include "ctn_key_listener_composite.h"
#include <algorithm>

namespace centurion {
namespace input {

KeyListenerComposite::KeyListenerComposite() {
  children = std::vector<IKeyListener_sptr>();
  children.reserve(10);
}

KeyListenerComposite::~KeyListenerComposite() { RemoveChildren(); }

void KeyListenerComposite::KeyStateUpdated(const KeyState& state) {
  for (IKeyListener_sptr child : children) {
    // if (child != nullptr) {
    child->KeyStateUpdated(state);
    //}
  }
}

void KeyListenerComposite::AddChild(IKeyListener_sptr kl) {
  if (kl != nullptr) {
    children.push_back(kl);
  }
}

void KeyListenerComposite::RemoveChild(IKeyListener_sptr kl) {
  if (kl != nullptr) {
    auto iterator = std::find(children.begin(), children.end(), kl);
    if (iterator != children.end()) {
      children.erase(iterator);
      children.shrink_to_fit();
    }
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