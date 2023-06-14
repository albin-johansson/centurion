/*
 * MIT License
 *
 * Copyright (c) 2019-2022 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef CENTURION_AUDIO_SOUND_EFFECT_HPP_
#define CENTURION_AUDIO_SOUND_EFFECT_HPP_

#ifndef CENTURION_NO_SDL_MIXER

#include <SDL_mixer.h>

#include <cassert>      // assert
#include <ostream>      // ostream
#include <string>       // string, to_string
#include <string_view>  // string_view

#include "../common.hpp"
#include "../detail/owner_handle_api.hpp"
#include "../detail/stdlib.hpp"
#include "../features.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen {

template <typename T>
class basic_sound_effect;

using sound_effect = basic_sound_effect<detail::owner_tag>;
using sound_effect_handle = basic_sound_effect<detail::handle_tag>;

/**
 * Represents a sound effect.
 *
 * Unlike with the music API, multiple sound effects can be played at the same time, which is
 * the main difference between the music and sound effect APIs.
 *
 * The supported file formats are:
 *   - WAVE/RIFF (.wav)
 *   - AIFF (.aiff)
 *   - VOC (.voc)
 *   - OGG (.ogg)
 *   - VOC (.voc)
 *
 * \see sound_effect
 * \see sound_effect_handle
 * \see music
 * \see get_sound
 */
template <typename T>
class basic_sound_effect final {
 public:
  using channel_index = int;
  using ms_type = millis<int>;

  inline constexpr static channel_index undefined_channel = -1;
  inline constexpr static int forever = -1;  ///< Used to play sounds indefinitely.

  explicit basic_sound_effect(maybe_owner<Mix_Chunk*> sound) noexcept(detail::is_handle<T>)
      : mChunk {sound}
  {
    if constexpr (detail::is_owner<T>) {
      if (!mChunk) {
        throw mix_error {};
      }
    }
  }

  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  explicit basic_sound_effect(const char* file) : mChunk {Mix_LoadWAV(file)}
  {
    if (!mChunk) {
      throw mix_error {};
    }
  }

  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  explicit basic_sound_effect(const std::string& file) : basic_sound_effect {file.c_str()}
  {
  }

  template <typename TT = T, detail::enable_for_handle<TT> = 0>
  explicit basic_sound_effect(const sound_effect& owner) noexcept : mChunk {owner.get()}
  {
  }

  auto play(const int iterations = 0) noexcept -> result
  {
    mChannel = Mix_PlayChannel(mChannel, mChunk.get(), detail::max(iterations, forever));
    return mChannel != -1;
  }

  void stop() noexcept
  {
    if (is_playing()) {
      Mix_Pause(mChannel);
      mChannel = undefined_channel;
    }
  }

  [[nodiscard]] auto is_playing() const noexcept -> bool
  {
    return (mChannel != undefined_channel) && Mix_Playing(mChannel);
  }

  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  [[nodiscard]] static auto is_any_playing() noexcept -> bool
  {
    return Mix_Playing(undefined_channel);
  }

  void fade_in(const ms_type duration) noexcept(noexcept(duration.count()))
  {
    assert(duration.count() > 0);
    if (!is_playing()) {
      mChannel = Mix_FadeInChannel(mChannel, get(), 0, duration.count());
    }
  }

  void fade_out(const ms_type duration) noexcept(noexcept(duration.count()))  // NOLINT
  {
    assert(duration.count() > 0);
    if (is_playing()) {
      Mix_FadeOutChannel(mChannel, duration.count());
    }
  }

  [[nodiscard]] auto is_fading() const noexcept -> bool
  {
    return is_playing() && Mix_FadingChannel(mChannel);
  }

  [[nodiscard]] auto channel() const noexcept -> maybe<channel_index>
  {
    if (mChannel != undefined_channel) {
      return mChannel;
    }
    else {
      return nothing;
    }
  }

  void set_volume(const int volume) noexcept
  {
    Mix_VolumeChunk(mChunk.get(), detail::clamp(volume, 0, max_volume()));
  }

  [[nodiscard]] auto volume() const noexcept -> int { return mChunk->volume; }

  [[nodiscard]] constexpr static auto max_volume() noexcept -> int { return MIX_MAX_VOLUME; }

  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  [[nodiscard]] static auto has_decoder(const char* name) noexcept -> bool
  {
    return Mix_HasChunkDecoder(name) == SDL_TRUE;
  }

  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  [[nodiscard]] static auto get_decoder(const int index) noexcept -> const char*
  {
    return Mix_GetChunkDecoder(index);
  }

  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  [[nodiscard]] static auto decoder_count() noexcept -> int
  {
    return Mix_GetNumChunkDecoders();
  }

  [[nodiscard]] auto get() const noexcept -> Mix_Chunk* { return mChunk.get(); }

#if SDL_MIXER_VERSION_ATLEAST(2, 6, 0)

  static void set_master_volume(const int volume) noexcept { Mix_MasterVolume(volume); }

  [[nodiscard]] static auto master_volume() noexcept -> int { return Mix_MasterVolume(-1); }

#endif  // SDL_MIXER_VERSION_ATLEAST(2, 6, 0)

 private:
  detail::pointer<T, Mix_Chunk> mChunk;
  channel_index mChannel {undefined_channel};

#ifdef CENTURION_MOCK_FRIENDLY_MODE

 public:
  void set_channel(const channel_index channel) noexcept { mChannel = channel; }

#endif  // CENTURION_MOCK_FRIENDLY_MODE
};

template <typename T>
[[nodiscard]] auto to_string(const basic_sound_effect<T>& sound) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("sound_effect(data: {}, volume: {})",
                     detail::address_of(sound.get()),
                     sound.volume());
#else
  return "sound_effect(data: " + detail::address_of(sound.get()) +
         ", volume: " + std::to_string(sound.volume()) + ")";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

template <typename T>
auto operator<<(std::ostream& stream, const basic_sound_effect<T>& sound) -> std::ostream&
{
  return stream << to_string(sound);
}

/// Returns a potentially empty handle to the sound associated with a channel.
[[nodiscard]] inline auto get_sound(const int channel) noexcept -> sound_effect_handle
{
  return sound_effect_handle {Mix_GetChunk(channel)};
}

}  // namespace cen

#endif  // CENTURION_NO_SDL_MIXER
#endif  // CENTURION_AUDIO_SOUND_EFFECT_HPP_
