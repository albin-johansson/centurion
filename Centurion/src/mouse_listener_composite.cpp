#include "mouse_listener_composite.h"

namespace centurion {
namespace input {

MouseListenerComposite::MouseListenerComposite() {
  listeners = std::vector<MouseListener_sptr>(10);
}

MouseListenerComposite::~MouseListenerComposite() { RemoveChildren(); }

void MouseListenerComposite::MousePressed(const MouseState& mouse) {
  for (MouseListener_sptr ml : listeners) {
    if (ml != nullptr) {
      ml->MousePressed(mouse);
    }
  }
}

void MouseListenerComposite::MouseReleased(const MouseState& mouse) {
  for (MouseListener_sptr ml : listeners) {
    if (ml != nullptr) {
      ml->MouseReleased(mouse);
    }
  }
}

void MouseListenerComposite::RemoveChildren() noexcept { listeners.clear(); }

void MouseListenerComposite::AddChild(MouseListener_sptr ml) {
  if (ml != nullptr) {
    listeners.push_back(ml);
  }
}

}  // namespace input
}  // namespace centurion