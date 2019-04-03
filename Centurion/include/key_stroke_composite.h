#pragma once
#include <memory>
#include <vector>
#include "key_stroke.h"

namespace centurion {
namespace events {

class KeyStrokeComposite final {  // FIXME should extend KeyStroke interface
 private:
  std::vector<std::shared_ptr<centurion::events::KeyStroke>> keyStrokes;

 public:
  KeyStrokeComposite();

  ~KeyStrokeComposite();

  void Update(const SDL_Event& event);

  void Add(std::shared_ptr<centurion::events::KeyStroke> keyStroke);

  void Clear();
};

}  // namespace events
}  // namespace centurion