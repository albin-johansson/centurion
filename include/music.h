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

#ifndef CENTURION_MUSIC_HEADER
#define CENTURION_MUSIC_HEADER

#include <SDL_mixer.h>

#include "centurion_api.h"
#include "centurion_utils.h"

namespace centurion {

/**
 * @enum FadeStatus
 * @brief Mirrors the values of the Mix_Fading enum.
 * @headerfile music.h
 * @since 3.0.0
 */
enum class FadeStatus {
  None = MIX_NO_FADING, /**< No currently fading music. */
  In = MIX_FADING_IN,   /**< Currently fading in music. */
  Out = MIX_FADING_OUT  /**< Currently fading out music. */
};

/**
 * Indicates whether or not the fading status values represent the same thing.
 *
 * @param lhs the Centurion fade status value.
 * @param rhs the SDL fade status value.
 * @return true if the fading status hints represent the same thing.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator==(FadeStatus lhs, Mix_Fading rhs) noexcept;

/**
 * Indicates whether or not the fading status values represent the same thing.
 *
 * @param lhs the SDL fade status value.
 * @param rhs the Centurion fade status value.
 * @return true if the fading status hints represent the same thing.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator==(Mix_Fading lhs, FadeStatus rhs) noexcept;

/**
 * The MusicType enum class mirrors the values of the Mix_MusicType enum.
 *
 * @since 3.0.0
 */
enum class MusicType {
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
 * Indicates whether or not the music type values represent the same thing.
 *
 * @param lhs the Centurion music type value.
 * @param rhs the SDL music type value.
 * @return true if the music type values represent the same thing.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator==(MusicType lhs, Mix_MusicType rhs) noexcept;

/**
 * Indicates whether or not the music type values represent the same thing.
 *
 * @param lhs the SDL music type value.
 * @param rhs the Centurion music type value.
 * @return true if the music type values represent the same thing.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator==(Mix_MusicType lhs, MusicType rhs) noexcept;

/**
 * The Music class represents audio files of music. Note! Only one music
 * instance can ever be playing at any time. The supported audio formats are the
 * following: <ul> <li>WAVE/RIFF (.wav)</li> <li>AIFF (.aiff)</li> <li>VOC
 * (.voc)</li> <li>MOD (.mod .xm .s3m .669 .it .med and more)</li> <li>MIDI
 * (.mid)</li> <li>OggVorbis (.ogg)</li> <li>MP3 (.mp3)</li> <li>FLAC
 * (.flac)</li>
 * </ul>
 * @since 3.0.0
 */
class Music final {
 public:
  /**
   * The maximum possible volume value.
   *
   * @since 4.0.0
   */
  static constexpr int maxVolume = MIX_MAX_VOLUME;

  /**
   * A constant that indicates that an audio snippet should be looped
   * indefinitely.
   *
   * @since 4.0.0
   */
  static constexpr int loopForever = -1;

  /**
   * @param file the file path of the music file that will be loaded.
   * @throws CenturionException if the music file cannot be loaded.
   * @since 3.0.0
   */
  CENTURION_API explicit Music(CZString file);

  /**
   * Creates a Music instance by moving the supplied Music instance.
   *
   * @param other the Music instance that will be moved.
   * @since 3.0.0
   */
  CENTURION_API Music(Music&& other) noexcept;

  Music(const Music&) = delete;

  /**
   * @since 3.0.0
   */
  CENTURION_API ~Music() noexcept;

  /**
   * Moves the contents of the supplied Music into this Music instance.
   *
   * @param other the Music instance that will be moved.
   * @return the assigned Music instance.
   * @since 3.0.0
   */
  CENTURION_API Music& operator=(Music&& other) noexcept;

  Music& operator=(const Music&) = delete;

  /**
   * Creates and returns a unique pointer to a Music instance.
   *
   * @param file the file path of the music file that will be loaded.
   * @return a unique pointer to a Music instance.
   * @throws CenturionException if the music file cannot be loaded.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static UniquePtr<Music> unique(CZString file);

  /**
   * Creates and returns a shared pointer to a Music instance.
   *
   * @param file the file path of the music file that will be loaded.
   * @return a shared pointer to a Music instance.
   * @throws CenturionException if the music file cannot be loaded.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static SharedPtr<Music> shared(CZString file);

  /**
   * Plays the music. Previously playing music will be halted. However, this
   * method will wait for music that was fading out to complete.
   *
   * @param nLoops the number of times to loop the music, a negative value is
   * indicates that the music should be looped forever. The default value is 1.
   * @since 3.0.0
   */
  CENTURION_API void play(int nLoops = 1) noexcept;

  /**
   * Resumes the music. This method can safely be invoked on halted, paused and
   * even currently playing music.
   *
   * @since 3.0.0
   */
  CENTURION_API static void resume() noexcept;

  /**
   * Pauses any currently playing music. Note! This method only affects music
   * that is currently playing, which doesn't include music that is being faded
   * in/out.
   *
   * @since 3.0.0
   */
  CENTURION_API static void pause() noexcept;

  /**
   * Stops ALL currently playing and fading music. Unlike <code>pause</code>,
   * this method affects all kinds of music.
   *
   * @since 3.0.0
   */
  CENTURION_API static void halt() noexcept;

  /**
   * Plays the music by fading it in by the specified amount of time. The fade
   * effect is only applied to the first iteration of playing the music. Any
   * previously playing music will be halted. However, if other music is
   * currently being faded out, this music will wait for that to complete.
   *
   * @param ms the amount of time for the fade to complete, in milliseconds. A
   * negative value is clamped to 0.
   * @param nLoops the number of iterations to play the music, a value less than
   * -1 will be clamped to -1, which indicates that the music should be played
   * forever.
   * @since 3.0.0
   */
  CENTURION_API void fade_in(int ms, int nLoops = 1) noexcept;

  /**
   * Fades out any currently playing music over the specified amount of time.
   * This method only affects music that is currently playing and not currently
   * fading out. In other words, this method has no effect if music is currently
   * being faded by the time the method is invoked.
   *
   * @param ms the amount of time for the fade to complete, in milliseconds. A
   * negative value is clamped to zero.
   * @since 3.0.0
   */
  CENTURION_API static void fade_out(int ms);

  /**
   * Sets the volume of all music.
   *
   * @param volume the volume that will be used, in the range [0,
   * Music::maxVolume]. An out-of-bounds value will be clamped to the closest
   * valid value.
   * @since 3.0.0
   */
  CENTURION_API static void set_volume(int volume) noexcept;

  /**
   * Indicates whether or not any music is currently playing.
   *
   * @return true if music is currently being played; false otherwise.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static bool playing() noexcept;

  /**
   * Indicates whether or not any music is paused.
   *
   * @return true if any music is paused; false otherwise.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static bool paused() noexcept;

  /**
   * Indicates whether or not any music is currently being faded in or out.
   *
   * @return true if any music is currently being faded in or out; false
   * otherwise.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static bool fading() noexcept;

  /**
   * Returns the volume of all music. The default value is set to
   * Music::maxVolume.
   *
   * @return the volume of all music, in the range [0, Music::maxVolume].
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static int volume() noexcept;

  /**
   * Returns the current fade status of the music playback.
   *
   * @return the current fade status.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static FadeStatus fade_status() noexcept;

  /**
   * Returns the type of the music.
   *
   * @return the type of the music.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API MusicType music_type() const noexcept;

  /**
   * Returns a textual representation of the Music instance.
   *
   * @return a textual representation of the Music instance.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API std::string to_string() const;

  /**
   * Returns a pointer to the internal Mix_Music. Use of this method is
   * not recommended, since it purposefully breaks const-correctness. However
   * it is useful since many SDL calls use non-const pointers even when no
   * change will be applied.
   *
   * @return a pointer to the internal Mix_Music.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  Mix_Music* get() const noexcept { return m_music; }

  /**
   * Converts the Music instance into a pointer to a Mix_Music instance.
   *
   * @return a pointer to the internal Mix_Music instance.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  operator Mix_Music*() noexcept { return m_music; }

  /**
   * Converts the Music instance into a pointer to a Mix_Music instance.
   *
   * @return a pointer to the internal Mix_Music instance.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  operator const Mix_Music*() const noexcept { return m_music; }

 private:
  Mix_Music* m_music = nullptr;

  /**
   * Destroys the resources associated with the Music instance.
   *
   * @since 4.0.0
   */
  void destroy() noexcept;

  /**
   * Moves the contents of the supplied music instance into this instance.
   *
   * @param other the instance that will be moved.
   * @since 4.0.0
   */
  void move(Music&& other) noexcept;
};

#ifdef CENTURION_HAS_IS_FINAL_TYPE_TRAIT
static_assert(std::is_final<Music>::value, "Music isn't final!");
#endif

static_assert(!std::is_nothrow_copy_constructible<Music>::value,
              "Music is copyable!");

static_assert(!std::is_nothrow_copy_assignable<Music>::value,
              "Music is copy assignable!");

static_assert(std::is_nothrow_move_constructible<Music>::value,
              "Music isn't nothrow move constructible!");

static_assert(std::is_nothrow_move_assignable<Music>::value,
              "Music isn't nothrow move assignable!");

static_assert(std::is_convertible<Music, Mix_Music*>::value,
              "Music isn't convertible to Mix_Music*!");

}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "music.cpp"
#endif

#endif  // CENTURION_MUSIC_HEADER