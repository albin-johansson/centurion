#ifndef CENTURION_LOG_HEADER
#define CENTURION_LOG_HEADER

#include <SDL.h>

#include <cassert>  // assert
#include <string>   // string
#include <utility>  // forward

#include "log_category.hpp"
#include "log_priority.hpp"
#include "not_null.hpp"
#include "str.hpp"
#include "to_underlying.hpp"

namespace cen {

/// \namespace cen::log
/// \brief Contains easy-to-use logging facilities.
/// \ingroup core
/// \since 3.0.0
namespace log {

/// \addtogroup core
/// \{

/**
 * \brief Logs a message with the specified priority and category.
 *
 * \details This function has no effect if the supplied string is null. Usage of this
 * function is quite bulky, so refer to the other logging methods for casual logging.
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
         const not_null<str> fmt,
         Args&&... args) noexcept
{
  assert(fmt);
  const auto sdlCategory = static_cast<SDL_LogCategory>(category);
  const auto prio = static_cast<SDL_LogPriority>(priority);
  SDL_LogMessage(sdlCategory, prio, fmt, std::forward<Args>(args)...);
}

/**
 * \brief Logs a message with `log_priority::info` and the specified category.
 *
 * \details This function has no effect if the supplied string is null.
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
void info(const log_category category, const not_null<str> fmt, Args&&... args) noexcept
{
  log::msg(log_priority::info, category, fmt, std::forward<Args>(args)...);
}

/**
 * \brief Logs a message with `log_priority::info` and `log_category::app`.
 *
 * \details This function has no effect if the supplied string is null.
 *
 * \tparam Args the types of the arguments that will be used in the formatted string.
 *
 * \param fmt the formatted string that will be logged, cannot be null.
 * \param args the arguments that will be used by the formatted string.
 *
 * \since 4.0.0
 */
template <typename... Args>
void info(const not_null<str> fmt, Args&&... args) noexcept
{
  log::info(log_category::app, fmt, std::forward<Args>(args)...);
}

/**
 * \brief Logs a message with `log_priority::warn` and the specified category.
 *
 * \details This function has no effect if the supplied string is null.
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
void warn(const log_category category, const not_null<str> fmt, Args&&... args) noexcept
{
  log::msg(log_priority::warn, category, fmt, std::forward<Args>(args)...);
}

/**
 * \brief Logs a message with `log_priority::warn` and `log_category::app`.
 *
 * \details This function has no effect if the supplied string is null.
 *
 * \tparam Args the types of the arguments that will be used in the formatted string.
 *
 * \param fmt the formatted string that will be logged, cannot be null.
 * \param args the arguments that will be used by the formatted string.
 *
 * \since 4.0.0
 */
template <typename... Args>
void warn(const not_null<str> fmt, Args&&... args) noexcept
{
  log::warn(log_category::app, fmt, std::forward<Args>(args)...);
}

/**
 * \brief Logs a message with `log_priority::verbose` and the specified category.
 *
 * \details This function has no effect if the supplied string is null.
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
             const not_null<str> fmt,
             Args&&... args) noexcept
{
  log::msg(log_priority::verbose, category, fmt, std::forward<Args>(args)...);
}

/**
 * \brief Logs a message with `log_priority::verbose` and `log_category::app`.
 *
 * \details This function has no effect if the supplied string is null.
 *
 * \tparam Args the types of the arguments that will be used in the formatted string.
 *
 * \param fmt the formatted string that will be logged, cannot be null.
 * \param args the arguments that will be used by the formatted string.
 *
 * \since 4.0.0
 */
template <typename... Args>
void verbose(const not_null<str> fmt, Args&&... args) noexcept
{
  log::verbose(log_category::app, fmt, std::forward<Args>(args)...);
}

/**
 * \brief Logs a message with `log_priority::debug` and the specified category.
 *
 * \details This function has no effect if the supplied string is null.
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
void debug(const log_category category, const not_null<str> fmt, Args&&... args) noexcept
{
  log::msg(log_priority::debug, category, fmt, std::forward<Args>(args)...);
}

/**
 * \brief Logs a message with `log_priority::debug` and `log_category::app`.
 *
 * \details This function has no effect if the supplied string is null.
 *
 * \tparam Args the types of the arguments that will be used in the formatted string.
 *
 * \param fmt the formatted string that will be logged, cannot be null.
 * \param args the arguments that will be used by the formatted string.
 *
 * \since 4.0.0
 */
template <typename... Args>
void debug(const not_null<str> fmt, Args&&... args) noexcept
{
  log::debug(log_category::app, fmt, std::forward<Args>(args)...);
}

/**
 * \brief Logs a message with `log_priority::critical` and the specified category.
 *
 * \details This function has no effect if the supplied string is null.
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
              const not_null<str> fmt,
              Args&&... args) noexcept
{
  log::msg(log_priority::critical, category, fmt, std::forward<Args>(args)...);
}

/**
 * \brief Logs a message with `log_priority::critical` and `log_category::app`.
 *
 * \details This function has no effect if the supplied string is null.
 *
 * \tparam Args the types of the arguments that will be used in the formatted string.
 *
 * \param fmt the formatted string that will be logged, cannot be null.
 * \param args the arguments that will be used by the formatted string.
 *
 * \since 4.0.0
 */
template <typename... Args>
void critical(const not_null<str> fmt, Args&&... args) noexcept
{
  log::critical(log_category::app, fmt, std::forward<Args>(args)...);
}

/**
 * \brief Logs a message with `log_priority::error` and the specified category.
 *
 * \details This function has no effect if the supplied string is null.
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
void error(const log_category category, const str fmt, Args&&... args) noexcept
{
  log::msg(log_priority::error, category, fmt, std::forward<Args>(args)...);
}

/**
 * \brief Logs a message with the `log_priority::error` and `log_category::app`.
 *
 * \tparam Args the types of the arguments that will be used in the formatted string.
 *
 * \param fmt the formatted string that will be logged, cannot be null.
 * \param args the arguments that will be used by the formatted string.
 *
 * \since 4.0.0
 */
template <typename... Args>
void error(const not_null<str> fmt, Args&&... args) noexcept
{
  log::error(log_category::app, fmt, std::forward<Args>(args)...);
}

/**
 * \brief Logs a string.
 *
 * \details This function is meant to be used for casual logging, where you just want to
 * log a string. The message will be logged with `log_priority::info` and
 * `log_category::app`.
 *
 * \param str the string that will be logged.
 *
 * \since 5.0.0
 */
inline void put(const std::string& str) noexcept
{
  log::info("%s", str.c_str());
}

/// \copydoc put()
inline void put(const not_null<str> str) noexcept
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
}  // namespace cen

#endif  // CENTURION_LOG_HEADER
