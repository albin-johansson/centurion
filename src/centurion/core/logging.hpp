#ifndef CENTURION_CORE_LOGGING_HPP_
#define CENTURION_CORE_LOGGING_HPP_

#include <SDL.h>

#include <array>        // array
#include <cassert>      // assert
#include <chrono>       // zoned_time, current_zone, system_clock
#include <iostream>     // clog
#include <ostream>      // ostream
#include <string>       // string
#include <string_view>  // string_view
#include <utility>      // forward

#include "../common.hpp"
#include "../features.hpp"
#include "../version.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format_to_n

#endif  // CENTURION_HAS_FEATURE_FORMAT

#if CENTURION_SDL_VERSION_IS(2, 0, 10)

/* Workaround for this enum being completely anonymous in SDL 2.0.10 */
using SDL_LogCategory = decltype(SDL_LOG_CATEGORY_APPLICATION);

#endif  // CENTURION_SDL_VERSION_IS(2, 0, 10)

namespace cen {

/// \addtogroup core
/// \{

/// \brief Represents different logging priorities.
/// \since 3.0.0
enum class log_priority {
  verbose = SDL_LOG_PRIORITY_VERBOSE,
  debug = SDL_LOG_PRIORITY_DEBUG,
  info = SDL_LOG_PRIORITY_INFO,
  warn = SDL_LOG_PRIORITY_WARN,
  error = SDL_LOG_PRIORITY_ERROR,
  critical = SDL_LOG_PRIORITY_CRITICAL,
};

/// \brief Represents different logging categories.
/// \since 3.0.0
enum class log_category {
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

/**
 * \brief Returns the number of enumerators for the `log_category` enum.
 *
 * \return the number of enumerators.
 *
 * \since 6.3.0
 */
[[nodiscard]] constexpr auto log_category_count() noexcept -> int
{
  return 10;
}

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
 * \brief Returns a textual version of the supplied log category.
 *
 * \details This function returns a string that mirrors the name of the enumerator, e.g.
 * `to_string(log_category::app) == "app"`.
 *
 * \param category the enumerator that will be converted.
 *
 * \return a string that mirrors the name of the enumerator.
 *
 * \throws cen_error if the enumerator is not recognized.
 *
 * \since 6.2.0
 */
[[nodiscard]] constexpr auto to_string(const log_category category) -> std::string_view
{
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
      throw Error{"Did not recognize log category!"};
  }
}

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
      throw Error{"Did not recognize log priority!"};
  }
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of a log category enumerator.
 *
 * \param stream the output stream that will be used.
 * \param priority the enumerator that will be printed.
 *
 * \see `to_string(log_category)`
 *
 * \return the used stream.
 *
 * \since 6.2.0
 */
inline auto operator<<(std::ostream& stream, const log_category category) -> std::ostream&
{
  return stream << to_string(category);
}

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

/// \name Logging
/// \{

/// \brief Resets all of the logging priorities.
/// \since 7.0.0
inline void reset_log_priorities() noexcept
{
  SDL_LogResetPriorities();
}

/**
 * \brief Sets the priority used by all logging categories.
 *
 * \param priority the priority that will be used.
 *
 * \since 7.0.0
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
 *
 * \since 7.0.0
 */
inline void set_priority(const log_category category, const log_priority priority) noexcept
{
  SDL_LogSetPriority(ToUnderlying(category), static_cast<SDL_LogPriority>(priority));
}

/**
 * \brief Returns the priority of a specific log category.
 *
 * \param category the log category that will be queried.
 *
 * \return the associated log priority.
 *
 * \since 3.0.0
 */
[[nodiscard]] inline auto get_priority(const log_category category) noexcept -> log_priority
{
  return static_cast<log_priority>(SDL_LogGetPriority(ToUnderlying(category)));
}

/**
 * \brief Returns the largest amount of characters that a logged string can contain without
 * being truncated.
 *
 * \return the maximum amount of characters in a logged string.
 *
 * \since 7.0.0
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

inline void log_info_raw(const char* str) noexcept
{
  log_info("%s", str);
}

inline void log_info_raw(const std::string& str) noexcept
{
  log_info("%s", str.c_str());
}

#if CENTURION_HAS_FEATURE_CONCEPTS

template <is_stateless_callable<log_category, log_priority, const char*> Callable>
inline void set_output_function([[maybe_unused]] Callable callable) noexcept
{
  const auto wrapper = [](void* /*erased*/,
                          const int category,
                          const SDL_LogPriority priority,
                          const char* message) {
    Callable call;
    call(static_cast<log_category>(category), static_cast<log_priority>(priority), message);
  };

  SDL_LogSetOutputFunction(wrapper, nullptr);
}

template <typename UserData,
          is_stateless_callable<UserData*, log_category, log_priority, const char*> Callable>
inline void set_output_function([[maybe_unused]] Callable callable, UserData* data) noexcept
{
  const auto wrapper = [](void* erased,
                          const int category,
                          const SDL_LogPriority priority,
                          const char* message) {
    Callable tmp;
    tmp(static_cast<UserData*>(erased),
        static_cast<log_category>(category),
        static_cast<log_priority>(priority),
        message);
  };

  SDL_LogSetOutputFunction(wrapper, data);
}

#if CENTURION_HAS_FEATURE_FORMAT && CENTURION_HAS_FEATURE_CHRONO_TIME_ZONES

inline void use_preset_output_function() noexcept
{
  using std::chrono::current_zone;
  using std::chrono::system_clock;
  using std::chrono::zoned_time;

  set_output_function(
      [](const log_category, const log_priority priority, const char* message) {
        const zoned_time time{current_zone(), system_clock::now()};

        std::array<char, 512> buffer;  // NOLINT
        const auto result = std::format_to_n(buffer.data(),
                                             buffer.size() - 1,
                                             "LOG {:%T} [{}] > {}\n",
                                             time,
                                             to_string(priority),
                                             message);
        *result.out = '\0';

        std::clog << std::string_view{buffer.data(), result.out};
      });
}

#endif  // CENTURION_HAS_FEATURE_FORMAT && CENTURION_HAS_FEATURE_CHRONO_TIME_ZONES

#endif  // CENTURION_HAS_FEATURE_CONCEPTS

/// \} End of logging

/// \} End of core

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

#endif  // CENTURION_CORE_LOGGING_HPP_
