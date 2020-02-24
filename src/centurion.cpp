#ifndef CENTURION_CENTURION_SOURCE
#define CENTURION_CENTURION_SOURCE

#include "centurion.h"

#include "centurion_exception.h"

namespace centurion {

bool Centurion::wasInit = false;

CENTURION_DEF void Centurion::init_sdl()
{
#ifndef CENTURION_NOAUDIO
  const auto result = SDL_Init(SDL_INIT_EVERYTHING);
  if (result < 0) {
    throw CenturionException{"Failed to load SDL2! " + Error::msg()};
  }
#else
  const auto result = SDL_Init(SDL_INIT_EVERYTHING & ~SDL_INIT_AUDIO);
  if (result < 0) {
    throw CenturionException{"Failed to load SDL2! " + Error::msg()};
  }
#endif
}

CENTURION_DEF void Centurion::init_ttf()
{
  const auto result = TTF_Init();
  if (result == -1) {
    throw CenturionException{"Failed to load SDL2_ttf! " + Error::msg()};
  }
}

CENTURION_DEF void Centurion::init_img()
{
  const auto flags = IMG_Init(img_flags);
  if (!flags) {
    throw CenturionException{"Failed to load SDL2_image! " + Error::msg()};
  }
}

CENTURION_DEF void Centurion::init_mix()
{
  const auto flags = Mix_Init(mix_flags);
  if (!flags) {
    throw CenturionException{"Failed to init SDL2_mixer! " + Error::msg()};
  }

  if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,
                    MIX_DEFAULT_FORMAT,
                    MIX_DEFAULT_CHANNELS,
                    4096) == -1) {
    throw CenturionException{"Failed to open audio! " + Error::msg()};
  }
}

CENTURION_DEF Centurion::Centurion()
{
  init();
}

CENTURION_DEF Centurion::~Centurion() noexcept
{
  close();
}

CENTURION_DEF void Centurion::init()
{
  if (!wasInit) {
    init_sdl();
    init_img();
    init_ttf();
#ifndef CENTURION_NOAUDIO
    init_mix();
#endif
    wasInit = true;
  }
}

CENTURION_DEF void Centurion::close() noexcept
{
  if (wasInit) {
    IMG_Quit();
    TTF_Quit();
#ifndef CENTURION_NOAUDIO
    Mix_CloseAudio();
    Mix_Quit();
#endif
    SDL_Quit();

    wasInit = false;
  }
}

}  // namespace centurion

#endif  // CENTURION_CENTURION_SOURCE