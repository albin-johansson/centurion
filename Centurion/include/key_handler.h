#pragma once
#include <SDL_keyboard.h>
#include <SDL_stdinc.h>
#include <memory>
#include <vector>
#include "key.h"

namespace centurion {
namespace keys {

class KeyHandler final {
 private:
  const Uint8* stateArr;
  int nKeys;
  std::vector<Uint8> prevStates;
  std::vector<centurion::keys::Key_sptr> keys;

  void CopyStates();

  inline bool WasReleased(SDL_Scancode scancode) const {
    return prevStates.at(scancode) && !stateArr[scancode];
  };

  bool ShouldTriggerKeyAction(const centurion::keys::Key_sptr key) const;

 public:
  KeyHandler();

  ~KeyHandler();

  void Update();

  void AddKey(centurion::keys::Key_sptr key);
};

typedef std::shared_ptr<centurion::keys::KeyHandler> KeyHandler_sptr;
typedef std::unique_ptr<centurion::keys::KeyHandler> KeyHandler_uptr;
typedef std::weak_ptr<centurion::keys::KeyHandler> KeyHandler_wptr;

}  // namespace keys
}  // namespace centurion