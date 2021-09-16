#ifndef CENTURION_SOUND_EFFECT_HEADER
#define CENTURION_SOUND_EFFECT_HEADER

#ifndef CENTURION_NO_SDL_MIXER

#include <SDL_mixer.h>

#include <cassert>   // assert
#include <memory>    // unique_ptr
#include <optional>  // optional
#include <ostream>   // ostream
#include <string>    // string, to_string

#include "../compiler/features.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

#include "../core/exception.hpp"
#include "../core/not_null.hpp"
#include "../core/owner.hpp"
#include "../core/result.hpp"
#include "../core/str.hpp"
#include "../core/time.hpp"
#include "../detail/address_of.hpp"
#include "../detail/clamp.hpp"
#include "../detail/max.hpp"
#include "../detail/owner_handle_api.hpp"

namespace cen {

/// \addtogroup audio
/// \{

template <typename T>
class basic_sound_effect;

/**
 * \typedef sound_effect
 *
 * \brief Represents an owning sound effect.
 *
 * \since 6.0.0
 */
using sound_effect = basic_sound_effect<detail::owning_type>;

/**
 * \typedef sound_effect_handle
 *
 * \brief Represents a non-owning sound effect.
 *
 * \since 6.0.0
 */
using sound_effect_handle = basic_sound_effect<detail::handle_type>;

/**
 * \class basic_sound_effect
 *
 * \brief Represents a sound effect.
 *
 * \ownerhandle `sound_effect`/`sound_effect_handle`
 *
 * \details Unlike with the music API, multiple sound effects can be played at the same
 * time, which is the main difference between the `music` and `sound_effect` APIs.
 *
 * \details The supported file formats are the following:
 *   - WAVE/RIFF (.wav)
 *   - AIFF (.aiff)
 *   - VOC (.voc)
 *   - OGG (.ogg)
 *   - VOC (.voc)
 *
 * \since 3.0.0
 *
 * \see `Mix_Chunk`
 * \see `music`
 * \see `get_sound()`
 */
template <typename T>
class basic_sound_effect final
{
 public:
  /**
   * \brief Indicates that an audio snippet should be looped indefinitely.
   *
   * \since 5.1.0
   */
  inline constexpr static int forever = -1;

  /// \name Construction
  /// \{

  // clang-format off

  /**
   * \brief Creates a sound effect based on an existing SDL sound effect.
   *
   * \note The created sound effect claims ownership of the supplied pointer only if the
   * sound effect has owning semantics.
   *
   * \param sound a pointer to the associated chunk instance, cannot be null if the sound
   * effect is owning.
   *
   * \throws mix_error if the supplied pointer is null and the sound effect is owning.
   *
   * \since 6.0.0
   */
  explicit basic_sound_effect(maybe_owner<Mix_Chunk*> sound) noexcept(!detail::is_owning<T>())
      : m_chunk{sound}
  {
    if constexpr (detail::is_owning<T>())
    {
      if (!m_chunk)
      {
        throw mix_error{};
      }
    }
  }

  // clang-format on

  /**
   * \brief Creates a sound effect based on the audio file at the specified location.
   *
   * \param file the file path of the audio file, cannot be null.
   *
   * \throws mix_error if the audio file cannot be loaded.
   *
   * \since 3.0.0
   */
  template <typename TT = T, detail::is_owner<TT> = 0>
  explicit basic_sound_effect(const not_null<str> file) : m_chunk{Mix_LoadWAV(file)}
  {
    if (!m_chunk) {
      throw mix_error{};
    }
  }

  /**
   * \brief Creates a sound effect based on the audio file at the specified location.
   *
   * \param file the file path of the audio file.
   *
   * \throws mix_error if the audio file cannot be loaded.
   *
   * \since 5.3.0
   */
  template <typename TT = T, detail::is_owner<TT> = 0>
  explicit basic_sound_effect(const std::string& file) : basic_sound_effect{file.c_str()}
  {}

  /**
   * \brief Creates a sound effect handle to on an existing sound effect.
   *
   * \param owner the owning sound effect.
   *
   * \since 6.0.0
   */
  template <typename TT = T, detail::is_handle<TT> = 0>
  explicit basic_sound_effect(const sound_effect& owner) noexcept : m_chunk{owner.get()}
  {}

  /// \} End of construction

  /// \name Playback functions
  /// \{

  /**
   * \brief Plays the sound effect.
   *
   * \note A negative value indicates that the sound effect should be looped forever.
   *
   * \param nLoops the amount of loops, `sound_effect::forever` can be used to loop the
   * sound effect indefinitely.
   *
   * \return `success` if the sound was played successfully; `failure` otherwise.
   *
   * \see `sound_effect::forever`
   *
   * \since 3.0.0
   */
  auto play(const int nLoops = 0) noexcept -> result
  {
    m_channel = Mix_PlayChannel(m_channel, m_chunk.get(), detail::max(nLoops, forever));
    return m_channel != -1;
  }

  /**
   * \brief Stops the sound effect from playing.
   *
   * \since 3.0.0
   */
  void stop() noexcept
  {
    if (is_playing()) {
      Mix_Pause(m_channel);
      m_channel = undefined_channel();
    }
  }

  /**
   * \brief Indicates whether or not the sound effect is currently playing.
   *
   * \return `true` if the sound effect is playing; `false` otherwise.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto is_playing() const noexcept -> bool
  {
    return (m_channel != undefined_channel()) && Mix_Playing(m_channel);
  }

  /**
   * \brief Indicates whether or not any sound effects are currently playing.
   *
   * \return `true` if any sound effect is playing on some channel; `false` otherwise.
   *
   * \since 5.1.0
   */
  template <typename TT = T, detail::is_owner<TT> = 0>
  [[nodiscard]] static auto is_any_playing() noexcept -> bool
  {
    return Mix_Playing(undefined_channel());
  }

  /// \} End of playback functions

  /// \name Fade functions
  /// \{

  /**
   * \brief Fades in the sound effect.
   *
   * \pre `ms` must be greater than zero.
   *
   * \details This function has no effect if the sound effect is currently playing.
   *
   * \param ms the duration to fade in, in milliseconds.
   *
   * \since 3.0.0
   */
  void fade_in(const milliseconds<int> ms) noexcept(noexcept(ms.count()))
  {
    assert(ms.count() > 0);
    if (!is_playing()) {
      m_channel = Mix_FadeInChannel(m_channel, get(), 0, ms.count());
    }
  }

  /**
   * \brief Fades out the sound effect.
   *
   * \pre `ms` must be greater than zero.
   *
   * \details This function has no effect if the sound effect isn't currently playing.
   *
   * \param ms the duration to fade in, in milliseconds.
   *
   * \since 3.0.0
   */
  void fade_out(const milliseconds<int> ms) noexcept(noexcept(ms.count()))  // NOLINT
  {
    assert(ms.count() > 0);
    if (is_playing()) {
      Mix_FadeOutChannel(m_channel, ms.count());
    }
  }

  /**
   * \brief Indicates whether or not the sound effect is being faded.
   *
   * \note If the sound effect is being faded, it's also playing so `is_playing()` will
   * also return `true`. Keep this in mind if you want to differentiate between the two.
   *
   * \return `true` if the sound effect is being faded; `false` otherwise.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto is_fading() const noexcept -> bool
  {
    return is_playing() && Mix_FadingChannel(m_channel);
  }

  /// \} End of fade functions

  /// \name Volume functions
  /// \{

  /**
   * \brief Sets the volume of the sound effect.
   *
   * \details This function will adjust input values outside the legal range to the
   * closest legal value.
   *
   * \param volume the volume of the sound effect, in the range [0,
   * `sound_effect::max_volume()`].
   *
   * \since 3.0.0
   */
  void set_volume(const int volume) noexcept
  {
    Mix_VolumeChunk(m_chunk.get(), detail::clamp(volume, 0, max_volume()));
  }

  /**
   * \brief Returns the current volume of the sound effect.
   *
   * \details By default, this property is set to 128.
   *
   * \return the current volume of the sound effect.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto volume() const noexcept -> int
  {
    return m_chunk->volume;
  }

  /**
   * \brief Returns the maximum possible volume value.
   *
   * \return the maximum possible volume value.
   *
   * \since 3.1.0
   */
  [[nodiscard]] constexpr static auto max_volume() noexcept -> int
  {
    return MIX_MAX_VOLUME;
  }

  /// \} End of volume functions

  /// \name Conversions
  /// \{

  /**
   * \brief Converts to `Mix_Chunk*`.
   *
   * \return a pointer to the associated `Mix_Chunk` instance.
   *
   * \since 4.0.0
   */
  [[nodiscard]] explicit operator Mix_Chunk*() noexcept
  {
    return m_chunk.get();
  }

  /**
   * \brief Converts to `const Mix_Chunk*`.
   *
   * \return a pointer to the associated `Mix_Chunk` instance.
   *
   * \since 4.0.0
   */
  [[nodiscard]] explicit operator const Mix_Chunk*() const noexcept
  {
    return m_chunk.get();
  }

  /// \} End of conversions

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
   * \see `Mix_GetChunkDecoder`
   *
   * \since 6.0.0
   */
  template <typename TT = T, detail::is_owner<TT> = 0>
  [[nodiscard]] static auto get_decoder(const int index) noexcept -> str
  {
    return Mix_GetChunkDecoder(index);
  }

  /**
   * \brief Indicates whether or not the system has the specified sound effect decoder.
   *
   * \param name the name of the decoder to check.
   *
   * \return `true` if the system has the specified decoder; `false` otherwise.
   *
   * \see `Mix_HasChunkDecoder`
   *
   * \since 6.0.0
   */
  template <typename TT = T, detail::is_owner<TT> = 0>
  [[nodiscard]] static auto has_decoder(const str name) noexcept -> bool
  {
    return Mix_HasChunkDecoder(name) == SDL_TRUE;
  }

  /**
   * \brief Returns the number of available sound effect decoders.
   *
   * \return the number of available sound effect decoders.
   *
   * \see `Mix_GetNumChunkDecoders`
   *
   * \since 6.0.0
   */
  template <typename TT = T, detail::is_owner<TT> = 0>
  [[nodiscard]] static auto decoder_count() noexcept -> int
  {
    return Mix_GetNumChunkDecoders();
  }

  /// \} End of decoder functions

  /**
   * \brief Returns the channel associated with the sound effect, if any.
   *
   * \note Channels are not associated with sound effects for long, and might change in
   * between playbacks.
   *
   * \return the channel currently associated with the sound effect; `std::nullopt` if
   * there is none.
   *
   * \since 5.1.0
   */
  [[nodiscard]] auto channel() const noexcept -> std::optional<int>
  {
    if (m_channel != undefined_channel()) {
      return m_channel;
    }
    else {
      return std::nullopt;
    }
  }

  /**
   * \brief Returns a pointer to the associated `Mix_Chunk` instance.
   *
   * \warning Don't take ownership of the returned pointer!
   *
   * \return a pointer to the associated `Mix_Chunk`.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto get() const noexcept -> Mix_Chunk*
  {
    return m_chunk.get();
  }

 private:
  struct deleter final
  {
    void operator()(Mix_Chunk* chunk) noexcept
    {
      Mix_FreeChunk(chunk);
    }
  };

  detail::pointer_manager<T, Mix_Chunk, deleter> m_chunk;
  int m_channel{undefined_channel()};

  [[nodiscard]] constexpr static auto undefined_channel() noexcept -> int
  {
    return -1;
  }

#ifdef CENTURION_MOCK_FRIENDLY_MODE

 public:
  void set_channel(const int channel) noexcept
  {
    m_channel = channel;
  }
#endif  // CENTURION_MOCK_FRIENDLY_MODE
};

/**
 * \brief Returns a handle to the sound effect currently associated with the specified
 * channel.
 *
 * \note There might not be a sound effect associated with the specified channel, in which
 * case the returned handle is null.
 *
 * \param channel the channel associated with the desired sound effect.
 *
 * \return a handle to the sound effect associated with the specified channel.
 *
 * \since 6.0.0
 */
[[nodiscard]] inline auto get_sound(const int channel) noexcept -> sound_effect_handle
{
  return sound_effect_handle{Mix_GetChunk(channel)};
}

/// \name String conversions
/// \{

/**
 * \brief Returns a textual representation of a sound effect.
 *
 * \param sound the sound effect that will be converted.
 *
 * \return a string that represents the sound effect.
 *
 * \since 5.0.0
 */
[[nodiscard]] inline auto to_string(const sound_effect& sound) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("sound_effect{{data: {}, volume: {}}}",
                     detail::address_of(sound.get()),
                     sound.volume());
#else
  return "sound_effect{data: " + detail::address_of(sound.get()) +
         ", volume: " + std::to_string(sound.volume()) + "}";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of a sound effect.
 *
 * \param stream the stream that will be used.
 * \param sound the sound effect that will be printed.
 *
 * \return the used stream.
 *
 * \since 5.0.0
 */
inline auto operator<<(std::ostream& stream, const sound_effect& sound) -> std::ostream&
{
  return stream << to_string(sound);
}

/// \} End of streaming

/// \} End of group audio

}  // namespace cen

#endif  // CENTURION_NO_SDL_MIXER
#endif  // CENTURION_SOUND_EFFECT_HEADER
