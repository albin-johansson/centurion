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
  keyListenerComposite->KeyStateUpdated(*keyState);
}

void InputDispatcher::NotifyMouseListeners() {
  mouseListenerComposite->MouseStateUpdated(*mouseState);
}

void InputDispatcher::AddMouseListener(IMouseListener_sptr ml) {
  mouseListenerComposite->AddChild(ml);
}

void InputDispatcher::AddKeyListener(IKeyListener_sptr kl) {
  keyListenerComposite->AddChild(kl);
}

void InputDispatcher::RemoveMouseListener(IMouseListener_sptr ml) {
  mouseListenerComposite->RemoveChild(ml);
}

void InputDispatcher::RemoveKeyListener(IKeyListener_sptr kl) {
  keyListenerComposite->RemoveChild(kl);
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