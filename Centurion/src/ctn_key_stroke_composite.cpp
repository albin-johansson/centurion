#include "ctn_key_stroke_composite.h"

namespace centurion {
namespace events {

// FIXME should extend KeyStroke interface

KeyStrokeComposite::KeyStrokeComposite() {
  keyStrokes = std::vector<KeyStroke_sptr>(10);
}

KeyStrokeComposite::~KeyStrokeComposite() { Clear(); }

void KeyStrokeComposite::Update(const Event& event) {
  for (KeyStroke_sptr keyStroke : keyStrokes) {
    if (keyStroke != nullptr) {
      keyStroke->Update(event);
    }
  }
}

void KeyStrokeComposite::AddKeyStroke(KeyStroke_sptr keyStroke) {
  keyStrokes.push_back(keyStroke);
  keyStrokes.shrink_to_fit();
}

void KeyStrokeComposite::Clear() noexcept { keyStrokes.clear(); }

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