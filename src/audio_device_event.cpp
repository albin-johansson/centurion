#ifndef CENTURION_AUDIO_DEVICE_EVENT_SOURCE
#define CENTURION_AUDIO_DEVICE_EVENT_SOURCE

#include "audio_device_event.h"

namespace centurion {
namespace event {

CENTURION_DEF
AudioDeviceEvent::AudioDeviceEvent() noexcept : CommonEvent{}
{}

CENTURION_DEF
AudioDeviceEvent::AudioDeviceEvent(const SDL_AudioDeviceEvent& event) noexcept
    : CommonEvent{event}
{}

CENTURION_DEF
AudioDeviceEvent::AudioDeviceEvent(SDL_AudioDeviceEvent&& event) noexcept
    : CommonEvent{std::move(event)}
{}

CENTURION_DEF
void AudioDeviceEvent::set_which(uint32_t which) noexcept
{
  m_event.which = which;
}

CENTURION_DEF
void AudioDeviceEvent::set_capture(bool capture) noexcept
{
  m_event.iscapture = capture;
}

CENTURION_DEF
uint32_t AudioDeviceEvent::which() const noexcept
{
  return m_event.which;
}

CENTURION_DEF
bool AudioDeviceEvent::output() const noexcept
{
  return !capture();
}

CENTURION_DEF
bool AudioDeviceEvent::capture() const noexcept
{
  return m_event.iscapture;
}

}  // namespace event
}  // namespace centurion

#endif  // CENTURION_AUDIO_DEVICE_EVENT_SOURCE
