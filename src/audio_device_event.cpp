#ifndef CENTURION_AUDIO_DEVICE_EVENT_SOURCE
#define CENTURION_AUDIO_DEVICE_EVENT_SOURCE

#include "event.hpp"

namespace centurion {

CENTURION_DEF
AudioDeviceEvent::AudioDeviceEvent() noexcept : CommonEvent{}
{}

CENTURION_DEF
AudioDeviceEvent::AudioDeviceEvent(const SDL_AudioDeviceEvent& event) noexcept
    : CommonEvent{event}
{}

CENTURION_DEF
void AudioDeviceEvent::set_which(u32 which) noexcept
{
  m_event.which = which;
}

CENTURION_DEF
void AudioDeviceEvent::set_capture(bool capture) noexcept
{
  m_event.iscapture = capture;
}

CENTURION_DEF
auto AudioDeviceEvent::which() const noexcept -> u32
{
  return m_event.which;
}

CENTURION_DEF
auto AudioDeviceEvent::output() const noexcept -> bool
{
  return !capture();
}

CENTURION_DEF
auto AudioDeviceEvent::capture() const noexcept -> bool
{
  return m_event.iscapture;
}

}  // namespace centurion

#endif  // CENTURION_AUDIO_DEVICE_EVENT_SOURCE
