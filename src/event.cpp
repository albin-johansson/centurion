#ifndef CENTURION_EVENT_SOURCE
#define CENTURION_EVENT_SOURCE

#include "event.hpp"

namespace centurion {

CENTURION_DEF
event::event() noexcept = default;

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

  if (t == event_type::quit) {
    m_data.emplace<quit_event>(m_event.quit);

  } else if (t == event_type::audio_device_added ||
             t == event_type::audio_device_removed) {
    m_data.emplace<audio_device_event>(m_event.adevice);

  } else if (t == event_type::controller_axis_motion) {
    m_data.emplace<controller_axis_event>(m_event.caxis);

  } else if (t == event_type::controller_button_down ||
             t == event_type::controller_button_up) {
    m_data.emplace<controller_button_event>(m_event.cbutton);

  } else if (t == event_type::controller_device_added ||
             t == event_type::controller_device_removed ||
             t == event_type::controller_device_remapped) {
    m_data.emplace<controller_device_event>(m_event.cdevice);

  } else if (t == event_type::dollar_gesture ||
             t == event_type::dollar_record) {
    m_data.emplace<dollar_gesture_event>(m_event.dgesture);

  } else if (t == event_type::drop_begin || t == event_type::drop_complete ||
             t == event_type::drop_file || t == event_type::drop_text) {
    m_data.emplace<drop_event>(m_event.drop);

  } else if (t == event_type::joystick_axis_motion) {
    m_data.emplace<joy_axis_event>(m_event.jaxis);

  } else if (t == event_type::joystick_ball_motion) {
    m_data.emplace<joy_ball_event>(m_event.jball);

  } else if (t == event_type::joystick_button_up ||
             t == event_type::joystick_button_down) {
    m_data.emplace<joy_button_event>(m_event.jbutton);

  } else if (t == event_type::joystick_device_added ||
             t == event_type::joystick_device_removed) {
    m_data.emplace<joy_device_event>(m_event.jdevice);

  } else if (t == event_type::joystick_hat_motion) {
    m_data.emplace<joy_hat_event>(m_event.jhat);

  } else if (t == event_type::key_down || t == event_type::key_up) {
    m_data.emplace<keyboard_event>(m_event.key);

  } else if (t == event_type::mouse_button_up ||
             t == event_type::mouse_button_down) {
    m_data.emplace<mouse_button_event>(m_event.button);

  } else if (t == event_type::mouse_motion) {
    m_data.emplace<mouse_motion_event>(m_event.motion);

  } else if (t == event_type::mouse_wheel) {
    m_data.emplace<mouse_wheel_event>(m_event.wheel);

  } else if (t == event_type::multi_gesture) {
    m_data.emplace<multi_gesture_event>(m_event.mgesture);

  } else if (t == event_type::text_editing) {
    m_data.emplace<text_editing_event>(m_event.edit);

  } else if (t == event_type::text_input) {
    m_data.emplace<text_input_event>(m_event.text);

  } else if (t == event_type::touch_motion || t == event_type::touch_down ||
             t == event_type::touch_up) {
    m_data.emplace<touch_finger_event>(m_event.tfinger);

  } else if (t == event_type::window) {
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