#pragma once

#include <SDL.h>
#include <fff.h>

extern "C"
{
  DECLARE_FAKE_VALUE_FUNC(const char*, Mix_GetChunkDecoder, int)
  DECLARE_FAKE_VALUE_FUNC(SDL_bool, Mix_HasChunkDecoder, const char*)
  DECLARE_FAKE_VALUE_FUNC(int, Mix_GetNumChunkDecoders)
}

namespace mocks {

void reset_mixer();

}
