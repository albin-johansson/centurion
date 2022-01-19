#ifndef CENTURION_AUDIO_HPP_
#define CENTURION_AUDIO_HPP_

#ifndef CENTURION_NO_SDL_MIXER

#include <SDL.h>
#include <SDL_mixer.h>

#include <cassert>   // assert
#include <memory>    // unique_ptr
#include <optional>  // optional
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

/**
 * \defgroup audio Audio
 *
 * \brief Provides music and sound effect facilities, based on SDL_mixer.
 */

/// \addtogroup audio
/// \{

/**
 * \brief Represents the various supported music types.
 */
enum class music_type {
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

/// \name Music type functions
/// \{

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

/// \} End of music type functions

/**
 * \brief Represents different playback states.
 */
enum class fade_status {
  none = MIX_NO_FADING,
  in = MIX_FADING_IN,
  out = MIX_FADING_OUT
};

/// \name Fade status functions
/// \{

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

/// \} End of fade status functions

/**
 * \brief Represents a piece of music.
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
 * \note Only one music instance can ever be playing at any time. As a result, many of the
 * functions in this class are static.
 *
 * \see `sound_effect`
 */
class music final {
 public:
  using ms_type = millis<int>;
  using music_hook_callback = void (*)(void*, uint8*, int);

  inline constexpr static int forever = -1;  ///< Used to loop music indefinitely.

  /// \name Construction
  /// \{

  /**
   * \brief Loads a music file.
   *
   * \param file the file path of the music file.
   *
   * \throws mix_error if the music file could not be loaded.
   */
  explicit music(const char* file) : mMusic{Mix_LoadMUS(file)}
  {
    if (!mMusic) {
      throw mix_error{};
    }
  }

  /// \copydoc music(const char*)
  explicit music(const std::string& file) : music{file.c_str()} {}

  /// \} End of construction

  /// \name Ordinary playback functions
  /// \{

  /**
   * \brief Begins playing the music.
   *
   * \details Any previously playing music will be halted. However, this function will
   * wait for music that was fading out to complete.
   *
   * \note A negative value indicates that the music should be played forever (see
   * `music::forever`). Furthermore, specifying `0` and `1` iterations both result in the music
   * being played *one* time. Other than these "special" values, the function behaves as
   * expected.
   *
   * \param iterations the number of times to loop the music; `forever` indicates that the
   * music should loop indefinitely.
   *
   * \return the channel used to play the music; an empty optional is returned on failure.
   *
   * \see `music::forever`
   */
  auto play(const int iterations = 0) noexcept -> std::optional<int>
  {
    const auto channel = Mix_PlayMusic(mMusic.get(), detail::max(iterations, forever));
    if (channel != -1) {
      return channel;
    }
    else {
      return std::nullopt;
    }
  }

  /**
   * \brief Resumes playing the music.
   *
   * \details This function can safely be invoked with halted, paused, and even playing music.
   */
  static void resume() noexcept { Mix_ResumeMusic(); }

  /**
   * \brief Pauses any currently playing music.
   *
   * \note This function only affects music that is currently playing, which does not
   * include music that is being faded in or out.
   *
   * \see `halt()`
   */
  static void pause() noexcept { Mix_PauseMusic(); }

  /**
   * \brief Stops *all* currently playing and fading music.
   *
   * \see `pause()`
   */
  static void halt() noexcept
  {
    Mix_HaltMusic(); /* This appears to always return 0, so we ignore it */
  }

  /**
   * \brief Indicates whether any music is currently playing.
   *
   * \return `true` if music is played; `false` otherwise.
   */
  [[nodiscard]] static auto is_playing() noexcept -> bool { return Mix_PlayingMusic(); }

  /**
   * \brief Indicates whether or the music is paused.
   *
   * \return `true` if the music is paused; `false` otherwise.
   */
  [[nodiscard]] static auto is_paused() noexcept -> bool { return Mix_PausedMusic(); }

  /// \} End of ordinary playback functions

  /// \name Fade functions
  /// \{

  /**
   * \brief Plays the music by fading it in by the specified amount of time.
   *
   * \pre `duration` must be greater than zero.
   *
   * \details The fade effect is only applied to the first iteration of the playback of
   * the music. Any previously playing music will be halted. However, if other music is
   * currently being faded out, this music will wait for that to complete.
   *
   * \param duration the amount of time it takes for the fade to complete.
   * \param iterations the amount of times to play the music; use `music::forever` to play the
   * music indefinitely.
   *
   * \return `success` if the fade is successful; `failure` otherwise.
   *
   * \see `play()`
   * \see `fade_out()`
   * \see `music::forever`
   */
  auto fade_in(const ms_type duration,
               const int iterations = 0) noexcept(noexcept(duration.count())) -> result
  {
    assert(duration.count() > 0);
    return Mix_FadeInMusic(mMusic.get(), detail::max(iterations, forever), duration.count()) ==
           0;
  }

  /**
   * \brief Fades out any currently playing music over the specified amount of time.
   *
   * \pre `duration` must be greater than zero.
   *
   * \details This function only affects music that is currently playing and not currently
   * fading out. In other words, this function has no effect if music is currently being
   * faded by the time the function is invoked.
   *
   * \param duration the amount of time for the fade to complete.
   *
   * \return `success` if the fade is successful; `failure` otherwise.
   *
   * \see `fade_in()`
   */
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

  /**
   * \brief Returns the fade status of the current music playback.
   *
   * \return the current fade status.
   *
   * \see `is_fading()`
   */
  [[nodiscard]] static auto get_fade_status() noexcept -> fade_status
  {
    return static_cast<fade_status>(Mix_FadingMusic());
  }

  /**
   * \brief Indicates whether any music is currently being faded in or out.
   *
   * \return `true` if music is being faded; `false` otherwise.
   */
  [[nodiscard]] static auto is_fading() noexcept -> bool
  {
    const auto status = get_fade_status();
    return status == fade_status::in || status == fade_status::out;
  }

  // TODO is_fading_in()
  // TODO is_fading_out()

  /// \} End of fade functions

  /// \name Playback position functions
  /// \{

  /**
   * \brief Rewinds the music stream to the initial position.
   */
  static void rewind() noexcept { Mix_RewindMusic(); }

  /**
   * \brief Sets the position in the music stream.
   *
   * \param position the new stream position.
   *
   * \return `success` if the position was successfully changed; `failure` otherwise.
   */
  static auto set_position(const double position) noexcept -> result
  {
    return Mix_SetMusicPosition(position) == 0;
  }

  /// \} End of playback position functions

  /// \name Volume functions
  /// \{

  /**
   * \brief Sets the overall volume of all music.
   *
   * \details An out-of-bounds volume will be clamped to the closest valid value.
   *
   * \param volume the volume that will be used, in the range [0, `music::max_volume()`].
   */
  static void set_volume(const int volume) noexcept
  {
    Mix_VolumeMusic(detail::clamp(volume, 0, MIX_MAX_VOLUME));
  }

  /**
   * \brief Returns the volume of the music.
   *
   * \details The default volume is equivalent to `music::max_volume()`.
   *
   * \return the music volume, in the range [0, `music::max_volume()`].
   */
  [[nodiscard]] static auto volume() noexcept -> int { return Mix_VolumeMusic(-1); }

  /**
   * \brief Returns the maximum possible volume.
   *
   * \return the maximum volume (equal to `MIX_MAX_VOLUME`).
   */
  [[nodiscard]] constexpr static auto max_volume() noexcept -> int { return MIX_MAX_VOLUME; }

  /// \} End of volume functions

  /// \name Hook functions
  /// \{

  /**
   * \brief Registers a custom music player or mixer function.
   *
   * \param callback the custom callback, can be null to use the default music player.
   * \param data optional user data that will be supplied to the callback.
   *
   * \see `reset_hook()`
   */
  template <typename T = void>
  static void set_hook(music_hook_callback callback, T* data = nullptr) noexcept
  {
    Mix_HookMusic(callback, data);
  }

  /**
   * \brief Resets the music player to the default one.
   */
  static void reset_hook() noexcept { set_hook(nullptr); }

  /**
   * \brief Returns the user data associated with the music player.
   *
   * \return the music player data, might be null.
   */
  [[nodiscard]] static auto hook_data() noexcept -> void* { return Mix_GetMusicHookData(); }

  /// \} End of hook functions

  /// \name Decoder functions
  /// \{

  /**
   * \brief Indicates whether the system has the specified music decoder.
   *
   * \param name the name of the decoder to check.
   *
   * \return `true` if the system has the specified decoder; `false` otherwise.
   */
  [[nodiscard]] static auto has_decoder(const char* name) noexcept -> bool
  {
    return Mix_HasMusicDecoder(name) == SDL_TRUE;
  }

  /**
   * \brief Returns the name of the decoder associated with the specified index.
   *
   * \param index the index of the desired decoder.
   *
   * \return the name of the decoder associated with the index; a null string is returned for
   * an invalid index.
   */
  [[nodiscard]] static auto get_decoder(const int index) noexcept -> const char*
  {
    return Mix_GetMusicDecoder(index);
  }

  /**
   * \brief Returns the number of available music decoders.
   *
   * \return the amount of decoders.
   */
  [[nodiscard]] static auto decoder_count() noexcept -> int
  {
    return Mix_GetNumMusicDecoders();
  }

  /// \} End of decoder functions

  /// \name Misc functions
  /// \{

  /**
   * \brief Returns the type of the associated music file.
   *
   * \return the music type.
   */
  [[nodiscard]] auto type() const noexcept -> music_type
  {
    return static_cast<music_type>(Mix_GetMusicType(mMusic.get()));
  }

  [[nodiscard]] auto get() const noexcept -> Mix_Music* { return mMusic.get(); }

  /// \} End of of misc functions

 private:
  managed_ptr<Mix_Music> mMusic;

#ifdef CENTURION_MOCK_FRIENDLY_MODE

 public:
  music() = default;

#endif  // CENTURION_MOCK_FRIENDLY_MODE
};

/// \name Music functions
/// \{

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

/// \} End of music functions

template <typename T>
class basic_sound_effect;

using sound_effect = basic_sound_effect<detail::owner_tag>;          ///< An owning sound.
using sound_effect_handle = basic_sound_effect<detail::handle_tag>;  ///< A non-owning sound.

/**
 * \brief Represents a sound effect.
 *
 * \ownerhandle `sound_effect`/`sound_effect_handle`
 *
 * \details Unlike with the music API, multiple sound effects can be played at the same
 * time, which is one of the main difference between the `music` and `sound_effect` APIs.
 *
 * \details The supported file formats are the following:
 *   - WAVE/RIFF (.wav)
 *   - AIFF (.aiff)
 *   - VOC (.voc)
 *   - OGG (.ogg)
 *   - VOC (.voc)
 *
 * \see `music`
 * \see `get_sound()`
 */
template <typename T>
class basic_sound_effect final {
 public:
  using ms_type = millis<int>;

  inline constexpr static int forever = -1;  ///< Used to play sounds indefinitely.

  /// \name Construction
  /// \{

  /**
   * \brief Creates a sound effect based on an existing SDL sound.
   *
   * \note The created sound effect claims ownership of the supplied pointer only if the
   * sound effect has owning semantics.
   *
   * \param sound a pointer to the associated chunk.
   *
   * \throws mix_error if the supplied pointer is null and the sound effect is owning.
   */
  explicit basic_sound_effect(maybe_owner<Mix_Chunk*> sound) noexcept(detail::is_handle<T>)
      : mChunk{sound}
  {
    if constexpr (detail::is_owner<T>) {
      if (!mChunk) {
        throw mix_error{};
      }
    }
  }

  /**
   * \brief Loads a sound effect at the specified file path.
   *
   * \param file the file path of the sound file.
   *
   * \throws mix_error if the file cannot be loaded.
   */
  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  explicit basic_sound_effect(const char* file) : mChunk{Mix_LoadWAV(file)}
  {
    if (!mChunk) {
      throw mix_error{};
    }
  }

  /// \copydoc basic_sound_effect(const char*)
  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  explicit basic_sound_effect(const std::string& file) : basic_sound_effect{file.c_str()}
  {}

  template <typename TT = T, detail::enable_for_handle<TT> = 0>
  explicit basic_sound_effect(const sound_effect& owner) noexcept : mChunk{owner.get()}
  {}

  /// \} End of construction

  /// \name Ordinary playback functions
  /// \{

  /**
   * \brief Begins playing the sound effect.
   *
   * \param iterations the amount of loops; use `sound_effect::forever` to loop indefinitely.
   *
   * \return `success` if the sound was played successfully; `failure` otherwise.
   *
   * \see `sound_effect::forever`
   */
  auto play(const int iterations = 0) noexcept -> result
  {
    mChannel = Mix_PlayChannel(mChannel, mChunk.get(), detail::max(iterations, forever));
    return mChannel != -1;
  }

  /**
   * \brief Stops playing the sound effect.
   */
  void stop() noexcept
  {
    if (is_playing()) {
      Mix_Pause(mChannel);
      mChannel = undefined_channel();
    }
  }

  /**
   * \brief Indicates whether the sound effect is currently playing.
   *
   * \return `true` if the sound effect is playing; `false` otherwise.
   */
  [[nodiscard]] auto is_playing() const noexcept -> bool
  {
    return (mChannel != undefined_channel()) && Mix_Playing(mChannel);
  }

  /**
   * \brief Indicates whether any sound effect is currently playing.
   *
   * \return `true` if a sound effect is playing; `false` otherwise.
   */
  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  [[nodiscard]] static auto is_any_playing() noexcept -> bool
  {
    return Mix_Playing(undefined_channel());
  }

  /// \} End of ordinary playback functions

  /// \name Fade functions
  /// \{

  /**
   * \brief Fades in the sound effect.
   *
   * \pre `duration` must be greater than zero.
   *
   * \details This function has no effect if the sound effect is currently playing.
   *
   * \param duration the duration to fade in.
   */
  void fade_in(const ms_type duration) noexcept(noexcept(duration.count()))
  {
    assert(duration.count() > 0);
    if (!is_playing()) {
      mChannel = Mix_FadeInChannel(mChannel, get(), 0, duration.count());
    }
  }

  /**
   * \brief Fades out the sound effect.
   *
   * \pre `duration` must be greater than zero.
   *
   * \details This function has no effect if the sound effect isn't currently playing.
   *
   * \param duration the duration to fade in.
   */
  void fade_out(const ms_type duration) noexcept(noexcept(duration.count()))  // NOLINT
  {
    assert(duration.count() > 0);
    if (is_playing()) {
      Mix_FadeOutChannel(mChannel, duration.count());
    }
  }

  /**
   * \brief Indicates whether the sound effect is being faded.
   *
   * \note Sound effects that are being faded are also playing, so `is_playing()` will
   * also return `true`. Keep this in mind if you plan to differentiate between the two cases.
   *
   * \return `true` if the sound effect is fading; `false` otherwise.
   */
  [[nodiscard]] auto is_fading() const noexcept -> bool
  {
    return is_playing() && Mix_FadingChannel(mChannel);
  }

  /// \} End of fade functions

  /// \name Volume functions
  /// \{

  /**
   * \brief Sets the volume of the sound effect.
   *
   * \details Invalid volumes will be clamped to the closest valid volume.
   *
   * \param volume the volume of the sound, in the range [0, `sound_effect::max_volume()`].
   */
  void set_volume(const int volume) noexcept
  {
    Mix_VolumeChunk(mChunk.get(), detail::clamp(volume, 0, max_volume()));
  }

  /**
   * \brief Returns the current volume of the sound effect.
   *
   * \details By default, the volume is set to `max_volume()`.
   *
   * \return the volume of the sound.
   */
  [[nodiscard]] auto volume() const noexcept -> int { return mChunk->volume; }

  /**
   * \brief Returns the maximum possible volume value.
   *
   * \return the maximum volume.
   */
  [[nodiscard]] constexpr static auto max_volume() noexcept -> int { return MIX_MAX_VOLUME; }

  /// \} End of volume functions

  /// \name Decoder functions
  /// \{

  /**
   * \brief Indicates whether the system has the specified sound effect decoder.
   *
   * \param name the name of the decoder to check.
   *
   * \return `true` if the system has the specified decoder; `false` otherwise.
   */
  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  [[nodiscard]] static auto has_decoder(const char* name) noexcept -> bool
  {
    return Mix_HasChunkDecoder(name) == SDL_TRUE;
  }

  /**
   * \brief Returns the name of the decoder associated with the specified index.
   *
   * \param index the index of the desired decoder.
   *
   * \return the name of the decoder associated with the index; a null string is returned if
   * the index is invalid.
   */
  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  [[nodiscard]] static auto get_decoder(const int index) noexcept -> const char*
  {
    return Mix_GetChunkDecoder(index);
  }

  /**
   * \brief Returns the number of available sound effect decoders.
   *
   * \return the amount of sound effect decoders.
   */
  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  [[nodiscard]] static auto decoder_count() noexcept -> int
  {
    return Mix_GetNumChunkDecoders();
  }

  /// \} End of decoder functions

  /// \name Misc functions
  /// \{

  /**
   * \brief Returns the channel associated with the sound effect, if any.
   *
   * \note Channels are not associated with sound effects for long, and might change in between
   * playbacks.
   *
   * \return the channel currently associated with the sound effect; an empty optional is
   * returned if there is none.
   */
  [[nodiscard]] auto channel() const noexcept -> std::optional<int>
  {
    if (mChannel != undefined_channel()) {
      return mChannel;
    }
    else {
      return std::nullopt;
    }
  }

  [[nodiscard]] auto get() const noexcept -> Mix_Chunk* { return mChunk.get(); }

  /// \} End of misc functions

 private:
  detail::pointer<T, Mix_Chunk> mChunk;
  int mChannel{undefined_channel()};

  [[nodiscard]] constexpr static auto undefined_channel() noexcept -> int { return -1; }

#ifdef CENTURION_MOCK_FRIENDLY_MODE

 public:
  void set_channel(const int channel) noexcept { mChannel = channel; }

#endif  // CENTURION_MOCK_FRIENDLY_MODE
};

/// \name Sound effect functions
/// \{

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

/**
 * \brief Returns a handle to the sound currently associated with a specific channel.
 *
 * \param channel the index of the channel to query.
 *
 * \return a handle to the sound effect associated with the specified channel; an empty handle
 * is returned if no sound is associated with the channel.
 */
[[nodiscard]] inline auto get_sound(const int channel) noexcept -> sound_effect_handle
{
  return sound_effect_handle{Mix_GetChunk(channel)};
}

/// \} End of sound effect functions

/// \} End of group audio

}  // namespace cen

#endif  // CENTURION_NO_SDL_MIXER
#endif  // CENTURION_AUDIO_HPP_
