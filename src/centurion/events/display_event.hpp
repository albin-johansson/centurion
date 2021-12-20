#ifndef CENTURION_EVENTS_DISPLAY_EVENT_HPP_
#define CENTURION_EVENTS_DISPLAY_EVENT_HPP_

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../common.hpp"
#include "../core/exception.hpp"
#include "event_base.hpp"

namespace cen {

#if SDL_VERSION_ATLEAST(2, 0, 14)

enum class DisplayEventID {
  None = SDL_DISPLAYEVENT_NONE,
  Orientation = SDL_DISPLAYEVENT_ORIENTATION,
  Connected = SDL_DISPLAYEVENT_CONNECTED,
  Disconnected = SDL_DISPLAYEVENT_DISCONNECTED,
};

class DisplayEvent final : public EventBase<SDL_DisplayEvent> {
 public:
  DisplayEvent() noexcept : EventBase{EventType::Display} {}

  explicit DisplayEvent(const SDL_DisplayEvent& event) noexcept : EventBase{event} {}

  void SetEventID(const DisplayEventID id) noexcept
  {
    mEvent.event = static_cast<Uint8>(ToUnderlying(id));
  }

  void SetIndex(const Uint32 index) noexcept { mEvent.display = index; }

  void SetData1(const Sint32 data) noexcept { mEvent.data1 = data; }

  [[nodiscard]] auto GetEventID() const noexcept -> DisplayEventID
  {
    return static_cast<DisplayEventID>(mEvent.event);
  }

  [[nodiscard]] auto GetIndex() const noexcept -> Uint32 { return mEvent.display; }

  [[nodiscard]] auto GetData1() const noexcept -> Sint32 { return mEvent.data1; }
};

template <>
inline auto AsSDLEvent(const EventBase<SDL_DisplayEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.display = event.get();
  return e;
}

[[nodiscard]] constexpr auto to_string(const DisplayEventID id) -> std::string_view
{
  switch (id) {
    case DisplayEventID::None:
      return "None";

    case DisplayEventID::Orientation:
      return "Orientation";

    case DisplayEventID::Connected:
      return "Connected";

    case DisplayEventID::Disconnected:
      return "Disconnected";

    default:
      throw Error{"Did not recognize display event ID!"};
  }
}

inline auto operator<<(std::ostream& stream, const DisplayEventID id) -> std::ostream&
{
  return stream << to_string(id);
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

}  // namespace cen

#endif  // CENTURION_EVENTS_DISPLAY_EVENT_HPP_
