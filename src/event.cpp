#ifndef CENTURION_EVENT_SOURCE
#define CENTURION_EVENT_SOURCE

#include "event.hpp"

#include <utility>

namespace centurion {
namespace event {

CENTURION_DEF
Event::Event() noexcept
{}

CENTURION_DEF
Event::Event(const SDL_Event& event) noexcept : m_event{event}
{}

CENTURION_DEF
Event::Event(SDL_Event&& event) noexcept : m_event{std::move(event)}
{}

CENTURION_DEF
void Event::refresh() noexcept
{
  SDL_PumpEvents();
}

CENTURION_DEF
void Event::push(Event& event) noexcept
{
  SDL_Event& sdlEvent = event;
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
bool Event::poll() noexcept
{
  return SDL_PollEvent(&m_event);
}

CENTURION_DEF
EventType Event::type() const noexcept
{
  return static_cast<EventType>(m_event.type);
}

CENTURION_DEF
Optional<QuitEvent> Event::as_quit_event() const noexcept
{
  if (type() == EventType::Quit) {
    return QuitEvent{m_event.quit};
  } else {
    return nothing;
  }
}

CENTURION_DEF
Optional<AudioDeviceEvent> Event::as_audio_device_event() const noexcept
{
  const auto isAudioEvent = type() == EventType::AudioDeviceAdded ||
                            type() == EventType::AudioDeviceRemoved;
  if (isAudioEvent) {
    return AudioDeviceEvent{m_event.adevice};
  } else {
    return nothing;
  }
}

CENTURION_DEF
Optional<ControllerAxisEvent> Event::as_controller_axis_event() const noexcept
{
  if (type() == EventType::ControllerAxisMotion) {
    return ControllerAxisEvent{m_event.caxis};
  } else {
    return nothing;
  }
}

CENTURION_DEF
Optional<ControllerButtonEvent> Event::as_controller_button_event()
    const noexcept
{
  const auto isContButtonEvent = type() == EventType::ControllerButtonDown ||
                                 type() == EventType::ControllerButtonUp;
  if (isContButtonEvent) {
    return ControllerButtonEvent{m_event.cbutton};
  } else {
    return nothing;
  }
}

CENTURION_DEF
Optional<ControllerDeviceEvent> Event::as_controller_device_event()
    const noexcept
{
  const auto isContDeviceEvent = type() == EventType::ControllerDeviceAdded ||
                                 type() == EventType::ControllerDeviceRemoved ||
                                 type() == EventType::ControllerDeviceRemapped;
  if (isContDeviceEvent) {
    return ControllerDeviceEvent{m_event.cdevice};
  } else {
    return nothing;
  }
}

CENTURION_DEF
Optional<DollarGestureEvent> Event::as_dollar_gesture_event() const noexcept
{
  const auto isDollarGestureEvent =
      type() == EventType::DollarGesture || type() == EventType::DollarRecord;
  if (isDollarGestureEvent) {
    return DollarGestureEvent{m_event.dgesture};
  } else {
    return nothing;
  }
}

CENTURION_DEF
Optional<DropEvent> Event::as_drop_event() const noexcept
{
  const auto isDropEvent =
      type() == EventType::DropBegin || type() == EventType::DropComplete ||
      type() == EventType::DropFile || type() == EventType::DropText;
  if (isDropEvent) {
    return DropEvent{m_event.drop};
  } else {
    return nothing;
  }
}

CENTURION_DEF
Optional<JoyAxisEvent> Event::as_joy_axis_event() const noexcept
{
  if (type() == EventType::JoystickAxisMotion) {
    return JoyAxisEvent{m_event.jaxis};
  } else {
    return nothing;
  }
}

CENTURION_DEF
Optional<JoyBallEvent> Event::as_joy_ball_event() const noexcept
{
  if (type() == EventType::JoystickBallMotion) {
    return JoyBallEvent{m_event.jball};
  } else {
    return nothing;
  }
}

CENTURION_DEF
Optional<JoyButtonEvent> Event::as_joy_button_event() const noexcept
{
  const auto isJoyButtonEvent = type() == EventType::JoystickButtonUp ||
                                type() == EventType::JoystickButtonDown;
  if (isJoyButtonEvent) {
    return JoyButtonEvent{m_event.jbutton};
  } else {
    return nothing;
  }
}

CENTURION_DEF
Optional<JoyDeviceEvent> Event::as_joy_device_event() const noexcept
{
  const auto isJoyDeviceEvent = type() == EventType::JoystickDeviceAdded ||
                                type() == EventType::JoystickDeviceRemoved;
  if (isJoyDeviceEvent) {
    return JoyDeviceEvent{m_event.jdevice};
  } else {
    return nothing;
  }
}

CENTURION_DEF
Optional<JoyHatEvent> Event::as_joy_hat_event() const noexcept
{
  if (type() == EventType::JoystickHatMotion) {
    return JoyHatEvent{m_event.jhat};
  } else {
    return nothing;
  }
}

CENTURION_DEF
Optional<KeyboardEvent> Event::as_keyboard_event() const noexcept
{
  const auto isKeyboardEvent =
      type() == EventType::KeyDown || type() == EventType::KeyUp;
  if (isKeyboardEvent) {
    return KeyboardEvent{m_event.key};
  } else {
    return nothing;
  }
}

CENTURION_DEF
Optional<MouseButtonEvent> Event::as_mouse_button_event() const noexcept
{
  const auto isMouseButtonEvent = type() == EventType::MouseButtonUp ||
                                  type() == EventType::MouseButtonDown;
  if (isMouseButtonEvent) {
    return MouseButtonEvent{m_event.button};
  } else {
    return nothing;
  }
}

CENTURION_DEF
Optional<MouseMotionEvent> Event::as_mouse_motion_event() const noexcept
{
  if (type() == EventType::MouseMotion) {
    return MouseMotionEvent{m_event.motion};
  } else {
    return nothing;
  }
}

CENTURION_DEF
Optional<MouseWheelEvent> Event::as_mouse_wheel_event() const noexcept
{
  if (type() == EventType::MouseWheel) {
    return MouseWheelEvent{m_event.wheel};
  } else {
    return nothing;
  }
}

CENTURION_DEF
Optional<MultiGestureEvent> Event::as_multi_gesture_event() const noexcept
{
  if (type() == EventType::MultiGesture) {
    return MultiGestureEvent{m_event.mgesture};
  } else {
    return nothing;
  }
}

CENTURION_DEF
Optional<TextEditingEvent> Event::as_text_editing_event() const noexcept
{
  if (type() == EventType::TextEditing) {
    return TextEditingEvent{m_event.edit};
  } else {
    return nothing;
  }
}

CENTURION_DEF
Optional<TextInputEvent> Event::as_text_input_event() const noexcept
{
  if (type() == EventType::TextInput) {
    return TextInputEvent{m_event.text};
  } else {
    return nothing;
  }
}

CENTURION_DEF
Optional<TouchFingerEvent> Event::as_touch_finger_event() const noexcept
{
  const auto isTouchFingerEvent = type() == EventType::TouchMotion ||
                                  type() == EventType::TouchDown ||
                                  type() == EventType::TouchUp;
  if (isTouchFingerEvent) {
    return TouchFingerEvent{m_event.tfinger};
  } else {
    return nothing;
  }
}

CENTURION_DEF
Optional<WindowEvent> Event::as_window_event() const noexcept
{
  if (type() == EventType::Window) {
    return WindowEvent{m_event.window};
  } else {
    return nothing;
  }
}

// CENTURION_DEF
// Optional<SysWMEvent> Event::as_syswm_event() const noexcept
//{
//  if (type() == EventType::System) {
//    return SysWMEvent{m_event.syswm};
//  } else {
//    return nothing;
//  }
//}

}  // namespace event
}  // namespace centurion

#endif  // CENTURION_EVENT_SOURCE