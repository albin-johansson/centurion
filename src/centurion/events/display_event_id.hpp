#ifndef CENTURION_DISPLAY_EVENT_ID_HEADER
#define CENTURION_DISPLAY_EVENT_ID_HEADER

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../core/exception.hpp"

namespace cen {

#if SDL_VERSION_ATLEAST(2, 0, 14)

/// \addtogroup event
/// \{

/**
 * \enum display_event_id
 *
 * \brief Represents the different variants of `display_event` events.
 *
 * \see `display_event_id_count()`
 * \see `display_event`
 *
 * \since 6.3.0
 */
enum class display_event_id
{
  none = SDL_DISPLAYEVENT_NONE,                  ///< Unused.
  orientation = SDL_DISPLAYEVENT_ORIENTATION,    ///< Display orientation changed.
  connected = SDL_DISPLAYEVENT_CONNECTED,        ///< A display was added.
  disconnected = SDL_DISPLAYEVENT_DISCONNECTED,  ///< A display was removed.
};

/**
 * \brief Returns the number of enumerators for the `display_event_id` enum.
 *
 * \return the number of enumerators.
 *
 * \since 6.3.0
 */
[[nodiscard]] constexpr auto display_event_id_count() noexcept -> int
{
  return 4;
}

/// \name String conversions
/// \{

/**
 * \brief Returns a textual version of the supplied display event ID.
 *
 * \details This function returns a string that mirrors the name of the enumerator, e.g.
 * `to_string(display_event_id::connected) == "connected"`.
 *
 * \param id the enumerator that will be converted.
 *
 * \return a string that mirrors the name of the enumerator.
 *
 * \throws cen_error if the enumerator is not recognized.
 *
 * \since 6.3.0
 */
[[nodiscard]] constexpr auto to_string(const display_event_id id) -> std::string_view
{
  switch (id) {
    case display_event_id::none:
      return "none";

    case display_event_id::orientation:
      return "orientation";

    case display_event_id::connected:
      return "connected";

    case display_event_id::disconnected:
      return "disconnected";

    default:
      throw cen_error{"Did not recognize display event ID!"};
  }
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of a display event ID enumerator.
 *
 * \param stream the output stream that will be used.
 * \param id the enumerator that will be printed.
 *
 * \see `to_string(display_event_id)`
 *
 * \return the used stream.
 *
 * \since 6.3.0
 */
inline auto operator<<(std::ostream& stream, const display_event_id id) -> std::ostream&
{
  return stream << to_string(id);
}

/// \} End of streaming

/// \} End of group event

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

}  // namespace cen

#endif  // CENTURION_DISPLAY_EVENT_ID_HEADER
