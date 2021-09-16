#ifndef CENTURION_HINT_PRIORITY_HEADER
#define CENTURION_HINT_PRIORITY_HEADER

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../core/exception.hpp"

namespace cen {

/// \addtogroup hints
/// \{

/**
 * \enum hint_priority
 *
 * \brief Provides three different priorities that can be specified when
 * setting the value of a hint.
 *
 * \since 4.1.0
 *
 * \see `SDL_HintPriority`
 */
enum class hint_priority
{
  low = SDL_HINT_DEFAULT,       ///< The lowest possible priority.
  normal = SDL_HINT_NORMAL,     ///< The priority used by default by `set_hint`.
  override = SDL_HINT_OVERRIDE  ///< The highest priority.
};

/// \name String conversions
/// \{

/**
 * \brief Returns a textual version of the supplied hint priority.
 *
 * \details This function returns a string that mirrors the name of the enumerator, e.g.
 * `to_string(hint_priority::low) == "low"`.
 *
 * \param priority the enumerator that will be converted.
 *
 * \return a string that mirrors the name of the enumerator.
 *
 * \throws cen_error if the enumerator is not recognized.
 *
 * \since 6.2.0
 */
[[nodiscard]] constexpr auto to_string(const hint_priority priority) -> std::string_view
{
  switch (priority) {
    case hint_priority::low:
      return "low";

    case hint_priority::normal:
      return "normal";

    case hint_priority::override:
      return "override";

    default:
      throw cen_error{"Did not recognize hint priority!"};
  }
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of a hint priority enumerator.
 *
 * \param stream the output stream that will be used.
 * \param priority the enumerator that will be printed.
 *
 * \see `to_string(hint_priority)`
 *
 * \return the used stream.
 *
 * \since 6.2.0
 */
inline auto operator<<(std::ostream& stream, const hint_priority priority) -> std::ostream&
{
  return stream << to_string(priority);
}

/// \} End of streaming

/// \} End of group hints

}  // namespace cen

#endif  // CENTURION_HINT_PRIORITY_HEADER
