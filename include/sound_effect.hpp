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
 * @file sound_effect.hpp
 *
 * @brief Provides the `SoundEffect` class.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

#ifndef CENTURION_SOUND_EFFECT_HEADER
#define CENTURION_SOUND_EFFECT_HEADER

#include <SDL_mixer.h>

#include "centurion_api.hpp"
#include "centurion_types.hpp"
#include "centurion_utils.hpp"

namespace centurion {

/**
 * @class SoundEffect
 *
 * @brief Represents a sound effect.
 *
 * @details Multiple various file formats are supported.
 *
 * @todo List the supported file formats.
 *
 * @since 3.0.0
 *
 * @see `Mix_Chunk`
 * @see `Music`
 *
 * @headerfile sound_effect.hpp
 */
class SoundEffect final {
 public:
  /**
   * @brief The maximum possible volume value.
   *
   * @since 4.0.0
   */
  inline static constexpr int maxVolume = MIX_MAX_VOLUME;

  /**
   * @brief Indicates that an audio snippet should be looped indefinitely.
   *
   * @since 4.0.0
   */
  inline static constexpr int loopForever = -1;

  /**
   * @brief Creates a sound effect based on the audio file at the specified
   * location.
   *
   * @param file the file path of the audio file.
   *
   * @throws centurion_exception if the audio file cannot be loaded.
   *
   * @since 3.0.0
   */
  CENTURION_API
  explicit SoundEffect(czstring file);

  /**
   * @brief Creates a sound effect by moving the contents of the supplied sound
   * effect.
   *
   * @param other the sound effect that will be moved.
   *
   * @since 3.0.0
   */
  CENTURION_API
  SoundEffect(SoundEffect&& other) noexcept;

  SoundEffect(const SoundEffect&) = delete;

  /**
   * @brief Moves the contents of the supplied sound effect into this one.
   *
   * @param other the sound effect that will be moved.
   *
   * @return the sound effect that absorbed the supplied sound effect.
   *
   * @since 3.0.0
   */
  CENTURION_API
  auto operator=(SoundEffect&& other) noexcept -> SoundEffect&;

  auto operator=(const SoundEffect&) -> SoundEffect& = delete;

  CENTURION_API
  ~SoundEffect();

  /**
   * @copydoc SoundEffect(czstring)
   */
  CENTURION_QUERY
  static auto unique(czstring file) -> std::unique_ptr<SoundEffect>;

  /**
   * @copydoc SoundEffect(czstring)
   */
  CENTURION_QUERY
  static auto shared(czstring file) -> std::shared_ptr<SoundEffect>;

  /**
   * @brief Plays the sound effect.
   *
   * @note A negative value indicates that the sound effect should be looped
   * forever.
   *
   * @param nLoops the amount of loops, can be negative.
   *
   * @see `SoundEffect::loopForever`
   *
   * @since 3.0.0
   */
  CENTURION_API
  void play(int nLoops = 0) noexcept;

  /**
   * @brief Stops the sound effect from playing.
   *
   * @since 3.0.0
   */
  CENTURION_API
  void stop() noexcept;

  /**
   * @brief Fades in the sound effect.
   *
   * @details This method has no effect if the supplied duration isn't greater
   * than zero or if the sound effect is currently playing.
   *
   * @param ms the duration to fade in, in milliseconds.
   *
   * @since 3.0.0
   */
  CENTURION_API
  void fade_in(milliseconds<int> ms) noexcept;

  /**
   * @brief Fades out the sound effect.
   *
   * @details This method has no effect if the supplied duration isn't greater
   * than zero or if the sound effect isn't currently playing.
   *
   * @param ms the duration to fade in, in milliseconds.
   *
   * @since 3.0.0
   */
  CENTURION_API
  void fade_out(milliseconds<int> ms) noexcept;

  /**
   * @brief Sets the volume of the sound effect.
   *
   * @details This method will adjust input values outside the legal range to
   * the closest legal value.
   *
   * @param volume the volume of the sound effect, in the range [0,
   * `SoundEffect::maxVolume`].
   *
   * @since 3.0.0
   */
  CENTURION_API
  void set_volume(int volume) noexcept;

  /**
   * @brief Indicates whether or not the sound effect is currently playing.
   *
   * @return `true` if the sound effect is playing; `false` otherwise.
   *
   * @since 3.0.0
   */
  CENTURION_QUERY
  auto playing() const noexcept -> bool;

  /**
   * @brief Returns a textual representation of the sound effect.
   *
   * @return a textual representation of the sound effect.
   *
   * @since 3.0.0
   */
  CENTURION_QUERY
  auto to_string() const -> std::string;

  /**
   * @brief Returns the current volume of the sound effect.
   *
   * @details By default, this property is set to 128.
   *
   * @return the current volume of the sound effect.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto volume() const noexcept -> int { return m_chunk->volume; }

  /**
   * @brief Returns a pointer to the associated `Mix_Chunk`.
   *
   * @warning Use of this method is not recommended, since it purposefully
   * breaks const-correctness. However it is useful since many SDL calls use
   * non-const pointers even when no change will be applied.
   *
   * @return a pointer to the associated `Mix_Chunk`.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto get() const noexcept -> Mix_Chunk* { return m_chunk; }

  /**
   * @brief Converts to `Mix_Chunk*`.
   *
   * @return a pointer to the associated `Mix_Chunk` instance.
   *
   * @since 4.0.0
   */
  [[nodiscard]] explicit operator Mix_Chunk*() noexcept { return m_chunk; }

  /**
   * @brief Converts to `const Mix_Chunk*`.
   *
   * @return a pointer to the associated `Mix_Chunk` instance.
   *
   * @since 4.0.0
   */
  [[nodiscard]] explicit operator const Mix_Chunk*() const noexcept
  {
    return m_chunk;
  }

  /**
   * @brief Returns the maximum possible volume value.
   *
   * @return the maximum possible volume value.
   *
   * @since 3.1.0
   */
  [[nodiscard]] static constexpr auto max_volume() noexcept -> int
  {
    return MIX_MAX_VOLUME;
  }

 private:
  static constexpr int undefinedChannel = -1;

  Mix_Chunk* m_chunk = nullptr;
  int m_channel = undefinedChannel;

  /**
   * @brief Destroys the resources associated with the sound effect.
   *
   * @since 4.0.0
   */
  void destroy() noexcept;

  /**
   * @brief Moves the contents of the supplied sound effect instance into this
   * instance.
   *
   * @param other the instance that will be moved.
   *
   * @since 4.0.0
   */
  void move(SoundEffect&& other) noexcept;

  /**
   * @brief Activates the sound effect by playing it the specified amount of
   * times.
   *
   * @param nLoops the amount of times to play the sound effect.
   *
   * @since 3.0.0
   */
  void activate(int nLoops) noexcept;
};

static_assert(std::is_final_v<SoundEffect>);
static_assert(std::is_nothrow_move_constructible_v<SoundEffect>);
static_assert(std::is_nothrow_move_assignable_v<SoundEffect>);
static_assert(!std::is_copy_constructible_v<SoundEffect>);
static_assert(!std::is_copy_assignable_v<SoundEffect>);

}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "sound_effect.cpp"
#endif

#endif  // CENTURION_SOUND_EFFECT_HEADER