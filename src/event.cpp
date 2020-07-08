#ifndef CENTURION_EVENT_SOURCE
#define CENTURION_EVENT_SOURCE

#include "event.hpp"

#include <utility>

namespace centurion::event {

CENTURION_DEF
Event::Event() noexcept
{
  m_data.emplace<std::monostate>();
}

CENTURION_DEF
Event::Event(const SDL_Event& event) noexcept : m_event{event}
{
  update_data();
}

CENTURION_DEF
Event::Event(SDL_Event&& event) noexcept : m_event{std::move(event)}
{
  update_data();
}

CENTURION_DEF
void Event::update_data() noexcept
{
  const auto t = type();

  if (t == EventType::Quit) {
    m_data.emplace<QuitEvent>(m_event.quit);

  } else if (t == EventType::AudioDeviceAdded ||
             t == EventType::AudioDeviceRemoved) {
    m_data.emplace<AudioDeviceEvent>(m_event.adevice);

  } else if (t == EventType::ControllerAxisMotion) {
    m_data.emplace<ControllerAxisEvent>(m_event.caxis);

  } else if (t == EventType::ControllerButtonDown ||
             t == EventType::ControllerButtonUp) {
    m_data.emplace<ControllerButtonEvent>(m_event.cbutton);

  } else if (t == EventType::ControllerDeviceAdded ||
             t == EventType::ControllerDeviceRemoved ||
             t == EventType::ControllerDeviceRemapped) {
    m_data.emplace<ControllerDeviceEvent>(m_event.cdevice);

  } else if (t == EventType::DollarGesture || t == EventType::DollarRecord) {
    m_data.emplace<DollarGestureEvent>(m_event.dgesture);

  } else if (t == EventType::DropBegin || t == EventType::DropComplete ||
             t == EventType::DropFile || t == EventType::DropText) {
    m_data.emplace<DropEvent>(m_event.drop);

  } else if (t == EventType::JoystickAxisMotion) {
    m_data.emplace<JoyAxisEvent>(m_event.jaxis);

  } else if (t == EventType::JoystickBallMotion) {
    m_data.emplace<JoyBallEvent>(m_event.jball);

  } else if (t == EventType::JoystickButtonUp ||
             t == EventType::JoystickButtonDown) {
    m_data.emplace<JoyButtonEvent>(m_event.jbutton);

  } else if (t == EventType::JoystickDeviceAdded ||
             t == EventType::JoystickDeviceRemoved) {
    m_data.emplace<JoyDeviceEvent>(m_event.jdevice);

  } else if (t == EventType::JoystickHatMotion) {
    m_data.emplace<JoyHatEvent>(m_event.jhat);

  } else if (t == EventType::KeyDown || t == EventType::KeyUp) {
    m_data.emplace<KeyboardEvent>(m_event.key);

  } else if (t == EventType::MouseButtonUp || t == EventType::MouseButtonDown) {
    m_data.emplace<MouseButtonEvent>(m_event.button);

  } else if (t == EventType::MouseMotion) {
    m_data.emplace<MouseMotionEvent>(m_event.motion);

  } else if (t == EventType::MouseWheel) {
    m_data.emplace<MouseWheelEvent>(m_event.wheel);

  } else if (t == EventType::MultiGesture) {
    m_data.emplace<MultiGestureEvent>(m_event.mgesture);

  } else if (t == EventType::TextEditing) {
    m_data.emplace<TextEditingEvent>(m_event.edit);

  } else if (t == EventType::TextInput) {
    m_data.emplace<TextInputEvent>(m_event.text);

  } else if (t == EventType::TouchMotion || t == EventType::TouchDown ||
             t == EventType::TouchUp) {
    m_data.emplace<TouchFingerEvent>(m_event.tfinger);

  } else if (t == EventType::Window) {
    m_data.emplace<WindowEvent>(m_event.window);
  }
}

CENTURION_DEF
void Event::refresh() noexcept
{
  SDL_PumpEvents();
}

CENTURION_DEF
void Event::push(Event& event) noexcept
{
  SDL_Event& sdlEvent = event.m_event;
  SDL_PushEvent(&sdlEvent);
}

CENTURION_DEF
void Event::flush() noexcept
{
  SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
}

CENTURION_DEF
void Event::flush_all() noexcept
{
  SDL_PumpEvents();
  SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
}

CENTURION_DEF
auto Event::poll() noexcept -> bool
{
  const bool result = SDL_PollEvent(&m_event);

  update_data();

  return result;
}

CENTURION_DEF
auto Event::type() const noexcept -> EventType
{
  return static_cast<EventType>(m_event.type);
}

}  // namespace centurion::event

#endif  // CENTURION_EVENT_SOURCE