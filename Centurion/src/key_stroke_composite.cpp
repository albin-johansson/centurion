#include "key_stroke_composite.h"

using std::shared_ptr;
using std::vector;

namespace centurion {
namespace events {

KeyStrokeComposite::KeyStrokeComposite() {
  keyStrokes = vector<shared_ptr<KeyStroke>>();
}

KeyStrokeComposite::~KeyStrokeComposite() { Clear(); }

void KeyStrokeComposite::Update(const Event& event) {
  for (shared_ptr<KeyStroke> keyStroke : keyStrokes) {
    if (keyStroke != nullptr) {
      keyStroke->Update(event);
    }
  }
}

void KeyStrokeComposite::AddKeyStroke(shared_ptr<KeyStroke> keyStroke) {
  keyStrokes.push_back(keyStroke);
  keyStrokes.shrink_to_fit();
}

void KeyStrokeComposite::Clear() { keyStrokes.clear(); }

KeyStrokeComposite_sptr KeyStrokeComposite::CreateShared() {
  return std::shared_ptr<KeyStrokeComposite>();
}

KeyStrokeComposite_uptr KeyStrokeComposite::CreateUnique() {
  return std::unique_ptr<KeyStrokeComposite>();
}

KeyStrokeComposite_wptr KeyStrokeComposite::CreateWeak() {
  return CreateShared();
}

}  // namespace events
}  // namespace centurion