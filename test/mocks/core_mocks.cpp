#include "core_mocks.hpp"

#include <array>  // array

#include "core/integers.hpp"

// clang-format off
extern "C" {
DEFINE_FAKE_VALUE_FUNC(int, SDL_Init, Uint32)
DEFINE_FAKE_VALUE_FUNC(int, TTF_Init)
DEFINE_FAKE_VALUE_FUNC(int, IMG_Init, int)
DEFINE_FAKE_VALUE_FUNC(int, Mix_Init, int)
DEFINE_FAKE_VALUE_FUNC(int, Mix_OpenAudio, int, Uint16, int, int)
DEFINE_FAKE_VALUE_FUNC(SDL_Window*, SDL_CreateWindow, const char*, int, int, int, int, Uint32)

DEFINE_FAKE_VOID_FUNC(SDL_Quit)
DEFINE_FAKE_VOID_FUNC(TTF_Quit)
DEFINE_FAKE_VOID_FUNC(IMG_Quit)
DEFINE_FAKE_VOID_FUNC(Mix_Quit)
DEFINE_FAKE_VOID_FUNC(Mix_CloseAudio)
DEFINE_FAKE_VOID_FUNC(SDL_free, void*);
DEFINE_FAKE_VOID_FUNC(SDL_DestroyWindow, SDL_Window*)
DEFINE_FAKE_VOID_FUNC(SDL_FreeSurface, SDL_Surface*)

DEFINE_FAKE_VALUE_FUNC(const char*, SDL_GetError);
DEFINE_FAKE_VALUE_FUNC(SDL_RWops*, SDL_RWFromFile, const char*, const char*)

DEFINE_FAKE_VALUE_FUNC(Uint32, SDL_GetWindowFlags, SDL_Window*)
}
// clang-format on

namespace mocks {

void reset_core()
{
  RESET_FAKE(SDL_Init);
  RESET_FAKE(TTF_Init);
  RESET_FAKE(IMG_Init);
  RESET_FAKE(Mix_OpenAudio);
  RESET_FAKE(SDL_CreateWindow);

  RESET_FAKE(SDL_Quit);
  RESET_FAKE(TTF_Quit);
  RESET_FAKE(IMG_Quit);
  RESET_FAKE(Mix_Quit);
  RESET_FAKE(Mix_CloseAudio);
  RESET_FAKE(SDL_free);
  RESET_FAKE(SDL_DestroyWindow);
  RESET_FAKE(SDL_FreeSurface);

  RESET_FAKE(SDL_GetError);
  RESET_FAKE(SDL_RWFromFile);

  RESET_FAKE(SDL_GetWindowFlags)

  std::array values{"dummy"};
  SET_RETURN_SEQ(SDL_GetError, values.data(), cen::isize(values));
}

}  // namespace mocks
