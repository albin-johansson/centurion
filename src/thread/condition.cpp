#include "condition.hpp"

#include "exception.hpp"
#include "mutex.hpp"

namespace centurion {

condition::condition() : m_cond{SDL_CreateCond()}
{
  if (!m_cond) {
    throw sdl_error{"Failed to create condition variable"};
  }
}

auto condition::signal() noexcept -> bool
{
  return SDL_CondSignal(m_cond.get()) == 0;
}

auto condition::broadcast() noexcept -> bool
{
  return SDL_CondBroadcast(m_cond.get()) == 0;
}

auto condition::wait(mutex& mutex) noexcept -> bool
{
  return SDL_CondWait(m_cond.get(), mutex.get()) == 0;
}

auto condition::wait(mutex& mutex, milliseconds<u32> ms) noexcept -> lock_status
{
  return static_cast<lock_status>(
      SDL_CondWaitTimeout(m_cond.get(), mutex.get(), ms.count()));
}

}  // namespace centurion
