#pragma once
#include <SDL_mixer.h>
#include <string>
#include "centurion.h"

class centurion::audio::SoundEffect {
 private:
  const static int CHANNEL_UNDEFINED = -10;
  int channel;
  bool isPlaying;
  Mix_Chunk* sound;

  void Update();

 public:
  SoundEffect(const std::string& path);

  ~SoundEffect();

  void Play();

  void Stop();

  bool IsPlaying() const { return isPlaying; }
};
