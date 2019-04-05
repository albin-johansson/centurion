#pragma once
#include <SDL_mixer.h>
#include <string>

namespace centurion {
namespace audio {

class SoundEffect {
 private:
  int channel;
  Mix_Chunk* sound;

  void Activate(int nLoops);

 public:
  SoundEffect(const std::string& path);

  ~SoundEffect();

  void Play();

  void Loop(int nLoops);

  void Stop();

  void SetVolume(int volume);

  int GetVolume() const;
};

}  // namespace audio
}  // namespace centurion