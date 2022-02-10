#ifndef CENTURION_LOGGING_HPP_
#define CENTURION_LOGGING_HPP_

#include <SDL.h>

#include <cassert>      // assert
#include <ostream>      // ostream
#include <string>       // string
#include <string_view>  // string_view
#include <utility>      // forward

#include "common.hpp"
#include "features.hpp"
#include "version.hpp"

#if CENTURION_SDL_VERSION_IS(2, 0, 10)

/* Workaround for this enum being completely anonymous in SDL 2.0.10 */
using SDL_LogCategory = decltype(SDL_LOG_CATEGORY_APPLICATION);

#endif  // CENTURION_SDL_VERSION_IS(2, 0, 10)

namespace cen {

/**
 * \ingroup common
 * \defgroup logging Logging
 *
 * \brief Provides logging utilities.
 */

/// \addtogroup logging
/// \{

/**
 * \brief Represents different logging priorities.
 *
 * \see `SDL_LogPriority`
 */
enum class log_priority
{
  verbose = SDL_LOG_PRIORITY_VERBOSE,
  debug = SDL_LOG_PRIORITY_DEBUG,
  info = SDL_LOG_PRIORITY_INFO,
  warn = SDL_LOG_PRIORITY_WARN,
  error = SDL_LOG_PRIORITY_ERROR,
  critical = SDL_LOG_PRIORITY_CRITICAL,
};

/// \name Log priority functions
/// \{

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
      throw exception{"Did not recognize log priority!"};
  }
}

inline auto operator<<(std::ostream& stream, const log_priority priority) -> std::ostream&
{
  return stream << to_string(priority);
}

/// \} End of log priority functions

/**
 * \brief Represents different logging categories.
 *
 * \see `SDL_LogCategory`
 */
enum class log_category
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
  custom = SDL_LOG_CATEGORY_CUSTOM
};

/// \name Log category functions
/// \{

[[nodiscard]] constexpr auto is_custom(const log_category category) noexcept -> bool
{
  return to_underlying(category) >= SDL_LOG_CATEGORY_CUSTOM;
}

[[nodiscard]] constexpr auto to_string(const log_category category) -> std::string_view
{
  if (is_custom(category)) {
    return "custom";
  }

  switch (category) {
    case log_category::app:
      return "app";

    case log_category::error:
      return "error";

    case log_category::assert:
      return "assert";

    case log_category::system:
      return "system";

    case log_category::audio:
      return "audio";

    case log_category::video:
      return "video";

    case log_category::render:
      return "render";

    case log_category::input:
      return "input";

    case log_category::test:
      return "test";

    case log_category::custom:
      return "custom";

    default:
      throw exception{"Did not recognize log category!"};
  }
}

inline auto operator<<(std::ostream& stream, const log_category category) -> std::ostream&
{
  return stream << to_string(category);
}

/// \} End of log category functions

/// \name Log functions
/// \{

/**
 * \brief Resets all of the logging priorities.
 */
inline void reset_log_priorities() noexcept
{
  SDL_LogResetPriorities();
}

/**
 * \brief Sets the priority used by all logging categories.
 *
 * \param priority the priority that will be used.
 */
inline void set_priority(const log_priority priority) noexcept
{
  const auto value = static_cast<SDL_LogPriority>(priority);
  SDL_LogSetAllPriority(value);
  SDL_LogSetPriority(SDL_LOG_CATEGORY_TEST, value); /* Apparently not set by SDL */
}

/**
 * \brief Sets the priority used by a specific category.
 *
 * \param category the category that will be affected.
 * \param priority the new priority.
 */
inline void set_priority(const log_category category, const log_priority priority) noexcept
{
  SDL_LogSetPriority(to_underlying(category), static_cast<SDL_LogPriority>(priority));
}

/**
 * \brief Returns the priority of a specific log category.
 *
 * \param category the log category that will be queried.
 *
 * \return the log priority.
 */
[[nodiscard]] inline auto get_priority(const log_category category) noexcept -> log_priority
{
  return static_cast<log_priority>(SDL_LogGetPriority(to_underlying(category)));
}

/**
 * \brief Returns the most characters a logged string may contain without being truncated.
 *
 * \return the maximum amount of characters in a logged string.
 */
[[nodiscard]] constexpr auto max_log_message_size() noexcept -> int
{
  return SDL_MAX_LOG_MESSAGE;
}

template <typename... Args>
void log(const log_priority priority,
         const log_category category,
         const char* fmt,
         Args&&... args) noexcept
{
  assert(fmt);
  SDL_LogMessage(static_cast<SDL_LogCategory>(category),
                 static_cast<SDL_LogPriority>(priority),
                 fmt,
                 std::forward<Args>(args)...);
}

template <typename... Args>
void log_verbose(const log_category category, const char* fmt, Args&&... args) noexcept
{
  log(log_priority::verbose, category, fmt, std::forward<Args>(args)...);
}

template <typename... Args>
void log_verbose(const char* fmt, Args&&... args) noexcept
{
  log_verbose(log_category::app, fmt, std::forward<Args>(args)...);
}

template <typename... Args>
void log_debug(const log_category category, const char* fmt, Args&&... args) noexcept
{
  log(log_priority::debug, category, fmt, std::forward<Args>(args)...);
}

template <typename... Args>
void log_debug(const char* fmt, Args&&... args) noexcept
{
  log_debug(log_category::app, fmt, std::forward<Args>(args)...);
}

template <typename... Args>
void log_info(const log_category category, const char* fmt, Args&&... args) noexcept
{
  log(log_priority::info, category, fmt, std::forward<Args>(args)...);
}

template <typename... Args>
void log_info(const char* fmt, Args&&... args) noexcept
{
  log_info(log_category::app, fmt, std::forward<Args>(args)...);
}

template <typename... Args>
void log_warn(const log_category category, const char* fmt, Args&&... args) noexcept
{
  log(log_priority::warn, category, fmt, std::forward<Args>(args)...);
}

template <typename... Args>
void log_warn(const char* fmt, Args&&... args) noexcept
{
  log_warn(log_category::app, fmt, std::forward<Args>(args)...);
}

template <typename... Args>
void log_error(const log_category category, const char* fmt, Args&&... args) noexcept
{
  log(log_priority::error, category, fmt, std::forward<Args>(args)...);
}

template <typename... Args>
void log_error(const char* fmt, Args&&... args) noexcept
{
  log_error(log_category::app, fmt, std::forward<Args>(args)...);
}

template <typename... Args>
void log_critical(const log_category category, const char* fmt, Args&&... args) noexcept
{
  log(log_priority::critical, category, fmt, std::forward<Args>(args)...);
}

template <typename... Args>
void log_critical(const char* fmt, Args&&... args) noexcept
{
  log_critical(log_category::app, fmt, std::forward<Args>(args)...);
}

/// \} End of log functions

/// \} End of group logging

}  // namespace cen

#ifndef CENTURION_NO_DEBUG_LOG_MACROS
#ifdef NDEBUG

#define CENTURION_LOG_INFO(fmt, ...)
#define CENTURION_LOG_WARN(fmt, ...)
#define CENTURION_LOG_VERBOSE(fmt, ...)
#define CENTURION_LOG_DEBUG(fmt, ...)
#define CENTURION_LOG_CRITICAL(fmt, ...)
#define CENTURION_LOG_ERROR(fmt, ...)

#else

#if CENTURION_HAS_FEATURE_CPP20

#define CENTURION_LOG_INFO(fmt, ...) cen::log_info(fmt __VA_OPT__(, ) __VA_ARGS__)
#define CENTURION_LOG_WARN(fmt, ...) cen::log_warn(fmt __VA_OPT__(, ) __VA_ARGS__)
#define CENTURION_LOG_VERBOSE(fmt, ...) cen::log_verbose(fmt __VA_OPT__(, ) __VA_ARGS__)
#define CENTURION_LOG_DEBUG(fmt, ...) cen::log_debug(fmt __VA_OPT__(, ) __VA_ARGS__)
#define CENTURION_LOG_CRITICAL(fmt, ...) cen::log_critical(fmt __VA_OPT__(, ) __VA_ARGS__)
#define CENTURION_LOG_ERROR(fmt, ...) cen::log_error(fmt __VA_OPT__(, ) __VA_ARGS__)

#else

#define CENTURION_LOG_INFO(fmt, ...) cen::log_info(fmt, __VA_ARGS__)
#define CENTURION_LOG_WARN(fmt, ...) cen::log_warn(fmt, __VA_ARGS__)
#define CENTURION_LOG_VERBOSE(fmt, ...) cen::log_verbose(fmt, __VA_ARGS__)
#define CENTURION_LOG_DEBUG(fmt, ...) cen::log_debug(fmt, __VA_ARGS__)
#define CENTURION_LOG_CRITICAL(fmt, ...) cen::log_critical(fmt, __VA_ARGS__)
#define CENTURION_LOG_ERROR(fmt, ...) cen::log_error(fmt, __VA_ARGS__)

#endif  // CENTURION_HAS_FEATURE_CPP20

#endif  // NDEBUG
#endif  // CENTURION_NO_DEBUG_LOG_MACROS

#endif  // CENTURION_LOGGING_HPP_
