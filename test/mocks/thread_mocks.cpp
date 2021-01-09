#include "thread_mocks.hpp"

extern "C" {
// Thread
DEFINE_FAKE_VALUE_FUNC(SDL_Thread*,
                       SDL_CreateThread,
                       SDL_ThreadFunction,
                       const char*,
                       void*,
                       pfnSDL_CurrentBeginThread,
                       pfnSDL_CurrentEndThread);
DEFINE_FAKE_VOID_FUNC(SDL_DetachThread, SDL_Thread*)
DEFINE_FAKE_VOID_FUNC(SDL_WaitThread, SDL_Thread*, int*)

// Mutex
DEFINE_FAKE_VOID_FUNC(SDL_DestroyMutex, SDL_mutex*)
DEFINE_FAKE_VALUE_FUNC(SDL_mutex*, SDL_CreateMutex)
DEFINE_FAKE_VALUE_FUNC(int, SDL_LockMutex, SDL_mutex*)
DEFINE_FAKE_VALUE_FUNC(int, SDL_UnlockMutex, SDL_mutex*)

// Semaphore
DEFINE_FAKE_VOID_FUNC(SDL_DestroySemaphore, SDL_sem*)
DEFINE_FAKE_VALUE_FUNC(SDL_sem*, SDL_CreateSemaphore, Uint32)
}

namespace mocks {

void reset_thread()
{
  RESET_FAKE(SDL_CreateThread);
  RESET_FAKE(SDL_DetachThread);
  RESET_FAKE(SDL_WaitThread);

  RESET_FAKE(SDL_DestroyMutex);
  RESET_FAKE(SDL_CreateMutex);
  RESET_FAKE(SDL_LockMutex);
  RESET_FAKE(SDL_UnlockMutex);

  RESET_FAKE(SDL_DestroySemaphore);
  RESET_FAKE(SDL_CreateSemaphore);
}

}  // namespace mocks
