#pragma once
#include <SDL_mixer.h>
#include <string>
#include "audio_component.h"

namespace centurion {
namespace audio {

class SoundEffect : public AudioComponent {
 private:
  int channel;
  Mix_Chunk* sound;

  void Activate(int nLoops);

 public:
  explicit SoundEffect(const std::string& path);

  ~SoundEffect();

  void Loop(int nLoops);

  void Play() override;

  void Stop() override;

  void SetVolume(int volume) override;

  int GetVolume() const override;
};

}  // namespace audio
}  // namespace centurion