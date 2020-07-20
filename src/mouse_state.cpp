#include "mouse_state.hpp"

#include "centurion_utils.hpp"

namespace centurion::input {

mouse_state::mouse_state() noexcept = default;

auto mouse_state::unique() -> std::unique_ptr<mouse_state>
{
  return std::make_unique<mouse_state>();
}

auto mouse_state::shared() -> std::shared_ptr<mouse_state>
{
  return std::make_shared<mouse_state>();
}

void mouse_state::update(int windowWidth, int windowHeight) noexcept
{
  windowWidth = (windowWidth < 1) ? 1 : windowWidth;
  windowHeight = (windowHeight < 1) ? 1 : windowHeight;

  m_oldX = m_mouseX;
  m_oldY = m_mouseY;
  m_prevLeftPressed = m_leftPressed;
  m_prevRightPressed = m_rightPressed;

  {
    const u32 mask = SDL_GetMouseState(&m_mouseX, &m_mouseY);
    m_leftPressed = mask & SDL_BUTTON(SDL_BUTTON_LEFT);
    m_rightPressed = mask & SDL_BUTTON(SDL_BUTTON_RIGHT);
  }

  {
    const auto xRatio =
        static_cast<float>(m_mouseX) / static_cast<float>(windowWidth);
    const auto adjustedX = xRatio * static_cast<float>(m_logicalWidth);

    const auto yRatio =
        static_cast<float>(m_mouseY) / static_cast<float>(windowHeight);
    const auto adjustedY = yRatio * static_cast<float>(m_logicalHeight);

    m_mouseX = static_cast<int>(adjustedX);
    m_mouseY = static_cast<int>(adjustedY);
  }
}

void mouse_state::reset() noexcept
{
  m_logicalWidth = 1;
  m_logicalHeight = 1;
}

void mouse_state::set_logical_width(int logicalWidth) noexcept
{
  if (logicalWidth <= 0) {
    logicalWidth = 1;
  }
  this->m_logicalWidth = logicalWidth;
}

void mouse_state::set_logical_height(int logicalHeight) noexcept
{
  if (logicalHeight <= 0) {
    logicalHeight = 1;
  }
  this->m_logicalHeight = logicalHeight;
}

auto mouse_state::was_left_button_released() const noexcept -> bool
{
  return !m_leftPressed && m_prevLeftPressed;
}

auto mouse_state::was_right_button_released() const noexcept -> bool
{
  return !m_rightPressed && m_prevRightPressed;
}

auto mouse_state::was_mouse_moved() const noexcept -> bool
{
  return (m_mouseX != m_oldX) || (m_mouseY != m_oldY);
}

}  // namespace centurion::input
