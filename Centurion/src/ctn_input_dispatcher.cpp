#include "ctn_input_dispatcher.h"
#include <SDL_events.h>

namespace centurion {
namespace input {

InputDispatcher::InputDispatcher() {
  mouseListenerComposite = MouseListenerComposite::CreateUnique();
  keyListenerComposite = KeyListenerComposite::CreateUnique();
  mouseState = MouseState::CreateUnique();
  keyState = KeyState::CreateUnique();
}

InputDispatcher::~InputDispatcher() = default;

void InputDispatcher::Update() {
  SDL_PumpEvents();
  shouldQuit = IsEventActive(SDL_QUIT);
  shouldRevalidateImages = IsEventActive(SDL_RENDER_DEVICE_RESET);

  NotifyKeyListeners();
  keyState->Update();

  NotifyMouseListeners();
  mouseState->Update();
}

void InputDispatcher::NotifyKeyListeners() {
  keyListenerComposite->StateUpdated(*keyState);
}

void InputDispatcher::NotifyMouseListeners() {
  if (mouseState->IsButtonPressed(MouseState::COMPLETE_MASK)) {
    mouseListenerComposite->MousePressed(*mouseState);
  }
  if (mouseState->WasButtonReleased(MouseState::COMPLETE_MASK)) {
    mouseListenerComposite->MouseReleased(*mouseState);
  }
}

void InputDispatcher::AddMouseListener(IMouseListener_sptr ml) {
  mouseListenerComposite->AddChild(ml);
}

void InputDispatcher::AddKeyListener(IKeyListener_sptr kl) {
  keyListenerComposite->AddChild(kl);
}

void InputDispatcher::ResetRevalidationFlag() noexcept {
  shouldRevalidateImages = false;
}

InputDispatcher_sptr InputDispatcher::CreateShared() {
  return std::make_shared<InputDispatcher>();
}

InputDispatcher_uptr InputDispatcher::CreateUnique() {
  return std::make_unique<InputDispatcher>();
}

InputDispatcher_wptr InputDispatcher::CreateWeak() { return CreateShared(); }

}  // namespace input
}  // namespace centurion