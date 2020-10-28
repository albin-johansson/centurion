#include "mutex.hpp"

#include "exception.hpp"

namespace cen {

mutex::mutex() : m_mutex{SDL_CreateMutex()}
{
  if (!m_mutex) {
    throw sdl_error{"Failed to create mutex"};
  }
}

auto mutex::lock() noexcept -> bool
{
  return SDL_LockMutex(get()) == 0;
}

auto mutex::try_lock() noexcept -> lock_status
{
  return static_cast<lock_status>(SDL_TryLockMutex(get()));
}

auto mutex::unlock() noexcept -> bool
{
  return SDL_UnlockMutex(get()) == 0;
}

auto mutex::get() noexcept -> SDL_mutex*
{
  return m_mutex.get();
}

}  // namespace cen
