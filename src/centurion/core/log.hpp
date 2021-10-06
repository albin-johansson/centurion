#ifndef CENTURION_LOG_HEADER
#define CENTURION_LOG_HEADER

#include <SDL.h>

#include <array>        // array
#include <cassert>      // assert
#include <chrono>       // zoned_time, current_zone, system_clock
#include <iostream>     // clog
#include <string>       // string
#include <string_view>  // string_view
#include <utility>      // forward

#include "../compiler/features.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format_to_n

#endif  // CENTURION_HAS_FEATURE_FORMAT

#include "is_stateless_callable.hpp"
#include "log_category.hpp"
#include "log_priority.hpp"
#include "not_null.hpp"
#include "str.hpp"
#include "to_underlying.hpp"

/// \namespace cen::log
/// \brief Contains easy-to-use logging facilities.
/// \ingroup core
/// \since 3.0.0
namespace cen::log {

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
void verbose(const log_category category, const not_null<str> fmt, Args&&... args) noexcept
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
void critical(const log_category category, const not_null<str> fmt, Args&&... args) noexcept
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
inline void set_priority(const log_category category, const log_priority priority) noexcept
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
[[nodiscard]] inline auto get_priority(const log_category category) noexcept -> log_priority
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

#if CENTURION_HAS_FEATURE_CONCEPTS

/**
 * \brief Sets the logging output function that will be used.
 *
 * \tparam Callable the type of the function object.
 *
 * \param callable the function object that will be used as the new logging output
 * function.
 *
 * \see `use_preset_output_function()`
 *
 * \since 6.2.0
 */
template <is_stateless_callable<log_category, log_priority, str> Callable>
inline void set_output_function([[maybe_unused]] Callable callable) noexcept
{
  const auto wrapper = [](void* /*erased*/,
                          const int category,
                          const SDL_LogPriority priority,
                          const str message) {
    Callable tmp;
    tmp(static_cast<log_category>(category), static_cast<log_priority>(priority), message);
  };

  SDL_LogSetOutputFunction(wrapper, nullptr);
}

/**
 * \brief Sets the logging output function that will be used.
 *
 * \tparam UserData the type of the user data.
 * \tparam Callable the type of the function object.
 *
 * \param callable the function object that will be used as the new logging output
 * function.
 * \param data a pointer to the user data, can safely be null. However, see the other
 * overload of this function if you do not need the user data.
 *
 * \see `use_preset_output_function()`
 *
 * \since 6.2.0
 */
template <typename UserData,
          is_stateless_callable<UserData*, log_category, log_priority, str> Callable>
inline void set_output_function([[maybe_unused]] Callable callable, UserData* data) noexcept
{
  const auto wrapper =
      [](void* erased, const int category, const SDL_LogPriority priority, const str message) {
        Callable tmp;
        tmp(static_cast<UserData*>(erased),
            static_cast<log_category>(category),
            static_cast<log_priority>(priority),
            message);
      };

  SDL_LogSetOutputFunction(wrapper, data);
}

#if CENTURION_HAS_FEATURE_FORMAT && CENTURION_HAS_FEATURE_CHRONO_TIME_ZONES

/**
 * \brief Sets the logging output function to a convenient preset.
 *
 * \details Calling this function will make the logging output be channeled through
 * `std::clog`, and use an output format that includes the current time (taking the
 * current time zone into account) and the log priority associated with each message.
 *
 * \see `set_output_function()`
 *
 * \since 6.2.0
 */
inline void use_preset_output_function() noexcept
{
  using std::chrono::current_zone;
  using std::chrono::system_clock;
  using std::chrono::zoned_time;

  set_output_function([](const log_category, const log_priority priority, const str message) {
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

/// \} End of group core

}  // namespace cen::log

#endif  // CENTURION_LOG_HEADER
