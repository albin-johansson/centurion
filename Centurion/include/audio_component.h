#pragma once
#include <memory>

namespace centurion {
namespace audio {

/**
\brief The AudioComponent class represents some sort of audio file.
\since 1.0.0
*/
class AudioComponent {
 protected:
  AudioComponent() = default;

 public:
  virtual ~AudioComponent() = default;

  /**
  \brief Start playing the audio file.
  \since 1.0.0
  */
  virtual void Play() = 0;

  /**
  \brief Stop playing the audio file.
  \since 1.0.0
  */
  virtual void Stop() = 0;

  /**
  \brief Assigns the volume of the audio file.
  \param volume - the desired volume of the audio file, in the range [0, 128].
  \since 1.0.0
  */
  virtual void SetVolume(int volume) = 0;

  /**
  \brief Returns the current volume of the audio file.
  \since 1.0.0
  */
  virtual int GetVolume() const = 0;
};

typedef std::shared_ptr<centurion::audio::AudioComponent> AudioComponent_sptr;
typedef std::unique_ptr<centurion::audio::AudioComponent> AudioComponent_uptr;
typedef std::weak_ptr<centurion::audio::AudioComponent> AudioComponent_wptr;

}  // namespace audio
}  // namespace centurion