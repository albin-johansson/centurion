#ifndef CENTURION_MOUSE_STATE_SOURCE
#define CENTURION_MOUSE_STATE_SOURCE

#include "mouse_state.h"

#include <SDL.h>

#include "centurion_utils.h"
#include "window.h"

namespace centurion {
namespace input {

CENTURION_DEF
MouseState::MouseState() noexcept = default;

CENTURION_DEF
MouseState::~MouseState() noexcept = default;

CENTURION_DEF
std::unique_ptr<MouseState> MouseState::unique()
{
  return centurion::detail::make_unique<MouseState>();
}

CENTURION_DEF
std::shared_ptr<MouseState> MouseState::shared()
{
  return std::make_shared<MouseState>();
}

CENTURION_DEF
void MouseState::window_updated(const  Window& window) noexcept
{
  m_windowWidth = window.width();
  m_windowHeight = window.height();
}

CENTURION_DEF
void MouseState::update() noexcept
{
  m_oldX = m_mouseX;
  m_oldY = m_mouseY;
  m_prevLeftPressed = m_leftPressed;
  m_prevRightPressed = m_rightPressed;

  {
    const Uint32 mask = SDL_GetMouseState(&m_mouseX, &m_mouseY);
    m_leftPressed = mask & SDL_BUTTON(SDL_BUTTON_LEFT);
    m_rightPressed = mask & SDL_BUTTON(SDL_BUTTON_RIGHT);
  }

  {
    const auto xRatio =
        static_cast<float>(m_mouseX) / static_cast<float>(m_windowWidth);
    const auto adjustedX = xRatio * static_cast<float>(m_logicalWidth);

    const auto yRatio =
        static_cast<float>(m_mouseY) / static_cast<float>(m_windowHeight);
    const auto adjustedY = yRatio * static_cast<float>(m_logicalHeight);

    m_mouseX = static_cast<int>(adjustedX);
    m_mouseY = static_cast<int>(adjustedY);
  }
}

CENTURION_DEF
void MouseState::reset() noexcept
{
  m_logicalWidth = 1;
  m_logicalHeight = 1;
  m_windowWidth = 1;
  m_windowHeight = 1;
}

CENTURION_DEF
void MouseState::set_logical_width(int logicalWidth) noexcept
{
  if (logicalWidth <= 0) {
    logicalWidth = 1;
  }
  this->m_logicalWidth = logicalWidth;
}

CENTURION_DEF
void MouseState::set_logical_height(int logicalHeight) noexcept
{
  if (logicalHeight <= 0) {
    logicalHeight = 1;
  }
  this->m_logicalHeight = logicalHeight;
}

CENTURION_DEF
void MouseState::set_window_width(int windowWidth) noexcept
{
  if (windowWidth <= 0) {
    windowWidth = 1;
  }
  this->m_windowWidth = windowWidth;
}

CENTURION_DEF
void MouseState::set_window_height(int windowHeight) noexcept
{
  if (windowHeight <= 0) {
    windowHeight = 1;
  }
  this->m_windowHeight = windowHeight;
}

CENTURION_DEF
int MouseState::mouse_x() const noexcept
{
  return m_mouseX;
}

CENTURION_DEF
int MouseState::mouse_y() const noexcept
{
  return m_mouseY;
}

CENTURION_DEF
bool MouseState::is_left_button_pressed() const noexcept
{
  return m_leftPressed;
}

CENTURION_DEF
bool MouseState::is_right_button_pressed() const noexcept
{
  return m_rightPressed;
}

CENTURION_DEF
bool MouseState::was_left_button_released() const noexcept
{
  return !m_leftPressed && m_prevLeftPressed;
}

CENTURION_DEF
bool MouseState::was_right_button_released() const noexcept
{
  return !m_rightPressed && m_prevRightPressed;
}

CENTURION_DEF
bool MouseState::was_mouse_moved() const noexcept
{
  return m_mouseX != m_oldX || m_mouseY != m_oldY;
}

CENTURION_DEF
int MouseState::window_width() const noexcept
{
  return m_windowWidth;
}

CENTURION_DEF
int MouseState::window_height() const noexcept
{
  return m_windowHeight;
}

CENTURION_DEF
int MouseState::logical_width() const noexcept
{
  return m_logicalWidth;
}

CENTURION_DEF
int MouseState::logical_height() const noexcept
{
  return m_logicalHeight;
}

}  // namespace input
}  // namespace centurion

#endif  // CENTURION_MOUSE_STATE_SOURCE