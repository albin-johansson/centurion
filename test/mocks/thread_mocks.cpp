#include "thread_mocks.hpp"

extern "C" {
// Mutex
DEFINE_FAKE_VOID_FUNC(SDL_DestroyMutex, SDL_mutex*)
DEFINE_FAKE_VALUE_FUNC(SDL_mutex*, SDL_CreateMutex)
DEFINE_FAKE_VALUE_FUNC(int, SDL_LockMutex, SDL_mutex*)
DEFINE_FAKE_VALUE_FUNC(int, SDL_UnlockMutex, SDL_mutex*)
}

namespace mocks {

void reset_thread()
{
  RESET_FAKE(SDL_DestroyMutex);
  RESET_FAKE(SDL_CreateMutex);
  RESET_FAKE(SDL_LockMutex);
  RESET_FAKE(SDL_UnlockMutex);
}

}  // namespace mocks
