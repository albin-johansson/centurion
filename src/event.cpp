#ifndef CENTURION_EVENT_SOURCE
#define CENTURION_EVENT_SOURCE

#include "event.hpp"

#include <utility>

namespace centurion {

CENTURION_DEF
event::event() noexcept
{
  m_data.emplace<std::monostate>();
}

CENTURION_DEF
event::event(const SDL_Event& event) noexcept : m_event{event}
{
  update_data();
}

CENTURION_DEF
event::event(SDL_Event&& event) noexcept : m_event{event}
{
  update_data();
}

CENTURION_DEF
void event::update_data() noexcept
{
  const auto t = type();

  if (t == event_type::Quit) {
    m_data.emplace<quit_event>(m_event.quit);

  } else if (t == event_type::AudioDeviceAdded ||
             t == event_type::AudioDeviceRemoved) {
    m_data.emplace<audio_device_event>(m_event.adevice);

  } else if (t == event_type::ControllerAxisMotion) {
    m_data.emplace<controller_axis_event>(m_event.caxis);

  } else if (t == event_type::ControllerButtonDown ||
             t == event_type::ControllerButtonUp) {
    m_data.emplace<controller_button_event>(m_event.cbutton);

  } else if (t == event_type::ControllerDeviceAdded ||
             t == event_type::ControllerDeviceRemoved ||
             t == event_type::ControllerDeviceRemapped) {
    m_data.emplace<controller_device_event>(m_event.cdevice);

  } else if (t == event_type::DollarGesture || t == event_type::DollarRecord) {
    m_data.emplace<dollar_gesture_event>(m_event.dgesture);

  } else if (t == event_type::DropBegin || t == event_type::DropComplete ||
             t == event_type::DropFile || t == event_type::DropText) {
    m_data.emplace<drop_event>(m_event.drop);

  } else if (t == event_type::JoystickAxisMotion) {
    m_data.emplace<joy_axis_event>(m_event.jaxis);

  } else if (t == event_type::JoystickBallMotion) {
    m_data.emplace<joy_ball_event>(m_event.jball);

  } else if (t == event_type::JoystickButtonUp ||
             t == event_type::JoystickButtonDown) {
    m_data.emplace<joy_button_event>(m_event.jbutton);

  } else if (t == event_type::JoystickDeviceAdded ||
             t == event_type::JoystickDeviceRemoved) {
    m_data.emplace<joy_device_event>(m_event.jdevice);

  } else if (t == event_type::JoystickHatMotion) {
    m_data.emplace<joy_hat_event>(m_event.jhat);

  } else if (t == event_type::KeyDown || t == event_type::KeyUp) {
    m_data.emplace<keyboard_event>(m_event.key);

  } else if (t == event_type::MouseButtonUp || t == event_type::MouseButtonDown) {
    m_data.emplace<mouse_button_event>(m_event.button);

  } else if (t == event_type::MouseMotion) {
    m_data.emplace<mouse_motion_event>(m_event.motion);

  } else if (t == event_type::MouseWheel) {
    m_data.emplace<mouse_wheel_event>(m_event.wheel);

  } else if (t == event_type::MultiGesture) {
    m_data.emplace<multi_gesture_event>(m_event.mgesture);

  } else if (t == event_type::TextEditing) {
    m_data.emplace<text_editing_event>(m_event.edit);

  } else if (t == event_type::TextInput) {
    m_data.emplace<text_input_event>(m_event.text);

  } else if (t == event_type::TouchMotion || t == event_type::TouchDown ||
             t == event_type::TouchUp) {
    m_data.emplace<touch_finger_event>(m_event.tfinger);

  } else if (t == event_type::Window) {
    m_data.emplace<window_event>(m_event.window);
  }
}

CENTURION_DEF
void event::refresh() noexcept
{
  SDL_PumpEvents();
}

CENTURION_DEF
void event::push(event& event) noexcept
{
  SDL_Event& sdlEvent = event.m_event;
  SDL_PushEvent(&sdlEvent);
}

CENTURION_DEF
void event::flush() noexcept
{
  SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
}

CENTURION_DEF
void event::flush_all() noexcept
{
  SDL_PumpEvents();
  SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
}

CENTURION_DEF
auto event::poll() noexcept -> bool
{
  const bool result = SDL_PollEvent(&m_event);

  update_data();

  return result;
}

CENTURION_DEF
auto event::type() const noexcept -> event_type
{
  return static_cast<event_type>(m_event.type);
}

}  // namespace centurion

#endif  // CENTURION_EVENT_SOURCE