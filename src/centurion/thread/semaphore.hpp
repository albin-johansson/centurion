#ifndef CENTURION_SEMAPHORE_HEADER
#define CENTURION_SEMAPHORE_HEADER

#include <SDL.h>

#include <memory>  // unique_ptr

#include "../core/exception.hpp"
#include "../core/integers.hpp"
#include "../core/result.hpp"
#include "../core/time.hpp"
#include "lock_status.hpp"

namespace cen {

/// \addtogroup thread
/// \{

/**
 * \class semaphore
 *
 * \brief Represents a semaphore with a set of "tokens" (or permits).
 *
 * \since 5.0.0
 */
class semaphore final
{
 public:
  /**
   * \brief Creates a semaphore with the specified amount of tokens.
   *
   * \param tokens the initial amount of tokens.
   *
   * \throws sdl_error if the semaphore cannot be created.
   *
   * \since 5.0.0
   */
  explicit semaphore(const u32 tokens) : m_semaphore{SDL_CreateSemaphore(tokens)}
  {
    if (!m_semaphore) {
      throw sdl_error{};
    }
  }

  /**
   * \brief Acquires a token from the semaphore.
   *
   * \note This function blocks the calling thread until a token is available.
   *
   * \return `success` if a token was acquired; `failure` otherwise.
   *
   * \since 5.0.0
   */
  auto acquire() noexcept -> result
  {
    return SDL_SemWait(m_semaphore.get()) == 0;
  }

  /**
   * \brief Attempts to acquire a token from the semaphore.
   *
   * \param ms the maximum amount of time to wait.
   *
   * \return `success` if a token was acquired; `timed_out` if no token was acquired in
   * the specified duration; `error` if something goes wrong.
   *
   * \since 5.0.0
   */
  auto acquire(const milliseconds<u32> ms) noexcept(noexcept(ms.count())) -> lock_status
  {
    return static_cast<lock_status>(SDL_SemWaitTimeout(m_semaphore.get(), ms.count()));
  }

  /**
   * \brief Attempts to acquire a token from the semaphore.
   *
   * \return `success` if a token was acquired; `timed_out` if the thread would've been
   * blocked; `error` if something goes wrong.
   *
   * \since 5.0.0
   */
  auto try_acquire() noexcept -> lock_status
  {
    return static_cast<lock_status>(SDL_SemTryWait(m_semaphore.get()));
  }

  /**
   * \brief Returns a token to the semaphore and notifies waiting threads.
   *
   * \return `success` if nothing went wrong; `failure` otherwise.
   *
   * \since 5.0.0
   */
  auto release() noexcept -> result
  {
    return SDL_SemPost(m_semaphore.get()) == 0;
  }

  /**
   * \brief Returns the amount of available tokens.
   *
   * \return the current amount of available tokens.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto tokens() const noexcept -> u32
  {
    return SDL_SemValue(m_semaphore.get());
  }

 private:
  struct deleter final
  {
    void operator()(SDL_sem* semaphore) noexcept
    {
      SDL_DestroySemaphore(semaphore);
    }
  };
  std::unique_ptr<SDL_sem, deleter> m_semaphore;
};

/// \} End of group thread

}  // namespace cen

#endif  // CENTURION_SEMAPHORE_HEADER
