#include "mixer_mocks.hpp"

extern "C"
{
  DEFINE_FAKE_VALUE_FUNC(const char*, Mix_GetChunkDecoder, int)
  DEFINE_FAKE_VALUE_FUNC(SDL_bool, Mix_HasChunkDecoder, const char*)
  DEFINE_FAKE_VALUE_FUNC(int, Mix_GetNumChunkDecoders)
}

namespace mocks {

void reset_mixer()
{
  RESET_FAKE(Mix_GetChunkDecoder)
  RESET_FAKE(Mix_HasChunkDecoder)
  RESET_FAKE(Mix_GetNumChunkDecoders)
}

}  // namespace mocks
