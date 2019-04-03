#include "key_stroke_composite.h"

using std::shared_ptr;

namespace centurion {
namespace events {

KeyStrokeComposite::KeyStrokeComposite() {
  keyStrokes = std::vector<shared_ptr<KeyStroke>>();
}

KeyStrokeComposite::~KeyStrokeComposite() { Clear(); }

void KeyStrokeComposite::Update(const SDL_Event& event) {
  for (shared_ptr<KeyStroke> keyStroke : keyStrokes) {
    if (keyStroke != nullptr) {
      keyStroke->Update(event);
    }
  }
}

void KeyStrokeComposite::Add(shared_ptr<KeyStroke> keyStroke) {
  keyStrokes.push_back(keyStroke);
  keyStrokes.shrink_to_fit();
}

void KeyStrokeComposite::Clear() { keyStrokes.clear(); }

}  // namespace events
}  // namespace centurion