#include "music.h"
#include <stdexcept>
#include <string>
#include "null_checker.h"

using centurion::tools::NullChecker;

namespace centurion {
namespace audio {

Music::Music(const std::string& path) {
  music = Mix_LoadMUS(path.c_str());
  if (NullChecker::IsNull(music)) {
    throw std::exception("Failed to load music!");
  } else {
    volume = MIX_MAX_VOLUME / 2;
  }
}

Music::~Music() { Mix_FreeMusic(music); }

void Music::ApplyVolume() { Mix_VolumeMusic(volume); }

void Music::Play() {
  if (IsMusicPlaying()) {
    Stop();
  }
  Mix_PlayMusic(music, -1);
  ApplyVolume();
}

void Music::FadeIn(int ms) {
  if (ms <= 0) {
    throw std::invalid_argument("Invalid fade in duration argument!");
  } else {
    if (IsMusicPlaying()) {
      Stop();
    }
    Mix_FadeInMusic(music, -1, ms);
    ApplyVolume();
  }
}

void Music::Stop() {
  if (IsMusicPlaying()) {
    Mix_PauseMusic();
  }
}

void Music::FadeOut(int ms) {
  if (ms <= 0) {
    throw std::invalid_argument("Invalid fade out duration argument!");
  } else {
    if (IsMusicPlaying()) {
      Mix_FadeOutMusic(ms);
    }
  }
}

void Music::SetVolume(int volume) {
  if (volume < 0 || volume > MIX_MAX_VOLUME) {
    throw std::invalid_argument("Invalid music volume argument!");
  } else {
    this->volume = volume;
  }
}

}  // namespace audio
}  // namespace centurion