#ifndef CENTURION_LOG_PRIORITY_HEADER
#define CENTURION_LOG_PRIORITY_HEADER

#include <SDL.h>

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
  info = SDL_LOG_PRIORITY_INFO,
  warn = SDL_LOG_PRIORITY_WARN,
  verbose = SDL_LOG_PRIORITY_VERBOSE,
  debug = SDL_LOG_PRIORITY_DEBUG,
  critical = SDL_LOG_PRIORITY_CRITICAL,
  error = SDL_LOG_PRIORITY_ERROR,
};

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
