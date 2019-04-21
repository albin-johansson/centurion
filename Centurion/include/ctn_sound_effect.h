#pragma once
#include <SDL_mixer.h>
#include <memory>
#include <string>
#include "ctn_audio_component.h"

namespace centurion {
namespace audio {

class SoundEffect;
typedef std::shared_ptr<SoundEffect> SoundEffect_sptr;
typedef std::unique_ptr<SoundEffect> SoundEffect_uptr;
typedef std::weak_ptr<SoundEffect> SoundEffect_wptr;

/**
\brief The SoundEffect class represents a sound effect. The supported file
extensions are MP3, OGG and FLAC.
\since 1.0.0
*/
class SoundEffect : public IAudioComponent {
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
  \since 1.0.0
  */
  void Loop(int nLoops);

  /**
  \brief Plays the sound effect.
  \since 1.0.0
  */
  void Play() noexcept override;

  /**
  \brief Stops playing the sound effect.
  \since 1.0.0
  */
  void Stop() noexcept override;

  /**
  \brief Sets the volume of the sound effect.
  \param volume - the desired volume, in the range [0, 128].
  \since 1.0.0
  */
  void SetVolume(int volume) override;

  /**
  \brief Returns the current volume of the sound effect.
  \since 1.0.0
  */
  int GetVolume() const noexcept override;

  /**
  \brief Returns a shared pointer that points to a SoundEffect instance.
  \param path - the path of the sound effect file.
  \since 1.1.0
  */
  static SoundEffect_sptr CreateShared(const std::string& path);

  /**
  \brief Returns a unique pointer that points to a SoundEffect instance.
  \param path - the path of the sound effect file.
  \since 1.1.0
  */
  static SoundEffect_uptr CreateUnique(const std::string& path);

  /**
  \brief Returns a weak pointer that points to a SoundEffect instance.
  \param path - the path of the sound effect file.
  \since 1.1.0
  */
  static SoundEffect_wptr CreateWeak(const std::string& path);
};

}  // namespace audio
}  // namespace centurion