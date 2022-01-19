#ifndef CENTURION_AUDIO_EVENTS_HPP_
#define CENTURION_AUDIO_EVENTS_HPP_

#include <SDL.h>

#include "common.hpp"
#include "event_base.hpp"

namespace cen {

/// \addtogroup event
/// \{

class audio_device_event final : public event_base<SDL_AudioDeviceEvent> {
 public:
  audio_device_event() : event_base{event_type::audio_device_added} {}

  explicit audio_device_event(const SDL_AudioDeviceEvent& event) noexcept : event_base{event}
  {}

  void set_which(const uint32 which) noexcept { mEvent.which = which; }

  void set_capture(const bool capture) noexcept { mEvent.iscapture = capture; }

  [[nodiscard]] auto which() const noexcept -> uint32 { return mEvent.which; }

  [[nodiscard]] auto is_capture() const noexcept -> bool { return mEvent.iscapture; }

  [[nodiscard]] auto is_output() const noexcept -> bool { return !is_capture(); }
};

template <>
inline auto as_sdl_event(const event_base<SDL_AudioDeviceEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.adevice = event.get();
  return e;
}

/// \} End of group event

}  // namespace cen

#endif  // CENTURION_AUDIO_EVENTS_HPP_
