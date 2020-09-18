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

/**
 * @defgroup thread Threads
 *
 * @brief Provides threading utilities for dealing with threads, mutexes, locks,
 * etc.
 *
 * @details SDL provides three basic synchronization primitives: mutex,
 * semaphore and condition variables.
 */

/**
 * @file thread.hpp
 *
 * @ingroup thread
 *
 * @brief Provides the threading API.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

#ifndef CENTURION_THREAD_HEADER
#define CENTURION_THREAD_HEADER

#include <SDL.h>

#include <memory>
#include <ostream>
#include <string>
#include <type_traits>

#include "centurion_api.hpp"
#include "types.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/// @addtogroup thread
/// @{

/**
 * @enum thread_priority
 *
 * @brief Represents different thread priorities.
 *
 * @note You might need higher privileges to use `high` or `critical`
 * priorities.
 *
 * @since 5.0.0
 *
 * @headerfile thread.hpp
 */
enum class thread_priority {
  low = SDL_THREAD_PRIORITY_LOW,        ///< Non-urgent, background processing.
  normal = SDL_THREAD_PRIORITY_NORMAL,  ///< General purpose processing, this is
                                        ///< the default.
  high = SDL_THREAD_PRIORITY_HIGH,      ///< For high-priority processing.
  critical =
      SDL_THREAD_PRIORITY_TIME_CRITICAL  ///< For timing-critical processing.
};

/**
 * @class thread
 *
 * @brief Represents a single thread of execution.
 *
 * @remarks This class purposefully features an API similar to that of
 * `std::thread`. However, unlike `std::thread`, this class will
 * automatically join itself upon destruction if it wasn't already detached
 * or joined.
 *
 * @note Beware that the C++ standard provides `std::thread` and
 * `std::jthread`, along with several other threading utilities. If possible,
 * you should prefer using the standard library API.
 *
 * @since 5.0.0
 *
 * @todo Centurion 6 (C++20): Support templated user data instead of just
 * `void*`.
 *
 * @headerfile thread.hpp
 */
class thread final
{
 public:
  /**
   * @typedef task_type
   *
   * @brief The signature of the function object that will be executed.
   *
   * @since 5.0.0
   */
  using task_type = SDL_ThreadFunction;

  /**
   * @typedef id
   *
   * @brief The type used for thread identifiers.
   *
   * @since 5.0.0
   */
  using id = SDL_threadID;

  /**
   * @brief Creates a thread and starts executing it.
   *
   * @param task the task that will be performed.
   * @param name the name of the thread, cannot be null.
   * @param data a pointer to optional user data that will be supplied to the
   * task function object.
   *
   * @throws sdl_error if the thread cannot be created.
   *
   * @since 5.0.0
   */
  CENTURION_API
  explicit thread(task_type task,
                  nn_czstring name = "thread",
                  void* data = nullptr);

  thread(const thread&) = delete;

  auto operator=(const thread&) -> thread& = delete;

  /**
   * @brief If the thread is joinable, then the thread is joined.
   *
   * @since 5.0.0
   */
  CENTURION_API
  ~thread() noexcept;

  /**
   * @brief Lets the thread terminate without having another thread join it.
   *
   * @note This function has no effect if the thread has already been joined
   * or detached.
   *
   * @since 5.0.0
   */
  CENTURION_API
  void detach() noexcept;

  /**
   * @brief Waits for the thread to finish its execution.
   *
   * @note This function just returns `0` if the thread has already been
   * joined or detached.
   *
   * @return the status code.
   *
   * @since 5.0.0
   */
  CENTURION_API
  auto join() noexcept -> int;

  /**
   * @brief Indicates whether or not the thread can be joined.
   *
   * @details A thread is joinable if it hasn't been previously detached or
   * joined.
   *
   * @note A joinable thread is also detachable.
   *
   * @return `true` if the thread can be joined; `false` otherwise.
   *
   * @since 5.0.0
   */
  CENTURION_QUERY
  auto joinable() const noexcept -> bool;

  /**
   * @brief Indicates whether or not the thread was joined.
   *
   * @return `true` if the thread has been joined; `false` otherwise.
   *
   * @since 5.0.0
   */
  CENTURION_QUERY
  auto was_joined() const noexcept -> bool;

  /**
   * @brief Indicates whether or not the thread was detached.
   *
   * @return `true` if the thread has been detached; `false` otherwise.
   *
   * @since 5.0.0
   */
  CENTURION_QUERY
  auto was_detached() const noexcept -> bool;

  /**
   * @brief Returns the identifier associated with the thread.
   *
   * @return the ID of the thread.
   *
   * @since 5.0.0
   */
  CENTURION_QUERY
  auto get_id() const noexcept -> id;

  /**
   * @brief Returns the name of the thread.
   *
   * @note The default name used is `"thread"`.
   *
   * @return the name of the thread.
   *
   * @since 5.0.0
   */
  CENTURION_QUERY
  auto name() const -> std::string;

  /**
   * @brief Returns a pointer to the associated SDL thread.
   *
   * @return a pointer to the associated SDL thread.
   *
   * @since 5.0.0
   */
  CENTURION_QUERY
  auto get() noexcept -> SDL_Thread*;

  /**
   * @copydoc get
   */
  CENTURION_QUERY
  auto get() const noexcept -> const SDL_Thread*;

  /**
   * @brief Forces the current thread to halt for at least the specified
   * duration.
   *
   * @note The actual time spent sleeping may differ, depending on the
   * scheduling of the operating system. You shouldn't use this function for
   * precise timing.
   *
   * @param ms the minimum amount of time to sleep for, in milliseconds.
   *
   * @since 5.0.0
   */
  CENTURION_API
  static void sleep(milliseconds<u32> ms) noexcept;

  /**
   * @brief Sets the priority of the current thread.
   *
   * @note You might need elevated privileges to use `high` or `critical`
   * priorities.
   *
   * @param priority the priority that will be used.
   *
   * @return `true` if the priority was successfully set; `false` otherwise.
   *
   * @since 5.0.0
   */
  CENTURION_API
  static auto set_priority(thread_priority priority) noexcept -> bool;

  /**
   * @brief Returns the identifier associated with the current thread.
   *
   * @return the ID of the current thread.
   *
   * @since 5.0.0
   */
  CENTURION_QUERY
  static auto current_id() noexcept -> id;

 private:
  SDL_Thread* m_thread{};
  bool m_joined{false};
  bool m_detached{false};
};

static_assert(!std::is_copy_constructible_v<thread>);
static_assert(!std::is_copy_assignable_v<thread>);

/**
 * @brief Returns a textual representation of a thread.
 *
 * @param thread the thread that will be converted.
 *
 * @return a string that represents a thread.
 *
 * @since 5.0.0
 */
CENTURION_QUERY
auto to_string(const thread& thread) -> std::string;

/**
 * @brief Prints a textual representation of a thread.
 *
 * @param stream the stream that will be used.
 * @param thread the thread that will be printed.
 *
 * @return the used stream.
 *
 * @since 5.0.0
 */
CENTURION_QUERY
auto operator<<(std::ostream& stream, const thread& thread) -> std::ostream&;

/**
 * @brief Indicates whether or not two thread priorities are the same.
 *
 * @param lhs the left-hand side thread priority.
 * @param rhs the right-hand side thread priority.
 *
 * @return `true` if the priorities are the same; `false` otherwise.
 *
 * @since 5.0.0
 */
[[nodiscard]] inline constexpr auto operator==(thread_priority lhs,
                                               SDL_ThreadPriority rhs) noexcept
    -> bool
{
  return static_cast<SDL_ThreadPriority>(lhs) == rhs;
}

/**
 * @copydoc operator==(thread_priority, SDL_ThreadPriority)
 */
[[nodiscard]] inline constexpr auto operator==(SDL_ThreadPriority lhs,
                                               thread_priority rhs) noexcept
    -> bool
{
  return rhs == lhs;
}

/**
 * @brief Indicates whether or not two thread priorities aren't the same.
 *
 * @param lhs the left-hand side thread priority.
 * @param rhs the right-hand side thread priority.
 *
 * @return `true` if the priorities aren't the same; `false` otherwise.
 *
 * @since 5.0.0
 */
[[nodiscard]] inline constexpr auto operator!=(thread_priority lhs,
                                               SDL_ThreadPriority rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/**
 * @copydoc operator!=(thread_priority, SDL_ThreadPriority)
 */
[[nodiscard]] inline constexpr auto operator!=(SDL_ThreadPriority lhs,
                                               thread_priority rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/// @}

}  // namespace cen

#endif  // CENTURION_THREAD_HEADER
