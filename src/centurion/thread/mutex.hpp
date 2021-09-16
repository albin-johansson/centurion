#ifndef CENTURION_MUTEX_HEADER
#define CENTURION_MUTEX_HEADER

#include <SDL.h>

#include <memory>  // unique_ptr

#include "../core/exception.hpp"
#include "../core/result.hpp"
#include "lock_status.hpp"

namespace cen {

/// \addtogroup thread
/// \{

/**
 * \class mutex
 *
 * \brief Represents a recursive mutex.
 *
 * \details The fact that the mutex is recursive mutex means that it's possible to nest
 * lock and unlock calls with the same mutex.
 *
 * \since 5.0.0
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
   * \throws sdl_error if the mutex cannot be created.
   *
   * \since 5.0.0
   */
  mutex() : m_mutex{SDL_CreateMutex()}
  {
    if (!m_mutex) {
      throw sdl_error{};
    }
  }

  /**
   * \brief Attempts to lock the mutex, blocks if the mutex isn't available.
   *
   * \return `success` if the mutex was successfully locked; `failure` otherwise.
   *
   * \since 5.0.0
   */
  auto lock() noexcept -> result
  {
    return SDL_LockMutex(get()) == 0;
  }

  /**
   * \brief Attempts to lock the mutex, returns if the mutex isn't available.
   *
   * \return the result of the operation.
   *
   * \since 5.0.0
   */
  auto try_lock() noexcept -> lock_status
  {
    return static_cast<lock_status>(SDL_TryLockMutex(get()));
  }

  /**
   * \brief Attempts to unlock the mutex.
   *
   * \return `success` if the mutex was successfully unlocked; `failure` otherwise.
   *
   * \since 5.0.0
   */
  auto unlock() noexcept -> result
  {
    return SDL_UnlockMutex(get()) == 0;
  }

  /**
   * \brief Returns a pointer to the associated SDL mutex.
   *
   * \return a pointer to the internal mutex.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto get() noexcept -> SDL_mutex*
  {
    return m_mutex.get();
  }

 private:
  struct deleter final
  {
    void operator()(SDL_mutex* mutex) noexcept
    {
      SDL_DestroyMutex(mutex);
    }
  };
  std::unique_ptr<SDL_mutex, deleter> m_mutex;

#ifdef CENTURION_MOCK_FRIENDLY_MODE

 public:
  explicit mutex(int){};
#endif  // CENTURION_MOCK_FRIENDLY_MODE
};

/// \} End of group thread

}  // namespace cen

#endif  // CENTURION_MUTEX_HEADER
