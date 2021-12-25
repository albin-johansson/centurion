#ifndef CENTURION_AUDIO_HPP_
#define CENTURION_AUDIO_HPP_

#ifndef CENTURION_NO_SDL_MIXER

#include <SDL.h>
#include <SDL_mixer.h>

#include <cassert>   // assert
#include <memory>    // unique_ptr
#include <optional>  // optional
#include <ostream>   // ostream
#include <string>    // string
#include <string>    // string, to_string

#include "common.hpp"
#include "features.hpp"
#include "memory.hpp"
#include "detail/owner_handle_api.hpp"
#include "detail/stdlib.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen {

enum class MusicType {
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

enum class FadeStatus {
  None = MIX_NO_FADING,
  In = MIX_FADING_IN,
  Out = MIX_FADING_OUT
};

class Music final {
 public:
  using MusicHookCallback = void (*)(void*, Uint8*, int);

  inline constexpr static int forever = -1;

  explicit Music(const char* file) : mMusic{Mix_LoadMUS(file)}
  {
    if (!mMusic) {
      throw MixError{};
    }
  }

  explicit Music(const std::string& file) : Music{file.c_str()} {}

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

  static void Resume() noexcept { Mix_ResumeMusic(); }

  static void Pause() noexcept { Mix_PauseMusic(); }

  static void Halt() noexcept
  {
    Mix_HaltMusic(); /* This appears to always return 0, so we ignore it */
  }

  static void Rewind() noexcept { Mix_RewindMusic(); }

  auto FadeIn(const Millis<int> duration,
              const int nLoops = 0) noexcept(noexcept(duration.count())) -> Result
  {
    assert(duration.count() > 0);
    return Mix_FadeInMusic(mMusic.get(), detail::max(nLoops, forever), duration.count()) == 0;
  }

  static auto FadeOut(const Millis<int> duration) noexcept(noexcept(duration.count()))
      -> Result
  {
    assert(duration.count() > 0);
    if (!IsFading()) {
      return Mix_FadeOutMusic(duration.count()) != 0;
    }
    else {
      return failure;
    }
  }

  [[nodiscard]] static auto GetFadeStatus() noexcept -> FadeStatus
  {
    return static_cast<FadeStatus>(Mix_FadingMusic());
  }

  [[nodiscard]] static auto IsPlaying() noexcept -> bool { return Mix_PlayingMusic(); }

  [[nodiscard]] static auto IsPaused() noexcept -> bool { return Mix_PausedMusic(); }

  [[nodiscard]] static auto IsFading() noexcept -> bool
  {
    const auto status = GetFadeStatus();
    return status == FadeStatus::In || status == FadeStatus::Out;
  }

  static auto SetPosition(const double position) noexcept -> Result
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

  static void ResetHook() noexcept { SetHook(nullptr); }

  [[nodiscard]] auto GetType() const noexcept -> MusicType
  {
    return static_cast<MusicType>(Mix_GetMusicType(mMusic.get()));
  }

  [[nodiscard]] static auto GetVolume() noexcept -> int { return Mix_VolumeMusic(-1); }

  [[nodiscard]] constexpr static auto GetMaxVolume() noexcept -> int { return MIX_MAX_VOLUME; }

  [[nodiscard]] static auto GetHookData() noexcept -> void* { return Mix_GetMusicHookData(); }

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

  [[nodiscard]] auto get() const noexcept -> Mix_Music* { return mMusic.get(); }

 private:
  Managed<Mix_Music> mMusic;

#ifdef CENTURION_MOCK_FRIENDLY_MODE

 public:
  Music() = default;

#endif  // CENTURION_MOCK_FRIENDLY_MODE
};

template <typename T>
class BasicSoundEffect;

using SoundEffect = BasicSoundEffect<detail::OwnerTag>;
using SoundEffectHandle = BasicSoundEffect<detail::HandleTag>;

template <typename T>
class BasicSoundEffect final {
 public:
  inline constexpr static int forever = -1;

  explicit BasicSoundEffect(MaybeOwner<Mix_Chunk*> sound) noexcept(detail::is_handle<T>)
      : mChunk{sound}
  {
    if constexpr (detail::is_owner<T>) {
      if (!mChunk) {
        throw MixError{};
      }
    }
  }

  template <typename TT = T, detail::EnableOwner<TT> = 0>
  explicit BasicSoundEffect(const char* file) : mChunk{Mix_LoadWAV(file)}
  {
    if (!mChunk) {
      throw MixError{};
    }
  }

  template <typename TT = T, detail::EnableOwner<TT> = 0>
  explicit BasicSoundEffect(const std::string& file) : BasicSoundEffect{file.c_str()}
  {}

  template <typename TT = T, detail::EnableHandle<TT> = 0>
  explicit BasicSoundEffect(const SoundEffect& owner) noexcept : mChunk{owner.get()}
  {}

  auto Play(const int iterations = 0) noexcept -> Result
  {
    mChannel = Mix_PlayChannel(mChannel, mChunk.get(), detail::max(iterations, forever));
    return mChannel != -1;
  }

  void Stop() noexcept
  {
    if (IsPlaying()) {
      Mix_Pause(mChannel);
      mChannel = GetUndefinedChannel();
    }
  }

  void FadeIn(const Millis<int> duration) noexcept(noexcept(duration.count()))
  {
    assert(duration.count() > 0);
    if (!IsPlaying()) {
      mChannel = Mix_FadeInChannel(mChannel, get(), 0, duration.count());
    }
  }

  void FadeOut(const Millis<int> duration) noexcept(noexcept(duration.count()))  // NOLINT
  {
    assert(duration.count() > 0);
    if (IsPlaying()) {
      Mix_FadeOutChannel(mChannel, duration.count());
    }
  }

  void SetVolume(const int volume) noexcept
  {
    Mix_VolumeChunk(mChunk.get(), detail::clamp(volume, 0, GetMaxVolume()));
  }

  [[nodiscard]] auto IsPlaying() const noexcept -> bool
  {
    return (mChannel != GetUndefinedChannel()) && Mix_Playing(mChannel);
  }

  template <typename TT = T, detail::EnableOwner<TT> = 0>
  [[nodiscard]] static auto IsAnyPlaying() noexcept -> bool
  {
    return Mix_Playing(GetUndefinedChannel());
  }

  [[nodiscard]] auto IsFading() const noexcept -> bool
  {
    return IsPlaying() && Mix_FadingChannel(mChannel);
  }

  [[nodiscard]] auto GetVolume() const noexcept -> int { return mChunk->volume; }

  [[nodiscard]] constexpr static auto GetMaxVolume() noexcept -> int { return MIX_MAX_VOLUME; }

  template <typename TT = T, detail::EnableOwner<TT> = 0>
  [[nodiscard]] static auto GetDecoder(const int index) noexcept -> const char*
  {
    return Mix_GetChunkDecoder(index);
  }

  template <typename TT = T, detail::EnableOwner<TT> = 0>
  [[nodiscard]] static auto HasDecoder(const char* name) noexcept -> bool
  {
    return Mix_HasChunkDecoder(name) == SDL_TRUE;
  }

  template <typename TT = T, detail::EnableOwner<TT> = 0>
  [[nodiscard]] static auto GetDecoderCount() noexcept -> int
  {
    return Mix_GetNumChunkDecoders();
  }

  [[nodiscard]] auto GetChannel() const noexcept -> std::optional<int>
  {
    if (mChannel != GetUndefinedChannel()) {
      return mChannel;
    }
    else {
      return std::nullopt;
    }
  }

  [[nodiscard]] auto get() const noexcept -> Mix_Chunk* { return mChunk.get(); }

 private:
  detail::Pointer<T, Mix_Chunk> mChunk;
  int mChannel{GetUndefinedChannel()};

  [[nodiscard]] constexpr static auto GetUndefinedChannel() noexcept -> int { return -1; }

#ifdef CENTURION_MOCK_FRIENDLY_MODE

 public:
  void set_channel(const int channel) noexcept { mChannel = channel; }

#endif  // CENTURION_MOCK_FRIENDLY_MODE
};

[[nodiscard]] inline auto GetSound(const int channel) noexcept -> SoundEffectHandle
{
  return SoundEffectHandle{Mix_GetChunk(channel)};
}

}  // namespace cen

#endif  // CENTURION_NO_SDL_MIXER
#endif  // CENTURION_AUDIO_HPP_
