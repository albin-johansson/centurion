#include "centurion.h"
#include "centurion_exception.h"

namespace centurion {

void Centurion::init_sdl() {
  if (const auto result = SDL_Init(SDL_INIT_EVERYTHING); result < 0) {
    throw CenturionException{"Failed to load SDL2! Error: " + std::string{SDL_GetError()}};
  }
}

void Centurion::init_ttf() {
  if (const auto result = TTF_Init(); result == -1) {
    throw CenturionException{"Failed to load SDL2_ttf! Error: " + std::string{TTF_GetError()}};
  }
}

void Centurion::init_img() {
  if (const auto flags = IMG_Init(img_flags); !flags) {
    throw CenturionException{"Failed to load SDL2_image! Error: " + std::string{IMG_GetError()}};
  }
}

void Centurion::init_mix() {
  if (const auto flags = Mix_Init(mix_flags); !flags) {
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
#ifndef CENTURION_NOAUDIO
    init_mix();
#endif
    wasInit = true;
  }
}

void Centurion::close() noexcept {
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

}
