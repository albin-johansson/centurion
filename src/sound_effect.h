#pragma once
#include <cstdint>
#include <string>
#include <SDL_mixer.h>

namespace centurion {

/**
 * The SoundEffect class represents sound effects in various file formats.
 *
 * @since 3.0.0
 */
class SoundEffect final {
 private:
  static constexpr int undefinedChannel = -1;

  Mix_Chunk* chunk = nullptr;
  int channel = undefinedChannel;

  /**
   * Activates the sound effect by playing it the specified amount of times.
   *
   * @param nLoops the amount of times to play the sound effect.
   * @since 3.0.0
   */
  void activate(int nLoops) noexcept;

 public:
  /**
   * A constant that can be used as the argument to the SoundEffect::Loop method, in order to make
   * the call more readable.
   *
   * @since 3.0.0
   */
  static constexpr int loopIndefinitely = -10;

  /**
   * @param file the file path of the audio file.
   * @throws CenturionException if the audio file cannot be loaded.
   * @since 3.0.0
   */
  explicit SoundEffect(const std::string& file);

  ~SoundEffect();

  /**
   * Plays the sound effect.
   *
   * @since 3.0.0
   */
  void play() noexcept;

  /**
   * Loops the sound effect by the specified amount of times.
   *
   * @param nLoops the amount of loops. A negative value indicates that the sound effect should
   * be looped indefinitely.
   * @since 3.0.0
   * @see SoundEffect::loopIndefinitely
   */
  void loop(int nLoops) noexcept;

  /**
   * Stops the sound effect from playing.
   *
   * @since 3.0.0
   */
  void stop() noexcept;

  /**
   * Fades in the sound effect. This method has no effect if the supplied duration isn't greater
   * than zero or if the sound effect is currently playing.
   *
   * @param ms the duration to fade in, in milliseconds.
   * @since 3.0.0
   */
  void fade_in(uint32_t ms) noexcept;

  /**
   * Fades out the sound effect. This method has no effect if the supplied duration isn't greater
   * than zero or if the sound effect isn't currently playing.
   *
   * @param ms the duration to fade in, in milliseconds.
   * @since 3.0.0
   */
  void fade_out(uint32_t ms) noexcept;

  /**
   * Sets the volume of the sound effect. This method will adjust input values outside
   * the legal range to the closest legal value.
   *
   * @param volume the volume of the sound effect, in the range [0, MIX_MAX_VOLUME].
   * @since 3.0.0
   */
  void set_volume(int volume) noexcept;

  /**
   * Returns the current volume of the sound effect.
   *
   * @return the current volume of the sound effect.
   * @since 3.0.0
   */
  [[nodiscard]]
  int get_volume() const noexcept;

  /**
   * Indicates whether or not the sound effect is currently playing.
   *
   * @return true if the sound effect is playing; false otherwise.
   * @since 3.0.0
   */
  [[nodiscard]]
  bool is_playing() const noexcept;
};

}
