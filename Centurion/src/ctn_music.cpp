#include "ctn_music.h"
#include <stdexcept>
#include <string>

namespace centurion {
namespace audio {

Music::Music(const std::string& path) {
  music = Mix_LoadMUS(path.c_str());
  if (music == nullptr) {
    throw std::exception("Failed to load music!");
  } else {
    volume = MIX_MAX_VOLUME / 2;
  }
}

Music::~Music() {
  Stop();
  Mix_FreeMusic(music);
}

void Music::Play() noexcept {
  if (IsMusicPlaying()) {
    Stop();
  }
  Mix_PlayMusic(music, -1);
}

void Music::FadeIn(int ms) {
  if (ms <= 0) {
    throw std::invalid_argument("Invalid fade in duration argument!");
  } else {
    if (IsMusicPlaying()) {
      Stop();
    }
    Mix_FadeInMusic(music, -1, ms);
  }
}

void Music::Stop() noexcept {
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
    Mix_VolumeMusic(volume);
    this->volume = volume;
  }
}

int Music::GetVolume() const noexcept { return volume; }

Music_sptr Music::CreateShared(const std::string& path) {
  return std::make_shared<Music>(path);
}

Music_uptr Music::CreateUnique(const std::string& path) {
  return std::make_unique<Music>(path);
}

Music_wptr Music::CreateWeak(const std::string& path) {
  return CreateShared(path);
}

}  // namespace audio
}  // namespace centurion