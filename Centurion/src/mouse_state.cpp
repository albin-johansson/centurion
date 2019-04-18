#include "mouse_state.h"

using centurion::geo::Point;

namespace centurion {
namespace input {

MouseState::MouseState() {
  x = 0;
  y = 0;
  prevMask = 0;
  currentMask = 0;
}

MouseState::~MouseState() = default;

void MouseState::Update() noexcept {
  prevMask = currentMask;
  currentMask = SDL_GetMouseState(&x, &y);
}

bool MouseState::IsButtonPressed(Uint32 buttonMask) const noexcept {
  if (!IsValidMask(buttonMask)) {
    return false;
  } else {
    return (currentMask & buttonMask);
  }
}

bool MouseState::WasButtonReleased(Uint32 buttonMask) const noexcept {
  if (!IsValidMask(buttonMask)) {
    return false;
  } else {
    return !(currentMask & buttonMask) && (prevMask & buttonMask);
  }
}

bool MouseState::IsLeftButtonPressed() const noexcept {
  return (currentMask & SDL_BUTTON_LMASK);
}

bool MouseState::IsRightButtonPressed() const noexcept {
  return (currentMask & SDL_BUTTON_RMASK);
}

bool MouseState::WasLeftButtonReleased() const noexcept {
  return !(currentMask & SDL_BUTTON_LMASK) && (prevMask | SDL_BUTTON_LMASK);
}

bool MouseState::WasRightButtonReleased() const noexcept {
  return !(currentMask & SDL_BUTTON_RMASK) && (prevMask | SDL_BUTTON_RMASK);
}

Point MouseState::GetPoint() const noexcept { return Point(x, y); }

MouseState_sptr MouseState::CreateShared() {
  return std::make_shared<MouseState>();
}

MouseState_uptr MouseState::CreateUnique() {
  return std::make_unique<MouseState>();
}

MouseState_wptr MouseState::CreateWeak() { return CreateShared(); }

}  // namespace input
}  // namespace centurion