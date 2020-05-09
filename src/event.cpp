#ifndef CENTURION_EVENT_SOURCE
#define CENTURION_EVENT_SOURCE

#include "event.h"

namespace centurion {
namespace event {

CENTURION_DEF
Event::Event() noexcept
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
    return tl::nullopt;
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
    return tl::nullopt;
  }
}

CENTURION_DEF
Optional<ControllerAxisEvent> Event::as_controller_axis_event() const noexcept
{
  if (type() == EventType::ControllerAxisMotion) {
    return ControllerAxisEvent{m_event.caxis};
  } else {
    return tl::nullopt;
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
    return tl::nullopt;
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
    return tl::nullopt;
  }
}

CENTURION_DEF
Optional<DollarGestureEvent> Event::as_dollar_gesture_event() const noexcept
{
  return centurion::Optional<DollarGestureEvent>();
}

CENTURION_DEF
Optional<DropEvent> Event::as_drop_event() const noexcept
{
  return centurion::Optional<DropEvent>();
}

CENTURION_DEF
Optional<JoyAxisEvent> Event::as_joy_axis_event() const noexcept
{
  return centurion::Optional<JoyAxisEvent>();
}

CENTURION_DEF
Optional<JoyBallEvent> Event::as_joy_ball_event() const noexcept
{
  return centurion::Optional<JoyBallEvent>();
}

CENTURION_DEF
Optional<JoyButtonEvent> Event::as_joy_button_event() const noexcept
{
  return centurion::Optional<JoyButtonEvent>();
}

CENTURION_DEF
Optional<JoyDeviceEvent> Event::as_joy_device_event() const noexcept
{
  return centurion::Optional<JoyDeviceEvent>();
}

CENTURION_DEF
Optional<JoyHatEvent> Event::as_joy_hat_event() const noexcept
{
  return centurion::Optional<JoyHatEvent>();
}

CENTURION_DEF
Optional<KeyboardEvent> Event::as_keyboard_event() const noexcept
{
  return centurion::Optional<KeyboardEvent>();
}

CENTURION_DEF
Optional<MouseButtonEvent> Event::as_mouse_button_event() const noexcept
{
  return centurion::Optional<MouseButtonEvent>();
}

CENTURION_DEF
Optional<MouseMotionEvent> Event::as_mouse_motion_event() const noexcept
{
  return centurion::Optional<MouseMotionEvent>();
}

CENTURION_DEF
Optional<MouseWheelEvent> Event::as_mouse_wheel_event() const noexcept
{
  return centurion::Optional<MouseWheelEvent>();
}

CENTURION_DEF
Optional<MultiGestureEvent> Event::as_multi_gesture_event() const noexcept
{
  return centurion::Optional<MultiGestureEvent>();
}

CENTURION_DEF
Optional<TextEditingEvent> Event::as_text_editing_event() const noexcept
{
  return centurion::Optional<TextEditingEvent>();
}

CENTURION_DEF
Optional<TextInputEvent> Event::as_text_input_event() const noexcept
{
  return centurion::Optional<TextInputEvent>();
}

CENTURION_DEF
Optional<TouchFingerEvent> Event::as_touch_finger_event() const noexcept
{
  return centurion::Optional<TouchFingerEvent>();
}

CENTURION_DEF
Optional<WindowEvent> Event::as_window_event() const noexcept
{
  return centurion::Optional<WindowEvent>();
}

}  // namespace event
}  // namespace centurion

#endif  // CENTURION_EVENT_SOURCE