#ifndef CENTURION_LOCK_STATUS_HEADER
#define CENTURION_LOCK_STATUS_HEADER

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../core/exception.hpp"

namespace cen {

/// \addtogroup thread
/// \{

enum class lock_status
{
  success = 0,
  timed_out = SDL_MUTEX_TIMEDOUT,
  error = -1
};

/// \name String conversions
/// \{

/**
 * \brief Returns a textual version of the supplied lock status.
 *
 * \details This function returns a string that mirrors the name of the enumerator, e.g.
 * `to_string(lock_status::success) == "success"`.
 *
 * \param status the enumerator that will be converted.
 *
 * \return a string that mirrors the name of the enumerator.
 *
 * \throws cen_error if the enumerator is not recognized.
 *
 * \since 6.2.0
 */
[[nodiscard]] constexpr auto to_string(const lock_status status) -> std::string_view
{
  switch (status) {
    case lock_status::success:
      return "success";

    case lock_status::timed_out:
      return "timed_out";

    case lock_status::error:
      return "error";

    default:
      throw cen_error{"Did not recognize lock status!"};
  }
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of a lock status enumerator.
 *
 * \param stream the output stream that will be used.
 * \param status the enumerator that will be printed.
 *
 * \see `to_string(lock_status)`
 *
 * \return the used stream.
 *
 * \since 6.2.0
 */
inline auto operator<<(std::ostream& stream, const lock_status status) -> std::ostream&
{
  return stream << to_string(status);
}

/// \} End of streaming

/// \} End of group thread

}  // namespace cen

#endif  // CENTURION_LOCK_STATUS_HEADER
