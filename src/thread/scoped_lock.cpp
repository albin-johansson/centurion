#include "scoped_lock.hpp"

#include "centurion_exception.hpp"
#include "mutex.hpp"

namespace centurion {

scoped_lock::scoped_lock(mutex& mutex) : m_mutex{&mutex}
{
  if (!mutex.lock()) {
    throw sdl_error{"Couldn't lock mutex"};
  }
}

scoped_lock::~scoped_lock() noexcept
{
  m_mutex->unlock();
}

}  // namespace centurion
