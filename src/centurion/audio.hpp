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

#ifndef CENTURION_AUDIO_HPP_
#define CENTURION_AUDIO_HPP_

#ifndef CENTURION_NO_SDL_MIXER

#include <SDL.h>
#include <SDL_mixer.h>

#include <cassert>   // assert
#include <memory>    // unique_ptr
#include <optional>  // optional, nullopt
#include <ostream>   // ostream
#include <string>    // string, to_string

#include "common.hpp"
#include "detail/owner_handle_api.hpp"
#include "detail/stdlib.hpp"
#include "features.hpp"
#include "memory.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen {

enum class music_type
{
  none = MUS_NONE,
  mp3 = MUS_MP3,
  wav = MUS_WAV,
  ogg = MUS_OGG,
  mod = MUS_MOD,
  midi = MUS_MID,
  cmd = MUS_CMD,
  flac = MUS_FLAC,
  opus = MUS_OPUS
};

[[nodiscard]] constexpr auto to_string(const music_type type) -> std::string_view
{
  switch (type) {
    case music_type::none:
      return "none";

    case music_type::mp3:
      return "mp3";

    case music_type::wav:
      return "wav";

    case music_type::ogg:
      return "ogg";

    case music_type::mod:
      return "mod";

    case music_type::midi:
      return "midi";

    case music_type::cmd:
      return "cmd";

    case music_type::flac:
      return "flac";

    case music_type::opus:
      return "opus";

    default:
      throw exception{"Did not recognize music type!"};
  }
}

inline auto operator<<(std::ostream& stream, const music_type type) -> std::ostream&
{
  return stream << to_string(type);
}

enum class fade_status
{
  none = MIX_NO_FADING,
  in = MIX_FADING_IN,
  out = MIX_FADING_OUT
};

[[nodiscard]] constexpr auto to_string(const fade_status status) -> std::string_view
{
  switch (status) {
    case fade_status::none:
      return "none";

    case fade_status::in:
      return "in";

    case fade_status::out:
      return "out";

    default:
      throw exception{"Did not recognize fade status!"};
  }
}

inline auto operator<<(std::ostream& stream, const fade_status status) -> std::ostream&
{
  return stream << to_string(status);
}

/**
 * Represents a piece of music.
 *
 * Note, only one music instance can ever be playing at any time. As a result, many of the
 * functions in this class are static.
 *
 * The supported audio formats are:
 *   - WAVE/RIFF (.wav)
 *   - AIFF (.aiff)
 *   - VOC (.voc)
 *   - MOD (.mod .xm .s3m .669 .it .med and more)
 *   - MIDI (.mid)
 *   - OggVorbis (.ogg)
 *   - MP3 (.mp3)
 *   - FLAC (.flac)
 *
 * \see sound_effect
 */
class music final
{
 public:
  using channel_index = int;
  using ms_type = millis<int>;
  using music_hook_callback = void (*)(void*, uint8*, int);

  inline constexpr static int forever = -1;  ///< Used to loop music indefinitely.

  explicit music(const char* file) : mMusic{Mix_LoadMUS(file)}
  {
    if (!mMusic) {
      throw mix_error{};
    }
  }

  explicit music(const std::string& file) : music{file.c_str()} {}

  auto play(const int iterations = 0) noexcept -> maybe<channel_index>
  {
    const auto channel = Mix_PlayMusic(mMusic.get(), detail::max(iterations, forever));
    if (channel != -1) {
      return channel;
    }
    else {
      return nothing;
    }
  }

  static void resume() noexcept { Mix_ResumeMusic(); }

  static void pause() noexcept { Mix_PauseMusic(); }

  static void halt() noexcept
  {
    Mix_HaltMusic(); /* This appears to always return 0, so we ignore it */
  }

  [[nodiscard]] static auto is_playing() noexcept -> bool { return Mix_PlayingMusic(); }

  [[nodiscard]] static auto is_paused() noexcept -> bool { return Mix_PausedMusic(); }

  auto fade_in(const ms_type duration,
               const int iterations = 0) noexcept(noexcept(duration.count())) -> result
  {
    assert(duration.count() > 0);
    return Mix_FadeInMusic(mMusic.get(), detail::max(iterations, forever), duration.count()) ==
           0;
  }

  static auto fade_out(const ms_type duration) noexcept(noexcept(duration.count())) -> result
  {
    assert(duration.count() > 0);
    if (!is_fading()) {
      return Mix_FadeOutMusic(duration.count()) != 0;
    }
    else {
      return failure;
    }
  }

  [[nodiscard]] static auto get_fade_status() noexcept -> fade_status
  {
    return static_cast<fade_status>(Mix_FadingMusic());
  }

  [[nodiscard]] static auto is_fading() noexcept -> bool
  {
    const auto status = get_fade_status();
    return status == fade_status::in || status == fade_status::out;
  }

  [[nodiscard]] static auto is_fading_in() noexcept -> bool
  {
    return get_fade_status() == fade_status::in;
  }

  [[nodiscard]] static auto is_fading_out() noexcept -> bool
  {
    return get_fade_status() == fade_status::out;
  }

  static void rewind() noexcept { Mix_RewindMusic(); }

  static auto set_position(const double position) noexcept -> result
  {
    return Mix_SetMusicPosition(position) == 0;
  }

  static void set_volume(const int volume) noexcept
  {
    Mix_VolumeMusic(detail::clamp(volume, 0, MIX_MAX_VOLUME));
  }

  [[nodiscard]] static auto volume() noexcept -> int { return Mix_VolumeMusic(-1); }

  [[nodiscard]] constexpr static auto max_volume() noexcept -> int { return MIX_MAX_VOLUME; }

  template <typename T = void>
  static void set_hook(music_hook_callback callback, T* data = nullptr) noexcept
  {
    Mix_HookMusic(callback, data);
  }

  static void reset_hook() noexcept { set_hook(nullptr); }

  [[nodiscard]] static auto hook_data() noexcept -> void* { return Mix_GetMusicHookData(); }

  [[nodiscard]] static auto has_decoder(const char* name) noexcept -> bool
  {
    return Mix_HasMusicDecoder(name) == SDL_TRUE;
  }

  [[nodiscard]] static auto get_decoder(const int index) noexcept -> const char*
  {
    return Mix_GetMusicDecoder(index);
  }

  [[nodiscard]] static auto decoder_count() noexcept -> int
  {
    return Mix_GetNumMusicDecoders();
  }

  [[nodiscard]] auto type() const noexcept -> music_type
  {
    return static_cast<music_type>(Mix_GetMusicType(mMusic.get()));
  }

#if SDL_MIXER_VERSION_ATLEAST(2, 6, 0)

  [[nodiscard]] static auto current_title() noexcept -> const char*
  {
    return Mix_GetMusicTitle(nullptr);
  }

  [[nodiscard]] auto title() const noexcept -> const char*
  {
    return Mix_GetMusicTitle(mMusic.get());
  }

  [[nodiscard]] auto title_tag() const noexcept -> const char*
  {
    return Mix_GetMusicTitleTag(mMusic.get());
  }

  [[nodiscard]] auto artist_tag() const noexcept -> const char*
  {
    return Mix_GetMusicArtistTag(mMusic.get());
  }

  [[nodiscard]] auto album_tag() const noexcept -> const char*
  {
    return Mix_GetMusicAlbumTag(mMusic.get());
  }

  [[nodiscard]] auto copyright_tag() const noexcept -> const char*
  {
    return Mix_GetMusicCopyrightTag(mMusic.get());
  }

  [[nodiscard]] auto position() const noexcept -> maybe<double>
  {
    const auto pos = Mix_GetMusicPosition(mMusic.get());
    if (pos != -1) {
      return pos;
    }
    else {
      return nothing;
    }
  }

  [[nodiscard]] auto duration() const noexcept -> maybe<double>
  {
    const auto duration = Mix_MusicDuration(mMusic.get());
    if (duration != -1) {
      return duration;
    }
    else {
      return nothing;
    }
  }

  [[nodiscard]] auto loop_start_time() const noexcept -> maybe<double>
  {
    const auto start = Mix_GetMusicLoopStartTime(mMusic.get());
    if (start != -1) {
      return start;
    }
    else {
      return nothing;
    }
  }

  [[nodiscard]] auto loop_end_time() const noexcept -> maybe<double>
  {
    const auto end = Mix_GetMusicLoopEndTime(mMusic.get());
    if (end != -1) {
      return end;
    }
    else {
      return nothing;
    }
  }

  [[nodiscard]] auto loop_length() const noexcept -> maybe<double>
  {
    const auto length = Mix_GetMusicLoopLengthTime(mMusic.get());
    if (length != -1) {
      return length;
    }
    else {
      return nothing;
    }
  }

#endif  // SDL_MIXER_VERSION_ATLEAST(2, 6, 0)

  [[nodiscard]] auto get() const noexcept -> Mix_Music* { return mMusic.get(); }

 private:
  managed_ptr<Mix_Music> mMusic;

#ifdef CENTURION_MOCK_FRIENDLY_MODE

 public:
  music() = default;

#endif  // CENTURION_MOCK_FRIENDLY_MODE
};

[[nodiscard]] inline auto to_string(const music& music) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("music(data: {}, volume: {})",
                     detail::address_of(music.get()),
                     music::volume());
#else
  return "music(data: " + detail::address_of(music.get()) +
         ", volume: " + std::to_string(music::volume()) + ")";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

inline auto operator<<(std::ostream& stream, const music& music) -> std::ostream&
{
  return stream << to_string(music);
}

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
class basic_sound_effect final
{
 public:
  using channel_index = int;
  using ms_type = millis<int>;

  inline constexpr static channel_index undefined_channel = -1;
  inline constexpr static int forever = -1;  ///< Used to play sounds indefinitely.

  explicit basic_sound_effect(maybe_owner<Mix_Chunk*> sound) noexcept(detail::is_handle<T>)
      : mChunk{sound}
  {
    if constexpr (detail::is_owner<T>) {
      if (!mChunk) {
        throw mix_error{};
      }
    }
  }

  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  explicit basic_sound_effect(const char* file) : mChunk{Mix_LoadWAV(file)}
  {
    if (!mChunk) {
      throw mix_error{};
    }
  }

  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  explicit basic_sound_effect(const std::string& file) : basic_sound_effect{file.c_str()}
  {}

  template <typename TT = T, detail::enable_for_handle<TT> = 0>
  explicit basic_sound_effect(const sound_effect& owner) noexcept : mChunk{owner.get()}
  {}

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
  channel_index mChannel{undefined_channel};

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
  return sound_effect_handle{Mix_GetChunk(channel)};
}

}  // namespace cen

#endif  // CENTURION_NO_SDL_MIXER
#endif  // CENTURION_AUDIO_HPP_
