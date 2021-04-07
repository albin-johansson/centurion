#ifndef CENTURION_CONDITION_HEADER
#define CENTURION_CONDITION_HEADER

#include <SDL.h>

#include <memory>  // unique_ptr

#include "../misc/exception.hpp"
#include "../misc/integers.hpp"
#include "../misc/time.hpp"
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
 *
 * \headerfile condition.hpp
 */
class condition final
{
 public:
  condition() : m_cond{SDL_CreateCond()}
  {
    if (!m_cond)
    {
      throw sdl_error{};
    }
  }

  /**
   * \brief Wakes up one of the threads that are waiting on the condition
   * variable.
   *
   * \return `true` if everything went OK; `false` upon failure.
   *
   * \since 5.0.0
   */
  auto signal() noexcept -> bool
  {
    return SDL_CondSignal(m_cond.get()) == 0;
  }

  /**
   * \brief Wakes up all threads that are waiting on the condition variable.
   *
   * \return `true` if everything went OK; `false` on failure.
   *
   * \since 5.0.0
   */
  auto broadcast() noexcept -> bool
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
   * \return `true` if everything went OK; `false` on failure.
   *
   * \since 5.0.0
   */
  auto wait(mutex& mutex) noexcept -> bool
  {
    return SDL_CondWait(m_cond.get(), mutex.get()) == 0;
  }

  /**
   * \brief Waits until the condition variable is signaled or if the specified
   * amount of time has passed.
   *
   * \pre The mutex must be locked when the function is called!
   *
   * \note This function is implemented by looping with a delay of 1 ms on some
   * platforms, and should be avoided if possible.
   *
   * \param mutex the mutex used to coordinate thread access.
   * \param ms the maximum amount of time to wait.
   *
   * \return `true` if everything went OK; `false` on failure.
   *
   * \since 5.0.0
   */
  auto wait(mutex& mutex, const milliseconds<u32> ms) -> lock_status
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

/// \}

}  // namespace cen

#endif  // CENTURION_CONDITION_HEADER
