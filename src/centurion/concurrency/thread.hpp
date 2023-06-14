/*
 * MIT License
 *
 * Copyright (c) 2019-2023 Albin Johansson
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

#ifndef CENTURION_CONCURRENCY_THREAD_HPP_
#define CENTURION_CONCURRENCY_THREAD_HPP_

#include <SDL.h>

#include <cassert>      // assert
#include <ostream>      // ostream
#include <string>       // string, to_string
#include <string_view>  // string_view
#include <type_traits>  // invoke_result_t
#include <utility>      // declval

#include "../common/errors.hpp"
#include "../common/primitives.hpp"
#include "../common/result.hpp"
#include "../common/traits.hpp"
#include "../common/utils.hpp"
#include "../detail/stdlib.hpp"
#include "../features.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

#if CENTURION_HAS_FEATURE_CONCEPTS

#include <concepts>  // convertible_to

#endif  // CENTURION_HAS_FEATURE_CONCEPTS

namespace cen {

using thread_id = SDL_threadID;

enum class thread_priority {
  low = SDL_THREAD_PRIORITY_LOW,
  normal = SDL_THREAD_PRIORITY_NORMAL,
  high = SDL_THREAD_PRIORITY_HIGH,
  critical = SDL_THREAD_PRIORITY_TIME_CRITICAL
};

/**
 * Represents a single thread of execution.
 *
 * \details Unlike `std::thread`, this class will automatically join itself upon destruction
 *          (given that it wasn't already detached or joined).
 */
class thread final {
 public:
  /// Creates a thread and starts executing it.
  CENTURION_NODISCARD_CTOR explicit thread(SDL_ThreadFunction task,
                                           const char* name = "thread",
                                           void* data = nullptr)
      : mThread {SDL_CreateThread(task, name, data)}
  {
    if (!mThread) {
      throw sdl_error {};
    }
  }

  CENTURION_DISABLE_COPY(thread)

  ~thread() noexcept
  {
    if (joinable()) {
      join();
    }
  }

#if CENTURION_HAS_FEATURE_CONCEPTS

  /**
   * Creates a thread and starts executing it.
   *
   * \details The supplied callable can either either return nothing or return a value
   *          convertible to an `int`. If the callable returns nothing, the thread will simply
   *          return `0`.
   *
   * \note The lambda you supply to this function must be stateless.
   *
   * \param task the callable that will be invoked when the thread starts running.
   * \param name the name of the thread.
   *
   * \return the created thread.
   */
  template <is_stateless_callable Callable>
  [[nodiscard]] static auto init([[maybe_unused]] Callable&& task, const char* name = "thread")
      -> thread
  {
    assert(name);

    constexpr bool nothrow = noexcept(Callable {}());

    const auto wrapper = [](void* /*data*/) noexcept(nothrow) -> int {
      Callable callable;
      if constexpr (std::convertible_to<std::invoke_result_t<Callable>, int>) {
        return callable();
      }
      else {
        callable();
        return 0;
      }
    };

    return thread {wrapper, name};
  }

  template <typename T = void, is_stateless_callable<T*> Callable>
  [[nodiscard]] static auto init([[maybe_unused]] Callable&& task,
                                 T* userData = nullptr,
                                 const char* name = "thread") -> thread
  {
    assert(name);

    constexpr bool nothrow = noexcept(Callable {}(std::declval<T*>()));

    const auto wrapper = [](void* erased) noexcept(nothrow) -> int {
      auto* ptr = static_cast<T*>(erased);

      Callable callable;
      if constexpr (std::convertible_to<std::invoke_result_t<Callable, T*>, int>) {
        return callable(ptr);
      }
      else {
        callable(ptr);
        return 0;
      }
    };

    return thread {wrapper, name, userData};
  }

#endif  // CENTURION_HAS_FEATURE_CONCEPTS

  static void sleep(const u32ms duration) noexcept(noexcept(duration.count()))
  {
    SDL_Delay(duration.count());
  }

  static auto set_priority(const thread_priority priority) noexcept -> result
  {
    return SDL_SetThreadPriority(static_cast<SDL_ThreadPriority>(priority)) == 0;
  }

  /// Waits for the thread to stop running.
  auto join() noexcept -> int
  {
    if (mJoined || mDetached) {
      return 0;
    }

    int status {};
    SDL_WaitThread(mThread, &status);

    mJoined = true;
    assert(mDetached != mJoined);

    return status;
  }

  /// Lets the thread terminate without having another thread join it.
  void detach() noexcept
  {
    if (mJoined || mDetached) {
      return;
    }

    SDL_DetachThread(mThread);

    mDetached = true;
    assert(mDetached != mJoined);
  }

  [[nodiscard]] static auto current_id() noexcept -> thread_id { return SDL_ThreadID(); }

  [[nodiscard]] auto id() const noexcept -> thread_id { return SDL_GetThreadID(mThread); }

  [[nodiscard]] auto name() const -> std::string { return SDL_GetThreadName(mThread); }

  [[nodiscard]] auto joinable() const noexcept -> bool { return !mJoined && !mDetached; }

  [[nodiscard]] auto joined() const noexcept -> bool { return mJoined; }

  [[nodiscard]] auto detached() const noexcept -> bool { return mDetached; }

  [[nodiscard]] auto data() noexcept -> SDL_Thread* { return mThread; }

  [[nodiscard]] auto data() const noexcept -> const SDL_Thread* { return mThread; }

 private:
  SDL_Thread* mThread {};
  bool mJoined {false};
  bool mDetached {false};
};

[[nodiscard]] inline auto to_string(const thread& thread) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("thread(data: {}, name: '{}', id: {})",
                     detail::address_of(thread.data()),
                     thread.name(),
                     thread.id());
#else
  return "thread(data: " + detail::address_of(thread.data()) + ", name: " + thread.name() +
         ", id: " + std::to_string(thread.id()) + ")";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

[[nodiscard]] constexpr auto to_string(const thread_priority priority) -> std::string_view
{
  switch (priority) {
    case thread_priority::low:
      return "low";

    case thread_priority::normal:
      return "normal";

    case thread_priority::high:
      return "high";

    case thread_priority::critical:
      return "critical";

    default:
      throw exception {"Did not recognize thread priority!"};
  }
}

inline auto operator<<(std::ostream& stream, const thread& thread) -> std::ostream&
{
  return stream << to_string(thread);
}

inline auto operator<<(std::ostream& stream, const thread_priority priority) -> std::ostream&
{
  return stream << to_string(priority);
}

}  // namespace cen

#endif  // CENTURION_CONCURRENCY_THREAD_HPP_
