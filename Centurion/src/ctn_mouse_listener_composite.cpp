#include "ctn_mouse_listener_composite.h"

namespace centurion {
namespace input {

MouseListenerComposite::MouseListenerComposite() {
  children = std::vector<IMouseListener_sptr>();
  children.reserve(10);
}

MouseListenerComposite::~MouseListenerComposite() { RemoveChildren(); }

void MouseListenerComposite::MouseStateUpdated(const MouseState& mouse) {
  for (IMouseListener_sptr ml : children) {
    ml->MouseStateUpdated(mouse);
  }
}

void MouseListenerComposite::RemoveChildren() noexcept { children.clear(); }

void MouseListenerComposite::AddChild(IMouseListener_sptr child) {
  if (child != nullptr) {
    children.push_back(child);
  }
}

void MouseListenerComposite::RemoveChild(IMouseListener_sptr child) {
  if (child != nullptr) {
    auto iterator = std::find(children.begin(), children.end(), child);
    if (iterator != children.end()) {
      children.erase(iterator);
      children.shrink_to_fit();
    }
  }
}

MouseListenerComposite_sptr MouseListenerComposite::CreateShared() {
  return std::make_shared<MouseListenerComposite>();
}

MouseListenerComposite_uptr MouseListenerComposite::CreateUnique() {
  return std::make_unique<MouseListenerComposite>();
}

MouseListenerComposite_wptr MouseListenerComposite::CreateWeak() {
  return CreateShared();
}

}  // namespace input
}  // namespace centurion