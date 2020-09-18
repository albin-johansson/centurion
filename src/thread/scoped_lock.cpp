#include "scoped_lock.hpp"

#include "exception.hpp"
#include "mutex.hpp"

namespace cen {

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

}  // namespace cen
