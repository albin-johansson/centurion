#include "jukebox.h"
#include <SDL_mixer.h>
#include <stdexcept>

using centurion::audio::Jukebox;
using std::invalid_argument;

//TODO

void Jukebox::PlayMusic() { Mix_PlayMusic(nullptr, 0); }

void Jukebox::PauseMusic() { Mix_PauseMusic(); }

void Jukebox::StopMusic() {}

void Jukebox::SetVolume(int volume) {
  if (volume < 0 || volume > 128) {
    throw invalid_argument("Invalid volume!");
  } else {
    Mix_VolumeMusic(volume);
  }
}