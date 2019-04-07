#pragma once

namespace centurion {
namespace audio {

/**
\brief The AudioComponent class represents some sort of audio file.
*/
class AudioComponent {
 protected:
  AudioComponent() = default;

 public:
  virtual ~AudioComponent() = default;

  /**
  \brief Start playing the audio file.
  */
  virtual void Play() = 0;

  /**
  \brief Stop playing the audio file.
  */
  virtual void Stop() = 0;

  /**
  \brief Assigns the volume of the audio file.
  \param volume - the desired volume of the audio file, in the range [0, 128].
  */
  virtual void SetVolume(int volume) = 0;

  /**
  \brief Returns the current volume of the audio file.
  */
  virtual int GetVolume() const = 0;
};

}  // namespace audio
}  // namespace centurion