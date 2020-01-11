#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>

int main(int argc, char** argv) {
  SDL_Init(SDL_INIT_EVERYTHING);
  IMG_Init(IMG_INIT_PNG);
  Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG);
  if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
    std::cerr << "Failed to open audio device! Error: " << SDL_GetError() << "\n";
  }
  TTF_Init();

  int result = Catch::Session().run(argc, argv);

  IMG_Quit();
  Mix_CloseAudio();
  Mix_Quit();
  TTF_Quit();
  SDL_Quit();
  return result;
}