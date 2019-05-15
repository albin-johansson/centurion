#include "ctn_key_stroke_composite.h"
#include <stdexcept>

namespace centurion {
namespace events {

KeyStrokeComposite::KeyStrokeComposite() {
  keyStrokes = std::vector<IKeyStroke_sptr>();
  keyStrokes.reserve(10);
}

KeyStrokeComposite::~KeyStrokeComposite() { Clear(); }

void KeyStrokeComposite::Update(const Event& event) {
  for (auto keyStroke : keyStrokes) {
    keyStroke->Update(event);
  }
}

void KeyStrokeComposite::AddKeyStroke(IKeyStroke_sptr keyStroke) {
  if (keyStroke == nullptr) {
    throw std::invalid_argument("Null KeyStroke pointer!");
  }
  keyStrokes.push_back(keyStroke);
}

void KeyStrokeComposite::Clear() noexcept {
  keyStrokes.clear();
  keyStrokes.shrink_to_fit();
  keyStrokes.reserve(10);
}

KeyStrokeComposite_sptr KeyStrokeComposite::CreateShared() {
  return std::shared_ptr<KeyStrokeComposite>();
}

KeyStrokeComposite_uptr KeyStrokeComposite::CreateUnique() {
  return std::unique_ptr<KeyStrokeComposite>();
}

}  // namespace events
}  // namespace centurion