#ifndef CENTURION_WINDOW_EVENT_HEADER
#define CENTURION_WINDOW_EVENT_HEADER

#include <SDL.h>

#include "common_event.hpp"

namespace cen {

/// \addtogroup event
/// \{

/**
 * \enum window_event_id
 *
 * \brief Mirrors the `SDL_WindowEventID` enum.
 *
 * \details Depending on the event ID of a `window_event` instance, the
 * `window_event::data_1()` and `window_event::data_2()` methods have special
 * meanings.
 *
 * <table style="width:100%">
 *   <tr>
 *     <th>Value</th>
 *     <th>data_1</th>
 *     <th>data_2</th>
 *   </tr>
 *   <tr>
 *    <td><code>None</code></td>
 *    <td>N/A</td>
 *    <td>N/A</td>
 *   </tr>
 *   <tr>
 *    <td><code>Shown</code></td>
 *    <td>N/A</td>
 *    <td>N/A</td>
 *   </tr>
 *   <tr>
 *    <td><code>Hidden</code></td>
 *    <td>N/A</td>
 *    <td>N/A</td>
 *   </tr>
 *   <tr>
 *    <td><code>Exposed</code></td>
 *    <td>N/A</td>
 *    <td>N/A</td>
 *   </tr>
 *   <tr>
 *    <td><code>Moved</code></td>
 *    <td>X</td>
 *    <td>Y</td>
 *   </tr>
 *   <tr>
 *    <td><code>Resized</code></td>
 *    <td>Width</td>
 *    <td>Height</td>
 *   </tr>
 *   <tr>
 *    <td><code>SizeChanged</code></td>
 *    <td>Width</td>
 *    <td>Height</td>
 *   </tr>
 *   <tr>
 *    <td><code>Minimized</code></td>
 *    <td>N/A</td>
 *    <td>N/A</td>
 *   </tr>
 *   <tr>
 *    <td><code>Maximized</code></td>
 *    <td>N/A</td>
 *    <td>N/A</td>
 *   </tr>
 *   <tr>
 *    <td><code>Restored</code></td>
 *    <td>N/A</td>
 *    <td>N/A</td>
 *   </tr>
 *   <tr>
 *    <td><code>Enter</code></td>
 *    <td>N/A</td>
 *    <td>N/A</td>
 *   </tr>
 *   <tr>
 *    <td><code>Leave</code></td>
 *    <td>N/A</td>
 *    <td>N/A</td>
 *   </tr>
 *   <tr>
 *    <td><code>FocusGained</code></td>
 *    <td>N/A</td>
 *    <td>N/A</td>
 *   </tr>
 *   <tr>
 *    <td><code>FocusLost</code></td>
 *    <td>N/A</td>
 *    <td>N/A</td>
 *   </tr>
 *   <tr>
 *    <td><code>Close</code></td>
 *    <td>N/A</td>
 *    <td>N/A</td>
 *   </tr>
 *   <tr>
 *    <td><code>TakeFocus</code></td>
 *    <td>N/A</td>
 *    <td>N/A</td>
 *   </tr>
 *   <tr>
 *    <td><code>HitTest</code></td>
 *    <td>N/A</td>
 *    <td>N/A</td>
 *   </tr>
 * </table>
 *
 * \since 4.0.0
 *
 * \headerfile event.hpp
 */
enum class window_event_id
{
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
  hit_test = SDL_WINDOWEVENT_HIT_TEST
};

/**
 * \class window_event
 *
 * \brief Represents an event that is associated with an action related to a
 * window.
 *
 * \see `SDL_WindowEvent`
 *
 * \since 4.0.0
 *
 * \headerfile window_event.hpp
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
  explicit window_event(const SDL_WindowEvent& event) noexcept
      : common_event{event}
  {}

  /**
   * \brief Returns the event ID of this window event.
   *
   * \details There are many different kinds of window events, use this
   * method to check what kind of action that triggered this event.
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
   * \details The meaning of this value is dependent on the window event ID
   * of this window event.
   *
   * For instance, if the event ID is `SizeChanged`, then data1 and data2
   * represent the new width and height of the window respectively. See the
   * `WindowEventID` documentation for more details about whether the value
   * returned from this method is meaningful in regard to the window event ID.
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
   * \details The meaning of this value is dependent on the window event ID
   * of this window event.
   *
   * For instance, if the event ID is `SizeChanged`, then data1 and data2
   * represent the new width and height of the window respectively. See the
   * `WindowEventID` documentation for more details about whether the value
   * returned from this method is meaningful in regard to the window event ID.
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

template <>
inline auto as_sdl_event(const common_event<SDL_WindowEvent>& event)
    -> SDL_Event
{
  SDL_Event e;
  e.window = event.get();
  return e;
}

/**
 * \brief Indicates whether or not two window event ID values are the same.
 *
 * \param lhs the left-hand side window event ID value.
 * \param rhs the right-hand side window event ID value.
 *
 * \return `true` if the window event ID values are the same; `false` otherwise.
 *
 * \since 4.0.0
 */
[[nodiscard]] constexpr auto operator==(const window_event_id lhs,
                                        const SDL_WindowEventID rhs) noexcept
    -> bool
{
  return static_cast<SDL_WindowEventID>(lhs) == rhs;
}

/**
 * \copydoc operator==(window_event_id, SDL_WindowEventID)
 */
[[nodiscard]] constexpr auto operator==(const SDL_WindowEventID lhs,
                                        const window_event_id rhs) noexcept
    -> bool
{
  return rhs == lhs;
}

/**
 * \brief Indicates whether or not two window event ID values aren't the same.
 *
 * \param lhs the left-hand side window event ID value.
 * \param rhs the right-hand side window event ID value.
 *
 * \return `true` if the window event ID values aren't the same; `false`
 * otherwise.
 *
 * \since 4.0.0
 */
[[nodiscard]] constexpr auto operator!=(const window_event_id lhs,
                                        const SDL_WindowEventID rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/**
 * \copydoc operator!=(window_event_id, SDL_WindowEventID)
 */
[[nodiscard]] constexpr auto operator!=(const SDL_WindowEventID lhs,
                                        const window_event_id rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/// \} End of group event

}  // namespace cen

#endif  // CENTURION_WINDOW_EVENT_HEADER
