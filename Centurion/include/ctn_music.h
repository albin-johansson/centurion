#pragma once
#include <SDL_mixer.h>
#include <memory>
#include <string>
#include "ctn_audio_component.h"

namespace centurion {
namespace audio {

class Music;
using Music_sptr = std::shared_ptr<Music>;
using Music_uptr = std::unique_ptr<Music>;
using Music_wptr = std::weak_ptr<Music>;

/**
\brief The Music class represents a music clip. The music clips must be of the
.WAV-format.
\since 1.0.0
*/
class Music final : public IAudioComponent {
 private:
  Mix_Music* music;
  int volume;

  inline bool IsMusicPlaying() const noexcept { return Mix_PlayingMusic(); }

 public:
  /**
  \param path - the path of the .WAV-file that the Music instance will
  represent.
  */
  explicit Music(const std::string& path);

  ~Music();

  /**
  \brief Starts playing the music file by fading it in.
  \param ms - the duration of the fade, in milliseconds.
  \since 1.0.0
  */
  void FadeIn(int ms);

  /**
  \brief Stops playing the music file by fading it out.
  \param ms - the duration of the fade, in milliseconds.
  \since 1.0.0
  */
  void FadeOut(int ms);

  /**
  \brief Starts playing the music file.
  \since 1.0.0
  */
  void Play() noexcept override;

  /**
  \brief Stops playing the music file.
  \since 1.0.0
  */
  void Stop() noexcept override;

  /**
  \brief Assigns the volume of the music file.
  \param volume - the desired volume of the music file, in the range [0, 128].
  \since 1.0.0
  */
  void SetVolume(int volume) override;

  /**
  \brief Returns the current volume of the music file.
  \since 1.0.0
  */
  int GetVolume() const noexcept override;

  /**
  \brief Returns a shared pointer that points to a Music instance.
  \param path - the path of the .WAV-file that the Music instance will
  represent.
  \since 1.1.0
  */
  static Music_sptr CreateShared(const std::string& path);

  /**
  \brief Returns a unique pointer that points to a Music instance.
  \param path - the path of the .WAV-file that the Music instance will
  represent.
  \since 1.1.0
  */
  static Music_uptr CreateUnique(const std::string& path);

  /**
  \brief Returns a weak pointer that points to a Music instance.
  \param path - the path of the .WAV-file that the Music instance will
  represent.
  \since 1.1.0
  */
  static Music_wptr CreateWeak(const std::string& path);
};

}  // namespace audio
}  // namespace centurion