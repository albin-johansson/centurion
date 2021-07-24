#ifndef CENTURION_WINDOW_EVENT_HEADER
#define CENTURION_WINDOW_EVENT_HEADER

#include <SDL.h>

#include "common_event.hpp"
#include "window_event_id.hpp"

namespace cen {

/// \addtogroup event
/// \{

/**
 * \class window_event
 *
 * \brief Represents an event that is associated with an action related to a
 * window.
 *
 * \see `SDL_WindowEvent`
 *
 * \since 4.0.0
 */
class window_event final : public common_event<SDL_WindowEvent>
{
 public:
  /**
   * \brief Creates a window event.
   *
   * \since 4.0.0
   */
  window_event() noexcept : common_event{event_type::window}
  {}

  /**
   * \brief Creates a window event based on the supplied SDL window event.
   *
   * \param event the SDL window event that will be copied.
   *
   * \since 4.0.0
   */
  explicit window_event(const SDL_WindowEvent& event) noexcept : common_event{event}
  {}

  /**
   * \brief Returns the event ID of this window event.
   *
   * \details There are many different kinds of window events, use this function to check
   * what kind of action that triggered this event.
   *
   * \return the event ID of this window event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto event_id() const noexcept -> window_event_id
  {
    return static_cast<window_event_id>(m_event.event);
  }

  /**
   * \brief Returns the value of the first data value.
   *
   * \details The meaning of this value is dependent on the window event ID of this window
   * event.
   *
   * For instance, if the event ID is `window_event_id::size_changed`, then data1 and
   * data2 represent the new width and height of the window respectively. See the
   * `window_event_id` documentation for more details about whether the value returned
   * from this function is meaningful in regard to the window event ID.
   *
   * \return the value of the first data value.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto data_1() const noexcept -> i32
  {
    return m_event.data1;
  }

  /**
   * \brief Returns the value of the second data value.
   *
   * \details The meaning of this value is dependent on the window event ID of this window
   * event.
   *
   * For instance, if the event ID is `window_event_id::size_changed`, then data1 and
   * data2 represent the new width and height of the window respectively. See the
   * `window_event_id` documentation for more details about whether the value returned
   * from this function is meaningful in regard to the window event ID.
   *
   * \return the value of the second data value.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto data_2() const noexcept -> i32
  {
    return m_event.data2;
  }
};

/// \name SDL event conversions
/// \{

template <>
inline auto as_sdl_event(const common_event<SDL_WindowEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.window = event.get();
  return e;
}

/// \} End of SDL event conversions

/// \} End of group event

}  // namespace cen

#endif  // CENTURION_WINDOW_EVENT_HEADER
