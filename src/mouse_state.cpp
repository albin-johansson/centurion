#ifndef CENTURION_MOUSE_STATE_SOURCE
#define CENTURION_MOUSE_STATE_SOURCE

#include "mouse_state.h"

#include <SDL.h>

#include <cstdint>

#include "window.h"

namespace centurion {

CENTURION_DEF MouseState::MouseState() noexcept = default;

CENTURION_DEF std::unique_ptr<MouseState> MouseState::unique() {
  return std::make_unique<MouseState>();
}

CENTURION_DEF std::shared_ptr<MouseState> MouseState::shared() {
  return std::make_shared<MouseState>();
}

CENTURION_DEF void MouseState::window_updated(const Window& window) noexcept {
  windowWidth = window.get_width();
  windowHeight = window.get_height();
}

CENTURION_DEF void MouseState::update() noexcept {
  oldX = mouseX;
  oldY = mouseY;
  prevLeftPressed = leftPressed;
  prevRightPressed = rightPressed;

  {
    const uint32_t mask = SDL_GetMouseState(&mouseX, &mouseY);
    leftPressed = mask & SDL_BUTTON(SDL_BUTTON_LEFT);
    rightPressed = mask & SDL_BUTTON(SDL_BUTTON_RIGHT);
  }

  {
    const auto xRatio =
        static_cast<float>(mouseX) / static_cast<float>(windowWidth);
    const auto adjustedX = xRatio * static_cast<float>(logicalWidth);

    const auto yRatio =
        static_cast<float>(mouseY) / static_cast<float>(windowHeight);
    const auto adjustedY = yRatio * static_cast<float>(logicalHeight);

    mouseX = static_cast<int>(adjustedX);
    mouseY = static_cast<int>(adjustedY);
  }
}

CENTURION_DEF void MouseState::reset() noexcept {
  logicalWidth = 1;
  logicalHeight = 1;
  windowWidth = 1;
  windowHeight = 1;
}

CENTURION_DEF void MouseState::set_logical_width(int logicalWidth) noexcept {
  if (logicalWidth <= 0) {
    logicalWidth = 1;
  }
  this->logicalWidth = logicalWidth;
}

CENTURION_DEF void MouseState::set_logical_height(int logicalHeight) noexcept {
  if (logicalHeight <= 0) {
    logicalHeight = 1;
  }
  this->logicalHeight = logicalHeight;
}

CENTURION_DEF void MouseState::set_window_width(int windowWidth) noexcept {
  if (windowWidth <= 0) {
    windowWidth = 1;
  }
  this->windowWidth = windowWidth;
}

CENTURION_DEF void MouseState::set_window_height(int windowHeight) noexcept {
  if (windowHeight <= 0) {
    windowHeight = 1;
  }
  this->windowHeight = windowHeight;
}

CENTURION_DEF int MouseState::get_mouse_x() const noexcept { return mouseX; }

CENTURION_DEF int MouseState::get_mouse_y() const noexcept { return mouseY; }

CENTURION_DEF bool MouseState::is_left_button_pressed() const noexcept {
  return leftPressed;
}

CENTURION_DEF bool MouseState::is_right_button_pressed() const noexcept {
  return rightPressed;
}

CENTURION_DEF bool MouseState::was_left_button_released() const noexcept {
  return !leftPressed && prevLeftPressed;
}

CENTURION_DEF bool MouseState::was_right_button_released() const noexcept {
  return !rightPressed && prevRightPressed;
}

CENTURION_DEF bool MouseState::was_mouse_moved() const noexcept {
  return mouseX != oldX || mouseY != oldY;
}

CENTURION_DEF int MouseState::get_window_width() const noexcept {
  return windowWidth;
}

CENTURION_DEF int MouseState::get_window_height() const noexcept {
  return windowHeight;
}

CENTURION_DEF int MouseState::get_logical_width() const noexcept {
  return logicalWidth;
}

CENTURION_DEF int MouseState::get_logical_height() const noexcept {
  return logicalHeight;
}

}  // namespace centurion

#endif  // CENTURION_MOUSE_STATE_SOURCE