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

#include "centurion_api.h"
#include "centurion_utils.h"

namespace centurion {

/**
 * The Log class provides easy-to-use logging facilities.
 *
 * @since 3.0.0
 */
class Log final {
 public:
  Log() = delete;
  Log(const Log&) = delete;
  Log(Log&&) = delete;
  Log& operator=(const Log&) = delete;
  Log& operator=(Log&&) = delete;

  /**
   * The Priority enum provides values the mirror those of SDL_LogPriority.
   *
   * @see SDL_LogPriority
   * @since 3.0.0
   */
  enum class Priority {
    Info = SDL_LOG_PRIORITY_INFO,
    Warn = SDL_LOG_PRIORITY_WARN,
    Verbose = SDL_LOG_PRIORITY_VERBOSE,
    Debug = SDL_LOG_PRIORITY_DEBUG,
    Critical = SDL_LOG_PRIORITY_CRITICAL,
    Error = SDL_LOG_PRIORITY_ERROR,
  };

  /**
   * The Category enum provides values the mirror those of SDL_LogCategory.
   *
   * @see SDL_LogCategory
   * @since 3.0.0
   */
  enum class Category {
    App = SDL_LOG_CATEGORY_APPLICATION,
    Error = SDL_LOG_CATEGORY_ERROR,
    Assert = SDL_LOG_CATEGORY_ASSERT,
    System = SDL_LOG_CATEGORY_SYSTEM,
    Audio = SDL_LOG_CATEGORY_AUDIO,
    Video = SDL_LOG_CATEGORY_VIDEO,
    Render = SDL_LOG_CATEGORY_RENDER,
    Input = SDL_LOG_CATEGORY_INPUT,
    Test = SDL_LOG_CATEGORY_TEST,
    Misc = SDL_LOG_CATEGORY_CUSTOM
  };

  /**
   * Logs a message with the specified priority and category. This method has no
   * effect if the supplied string is null. Usage of this method is quite
   * bulky, so refer to the other logging methods for casual logging.
   *
   * @tparam Args the types of the arguments that will be used in the
   * formatted string.
   * @param priority the priority that will be used.
   * @param category the category that will be used.
   * @param fmt the formatted string that will be logged, can safely be null.
   * @param args the arguments that will be used by the formatted string.
   * @since 4.0.0
   */
  template <typename... Args>
  static void log(Priority priority,
                  Category category,
                  CZString fmt,
                  Args... args) noexcept
  {
    if (fmt) {
      const auto sdlCategory = static_cast<SDL_LogCategory>(category);
      const auto prio = static_cast<SDL_LogPriority>(priority);
      SDL_LogMessage(sdlCategory, prio, fmt, args...);
    }
  }

  /**
   * Logs a message with the <code>Info</code> priority and <code>App</code>
   * category. This method has no effect if the supplied string is null.
   *
   * @tparam Args the types of the arguments that will be used in the
   * formatted string.
   * @param fmt the formatted string that will be logged, can safely be null.
   * @param args the arguments that will be used by the formatted string.
   * @since 4.0.0
   */
  template <typename... Args>
  static void info(CZString fmt, Args... args) noexcept
  {
    Log::info(Category::App, fmt, args...);
  }

  /**
   * Logs a message with the <code>Info</code> priority and the specified
   * category. This method has no effect if the supplied string is null.
   *
   * @tparam Args the types of the arguments that will be used in the
   * formatted string.
   * @param category the category that will be used.
   * @param fmt the formatted string that will be logged, can safely be null.
   * @param args the arguments that will be used by the formatted string.
   * @since 4.0.0
   */
  template <typename... Args>
  static void info(Category category, CZString fmt, Args... args) noexcept
  {
    Log::log(Priority::Info, category, fmt, args...);
  }

  /**
   * Logs a message with the <code>Warn</code> priority and <code>App</code>
   * category. This method has no effect if the supplied string is null.
   *
   * @tparam Args the types of the arguments that will be used in the
   * formatted string.
   * @param fmt the formatted string that will be logged, can safely be null.
   * @param args the arguments that will be used by the formatted string.
   * @since 4.0.0
   */
  template <typename... Args>
  static void warn(CZString fmt, Args... args) noexcept
  {
    Log::warn(Category::App, fmt, args...);
  }

  /**
   * Logs a message with the <code>Warn</code> priority and the specified
   * category. This method has no effect if the supplied string is null.
   *
   * @tparam Args the types of the arguments that will be used in the
   * formatted string.
   * @param category the category that will be used.
   * @param fmt the formatted string that will be logged, can safely be null.
   * @param args the arguments that will be used by the formatted string.
   * @since 4.0.0
   */
  template <typename... Args>
  static void warn(Category category, CZString fmt, Args... args) noexcept
  {
    Log::log(Priority::Warn, category, fmt, args...);
  }

  /**
   * Logs a message with the <code>Verbose</code> priority and <code>App</code>
   * category. This method has no effect if the supplied string is null.
   *
   * @tparam Args the types of the arguments that will be used in the
   * formatted string.
   * @param fmt the formatted string that will be logged, can safely be null.
   * @param args the arguments that will be used by the formatted string.
   * @since 4.0.0
   */
  template <typename... Args>
  static void verbose(CZString fmt, Args... args) noexcept
  {
    Log::verbose(Category::App, fmt, args...);
  }

  /**
   * Logs a message with the <code>Verbose</code> priority and the specified
   * category. This method has no effect if the supplied string is null.
   *
   * @tparam Args the types of the arguments that will be used in the
   * formatted string.
   * @param category the category that will be used.
   * @param fmt the formatted string that will be logged, can safely be null.
   * @param args the arguments that will be used by the formatted string.
   * @since 4.0.0
   */
  template <typename... Args>
  static void verbose(Category category, CZString fmt, Args... args) noexcept
  {
    Log::log(Priority::Verbose, category, fmt, args...);
  }

  /**
   * Logs a message with the <code>Debug</code> priority and <code>App</code>
   * category. This method has no effect if the supplied string is null.
   *
   * @tparam Args the types of the arguments that will be used in the
   * formatted string.
   * @param fmt the formatted string that will be logged, can safely be null.
   * @param args the arguments that will be used by the formatted string.
   * @since 4.0.0
   */
  template <typename... Args>
  static void debug(CZString fmt, Args... args) noexcept
  {
    Log::debug(Category::App, fmt, args...);
  }

  /**
   * Logs a message with the <code>Debug</code> priority and the specified
   * category. This method has no effect if the supplied string is null.
   *
   * @tparam Args the types of the arguments that will be used in the
   * formatted string.
   * @param category the category that will be used.
   * @param fmt the formatted string that will be logged, can safely be null.
   * @param args the arguments that will be used by the formatted string.
   * @since 4.0.0
   */
  template <typename... Args>
  static void debug(Category category, CZString fmt, Args... args) noexcept
  {
    Log::log(Priority::Debug, category, fmt, args...);
  }

  /**
   * Logs a message with the <code>Critical</code> priority and <code>App</code>
   * category. This method has no effect if the supplied string is null.
   *
   * @tparam Args the types of the arguments that will be used in the
   * formatted string.
   * @param fmt the formatted string that will be logged, can safely be null.
   * @param args the arguments that will be used by the formatted string.
   * @since 4.0.0
   */
  template <typename... Args>
  static void critical(CZString fmt, Args... args) noexcept
  {
    Log::critical(Category::App, fmt, args...);
  }

  /**
   * Logs a message with the <code>Critical</code> priority and the specified
   * category. This method has no effect if the supplied string is null.
   *
   * @tparam Args the types of the arguments that will be used in the
   * formatted string.
   * @param category the category that will be used.
   * @param fmt the formatted string that will be logged, can safely be null.
   * @param args the arguments that will be used by the formatted string.
   * @since 4.0.0
   */
  template <typename... Args>
  static void critical(Category category, CZString fmt, Args... args) noexcept
  {
    Log::log(Priority::Critical, category, fmt, args...);
  }

  /**
   * Logs a message with the <code>Error</code> priority and <code>App</code>
   * category. This method has no effect if the supplied string is null.
   *
   * @tparam Args the types of the arguments that will be used in the
   * formatted string.
   * @param fmt the formatted string that will be logged, can safely be null.
   * @param args the arguments that will be used by the formatted string.
   * @since 4.0.0
   */
  template <typename... Args>
  static void error(CZString fmt, Args... args) noexcept
  {
    Log::error(Category::App, fmt, args...);
  }

  /**
   * Logs a message with the <code>Error</code> priority and the specified
   * category. This method has no effect if the supplied string is null.
   *
   * @tparam Args the types of the arguments that will be used in the
   * formatted string.
   * @param category the category that will be used.
   * @param fmt the formatted string that will be logged, can safely be null.
   * @param args the arguments that will be used by the formatted string.
   * @since 4.0.0
   */
  template <typename... Args>
  static void error(Category category, CZString fmt, Args... args) noexcept
  {
    Log::log(Priority::Error, category, fmt, args...);
  }

  /**
   * Resets all of the logging priorities.
   *
   * @since 3.0.0
   */
  CENTURION_API static void reset_priorities() noexcept;

  /**
   * Sets the priority of all categories.
   *
   * @param prio the priority that will be used.
   * @since 3.0.0
   */
  CENTURION_API static void set_priority(Priority prio) noexcept;

  /**
   * Sets the priority of the specified category.
   *
   * @param category the category that will have its priority changed.
   * @param prio the new priority value.
   * @since 3.0.0
   */
  CENTURION_API static void set_priority(Category category,
                                         Priority prio) noexcept;

  /**
   * Returns the priority of the specified category.
   *
   * @param category the category to return the priority of.
   * @return the priority of the specified category.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static Priority priority(Category category) noexcept;

  /**
   * Returns the maximum size, i.e the maximum amount of characters that a
   * string can contain and successfully be logged without being truncated.
   *
   * @return the maximum amount of characters that a loggable string can
   * contain. Strings longer that this value will be truncated.
   * @since 4.0.0
   * @see SDL_MAX_LOG_MESSAGE
   */
  CENTURION_NODISCARD
  constexpr static int max_message_size() noexcept
  {
    return SDL_MAX_LOG_MESSAGE;
  }
};

#ifdef CENTURION_HAS_IS_FINAL_TYPE_TRAIT
static_assert(std::is_final<Log>::value, "Log isn't final!");
#endif

static_assert(!std::is_constructible<Log>::value, "Log is constructible!");

static_assert(!std::is_copy_constructible<Log>::value,
              "Log is copy constructible!");

static_assert(!std::is_move_constructible<Log>::value,
              "Log is move constructible!");

static_assert(!std::is_copy_assignable<Log>::value, "Log is copy assignable!");

static_assert(!std::is_move_assignable<Log>::value, "Log is move assignable!");

/**
 * Indicates whether or not the two log priorities represent the same priority.
 *
 * @param lhs the left-hand side Centurion priority.
 * @param rhs the right-hand side SDL priority.
 * @return true if the priorities are the same; false otherwise.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator==(Log::Priority lhs, SDL_LogPriority rhs) noexcept;

/**
 * Indicates whether or not the two log priorities represent the same priority.
 *
 * @param lhs the left-hand side SDL priority.
 * @param rhs the right-hand side Centurion priority.
 * @return true if the priorities are the same; false otherwise.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator==(SDL_LogPriority lhs, Log::Priority rhs) noexcept;

/**
 * Indicates whether or not the two log priorities don't represent the same
 * priority.
 *
 * @param lhs the left-hand side Centurion priority.
 * @param rhs the right-hand side SDL priority.
 * @return true if the priorities aren't the same; false otherwise.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator!=(Log::Priority lhs, SDL_LogPriority rhs) noexcept;

/**
 * Indicates whether or not the two log priorities don't represent the same
 * priority.
 *
 * @param lhs the left-hand side SDL priority.
 * @param rhs the right-hand side Centurion priority.
 * @return true if the priorities aren't the same; false otherwise.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator!=(SDL_LogPriority lhs, Log::Priority rhs) noexcept;

/**
 * Indicates whether or not the two log categories represent the same value.
 *
 * @param lhs the left-hand side Centurion category.
 * @param rhs the right-hand side SDL category.
 * @return true if the categories are the same; false otherwise.
 * @since 4.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator==(Log::Category lhs, SDL_LogCategory rhs) noexcept;

/**
 * Indicates whether or not the two log categories represent the same value.
 *
 * @param lhs the left-hand side SDL category.
 * @param rhs the right-hand side Centurion category.
 * @return true if the priorities are the same; false otherwise.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator==(SDL_LogCategory lhs, Log::Category rhs) noexcept;

/**
 * Indicates whether or not the two log priorities don't represent the same
 * priority.
 *
 * @param lhs the left-hand side Centurion priority.
 * @param rhs the right-hand side SDL priority.
 * @return true if the priorities aren't the same; false otherwise.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator!=(Log::Category lhs, SDL_LogCategory rhs) noexcept;

/**
 * Indicates whether or not the two log priorities don't represent the same
 * priority.
 *
 * @param lhs the left-hand side SDL priority.
 * @param rhs the right-hand side Centurion priority.
 * @return true if the priorities aren't the same; false otherwise.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator!=(SDL_LogCategory lhs, Log::Category rhs) noexcept;

}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "log.cpp"
#endif

#endif  // CENTURION_LOG_HEADER
