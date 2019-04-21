#pragma once
#include <memory>

namespace centurion {
namespace audio {

/**
\brief The IAudioComponent class is an interface that specifies objects that
represent some sort of audio file.
\since 1.0.0
*/
class IAudioComponent {
 protected:
  IAudioComponent() = default;

 public:
  virtual ~IAudioComponent() = default;

  /**
  \brief Starts playing the audio file.
  \since 1.0.0
  */
  virtual void Play() = 0;

  /**
  \brief Stops playing the audio file.
  \since 1.0.0
  */
  virtual void Stop() = 0;

  /**
  \brief Assigns the volume of the audio.
  \param volume - the volume of the audio file, in the range [0, 128].
  \since 1.0.0
  */
  virtual void SetVolume(int volume) = 0;

  /**
  \brief Returns the current volume of the audio file.
  \since 1.0.0
  */
  virtual int GetVolume() const = 0;
};

typedef std::shared_ptr<IAudioComponent> IAudioComponent_sptr;
typedef std::unique_ptr<IAudioComponent> IAudioComponent_uptr;
typedef std::weak_ptr<IAudioComponent> IAudioComponent_wptr;

}  // namespace audio
}  // namespace centurion