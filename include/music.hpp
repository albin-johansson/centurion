/*
 * MIT License
 *
 * Copyright (c) 2019-2021 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef CENTURION_MUSIC_HEADER
#define CENTURION_MUSIC_HEADER

#include <SDL_mixer.h>

#include <cassert>  // assert
#include <memory>   // unique_ptr
#include <ostream>  // ostream
#include <string>   // string

#include "centurion_cfg.hpp"
#include "czstring.hpp"
#include "detail/address_of.hpp"
#include "detail/any_eq.hpp"
#include "detail/clamp.hpp"
#include "detail/max.hpp"
#include "detail/to_string.hpp"
#include "exception.hpp"
#include "not_null.hpp"
#include "time.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/// \addtogroup audio
/// \{

/**
 * \enum fade_status
 *
 * \brief Mirrors the values of the `Mix_Fading` enum.
 *
 * \since 3.0.0
 *
 * \headerfile music.hpp
 */
enum class fade_status
{
  none = MIX_NO_FADING,  ///< No currently fading music.
  in = MIX_FADING_IN,    ///< Currently fading in music.
  out = MIX_FADING_OUT   ///< Currently fading out music.
};

/**
 * \enum music_type
 *
 * \brief Mirrors the values of the `Mix_MusicType` enum.
 *
 * \since 3.0.0
 *
 * \headerfile music.hpp
 */
enum class music_type
{
  unknown = MUS_NONE,
  mp3 = MUS_MP3,
  wav = MUS_WAV,
  ogg = MUS_OGG,
  mod = MUS_MOD,
  midi = MUS_MID,
  cmd = MUS_CMD,
  flac = MUS_FLAC,
  opus = MUS_OPUS
};

/**
 * \class music
 *
 * \brief Represents a music file.
 *
 * \details The supported audio formats are the following:
 * <ul>
 *   <li>WAVE/RIFF (.wav)</li>
 *   <li>AIFF (.aiff)</li>
 *   <li>VOC (.voc)</li>
 *   <li>MOD (.mod .xm .s3m .669 .it .med and more)</li>
 *   <li>MIDI (.mid)</li>
 *   <li>OggVorbis (.ogg)</li>
 *   <li>MP3 (.mp3)</li>
 *   <li>FLAC (.flac)</li>
 * </ul>
 *
 * \note Only one music instance can ever be playing at any time.
 *
 * \todo Look into special effects API (also applies for sound effects).
 *
 * \see `Mix_Music`
 * \see `sound_effect`
 *
 * \since 3.0.0
 *
 * \headerfile music.hpp
 */
class music final
{
 public:
  /**
   * \brief A constant that indicates that the music should be looped
   * indefinitely.
   *
   * \since 5.1.0
   */
  inline constexpr static int forever = -1;

  /**
   * \brief A constant that indicates that an audio snippet should be looped
   * indefinitely.
   *
   * \deprecated Since 5.1.0, use `music::forever` instead.
   *
   * \since 4.0.0
   */
  [[deprecated]] inline constexpr static int loopForever = forever;

  /**
   * \brief Creates a `music` instance based on the file at the specified path.
   *
   * \param file the file path of the music file that will be loaded, cannot
   * be null.
   *
   * \throws mix_error if the music file cannot be loaded.
   *
   * \since 3.0.0
   */
  explicit music(not_null<czstring> file) : m_music{Mix_LoadMUS(file)}
  {
    if (!m_music) {
      throw mix_error{};
    }
  }

  /**
   * \brief Plays the music associated with this instance.
   *
   * \details Any previously playing music will be halted. However, this
   * method will wait for music that was fading out to complete.
   *
   * \note The term loops is a little bit confusing here, even in the SDL_mixer
   * documentation. A negative value indicates that the music should be played
   * forever. Furthermore, the values 0 and 1 both results in the music being
   * played *one time*. Except for these "special" values, the method behaves as
   * expected.
   *
   * \param nLoops the number of times to loop the music, `music::forever` can
   * be supplied to loop the music indefinitely.
   *
   * \see `music::forever`
   *
   * \since 3.0.0
   */
  void play(const int nLoops = 0) noexcept
  {
    Mix_PlayMusic(m_music.get(), detail::max(nLoops, forever));
  }

  /**
   * \brief Resumes playing the music.
   *
   * \details This method can safely be invoked with halted, paused and even
   * currently playing music.
   *
   * \since 3.0.0
   */
  static void resume() noexcept
  {
    Mix_ResumeMusic();
  }

  /**
   * \brief Pauses any currently playing music.
   *
   * \note This method only affects music that is currently playing, which
   * doesn't include music that is being faded in/out.
   *
   * \since 3.0.0
   */
  static void pause() noexcept
  {
    Mix_PauseMusic();
  }

  /**
   * \brief Stops ALL currently playing and fading music.
   *
   * \details Unlike `pause()`, this method affects all kinds of music.
   *
   * \since 3.0.0
   */
  static void halt() noexcept
  {
    Mix_HaltMusic();
  }

  /**
   * \brief Plays the music by fading it in by the specified amount of time.
   *
   * \pre `ms` must be greater than zero.
   *
   * \details The fade effect is only applied to the first iteration of
   * the playback of the music. Any previously playing music will be halted.
   * However, if other music is currently being faded out, this music will
   * wait for that to complete.
   *
   * \note The term loops is a little bit confusing here, even in the SDL_mixer
   * documentation. A negative value indicates that the music should be played
   * forever. Furthermore, the values 0 and 1 both results in the music being
   * played *one time*. Except for these "special" values, the method behaves as
   * expected.
   *
   * \param ms the amount of time it takes for the fade to complete.
   *
   * \param nLoops the number of iterations to play the music, `music::forever`
   * can be supplied to loop the music indefinitely.
   *
   * \see `music::forever`
   *
   * \since 3.0.0
   */
  void fade_in(const milliseconds<int> ms, const int nLoops = 0)
  {
    assert(ms.count() > 0);
    Mix_FadeInMusic(m_music.get(), detail::max(nLoops, forever), ms.count());
  }

  /**
   * \brief Fades out any currently playing music over the specified amount of
   * time.
   *
   * \pre `ms` must be greater than zero.
   *
   * \details This method only affects music that is currently playing and
   * not currently fading out. In other words, this method has no effect if
   * music is currently being faded by the time the method is invoked.
   *
   * \param ms the amount of time for the fade to complete, in milliseconds.
   *
   * \since 3.0.0
   */
  static void fade_out(const milliseconds<int> ms)
  {
    assert(ms.count() > 0);
    if (!is_fading()) {
      Mix_FadeOutMusic(ms.count());
    }
  }

  /**
   * \brief Sets the volume of all music.
   *
   * \param volume the volume that will be used, in the range [0,
   * `music::max_volume()`]. An out-of-bounds value will be clamped to the
   * closest valid value.
   *
   * \since 3.0.0
   */
  static void set_volume(const int volume) noexcept
  {
    Mix_VolumeMusic(detail::clamp(volume, 0, MIX_MAX_VOLUME));
  }

  /**
   * \brief Indicates whether or not any music is currently playing.
   *
   * \return `true` if music is currently being played; `false` otherwise.
   *
   * \since 3.0.0
   */
  [[nodiscard]] static auto is_playing() noexcept -> bool
  {
    return Mix_PlayingMusic();
  }

  /**
   * \brief Indicates whether or not any music is paused.
   *
   * \return `true` if the music is paused; `false` otherwise.
   *
   * \since 3.0.0
   */
  [[nodiscard]] static auto is_paused() noexcept -> bool
  {
    return Mix_PausedMusic();
  }

  /**
   * \brief Indicates whether or not any music is currently being faded in or
   * out.
   *
   * \return `true` if music is currently being faded in or out; `false`
   * otherwise.
   *
   * \since 3.0.0
   */
  [[nodiscard]] static auto is_fading() noexcept -> bool
  {
    return detail::any_eq(get_fade_status(), fade_status::in, fade_status::out);
  }

  /**
   * \brief Returns the volume of the music.
   *
   * \details The default value is set to `music::max_volume()`.
   *
   * \return the volume of the music, in the range [0, `music::max_volume()`].
   *
   * \since 3.0.0
   */
  [[nodiscard]] static auto volume() noexcept -> int
  {
    return Mix_VolumeMusic(-1);
  }

  /**
   * \brief Returns the current fade status of the music playback.
   *
   * \return the current fade status.
   *
   * \since 3.0.0
   */
  [[nodiscard]] static auto get_fade_status() noexcept -> fade_status
  {
    return static_cast<fade_status>(Mix_FadingMusic());
  }

  /**
   * \brief Returns the type of the music.
   *
   * \return the type of the music.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto type() const noexcept -> music_type
  {
    return static_cast<music_type>(Mix_GetMusicType(m_music.get()));
  }

  /**
   * \brief Returns a pointer to the associated `Mix_Music`.
   *
   * \warning Use of this method is not recommended. However, it's useful since
   * many SDL calls use non-const pointers even when no change will be applied.
   *
   * \warning Don't take ownership of the returned pointer!
   *
   * \return a pointer to the associated `Mix_Music`.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto get() const noexcept -> Mix_Music*
  {
    return m_music.get();
  }

  /**
   * \brief Converts to `Mix_Music*`.
   *
   * \return a pointer to the associated `Mix_Music` instance.
   *
   * \since 4.0.0
   */
  [[nodiscard]] explicit operator Mix_Music*() noexcept
  {
    return m_music.get();
  }

  /**
   * \brief Converts to `const Mix_Music*`.
   *
   * \return a pointer to the associated `Mix_Music` instance.
   *
   * \since 3.0.0
   */
  [[nodiscard]] explicit operator const Mix_Music*() const noexcept
  {
    return m_music.get();
  }

  /**
   * \brief Returns the maximum possible volume.
   *
   * \return the maximum possible volume value, equal to `MIX_MAX_VOLUME`.
   *
   * \since 5.0.0
   */
  [[nodiscard]] constexpr static auto max_volume() noexcept -> int
  {
    return MIX_MAX_VOLUME;
  }

 private:
  struct deleter final
  {
    void operator()(Mix_Music* music) noexcept
    {
      Mix_FreeMusic(music);
    }
  };

  std::unique_ptr<Mix_Music, deleter> m_music;

#ifdef CENTURION_MOCK_FRIENDLY_MODE
 public:
  music() = default;
#endif
};

/**
 * \brief Returns a textual representation of a `music` instance.
 *
 * \param music the instance that will be converted.
 *
 * \return a string that represents the `music` instance.
 *
 * \since 5.0.0
 */
[[nodiscard]] inline auto to_string(const music& music) -> std::string
{
  return "[music | data: " + detail::address_of(music.get()) +
         ", volume: " + detail::to_string(music::volume()).value() + "]";
}

/**
 * \brief Prints a textual representation of a `music` instance.
 *
 * \param stream the stream that will be used.
 * \param music the `music` instance that will be printed.
 *
 * \return the used stream.
 *
 * \since 5.0.0
 */
inline auto operator<<(std::ostream& stream, const music& music)
    -> std::ostream&
{
  stream << to_string(music);
  return stream;
}

/**
 * \brief Indicates whether or not the fading status values represent are the
 * same.
 *
 * \param lhs the left-hand side fading status value.
 * \param rhs the right-hand side fading status value.
 *
 * \return `true` if the fading status values are the same; `false` otherwise.
 *
 * \since 3.0.0
 */
[[nodiscard]] constexpr auto operator==(const fade_status lhs,
                                        const Mix_Fading rhs) noexcept -> bool
{
  return static_cast<Mix_Fading>(lhs) == rhs;
}

/**
 * \copydoc operator==(fade_status, Mix_Fading)
 */
[[nodiscard]] constexpr auto operator==(const Mix_Fading lhs,
                                        const fade_status rhs) noexcept -> bool
{
  return rhs == lhs;
}

/**
 * \brief Indicates whether or not the fading status values represent aren't the
 * same.
 *
 * \param lhs the left-hand side fading status value.
 * \param rhs the right-hand side fading status value.
 *
 * \return `true` if the fading status values aren't the same; `false`
 * otherwise.
 *
 * \since 5.0.0
 */
[[nodiscard]] constexpr auto operator!=(const fade_status lhs,
                                        const Mix_Fading rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/**
 * \copydoc operator!=(fade_status, Mix_Fading)
 */
[[nodiscard]] constexpr auto operator!=(const Mix_Fading lhs,
                                        const Mix_Fading rhs) noexcept -> bool
{
  return !(lhs == rhs);  // NOLINT
}

/**
 * \brief Indicates whether or not the music type values are the same.
 *
 * \param lhs the left-hand side music type value.
 * \param rhs the right-hand side music type value.
 *
 * \return `true` if the music type values are the same; `false` otherwise.
 *
 * \since 3.0.0
 */
[[nodiscard]] constexpr auto operator==(const music_type lhs,
                                        const Mix_MusicType rhs) noexcept
    -> bool
{
  return static_cast<Mix_MusicType>(lhs) == rhs;
}

/**
 * \copydoc operator==(music_type, Mix_MusicType)
 */
[[nodiscard]] constexpr auto operator==(const Mix_MusicType lhs,
                                        const music_type rhs) noexcept -> bool
{
  return rhs == lhs;
}

/**
 * \brief Indicates whether or not the music type values aren't the same.
 *
 * \param lhs the left-hand side music type value.
 * \param rhs the right-hand side music type value.
 *
 * \return `true` if the music type values aren't the same; `false` otherwise.
 *
 * \since 5.0.0
 */
[[nodiscard]] constexpr auto operator!=(const music_type lhs,
                                        const Mix_MusicType rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/**
 * \copydoc operator!=(music_type, Mix_MusicType)
 */
[[nodiscard]] constexpr auto operator!=(const Mix_MusicType lhs,
                                        const music_type rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \}

}  // namespace cen

#endif  // CENTURION_MUSIC_HEADER