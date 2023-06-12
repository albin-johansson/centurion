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

#ifndef CENTURION_AUDIO_MUSIC_HPP_
#define CENTURION_AUDIO_MUSIC_HPP_

#ifndef CENTURION_NO_SDL_MIXER

#include <SDL_mixer.h>

#include <ostream>      // ostream
#include <string>       // string, to_string
#include <string_view>  // string_view

#include "../common.hpp"
#include "../detail/stdlib.hpp"
#include "../features.hpp"
#include "fade_status.hpp"
#include "music_type.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen {

/**
 * Represents a piece of music.
 *
 * \note Only one music instance can ever be playing at any time. As a result, many of the
 *       functions in this class are static.
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

}  // namespace cen

#endif  // CENTURION_NO_SDL_MIXER
#endif  // CENTURION_AUDIO_MUSIC_HPP_
