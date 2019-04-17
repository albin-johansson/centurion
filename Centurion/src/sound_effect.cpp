#include "sound_effect.h"
#include <stdio.h>
#include <stdexcept>
#include "null_checker.h"

#define UNDEFINED_CHANNEL ((int)(-1))

using centurion::tools::NullChecker;

namespace centurion {
namespace audio {

SoundEffect::SoundEffect(const std::string& path) {
  sound = Mix_LoadWAV(path.c_str());
  if (sound == nullptr) {
    printf("%s", Mix_GetError());
    throw std::invalid_argument("Null sound effect!");
  } else {
    channel = UNDEFINED_CHANNEL;
    SetVolume(MIX_MAX_VOLUME / 2);
  }
}

SoundEffect::~SoundEffect() {
  Stop();
  Mix_FreeChunk(sound);
}

std::shared_ptr<SoundEffect> SoundEffect::Create(const std::string& path) {
  return std::make_shared<SoundEffect>(path);
}

void SoundEffect::Activate(int nLoops) {
  if (channel != UNDEFINED_CHANNEL) {
    Mix_PlayChannel(channel, sound, nLoops);
  } else {
    channel = Mix_PlayChannel(UNDEFINED_CHANNEL, sound, nLoops);
  }
}

void SoundEffect::Play() noexcept { Activate(0); }

void SoundEffect::Loop(int nLoops) {
  if (nLoops < -1) {
    throw std::invalid_argument("Loop value is less than -1!");
  } else {
    Activate(nLoops);
  }
}

void SoundEffect::Stop() noexcept {
  if ((channel != UNDEFINED_CHANNEL) && Mix_Playing(channel)) {
    Mix_Pause(channel);
    channel = UNDEFINED_CHANNEL;
  }
}

void SoundEffect::SetVolume(int volume) {
  if (volume < 0 || volume > MIX_MAX_VOLUME) {
    throw std::invalid_argument("Invalid volume argument!");
  } else {
    Mix_VolumeChunk(sound, volume);
  }
}

int SoundEffect::GetVolume() const noexcept { return sound->volume; }

}  // namespace audio
}  // namespace centurion

#undef UNDEFINED_CHANNEL