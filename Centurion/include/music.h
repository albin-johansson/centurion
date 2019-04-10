#pragma once
#include <SDL_mixer.h>
#include <memory>
#include <string>
#include "audio_component.h"

namespace centurion {
namespace audio {

/**
\brief The Music class represents a music clip. The music clips must be of the
.WAV-format.
*/
class Music : public AudioComponent {
 private:
  Mix_Music* music;
  int volume;

  inline bool IsMusicPlaying() { return Mix_PlayingMusic(); }

 public:
  /**
  \param path - the path of the .WAV-file that the Music instance will
  represent.
  */
  explicit Music(const std::string& path);

  ~Music();

  /**
  \brief Creates and returns a heap allocated Music instance.
  \param path - the path of the .WAV-file that the Music instance will
  represent.
  */
  static std::shared_ptr<centurion::audio::Music> Create(
      const std::string& path);

  /**
  \brief Starts playing the music file by fading it in.
  \param ms - the duration of the fade, in milliseconds.
  */
  void FadeIn(int ms);

  /**
  \brief Stops playing the music file by fading it out.
  \param ms - the duration of the fade, in milliseconds.
  */
  void FadeOut(int ms);

  /**
  \brief Starts playing the music file.
  */
  void Play() override;

  /**
  \brief Stops playing the music file.
  */
  void Stop() override;

  /**
  \brief Assigns the volume of the music file.
  \param volume - the desired volume of the music file, in the range [0, 128].
  */
  void SetVolume(int volume) override;

  /**
  \brief Returns the current volume of the music file.
  */
  int GetVolume() const override;
};

}  // namespace audio
}  // namespace centurion