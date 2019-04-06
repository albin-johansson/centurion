#pragma once

namespace centurion {
namespace audio {

class AudioComponent {
 protected:
  AudioComponent() = default;

 public:
  virtual ~AudioComponent() = default;

  virtual void Play() = 0;

  virtual void Stop() = 0;

  virtual void SetVolume(int volume) = 0;

  virtual int GetVolume() const = 0;
};

}  // namespace audio
}  // namespace centurion