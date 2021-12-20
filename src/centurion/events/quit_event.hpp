#ifndef CENTURION_EVENTS_QUIT_EVENT_HPP_
#define CENTURION_EVENTS_QUIT_EVENT_HPP_

#include <SDL.h>

#include "event_base.hpp"

namespace cen {

/// \addtogroup event
/// \{

/**
 * \class quit_event
 *
 * \brief Represents the event of the user wanting to close the application,
 * usually by pressing the "X"-button on the window frame.
 *
 * \see `SDL_QuitEvent`
 *
 * \since 4.0.0
 */
class quit_event final : public EventBase<SDL_QuitEvent> {
 public:
  /**
   * \brief Creates a quit event.
   *
   * \since 4.0.0
   */
  quit_event() noexcept : EventBase{EventType::Quit} {}

  /**
   * \brief Creates a quit event based on the supplied SDL event.
   *
   * \param event the SDL event that will be copied.
   *
   * \since 4.0.0
   */
  explicit quit_event(const SDL_QuitEvent& event) noexcept : EventBase{event} {}
};

/// \name SDL event conversions
/// \{

template <>
inline auto AsSDLEvent(const EventBase<SDL_QuitEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.quit = event.get();
  return e;
}

/// \} End of SDL event conversions

/// \} End of group event

}  // namespace cen

#endif  // CENTURION_EVENTS_QUIT_EVENT_HPP_
