#ifndef CENTURION_AUDIO_DEVICE_EVENT_SOURCE
#define CENTURION_AUDIO_DEVICE_EVENT_SOURCE

#include "event.hpp"

namespace centurion {

CENTURION_DEF
audio_device_event::audio_device_event() noexcept : common_event{}
{}

CENTURION_DEF
audio_device_event::audio_device_event(
    const SDL_AudioDeviceEvent& event) noexcept
    : common_event{event}
{}

CENTURION_DEF
void audio_device_event::set_which(u32 which) noexcept
{
  m_event.which = which;
}

CENTURION_DEF
void audio_device_event::set_capture(bool capture) noexcept
{
  m_event.iscapture = capture;
}

CENTURION_DEF
auto audio_device_event::which() const noexcept -> u32
{
  return m_event.which;
}

CENTURION_DEF
auto audio_device_event::output() const noexcept -> bool
{
  return !capture();
}

CENTURION_DEF
auto audio_device_event::capture() const noexcept -> bool
{
  return m_event.iscapture;
}

}  // namespace centurion

#endif  // CENTURION_AUDIO_DEVICE_EVENT_SOURCE
