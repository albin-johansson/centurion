/*
 * MIT License
 *
 * Copyright (c) 2019 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once
#include <SDL_log.h>
#include "centurion_api.h"

namespace centurion {

/**
 * The Priority enum provides values the mirror those of SDL_LogPriority.
 *
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
 * Indicates whether or not the two log priorities represent the same priority.
 *
 * @param a the lhs Centurion priority.
 * @param b the rhs SDL priority.
 * @return true if the priorities are the same; false otherwise.
 * @since 3.0.0
 */
[[nodiscard]]
inline bool operator==(Priority a, SDL_LogPriority b) noexcept {
  return static_cast<SDL_LogPriority>(a) == b;
}

/**
 * Indicates whether or not the two log priorities represent the same priority.
 *
 * @param a the lhs SDL priority.
 * @param b the rhs Centurion priority.
 * @return true if the priorities are the same; false otherwise.
 * @since 3.0.0
 */
[[nodiscard]]
inline bool operator==(SDL_LogPriority a, Priority b) noexcept {
  return a == static_cast<SDL_LogPriority>(b);
}

/**
 * The Category enum provides values the mirror those of SDL_LOG_CATEGORY_x.
 *
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
 * The Log class provides logging-related methods.
 *
 * @since 3.0.0
 */
class CENTURION_API Log final {
 public:
  Log() = delete;

  Log(const Log&) = delete;

  Log(Log&&) = delete;

  Log& operator=(const Log&) = delete;

  Log& operator=(Log&&) = delete;

  /**
   * Resets all of the logging priorities.
   *
   * @since 3.0.0
   */
  CENTURION_API static void reset_priorites() noexcept;

  /**
   * Logs a message.
   *
   * @param category the category of the message.
   * @param prio the priority of the message.
   * @param fmt the formatted string.
   * @param ... the values that are used by the formatted string.
   * @since 3.0.0
   */
  CENTURION_API static void msgf(Category category, Priority prio, const char* fmt, ...) noexcept;

  /**
   * Logs a message.
   *
   * @param category the category of the message.
   * @param fmt the formatted string.
   * @param ... the values that are used by the formatted string.
   * @since 3.0.0
   */
  CENTURION_API static void msgf(Category category, const char* fmt, ...) noexcept;

  /**
   * Logs a message with the App category and Info priority.
   *
   * @param fmt the formatted string.
   * @param ... the values that are used by the formatted string.
   * @since 3.0.0
   */
  CENTURION_API static void msgf(const char* fmt, ...) noexcept;

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
  CENTURION_API static void set_priority(Category category, Priority prio) noexcept;

  /**
   * Returns the priority of the specified category.
   *
   * @param category the category to return the priority of.
   * @return the priority of the specified category.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API static Priority get_priority(Category category) noexcept;
};

}
