#ifndef CENTURION_MUSIC_HEADER
#define CENTURION_MUSIC_HEADER

#ifndef CENTURION_NO_SDL_MIXER

  #include <SDL_mixer.h>

  #include <cassert>   // assert
  #include <memory>    // unique_ptr
  #include <optional>  // optional
  #include <ostream>   // ostream
  #include <string>    // string, to_string

  #include "../core/czstring.hpp"
  #include "../core/exception.hpp"
  #include "../core/not_null.hpp"
  #include "../core/result.hpp"
  #include "../core/time.hpp"
  #include "../detail/address_of.hpp"
  #include "../detail/any_eq.hpp"
  #include "../detail/clamp.hpp"
  #include "../detail/max.hpp"

namespace cen {

/// \addtogroup audio
/// \{

/**
 * \enum fade_status
 *
 * \brief Provides values that represent different fade playback states.
 *
 * \since 3.0.0
 *
 * \see `Mix_Fading`
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
 * \brief Provides values that represent different supported music types.
 *
 * \since 3.0.0
 *
 * \see `Mix_MusicType`
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
 *   - WAVE/RIFF (.wav)
 *   - AIFF (.aiff)
 *   - VOC (.voc)
 *   - MOD (.mod .xm .s3m .669 .it .med and more)
 *   - MIDI (.mid)
 *   - OggVorbis (.ogg)
 *   - MP3 (.mp3)
 *   - FLAC (.flac)
 *
 * \note Only one music instance can ever be playing at any time, which means that many of
 * the functions in this class are static.
 *
 * \todo Look into special effects API (also applies for sound effects).
 *
 * \see `Mix_Music`
 * \see `sound_effect`
 *
 * \since 3.0.0
 */
class music final
{
 public:
  /**
   * \brief A constant that indicates that the music should be looped indefinitely.
   *
   * \since 5.1.0
   */
  inline constexpr static int forever = -1;

  /// \name Construction
  /// \{

  /**
   * \brief Creates a `music` instance based on the file at the specified path.
   *
   * \param file the file path of the music file that will be loaded, cannot be null.
   *
   * \throws mix_error if the music file cannot be loaded.
   *
   * \since 3.0.0
   */
  explicit music(const not_null<czstring> file) : m_music{Mix_LoadMUS(file)}
  {
    if (!m_music)
    {
      throw mix_error{};
    }
  }

  /**
   * \brief Creates a `music` instance based on the file at the specified path.
   *
   * \param file the file path of the music file that will be loaded.
   *
   * \throws mix_error if the music file cannot be loaded.
   *
   * \since 5.3.0
   */
  explicit music(const std::string& file) : music{file.c_str()}
  {}

  /// \} End of construction

  /// \name Playback functions
  /// \{

  /**
   * \brief Plays the music associated with this instance.
   *
   * \details Any previously playing music will be halted. However, this method will wait
   * for music that was fading out to complete.
   *
   * \note The term loops is a little bit confusing here, even in the SDL_mixer
   * documentation. A negative value indicates that the music should be played forever.
   * Furthermore, the values 0 and 1 both results in the music being played *one time*.
   * Except for these "special" values, the function behaves as expected.
   *
   * \param nLoops the number of times to loop the music, `music::forever` can
   * be supplied to loop the music indefinitely.
   *
   * \return the channel used to play the music; `std::nullopt` on failure.
   *
   * \see `music::forever`
   *
   * \since 3.0.0
   */
  auto play(const int nLoops = 0) noexcept -> std::optional<int>
  {
    const auto channel = Mix_PlayMusic(m_music.get(), detail::max(nLoops, forever));
    if (channel != -1)
    {
      return channel;
    }
    else
    {
      return std::nullopt;
    }
  }

  /**
   * \brief Resumes playing the music.
   *
   * \details This method can safely be invoked with halted, paused and even currently
   * playing music.
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
   * \note This method only affects music that is currently playing, which doesn't include
   * music that is being faded in/out.
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
    Mix_HaltMusic();  // This appears to always return 0
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

  /// \} Playback functions

  /// \name Fade functions
  /// \{

  /**
   * \brief Plays the music by fading it in by the specified amount of time.
   *
   * \pre `ms` must be greater than zero.
   *
   * \details The fade effect is only applied to the first iteration of the playback of
   * the music. Any previously playing music will be halted. However, if other music is
   * currently being faded out, this music will wait for that to complete.
   *
   * \note The term loops is a little bit confusing here, even in the SDL_mixer
   * documentation. A negative value indicates that the music should be played forever.
   * Furthermore, the values 0 and 1 both results in the music being played *one time*.
   * Except for these "special" values, the method behaves as expected.
   *
   * \param ms the amount of time it takes for the fade to complete.
   *
   * \param nLoops the number of iterations to play the music, `music::forever` can be
   * supplied to loop the music indefinitely.
   *
   * \return `success` if the fade is successful; `failure` otherwise.
   *
   * \see `music::forever`
   *
   * \since 3.0.0
   */
  auto fade_in(const milliseconds<int> ms,
               const int nLoops = 0) noexcept(noexcept(ms.count())) -> result
  {
    assert(ms.count() > 0);
    return Mix_FadeInMusic(m_music.get(), detail::max(nLoops, forever), ms.count()) == 0;
  }

  /**
   * \brief Fades out any currently playing music over the specified amount of time.
   *
   * \pre `ms` must be greater than zero.
   *
   * \details This method only affects music that is currently playing and not currently
   * fading out. In other words, this method has no effect if music is currently being
   * faded by the time the method is invoked.
   *
   * \param ms the amount of time for the fade to complete, in milliseconds.
   *
   * \return `success` if the fade is successful; `failure` on failure.
   *
   * \since 3.0.0
   */
  static auto fade_out(const milliseconds<int> ms) noexcept(noexcept(ms.count()))
      -> result
  {
    assert(ms.count() > 0);
    if (!is_fading())
    {
      return Mix_FadeOutMusic(ms.count()) != 0;
    }
    else
    {
      return failure;
    }
  }

  /**
   * \brief Indicates whether or not any music is currently being faded in or out.
   *
   * \return `true` if music is currently being faded in or out; `false` otherwise.
   *
   * \since 3.0.0
   */
  [[nodiscard]] static auto is_fading() noexcept -> bool
  {
    return detail::any_eq(get_fade_status(), fade_status::in, fade_status::out);
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

  /// \} End of fade functions

  /// \name Playback position functions
  /// \{

  /**
   * \brief Rewinds the music stream to the initial position.
   *
   * \see `Mix_RewindMusic`
   *
   * \since 6.0.0
   */
  static void rewind() noexcept
  {
    Mix_RewindMusic();
  }

  /**
   * \brief Sets the position in the music stream.
   *
   * \param position the new music stream position.
   *
   * \return `success` if the music position was successfully changed; `failure`
   * otherwise.
   *
   * \see `Mix_SetMusicPosition`
   *
   * \since 6.0.0
   */
  static auto set_position(const double position) noexcept -> result
  {
    return Mix_SetMusicPosition(position) == 0;
  }

  /// \} End of playback position functions

  /// \name Volume functions
  /// \{

  /**
   * \brief Sets the volume of all music.
   *
   * \param volume the volume that will be used, in the range [0, `music::max_volume()`].
   * An out-of-bounds value will be clamped to the closest valid value.
   *
   * \since 3.0.0
   */
  static void set_volume(const int volume) noexcept
  {
    Mix_VolumeMusic(detail::clamp(volume, 0, MIX_MAX_VOLUME));
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

  /// \} End of volume functions

  /// \name Conversions
  /// \{

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

  /// \} End of conversions

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
   * \brief Returns a pointer to the associated `Mix_Music` instance.
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

  /// \name Hook functions
  /// \{

  using music_hook_callback = void(SDLCALL*)(void*, u8*, int) noexcept;

  /**
   * \brief Registers a custom music player or mixer function.
   *
   * \param callback the custom callback, can be null to use the default music player.
   * \param data optional data that will be supplied to the callback.
   *
   * \since 6.0.0
   */
  template <typename T = void>
  static void set_hook(music_hook_callback callback, T* data = nullptr) noexcept
  {
    Mix_HookMusic(callback, data);
  }

  /**
   * \brief Resets the music player to the default one.
   *
   * \since 6.0.0
   */
  static void reset_hook() noexcept
  {
    set_hook(nullptr);
  }

  /**
   * \brief Returns a pointer to the user data associated with the music player.
   *
   * \return a pointer to the music player data, might be null.
   *
   * \since 6.0.0
   */
  [[nodiscard]] static auto get_hook_data() noexcept -> void*
  {
    return Mix_GetMusicHookData();
  }

  /// \} End of hook functions

  /// \name Decoder functions
  /// \{

  /**
   * \brief Returns the name of the decoder associated with the specified index.
   *
   * \param index the index of the desired decoder.
   *
   * \return the name of the decoder associated with the specified index; a null string is
   * returned if the index is invalid.
   *
   * \see `Mix_GetMusicDecoder`
   *
   * \since 6.0.0
   */
  [[nodiscard]] static auto get_decoder(const int index) noexcept -> czstring
  {
    return Mix_GetMusicDecoder(index);
  }

  /**
   * \brief Indicates whether or not the system has the specified music decoder.
   *
   * \param name the name of the decoder to check.
   *
   * \return `true` if the system has the specified decoder; `false` otherwise.
   *
   * \see `Mix_HasMusicDecoder`
   *
   * \since 6.0.0
   */
  [[nodiscard]] static auto has_decoder(const czstring name) noexcept -> bool
  {
    return Mix_HasMusicDecoder(name) == SDL_TRUE;
  }

  /**
   * \brief Returns the number of available music decoders.
   *
   * \return the number of available music decoders.
   *
   * \see `Mix_GetNumMusicDecoders`
   *
   * \since 6.0.0
   */
  [[nodiscard]] static auto decoder_count() noexcept -> int
  {
    return Mix_GetNumMusicDecoders();
  }

  /// \} End of decoder functions

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

/// \name Callbacks
/// \{

using music_finished_callback = void(SDLCALL*)() noexcept;

/**
 * \brief Sets the callback that is invoked each time the music finishes playing or is
 * stopped as a result of `cen::music::halt()`.
 *
 * \warning Make sure that your callback doesn't throw (or at least doesn't leak) any
 * exceptions.
 *
 * \param callback the callback.
 *
 * \since 6.0.0
 */
inline void on_music_finished(music_finished_callback callback) noexcept
{
  Mix_HookMusicFinished(callback);
}

/// \} End of callbacks

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
  return "music{data: " + detail::address_of(music.get()) +
         ", volume: " + std::to_string(music::volume()) + "}";
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
inline auto operator<<(std::ostream& stream, const music& music) -> std::ostream&
{
  return stream << to_string(music);
}

/// \name Music-related comparison operators
/// \{

/**
 * \brief Indicates whether or not the fading status values represent are the same.
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

/// \copydoc operator==(fade_status, Mix_Fading)
[[nodiscard]] constexpr auto operator==(const Mix_Fading lhs,
                                        const fade_status rhs) noexcept -> bool
{
  return rhs == lhs;
}

/**
 * \brief Indicates whether or not the fading status values represent aren't the same.
 *
 * \param lhs the left-hand side fading status value.
 * \param rhs the right-hand side fading status value.
 *
 * \return `true` if the fading status values aren't the same; `false` otherwise.
 *
 * \since 5.0.0
 */
[[nodiscard]] constexpr auto operator!=(const fade_status lhs,
                                        const Mix_Fading rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \copydoc operator!=(fade_status, Mix_Fading)
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
                                        const Mix_MusicType rhs) noexcept -> bool
{
  return static_cast<Mix_MusicType>(lhs) == rhs;
}

/// \copydoc operator==(music_type, Mix_MusicType)
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
                                        const Mix_MusicType rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \copydoc operator!=(music_type, Mix_MusicType)
[[nodiscard]] constexpr auto operator!=(const Mix_MusicType lhs,
                                        const music_type rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \} End of music-related comparison operators
/// \} End of group audio

}  // namespace cen

#endif  // CENTURION_NO_SDL_MIXER
#endif  // CENTURION_MUSIC_HEADER