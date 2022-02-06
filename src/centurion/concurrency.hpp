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

/**
 * \defgroup concurrency Concurrency
 *
 * \brief Provides low-level abstractions related to concurrent programming.
 */

/// \addtogroup concurrency
/// \{

using thread_id = SDL_threadID;

/**
 * \brief Represents different thread priorities.
 *
 * \note You might need higher privileges to use `high` or `critical` priorities.
 */
enum class thread_priority
{
  low = SDL_THREAD_PRIORITY_LOW,        ///< Non-urgent, background processing.
  normal = SDL_THREAD_PRIORITY_NORMAL,  ///< General purpose processing, this is the default.
  high = SDL_THREAD_PRIORITY_HIGH,      ///< High-priority processing.
  critical = SDL_THREAD_PRIORITY_TIME_CRITICAL  ///< Time-critical processing.
};

/// \name Thread priority functions
/// \{

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

/// \} End of thread priority functions

enum class lock_status
{
  success = 0,
  timed_out = SDL_MUTEX_TIMEDOUT,
  error = -1
};

/// \name Lock status functions
/// \{

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

/// \} End of lock status functions

/**
 * \brief Represents a recursive mutex.
 *
 * \details The fact that the mutex is recursive means that it's possible to nest lock
 * and unlock calls with the same mutex.
 *
 * \see `scoped_lock`
 * \see `try_lock`
 */
class mutex final
{
 public:
  /**
   * \brief Creates an unlocked mutex.
   *
   * \throws sdl_error if the mutex could not be created.
   */
  mutex() : mMutex{SDL_CreateMutex()}
  {
    if (!mMutex) {
      throw sdl_error{};
    }
  }

  /**
   * \brief Attempts to lock the mutex, blocks if the mutex isn't available.
   *
   * \return `success` if the mutex was successfully locked; `failure` otherwise.
   */
  auto lock() noexcept -> result { return SDL_LockMutex(data()) == 0; }

  /**
   * \brief Attempts to lock the mutex, returns if the mutex isn't available.
   *
   * \return the result of the operation.
   */
  auto try_lock() noexcept -> lock_status
  {
    return static_cast<lock_status>(SDL_TryLockMutex(data()));
  }

  /**
   * \brief Attempts to unlock the mutex.
   *
   * \return `success` if the mutex was successfully unlocked; `failure` otherwise.
   */
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

/**
 * \brief An RAII blocking lock that unlocks an associated mutex upon destruction.
 */
class scoped_lock final
{
 public:
  /**
   * \brief Attempts to lock a mutex.
   *
   * \param mutex the mutex that will be locked.
   *
   * \throws sdl_error if the mutex couldn't be locked.
   */
  CENTURION_NODISCARD_CTOR explicit scoped_lock(mutex& mutex) : mMutex{&mutex}
  {
    if (!mutex.lock()) {
      throw sdl_error{};
    }
  }

  CENTURION_DISABLE_COPY(scoped_lock)

  /**
   * \brief Unlocks the associated mutex.
   */
  ~scoped_lock() noexcept { mMutex->unlock(); }

 private:
  mutex* mMutex{};
};

/**
 * \brief An RAII non-blocking lock that unlocks an associated mutex upon destruction.
 */
class try_lock final
{
 public:
  /**
   * \brief Attempts to lock a mutex.
   *
   * \param mutex the mutex to lock.
   */
  CENTURION_NODISCARD_CTOR explicit try_lock(mutex& mutex) noexcept
      : mMutex{&mutex}
      , mStatus{mutex.try_lock()}
  {}

  CENTURION_DISABLE_COPY(try_lock)

  /**
   * \brief Unlocks the associated mutex if it was successfully locked.
   */
  ~try_lock() noexcept
  {
    if (mStatus == lock_status::success) {
      mMutex->unlock();
    }
  }

  /**
   * \brief Returns the result of trying to lock the associated mutex.
   *
   * \return the lock result.
   */
  [[nodiscard]] auto status() const noexcept -> lock_status { return mStatus; }

  /**
   * \brief Indicates whether the mutex was successfully locked.
   *
   * \return `true` if the mutex was locked; `false` otherwise.
   */
  [[nodiscard]] auto locked() const noexcept -> bool
  {
    return status() == lock_status::success;
  }

  /**
   * \brief Indicates whether the lock timed out whilst trying to lock the mutex.
   *
   * \return `true` if the locking timed out; `false` otherwise.
   */
  [[nodiscard]] auto timed_out() const noexcept -> bool
  {
    return status() == lock_status::timed_out;
  }

  /**
   * \brief Indicates whether there was an error whilst locking the mutex.
   *
   * \return `true` if something went wrong whilst locking the mutex; `false` otherwise.
   */
  [[nodiscard]] auto failed() const noexcept -> bool { return status() == lock_status::error; }

  /// \copydoc locked()
  [[nodiscard]] explicit operator bool() const noexcept { return locked(); }

 private:
  mutex* mMutex{};
  lock_status mStatus{};
};

/**
 * \brief Represents a condition variable.
 */
class condition final
{
 public:
  /**
   * \brief Creates a condition variable.
   *
   * \throws sdl_error if the condition variable cannot be initialized.
   */
  condition() : mCond{SDL_CreateCond()}
  {
    if (!mCond) {
      throw sdl_error{};
    }
  }

  /**
   * \brief Wakes up one of the threads waiting on the condition variable.
   *
   * \return `success` if nothing went wrong; `failure` otherwise.
   */
  auto signal() noexcept -> result { return SDL_CondSignal(mCond.get()) == 0; }

  /**
   * \brief Wakes up all threads that are waiting on the condition variable.
   *
   * \return `success` if nothing went wrong; `failure` otherwise.
   */
  auto broadcast() noexcept -> result { return SDL_CondBroadcast(mCond.get()) == 0; }

  /**
   * \brief Waits until the condition variable is signaled.
   *
   * \pre the mutex must be locked when this function is called.
   *
   * \param mutex the mutex that will be used.
   *
   * \return `success` if nothing went wrong; `failure` otherwise.
   */
  auto wait(mutex& mutex) noexcept -> result
  {
    return SDL_CondWait(mCond.get(), mutex.data()) == 0;
  }

  /**
   * \brief Waits until signalled or if the specified amount of time passes.
   *
   * \details This function is implement by looping with a delay of 1 ms on some platforms, and
   * should therefore be avoided if possible.
   *
   * \pre the mutex must be locked when this function is called.
   *
   * \param mutex the mutex that will be used.
   * \param duration the maximum amount of time to wait.
   *
   * \return `success` if nothing went wrong; `failure` otherwise.
   */
  auto wait(mutex& mutex, const u32ms duration) noexcept(noexcept(duration.count()))
      -> lock_status
  {
    return static_cast<lock_status>(
        SDL_CondWaitTimeout(mCond.get(), mutex.data(), duration.count()));
  }

 private:
  managed_ptr<SDL_cond> mCond;
};

/**
 * \brief Represents a semaphore with a set of "tokens" (or permits).
 */
class semaphore final
{
 public:
  /**
   * \brief Creates a semaphore.
   *
   * \param tokens the initial amount of tokens.
   */
  explicit semaphore(const uint32 tokens) : mSemaphore{SDL_CreateSemaphore(tokens)}
  {
    if (!mSemaphore) {
      throw sdl_error{};
    }
  }

  /**
   * \brief Acquires a token from the semaphore.
   *
   * \note This function blocks the calling thread until a token is available.
   *
   * \return `success` if a token was acquired; `failure` otherwise.
   */
  auto acquire() noexcept -> result { return SDL_SemWait(mSemaphore.get()) == 0; }

  /**
   * \brief Attempts to acquire a token from the semaphore.
   *
   * \param duration the maximum amount of time to wait.
   *
   * \return `success` if a token was acquired;
   *         `timed_out` if no token was acquired in the specified duration;
   *         `error` if something goes wrong.
   */
  auto acquire(const u32ms duration) noexcept(noexcept(duration.count())) -> lock_status
  {
    return static_cast<lock_status>(SDL_SemWaitTimeout(mSemaphore.get(), duration.count()));
  }

  /**
   * \brief Attempts to acquire a token from the semaphore.
   *
   * \return `success` if a token was acquired;
   *         `timed_out` if the thread would've been blocked;
   *         `error` if something goes wrong.
   */
  auto try_acquire() noexcept -> lock_status
  {
    return static_cast<lock_status>(SDL_SemTryWait(mSemaphore.get()));
  }

  /**
   * \brief Returns a token to the semaphore and notifies waiting threads.
   *
   * \return `success` if nothing went wrong; `failure` otherwise.
   */
  auto release() noexcept -> result { return SDL_SemPost(mSemaphore.get()) == 0; }

  /**
   * \brief Returns the amount of currently available tokens.
   *
   * \return the amount of tokens.
   */
  [[nodiscard]] auto count() const noexcept -> uint32
  {
    return SDL_SemValue(mSemaphore.get());
  }

 private:
  managed_ptr<SDL_sem> mSemaphore;
};

/**
 * \brief Represents a single thread of execution.
 *
 * \details Unlike `std::thread`, this class will automatically join itself upon destruction,
 * given that it wasn't already detached or joined.
 *
 * \remarks Beware that the C++ standard provides `std::thread` and `std::jthread`, along
 * with several other threading utilities. You should consider using the standard library API.
 */
class thread final
{
 public:
  /// \name Construction
  /// \{

  /**
   * \brief Creates a thread and starts executing it.
   *
   * \param task the task that will be performed.
   * \param name the name of the thread, cannot be null.
   * \param data optional user data that will be supplied to the task function object.
   *
   * \throws sdl_error if the thread cannot be created.
   */
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

  /**
   * \brief Joins the thread, if it hasn't already been joined.
   */
  ~thread() noexcept
  {
    if (joinable()) {
      join();
    }
  }

#if CENTURION_HAS_FEATURE_CONCEPTS

  /**
   * \brief Creates a thread that will execute the supplied callable.
   *
   * \details The supplied callable can either either return nothing or return a value
   * convertible to an `int`. If the callable returns nothing, the thread will simply
   * return `0`.
   *
   * \note If you supply a lambda to this function, it must be stateless.
   *
   * \tparam Callable the type of the callable.
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

  /**
   * \brief Creates a thread that will execute the supplied callable.
   *
   * \details The supplied callable can either either return nothing or return a value
   * convertible to an `int`. If the callable returns nothing, the thread will simply
   * return `0`.
   *
   * \note If you supply a lambda to this function, it must be stateless.
   *
   * \tparam Callable the type of the callable.
   *
   * \param task the callable that will be invoked when the thread starts running.
   * \param userData optional user data that will be supplied to the callable.
   * \param name the name of the thread.
   *
   * \return the created thread.
   */
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

  /// \} End of construction

  /**
   * \brief Forces the current thread to halt for at least the specified duration.
   *
   * \details The actual time spent sleeping may differ, depending on the scheduling of the
   * operating system. You shouldn't use this function for precise timing.
   *
   * \param duration the minimum amount of time to sleep for.
   */
  static void sleep(const u32ms duration) noexcept(noexcept(duration.count()))
  {
    SDL_Delay(duration.count());
  }

  /**
   * \brief Sets the priority of the current thread.
   *
   * \param priority the priority that will be used.
   *
   * \return `success` if the priority was successfully set; `failure` otherwise.
   */
  static auto set_priority(const thread_priority priority) noexcept -> result
  {
    return SDL_SetThreadPriority(static_cast<SDL_ThreadPriority>(priority)) == 0;
  }

  /// \name Mutators
  /// \{

  /**
   * \brief Waits for the thread to finish its execution.
   *
   * \details This function just returns `0` if the thread has already been joined or detached.
   *
   * \return the status code.
   */
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

  /**
   * \brief Lets the thread terminate without having another thread join it.
   *
   * \details This function has no effect if the thread has already been joined or detached.
   */
  void detach() noexcept
  {
    if (mJoined || mDetached) {
      return;
    }

    SDL_DetachThread(mThread);

    mDetached = true;
    assert(mDetached != mJoined);
  }

  /// \} End of mutators

  /// \name Queries
  /// \{

  /**
   * \brief Returns the identifier associated with the current thread.
   *
   * \return the ID of the current thread.
   */
  [[nodiscard]] static auto current_id() noexcept -> thread_id { return SDL_ThreadID(); }

  /**
   * \brief Returns the identifier associated with the thread.
   *
   * \return the ID of the thread.
   */
  [[nodiscard]] auto id() const noexcept -> thread_id { return SDL_GetThreadID(mThread); }

  /**
   * \brief Returns the name of the thread.
   *
   * \return the thread name.
   */
  [[nodiscard]] auto name() const -> std::string { return SDL_GetThreadName(mThread); }

  /**
   * \brief Indicates whether the thread can be joined.
   *
   * \details A thread is joinable if it hasn't been previously detached or joined.
   *
   * \note A joinable thread is also detachable.
   *
   * \return `true` if the thread is joinable; `false` otherwise.
   */
  [[nodiscard]] auto joinable() const noexcept -> bool { return !mJoined && !mDetached; }

  /**
   * \brief Indicates whether or not the thread was joined.
   *
   * \return `true` if the thread has been joined; `false` otherwise.
   */
  [[nodiscard]] auto joined() const noexcept -> bool { return mJoined; }

  /**
   * \brief Indicates whether or not the thread was detached.
   *
   * \return `true` if the thread has been detached; `false` otherwise.
   */
  [[nodiscard]] auto detached() const noexcept -> bool { return mDetached; }

  /// \} End of queries

  /// \name Misc functions
  /// \{

  [[nodiscard]] auto data() noexcept -> SDL_Thread* { return mThread; }

  [[nodiscard]] auto data() const noexcept -> const SDL_Thread* { return mThread; }

  /// \} End of misc functions

 private:
  SDL_Thread* mThread{};
  bool mJoined{false};
  bool mDetached{false};
};

/// \name Thread functions
/// \{

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

/// \} End of thread functions

/// \} End of group concurrency

}  // namespace cen

#endif  // CENTURION_CONCURRENCY_HPP_
