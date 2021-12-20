#ifndef CENTURION_EVENTS_AUDIO_DEVICE_EVENT_HPP_
#define CENTURION_EVENTS_AUDIO_DEVICE_EVENT_HPP_

#include <SDL.h>

#include "../common.hpp"
#include "event_base.hpp"

namespace cen {

/// \addtogroup event
/// \{

class AudioDeviceEvent final : public EventBase<SDL_AudioDeviceEvent> {
 public:
  AudioDeviceEvent() noexcept : EventBase{EventType::AudioDeviceAdded} {}

  explicit AudioDeviceEvent(const SDL_AudioDeviceEvent& event) noexcept : EventBase{event} {}

  void SetWhich(const Uint32 which) noexcept { mEvent.which = which; }
  void SetCapture(const bool capture) noexcept { mEvent.iscapture = capture; }

  [[nodiscard]] auto GetWhich() const noexcept -> Uint32 { return mEvent.which; }
  [[nodiscard]] auto IsCapture() const noexcept -> bool { return mEvent.iscapture; }
  [[nodiscard]] auto IsOutput() const noexcept -> bool { return !IsCapture(); }
};

/// \name SDL event conversions
/// \{

template <>
inline auto AsSDLEvent(const EventBase<SDL_AudioDeviceEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.adevice = event.get();
  return e;
}

/// \} End of SDL event conversions

/// \} End of group event

}  // namespace cen

#endif  // CENTURION_EVENTS_AUDIO_DEVICE_EVENT_HPP_
