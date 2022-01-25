#ifndef CENTURION_WINDOW_EVENTS_HPP_
#define CENTURION_WINDOW_EVENTS_HPP_

#include <SDL.h>

#include "common.hpp"
#include "event_base.hpp"

namespace cen {

/// \addtogroup event
/// \{

enum class window_event_id {
  none = SDL_WINDOWEVENT_NONE,
  shown = SDL_WINDOWEVENT_SHOWN,
  hidden = SDL_WINDOWEVENT_HIDDEN,
  exposed = SDL_WINDOWEVENT_EXPOSED,
  moved = SDL_WINDOWEVENT_MOVED,
  resized = SDL_WINDOWEVENT_RESIZED,
  size_changed = SDL_WINDOWEVENT_SIZE_CHANGED,
  minimized = SDL_WINDOWEVENT_MINIMIZED,
  maximized = SDL_WINDOWEVENT_MAXIMIZED,
  restored = SDL_WINDOWEVENT_RESTORED,
  enter = SDL_WINDOWEVENT_ENTER,
  leave = SDL_WINDOWEVENT_LEAVE,
  focus_gained = SDL_WINDOWEVENT_FOCUS_GAINED,
  focus_lost = SDL_WINDOWEVENT_FOCUS_LOST,
  close = SDL_WINDOWEVENT_CLOSE,
  take_focus = SDL_WINDOWEVENT_TAKE_FOCUS,

#if SDL_VERSION_ATLEAST(2, 0, 18)
  display_changed = SDL_WINDOWEVENT_DISPLAY_CHANGED,
  icc_profile_changed = SDL_WINDOWEVENT_ICCPROF_CHANGED,
#endif  // SDL_VERSION_ATLEAST(2, 0, 18)

  hit_test = SDL_WINDOWEVENT_HIT_TEST
};

/// \name Window event ID functions
/// \{

[[nodiscard]] constexpr auto to_string(const window_event_id id) -> std::string_view
{
  switch (id) {
    case window_event_id::none:
      return "none";

    case window_event_id::shown:
      return "shown";

    case window_event_id::hidden:
      return "hidden";

    case window_event_id::exposed:
      return "exposed";

    case window_event_id::moved:
      return "moved";

    case window_event_id::resized:
      return "resized";

    case window_event_id::size_changed:
      return "size_changed";

    case window_event_id::minimized:
      return "minimized";

    case window_event_id::maximized:
      return "maximized";

    case window_event_id::restored:
      return "restored";

    case window_event_id::enter:
      return "enter";

    case window_event_id::leave:
      return "leave";

    case window_event_id::focus_gained:
      return "focus_gained";

    case window_event_id::focus_lost:
      return "focus_lost";

    case window_event_id::close:
      return "close";

    case window_event_id::take_focus:
      return "take_focus";

    case window_event_id::hit_test:
      return "hit_test";

#if SDL_VERSION_ATLEAST(2, 0, 18)

    case window_event_id::display_changed:
      return "display_changed";

    case window_event_id::icc_profile_changed:
      return "icc_profile_changed";

#endif  // SDL_VERSION_ATLEAST(2, 0, 18)

    default:
      throw exception{"Did not recognize window event ID!"};
  }
}

inline auto operator<<(std::ostream& stream, const window_event_id id) -> std::ostream&
{
  return stream << to_string(id);
}

/// \} End of window event ID functions

class window_event final : public event_base<SDL_WindowEvent> {
 public:
  window_event() : event_base{event_type::window} {}

  explicit window_event(const SDL_WindowEvent& event) noexcept : event_base{event} {}

  void set_event_id(const window_event_id id) noexcept
  {
    mEvent.event = static_cast<uint8>(id);
  }

  void set_data1(const int32 value) noexcept { mEvent.data1 = value; }

  void set_data2(const int32 value) noexcept { mEvent.data2 = value; }

  [[nodiscard]] auto event_id() const noexcept -> window_event_id
  {
    return static_cast<window_event_id>(mEvent.event);
  }

  [[nodiscard]] auto data1() const noexcept -> int32 { return mEvent.data1; }

  [[nodiscard]] auto data2() const noexcept -> int32 { return mEvent.data2; }
};

template <>
inline auto as_sdl_event(const event_base<SDL_WindowEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.window = event.get();
  return e;
}

/// \} End of group event

}  // namespace cen

#endif  // CENTURION_WINDOW_EVENTS_HPP_
