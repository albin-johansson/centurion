#pragma once
#include <SDL_mixer.h>
#include <string>
#include "audio_component.h"

namespace centurion {
namespace audio {

/**
\brief The SoundEffect class represents a sound effect. The supported file
extensions are MP3, OGG and FLAC.
*/
class SoundEffect : public AudioComponent {
 private:
  int channel;
  Mix_Chunk* sound;

  void Activate(int nLoops);

 public:
  /**
  \param path - the path of the sound effect file.
  */
  explicit SoundEffect(const std::string& path);

  ~SoundEffect();

  /**
  \brief Plays the sound effect and loops it by the specified number of times.
  \param nLoops - the number of loops that will be played.
  */
  void Loop(int nLoops);

  /**
  \brief Plays the sound effect.
  */
  void Play() override;

  /**
  \brief Stops playing the sound effect.
  */
  void Stop() override;

  /**
  \brief Sets the volume of the sound effect.
  \param volume - the desired volume, in the range [0, 128].
  */
  void SetVolume(int volume) override;

  /**
  \brief Returns the current volume of the sound effect.
  */
  int GetVolume() const override;
};

}  // namespace audio
}  // namespace centurion