#ifndef CENTURION_EVENTS_AUDIO_DEVICE_EVENT_HPP_
#define CENTURION_EVENTS_AUDIO_DEVICE_EVENT_HPP_

#include <SDL.h>

#include "../common.hpp"
#include "common_event.hpp"

namespace cen {

/// \addtogroup event
/// \{

class audio_device_event final : public common_event<SDL_AudioDeviceEvent> {
 public:
  audio_device_event() noexcept : common_event{EventType::AudioDeviceAdded} {}

  explicit audio_device_event(const SDL_AudioDeviceEvent& event) noexcept : common_event{event}
  {}

  void set_which(const Uint32 which) noexcept { m_event.which = which; }
  void set_capture(const bool capture) noexcept { m_event.iscapture = capture; }

  [[nodiscard]] auto which() const noexcept -> Uint32 { return m_event.which; }
  [[nodiscard]] auto output() const noexcept -> bool { return !capture(); }
  [[nodiscard]] auto capture() const noexcept -> bool { return m_event.iscapture; }
};

/// \name SDL event conversions
/// \{

template <>
inline auto as_sdl_event(const common_event<SDL_AudioDeviceEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.adevice = event.get();
  return e;
}

/// \} End of SDL event conversions

/// \} End of group event

}  // namespace cen

#endif  // CENTURION_EVENTS_AUDIO_DEVICE_EVENT_HPP_
