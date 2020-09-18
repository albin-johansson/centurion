#include "event.hpp"

namespace cen {

audio_device_event::audio_device_event() noexcept : common_event{}
{}

audio_device_event::audio_device_event(
    const SDL_AudioDeviceEvent& event) noexcept
    : common_event{event}
{}

void audio_device_event::set_which(u32 which) noexcept
{
  m_event.which = which;
}

void audio_device_event::set_capture(bool capture) noexcept
{
  m_event.iscapture = capture;
}

auto audio_device_event::which() const noexcept -> u32
{
  return m_event.which;
}

auto audio_device_event::output() const noexcept -> bool
{
  return !capture();
}

auto audio_device_event::capture() const noexcept -> bool
{
  return m_event.iscapture;
}

}  // namespace cen
