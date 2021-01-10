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

/**
 * \defgroup audio Audio
 *
 * \brief Contains the audio API, for playing as sound effects and music.
 */

#ifndef CENTURION_SOUND_EFFECT_HEADER
#define CENTURION_SOUND_EFFECT_HEADER

#include <SDL_mixer.h>

#include <cassert>   // assert
#include <memory>    // unique_ptr
#include <optional>  // optional
#include <ostream>   // ostream
#include <string>    // string

#include "centurion_cfg.hpp"
#include "czstring.hpp"
#include "detail/address_of.hpp"
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
 * \class sound_effect
 *
 * \brief Represents a sound effect.
 *
 * \details The supported file formats are the following:
 * <ul>
 *   <li>WAVE/RIFF (.wav)</li>
 *   <li>AIFF (.aiff)</li>
 *   <li>VOC (.voc)</li>
 *   <li>OGG (.ogg)</li>
 *   <li>VOC (.voc)</li>
 * </ul>
 *
 * \par Usage
 * Usage of this class is pretty straightforward and self-explanatory. The
 * fundamental methods are `play()` and `stop()`, with additional support for
 * effects such as fading and looping.
 *
 * \since 3.0.0
 *
 * \see `Mix_Chunk`
 * \see `music`
 *
 * \headerfile sound_effect.hpp
 */
class sound_effect final
{
 public:
  /**
   * \brief Indicates that an audio snippet should be looped indefinitely.
   *
   * \since 5.1.0
   */
  inline constexpr static int forever = -1;

  /**
   * \brief Indicates that an audio snippet should be looped indefinitely.
   *
   * \deprecated Use `sound_effect::forever` instead.
   *
   * \since 4.0.0
   */
  [[deprecated]] inline constexpr static int loopForever = forever;

  /**
   * \brief Creates a sound effect based on the audio file at the specified
   * location.
   *
   * \param file the file path of the audio file, cannot be null.
   *
   * \throws mix_error if the audio file cannot be loaded.
   *
   * \since 3.0.0
   */
  explicit sound_effect(not_null<czstring> file) : m_chunk{Mix_LoadWAV(file)}
  {
    if (!m_chunk) {
      throw mix_error{};
    }
  }

  /**
   * \brief Plays the sound effect.
   *
   * \note A negative value indicates that the sound effect should be looped
   * forever.
   *
   * \param nLoops the amount of loops, `sound_effect::forever` can be used to
   * loop the sound effect indefinitely.
   *
   * \see `sound_effect::forever`
   *
   * \since 3.0.0
   */
  void play(const int nLoops = 0) noexcept
  {
    activate(detail::max(nLoops, forever));
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
   * \brief Fades in the sound effect.
   *
   * \pre `ms` must be greater than zero.
   *
   * \details This method has no effect if the sound effect is currently
   * playing.
   *
   * \param ms the duration to fade in, in milliseconds.
   *
   * \since 3.0.0
   */
  void fade_in(const milliseconds<int> ms) noexcept
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
   * \details This method has no effect if the sound effect isn't currently
   * playing.
   *
   * \param ms the duration to fade in, in milliseconds.
   *
   * \since 3.0.0
   */
  void fade_out(const milliseconds<int> ms) noexcept  // NOLINT not const
  {
    assert(ms.count() > 0);
    if (is_playing()) {
      Mix_FadeOutChannel(m_channel, ms.count());
    }
  }

  /**
   * \brief Sets the volume of the sound effect.
   *
   * \details This method will adjust input values outside the legal range to
   * the closest legal value.
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
   * \return `true` if any sound effect is playing on some channel; `false`
   * otherwise.
   *
   * \since 5.1.0
   */
  [[nodiscard]] static auto is_any_playing() noexcept -> bool
  {
    return Mix_Playing(undefined_channel());
  }

  /**
   * \brief Indicates whether or not the sound effect is being faded.
   *
   * \note If the sound effect is being faded, it's also playing so
   * `is_playing()` will also return `true`. Keep this in mind if you want to
   * differentiate between the two.
   *
   * \return `true` if the sound effect is being faded; `false` otherwise.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto is_fading() const noexcept -> bool
  {
    return is_playing() && Mix_FadingChannel(m_channel);
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
   * \brief Returns the channel associated with the sound effect, if any.
   *
   * \note Channels are not associated with sound effects for long, and might
   * change in between playbacks.
   *
   * \return the channel currently associated with the sound effect;
   * `std::nullopt` if there is none.
   *
   * \since 5.1.0
   */
  [[nodiscard]] auto channel() const noexcept -> std::optional<int>
  {
    if (m_channel != undefined_channel()) {
      return m_channel;
    } else {
      return std::nullopt;
    }
  }

  /**
   * \brief Returns a pointer to the associated `Mix_Chunk`.
   *
   * \warning Use of this method is not recommended. However it is useful since
   * many SDL calls use non-const pointers even when no change will be applied.
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

 private:
  struct deleter final
  {
    void operator()(Mix_Chunk* chunk) noexcept
    {
      Mix_FreeChunk(chunk);
    }
  };

  std::unique_ptr<Mix_Chunk, deleter> m_chunk;
  int m_channel{undefined_channel()};

  [[nodiscard]] constexpr static auto undefined_channel() noexcept -> int
  {
    return -1;
  }

  /**
   * \brief Activates the sound effect by playing it the specified amount of
   * times.
   *
   * \param nLoops the amount of times to play the sound effect.
   *
   * \since 3.0.0
   */
  void activate(const int nLoops) noexcept
  {
    if (m_channel != undefined_channel()) {
      Mix_PlayChannel(m_channel, m_chunk.get(), nLoops);
    } else {
      m_channel = Mix_PlayChannel(undefined_channel(), m_chunk.get(), nLoops);
    }
  }

#ifdef CENTURION_MOCK_FRIENDLY_MODE
 public:
  sound_effect() = default;

  void set_channel(const int channel) noexcept
  {
    m_channel = channel;
  }
#endif  // CENTURION_MOCK_FRIENDLY_MODE
};

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
  using detail::to_string;
  return "[sound_effect | data: " + detail::address_of(sound.get()) +
         ", volume: " + detail::to_string(sound.volume()).value() + "]";
}

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
inline auto operator<<(std::ostream& stream, const sound_effect& sound)
    -> std::ostream&
{
  stream << to_string(sound);
  return stream;
}

/// \}

}  // namespace cen

#endif  // CENTURION_SOUND_EFFECT_HEADER