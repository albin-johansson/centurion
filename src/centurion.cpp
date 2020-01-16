#include "centurion.h"
#include "centurion_exception.h"

namespace centurion {

void Centurion::init_sdl() {
  const auto result = SDL_Init(SDL_INIT_EVERYTHING);
  if (result < 0) {
    throw CenturionException{"Failed to load SDL2! Error: " + std::string{SDL_GetError()}};
  }
}

void Centurion::init_ttf() {
  const auto result = TTF_Init();
  if (result == -1) {
    throw CenturionException{"Failed to load SDL2_ttf! Error: " + std::string{TTF_GetError()}};
  }
}

void Centurion::init_img() {
  const auto flags = IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF | IMG_INIT_WEBP);
  if (!flags) {
    throw CenturionException{"Failed to load SDL2_image! Error: " + std::string{IMG_GetError()}};
  }
}

void Centurion::init_mix() {
  const auto flags = Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_FLAC | MIX_INIT_MID |
      MIX_INIT_MOD | MIX_INIT_OPUS);
  if (!flags) {
    throw CenturionException{"Failed to init SDL2_mixer! Error: " + std::string{Mix_GetError()}};
  }

  if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) == -1) {
    throw CenturionException{"Failed to open audio! Error: " + std::string{Mix_GetError()}};
  }
}

Centurion::Centurion() {
  init();
}

Centurion::~Centurion() noexcept {
  close();
}

void Centurion::init() {
  if (!wasInit) {
    init_sdl();
    init_img();
    init_ttf();
    init_mix();
    wasInit = true;
  }
}

void Centurion::close() noexcept {
  if (wasInit) {
    IMG_Quit();
    TTF_Quit();
    Mix_CloseAudio();
    Mix_Quit();
    SDL_Quit();
    wasInit = false;
  }
}

}
