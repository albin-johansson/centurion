#include "semaphore.hpp"

#include "exception.hpp"

namespace centurion {

semaphore::semaphore(u32 tokens) : m_semaphore{SDL_CreateSemaphore(tokens)}
{
  if (!m_semaphore) {
    throw sdl_error{"Failed to create semaphore"};
  }
}

auto semaphore::acquire() noexcept -> bool
{
  return SDL_SemWait(m_semaphore.get()) == 0;
}

auto semaphore::acquire(milliseconds<u32> ms) noexcept -> lock_status
{
  return static_cast<lock_status>(
      SDL_SemWaitTimeout(m_semaphore.get(), ms.count()));
}

auto semaphore::try_acquire() noexcept -> lock_status
{
  return static_cast<lock_status>(SDL_SemTryWait(m_semaphore.get()));
}

auto semaphore::release() noexcept -> bool
{
  return SDL_SemPost(m_semaphore.get()) == 0;
}

auto semaphore::tokens() const noexcept -> u32
{
  return SDL_SemValue(m_semaphore.get());
}

}  // namespace centurion
