#ifndef CENTURION_EVENTS_WINDOW_EVENT_HPP_
#define CENTURION_EVENTS_WINDOW_EVENT_HPP_

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../core/exception.hpp"
#include "event_base.hpp"

namespace cen {

enum class WindowEventID {
  None = SDL_WINDOWEVENT_NONE,
  Shown = SDL_WINDOWEVENT_SHOWN,
  Hidden = SDL_WINDOWEVENT_HIDDEN,
  Exposed = SDL_WINDOWEVENT_EXPOSED,
  Moved = SDL_WINDOWEVENT_MOVED,
  Resized = SDL_WINDOWEVENT_RESIZED,
  SizeChanged = SDL_WINDOWEVENT_SIZE_CHANGED,
  Minimized = SDL_WINDOWEVENT_MINIMIZED,
  Maximized = SDL_WINDOWEVENT_MAXIMIZED,
  Restored = SDL_WINDOWEVENT_RESTORED,
  Enter = SDL_WINDOWEVENT_ENTER,
  Leave = SDL_WINDOWEVENT_LEAVE,
  FocusGained = SDL_WINDOWEVENT_FOCUS_GAINED,
  FocusLost = SDL_WINDOWEVENT_FOCUS_LOST,
  Close = SDL_WINDOWEVENT_CLOSE,
  TakeFocus = SDL_WINDOWEVENT_TAKE_FOCUS,
  HitTest = SDL_WINDOWEVENT_HIT_TEST
};

class WindowEvent final : public EventBase<SDL_WindowEvent> {
 public:
  WindowEvent() noexcept : EventBase{EventType::Window} {}

  explicit WindowEvent(const SDL_WindowEvent& event) noexcept : EventBase{event} {}

  void SetEventID(const WindowEventID id) noexcept { mEvent.event = static_cast<Uint8>(id); }

  void SetData1(const Sint32 value) noexcept { mEvent.data1 = value; }
  void SetData2(const Sint32 value) noexcept { mEvent.data2 = value; }

  [[nodiscard]] auto GetEventID() const noexcept -> WindowEventID
  {
    return static_cast<WindowEventID>(mEvent.event);
  }

  [[nodiscard]] auto GetData1() const noexcept -> Sint32 { return mEvent.data1; }
  [[nodiscard]] auto GetData2() const noexcept -> Sint32 { return mEvent.data2; }
};

template <>
inline auto AsSDLEvent(const EventBase<SDL_WindowEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.window = event.get();
  return e;
}

[[nodiscard]] constexpr auto to_string(const WindowEventID id) -> std::string_view
{
  switch (id) {
    case WindowEventID::None:
      return "None";

    case WindowEventID::Shown:
      return "Shown";

    case WindowEventID::Hidden:
      return "Hidden";

    case WindowEventID::Exposed:
      return "Exposed";

    case WindowEventID::Moved:
      return "Moved";

    case WindowEventID::Resized:
      return "Resized";

    case WindowEventID::SizeChanged:
      return "SizeChanged";

    case WindowEventID::Minimized:
      return "Minimized";

    case WindowEventID::Maximized:
      return "Maximized";

    case WindowEventID::Restored:
      return "Restored";

    case WindowEventID::Enter:
      return "Enter";

    case WindowEventID::Leave:
      return "Leave";

    case WindowEventID::FocusGained:
      return "FocusGained";

    case WindowEventID::FocusLost:
      return "FocusLost";

    case WindowEventID::Close:
      return "Close";

    case WindowEventID::TakeFocus:
      return "TakeFocus";

    case WindowEventID::HitTest:
      return "HitTest";

    default:
      throw Error{"Did not recognize window event ID!"};
  }
}

inline auto operator<<(std::ostream& stream, const WindowEventID id) -> std::ostream&
{
  return stream << to_string(id);
}

}  // namespace cen

#endif  // CENTURION_EVENTS_WINDOW_EVENT_HPP_
