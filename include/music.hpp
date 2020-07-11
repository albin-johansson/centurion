/*
 * MIT License
 *
 * Copyright (c) 2019-2020 Albin Johansson
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

/**
 * @file music.hpp
 *
 * @brief Provides the music API.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

#ifndef CENTURION_MUSIC_HEADER
#define CENTURION_MUSIC_HEADER

#include <SDL_mixer.h>

#include "centurion_api.hpp"
#include "centurion_types.hpp"
#include "centurion_utils.hpp"

namespace centurion {

/**
 * @enum FadeStatus
 *
 * @brief Mirrors the values of the `Mix_Fading` enum.
 *
 * @since 3.0.0
 *
 * @headerfile music.hpp
 */
enum class fade_status {
  none = MIX_NO_FADING, /**< No currently fading music. */
  in = MIX_FADING_IN,   /**< Currently fading in music. */
  out = MIX_FADING_OUT  /**< Currently fading out music. */
};

/**
 * @brief Indicates whether or not the fading status values represent are the
 * same.
 *
 * @param lhs the left-hand side fading status value.
 * @param rhs the right-hand side fading status value.
 *
 * @return `true` if the fading status values are the same; `false` otherwise.
 *
 * @since 3.0.0
 */
[[nodiscard]] inline constexpr auto operator==(fade_status lhs,
                                               Mix_Fading rhs) noexcept -> bool
{
  return static_cast<Mix_Fading>(lhs) == rhs;
}

/**
 * @copydoc operator==(fade_status, Mix_Fading)
 */
[[nodiscard]] inline constexpr auto operator==(Mix_Fading lhs,
                                               fade_status rhs) noexcept -> bool
{
  return rhs == lhs;
}

/**
 * @brief Indicates whether or not the fading status values represent aren't the
 * same.
 *
 * @param lhs the left-hand side fading status value.
 * @param rhs the right-hand side fading status value.
 *
 * @return `true` if the fading status values aren't the same; `false`
 * otherwise.
 *
 * @since 5.0.0
 */
[[nodiscard]] inline constexpr auto operator!=(fade_status lhs,
                                               Mix_Fading rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/**
 * @copydoc operator!=(fade_status, Mix_Fading)
 */
[[nodiscard]] inline constexpr auto operator!=(Mix_Fading lhs,
                                               Mix_Fading rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/**
 * @enum music_type
 *
 * @brief Mirrors the values of the `Mix_MusicType` enum.
 *
 * @since 3.0.0
 *
 * @headerfile music.hpp
 */
enum class music_type {
  Unknown = MUS_NONE,
  MP3 = MUS_MP3,
  WAV = MUS_WAV,
  OGG = MUS_OGG,
  MOD = MUS_MOD,
  MIDI = MUS_MID,
  CMD = MUS_CMD,
  FLAC = MUS_FLAC,
  OPUS = MUS_OPUS
};

/**
 * @brief Indicates whether or not the music type values are the same.
 *
 * @param lhs the left-hand side music type value.
 * @param rhs the right-hand side music type value.
 *
 * @return `true` if the music type values are the same; `false` otherwise.
 *
 * @since 3.0.0
 */
[[nodiscard]] inline constexpr auto operator==(music_type lhs,
                                               Mix_MusicType rhs) noexcept
    -> bool
{
  return static_cast<Mix_MusicType>(lhs) == rhs;
}

/**
 * @copydoc operator==(music_type, Mix_MusicType)
 */
[[nodiscard]] inline constexpr auto operator==(Mix_MusicType lhs,
                                               music_type rhs) noexcept -> bool
{
  return rhs == lhs;
}

/**
 * @brief Indicates whether or not the music type values aren't the same.
 *
 * @param lhs the left-hand side music type value.
 * @param rhs the right-hand side music type value.
 *
 * @return `true` if the music type values aren't the same; `false` otherwise.
 *
 * @since 5.0.0
 */
[[nodiscard]] inline constexpr auto operator!=(music_type lhs,
                                               Mix_MusicType rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/**
 * @copydoc operator!=(music_type, Mix_MusicType)
 */
[[nodiscard]] inline constexpr auto operator!=(Mix_MusicType lhs,
                                               music_type rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/**
 * @class music
 *
 * @brief Represents a music file.
 *
 * @details The supported audio formats are the following:
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
 * @note Only one music instance can ever be playing at any time.
 *
 * @see `Mix_Music`
 *
 * @since 3.0.0
 *
 * @headerfile music.hpp
 */
class music final {
 public:
  /**
   * @brief The maximum possible volume value.
   *
   * @since 4.0.0
   */
  inline static constexpr int maxVolume = MIX_MAX_VOLUME;

  /**
   * @brief A constant that indicates that an audio snippet should be looped
   * indefinitely.
   *
   * @since 4.0.0
   */
  inline static constexpr int loopForever = -1;

  /**
   * @brief Creates a `music` instance based on the file at the specified path.
   *
   * @param file the file path of the music file that will be loaded.
   *
   * @throws centurion_exception if the music file cannot be loaded.
   *
   * @since 3.0.0
   */
  CENTURION_API
  explicit music(czstring file);

  /**
   * @brief Creates a `music` instance by moving the supplied instance.
   *
   * @param other the instance that will be moved.
   *
   * @since 3.0.0
   */
  CENTURION_API
  music(music&& other) noexcept;

  music(const music&) = delete;

  CENTURION_API
  ~music() noexcept;

  /**
   * Moves the contents of the supplied Music into this Music instance.
   *
   * @param other the Music instance that will be moved.
   * @return the assigned Music instance.
   * @since 3.0.0
   */
  CENTURION_API
  auto operator=(music&& other) noexcept -> music&;

  auto operator=(const music&) -> music& = delete;

  /**
   * @copydoc music(czstring)
   */
  CENTURION_QUERY
  static auto unique(czstring file) -> std::unique_ptr<music>;

  /**
   * @copydoc music(czstring)
   */
  CENTURION_QUERY
  static auto shared(czstring file) -> std::shared_ptr<music>;

  /**
   * @brief Plays the music associated with this instance.
   *
   * @details Any previously playing music will be halted. However, this
   * method will wait for music that was fading out to complete.
   *
   * @note The term loops is a little bit confusing here, even in the SDL_mixer documentation. A
   * negative value indicates that the music should be played forever. Furthermore, the values 0
   * and 1 both results in the music being played *one time*. Except for these "special" values,
   * the method behaves as expected.
   *
   * @param nLoops the number of times to loop the music, a negative value is
   * indicates that the music should be looped forever. The default value is 1.
   *
   * @since 3.0.0
   */
  CENTURION_API
  void play(int nLoops = 1) noexcept;

  /**
   * @brief Resumes playing the music.
   *
   * @details This method can safely be invoked with halted, paused and even
   * currently playing music.
   *
   * @since 3.0.0
   */
  CENTURION_API
  static void resume() noexcept;

  /**
   * @brief Pauses any currently playing music.
   *
   * @note This method only affects music that is currently playing, which
   * doesn't include music that is being faded in/out.
   *
   * @since 3.0.0
   */
  CENTURION_API
  static void pause() noexcept;

  /**
   * @brief Stops ALL currently playing and fading music.
   *
   * @details Unlike `pause()`, this method affects all kinds of music.
   *
   * @since 3.0.0
   */
  CENTURION_API
  static void halt() noexcept;

  /**
   * @brief Plays the music by fading it in by the specified amount of time.
   *
   * @details The fade effect is only applied to the first iteration of
   * the playback of the music. Any previously playing music will be halted.
   * However, if other music is currently being faded out, this music will
   * wait for that to complete.
   *
   * @note The term loops is a little bit confusing here, even in the SDL_mixer documentation. A
   * negative value indicates that the music should be played forever. Furthermore, the values 0
   * and 1 both results in the music being played *one time*. Except for these "special" values,
   * the method behaves as expected.
   *
   * @param ms the amount of time for the fade to complete, in milliseconds. A
   * negative value is clamped to 0.
   *
   * @param nLoops the number of iterations to play the music, a negative value
   * indicates that the music should be looped forever.
   *
   * @since 3.0.0
   */
  CENTURION_API
  void fade_in(milliseconds<int> ms, int nLoops = 1) noexcept;

  /**
   * @brief Fades out any currently playing music over the specified amount of
   * time.
   *
   * @details This method only affects music that is currently playing and
   * not currently fading out. In other words, this method has no effect if
   * music is currently being faded by the time the method is invoked.
   *
   * @param ms the amount of time for the fade to complete, in milliseconds. A
   * negative value is clamped to zero.
   *
   * @since 3.0.0
   */
  CENTURION_API
  static void fade_out(milliseconds<int> ms) noexcept;

  /**
   * @brief Sets the volume of all music.
   *
   * @param volume the volume that will be used, in the range [0,
   * `music::maxVolume`]. An out-of-bounds value will be clamped to the
   * closest valid value.
   *
   * @since 3.0.0
   */
  CENTURION_API
  static void set_volume(int volume) noexcept;

  /**
   * @brief Indicates whether or not any music is currently playing.
   *
   * @return `true` if music is currently being played; `false` otherwise.
   *
   * @since 3.0.0
   */
  CENTURION_QUERY
  static auto is_playing() noexcept -> bool;

  /**
   * @brief Indicates whether or not any music is paused.
   *
   * @return `true` if the music is paused; `false` otherwise.
   *
   * @since 3.0.0
   */
  CENTURION_QUERY
  static auto is_paused() noexcept -> bool;

  /**
   * @brief Indicates whether or not any music is currently being faded in or
   * out.
   *
   * @return `true` if music is currently being faded in or out; `false`
   * otherwise.
   *
   * @since 3.0.0
   */
  CENTURION_QUERY
  static auto is_fading() noexcept -> bool;

  /**
   * @brief Returns the volume of the music.
   *
   * @details The default value is set to `music::maxVolume`.
   *
   * @return the volume of the music, in the range [0, `music::maxVolume`].
   *
   * @since 3.0.0
   */
  CENTURION_QUERY
  static auto volume() noexcept -> int;

  /**
   * @brief Returns the current fade status of the music playback.
   *
   * @return the current fade status.
   *
   * @since 3.0.0
   */
  CENTURION_QUERY
  static auto get_fade_status() noexcept -> fade_status;

  /**
   * @brief Returns the type of the music.
   *
   * @return the type of the music.
   *
   * @since 3.0.0
   */
  CENTURION_QUERY
  auto type() const noexcept -> music_type;

  /**
   * @brief Returns a textual representation of the instance.
   *
   * @return a textual representation of the `music` instance.
   *
   * @since 3.0.0
   */
  CENTURION_QUERY
  auto to_string() const -> std::string;

  /**
   * @brief Returns a pointer to the associated `Mix_Music`.
   *
   * @warning Use of this method is not recommended, since it purposefully
   * breaks const-correctness. However, it's useful since many SDL calls use
   * non-const pointers even when no change will be applied.
   *
   * @return a pointer to the associated `Mix_Music`.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto get() const noexcept -> Mix_Music* { return m_music; }

  /**
   * @brief Converts to `Mix_Music*`.
   *
   * @return a pointer to the associated `Mix_Music` instance.
   *
   * @since 4.0.0
   */
  [[nodiscard]] explicit operator Mix_Music*() noexcept { return m_music; }

  /**
   * @brief Converts to `const Mix_Music*`.
   *
   * @return a pointer to the associated `Mix_Music` instance.
   *
   * @since 3.0.0
   */
  [[nodiscard]] explicit operator const Mix_Music*() const noexcept
  {
    return m_music;
  }

 private:
  Mix_Music* m_music = nullptr;

  /**
   * @brief Destroys the resources associated with the `music` instance.
   *
   * @since 4.0.0
   */
  void destroy() noexcept;

  /**
   * @brief Moves the contents of the supplied music instance into this
   * instance.
   *
   * @param other the instance that will be moved.
   *
   * @since 4.0.0
   */
  void move(music&& other) noexcept;
};

static_assert(std::is_final_v<music>);
static_assert(!std::is_nothrow_copy_constructible_v<music>);
static_assert(!std::is_nothrow_copy_assignable_v<music>);
static_assert(std::is_nothrow_move_constructible_v<music>);
static_assert(std::is_nothrow_move_assignable_v<music>);

}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "music.cpp"
#endif

#endif  // CENTURION_MUSIC_HEADER