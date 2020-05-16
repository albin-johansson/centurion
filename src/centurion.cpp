#ifndef CENTURION_CENTURION_SOURCE
#define CENTURION_CENTURION_SOURCE

#include "centurion.h"

#include "error.h"

namespace centurion {

CENTURION_DEF
void Centurion::init_sdl()
{
  const auto result = SDL_Init(cfg.coreFlags);
  if (result < 0) {
    throw Error::from_core("Failed to load SDL2!");
  }
}

CENTURION_DEF
void Centurion::init_ttf()
{
  const auto result = TTF_Init();
  if (result == -1) {
    throw Error::from_ttf("Failed to load SDL2_ttf!");
  }
}

CENTURION_DEF
void Centurion::init_img()
{
  const auto flags = IMG_Init(cfg.imageFlags);
  if (!flags) {
    throw Error::from_image("Failed to load SDL2_image!");
  }
}

CENTURION_DEF
void Centurion::init_mix()
{
  const auto flags = Mix_Init(cfg.mixerFlags);
  if (!flags) {
    throw Error::from_mixer("Failed to load SDL2_mixer!");
  }

  if (Mix_OpenAudio(cfg.mixerFreq,
                    cfg.mixerFormat,
                    cfg.mixerChannels,
                    cfg.mixerChunkSize) == -1) {
    throw Error::from_mixer("Failed to open audio!");
  }
}

CENTURION_DEF
Centurion::Centurion()
{
  init();
}

CENTURION_DEF
Centurion::Centurion(const CenturionConfig& cfg_) : cfg{cfg_}
{
  init();
}

CENTURION_DEF
Centurion::~Centurion() noexcept
{
  close();
}

CENTURION_DEF
void Centurion::init()
{
  if (cfg.initCore) {
    init_sdl();
  }

  if (cfg.initImage) {
    init_img();
  }

  if (cfg.initTTF) {
    init_ttf();
  }

  if (cfg.initMixer) {
    init_mix();
  }
}

CENTURION_DEF
void Centurion::close() noexcept
{
  if (cfg.initImage) {
    IMG_Quit();
  }

  if (cfg.initTTF) {
    TTF_Quit();
  }

  if (cfg.initMixer) {
    Mix_CloseAudio();
    Mix_Quit();
  }

  if (cfg.initCore) {
    SDL_Quit();
  }
}

}  // namespace centurion

#endif  // CENTURION_CENTURION_SOURCE