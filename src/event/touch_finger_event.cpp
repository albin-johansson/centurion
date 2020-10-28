#include <algorithm>

#include "detail/utils.hpp"
#include "event.hpp"

namespace cen {

touch_finger_event::touch_finger_event() noexcept : common_event{}
{}

touch_finger_event::touch_finger_event(
    const SDL_TouchFingerEvent& event) noexcept
    : common_event{event}
{}

void touch_finger_event::set_touch_id(SDL_TouchID id) noexcept
{
  m_event.touchId = id;
}

void touch_finger_event::set_finger_id(SDL_FingerID id) noexcept
{
  m_event.fingerId = id;
}

void touch_finger_event::set_window_id(u32 id) noexcept
{
  m_event.windowID = id;
}

void touch_finger_event::set_x(float x) noexcept
{
  m_event.x = std::clamp(x, 0.0f, 1.0f);
}

void touch_finger_event::set_y(float y) noexcept
{
  m_event.y = std::clamp(y, 0.0f, 1.0f);
}

void touch_finger_event::set_dx(float dx) noexcept
{
  m_event.dx = std::clamp(dx, -1.0f, 1.0f);
}

void touch_finger_event::set_dy(float dy) noexcept
{
  m_event.dy = std::clamp(dy, -1.0f, 1.0f);
}

void touch_finger_event::set_pressure(float pressure) noexcept
{
  m_event.pressure = std::clamp(pressure, 0.0f, 1.0f);
}

auto touch_finger_event::touch_id() const noexcept -> SDL_TouchID
{
  return m_event.touchId;
}

auto touch_finger_event::finger_id() const noexcept -> SDL_FingerID
{
  return m_event.fingerId;
}

auto touch_finger_event::window_id() const noexcept -> u32
{
  return m_event.windowID;
}

auto touch_finger_event::x() const noexcept -> float
{
  return m_event.x;
}

auto touch_finger_event::y() const noexcept -> float
{
  return m_event.y;
}

auto touch_finger_event::dx() const noexcept -> float
{
  return m_event.dx;
}

auto touch_finger_event::dy() const noexcept -> float
{
  return m_event.dy;
}

auto touch_finger_event::pressure() const noexcept -> float
{
  return m_event.pressure;
}

}  // namespace cen
