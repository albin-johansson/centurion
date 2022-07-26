/*
 * MIT License
 *
 * Copyright (c) 2019-2022 Albin Johansson
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

#ifndef CENTURION_CONCURRENCY_HPP_
#define CENTURION_CONCURRENCY_HPP_

#include <SDL.h>

#include <cassert>      // assert
#include <ostream>      // ostream
#include <string>       // string, to_string
#include <string_view>  // string_view
#include <type_traits>  // invoke_result_t, declval

#include "common.hpp"
#include "detail/stdlib.hpp"
#include "features.hpp"
#include "memory.hpp"

#if CENTURION_HAS_FEATURE_CONCEPTS

#include <concepts>  // convertible_to, default_initializable, invocable

#endif  // CENTURION_HAS_FEATURE_CONCEPTS

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen {

using thread_id = SDL_threadID;

enum class thread_priority
{
  low = SDL_THREAD_PRIORITY_LOW,
  normal = SDL_THREAD_PRIORITY_NORMAL,
  high = SDL_THREAD_PRIORITY_HIGH,
  critical = SDL_THREAD_PRIORITY_TIME_CRITICAL
};

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
      throw exception{"Did not recognize thread priority!"};
  }
}

inline auto operator<<(std::ostream& stream, const thread_priority priority) -> std::ostream&
{
  return stream << to_string(priority);
}

enum class lock_status
{
  success = 0,
  timed_out = SDL_MUTEX_TIMEDOUT,
  error = -1
};

[[nodiscard]] constexpr auto to_string(const lock_status status) -> std::string_view
{
  switch (status) {
    case lock_status::success:
      return "success";

    case lock_status::timed_out:
      return "timed_out";

    case lock_status::error:
      return "error";

    default:
      throw exception{"Did not recognize lock status!"};
  }
}

inline auto operator<<(std::ostream& stream, const lock_status status) -> std::ostream&
{
  return stream << to_string(status);
}

/**
 * Represents a recursive mutex.
 *
 * \see scoped_lock
 * \see try_lock
 */
class mutex final
{
 public:
  /// Creates an unlocked mutex.
  mutex() : mMutex{SDL_CreateMutex()}
  {
    if (!mMutex) {
      throw sdl_error{};
    }
  }

  /// Attempts to lock the mutex, blocks if the mutex isn't available.
  auto lock() noexcept -> result { return SDL_LockMutex(data()) == 0; }

  /// Attempts to lock the mutex and returns immediately.
  auto try_lock() noexcept -> lock_status
  {
    return static_cast<lock_status>(SDL_TryLockMutex(data()));
  }

  auto unlock() noexcept -> result { return SDL_UnlockMutex(data()) == 0; }

  [[nodiscard]] auto data() noexcept -> SDL_mutex* { return mMutex.get(); }

  [[nodiscard]] auto data() const noexcept -> const SDL_mutex* { return mMutex.get(); }

 private:
  managed_ptr<SDL_mutex> mMutex;

#ifdef CENTURION_MOCK_FRIENDLY_MODE

 public:
  explicit mutex(int /*dummy*/){};

#endif  // CENTURION_MOCK_FRIENDLY_MODE
};

/// An RAII style blocking lock that unlocks the associated mutex upon destruction.
class scoped_lock final
{
 public:
  /// Attempts to lock a mutex.
  CENTURION_NODISCARD_CTOR explicit scoped_lock(mutex& mutex) : mMutex{&mutex}
  {
    if (!mutex.lock()) {
      throw sdl_error{};
    }
  }

  CENTURION_DISABLE_COPY(scoped_lock)
  CENTURION_DISABLE_MOVE(scoped_lock)

  ~scoped_lock() noexcept { mMutex->unlock(); }

 private:
  mutex* mMutex{};
};

/// An RAII style non-blocking lock that unlocks the associated mutex upon destruction.
class try_lock final
{
 public:
  /// Attempts to lock a mutex.
  CENTURION_NODISCARD_CTOR explicit try_lock(mutex& mutex) noexcept
      : mMutex{&mutex}
      , mStatus{mutex.try_lock()}
  {}

  CENTURION_DISABLE_COPY(try_lock)

  ~try_lock() noexcept
  {
    if (mStatus == lock_status::success) {
      mMutex->unlock();
    }
  }

  [[nodiscard]] auto status() const noexcept -> lock_status { return mStatus; }

  [[nodiscard]] auto locked() const noexcept -> bool
  {
    return status() == lock_status::success;
  }

  [[nodiscard]] auto timed_out() const noexcept -> bool
  {
    return status() == lock_status::timed_out;
  }

  [[nodiscard]] auto failed() const noexcept -> bool { return status() == lock_status::error; }

  /// Indicates whether the mutex was successfully locked.
  [[nodiscard]] explicit operator bool() const noexcept { return locked(); }

 private:
  mutex* mMutex{};
  lock_status mStatus{};
};

/// Represents a condition variable.
class condition final
{
 public:
  condition() : mCond{SDL_CreateCond()}
  {
    if (!mCond) {
      throw sdl_error{};
    }
  }

  /// Wakes up one of the threads waiting on the condition variable.
  auto signal() noexcept -> result { return SDL_CondSignal(mCond.get()) == 0; }

  /// Wakes up all threads that are waiting on the condition variable.
  auto broadcast() noexcept -> result { return SDL_CondBroadcast(mCond.get()) == 0; }

  auto wait(mutex& mutex) noexcept -> result
  {
    return SDL_CondWait(mCond.get(), mutex.data()) == 0;
  }

  auto wait(mutex& mutex, const u32ms duration) noexcept(noexcept(duration.count()))
      -> lock_status
  {
    return static_cast<lock_status>(
        SDL_CondWaitTimeout(mCond.get(), mutex.data(), duration.count()));
  }

 private:
  managed_ptr<SDL_cond> mCond;
};

/// Represents a semaphore with a set of "tokens" (or "permits").
class semaphore final
{
 public:
  /// Creates a semaphore with an initial amount of tokens.
  explicit semaphore(const uint32 tokens) : mSemaphore{SDL_CreateSemaphore(tokens)}
  {
    if (!mSemaphore) {
      throw sdl_error{};
    }
  }

  /// Acquires a token from the semaphore, blocks until a token is available.
  auto acquire() noexcept -> result { return SDL_SemWait(mSemaphore.get()) == 0; }

  auto acquire(const u32ms duration) noexcept(noexcept(duration.count())) -> lock_status
  {
    return static_cast<lock_status>(SDL_SemWaitTimeout(mSemaphore.get(), duration.count()));
  }

  auto try_acquire() noexcept -> lock_status
  {
    return static_cast<lock_status>(SDL_SemTryWait(mSemaphore.get()));
  }

  /// Returns a token to the semaphore and notifies waiting threads.
  auto release() noexcept -> result { return SDL_SemPost(mSemaphore.get()) == 0; }

  /// Returns the amount of available tokens.
  [[nodiscard]] auto count() const noexcept -> uint32
  {
    return SDL_SemValue(mSemaphore.get());
  }

 private:
  managed_ptr<SDL_sem> mSemaphore;
};

/**
 * Represents a single thread of execution.
 *
 * Unlike std::thread, this class will automatically join itself upon destruction (given that
 * it wasn't already detached or joined).
 */
class thread final
{
 public:
  /// Creates a thread and starts executing it.
  CENTURION_NODISCARD_CTOR explicit thread(SDL_ThreadFunction task,
                                           const char* name = "thread",
                                           void* data = nullptr)
      : mThread{SDL_CreateThread(task, name, data)}
  {
    if (!mThread) {
      throw sdl_error{};
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
   * The supplied callable can either either return nothing or return a value convertible to an
   * `int`. If the callable returns nothing, the thread will simply return `0`.
   *
   * Note, any lambda you supply to this function must be stateless.
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

    constexpr bool nothrow = noexcept(Callable{}());

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

    return thread{wrapper, name};
  }

  template <typename T = void, is_stateless_callable<T*> Callable>
  [[nodiscard]] static auto init([[maybe_unused]] Callable&& task,
                                 T* userData = nullptr,
                                 const char* name = "thread") -> thread
  {
    assert(name);

    constexpr bool nothrow = noexcept(Callable{}(std::declval<T*>()));

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

    return thread{wrapper, name, userData};
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

    int status{};
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
  SDL_Thread* mThread{};
  bool mJoined{false};
  bool mDetached{false};
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

inline auto operator<<(std::ostream& stream, const thread& thread) -> std::ostream&
{
  return stream << to_string(thread);
}

}  // namespace cen

#endif  // CENTURION_CONCURRENCY_HPP_
