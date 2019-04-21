#include "ctn_mouse_listener_composite.h"

namespace centurion {
namespace input {

MouseListenerComposite::MouseListenerComposite() {
  children = std::vector<IMouseListener_sptr>(10);
}

MouseListenerComposite::~MouseListenerComposite() { RemoveChildren(); }

void MouseListenerComposite::MousePressed(const MouseState& mouse) {
  for (IMouseListener_sptr ml : children) {
    if (ml != nullptr) {
      ml->MousePressed(mouse);
    }
  }
}

void MouseListenerComposite::MouseReleased(const MouseState& mouse) {
  for (IMouseListener_sptr ml : children) {
    if (ml != nullptr) {
      ml->MouseReleased(mouse);
    }
  }
}

void MouseListenerComposite::RemoveChildren() noexcept { children.clear(); }

void MouseListenerComposite::AddChild(IMouseListener_sptr child) {
  if (child != nullptr) {
    children.push_back(child);
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