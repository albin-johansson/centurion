#ifndef CENTURION_AUDIO_SOUND_EFFECT_HPP_
#define CENTURION_AUDIO_SOUND_EFFECT_HPP_

#ifndef CENTURION_NO_SDL_MIXER

#include <SDL_mixer.h>

#include <cassert>   // assert
#include <memory>    // unique_ptr
#include <optional>  // optional
#include <ostream>   // ostream
#include <string>    // string, to_string

#include "../core/common.hpp"
#include "../core/exception.hpp"
#include "../core/features.hpp"
#include "../core/time.hpp"
#include "../detail/owner_handle_api.hpp"
#include "../detail/stdlib.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen {

template <typename T>
class BasicSoundEffect;

using SoundEffect = BasicSoundEffect<detail::owning_type>;

using SoundEffectHandle = BasicSoundEffect<detail::handle_type>;

template <typename T>
class BasicSoundEffect final
{
 public:
  using Ms = milliseconds<int>;

  inline constexpr static int forever = -1;

  explicit BasicSoundEffect(maybe_owner<Mix_Chunk*> sound) noexcept(!detail::is_owning<T>())
      : mChunk{sound}
  {
    if constexpr (detail::is_owning<T>()) {
      if (!mChunk) {
        throw mix_error{};
      }
    }
  }

  template <typename TT = T, detail::is_owner<TT> = 0>
  explicit BasicSoundEffect(const char* file) : mChunk{Mix_LoadWAV(file)}
  {
    if (!mChunk) {
      throw mix_error{};
    }
  }

  template <typename TT = T, detail::is_owner<TT> = 0>
  explicit BasicSoundEffect(const std::string& file) : BasicSoundEffect{file.c_str()}
  {}

  template <typename TT = T, detail::is_handle<TT> = 0>
  explicit BasicSoundEffect(const SoundEffect& owner) noexcept : mChunk{owner.get()}
  {}

  auto Play(const int iterations = 0) noexcept -> result
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

  void FadeIn(const Ms ms) noexcept(noexcept(ms.count()))
  {
    assert(ms.count() > 0);
    if (!IsPlaying()) {
      mChannel = Mix_FadeInChannel(mChannel, get(), 0, ms.count());
    }
  }

  void FadeOut(const Ms ms) noexcept(noexcept(ms.count()))  // NOLINT
  {
    assert(ms.count() > 0);
    if (IsPlaying()) {
      Mix_FadeOutChannel(mChannel, ms.count());
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

  template <typename TT = T, detail::is_owner<TT> = 0>
  [[nodiscard]] static auto IsAnyPlaying() noexcept -> bool
  {
    return Mix_Playing(GetUndefinedChannel());
  }

  [[nodiscard]] auto IsFading() const noexcept -> bool
  {
    return IsPlaying() && Mix_FadingChannel(mChannel);
  }

  [[nodiscard]] auto GetVolume() const noexcept -> int
  {
    return mChunk->volume;
  }

  [[nodiscard]] constexpr static auto GetMaxVolume() noexcept -> int
  {
    return MIX_MAX_VOLUME;
  }

  template <typename TT = T, detail::is_owner<TT> = 0>
  [[nodiscard]] static auto GetDecoder(const int index) noexcept -> const char*
  {
    return Mix_GetChunkDecoder(index);
  }

  template <typename TT = T, detail::is_owner<TT> = 0>
  [[nodiscard]] static auto HasDecoder(const cstr name) noexcept -> bool
  {
    return Mix_HasChunkDecoder(name) == SDL_TRUE;
  }

  template <typename TT = T, detail::is_owner<TT> = 0>
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

  [[nodiscard]] auto get() const noexcept -> Mix_Chunk*
  {
    return mChunk.get();
  }

 private:
  detail::Pointer<T, Mix_Chunk> mChunk;
  int mChannel{GetUndefinedChannel()};

  [[nodiscard]] constexpr static auto GetUndefinedChannel() noexcept -> int
  {
    return -1;
  }

#ifdef CENTURION_MOCK_FRIENDLY_MODE

 public:
  void set_channel(const int channel) noexcept
  {
    mChannel = channel;
  }

#endif  // CENTURION_MOCK_FRIENDLY_MODE
};

[[nodiscard]] inline auto GetSound(const int channel) noexcept -> SoundEffectHandle
{
  return SoundEffectHandle{Mix_GetChunk(channel)};
}

}  // namespace cen

#endif  // CENTURION_NO_SDL_MIXER
#endif  // CENTURION_AUDIO_SOUND_EFFECT_HPP_
