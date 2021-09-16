#ifndef CENTURION_LOG_PRIORITY_HEADER
#define CENTURION_LOG_PRIORITY_HEADER

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "exception.hpp"

namespace cen {

/// \addtogroup core
/// \{

/**
 * \enum log_priority
 *
 * \brief Provides values that represent different logging priorities.
 *
 * \see `SDL_LogPriority`
 *
 * \since 3.0.0
 */
enum class log_priority : int
{
  verbose = SDL_LOG_PRIORITY_VERBOSE,
  debug = SDL_LOG_PRIORITY_DEBUG,
  info = SDL_LOG_PRIORITY_INFO,
  warn = SDL_LOG_PRIORITY_WARN,
  error = SDL_LOG_PRIORITY_ERROR,
  critical = SDL_LOG_PRIORITY_CRITICAL,
};

/**
 * \brief Returns the number of available log priorities.
 *
 * \return the number of log priorities.
 *
 * \since 6.2.0
 */
[[nodiscard]] constexpr auto log_priority_count() noexcept -> int
{
  return SDL_NUM_LOG_PRIORITIES;
}

/// \name String conversions
/// \{

/**
 * \brief Returns a textual version of the supplied log priority.
 *
 * \details This function returns a string that mirrors the name of the enumerator, e.g.
 * `to_string(log_priority::debug) == "debug"`.
 *
 * \param priority the enumerator that will be converted.
 *
 * \return a string that mirrors the name of the enumerator.
 *
 * \throws cen_error if the enumerator is not recognized.
 *
 * \since 6.2.0
 */
[[nodiscard]] constexpr auto to_string(const log_priority priority) -> std::string_view
{
  switch (priority) {
    case log_priority::verbose:
      return "verbose";

    case log_priority::debug:
      return "debug";

    case log_priority::info:
      return "info";

    case log_priority::warn:
      return "warn";

    case log_priority::error:
      return "error";

    case log_priority::critical:
      return "critical";

    default:
      throw cen_error{"Did not recognize log priority!"};
  }
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of a log priority enumerator.
 *
 * \param stream the output stream that will be used.
 * \param priority the enumerator that will be printed.
 *
 * \see `to_string(log_priority)`
 *
 * \return the used stream.
 *
 * \since 6.2.0
 */
inline auto operator<<(std::ostream& stream, const log_priority priority) -> std::ostream&
{
  return stream << to_string(priority);
}

/// \} End of streaming

/// \name Log priority comparison operators
/// \{

/**
 * \brief Indicates whether or not the two log priorities values are the same.
 *
 * \param lhs the left-hand side log priority value.
 * \param rhs the right-hand side log priority value.
 *
 * \return `true` if the priorities are the same; `false` otherwise.
 *
 * \since 3.0.0
 */
[[nodiscard]] constexpr auto operator==(const log_priority lhs,
                                        const SDL_LogPriority rhs) noexcept -> bool
{
  return static_cast<SDL_LogPriority>(lhs) == rhs;
}

/// \copydoc operator==(const log_priority, const SDL_LogPriority)
[[nodiscard]] constexpr auto operator==(const SDL_LogPriority lhs,
                                        const log_priority rhs) noexcept -> bool
{
  return rhs == lhs;
}

/**
 * \brief Indicates whether or not the two log priorities values aren't the same.
 *
 * \param lhs the left-hand side log priority value.
 * \param rhs the right-hand side log priority value.
 *
 * \return `true` if the priorities aren't the same; `false` otherwise.
 *
 * \since 3.0.0
 */
[[nodiscard]] constexpr auto operator!=(const log_priority lhs,
                                        const SDL_LogPriority rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \copydoc operator!=(const log_priority, const SDL_LogPriority)
[[nodiscard]] constexpr auto operator!=(const SDL_LogPriority lhs,
                                        const log_priority rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \} End of log priority comparison operators

/// \} End of group core

}  // namespace cen

#endif  // CENTURION_LOG_PRIORITY_HEADER
