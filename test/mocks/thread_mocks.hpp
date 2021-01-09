#pragma once

#include <SDL.h>
#include <fff.h>

extern "C" {
// Mutex
DECLARE_FAKE_VOID_FUNC(SDL_DestroyMutex, SDL_mutex*)
DECLARE_FAKE_VALUE_FUNC(SDL_mutex*, SDL_CreateMutex)
DECLARE_FAKE_VALUE_FUNC(int, SDL_LockMutex, SDL_mutex*)
DECLARE_FAKE_VALUE_FUNC(int, SDL_UnlockMutex, SDL_mutex*)
}

namespace mocks {

void reset_thread();

}