#ifndef CENTURION_AUDIO_DEVICE_EVENT_SOURCE
#define CENTURION_AUDIO_DEVICE_EVENT_SOURCE

#include "audio_device_event.h"

namespace centurion {
namespace event {

CENTURION_DEF
AudioDeviceEvent::AudioDeviceEvent() noexcept : BaseEvent{}
{}

CENTURION_DEF
AudioDeviceEvent::AudioDeviceEvent(const SDL_AudioDeviceEvent& event) noexcept
    : BaseEvent{event}
{}

CENTURION_DEF
AudioDeviceEvent::AudioDeviceEvent(SDL_AudioDeviceEvent&& event) noexcept
    : BaseEvent{std::move(event)}
{}

CENTURION_DEF
void AudioDeviceEvent::set_type(AudioDeviceEventID id) noexcept
{
  m_event.type = static_cast<uint32_t>(id);
}

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
AudioDeviceEventID AudioDeviceEvent::type() const noexcept
{
  return static_cast<AudioDeviceEventID>(m_event.type);
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
