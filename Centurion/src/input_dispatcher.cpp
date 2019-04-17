#include "input_dispatcher.h"
#include <SDL_events.h>

namespace centurion {
namespace input {

InputDispatcher::InputDispatcher() {
  mouseListenerComposite = std::make_unique<MouseListenerComposite>();
  keyListenerComposite = KeyListenerComposite::CreateUnique();
  mouseState = std::make_unique<MouseState>();
  keyState = std::make_unique<KeyState>();
  shouldQuit = false;
}

InputDispatcher::~InputDispatcher() = default;

void InputDispatcher::Update() {
  SDL_PumpEvents();
  shouldQuit = SDL_QuitRequested();

  keyState->Update();
  NotifyKeyListeners();

  mouseState->Update();
  NotifyMouseListeners();
}

void InputDispatcher::NotifyKeyListeners() {
  // TODO should probably be optimized, if possible.
  keyListenerComposite->KeyPressed(*keyState);
  keyListenerComposite->KeyReleased(*keyState);
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