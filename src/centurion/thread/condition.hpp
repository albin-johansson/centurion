#ifndef CENTURION_CONDITION_HEADER
#define CENTURION_CONDITION_HEADER

#include <SDL.h>

#include <memory>  // unique_ptr

#include "../core/exception.hpp"
#include "../core/integers.hpp"
#include "../core/result.hpp"
#include "../core/time.hpp"
#include "lock_status.hpp"
#include "mutex.hpp"
#include "scoped_lock.hpp"

namespace cen {

/// \addtogroup thread
/// \{

/**
 * \class condition
 *
 * \brief Represents a condition variable.
 *
 * \since 5.0.0
 */
class condition final
{
 public:
  condition() : m_cond{SDL_CreateCond()}
  {
    if (!m_cond) {
      throw sdl_error{};
    }
  }

  /**
   * \brief Wakes up one of the threads that are waiting on the condition variable.
   *
   * \return `success` if nothing went wrong; `failure` otherwise.
   *
   * \since 5.0.0
   */
  auto signal() noexcept -> result
  {
    return SDL_CondSignal(m_cond.get()) == 0;
  }

  /**
   * \brief Wakes up all threads that are waiting on the condition variable.
   *
   * \return `success` if nothing went wrong; `failure` otherwise.
   *
   * \since 5.0.0
   */
  auto broadcast() noexcept -> result
  {
    return SDL_CondBroadcast(m_cond.get()) == 0;
  }

  /**
   * \brief Waits until the condition variable is signaled.
   *
   * \pre The mutex must be locked when the function is called!
   *
   * \param mutex the mutex used to coordinate thread access.
   *
   * \return `success` if nothing went wrong; `failure` otherwise.
   *
   * \since 5.0.0
   */
  auto wait(mutex& mutex) noexcept -> result
  {
    return SDL_CondWait(m_cond.get(), mutex.get()) == 0;
  }

  /**
   * \brief Waits until the condition variable is signaled or if the specified amount of
   * time has passed.
   *
   * \pre The mutex must be locked when the function is called!
   *
   * \note This function is implemented by looping with a delay of 1 ms on some platforms,
   * and should be avoided if possible.
   *
   * \param mutex the mutex used to coordinate thread access.
   * \param ms the maximum amount of time to wait.
   *
   * \return `true` if everything went OK; `false` on failure.
   *
   * \since 5.0.0
   */
  auto wait(mutex& mutex, const milliseconds<u32> ms) noexcept(noexcept(ms.count()))
      -> lock_status
  {
    return static_cast<lock_status>(
        SDL_CondWaitTimeout(m_cond.get(), mutex.get(), ms.count()));
  }

 private:
  struct deleter final
  {
    void operator()(SDL_cond* cond) noexcept
    {
      SDL_DestroyCond(cond);
    };
  };

  std::unique_ptr<SDL_cond, deleter> m_cond;
};

/// \} End of group thread

}  // namespace cen

#endif  // CENTURION_CONDITION_HEADER
