#ifndef CENTURION_LOG_HEADER
#define CENTURION_LOG_HEADER

#include <SDL.h>

#include <cassert>  // assert
#include <string>   // string
#include <utility>  // forward

#include "czstring.hpp"
#include "macros.hpp"
#include "not_null.hpp"
#include "to_underlying.hpp"

#if CENTURION_SDL_VERSION_IS(2, 0, 10)

// Workaround for this enum being completely anonymous in SDL 2.0.10
using SDL_LogCategory = decltype(SDL_LOG_CATEGORY_APPLICATION);

#endif  // CENTURION_SDL_VERSION_IS(2, 0, 10)

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

/**
 * \enum log_category
 *
 * \brief Provides values that represent different logging categories.
 *
 * \see `SDL_LogCategory`
 *
 * \since 3.0.0
 */
enum class log_category : int
{
  app = SDL_LOG_CATEGORY_APPLICATION,
  error = SDL_LOG_CATEGORY_ERROR,
  assert = SDL_LOG_CATEGORY_ASSERT,
  system = SDL_LOG_CATEGORY_SYSTEM,
  audio = SDL_LOG_CATEGORY_AUDIO,
  video = SDL_LOG_CATEGORY_VIDEO,
  render = SDL_LOG_CATEGORY_RENDER,
  input = SDL_LOG_CATEGORY_INPUT,
  test = SDL_LOG_CATEGORY_TEST,
  misc = SDL_LOG_CATEGORY_CUSTOM
};

/// \} End of group core

/**
 * \namespace cen::log
 *
 * \ingroup core
 *
 * \brief Contains easy-to-use logging facilities.
 *
 * \details The usage of the logging API will be very familiar to most people that have
 * used the `printf` and/or the `SDL_Log` facilities.
 *
 * \since 3.0.0
 */
namespace log {

/// \addtogroup core
/// \{

/**
 * \brief Logs a message with the specified priority and category.
 *
 * \details This method has no effect if the supplied string is null. Usage of this method
 * is quite bulky, so refer to the other logging methods for casual logging.
 *
 * \tparam Args the types of the arguments that will be used in the formatted string.
 *
 * \param priority the priority that will be used.
 * \param category the category that will be used.
 * \param fmt the formatted string that will be logged, cannot be null.
 * \param args the arguments that will be used by the formatted string.
 *
 * \since 4.0.0
 */
template <typename... Args>
void msg(const log_priority priority,
         const log_category category,
         const not_null<czstring> fmt,
         Args&&... args) noexcept
{
  assert(fmt);
  const auto sdlCategory = static_cast<SDL_LogCategory>(category);
  const auto prio = static_cast<SDL_LogPriority>(priority);
  SDL_LogMessage(sdlCategory, prio, fmt, std::forward<Args>(args)...);
}

/**
 * \brief Logs a message with `priority::info` and the specified category.
 *
 * \details This method has no effect if the supplied string is null.
 *
 * \tparam Args the types of the arguments that will be used in the formatted string.
 *
 * \param category the category that will be used.
 * \param fmt the formatted string that will be logged, cannot be null.
 * \param args the arguments that will be used by the formatted string.
 *
 * \since 4.0.0
 */
template <typename... Args>
void info(const log_category category,
          const not_null<czstring> fmt,
          Args&&... args) noexcept
{
  log::msg(log_priority::info, category, fmt, std::forward<Args>(args)...);
}

/**
 * \brief Logs a message with `priority::info` and `category::app`.
 *
 * \details This method has no effect if the supplied string is null.
 *
 * \tparam Args the types of the arguments that will be used in the formatted string.
 *
 * \param fmt the formatted string that will be logged, cannot be null.
 * \param args the arguments that will be used by the formatted string.
 *
 * \since 4.0.0
 */
template <typename... Args>
void info(const not_null<czstring> fmt, Args&&... args) noexcept
{
  log::info(log_category::app, fmt, std::forward<Args>(args)...);
}

/**
 * \brief Logs a message with `priority::warn` and the specified category.
 *
 * \details This method has no effect if the supplied string is null.
 *
 * \tparam Args the types of the arguments that will be used in the formatted string.
 *
 * \param category the category that will be used.
 * \param fmt the formatted string that will be logged, cannot be null.
 * \param args the arguments that will be used by the formatted string.
 *
 * \since 4.0.0
 */
template <typename... Args>
void warn(const log_category category,
          const not_null<czstring> fmt,
          Args&&... args) noexcept
{
  log::msg(log_priority::warn, category, fmt, std::forward<Args>(args)...);
}

/**
 * \brief Logs a message with `priority::warn` and `category::app`.
 *
 * \details This method has no effect if the supplied string is null.
 *
 * \tparam Args the types of the arguments that will be used in the formatted string.
 *
 * \param fmt the formatted string that will be logged, cannot be null.
 * \param args the arguments that will be used by the formatted string.
 *
 * \since 4.0.0
 */
template <typename... Args>
void warn(const not_null<czstring> fmt, Args&&... args) noexcept
{
  log::warn(log_category::app, fmt, std::forward<Args>(args)...);
}

/**
 * \brief Logs a message with `priority::verbose` and the specified category.
 *
 * \details This method has no effect if the supplied string is null.
 *
 * \tparam Args the types of the arguments that will be used in the formatted string.
 *
 * \param category the category that will be used.
 * \param fmt the formatted string that will be logged, cannot be null.
 * \param args the arguments that will be used by the formatted string.
 *
 * \since 4.0.0
 */
template <typename... Args>
void verbose(const log_category category,
             const not_null<czstring> fmt,
             Args&&... args) noexcept
{
  log::msg(log_priority::verbose, category, fmt, std::forward<Args>(args)...);
}

/**
 * \brief Logs a message with `priority::verbose` and `category::app`.
 *
 * \details This method has no effect if the supplied string is null.
 *
 * \tparam Args the types of the arguments that will be used in the formatted string.
 *
 * \param fmt the formatted string that will be logged, cannot be null.
 * \param args the arguments that will be used by the formatted string.
 *
 * \since 4.0.0
 */
template <typename... Args>
void verbose(const not_null<czstring> fmt, Args&&... args) noexcept
{
  log::verbose(log_category::app, fmt, std::forward<Args>(args)...);
}

/**
 * \brief Logs a message with `priority::debug` and the specified category.
 *
 * \details This method has no effect if the supplied string is null.
 *
 * \tparam Args the types of the arguments that will be used in the formatted string.
 *
 * \param category the category that will be used.
 * \param fmt the formatted string that will be logged, cannot be null.
 * \param args the arguments that will be used by the formatted string.
 *
 * \since 4.0.0
 */
template <typename... Args>
void debug(const log_category category,
           const not_null<czstring> fmt,
           Args&&... args) noexcept
{
  log::msg(log_priority::debug, category, fmt, std::forward<Args>(args)...);
}

/**
 * \brief Logs a message with `priority::debug` and `category::app`.
 *
 * \details This method has no effect if the supplied string is null.
 *
 * \tparam Args the types of the arguments that will be used in the formatted string.
 *
 * \param fmt the formatted string that will be logged, cannot be null.
 * \param args the arguments that will be used by the formatted string.
 *
 * \since 4.0.0
 */
template <typename... Args>
void debug(const not_null<czstring> fmt, Args&&... args) noexcept
{
  log::debug(log_category::app, fmt, std::forward<Args>(args)...);
}

/**
 * \brief Logs a message with `priority::critical` and the specified category.
 *
 * \details This method has no effect if the supplied string is null.
 *
 * \tparam Args the types of the arguments that will be used in the formatted string.
 *
 * \param category the category that will be used.
 * \param fmt the formatted string that will be logged, cannot be null.
 * \param args the arguments that will be used by the formatted string.
 *
 * \since 4.0.0
 */
template <typename... Args>
void critical(const log_category category,
              const not_null<czstring> fmt,
              Args&&... args) noexcept
{
  log::msg(log_priority::critical, category, fmt, std::forward<Args>(args)...);
}

/**
 * \brief Logs a message with `priority::critical` and `category::app` .
 *
 * \details This method has no effect if the supplied string is null.
 *
 * \tparam Args the types of the arguments that will be used in the formatted string.
 *
 * \param fmt the formatted string that will be logged, cannot be null.
 * \param args the arguments that will be used by the formatted string.
 *
 * \since 4.0.0
 */
template <typename... Args>
void critical(const not_null<czstring> fmt, Args&&... args) noexcept
{
  log::critical(log_category::app, fmt, std::forward<Args>(args)...);
}

/**
 * \brief Logs a message with `priority::error` and the specified category.
 *
 * \details This method has no effect if the supplied string is null.
 *
 * \tparam Args the types of the arguments that will be used in the formatted string.
 *
 * \param category the category that will be used.
 * \param fmt the formatted string that will be logged, cannot be null.
 * \param args the arguments that will be used by the formatted string.
 *
 * \since 4.0.0
 */
template <typename... Args>
void error(const log_category category, const czstring fmt, Args&&... args) noexcept
{
  log::msg(log_priority::error, category, fmt, std::forward<Args>(args)...);
}

/**
 * \brief Logs a message with the `priority::error` and `category::app`.
 *
 * \tparam Args the types of the arguments that will be used in the formatted string.
 *
 * \param fmt the formatted string that will be logged, cannot be null.
 * \param args the arguments that will be used by the formatted string.
 *
 * \since 4.0.0
 */
template <typename... Args>
void error(const not_null<czstring> fmt, Args&&... args) noexcept
{
  log::error(log_category::app, fmt, std::forward<Args>(args)...);
}

/**
 * \brief Logs a string.
 *
 * \details This function is meant to be used for casual logging, where you just want to
 * log a string. The message will be logged with `priority::info` and `category::app`.
 *
 * \param str the string that will be logged.
 *
 * \since 5.0.0
 */
inline void put(const std::string& str) noexcept
{
  log::info("%s", str.c_str());
}

/// \copydoc put(const std::string&)
inline void put(const not_null<czstring> str) noexcept
{
  log::info("%s", str);
}

/**
 * \brief Resets all of the logging priorities.
 *
 * \since 3.0.0
 */
inline void reset_priorities() noexcept
{
  SDL_LogResetPriorities();
}

/**
 * \brief Sets the priority of all categories.
 *
 * \param priority the priority that will be used.
 *
 * \since 3.0.0
 */
inline void set_priority(const log_priority priority) noexcept
{
  const auto p = static_cast<SDL_LogPriority>(priority);
  SDL_LogSetAllPriority(p);

  // Apparently not set by SDL
  SDL_LogSetPriority(SDL_LOG_CATEGORY_TEST, p);
}

/**
 * \brief Sets the priority of the specified category.
 *
 * \param category the category that will have its priority changed.
 * \param priority the new priority value.
 *
 * \since 3.0.0
 */
inline void set_priority(const log_category category,
                         const log_priority priority) noexcept
{
  SDL_LogSetPriority(to_underlying(category), static_cast<SDL_LogPriority>(priority));
}

/**
 * \brief Returns the priority of the specified category.
 *
 * \param category the category to return the priority of.
 * \return the priority of the specified category.
 *
 * \since 3.0.0
 */
[[nodiscard]] inline auto get_priority(const log_category category) noexcept
    -> log_priority
{
  return static_cast<log_priority>(SDL_LogGetPriority(to_underlying(category)));
}

/**
 * \brief Returns the maximum size, i.e the maximum amount of characters that a string can
 * contain and successfully be logged without being truncated.
 *
 * \note Strings longer that this value will be truncated.
 *
 * \return the maximum amount of characters that a loggable string can contain.
 *
 * \see `SDL_MAX_LOG_MESSAGE`
 *
 * \since 4.0.0
 */
[[nodiscard]] constexpr auto max_message_size() noexcept -> int
{
  return SDL_MAX_LOG_MESSAGE;
}

/// \} End of group core

}  // namespace log

/// \addtogroup core
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

/// \copydoc operator==(log_priority, SDL_LogPriority)
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

/// \copydoc operator!=(log_priority, SDL_LogPriority)
[[nodiscard]] constexpr auto operator!=(const SDL_LogPriority lhs,
                                        const log_priority rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/**
 * \brief Indicates whether or not the two log category values are the same.
 *
 * \param lhs the left-hand side log category value.
 * \param rhs the right-hand side log category value.
 *
 * \return `true` if the categories are the same; `false` otherwise.
 *
 * \since 4.0.0
 */
[[nodiscard]] constexpr auto operator==(const log_category lhs,
                                        const SDL_LogCategory rhs) noexcept -> bool
{
  return static_cast<SDL_LogCategory>(lhs) == rhs;
}

/// \copydoc operator==(log_category, SDL_LogCategory)
[[nodiscard]] constexpr auto operator==(const SDL_LogCategory lhs,
                                        const log_category rhs) noexcept -> bool
{
  return rhs == lhs;
}

/**
 * \brief Indicates whether or not the two log category values are the same.
 *
 * \param lhs the left-hand side log category value.
 * \param rhs the right-hand side log category value.
 *
 * \return `true` if the categories are the same; `false` otherwise.
 *
 * \since 4.0.0
 */
[[nodiscard]] constexpr auto operator!=(const log_category lhs,
                                        const SDL_LogCategory rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \copydoc operator!=(log_category, SDL_LogCategory)
[[nodiscard]] constexpr auto operator!=(const SDL_LogCategory lhs,
                                        const log_category rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \} End of group core

}  // namespace cen

/// \addtogroup core
/// \{

#ifndef CENTURION_NO_DEBUG_LOG_MACROS
#ifdef NDEBUG

/// \def CENTURION_LOG_INFO
#define CENTURION_LOG_INFO(fmt, ...)

/// \def CENTURION_LOG_WARN
#define CENTURION_LOG_WARN(fmt, ...)

/// \def CENTURION_LOG_VERBOSE
#define CENTURION_LOG_VERBOSE(fmt, ...)

/// \def CENTURION_LOG_DEBUG
#define CENTURION_LOG_DEBUG(fmt, ...)

/// \def CENTURION_LOG_CRITICAL
#define CENTURION_LOG_CRITICAL(fmt, ...)

/// \def CENTURION_LOG_ERROR
#define CENTURION_LOG_ERROR(fmt, ...)

#else

/// \def CENTURION_LOG_INFO
#define CENTURION_LOG_INFO(fmt, ...) cen::log::info(fmt, __VA_ARGS__)

/// \def CENTURION_LOG_WARN
#define CENTURION_LOG_WARN(fmt, ...) cen::log::warn(fmt, __VA_ARGS__)

/// \def CENTURION_LOG_VERBOSE
#define CENTURION_LOG_VERBOSE(fmt, ...) cen::log::verbose(fmt, __VA_ARGS__)

/// \def CENTURION_LOG_DEBUG
#define CENTURION_LOG_DEBUG(fmt, ...) cen::log::debug(fmt, __VA_ARGS__)

/// \def CENTURION_LOG_CRITICAL
#define CENTURION_LOG_CRITICAL(fmt, ...) cen::log::critical(fmt, __VA_ARGS__)

/// \def CENTURION_LOG_ERROR
#define CENTURION_LOG_ERROR(fmt, ...) cen::log::error(fmt, __VA_ARGS__)

#endif  // NDEBUG
#endif  // CENTURION_NO_DEBUG_LOG_MACROS

/**
 * \def CENTURION_LOG_INFO
 *
 * \note This macro can be excluded by defining `CENTURION_NO_DEBUG_LOG_MACROS`.
 *
 * \brief A debug-only macro that expands to `cen::log::info`.
 *
 * \since 5.0.0
 */

/**
 * \def CENTURION_LOG_WARN
 *
 * \note This macro can be excluded by defining `CENTURION_NO_DEBUG_LOG_MACROS`.
 *
 * \brief A debug-only macro that expands to `cen::log::warn`.
 *
 * \since 5.0.0
 */

/**
 * \def CENTURION_LOG_VERBOSE
 *
 * \note This macro can be excluded by defining `CENTURION_NO_DEBUG_LOG_MACROS`.
 *
 * \brief A debug-only macro that expands to `cen::log::verbose`.
 *
 * \since 5.0.0
 */

/**
 * \def CENTURION_LOG_DEBUG
 *
 * \note This macro can be excluded by defining `CENTURION_NO_DEBUG_LOG_MACROS`.
 *
 * \brief A debug-only macro that expands to `cen::log::debug`.
 *
 * \since 5.0.0
 */

/**
 * \def CENTURION_LOG_CRITICAL
 *
 * \note This macro can be excluded by defining `CENTURION_NO_DEBUG_LOG_MACROS`.
 *
 * \brief A debug-only macro that expands to `cen::log::critical`.
 *
 * \since 5.0.0
 */

/**
 * \def CENTURION_LOG_ERROR
 *
 * \note This macro can be excluded by defining `CENTURION_NO_DEBUG_LOG_MACROS`.
 *
 * \brief A debug-only macro that expands to `cen::log::error`.
 *
 * \since 5.0.0
 */

/// \} End of group core

#endif  // CENTURION_LOG_HEADER
