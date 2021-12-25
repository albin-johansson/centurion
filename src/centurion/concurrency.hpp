#ifndef CENTURION_CONCURRENCY_HPP_
#define CENTURION_CONCURRENCY_HPP_

#include <SDL.h>

#include <cassert>      // assert
#include <ostream>      // ostream
#include <string>       // string, to_string
#include <string_view>  // string_view
#include <type_traits>  // invoke_result_t, declval

#include "common.hpp"
#include "features.hpp"
#include "memory.hpp"
#include "detail/stdlib.hpp"

#if CENTURION_HAS_FEATURE_CONCEPTS

#include <concepts>  // convertible_to, default_initializable, invocable

#endif  // CENTURION_HAS_FEATURE_CONCEPTS

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen {

/// \addtogroup system
/// \{

using ThreadID = SDL_threadID;

enum class ThreadPriority {
  Low = SDL_THREAD_PRIORITY_LOW,       /* Non-urgent, background processing. */
  Normal = SDL_THREAD_PRIORITY_NORMAL, /* General purpose processing, this is the default. */
  High = SDL_THREAD_PRIORITY_HIGH,     /* High-priority processing. */
  Critical = SDL_THREAD_PRIORITY_TIME_CRITICAL /* Time-critical processing. */
};

enum class LockStatus {
  Success = 0,
  TimedOut = SDL_MUTEX_TIMEDOUT,
  Error = -1
};

class Mutex final {
 public:
  /* Creates an unlocked mutex. */
  Mutex() : mMutex{SDL_CreateMutex()}
  {
    if (!mMutex) {
      throw SDLError{};
    }
  }

  /* Attempts to lock the mutex, blocks if the mutex is unavailable. */
  auto Lock() noexcept -> Result { return SDL_LockMutex(get()) == 0; }

  /*  Attempts to lock the mutex, returns if the mutex is unavailable. */
  auto TryLock() noexcept -> LockStatus
  {
    return static_cast<LockStatus>(SDL_TryLockMutex(get()));
  }

  /*  Attempts to unlock the mutex. */
  auto Unlock() noexcept -> Result { return SDL_UnlockMutex(get()) == 0; }

  [[nodiscard]] auto get() noexcept -> SDL_mutex* { return mMutex.get(); }

 private:
  Managed<SDL_mutex> mMutex;

#ifdef CENTURION_MOCK_FRIENDLY_MODE

 public:
  explicit Mutex(int /*dummy*/){};

#endif  // CENTURION_MOCK_FRIENDLY_MODE
};

class ScopedLock final {
 public:
  CENTURION_DISABLE_COPY(ScopedLock)

  /* Attempts to lock the supplied mutex. */
  CENTURION_NODISCARD_CTOR explicit ScopedLock(Mutex& mutex) : mMutex{&mutex}
  {
    if (!mutex.Lock()) {
      throw SDLError{};
    }
  }

  /* Unlocks the associated mutex. */
  ~ScopedLock() noexcept { mMutex->Unlock(); }

 private:
  Mutex* mMutex{};
};

class TryLock final {
 public:
  CENTURION_DISABLE_COPY(TryLock)

  /* Attempts to lock the supplied mutex. */
  CENTURION_NODISCARD_CTOR explicit TryLock(Mutex& mutex) noexcept
      : mMutex{&mutex}
      , mStatus{mutex.TryLock()}
  {}

  /* Unlocks the associated mutex if it was successfully locked. */
  ~TryLock() noexcept
  {
    if (mStatus == LockStatus::Success) {
      mMutex->Unlock();
    }
  }

  /* Returns the result of trying to lock the associated mutex. */
  [[nodiscard]] auto GetStatus() const noexcept -> LockStatus { return mStatus; }

  /* Indicates whether the mutex was successfully locked. */
  [[nodiscard]] auto DidLock() const noexcept -> bool
  {
    return GetStatus() == LockStatus::Success;
  }

  /* Indicates whether the lock timed out whilst trying to lock the mutex. */
  [[nodiscard]] auto DidTimeOut() const noexcept -> bool
  {
    return GetStatus() == LockStatus::TimedOut;
  }

  /* Indicates whether there was an error whilst locking the mutex. */
  [[nodiscard]] auto DidFail() const noexcept -> bool
  {
    return GetStatus() == LockStatus::Error;
  }

  [[nodiscard]] explicit operator bool() const noexcept { return DidLock(); }

 private:
  Mutex* mMutex{};
  LockStatus mStatus{};
};

class Condition final {
 public:
  Condition() : mCond{SDL_CreateCond()}
  {
    if (!mCond) {
      throw SDLError{};
    }
  }

  /* Wakes up one of the threads waiting on the condition variable. */
  auto Signal() noexcept -> Result { return SDL_CondSignal(mCond.get()) == 0; }

  /* Wakes up all threads that are waiting on the condition variable. */
  auto Broadcast() noexcept -> Result { return SDL_CondBroadcast(mCond.get()) == 0; }

  /* Waits until the condition variable is signaled. */
  auto Wait(Mutex& mutex) noexcept -> Result
  {
    return SDL_CondWait(mCond.get(), mutex.get()) == 0;
  }

  /* Waits until signalled or if the specified amount of time passes. */
  auto Wait(Mutex& mutex, const U32_Millis ms) noexcept(noexcept(ms.count())) -> LockStatus
  {
    return static_cast<LockStatus>(SDL_CondWaitTimeout(mCond.get(), mutex.get(), ms.count()));
  }

 private:
  Managed<SDL_cond> mCond;
};

class Semaphore final {
 public:
  /* Creates a semaphore with the specified amount of tokens. */
  explicit Semaphore(const Uint32 tokens) : mSemaphore{SDL_CreateSemaphore(tokens)}
  {
    if (!mSemaphore) {
      throw SDLError{};
    }
  }

  /* Waits until a token is available. */
  auto Acquire() noexcept -> Result { return SDL_SemWait(mSemaphore.get()) == 0; }

  /* Waits until a token is available for a limited time. */
  auto Acquire(const U32_Millis ms) noexcept(noexcept(ms.count())) -> LockStatus
  {
    return static_cast<LockStatus>(SDL_SemWaitTimeout(mSemaphore.get(), ms.count()));
  }

  /* Attempts to acquire a token. */
  auto TryAcquire() noexcept -> LockStatus
  {
    return static_cast<LockStatus>(SDL_SemTryWait(mSemaphore.get()));
  }

  /* Returns a token to the semaphore and notifies waiting threads. */
  auto Release() noexcept -> Result { return SDL_SemPost(mSemaphore.get()) == 0; }

  [[nodiscard]] auto GetTokens() const noexcept -> Uint32
  {
    return SDL_SemValue(mSemaphore.get());
  }

 private:
  Managed<SDL_sem> mSemaphore;
};

class Thread final {
 public:
  CENTURION_DISABLE_COPY(Thread)

  /* Creates a thread and starts executing it. */
  CENTURION_NODISCARD_CTOR explicit Thread(SDL_ThreadFunction task,
                                           const char* name = "thread",
                                           void* data = nullptr)
      : mThread{SDL_CreateThread(task, name, data)}
  {
    if (!mThread) {
      throw SDLError{};
    }
  }

  /* Joins the thread */
  ~Thread() noexcept
  {
    if (IsJoinable()) {
      Join();
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
   *
   * \since 6.2.0
   */
  template <is_stateless_callable Callable>
  [[nodiscard]] static auto Init([[maybe_unused]] Callable&& task, const char* name = "thread")
      -> Thread
  {
    assert(name);

    constexpr bool isNoexcept = noexcept(Callable{}());

    const auto wrapper = [](void* /*data*/) noexcept(isNoexcept) -> int {
      Callable callable;
      if constexpr (std::convertible_to<std::invoke_result_t<Callable>, int>) {
        return callable();
      }
      else {
        callable();
        return 0;
      }
    };

    return Thread{wrapper, name};
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
   *
   * \since 6.2.0
   */
  template <typename T = void, is_stateless_callable<T*> Callable>
  [[nodiscard]] static auto Init([[maybe_unused]] Callable&& task,
                                 T* userData = nullptr,
                                 const char* name = "thread") -> Thread
  {
    assert(name);

    constexpr bool isNoexcept = noexcept(Callable{}(std::declval<T*>()));

    const auto wrapper = [](void* erased) noexcept(isNoexcept) -> int {
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

    return Thread{wrapper, name, userData};
  }

#endif  // CENTURION_HAS_FEATURE_CONCEPTS

  /* Forces the current thread to halt for at least the specified amount of time. */
  static void Sleep(const U32_Millis ms) noexcept(noexcept(ms.count()))
  {
    SDL_Delay(ms.count());
  }

  /* Lets the thread terminate without having another thread join it. */
  void Detach() noexcept
  {
    if (mJoined || mDetached) {
      return;
    }

    SDL_DetachThread(mThread);

    mDetached = true;
    assert(mDetached != mJoined);
  }

  /* Waits for the thread to finish executing. */
  auto Join() noexcept -> int
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

  static auto SetPriority(const ThreadPriority priority) noexcept -> Result
  {
    const auto prio = static_cast<SDL_ThreadPriority>(priority);
    return SDL_SetThreadPriority(prio) == 0;
  }

  [[nodiscard]] auto IsJoinable() const noexcept -> bool { return !mJoined && !mDetached; }

  [[nodiscard]] auto IsJoined() const noexcept -> bool { return mJoined; }

  [[nodiscard]] auto IsDetached() const noexcept -> bool { return mDetached; }

  [[nodiscard]] auto GetName() const -> std::string { return SDL_GetThreadName(mThread); }

  [[nodiscard]] auto GetID() const noexcept -> ThreadID { return SDL_GetThreadID(mThread); }

  [[nodiscard]] static auto GetCurrentID() noexcept -> ThreadID { return SDL_ThreadID(); }

  [[nodiscard]] auto get() noexcept -> SDL_Thread* { return mThread; }

  [[nodiscard]] auto get() const noexcept -> const SDL_Thread* { return mThread; }

 private:
  SDL_Thread* mThread{};
  bool mJoined{false};
  bool mDetached{false};
};

[[nodiscard]] constexpr auto to_string(const ThreadPriority priority) -> std::string_view
{
  switch (priority) {
    case ThreadPriority::Low:
      return "Low";

    case ThreadPriority::Normal:
      return "Normal";

    case ThreadPriority::High:
      return "High";

    case ThreadPriority::Critical:
      return "Critical";

    default:
      throw Error{"Did not recognize thread priority!"};
  }
}

[[nodiscard]] constexpr auto to_string(const LockStatus status) -> std::string_view
{
  switch (status) {
    case LockStatus::Success:
      return "Success";

    case LockStatus::TimedOut:
      return "TimedOut";

    case LockStatus::Error:
      return "Error";

    default:
      throw Error{"Did not recognize lock status!"};
  }
}

[[nodiscard]] inline auto to_string(const Thread& thread) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("Thread(data: {}, name: {}, id: {})",
                     detail::address_of(thread.get()),
                     thread.GetName(),
                     thread.GetID());
#else
  return "Thread(data: " + detail::address_of(thread.get()) + ", name: " + thread.GetName() +
         ", id: " + std::to_string(thread.GetID()) + ")";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

inline auto operator<<(std::ostream& stream, const ThreadPriority priority) -> std::ostream&
{
  return stream << to_string(priority);
}

inline auto operator<<(std::ostream& stream, const LockStatus status) -> std::ostream&
{
  return stream << to_string(status);
}

inline auto operator<<(std::ostream& stream, const Thread& thread) -> std::ostream&
{
  return stream << to_string(thread);
}

/// \} End of group system

}  // namespace cen

#endif  // CENTURION_CONCURRENCY_HPP_
