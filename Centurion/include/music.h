#pragma once
#include <SDL_mixer.h>
#include <string>
#include "audio_component.h"

// TODO possibly use Jukebox class since only one Music instance can be used at
// a time
namespace centurion {
namespace audio {

class Music : public AudioComponent {
 private:
  Mix_Music* music;
  int volume;

  inline bool IsMusicPlaying() { return Mix_PlayingMusic(); }

 public:
  explicit Music(const std::string& path);

  ~Music();

  void FadeIn(int ms);

  void FadeOut(int ms);

  void Play() override;

  void Stop() override;

  void SetVolume(int volume) override;

  int GetVolume() const override;
};

}  // namespace audio
}  // namespace centurion