#ifndef CENTURION_QUIT_EVENT_HEADER
#define CENTURION_QUIT_EVENT_HEADER

#include <SDL_events.h>

#include "base_event.h"
#include "centurion_api.h"

namespace centurion {
namespace event {

/**
 * The QuitEvent class represents the event of the user wanting to close the
 * application, usually by pressing the "X"-button on the window frame.
 *
 * @see SDL_QuitEvent
 * @since 4.0.0
 */
class QuitEvent : public TEvent<SDL_QuitEvent> {
 public:
  /**
   * Creates a default-initialized quit event.
   *
   * @since 4.0.0
   */
  CENTURION_API QuitEvent() noexcept;

  /**
   * Creates a quit event based on the supplied SDL event.
   *
   * @param event the SDL event that will be copied.
   * @since 4.0.0
   */
  CENTURION_API explicit QuitEvent(const SDL_QuitEvent& event) noexcept;

  /**
   * Creates a quit event based on the supplied SDL event.
   *
   * @param event the SDL event that will be moved.
   * @since 4.0.0
   */
  CENTURION_API explicit QuitEvent(SDL_QuitEvent&& event) noexcept;
};

}  // namespace event
}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "quit_event.cpp"
#endif  // CENTURION_HEADER_ONLY

#endif  // CENTURION_QUIT_EVENT_HEADER