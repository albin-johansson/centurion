#pragma once

#include <SDL.h>
#include <fff.h>

// clang-format off
extern "C" {
// Thread
#undef SDL_CreateThread  // Don't do this at home
DECLARE_FAKE_VALUE_FUNC(SDL_Thread*,
                        SDL_CreateThread,
                        SDL_ThreadFunction,
                        const char*,
                        void*,
                        pfnSDL_CurrentBeginThread,
                        pfnSDL_CurrentEndThread);
DECLARE_FAKE_VOID_FUNC(SDL_DetachThread, SDL_Thread*)
DECLARE_FAKE_VOID_FUNC(SDL_WaitThread, SDL_Thread*, int*)

// Mutex
DECLARE_FAKE_VOID_FUNC(SDL_DestroyMutex, SDL_mutex*)
DECLARE_FAKE_VALUE_FUNC(SDL_mutex*, SDL_CreateMutex)
DECLARE_FAKE_VALUE_FUNC(int, SDL_LockMutex, SDL_mutex*)
DECLARE_FAKE_VALUE_FUNC(int, SDL_UnlockMutex, SDL_mutex*)

// Semaphore
DECLARE_FAKE_VOID_FUNC(SDL_DestroySemaphore, SDL_sem*)
DECLARE_FAKE_VALUE_FUNC(SDL_sem*, SDL_CreateSemaphore, Uint32)
}
// clang-format on

namespace mocks {

void reset_thread();

}