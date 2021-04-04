#pragma once

#include <SDL.h>
#include <fff.h>

// clang-format off
extern "C" {
// Initialization
DECLARE_FAKE_VALUE_FUNC(int, SDL_Init, Uint32)
DECLARE_FAKE_VALUE_FUNC(int, TTF_Init)
DECLARE_FAKE_VALUE_FUNC(int, IMG_Init, int)
DECLARE_FAKE_VALUE_FUNC(int, Mix_Init, int)
DECLARE_FAKE_VALUE_FUNC(int, Mix_OpenAudio, int, Uint16, int, int)
DECLARE_FAKE_VALUE_FUNC(SDL_Window*, SDL_CreateWindow, const char*, int, int, int, int, Uint32)

// Cleanup
DECLARE_FAKE_VOID_FUNC(SDL_Quit)
DECLARE_FAKE_VOID_FUNC(TTF_Quit)
DECLARE_FAKE_VOID_FUNC(IMG_Quit)
DECLARE_FAKE_VOID_FUNC(Mix_Quit)
DECLARE_FAKE_VOID_FUNC(Mix_CloseAudio)
DECLARE_FAKE_VOID_FUNC(SDL_free, void*);
DECLARE_FAKE_VOID_FUNC(SDL_DestroyWindow, SDL_Window*)
DECLARE_FAKE_VOID_FUNC(SDL_FreeSurface, SDL_Surface*)

// Misc
DECLARE_FAKE_VALUE_FUNC(const char*, SDL_GetError);
DECLARE_FAKE_VALUE_FUNC(SDL_RWops*, SDL_RWFromFile, const char*, const char*)

// Window
DECLARE_FAKE_VALUE_FUNC(Uint32, SDL_GetWindowFlags, SDL_Window*)
}
// clang-format on

namespace mocks {

void reset_core();

}
