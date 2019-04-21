#include "mouse_listener_composite.h"

namespace centurion {
namespace input {

MouseListenerComposite::MouseListenerComposite() {
  listeners = std::vector<IMouseListener_sptr>(10);
}

MouseListenerComposite::~MouseListenerComposite() { RemoveChildren(); }

void MouseListenerComposite::MousePressed(const MouseState& mouse) {
  for (IMouseListener_sptr ml : listeners) {
    if (ml != nullptr) {
      ml->MousePressed(mouse);
    }
  }
}

void MouseListenerComposite::MouseReleased(const MouseState& mouse) {
  for (IMouseListener_sptr ml : listeners) {
    if (ml != nullptr) {
      ml->MouseReleased(mouse);
    }
  }
}

void MouseListenerComposite::RemoveChildren() noexcept { listeners.clear(); }

void MouseListenerComposite::AddChild(IMouseListener_sptr ml) {
  if (ml != nullptr) {
    listeners.push_back(ml);
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