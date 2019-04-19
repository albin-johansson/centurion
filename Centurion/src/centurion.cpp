#include "centurion.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>

#define SDL_MIXER_ERROR_CODE 0
#define SDL_IMAGE_ERROR_CODE 0
#define SDL_TTF_ERROR_CODE -1

using std::exception;
using std::string;

namespace centurion {

bool Centurion::isInit = false;

void Centurion::InitCore() {
  int result = SDL_Init(SDL_INIT_EVERYTHING);
  if (result < 0) {
    Centurion::ThrowInitializationException(SDL_GetError());
  }
}

void Centurion::InitSDLImage() {
  int result =
      IMG_Init(IMG_InitFlags::IMG_INIT_PNG | IMG_InitFlags::IMG_INIT_JPG);
  if (result == SDL_IMAGE_ERROR_CODE) {
    Centurion::ThrowInitializationException(IMG_GetError());
  }
}

void Centurion::InitSDLMixer() {
  int result =
      Mix_Init(MIX_InitFlags::MIX_INIT_MP3 | MIX_InitFlags::MIX_INIT_OGG |
               MIX_InitFlags::MIX_INIT_FLAC);

  if ((Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) ||
      (result == SDL_MIXER_ERROR_CODE)) {
    Centurion::ThrowInitializationException(Mix_GetError());
  }
}

void Centurion::InitSDLTTF() {
  int result = TTF_Init();
  if (result == SDL_TTF_ERROR_CODE) {
    Centurion::ThrowInitializationException(TTF_GetError());
  }
}

void Centurion::ThrowInitializationException(const string error) {
  string str = "Failed to initialize Centurion! Error: " + error;
  throw exception(str.c_str());
}

void Centurion::Init() {
  if (!isInit) {
    Centurion::InitCore();
    Centurion::InitSDLImage();
    Centurion::InitSDLMixer();
    Centurion::InitSDLTTF();
    isInit = true;
  }
}

void Centurion::Close() noexcept {
  if (isInit) {
    IMG_Quit();
    TTF_Quit();
    Mix_CloseAudio();
    Mix_Quit();
    SDL_Quit();
    isInit = false;
  }
}

}  // namespace centurion

#undef SDL_MIXER_ERROR_CODE
#undef SDL_IMAGE_ERROR_CODE
#undef SDL_TTF_ERROR_CODE