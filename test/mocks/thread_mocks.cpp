#include "thread_mocks.hpp"

extern "C" {
// Mutex
DEFINE_FAKE_VOID_FUNC(SDL_DestroyMutex, SDL_mutex*)
DEFINE_FAKE_VALUE_FUNC(SDL_mutex*, SDL_CreateMutex)
DEFINE_FAKE_VALUE_FUNC(int, SDL_LockMutex, SDL_mutex*)
DEFINE_FAKE_VALUE_FUNC(int, SDL_UnlockMutex, SDL_mutex*)

// Semaphore
DEFINE_FAKE_VOID_FUNC(SDL_DestroySemaphore, SDL_sem*)
DEFINE_FAKE_VALUE_FUNC(SDL_sem*, SDL_CreateSemaphore, Uint32)

// Condition
DEFINE_FAKE_VOID_FUNC(SDL_DestroyCond, SDL_cond*)
DEFINE_FAKE_VALUE_FUNC(SDL_cond*, SDL_CreateCond)
}

namespace mocks {

void reset_thread()
{
  RESET_FAKE(SDL_DestroyMutex)
  RESET_FAKE(SDL_CreateMutex)
  RESET_FAKE(SDL_LockMutex)
  RESET_FAKE(SDL_UnlockMutex)

  RESET_FAKE(SDL_DestroySemaphore)
  RESET_FAKE(SDL_CreateSemaphore)

  RESET_FAKE(SDL_DestroyCond)
  RESET_FAKE(SDL_CreateCond)
}

}  // namespace mocks
