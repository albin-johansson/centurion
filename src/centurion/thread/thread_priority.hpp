#ifndef CENTURION_THREAD_PRIORITY_HEADER
#define CENTURION_THREAD_PRIORITY_HEADER

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../core/exception.hpp"

namespace cen {

/// \addtogroup thread
/// \{

/**
 * \enum thread_priority
 *
 * \brief Represents different thread priorities.
 *
 * \note You might need higher privileges to use `high` or `critical` priorities.
 *
 * \since 5.0.0
 */
enum class thread_priority
{
  // clang-format off
  low = SDL_THREAD_PRIORITY_LOW,        ///< Non-urgent, background processing.
  normal = SDL_THREAD_PRIORITY_NORMAL,  ///< General purpose processing, this is the default.
  high = SDL_THREAD_PRIORITY_HIGH,              ///< For high-priority processing.
  critical = SDL_THREAD_PRIORITY_TIME_CRITICAL  ///< For timing-critical processing.
  // clang-format on
};

/// \name String conversions
/// \{

/**
 * \brief Returns a textual version of the supplied thread priority.
 *
 * \details This function returns a string that mirrors the name of the enumerator, e.g.
 * `to_string(thread_priority::high) == "high"`.
 *
 * \param priority the enumerator that will be converted.
 *
 * \return a string that mirrors the name of the enumerator.
 *
 * \throws cen_error if the enumerator is not recognized.
 *
 * \since 6.2.0
 */
[[nodiscard]] constexpr auto to_string(const thread_priority priority) -> std::string_view
{
  switch (priority) {
    case thread_priority::low:
      return "low";

    case thread_priority::normal:
      return "normal";

    case thread_priority::high:
      return "high";

    case thread_priority::critical:
      return "critical";

    default:
      throw cen_error{"Did not recognize thread priority!"};
  }
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of a thread priority enumerator.
 *
 * \param stream the output stream that will be used.
 * \param priority the enumerator that will be printed.
 *
 * \see `to_string(thread_priority)`
 *
 * \return the used stream.
 *
 * \since 6.2.0
 */
inline auto operator<<(std::ostream& stream, const thread_priority priority) -> std::ostream&
{
  return stream << to_string(priority);
}

/// \} End of streaming

/// \name Thread priority comparison operators
/// \{

/**
 * \brief Indicates whether or not two thread priorities are the same.
 *
 * \param lhs the left-hand side thread priority.
 * \param rhs the right-hand side thread priority.
 *
 * \return `true` if the priorities are the same; `false` otherwise.
 *
 * \since 5.0.0
 */
[[nodiscard]] constexpr auto operator==(const thread_priority lhs,
                                        const SDL_ThreadPriority rhs) noexcept -> bool
{
  return static_cast<SDL_ThreadPriority>(lhs) == rhs;
}

/// \copydoc operator==(thread_priority, SDL_ThreadPriority)
[[nodiscard]] constexpr auto operator==(const SDL_ThreadPriority lhs,
                                        const thread_priority rhs) noexcept -> bool
{
  return rhs == lhs;
}

/**
 * \brief Indicates whether or not two thread priorities aren't the same.
 *
 * \param lhs the left-hand side thread priority.
 * \param rhs the right-hand side thread priority.
 *
 * \return `true` if the priorities aren't the same; `false` otherwise.
 *
 * \since 5.0.0
 */
[[nodiscard]] constexpr auto operator!=(const thread_priority lhs,
                                        const SDL_ThreadPriority rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \copydoc operator!=(thread_priority, SDL_ThreadPriority)
[[nodiscard]] constexpr auto operator!=(const SDL_ThreadPriority lhs,
                                        const thread_priority rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \} End of thread priority comparison operators

/// \} End of group thread

}  // namespace cen

#endif  // CENTURION_THREAD_PRIORITY_HEADER
