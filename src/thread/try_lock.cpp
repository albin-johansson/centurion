#include "try_lock.hpp"

namespace cen {

try_lock::try_lock(mutex& mutex) noexcept
    : m_mutex{&mutex}, m_status{mutex.try_lock()}
{}

try_lock::~try_lock() noexcept
{
  if (m_status == lock_status::success) {
    m_mutex->unlock();
  }
}

auto try_lock::get_status() const noexcept -> lock_status
{
  return m_status;
}

auto try_lock::success() const noexcept -> bool
{
  return get_status() == lock_status::success;
}

auto try_lock::timed_out() const noexcept -> bool
{
  return get_status() == lock_status::timed_out;
}

auto try_lock::error() const noexcept -> bool
{
  return get_status() == lock_status::error;
}

try_lock::operator bool() const noexcept
{
  return success();
}

}  // namespace cen