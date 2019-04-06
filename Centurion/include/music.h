#pragma once
#include <SDL_mixer.h>
#include <string>

// TODO possibly use Jukebox class since only one Music instance can be used at
// a time
namespace centurion {
namespace audio {

class Music {
 private:
  Mix_Music* music;
  int volume;

  inline bool IsMusicPlaying() { return Mix_PlayingMusic(); }

  void ApplyVolume();

 public:
  explicit Music(const std::string& path);

  ~Music();

  void Play();

  void Stop();

  void FadeIn(int ms);

  void FadeOut(int ms);

  void SetVolume(int volume);

  inline int GetVolume() const { return volume; }
};

}  // namespace audio
}  // namespace centurion