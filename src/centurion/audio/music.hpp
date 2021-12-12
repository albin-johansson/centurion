#ifndef CENTURION_AUDIO_MUSIC_HPP_
#define CENTURION_AUDIO_MUSIC_HPP_

#ifndef CENTURION_NO_SDL_MIXER

#include <SDL.h>
#include <SDL_mixer.h>

#include <cassert>   // assert
#include <optional>  // optional
#include <string>    // string

#include "../core/common.hpp"
#include "../core/exception.hpp"
#include "../core/features.hpp"
#include "../core/memory.hpp"
#include "../core/time.hpp"
#include "../detail/any_eq.hpp"
#include "../detail/stdlib.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen {

enum class MusicType
{
  None = MUS_NONE,
  MP3 = MUS_MP3,
  WAV = MUS_WAV,
  OGG = MUS_OGG,
  MOD = MUS_MOD,
  MIDI = MUS_MID,
  CMD = MUS_CMD,
  FLAC = MUS_FLAC,
  OPUS = MUS_OPUS
};

enum class FadeStatus
{
  None = MIX_NO_FADING,
  In = MIX_FADING_IN,
  Out = MIX_FADING_OUT
};

class Music final
{
 public:
  using Ms = milliseconds<int>;
  using MusicHookCallback = void (*)(void*, Uint8*, int);

  inline constexpr static int forever = -1;

  explicit Music(const char* file) : mMusic{Mix_LoadMUS(file)}
  {
    if (!mMusic) {
      throw MixError{};
    }
  }

  explicit Music(const std::string& file) : Music{file.c_str()}
  {}

  auto Play(const int iterations = 0) noexcept -> std::optional<int>
  {
    const auto channel = Mix_PlayMusic(mMusic.get(), detail::max(iterations, forever));
    if (channel != -1) {
      return channel;
    }
    else {
      return std::nullopt;
    }
  }

  static void Resume() noexcept
  {
    Mix_ResumeMusic();
  }

  static void Pause() noexcept
  {
    Mix_PauseMusic();
  }

  static void Halt() noexcept
  {
    Mix_HaltMusic(); /* This appears to always return 0, so we ignore it */
  }

  static void Rewind() noexcept
  {
    Mix_RewindMusic();
  }

  auto FadeIn(const Ms ms, const int nLoops = 0) noexcept(noexcept(ms.count())) -> result
  {
    assert(ms.count() > 0);
    return Mix_FadeInMusic(mMusic.get(), detail::max(nLoops, forever), ms.count()) == 0;
  }

  static auto FadeOut(const Ms ms) noexcept(noexcept(ms.count())) -> result
  {
    assert(ms.count() > 0);
    if (!IsFading()) {
      return Mix_FadeOutMusic(ms.count()) != 0;
    }
    else {
      return failure;
    }
  }

  [[nodiscard]] static auto GetFadeStatus() noexcept -> FadeStatus
  {
    return static_cast<FadeStatus>(Mix_FadingMusic());
  }

  [[nodiscard]] static auto IsPlaying() noexcept -> bool
  {
    return Mix_PlayingMusic();
  }

  [[nodiscard]] static auto IsPaused() noexcept -> bool
  {
    return Mix_PausedMusic();
  }

  [[nodiscard]] static auto IsFading() noexcept -> bool
  {
    const auto status = GetFadeStatus();
    return status == FadeStatus::In || status == FadeStatus::Out;
  }

  static auto SetPosition(const double position) noexcept -> result
  {
    return Mix_SetMusicPosition(position) == 0;
  }

  static void SetVolume(const int volume) noexcept
  {
    Mix_VolumeMusic(detail::clamp(volume, 0, MIX_MAX_VOLUME));
  }

  template <typename T = void>
  static void SetHook(MusicHookCallback callback, T* data = nullptr) noexcept
  {
    Mix_HookMusic(callback, data);
  }

  static void ResetHook() noexcept
  {
    SetHook(nullptr);
  }

  [[nodiscard]] auto GetType() const noexcept -> MusicType
  {
    return static_cast<MusicType>(Mix_GetMusicType(mMusic.get()));
  }

  [[nodiscard]] static auto GetVolume() noexcept -> int
  {
    return Mix_VolumeMusic(-1);
  }

  [[nodiscard]] constexpr static auto GetMaxVolume() noexcept -> int
  {
    return MIX_MAX_VOLUME;
  }

  [[nodiscard]] auto get() const noexcept -> Mix_Music*
  {
    return mMusic.get();
  }

  [[nodiscard]] static auto GetHookData() noexcept -> void*
  {
    return Mix_GetMusicHookData();
  }

  [[nodiscard]] static auto GetDecoder(const int index) noexcept -> const char*
  {
    return Mix_GetMusicDecoder(index);
  }

  [[nodiscard]] static auto HasDecoder(const char* name) noexcept -> bool
  {
    return Mix_HasMusicDecoder(name) == SDL_TRUE;
  }

  [[nodiscard]] static auto GetDecoderCount() noexcept -> int
  {
    return Mix_GetNumMusicDecoders();
  }

 private:
  Managed<Mix_Music> mMusic;

#ifdef CENTURION_MOCK_FRIENDLY_MODE

 public:
  Music() = default;

#endif  // CENTURION_MOCK_FRIENDLY_MODE
};

}  // namespace cen

#endif  // CENTURION_NO_SDL_MIXER
#endif  // CENTURION_AUDIO_MUSIC_HPP_