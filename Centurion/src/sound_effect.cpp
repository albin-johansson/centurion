#include "sound_effect.h"

using centurion::audio::SoundEffect;

SoundEffect::SoundEffect(const std::string& path) {
  channel = SoundEffect::CHANNEL_UNDEFINED;
  isPlaying = false;

  Mix_LoadWAV(path.c_str());
  sound = nullptr;
}

SoundEffect::~SoundEffect() { Mix_FreeChunk(sound); }

void SoundEffect::Update() {
  if (isPlaying && !Mix_Playing(channel)) {
    isPlaying = false;
    channel = SoundEffect::CHANNEL_UNDEFINED;
  }
}

void SoundEffect::Play() {
  Update();
  if (!isPlaying) {
    channel = Mix_PlayChannel(-1, sound, 0);
    isPlaying = true;
  }
}

void SoundEffect::Stop() {
  if (isPlaying) {
    Mix_HaltChannel(channel);
    isPlaying = false;
    channel = SoundEffect::CHANNEL_UNDEFINED;
  }
}