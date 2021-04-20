#ifndef CENTURION_SCOPED_LOCK_HEADER
#define CENTURION_SCOPED_LOCK_HEADER

#include <SDL.h>

#include "../core/exception.hpp"
#include "mutex.hpp"

namespace cen {

/// \addtogroup thread
/// \{

/**
 * \class scoped_lock
 *
 * \brief Represents an RAII-style blocking lock that automatically unlocks the
 * associated mutex upon destruction.
 *
 * \remarks This class is purposefully similar to `std::scoped_lock`.
 *
 * \since 5.0.0
 *
 * \headerfile scoped_lock.hpp
 */
class scoped_lock final
{
 public:
  /**
   * \brief Attempts to lock the supplied mutex.
   *
   * \param mutex the mutex that will be locked.
   *
   * \throws sdl_error if the mutex can't be locked.
   *
   * \since 5.0.0
   */
  explicit scoped_lock(mutex& mutex) : m_mutex{&mutex}
  {
    if (!mutex.lock())
    {
      throw sdl_error{};
    }
  }

  scoped_lock(const scoped_lock&) = delete;

  auto operator=(const scoped_lock&) -> scoped_lock& = delete;

  /**
   * \brief Unlocks the associated mutex.
   *
   * \since 5.0.0
   */
  ~scoped_lock() noexcept
  {
    m_mutex->unlock();
  }

 private:
  mutex* m_mutex{};
};

/// \} End of group thread

}  // namespace cen

#endif  // CENTURION_SCOPED_LOCK_HEADER
