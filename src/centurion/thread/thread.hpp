#ifndef CENTURION_THREAD_HEADER
#define CENTURION_THREAD_HEADER

#include <SDL.h>

#include <cassert>      // assert
#include <ostream>      // ostream
#include <string>       // string, to_string
#include <type_traits>  // invoke_result_t, declval

#include "../compiler/features.hpp"

#if CENTURION_HAS_FEATURE_CONCEPTS

#include <concepts>  // convertible_to, default_initializable, invocable

#endif  // CENTURION_HAS_FEATURE_CONCEPTS

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

#include "../core/exception.hpp"
#include "../core/integers.hpp"
#include "../core/is_stateless_callable.hpp"
#include "../core/not_null.hpp"
#include "../core/result.hpp"
#include "../core/str.hpp"
#include "../core/time.hpp"
#include "../detail/address_of.hpp"
#include "thread_priority.hpp"

namespace cen {

/// \addtogroup thread
/// \{

using thread_id = SDL_threadID;

/**
 * \class thread
 *
 * \brief Represents a single thread of execution.
 *
 * \remarks This class purposefully features an API similar to that of `std::thread`.
 * However, unlike `std::thread`, this class will automatically join itself upon
 * destruction if it wasn't already detached or joined.
 *
 * \note Beware that the C++ standard provides `std::thread` and `std::jthread`, along
 * with several other threading utilities. If possible, you should prefer using the
 * standard library API.
 *
 * \since 5.0.0
 */
class thread final
{
 public:
  /**
   * \typedef task_type
   *
   * \brief The signature of the function object that will be executed.
   *
   * \since 5.0.0
   */
  using task_type = SDL_ThreadFunction;

  /**
   * \typedef id
   *
   * \brief The type used for thread identifiers.
   *
   * \deprecated Since 6.2.0, use `thread_id` instead.
   *
   * \since 5.0.0
   */
  using id [[deprecated]] = SDL_threadID;

  /// \name Construction/Destruction
  /// \{

  /**
   * \brief Creates a thread and starts executing it.
   *
   * \param task the task that will be performed.
   * \param name the name of the thread, cannot be null.
   * \param data a pointer to optional user data that will be supplied to the task
   * function object.
   *
   * \throws sdl_error if the thread cannot be created.
   *
   * \since 5.0.0
   */
  CENTURION_NODISCARD_CTOR explicit thread(task_type task,
                                           const not_null<str> name = "thread",
                                           void* data = nullptr)
      : m_thread{SDL_CreateThread(task, name, data)}
  {
    if (!m_thread) {
      throw sdl_error{};
    }
  }

  thread(const thread&) = delete;

  auto operator=(const thread&) -> thread& = delete;

  /**
   * \brief If the thread is joinable, then the thread is joined.
   *
   * \since 5.0.0
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
   *
   * \since 6.2.0
   */
  template <is_stateless_callable Callable>
  [[nodiscard]] static auto init([[maybe_unused]] Callable&& task,
                                 const not_null<str> name = "thread") -> thread
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
   *
   * \since 6.2.0
   */
  template <typename T = void, is_stateless_callable<T*> Callable>
  [[nodiscard]] static auto init([[maybe_unused]] Callable&& task,
                                 T* userData = nullptr,
                                 const not_null<str> name = "thread") -> thread
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

    return thread{wrapper, name, userData};
  }

#endif  // CENTURION_HAS_FEATURE_CONCEPTS

  /// \} End of construction/destruction

  /**
   * \brief Forces the current thread to halt for at least the specified duration.
   *
   * \note The actual time spent sleeping may differ, depending on the scheduling of the
   * operating system. You shouldn't use this function for precise timing.
   *
   * \param ms the minimum amount of time to sleep for, in milliseconds.
   *
   * \since 5.0.0
   */
  static void sleep(const milliseconds<u32> ms) noexcept(noexcept(ms.count()))
  {
    SDL_Delay(ms.count());
  }

  /**
   * \brief Sets the priority of the current thread.
   *
   * \note You might need elevated privileges to use `high` or `critical` priorities.
   *
   * \param priority the priority that will be used.
   *
   * \return `success` if the priority was successfully set; `failure` otherwise.
   *
   * \since 5.0.0
   */
  static auto set_priority(const thread_priority priority) noexcept -> result
  {
    const auto prio = static_cast<SDL_ThreadPriority>(priority);
    return SDL_SetThreadPriority(prio) == 0;
  }

  /// \name Mutators
  /// \{

  /**
   * \brief Lets the thread terminate without having another thread join it.
   *
   * \note This function has no effect if the thread has already been joined or detached.
   *
   * \since 5.0.0
   */
  void detach() noexcept
  {
    if (m_joined || m_detached) {
      return;
    }

    SDL_DetachThread(m_thread);

    m_detached = true;
    assert(m_detached != m_joined);
  }

  /**
   * \brief Waits for the thread to finish its execution.
   *
   * \note This function just returns `0` if the thread has already been joined or
   * detached.
   *
   * \return the status code.
   *
   * \since 5.0.0
   */
  auto join() noexcept -> int
  {
    if (m_joined || m_detached) {
      return 0;
    }

    int status{};
    SDL_WaitThread(m_thread, &status);

    m_joined = true;
    assert(m_detached != m_joined);

    return status;
  }

  /// \} End of mutators

  /// \name Queries
  /// \{

  /**
   * \brief Indicates whether or not the thread can be joined.
   *
   * \details A thread is joinable if it hasn't been previously detached or joined.
   *
   * \note A joinable thread is also detachable.
   *
   * \return `true` if the thread can be joined; `false` otherwise.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto joinable() const noexcept -> bool
  {
    return !m_joined && !m_detached;
  }

  /**
   * \brief Indicates whether or not the thread was joined.
   *
   * \return `true` if the thread has been joined; `false` otherwise.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto was_joined() const noexcept -> bool
  {
    return m_joined;
  }

  /**
   * \brief Indicates whether or not the thread was detached.
   *
   * \return `true` if the thread has been detached; `false` otherwise.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto was_detached() const noexcept -> bool
  {
    return m_detached;
  }

  /**
   * \brief Returns the identifier associated with the thread.
   *
   * \return the ID of the thread.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto get_id() const noexcept -> thread_id
  {
    return SDL_GetThreadID(m_thread);
  }

  /**
   * \brief Returns the identifier associated with the current thread.
   *
   * \return the ID of the current thread.
   *
   * \since 5.0.0
   */
  [[nodiscard]] static auto current_id() noexcept -> thread_id
  {
    return SDL_ThreadID();
  }

  /**
   * \brief Returns the name of the thread.
   *
   * \note The default name used is `"thread"`.
   *
   * \return the name of the thread.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto name() const -> std::string
  {
    return SDL_GetThreadName(m_thread);
  }

  /**
   * \brief Returns a pointer to the associated SDL thread.
   *
   * \return a pointer to the associated SDL thread.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto get() noexcept -> SDL_Thread*
  {
    return m_thread;
  }

  /// \copydoc get
  [[nodiscard]] auto get() const noexcept -> const SDL_Thread*
  {
    return m_thread;
  }

  /// \} End of queries

 private:
  SDL_Thread* m_thread{};
  bool m_joined{false};
  bool m_detached{false};
};

/// \name String conversions
/// \{

/**
 * \brief Returns a textual representation of a thread.
 *
 * \param thread the thread that will be converted.
 *
 * \return a string that represents a thread.
 *
 * \since 5.0.0
 */
[[nodiscard]] inline auto to_string(const thread& thread) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("thread{{data: {}, name: {}, id: {}}}",
                     detail::address_of(thread.get()),
                     thread.name(),
                     thread.get_id());
#else
  return "thread{data: " + detail::address_of(thread.get()) + ", name: " + thread.name() +
         ", id: " + std::to_string(thread.get_id()) + "}";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of a thread.
 *
 * \param stream the stream that will be used.
 * \param thread the thread that will be printed.
 *
 * \return the used stream.
 *
 * \since 5.0.0
 */
inline auto operator<<(std::ostream& stream, const thread& thread) -> std::ostream&
{
  stream << to_string(thread);
  return stream;
}

/// \} End of streaming

/// \} End of group thread

}  // namespace cen

#endif  // CENTURION_THREAD_HEADER
