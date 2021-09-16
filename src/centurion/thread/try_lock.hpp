#ifndef CENTURION_TRY_LOCK_HEADER
#define CENTURION_TRY_LOCK_HEADER

#include <SDL.h>

#include "../compiler/features.hpp"
#include "lock_status.hpp"
#include "mutex.hpp"

namespace cen {

/// \addtogroup thread
/// \{

/**
 * \class try_lock
 *
 * \brief Represents an RAII-style non-blocking lock that automatically unlocks the
 * associated mutex upon destruction.
 *
 * \since 5.0.0
 */
class try_lock final
{
 public:
  /**
   * \brief Attempts to lock the supplied mutex.
   *
   * \param mutex the mutex that will be locked.
   *
   * \since 5.0.0
   */
  CENTURION_NODISCARD_CTOR explicit try_lock(mutex& mutex) noexcept
      : m_mutex{&mutex}
      , m_status{mutex.try_lock()}
  {}

  try_lock(const try_lock&) = delete;

  auto operator=(const try_lock&) -> try_lock& = delete;

  /**
   * \brief Unlocks the associated mutex if it was successfully locked.
   *
   * \since 5.0.0
   */
  ~try_lock() noexcept
  {
    if (m_status == lock_status::success) {
      m_mutex->unlock();
    }
  }

  /**
   * \brief Returns the result of trying to lock the associated mutex.
   *
   * \return the lock status.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto get_status() const noexcept -> lock_status
  {
    return m_status;
  }

  /**
   * \brief Indicates whether or not the mutex was successfully locked.
   *
   * \return `true` if the mutex was locked; `false` otherwise.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto success() const noexcept -> bool
  {
    return get_status() == lock_status::success;
  }

  /**
   * \brief Indicates whether or not the lock timed out whilst trying to lock the mutex.
   *
   * \return `true` if the locking timed out; `false` otherwise.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto timed_out() const noexcept -> bool
  {
    return get_status() == lock_status::timed_out;
  }

  /**
   * \brief Indicates whether or not there was an error whilst locking the mutex.
   *
   * \return `true` if something went wrong whilst locking the mutex; `false` otherwise.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto error() const noexcept -> bool
  {
    return get_status() == lock_status::error;
  }

  /// \copydoc success()
  [[nodiscard]] explicit operator bool() const noexcept
  {
    return success();
  }

 private:
  mutex* m_mutex{};
  lock_status m_status{};
};

/// \} End of group thread

}  // namespace cen

#endif  // CENTURION_TRY_LOCK_HEADER
