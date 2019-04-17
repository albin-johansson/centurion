#include "input_dispatcher.h"
#include <SDL_events.h>

namespace centurion {
namespace input {

InputDispatcher::InputDispatcher() {
  mouseListenerComposite = std::make_unique<MouseListenerComposite>();
  keyListenerComposite = std::make_unique<KeyListenerComposite>();
  mouseState = std::make_unique<MouseState>();
  keyState = std::make_unique<KeyState>();
}

InputDispatcher::~InputDispatcher() = default;

void InputDispatcher::Update() {
  SDL_PumpEvents();

  keyState->Update();
  NotifyKeyListeners();

  mouseState->Update();
  NotifyMouseListeners();
}

void InputDispatcher::NotifyKeyListeners() {
  // TODO
}

void InputDispatcher::NotifyMouseListeners() {
  if (mouseState->IsButtonPressed(MouseState::COMPLETE_MASK)) {
    mouseListenerComposite->MousePressed(*mouseState);
  }
  if (mouseState->WasButtonReleased(MouseState::COMPLETE_MASK)) {
    mouseListenerComposite->MouseReleased(*mouseState);
  }
}

void InputDispatcher::AddMouseListener(MouseListener_sptr ml) {
  mouseListenerComposite->AddChild(ml);
}

void InputDispatcher::AddKeyListener(KeyListener_sptr kl) {
  keyListenerComposite->AddChild(kl);
}

}  // namespace input
}  // namespace centurion