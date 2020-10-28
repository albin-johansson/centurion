/*
 * MIT License
 *
 * Copyright (c) 2019-2020 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef CENTURION_LOG_HEADER
#define CENTURION_LOG_HEADER

#include <SDL_log.h>

#include "centurion_api.hpp"
#include "detail/utils.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

/// \addtogroup misc
/// \{

/**
 * \namespace cen::log
 *
 * \brief Contains easy-to-use logging facilities.
 *
 * \details The usage of the logging API will be very familiar to most people
 * that have used the `printf` and/or the `SDL_Log` facilities.
 * \code{.cpp}
 *   czstring str = "bar";
 *   int i = 12;
 *   log::info("foo %s: %i", str, i); // logs the string "foo bar: 12"
 * \endcode
 * There are multiple priorities that can be used when logging. All
 * priorities have dedicated logging methods. All of these methods use
 * `category::app`.
 * \code{.cpp}
 *   log::info("General information message");
 *   log::warn("Warning that something is fishy!");
 *   log::debug("This might be useful for debugging");
 *   log::critical("Something has gone very wrong!");
 *   log::error("Information about an error!");
 * \endcode
 * You can also specify the category manually.
 * \code{.cpp}
 *   log::info(log::category::render, "Something about rendering...");
 * \endcode
 * Furthermore, if you really want to, you can manually specify the priority
 * and category with the `log::msg` function.
 * \code{.cpp}
 *   log::msg(log::priority::info, log::category::app, "Hello!");
 * \endcode
 *
 * \since 3.0.0
 *
 * \headerfile log.hpp
 */
namespace cen::log {

/**
 * \enum priority
 *
 * \brief Mirrors the `SDL_LogPriority` enum.
 *
 * \see `SDL_LogPriority`
 *
 * \since 3.0.0
 *
 * \headerfile log.hpp
 */
enum class priority
{
  info = SDL_LOG_PRIORITY_INFO,
  warn = SDL_LOG_PRIORITY_WARN,
  verbose = SDL_LOG_PRIORITY_VERBOSE,
  debug = SDL_LOG_PRIORITY_DEBUG,
  critical = SDL_LOG_PRIORITY_CRITICAL,
  error = SDL_LOG_PRIORITY_ERROR,
};

/**
 * \enum category
 *
 * \brief Mirrors the `SDL_LogCategory` enum.
 *
 * \see `SDL_LogCategory`
 *
 * \since 3.0.0
 *
 * \headerfile log.hpp
 */
enum class category
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

/**
 * \brief Logs a message with the specified priority and category.
 *
 * \details This method has no effect if the supplied string is null. Usage
 * of this method is quite bulky, so refer to the other logging methods for
 * casual logging.
 *
 * \tparam Args the types of the arguments that will be used in the
 * formatted string.
 *
 * \param priority the priority that will be used.
 * \param category the category that will be used.
 * \param fmt the formatted string that will be logged, cannot be null.
 * \param args the arguments that will be used by the formatted string.
 *
 * \since 4.0.0
 */
template <typename... Args>
void msg(log::priority priority,
         log::category category,
         nn_czstring fmt,
         Args&&... args) noexcept
{
  const auto sdlCategory = static_cast<SDL_LogCategory>(category);
  const auto prio = static_cast<SDL_LogPriority>(priority);
  SDL_LogMessage(sdlCategory, prio, fmt, args...);
}

/**
 * \brief Logs a message with `priority::info` and the specified category.
 *
 * \details This method has no effect if the supplied string is null.
 *
 * \tparam Args the types of the arguments that will be used in the
 * formatted string.
 *
 * \param category the category that will be used.
 * \param fmt the formatted string that will be logged, cannot be null.
 * \param args the arguments that will be used by the formatted string.
 *
 * \since 4.0.0
 */
template <typename... Args>
void info(category category, nn_czstring fmt, Args&&... args) noexcept
{
  log::msg(log::priority::info, category, fmt, args...);
}

/**
 * \brief Logs a message with `priority::info` and `category::app`.
 *
 * \details This method has no effect if the supplied string is null.
 *
 * \tparam Args the types of the arguments that will be used in the
 * formatted string.
 *
 * \param fmt the formatted string that will be logged, cannot be null.
 * \param args the arguments that will be used by the formatted string.
 *
 * \since 4.0.0
 */
template <typename... Args>
void info(nn_czstring fmt, Args&&... args) noexcept
{
  log::info(log::category::app, fmt, args...);
}

/**
 * \brief Logs a message with `priority::warn` and the specified category.
 *
 * \details This method has no effect if the supplied string is null.
 *
 * \tparam Args the types of the arguments that will be used in the
 * formatted string.
 *
 * \param category the category that will be used.
 * \param fmt the formatted string that will be logged, cannot be null.
 * \param args the arguments that will be used by the formatted string.
 *
 * \since 4.0.0
 */
template <typename... Args>
void warn(category category, nn_czstring fmt, Args&&... args) noexcept
{
  log::msg(priority::warn, category, fmt, args...);
}

/**
 * \brief Logs a message with `priority::warn` and `category::app`.
 *
 * \details This method has no effect if the supplied string is null.
 *
 * \tparam Args the types of the arguments that will be used in the
 * formatted string.
 *
 * \param fmt the formatted string that will be logged, cannot be null.
 * \param args the arguments that will be used by the formatted string.
 *
 * \since 4.0.0
 */
template <typename... Args>
void warn(nn_czstring fmt, Args&&... args) noexcept
{
  log::warn(category::app, fmt, args...);
}

/**
 * \brief Logs a message with `priority::verbose` and the specified category.
 *
 * \details This method has no effect if the supplied string is null.
 *
 * \tparam Args the types of the arguments that will be used in the
 * formatted string.
 *
 * \param category the category that will be used.
 * \param fmt the formatted string that will be logged, cannot be null.
 * \param args the arguments that will be used by the formatted string.
 *
 * \since 4.0.0
 */
template <typename... Args>
void verbose(category category, nn_czstring fmt, Args&&... args) noexcept
{
  log::msg(priority::verbose, category, fmt, args...);
}

/**
 * \brief Logs a message with `priority::verbose` and `category::app`.
 *
 * \details This method has no effect if the supplied string is null.
 *
 * \tparam Args the types of the arguments that will be used in the
 * formatted string.
 *
 * \param fmt the formatted string that will be logged, cannot be null.
 * \param args the arguments that will be used by the formatted string.
 *
 * \since 4.0.0
 */
template <typename... Args>
void verbose(nn_czstring fmt, Args&&... args) noexcept
{
  log::verbose(category::app, fmt, args...);
}

/**
 * \brief Logs a message with `priority::debug` and the specified category.
 *
 * \details This method has no effect if the supplied string is null.
 *
 * \tparam Args the types of the arguments that will be used in the
 * formatted string.
 *
 * \param category the category that will be used.
 * \param fmt the formatted string that will be logged, cannot be null.
 * \param args the arguments that will be used by the formatted string.
 *
 * \since 4.0.0
 */
template <typename... Args>
void debug(category category, nn_czstring fmt, Args&&... args) noexcept
{
  log::msg(priority::debug, category, fmt, args...);
}

/**
 * \brief Logs a message with `priority::debug` and `category::app`.
 *
 * \details This method has no effect if the supplied string is null.
 *
 * \tparam Args the types of the arguments that will be used in the
 * formatted string.
 *
 * \param fmt the formatted string that will be logged, cannot be null.
 * \param args the arguments that will be used by the formatted string.
 *
 * \since 4.0.0
 */
template <typename... Args>
void debug(nn_czstring fmt, Args&&... args) noexcept
{
  log::debug(category::app, fmt, args...);
}

/**
 * \brief Logs a message with `priority::critical` and the specified category.
 *
 * \details This method has no effect if the supplied string is null.
 *
 * \tparam Args the types of the arguments that will be used in the
 * formatted string.
 *
 * \param category the category that will be used.
 * \param fmt the formatted string that will be logged, cannot be null.
 * \param args the arguments that will be used by the formatted string.
 *
 * \since 4.0.0
 */
template <typename... Args>
void critical(category category, czstring fmt, Args&&... args) noexcept
{
  log::msg(priority::critical, category, fmt, args...);
}

/**
 * \brief Logs a message with `priority::critical` and `category::app` .
 *
 * \details This method has no effect if the supplied string is null.
 *
 * \tparam Args the types of the arguments that will be used in the
 * formatted string.
 *
 * \param fmt the formatted string that will be logged, cannot be null.
 * \param args the arguments that will be used by the formatted string.
 *
 * \since 4.0.0
 */
template <typename... Args>
void critical(nn_czstring fmt, Args&&... args) noexcept
{
  log::critical(category::app, fmt, args...);
}

/**
 * \brief Logs a message with `priority::error` and the specified category.
 *
 * \details This method has no effect if the supplied string is null.
 *
 * \tparam Args the types of the arguments that will be used in the
 * formatted string.
 *
 * \param category the category that will be used.
 * \param fmt the formatted string that will be logged, cannot be null.
 * \param args the arguments that will be used by the formatted string.
 *
 * \since 4.0.0
 */
template <typename... Args>
void error(category category, czstring fmt, Args&&... args) noexcept
{
  log::msg(priority::error, category, fmt, args...);
}

/**
 * \brief Logs a message with the `priority::error` and `category::app`.
 *
 * \tparam Args the types of the arguments that will be used in the
 * formatted string.
 *
 * \param fmt the formatted string that will be logged, cannot be null.
 * \param args the arguments that will be used by the formatted string.
 *
 * \since 4.0.0
 */
template <typename... Args>
void error(nn_czstring fmt, Args&&... args) noexcept
{
  log::error(category::app, fmt, args...);
}

/**
 * \brief Logs a string.
 *
 * \details This function is meant to be used for casual logging, where you
 * just want to log a string. The message will be logged with
 * `priority::info` and `category::app`.
 *
 * \param str the string that will be logged.
 *
 * \since 5.0.0
 */
inline void put(const std::string& str) noexcept
{
  log::info("%s", str.c_str());
}

/**
 * \copydoc put(const std::string&)
 */
inline void put(nn_czstring str) noexcept
{
  log::info("%s", str);
}

/**
 * \brief Resets all of the logging priorities.
 *
 * \since 3.0.0
 */
CENTURION_API
void reset_priorities() noexcept;

/**
 * \brief Sets the priority of all categories.
 *
 * \param prio the priority that will be used.
 *
 * \since 3.0.0
 */
CENTURION_API
void set_priority(priority prio) noexcept;

/**
 * \brief Sets the priority of the specified category.
 *
 * \param category the category that will have its priority changed.
 * \param prio the new priority value.
 *
 * \since 3.0.0
 */
CENTURION_API
void set_priority(category category, priority prio) noexcept;

/**
 * \brief Returns the priority of the specified category.
 *
 * \param category the category to return the priority of.
 * \return the priority of the specified category.
 *
 * \since 3.0.0
 */
CENTURION_QUERY
auto get_priority(category category) noexcept -> log::priority;

/**
 * \brief Returns the maximum size, i.e the maximum amount of characters that
 * a string can contain and successfully be logged without being truncated.
 *
 * \note Strings longer that this value will be truncated.
 *
 * \return the maximum amount of characters that a loggable string can
 * contain.
 *
 * \see `SDL_MAX_LOG_MESSAGE`
 *
 * \since 4.0.0
 */
[[nodiscard]] constexpr auto max_message_size() noexcept -> int
{
  return SDL_MAX_LOG_MESSAGE;
}

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
[[nodiscard]] inline constexpr auto operator==(priority lhs,
                                               SDL_LogPriority rhs) noexcept
    -> bool
{
  return static_cast<SDL_LogPriority>(lhs) == rhs;
}

/**
 * \copydoc operator==(priority, SDL_LogPriority)
 */
[[nodiscard]] inline constexpr auto operator==(SDL_LogPriority lhs,
                                               priority rhs) noexcept -> bool
{
  return rhs == lhs;
}

/**
 * \brief Indicates whether or not the two log priorities values aren't the
 * same.
 *
 * \param lhs the left-hand side log priority value.
 * \param rhs the right-hand side log priority value.
 *
 * \return `true` if the priorities aren't the same; `false` otherwise.
 *
 * \since 3.0.0
 */
[[nodiscard]] inline constexpr auto operator!=(priority lhs,
                                               SDL_LogPriority rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/**
 * \copydoc operator!=(priority, SDL_LogPriority)
 */
[[nodiscard]] inline constexpr auto operator!=(SDL_LogPriority lhs,
                                               priority rhs) noexcept -> bool
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
[[nodiscard]] inline constexpr auto operator==(category lhs,
                                               SDL_LogCategory rhs) noexcept
    -> bool
{
  return static_cast<SDL_LogCategory>(lhs) == rhs;
}

/**
 * \copydoc operator==(category, SDL_LogCategory)
 */
[[nodiscard]] inline constexpr auto operator==(SDL_LogCategory lhs,
                                               category rhs) noexcept -> bool
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
[[nodiscard]] inline constexpr auto operator!=(category lhs,
                                               SDL_LogCategory rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/**
 * \copydoc operator!=(category, SDL_LogCategory)
 */
[[nodiscard]] inline constexpr auto operator!=(SDL_LogCategory lhs,
                                               category rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

}  // namespace cen::log

#ifdef CENTURION_USE_DEBUG_LOGGING_MACROS

#ifdef NDEBUG

/**
 * \def CENTURION_LOG_INFO
 */
#define CENTURION_LOG_INFO(fmt, ...)

/**
 * \def CENTURION_LOG_WARN
 */
#define CENTURION_LOG_WARN(fmt, ...)

/**
 * \def CENTURION_LOG_VERBOSE
 */
#define CENTURION_LOG_VERBOSE(fmt, ...)

/**
 * \def CENTURION_LOG_DEBUG
 */
#define CENTURION_LOG_DEBUG(fmt, ...)

/**
 * \def CENTURION_LOG_CRITICAL
 */
#define CENTURION_LOG_CRITICAL(fmt, ...)

/**
 * \def CENTURION_LOG_ERROR
 */
#define CENTURION_LOG_ERROR(fmt, ...)

#else

/**
 * \def CENTURION_LOG_INFO
 */
#define CENTURION_LOG_INFO(fmt, ...) cen::log::info(fmt, __VA_ARGS__)

/**
 * \def CENTURION_LOG_WARN
 */
#define CENTURION_LOG_WARN(fmt, ...) cen::log::warn(fmt, __VA_ARGS__)

/**
 * \def CENTURION_LOG_VERBOSE
 */
#define CENTURION_LOG_VERBOSE(fmt, ...) cen::log::verbose(fmt, __VA_ARGS__)

/**
 * \def CENTURION_LOG_DEBUG
 */
#define CENTURION_LOG_DEBUG(fmt, ...) cen::log::debug(fmt, __VA_ARGS__)

/**
 * \def CENTURION_LOG_CRITICAL
 */
#define CENTURION_LOG_CRITICAL(fmt, ...) cen::log::critical(fmt, __VA_ARGS__)

/**
 * \def CENTURION_LOG_ERROR
 */
#define CENTURION_LOG_ERROR(fmt, ...) cen::log::error(fmt, __VA_ARGS__)

#endif  // NDEBUG

#endif  // CENTURION_USE_DEBUG_LOGGING_MACROS

/**
 * \def CENTURION_LOG_INFO
 *
 * \brief A debug-only macro that expands to `cen::log::info`.
 *
 * \since 5.0.0
 */

/**
 * \def CENTURION_LOG_WARN
 *
 * \brief A debug-only macro that expands to `cen::log::warn`.
 *
 * \since 5.0.0
 */

/**
 * \def CENTURION_LOG_VERBOSE
 *
 * \brief A debug-only macro that expands to `cen::log::verbose`.
 *
 * \since 5.0.0
 */

/**
 * \def CENTURION_LOG_DEBUG
 *
 * \brief A debug-only macro that expands to `cen::log::debug`.
 *
 * \since 5.0.0
 */

/**
 * \def CENTURION_LOG_CRITICAL
 *
 * \brief A debug-only macro that expands to `cen::log::critical`.
 *
 * \since 5.0.0
 */

/**
 * \def CENTURION_LOG_ERROR
 *
 * \brief A debug-only macro that expands to `cen::log::error`.
 *
 * \since 5.0.0
 */

/// \}

#endif  // CENTURION_LOG_HEADER
