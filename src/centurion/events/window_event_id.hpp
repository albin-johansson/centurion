#ifndef CENTURION_WINDOW_EVENT_ID_HEADER
#define CENTURION_WINDOW_EVENT_ID_HEADER

#include <SDL.h>

#include <ostream>  // ostream
#include <string>   // string

#include "../core/exception.hpp"

namespace cen {

/// \addtogroup event
/// \{

/**
 * \enum window_event_id
 *
 * \brief Represents different flavours of window events.
 *
 * \details Depending on the event ID of a `window_event` instance, the
 * `window_event::data_1()` and `window_event::data_2()` methods have special meanings.
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
 * \brief Returns a textual version of the supplied window event ID.
 *
 * \details This function returns a string that mirrors the name of the enumerator, e.g.
 * `to_string(window_event_id::enter) == "enter"`.
 *
 * \param id the enumerator that will be converted.
 *
 * \return a string that mirrors the name of the enumerator.
 *
 * \throws cen_error if the enumerator is not recognized.
 *
 * \since 6.2.0
 */
[[nodiscard]] inline auto to_string(const window_event_id id) -> std::string
{
  switch (id)
  {
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

    default:
      throw cen_error{"Did not recognize window event ID!"};
  }
}

/**
 * \brief Prints a textual representation of a window event ID enumerator.
 *
 * \param stream the output stream that will be used.
 * \param id the enumerator that will be printed.
 *
 * \see `to_string(window_event_id)`
 *
 * \return the used stream.
 *
 * \since 6.2.0
 */
inline auto operator<<(std::ostream& stream, const window_event_id id) -> std::ostream&
{
  return stream << to_string(id);
}

/// \name Window event ID comparison operators
/// \{

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
                                        const SDL_WindowEventID rhs) noexcept -> bool
{
  return static_cast<SDL_WindowEventID>(lhs) == rhs;
}

/// \copydoc operator==(window_event_id, SDL_WindowEventID)
[[nodiscard]] constexpr auto operator==(const SDL_WindowEventID lhs,
                                        const window_event_id rhs) noexcept -> bool
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
                                        const SDL_WindowEventID rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \copydoc operator!=(window_event_id, SDL_WindowEventID)
[[nodiscard]] constexpr auto operator!=(const SDL_WindowEventID lhs,
                                        const window_event_id rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \} End of window event ID comparison operators

/// \} End of group event

}  // namespace cen

#endif  // CENTURION_WINDOW_EVENT_ID_HEADER
