#ifndef CENTURION_EVENT_SOURCE
#define CENTURION_EVENT_SOURCE

#include "event.hpp"

#include <utility>

namespace centurion::event {

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
  SDL_Event& sdlEvent = event.get();
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
  return SDL_PollEvent(&m_event);
}

CENTURION_DEF
auto Event::type() const noexcept -> EventType
{
  return static_cast<EventType>(m_event.type);
}

CENTURION_DEF
auto Event::as_quit_event() const noexcept -> Optional<QuitEvent>
{
  if (type() == EventType::Quit) {
    return QuitEvent{m_event.quit};
  } else {
    return nothing;
  }
}

CENTURION_DEF
auto Event::as_audio_device_event() const noexcept -> Optional<AudioDeviceEvent>
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
auto Event::as_controller_axis_event() const noexcept
    -> Optional<ControllerAxisEvent>
{
  if (type() == EventType::ControllerAxisMotion) {
    return ControllerAxisEvent{m_event.caxis};
  } else {
    return nothing;
  }
}

CENTURION_DEF
auto Event::as_controller_button_event() const noexcept
    -> Optional<ControllerButtonEvent>
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
auto Event::as_controller_device_event() const noexcept
    -> Optional<ControllerDeviceEvent>
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
auto Event::as_dollar_gesture_event() const noexcept
    -> Optional<DollarGestureEvent>
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
auto Event::as_drop_event() const noexcept -> Optional<DropEvent>
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
auto Event::as_joy_axis_event() const noexcept -> Optional<JoyAxisEvent>
{
  if (type() == EventType::JoystickAxisMotion) {
    return JoyAxisEvent{m_event.jaxis};
  } else {
    return nothing;
  }
}

CENTURION_DEF
auto Event::as_joy_ball_event() const noexcept -> Optional<JoyBallEvent>
{
  if (type() == EventType::JoystickBallMotion) {
    return JoyBallEvent{m_event.jball};
  } else {
    return nothing;
  }
}

CENTURION_DEF
auto Event::as_joy_button_event() const noexcept -> Optional<JoyButtonEvent>
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
auto Event::as_joy_device_event() const noexcept -> Optional<JoyDeviceEvent>
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
auto Event::as_joy_hat_event() const noexcept -> Optional<JoyHatEvent>
{
  if (type() == EventType::JoystickHatMotion) {
    return JoyHatEvent{m_event.jhat};
  } else {
    return nothing;
  }
}

CENTURION_DEF
auto Event::as_keyboard_event() const noexcept -> Optional<KeyboardEvent>
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
auto Event::as_mouse_button_event() const noexcept -> Optional<MouseButtonEvent>
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
auto Event::as_mouse_motion_event() const noexcept -> Optional<MouseMotionEvent>
{
  if (type() == EventType::MouseMotion) {
    return MouseMotionEvent{m_event.motion};
  } else {
    return nothing;
  }
}

CENTURION_DEF
auto Event::as_mouse_wheel_event() const noexcept -> Optional<MouseWheelEvent>
{
  if (type() == EventType::MouseWheel) {
    return MouseWheelEvent{m_event.wheel};
  } else {
    return nothing;
  }
}

CENTURION_DEF
auto Event::as_multi_gesture_event() const noexcept
    -> Optional<MultiGestureEvent>
{
  if (type() == EventType::MultiGesture) {
    return MultiGestureEvent{m_event.mgesture};
  } else {
    return nothing;
  }
}

CENTURION_DEF
auto Event::as_text_editing_event() const noexcept -> Optional<TextEditingEvent>
{
  if (type() == EventType::TextEditing) {
    return TextEditingEvent{m_event.edit};
  } else {
    return nothing;
  }
}

CENTURION_DEF
auto Event::as_text_input_event() const noexcept -> Optional<TextInputEvent>
{
  if (type() == EventType::TextInput) {
    return TextInputEvent{m_event.text};
  } else {
    return nothing;
  }
}

CENTURION_DEF
auto Event::as_touch_finger_event() const noexcept -> Optional<TouchFingerEvent>
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
auto Event::as_window_event() const noexcept -> Optional<WindowEvent>
{
  if (type() == EventType::Window) {
    return WindowEvent{m_event.window};
  } else {
    return nothing;
  }
}

}  // namespace centurion::event

#endif  // CENTURION_EVENT_SOURCE