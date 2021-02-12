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

#ifndef CENTURION_HAPTIC_HEADER
#define CENTURION_HAPTIC_HEADER

#include <SDL.h>

#include <cassert>      // assert
#include <optional>     // optional
#include <ostream>      // ostream
#include <string>       // string
#include <type_traits>  // true_type, false_type, enable_if_t

#include "centurion_cfg.hpp"
#include "czstring.hpp"
#include "detail/address_of.hpp"
#include "detail/clamp.hpp"
#include "detail/max.hpp"
#include "detail/owner_handle_api.hpp"
#include "exception.hpp"
#include "integers.hpp"
#include "joystick.hpp"
#include "time.hpp"
#include "vector3.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/// \addtogroup input
/// \{

/**
 * \brief A constant that can be used to play an effect indefinitely.
 *
 * \since 5.2.0
 */
inline constexpr u32 haptic_infinity = SDL_HAPTIC_INFINITY;

/**
 * \enum haptic_feature
 *
 * \brief Provides values that represent all of the haptic features.
 *
 * \since 5.2.0
 *
 * \headerfile haptic_feature
 */
enum class haptic_feature
{
  constant = SDL_HAPTIC_CONSTANT,
  sine = SDL_HAPTIC_SINE,
  left_right = SDL_HAPTIC_LEFTRIGHT,
  triangle = SDL_HAPTIC_TRIANGLE,
  sawtooth_up = SDL_HAPTIC_SAWTOOTHUP,
  sawtooth_down = SDL_HAPTIC_SAWTOOTHDOWN,
  ramp = SDL_HAPTIC_RAMP,
  spring = SDL_HAPTIC_SPRING,
  damper = SDL_HAPTIC_DAMPER,
  inertia = SDL_HAPTIC_INERTIA,
  friction = SDL_HAPTIC_FRICTION,
  custom = SDL_HAPTIC_CUSTOM,
  gain = SDL_HAPTIC_GAIN,
  autocenter = SDL_HAPTIC_AUTOCENTER,
  status = SDL_HAPTIC_STATUS,
  pause = SDL_HAPTIC_PAUSE
};

/**
 * \enum haptic_direction_type
 *
 * \brief Represents the different types of haptic directions.
 *
 * \since 5.2.0
 *
 * \headerfile haptic.hpp
 */
enum class haptic_direction_type
{
  polar = SDL_HAPTIC_POLAR,
  cartesian = SDL_HAPTIC_CARTESIAN,
  spherical = SDL_HAPTIC_SPHERICAL
};

/**
 * \class haptic_direction
 *
 * \brief Represents a haptic direction, used by haptic effects.
 *
 * \since 5.2.0
 *
 * \headerfile haptic.hpp
 */
class haptic_direction final
{
 public:
  using direction_type = vector3<i32>;

  /**
   * \brief Creates a haptic direction of the specified type.
   *
   * \param type the type of the direction.
   *
   * \since 5.2.0
   */
  explicit haptic_direction(const haptic_direction_type type) noexcept
  {
    set_type(type);
  }

  /**
   * \brief Creates a haptic direction based on an `SDL_HapticDirection`
   * instance.
   *
   * \param direction the direction that will be copied.
   *
   * \since 5.2.0
   */
  explicit haptic_direction(const SDL_HapticDirection& direction) noexcept
      : m_direction{direction}
  {}

  /**
   * \brief Sets the type of the direction.
   *
   * \param type the new type of the direction.
   *
   * \since 5.2.0
   */
  void set_type(const haptic_direction_type type) noexcept
  {
    m_direction.type = static_cast<u8>(type);
  }

  /**
   * \brief Sets the value of direction.
   *
   * \param direction the new value of the direction.
   *
   * \since 5.2.0
   */
  void set_value(const direction_type& direction) noexcept
  {
    m_direction.dir[0] = direction.x;
    m_direction.dir[1] = direction.y;
    m_direction.dir[2] = direction.z;
  }

  /**
   * \brief Returns the type associated with the direction.
   *
   * \return the current type of the direction.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto type() const noexcept -> haptic_direction_type
  {
    return static_cast<haptic_direction_type>(m_direction.type);
  }

  /**
   * \brief Returns the value of the direction.
   *
   * \return the current value of the direction.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto value() const noexcept -> direction_type
  {
    return {m_direction.dir[0], m_direction.dir[1], m_direction.dir[2]};
  }

  /**
   * \brief Returns the internal representation of the direction.
   *
   * \return the internal representation.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto get() const noexcept -> const SDL_HapticDirection&
  {
    return m_direction;
  }

 private:
  SDL_HapticDirection m_direction{};
};

/**
 * \class haptic_effect
 *
 * \brief Represents a haptic effect.
 *
 * \details The following is an illustration of the different stages of a haptic
 * effect, copied from the SDL documentation, albeit with tweaked terms.
 * \verbatim
    Strength
    ^
    |
    |    effect level -->  _________________
    |                     /                 \
    |                    /                   \
    |                   /                     \
    |                  /                       \
    | attack_level --> |                        \
    |                  |                        |  <---  fade_level
    |
    +--------------------------------------------------> Time
                       [--]                 [---]
                       attack_length        fade_length

    [------------------][-----------------------]
    delay               duration
    \endverbatim
 *
 * \tparam Derived the type of the subclass for CRTP.
 *
 * \since 5.2.0
 *
 * \headerfile haptic.hpp
 */
template <typename Derived>
class haptic_effect
{
  template <typename T>
  using has_direction = std::enable_if_t<T::hasDirection, bool>;

  template <typename T>
  using has_envelope = std::enable_if_t<T::hasEnvelope, bool>;

  template <typename T>
  using has_trigger = std::enable_if_t<T::hasTrigger, bool>;

  template <typename T>
  using has_delay = std::enable_if_t<T::hasDelay, bool>;

 public:
  /// \name Direction functions
  /// \{

  /**
   * \brief Sets the haptic direction associated with the effect.
   *
   * \note This function is not available for all haptic effects.
   *
   * \tparam D dummy parameter for SFINAE.
   *
   * \param direction the new direction of the effect.
   *
   * \since 5.2.0
   */
  template <typename D = Derived, has_direction<D> = true>
  void set_direction(const haptic_direction& direction) noexcept
  {
    rep().direction = direction.get();
  }

  /**
   * \brief Returns the haptic direction associated with the effect.
   *
   * \tparam D dummy parameter for SFINAE.
   *
   * \return the current direction associated with the effect.
   *
   * \since 5.2.0
   */
  template <typename D = Derived, has_direction<D> = true>
  [[nodiscard]] auto direction() const noexcept -> haptic_direction
  {
    return haptic_direction{rep().direction};
  }

  /// \} End of direction functions

  /// \name Replay functions
  /// \{

  /**
   * \brief Sets the effect to be repeated indefinitely when run.
   *
   * \details This function makes the effect repeat forever when run, but the
   * attack and fade are not repeated.
   *
   * \since 5.2.0
   */
  void set_repeat_forever() noexcept
  {
    rep().length = haptic_infinity;
  }

  /**
   * \brief Sets the duration of the effect.
   *
   * \param ms the duration of the effect.
   *
   * \since 5.2.0
   */
  void set_duration(const milliseconds<u32> ms)
  {
    rep().length = ms.count();
  }

  /**
   * \brief Sets the delay before before the effect is started.
   *
   * \note This function is not available for all haptic effects.
   *
   * \tparam D dummy parameter for SFINAE.
   *
   * \param ms the delay before before the effect is started.
   *
   * \since 5.2.0
   */
  template <typename D = Derived, has_delay<D> = true>
  void set_delay(const milliseconds<u16> ms)
  {
    rep().delay = ms.count();
  }

  /**
   * \brief Returns the duration of the effect.
   *
   * \return the duration of the effect.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto duration() const -> milliseconds<u32>
  {
    return milliseconds<u32>{rep().length};
  }

  /**
   * \brief Returns the delay before before the effect is started.
   *
   * \note This function is not available for all haptic effects.
   *
   * \tparam D dummy parameter for SFINAE.
   *
   * \return the delay before before the effect is started.
   *
   * \since 5.2.0
   */
  template <typename D = Derived, has_delay<D> = true>
  [[nodiscard]] auto delay() const -> milliseconds<u16>
  {
    return milliseconds<u16>{rep().delay};
  }

  /// \} End of replay functions

  /// \name Trigger functions
  /// \{

  /**
   * \brief Sets the button that triggers the effect.
   *
   * \note This function is not available for all haptic effects.
   *
   * \tparam D dummy parameter for SFINAE.
   *
   * \param button the button that triggers the effect.
   *
   * \since 5.2.0
   */
  template <typename D = Derived, has_trigger<D> = true>
  void set_button(const u16 button) noexcept
  {
    rep().button = button;
  }

  /**
   * \brief Sets the minimum interval in between activations of the effect.
   *
   * \note This function is not available for all haptic effects.
   *
   * \tparam D dummy parameter for SFINAE.
   *
   * \param ms the minimum interval in between activations of the effect.
   *
   * \since 5.2.0
   */
  template <typename D = Derived, has_trigger<D> = true>
  void set_interval(const milliseconds<u16> ms)
  {
    rep().interval = ms.count();
  }

  /**
   * \brief Returns the button that triggers the effect.
   *
   * \note This function is not available for all haptic effects.
   *
   * \tparam D dummy parameter for SFINAE.
   *
   * \return the button that triggers the effect.
   *
   * \since 5.2.0
   */
  template <typename D = Derived, has_trigger<D> = true>
  [[nodiscard]] auto button() const noexcept -> u16
  {
    return rep().button;
  }

  /**
   * \brief Returns the minimum interval in between activations of the effect.
   *
   * \note This function is not available for all haptic effects.
   *
   * \tparam D dummy parameter for SFINAE.
   *
   * \return the minimum interval in between activations of the effect.
   *
   * \since 5.2.0
   */
  template <typename D = Derived, has_trigger<D> = true>
  [[nodiscard]] auto interval() const -> milliseconds<u16>
  {
    return milliseconds<u16>{rep().interval};
  }

  /// \} End of trigger functions

  /// \name Envelope functions
  /// \{

  /**
   * \brief Sets the level at the *start* of the attack.
   *
   * \note This function is not available for all haptic effects.
   *
   * \tparam D dummy parameter for SFINAE.
   *
   * \param level the level at the start of the attack.
   *
   * \since 5.2.0
   */
  template <typename D = Derived, has_envelope<D> = true>
  void set_attack_level(const u16 level) noexcept
  {
    rep().attack_level = level;
  }

  /**
   * \brief Sets the level at the *end* of the fade out.
   *
   * \note This function is not available for all haptic effects.
   *
   * \tparam D dummy parameter for SFINAE.
   *
   * \param level the level at the *end* of the fade out.
   *
   * \since 5.2.0
   */
  template <typename D = Derived, has_envelope<D> = true>
  void set_fade_level(const u16 level) noexcept
  {
    rep().fade_level = level;
  }

  /**
   * \brief Sets the duration of the attack.
   *
   * \note This function is not available for all haptic effects.
   *
   * \tparam D dummy parameter for SFINAE.
   *
   * \param ms the duration of the attack.
   *
   * \since 5.2.0
   */
  template <typename D = Derived, has_envelope<D> = true>
  void set_attack_duration(const milliseconds<u16> ms)
  {
    rep().attack_length = ms.count();
  }

  /**
   * \brief Sets the duration of the fade out.
   *
   * \note This function is not available for all haptic effects.
   *
   * \tparam D dummy parameter for SFINAE.
   *
   * \param ms the duration of the fade out.
   *
   * \since 5.2.0
   */
  template <typename D = Derived, has_envelope<D> = true>
  void set_fade_duration(const milliseconds<u16> ms)
  {
    rep().fade_length = ms.count();
  }

  /**
   * \brief Returns the level at the *start* of the attack.
   *
   * \note This function is not available for all haptic effects.
   *
   * \tparam D dummy parameter for SFINAE.
   *
   * \return the the level at the *start* of the attack.
   *
   * \since 5.2.0
   */
  template <typename D = Derived, has_envelope<D> = true>
  [[nodiscard]] auto attack_level() const noexcept -> u16
  {
    return rep().attack_level;
  }

  /**
   * \brief Returns the level at the *end* of the fade.
   *
   * \note This function is not available for all haptic effects.
   *
   * \tparam D dummy parameter for SFINAE.
   *
   * \return the level at the *end* of the fade.
   *
   * \since 5.2.0
   */
  template <typename D = Derived, has_envelope<D> = true>
  [[nodiscard]] auto fade_level() const noexcept -> u16
  {
    return rep().fade_level;
  }

  /**
   * \brief Returns the duration of the attack.
   *
   * \note This function is not available for all haptic effects.
   *
   * \tparam D dummy parameter for SFINAE.
   *
   * \return the duration of the attack.
   *
   * \since 5.2.0
   */
  template <typename D = Derived, has_envelope<D> = true>
  [[nodiscard]] auto attack_duration() const -> milliseconds<u16>
  {
    return milliseconds<u16>{rep().attack_length};
  }

  /**
   * \brief Returns the duration of the fade out.
   *
   * \note This function is not available for all haptic effects.
   *
   * \tparam D dummy parameter for SFINAE.
   *
   * \return the duration of the fade out.
   *
   * \since 5.2.0
   */
  template <typename D = Derived, has_envelope<D> = true>
  [[nodiscard]] auto fade_duration() const -> milliseconds<u16>
  {
    return milliseconds<u16>{rep().fade_length};
  }

  /// \} End of envelope functions

  /**
   * \brief Returns the type associated with the haptic effect.
   *
   * \return the associated effect type.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto type() const noexcept -> u16
  {
    return rep().type;
  }

  /**
   * \brief Returns the internal effect representation.
   *
   * \return the internal effect representation.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto get() noexcept -> SDL_HapticEffect&
  {
    return m_effect;
  }

  /**
   * \copydoc get()
   */
  [[nodiscard]] auto get() const noexcept -> const SDL_HapticEffect&
  {
    return m_effect;
  }

 protected:
  SDL_HapticEffect m_effect{};

 private:
  [[nodiscard]] auto derived() noexcept -> Derived*
  {
    return static_cast<Derived*>(this);
  }

  [[nodiscard]] auto derived() const noexcept -> const Derived*
  {
    return static_cast<const Derived*>(this);
  }

  [[nodiscard]] auto rep() noexcept -> auto&
  {
    return derived()->representation();
  }

  [[nodiscard]] auto rep() const noexcept -> const auto&
  {
    return derived()->representation();
  }
};

/**
 * \class haptic_constant
 *
 * \brief Represents a haptic effect that applies a constant force in some
 * direction.
 *
 * \note See the SDL documentation for `SDL_HapticConstant` for much more
 * detailed related documentation.
 *
 * \see SDL_HapticConstant
 *
 * \since 5.2.0
 *
 * \headerfile haptic.hpp
 */
class haptic_constant final : public haptic_effect<haptic_constant>
{
 public:
  inline constexpr static bool hasDirection = true;
  inline constexpr static bool hasEnvelope = true;
  inline constexpr static bool hasTrigger = true;
  inline constexpr static bool hasDelay = true;

  /**
   * \brief Creates a constant haptic effect.
   *
   * \since 5.2.0
   */
  haptic_constant() noexcept
  {
    m_effect.constant = {};
    representation().type = SDL_HAPTIC_CONSTANT;
  }

  /**
   * \brief Returns the internal representation.
   *
   * \return the internal representation.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto representation() noexcept -> SDL_HapticConstant&
  {
    return m_effect.constant;
  }

  /**
   * \copydoc representation();
   */
  [[nodiscard]] auto representation() const noexcept
      -> const SDL_HapticConstant&
  {
    return m_effect.constant;
  }
};

/**
 * \class haptic_periodic
 *
 * \brief Represents a wave-shaped haptic effect that repeats itself over time.
 *
 * \note See the SDL documentation for `SDL_HapticPeriodic` for much more
 * detailed related documentation.
 *
 * \see SDL_HapticPeriodic
 *
 * \since 5.2.0
 *
 * \headerfile haptic.hpp
 */
class haptic_periodic final : public haptic_effect<haptic_periodic>
{
 public:
  inline constexpr static bool hasDirection = true;
  inline constexpr static bool hasEnvelope = true;
  inline constexpr static bool hasTrigger = true;
  inline constexpr static bool hasDelay = true;

  /**
   * \enum periodic_type
   *
   * \brief Provides values that serve as identifiers for the different kinds of
   * "periodic" haptic effects.
   *
   * \since 5.2.0
   */
  enum periodic_type : u16
  {
    sine = SDL_HAPTIC_SINE,
    left_right = SDL_HAPTIC_LEFTRIGHT,
    triangle = SDL_HAPTIC_TRIANGLE,
    sawtooth_up = SDL_HAPTIC_SAWTOOTHUP,
    sawtooth_down = SDL_HAPTIC_SAWTOOTHDOWN
  };

  /**
   * \brief Creates a periodic haptic effect.
   *
   * \details The type of the effects defaults to `sine`.
   *
   * \since 5.2.0
   */
  explicit haptic_periodic(const periodic_type type = sine) noexcept
  {
    m_effect.periodic = {};
    set_type(type);
  }

  /**
   * \brief Sets the type of the effect.
   *
   * \param type the periodic effect type.
   *
   * \since 5.2.0
   */
  void set_type(const periodic_type type) noexcept
  {
    representation().type = static_cast<u16>(type);
  }

  /**
   * \brief Sets the period of the wave.
   *
   * \param ms the period duration of the wave.
   *
   * \since 5.2.0
   */
  void set_period(const milliseconds<u16> ms)
  {
    representation().period = ms.count();
  }

  /**
   * \brief Sets the magnitude (peak value) of the wave.
   *
   * \note If the supplied magnitude is negative, that is interpreted as an
   * extra phase_shift shift of 180 degrees.
   *
   * \param magnitude the magnitude of the wave, can be negative.
   *
   * \since 5.2.0
   */
  void set_magnitude(const i16 magnitude) noexcept
  {
    representation().magnitude = magnitude;
  }

  /**
   * \brief Sets the mean value of the wave.
   *
   * \param mean the mean value of the wave.
   *
   * \since 5.2.0
   */
  void set_mean(const i16 mean) noexcept
  {
    representation().offset = mean;
  }

  /**
   * \brief Sets the phase_shift shift.
   *
   * \param shift the positive phase_shift shift, interpreted as hundredths of a
   * degree.
   *
   * \since 5.2.0
   */
  void set_phase_shift(const u16 shift) noexcept
  {
    representation().phase = shift;
  }

  /**
   * \brief Returns the current period of the wave.
   *
   * \return the period of the wave.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto period() const -> milliseconds<u16>
  {
    return milliseconds<u16>{representation().period};
  }

  /**
   * \brief Returns the current magnitude (peak value) of the wave.
   *
   * \return the magnitude of the wave.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto magnitude() const noexcept -> i16
  {
    return representation().magnitude;
  }

  /**
   * \brief Returns the current mean value of the wave.
   *
   * \return the mean value of the wave.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto mean() const noexcept -> i16
  {
    return representation().offset;
  }

  /**
   * \brief Returns the current positive phase shift of the wave.
   *
   * \return the positive phase shift of the wave, in hundredths of a degree.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto phase_shift() const noexcept -> u16
  {
    return representation().phase;
  }

  /**
   * \brief Returns the internal representation.
   *
   * \return the internal representation.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto representation() noexcept -> SDL_HapticPeriodic&
  {
    return m_effect.periodic;
  }

  /**
   * \copydoc representation();
   */
  [[nodiscard]] auto representation() const noexcept
      -> const SDL_HapticPeriodic&
  {
    return m_effect.periodic;
  }
};

/**
 * \class haptic_ramp
 *
 * \brief Represents a linear or quadratic haptic effect.
 *
 * \note See the SDL documentation for `SDL_HapticRamp` for much more detailed
 * related documentation.
 *
 * \see SDL_HapticRamp
 *
 * \since 5.2.0
 *
 * \headerfile haptic.hpp
 */
class haptic_ramp final : public haptic_effect<haptic_ramp>
{
 public:
  inline constexpr static bool hasDirection = true;
  inline constexpr static bool hasEnvelope = true;
  inline constexpr static bool hasTrigger = true;
  inline constexpr static bool hasDelay = true;

  /**
   * \brief Creates a haptic ramp effect.
   *
   * \since 5.2.0
   */
  haptic_ramp() noexcept
  {
    m_effect.ramp = {};
    representation().type = SDL_HAPTIC_RAMP;
  }

  /**
   * \brief Sets the initial strength level.
   *
   * \param start the initial strength level.
   *
   * \since 5.2.0
   */
  void set_start_strength(const i16 start) noexcept
  {
    representation().start = start;
  }

  /**
   * \brief Sets the strength level at the end of the effect.
   *
   * \param end the strength level at the end of the effect.
   *
   * \since 5.2.0
   */
  void set_end_strength(const i16 end) noexcept
  {
    representation().end = end;
  }

  /**
   * \brief Returns the initial strength level.
   *
   * \return the initial strength level.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto start_strength() const noexcept -> i16
  {
    return representation().start;
  }

  /**
   * \brief Returns the strength level at the end of the effect.
   *
   * \return the final strength level.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto end_strength() const noexcept -> i16
  {
    return representation().end;
  }

  /**
   * \brief Returns the internal representation.
   *
   * \return the internal representation.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto representation() noexcept -> SDL_HapticRamp&
  {
    return m_effect.ramp;
  }

  /**
   * \copydoc representation();
   */
  [[nodiscard]] auto representation() const noexcept -> const SDL_HapticRamp&
  {
    return m_effect.ramp;
  }
};

/**
 * \class haptic_custom
 *
 * \brief Represents a custom haptic effect, similar to a periodic effect.
 *
 * \note See the SDL documentation for `SDL_HapticCustom` for much more detailed
 * related documentation.
 *
 * \see SDL_HapticCustom
 *
 * \since 5.2.0
 *
 * \headerfile haptic.hpp
 */
class haptic_custom final : public haptic_effect<haptic_custom>
{
 public:
  inline constexpr static bool hasDirection = true;
  inline constexpr static bool hasEnvelope = true;
  inline constexpr static bool hasTrigger = true;
  inline constexpr static bool hasDelay = true;

  /**
   * \brief Creates a haptic custom effect.
   *
   * \since 5.2.0
   */
  haptic_custom() noexcept
  {
    m_effect.custom = {};
    representation().type = SDL_HAPTIC_CUSTOM;
  }

  /**
   * \brief Sets the number of axes that are used.
   *
   * \pre `count` must be greater than zero.
   *
   * \param count the number of axes that will be used.
   *
   * \since 5.2.0
   */
  void set_axis_count(const u8 count) noexcept
  {
    assert(count > 0);
    representation().channels = detail::max(u8{1}, count);
  }

  /**
   * \brief Sets the duration of the sample periods.
   *
   * \param ms duration of sample periods.
   *
   * \since 5.2.0
   */
  void set_sample_period(const milliseconds<u16> ms)
  {
    representation().period = ms.count();
  }

  /**
   * \brief Sets the number of samples.
   *
   * \param count the number of samples.
   *
   * \since 5.2.0
   */
  void set_sample_count(const u16 count) noexcept
  {
    representation().samples = count;
  }

  /**
   * \brief Sets the associated custom data.
   *
   * \note The data must be allocated and managed by you.
   *
   * \details The data should consist of `sample_count()` * `axis_count()`
   * sample items.
   *
   * \param data a pointer to the custom sample data.
   *
   * \since 5.2.0
   */
  void set_data(u16* data) noexcept
  {
    representation().data = data;
  }

  /**
   * \brief Returns the number of axes that are used.
   *
   * \return the number of used axes.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto axis_count() const noexcept -> u8
  {
    return representation().channels;
  }

  /**
   * \brief Returns the duration of samples.
   *
   * \return the duration of samples.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto sample_period() const -> milliseconds<u16>
  {
    return milliseconds<u16>{representation().period};
  }

  /**
   * \brief Returns the number of samples.
   *
   * \return the number of samples.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto sample_count() const noexcept -> u16
  {
    return representation().samples;
  }

  /**
   * \brief Returns a pointer to user-provided data.
   *
   * \return a pointer to custom user-provided data, might be null.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto data() const noexcept -> u16*
  {
    return representation().data;
  }

  /**
   * \brief Returns the internal representation.
   *
   * \return the internal representation.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto representation() noexcept -> SDL_HapticCustom&
  {
    return m_effect.custom;
  }

  /**
   * \copydoc representation();
   */
  [[nodiscard]] auto representation() const noexcept -> const SDL_HapticCustom&
  {
    return m_effect.custom;
  }
};

/**
 * \class haptic_condition
 *
 * \brief Represents an axes-based haptic effect.
 *
 * \note See the SDL documentation for `SDL_HapticCondition` for much more
 * detailed related documentation.
 *
 * \see SDL_HapticCondition
 *
 * \since 5.2.0
 *
 * \headerfile haptic.hpp
 */
class haptic_condition final : public haptic_effect<haptic_condition>
{
 public:
  inline constexpr static bool hasDirection = false;
  inline constexpr static bool hasEnvelope = false;
  inline constexpr static bool hasTrigger = true;
  inline constexpr static bool hasDelay = true;

  /**
   * \enum condition_type
   *
   * \brief Provides values that serve as identifiers for the different kinds of
   * "condition" haptic effects.
   *
   * \since 5.2.0
   */
  enum condition_type : u32
  {
    spring = SDL_HAPTIC_SPRING,     ///< Based on axes position.
    damper = SDL_HAPTIC_DAMPER,     ///< Based on axes velocity.
    inertia = SDL_HAPTIC_INERTIA,   ///< Based on axes acceleration.
    friction = SDL_HAPTIC_FRICTION  ///< Based on axes movement.
  };

  /**
   * \brief Creates a haptic "condition" effect.
   *
   * \param type the type of the effect.
   *
   * \since 5.2.0
   */
  explicit haptic_condition(const condition_type type = spring) noexcept
  {
    m_effect.condition = {};
    set_type(type);
  }

  /**
   * \brief Sets the type of the effect.
   *
   * \param type the type of the effect.
   *
   * \since 5.2.0
   */
  void set_type(const condition_type type) noexcept
  {
    representation().type = type;
  }

  /**
   * \brief Sets the effect level when the joystick is to the "positive" side.
   *
   * \param level the x-, y- and z-axis levels.
   *
   * \since 5.2.0
   */
  void set_joystick_positive_level(const vector3<u16>& level) noexcept
  {
    representation().right_sat[0] = level.x;
    representation().right_sat[1] = level.y;
    representation().right_sat[2] = level.z;
  }

  /**
   * \brief Sets the effect level when the joystick is to the "negative" side.
   *
   * \param level the x-, y- and z-axis levels.
   *
   * \since 5.2.0
   */
  void set_joystick_negative_level(const vector3<u16>& level) noexcept
  {
    representation().left_sat[0] = level.x;
    representation().left_sat[1] = level.y;
    representation().left_sat[2] = level.z;
  }

  /**
   * \brief Sets of quickly the force should increase towards the "positive"
   * side.
   *
   * \param rate the x-, y- and z-axis rates.
   *
   * \since 5.2.0
   */
  void set_force_rate_positive(const vector3<i16>& rate) noexcept
  {
    representation().right_coeff[0] = rate.x;
    representation().right_coeff[1] = rate.y;
    representation().right_coeff[2] = rate.z;
  }

  /**
   * \brief Sets of quickly the force should increase towards the "negative"
   * side.
   *
   * \param rate the x-, y- and z-axis rates.
   *
   * \since 5.2.0
   */
  void set_force_rate_negative(const vector3<i16>& rate) noexcept
  {
    representation().left_coeff[0] = rate.x;
    representation().left_coeff[1] = rate.y;
    representation().left_coeff[2] = rate.z;
  }

  /**
   * \brief Sets the size of the dead zone.
   *
   * \param size the x-, y- and z-axis sizes.
   *
   * \since 5.2.0
   */
  void set_deadband(const vector3<u16>& size) noexcept
  {
    representation().deadband[0] = size.x;
    representation().deadband[1] = size.y;
    representation().deadband[2] = size.z;
  }

  /**
   * \brief Sets the "center", i.e. the position of the dead zone.
   *
   * \param center the position of the dead zone.
   *
   * \since 5.2.0
   */
  void set_center(const vector3<i16>& center) noexcept
  {
    representation().center[0] = center.x;
    representation().center[1] = center.y;
    representation().center[2] = center.z;
  }

  /**
   * \brief Returns the effect level when the joystick is to the "positive"
   * side.
   *
   * \return the positive side effect level.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto joystick_positive_level() const noexcept -> vector3<u16>
  {
    const auto& level = representation().right_sat;
    return {level[0], level[1], level[2]};
  }

  /**
   * \brief Returns the effect level when the joystick is to the "negative"
   * side.
   *
   * \return the negative side effect level.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto joystick_negative_level() const noexcept -> vector3<u16>
  {
    const auto& level = representation().left_sat;
    return {level[0], level[1], level[2]};
  }

  /**
   * \brief Returns how fast the force increases towards to the "positive" side.
   *
   * \return the positive side force increase rate.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto force_rate_positive() const noexcept -> vector3<i16>
  {
    const auto& rate = representation().right_coeff;
    return {rate[0], rate[1], rate[2]};
  }

  /**
   * \brief Returns how fast the force increases towards to the "negative" side.
   *
   * \return the negative side force increase rate.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto force_rate_negative() const noexcept -> vector3<i16>
  {
    const auto& rate = representation().left_coeff;
    return {rate[0], rate[1], rate[2]};
  }

  /**
   * \brief Returns the size of the dead zone.
   *
   * \return the size of the dead zone.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto deadband() const noexcept -> vector3<u16>
  {
    const auto& band = representation().deadband;
    return {band[0], band[1], band[2]};
  }

  /**
   * \brief Returns the position of the dead zone.
   *
   * \return the position of the dead zone.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto center() const noexcept -> vector3<i16>
  {
    const auto& center = representation().center;
    return {center[0], center[1], center[2]};
  }

  /**
   * \brief Returns the internal representation.
   *
   * \return the internal representation.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto representation() noexcept -> SDL_HapticCondition&
  {
    return m_effect.condition;
  }

  /**
   * \copydoc representation();
   */
  [[nodiscard]] auto representation() const noexcept
      -> const SDL_HapticCondition&
  {
    return m_effect.condition;
  }
};

/**
 * \class haptic_left_right
 *
 * \brief Represents a haptic effect based on controlling the large and small
 * motors featured in many modern game controllers.
 *
 * \note See the SDL documentation for `SDL_HapticLeftRight` for much more
 * detailed related documentation.
 *
 * \see SDL_HapticLeftRight
 *
 * \since 5.2.0
 *
 * \headerfile haptic.hpp
 */
class haptic_left_right final : public haptic_effect<haptic_left_right>
{
 public:
  inline constexpr static bool hasDirection = false;
  inline constexpr static bool hasEnvelope = false;
  inline constexpr static bool hasTrigger = false;
  inline constexpr static bool hasDelay = false;

  /**
   * \brief Creates a "left/right" haptic effect.
   *
   * \since 5.2.0
   */
  haptic_left_right() noexcept
  {
    m_effect.leftright = {};
    representation().type = SDL_HAPTIC_LEFTRIGHT;
  }

  /**
   * \brief Sets the magnitude of the large (low frequency) controller motor.
   *
   * \param magnitude the magnitude of the large motor.
   *
   * \since 5.2.0
   */
  void set_large_magnitude(const u16 magnitude) noexcept
  {
    representation().large_magnitude = magnitude;
  }

  /**
   * \brief Sets the magnitude of the small (high frequency) controller motor.
   *
   * \param magnitude the magnitude of the small motor.
   *
   * \since 5.2.0
   */
  void set_small_magnitude(const u16 magnitude) noexcept
  {
    representation().small_magnitude = magnitude;
  }

  /**
   * \brief Returns the magnitude of the large (low frequency) controller motor.
   *
   * \return the magnitude of the large motor.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto large_magnitude() const noexcept -> u16
  {
    return representation().large_magnitude;
  }

  /**
   * \brief Returns the magnitude of the small (high frequency) controller
   * motor.
   *
   * \return the magnitude of the small motor.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto small_magnitude() const noexcept -> u16
  {
    return representation().small_magnitude;
  }

  /**
   * \brief Returns the internal representation.
   *
   * \return the internal representation.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto representation() noexcept -> SDL_HapticLeftRight&
  {
    return m_effect.leftright;
  }

  /**
   * \copydoc representation();
   */
  [[nodiscard]] auto representation() const noexcept
      -> const SDL_HapticLeftRight&
  {
    return m_effect.leftright;
  }
};

template <typename B>
class basic_haptic;

/**
 * \typedef haptic
 *
 * \brief Represents an owning haptic device.
 *
 * \since 5.2.0
 */
using haptic = basic_haptic<std::true_type>;

/**
 * \typedef haptic_handle
 *
 * \brief Represents a non-owning haptic device.
 *
 * \since 5.2.0
 */
using haptic_handle = basic_haptic<std::false_type>;

/**
 * \class basic_haptic
 *
 * \brief Represents a haptic (force feedback) device.
 *
 * \tparam B `std::true_type` for owning haptic devices; `std::false_type` for
 * non-owning haptic devices.
 *
 * \see `haptic`
 * \see `haptic_handle`
 *
 * \since 5.2.0
 *
 * \headerfile haptic.hpp
 */
template <typename B>
class basic_haptic final
{
 public:
  using effect_id = int;

  /// \name Construction
  /// \{

  /**
   * \brief Creates a haptic instance based on an existing pointer.
   *
   * \note The created instance will claim ownership of the supplied pointer if
   * the class has owning semantics.
   *
   * \param haptic a pointer to the haptic device data.
   *
   * \throws exception if the supplied pointer is null and the class has owning
   * semantics.
   *
   * \since 5.2.0
   */
  explicit basic_haptic(SDL_Haptic* haptic) noexcept(!B::value)
      : m_haptic{haptic}
  {
    if constexpr (B::value) {
      if (!m_haptic) {
        throw exception{"Null haptic pointer!"};
      }
    }
  }

  /**
   * \brief Creates a haptic device based on a haptic device index.
   *
   * \note This constructor is only available for owning haptic instances.
   *
   * \tparam BB dummy parameter for SFINAE.
   *
   * \param index the device index of the desired haptic device.
   *
   * \throws sdl_error if the haptic device couldn't be opened.
   *
   * \since 5.2.0
   */
  template <typename BB = B, detail::is_owner<BB> = true>
  explicit basic_haptic(const int index = 0) : m_haptic{SDL_HapticOpen(index)}
  {
    if (!m_haptic) {
      throw sdl_error{};
    }
  }

  /**
   * \brief Creates a handle based on an owning haptic instance.
   *
   * \tparam BB dummy parameter for SFINAE.
   *
   * \param owner the associated owning haptic device.
   *
   * \since 5.2.0
   */
  template <typename BB = B, detail::is_handle<BB> = true>
  explicit basic_haptic(const haptic& owner) noexcept : m_haptic{owner.get()}
  {}

  /**
   * \brief Creates a haptic device based on a joystick.
   *
   * \note This function is only available for owning haptic instances.
   *
   * \tparam BB dummy parameter for SFINAE.
   *
   * \param joystick a joystick handle to the associated joystick.
   *
   * \throws sdl_error if the haptic device couldn't be opened.
   *
   * \see `is_joystick_haptic()`
   *
   * \since 5.2.0
   */
  template <typename T, typename BB = B, detail::is_owner<BB> = true>
  [[nodiscard]] static auto from_joystick(const basic_joystick<T>& joystick)
      -> basic_haptic
  {
    if (auto* ptr = SDL_HapticOpenFromJoystick(joystick.get())) {
      return basic_haptic{ptr};
    } else {
      throw sdl_error{};
    }
  }

  /**
   * \brief Creates a haptic device based on the current mouse.
   *
   * \note This function is only available for owning haptic instances.
   *
   * \tparam BB dummy parameter for SFINAE.
   *
   * \throws sdl_error if the haptic device couldn't be opened.
   *
   * \see `is_mouse_haptic()`
   *
   * \since 5.2.0
   */
  template <typename BB = B, detail::is_owner<BB> = true>
  [[nodiscard]] static auto from_mouse() -> basic_haptic
  {
    if (auto* ptr = SDL_HapticOpenFromMouse()) {
      return basic_haptic{ptr};
    } else {
      throw sdl_error{};
    }
  }

  /// \} End of construction

  /// \name Rumble effects
  /// \{

  /**
   * \brief Initializes rumble playback for the haptic device.
   *
   * \return `true` if rumble playback was successfully initialized; `false`
   * otherwise.
   *
   * \since 5.2.0
   */
  auto init_rumble() noexcept -> bool
  {
    return SDL_HapticRumbleInit(m_haptic) == 0;
  }

  /**
   * \brief Plays a rumble effect.
   *
   * \note Make sure to call ``init_rumble()`` before calling this function!
   *
   * \param strength the strength of the rumble effect, clamped to [0, 1].
   * \param duration the duration of the rumble effect.
   *
   * \return `true` on success; `false` if something went wrong.
   *
   * \since 5.2.0
   */
  auto play_rumble(const float strength, const milliseconds<u32> duration)
      -> bool
  {
    return SDL_HapticRumblePlay(m_haptic,
                                detail::clamp(strength, 0.0f, 1.0f),
                                duration.count()) == 0;
  }

  /**
   * \brief Stops the current rumble effect.
   *
   * \return `true` on success; `false` otherwise.
   *
   * \since 5.2.0
   */
  auto stop_rumble() noexcept -> bool
  {
    return SDL_HapticRumbleStop(m_haptic) == 0;
  }

  /**
   * \brief Indicates whether or not rumble playback is supported.
   *
   * \return `true` if rumble playback is supported; `false` otherwise.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto is_rumble_supported() const noexcept -> bool
  {
    return SDL_HapticRumbleSupported(m_haptic) == SDL_TRUE;
  }

  /// \} End of rumble effects

  /// \name Effects
  /// \{

  /**
   * \brief Pauses the device.
   *
   * \pre The device must support the `pause` feature.
   * \post You must call `unpause()` before calling `upload()` or `update()`.
   *
   * \return `true` on success; `false` otherwise.
   *
   * \since 5.2.0
   */
  auto pause() noexcept -> bool
  {
    assert(has_feature_pause());
    return SDL_HapticPause(m_haptic) == 0;
  }

  /**
   * \brief Unpauses the device.
   *
   * \pre `pause()` must have been called before this function is invoked.
   *
   * \return `true` on success; `false` otherwise.
   *
   * \since 5.2.0
   */
  auto unpause() noexcept -> bool
  {
    return SDL_HapticUnpause(m_haptic) == 0;
  }

  /**
   * \brief Uploads an effect to the device.
   *
   * \param effect the effect that will be uploaded to the device.
   *
   * \return the ID associated with the uploaded effect; `std::nullopt` if
   * something went wrong.
   *
   * \since 5.2.0
   */
  template <typename D>
  auto upload(const haptic_effect<D>& effect) noexcept
      -> std::optional<effect_id>
  {
    auto internal = effect.get();
    const auto id = SDL_HapticNewEffect(m_haptic, &internal);
    if (id != -1) {
      return id;
    } else {
      return std::nullopt;
    }
  }

  /**
   * \brief Attempts to update the effect associated with the specified ID.
   *
   * \note It is not possible to change the type of the effect through this
   * function.
   *
   * \note You might experience strange results if you call this function for an
   * effect that is currently playing, but it is possible.
   *
   * \param id the ID associated with the effect that will be updated.
   * \param effect the new properties that will be associated with the effect.
   *
   * \return `true` on success; `false` if something went wrong.
   *
   * \since 5.2.0
   */
  template <typename D>
  auto update(const effect_id id, const haptic_effect<D>& effect) noexcept
      -> bool
  {
    auto internal = effect.get();
    return SDL_HapticUpdateEffect(m_haptic, id, &internal) == 0;
  }

  /**
   * \brief Runs the specified effect.
   *
   * \note If you want to repeat the effect indefinitely without repeating the
   * attack and fade, see `haptic_effect::set_repeat_forever()`.
   *
   * \param id the ID associated with the effect that will be run.
   * \param iterations the number of iterations, can be `haptic_infinity` to
   * repeat the effect forever (including the attack and fade).
   *
   * \return `true` on success; `false` if something went wrong.
   *
   * \since 5.2.0
   */
  auto run(const effect_id id, const u32 iterations = 1) noexcept -> bool
  {
    return SDL_HapticRunEffect(m_haptic, id, iterations) == 0;
  }

  /**
   * \brief Stops a currently running effect.
   *
   * \param id the ID associated with the effect that will be stopped.
   *
   * \return `true` on success; `false` otherwise.
   *
   * \since 5.2.0
   */
  auto stop(const effect_id id) noexcept -> bool
  {
    return SDL_HapticStopEffect(m_haptic, id) == 0;
  }

  /**
   * \brief Stops all currently running effects on the device.
   *
   * \return `true` on success; `false` otherwise.
   *
   * \since 5.2.0
   */
  auto stop_all() noexcept -> bool
  {
    return SDL_HapticStopAll(m_haptic) == 0;
  }

  /**
   * \brief Destroys the effect associated with the specified ID.
   *
   * \note This is done automatically when the device is destructed.
   *
   * \details The effect will be destroyed will be stopped if it is running
   * by the time this function is invoked.
   *
   * \param id the ID associated with the effect that will be destroyed.
   *
   * \since 5.2.0
   */
  void destroy(const effect_id id) noexcept
  {
    SDL_HapticDestroyEffect(m_haptic, id);
  }

  /**
   * \brief Sets the gain the is used.
   *
   * \pre The device must support the `gain` feature.
   * \pre `gain` must be greater or equal to zero.
   * \pre `gain` must be less than or equal to zero.
   *
   * \param gain the gain that will be used, in the interval [0, 100].
   *
   * \return `true` on success; `false` otherwise.
   *
   * \since 5.2.0
   */
  auto set_gain(const int gain) noexcept -> bool
  {
    assert(has_feature_gain());
    assert(gain >= 0);
    assert(gain <= 100);
    return SDL_HapticSetGain(m_haptic, gain) == 0;
  }

  /**
   * \brief Sets the autocenter value that will be used.
   *
   * \pre The device must support the `autocenter` feature.
   * \pre `autocenter` must be greater or equal to zero.
   * \pre `autocenter` must be less than or equal to zero.
   *
   * \param autocenter the value of the autocenter that will be used, in the
   * interval [0, 100]. Autocentering will be disabled if this value is zero.
   *
   * \return `true` on success; `false` otherwise.
   *
   * \since 5.2.0
   */
  auto set_autocenter(const int autocenter) noexcept -> bool
  {
    assert(has_feature_autocenter());
    assert(autocenter >= 0);
    assert(autocenter <= 100);
    return SDL_HapticSetAutocenter(m_haptic, autocenter) == 0;
  }

  /**
   * \brief Indicates whether or not the device can run the specified effect.
   *
   * \param effect the effect that will be checked.
   *
   * \return `true` if the device supports the effect; `false` otherwise.
   *
   * \since 5.2.0
   */
  template <typename D>
  [[nodiscard]] auto is_supported(const haptic_effect<D>& effect) const noexcept
      -> bool
  {
    auto internal = effect.get();
    return SDL_HapticEffectSupported(m_haptic, &internal) == SDL_TRUE;
  }

  /**
   * \brief Indicates whether or not the specified effect is playing on the
   * device.
   *
   * \pre The device must support the `status` feature.
   *
   * \return `true` on if the effect is playing on the device; `false`
   * otherwise.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto is_playing(const effect_id id) const noexcept -> bool
  {
    assert(has_feature_status());
    return SDL_HapticGetEffectStatus(m_haptic, id) == 1;
  }

  /// \}

  /// \name Feature checks
  /// \{

  /**
   * \brief Indicates whether or not the device supports the specified feature.
   *
   * \param feature the haptic feature to be checked.
   *
   * \return `true` if the feature is supported; `false` otherwise.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto has_feature(const haptic_feature feature) const noexcept
      -> bool
  {
    return has_feature(static_cast<unsigned>(feature));
  }

  /**
   * \brief Indicates whether or not the device has the `constant` feature.
   *
   * \note This is a convenience function that calls `has_feature()`.
   *
   * \return `true` if the device has the feature; `false` otherwise.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto has_feature_constant() const noexcept -> bool
  {
    return has_feature(haptic_feature::constant);
  }

  /**
   * \brief Indicates whether or not the device has the `sine` feature.
   *
   * \note This is a convenience function that calls `has_feature()`.
   *
   * \return `true` if the device has the feature; `false` otherwise.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto has_feature_sine() const noexcept -> bool
  {
    return has_feature(haptic_feature::sine);
  }

  /**
   * \brief Indicates whether or not the device has the `left_right` feature.
   *
   * \note This is a convenience function that calls `has_feature()`.
   *
   * \return `true` if the device has the feature; `false` otherwise.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto has_feature_left_right() const noexcept -> bool
  {
    return has_feature(haptic_feature::left_right);
  }

  /**
   * \brief Indicates whether or not the device has the `triangle` feature.
   *
   * \note This is a convenience function that calls `has_feature()`.
   *
   * \return `true` if the device has the feature; `false` otherwise.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto has_feature_triangle() const noexcept -> bool
  {
    return has_feature(haptic_feature::triangle);
  }

  /**
   * \brief Indicates whether or not the device has the `sawtooth_up` feature.
   *
   * \note This is a convenience function that calls `has_feature()`.
   *
   * \return `true` if the device has the feature; `false` otherwise.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto has_feature_sawtooth_up() const noexcept -> bool
  {
    return has_feature(haptic_feature::sawtooth_up);
  }

  /**
   * \brief Indicates whether or not the device has the `sawtooth_down` feature.
   *
   * \note This is a convenience function that calls `has_feature()`.
   *
   * \return `true` if the device has the feature; `false` otherwise.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto has_feature_sawtooth_down() const noexcept -> bool
  {
    return has_feature(haptic_feature::sawtooth_down);
  }

  /**
   * \brief Indicates whether or not the device has the `ramp` feature.
   *
   * \note This is a convenience function that calls `has_feature()`.
   *
   * \return `true` if the device has the feature; `false` otherwise.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto has_feature_ramp() const noexcept -> bool
  {
    return has_feature(haptic_feature::ramp);
  }

  /**
   * \brief Indicates whether or not the device has the `spring` feature.
   *
   * \note This is a convenience function that calls `has_feature()`.
   *
   * \return `true` if the device has the feature; `false` otherwise.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto has_feature_spring() const noexcept -> bool
  {
    return has_feature(haptic_feature::spring);
  }

  /**
   * \brief Indicates whether or not the device has the `damper` feature.
   *
   * \note This is a convenience function that calls `has_feature()`.
   *
   * \return `true` if the device has the feature; `false` otherwise.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto has_feature_damper() const noexcept -> bool
  {
    return has_feature(haptic_feature::damper);
  }

  /**
   * \brief Indicates whether or not the device has the `inertia` feature.
   *
   * \note This is a convenience function that calls `has_feature()`.
   *
   * \return `true` if the device has the feature; `false` otherwise.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto has_feature_inertia() const noexcept -> bool
  {
    return has_feature(haptic_feature::inertia);
  }

  /**
   * \brief Indicates whether or not the device has the `friction` feature.
   *
   * \note This is a convenience function that calls `has_feature()`.
   *
   * \return `true` if the device has the feature; `false` otherwise.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto has_feature_friction() const noexcept -> bool
  {
    return has_feature(haptic_feature::friction);
  }

  /**
   * \brief Indicates whether or not the device has the `gain` feature.
   *
   * \note This is a convenience function that calls `has_feature()`.
   *
   * \return `true` if the device has the feature; `false` otherwise.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto has_feature_gain() const noexcept -> bool
  {
    return has_feature(haptic_feature::gain);
  }

  /**
   * \brief Indicates whether or not the device has the `autocenter` feature.
   *
   * \note This is a convenience function that calls `has_feature()`.
   *
   * \return `true` if the device has the feature; `false` otherwise.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto has_feature_autocenter() const noexcept -> bool
  {
    return has_feature(haptic_feature::autocenter);
  }

  /**
   * \brief Indicates whether or not the device has the `status` feature.
   *
   * \note This is a convenience function that calls `has_feature()`.
   *
   * \return `true` if the device has the feature; `false` otherwise.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto has_feature_status() const noexcept -> bool
  {
    return has_feature(haptic_feature::status);
  }

  /**
   * \brief Indicates whether or not the device has the `pause` feature.
   *
   * \note This is a convenience function that calls `has_feature()`.
   *
   * \return `true` if the device has the feature; `false` otherwise.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto has_feature_pause() const noexcept -> bool
  {
    return has_feature(haptic_feature::pause);
  }

  /**
   * \brief Indicates whether or not the device has the `custom` feature.
   *
   * \note This is a convenience function that calls `has_feature()`.
   *
   * \return `true` if the device has the feature; `false` otherwise.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto has_feature_custom() const noexcept -> bool
  {
    return has_feature(haptic_feature::custom);
  }

  /// \} End of feature queries

  /// \name Device information
  /// \{

  /**
   * \brief Returns the index associated with the haptic device.
   *
   * \return the index associated with the haptic device; `std::nullopt` if
   * something goes wrong.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto index() const noexcept -> std::optional<int>
  {
    const auto res = SDL_HapticIndex(m_haptic);
    if (res != -1) {
      return res;
    } else {
      return std::nullopt;
    }
  }

  /**
   * \brief Attempts to return the name associated with the haptic device.
   *
   * \return the name associated with the haptic device; a null pointer is
   * returned if no name was found.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto name() const noexcept -> czstring
  {
    if (const auto i = index()) {
      return SDL_HapticName(*i);
    } else {
      return nullptr;
    }
  }

  /**
   * \brief Returns the maximum amount of effect the device can store.
   *
   * \note This function isn't supported on all platforms and the returned value
   * should be treated as an approximation.
   *
   * \return the maximum number of effects the the haptic device can store;
   * `std::nullopt` if something goes wrong.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto effect_capacity() const noexcept -> std::optional<int>
  {
    const auto capacity = SDL_HapticNumEffects(m_haptic);
    if (capacity != -1) {
      return capacity;
    } else {
      return std::nullopt;
    }
  }

  /**
   * \brief Returns the maximum amount of effects that can be played
   * simultaneously.
   *
   * \note This function isn't supported on all platforms.
   *
   * \return the maximum number of effects that can be playing simultaneously;
   * `std::nullopt` if something goes wrong.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto concurrent_capacity() const noexcept -> std::optional<int>
  {
    const auto capacity = SDL_HapticNumEffectsPlaying(m_haptic);
    if (capacity != -1) {
      return capacity;
    } else {
      return std::nullopt;
    }
  }

  /**
   * \brief Returns the number of axes that the haptic device has.
   *
   * \return the number of axes that the haptic device has.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto axis_count() const noexcept -> int
  {
    return SDL_HapticNumAxes(m_haptic);
  }

  /// \} End of device information

  /**
   * \brief Returns the number of available haptic devices.
   *
   * \return the amount of available haptic devices.
   *
   * \since 5.2.0
   */
  [[nodiscard]] static auto count() noexcept -> int
  {
    return SDL_NumHaptics();
  }

  /**
   * \brief Indicates whether or not a joystick has haptic capabilities.
   *
   * \param joystick the joystick that will be checked.
   *
   * \return `true` if the joystick has haptic capabilities; `false` otherwise.
   *
   * \since 5.2.0
   */
  template <typename T>
  [[nodiscard]] static auto is_joystick_haptic(
      const basic_joystick<T>& joystick) noexcept -> bool
  {
    return SDL_JoystickIsHaptic(joystick.get()) == SDL_TRUE;
  }

  /**
   * \brief Indicates whether or not the system mouse has haptic capabilities.
   *
   * \return `true` if the mouse has haptic capabilities; `false` otherwise.
   *
   * \since 5.2.0
   */
  [[nodiscard]] static auto is_mouse_haptic() noexcept -> bool
  {
    return SDL_MouseIsHaptic();
  }

  /**
   * \brief Indicates whether or not a haptic device at a specified index has
   * been opened.
   *
   * \param index the index of the haptic device that will be queried.
   *
   * \return `true` if the haptic device has been opened; `false` otherwise.
   *
   * \since 5.2.0
   */
  [[nodiscard]] static auto is_opened(const int index) noexcept -> bool
  {
    return SDL_HapticOpened(index);
  }

  /**
   * \brief Indicates whether or not the handle holds a non-null pointer.
   *
   * \tparam BB dummy parameter for SFINAE.
   *
   * \return `true` if the handle holds a non-null pointer; `false` otherwise.
   *
   * \since 5.2.0
   */
  template <typename BB = B, detail::is_handle<BB> = true>
  explicit operator bool() const noexcept
  {
    return m_haptic != nullptr;
  }

  /**
   * \brief Returns a pointer to the internal representation.
   *
   * \warning Don't claim ownership of the returned pointer!
   *
   * \return a pointer to the internal representation.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto get() const noexcept -> SDL_Haptic*
  {
    return m_haptic.get();
  }

 private:
  struct deleter final
  {
    void operator()(SDL_Haptic* haptic) noexcept
    {
      SDL_HapticClose(haptic);
    }
  };
  detail::pointer_manager<B, SDL_Haptic, deleter> m_haptic;

  /**
   * \brief Indicates whether or not the haptic device supports the specified
   features.
   *
   * \details The supplied value must be a masked subset of the following flags:
   *
   * \verbatim
       SDL_HAPTIC_CONSTANT
       SDL_HAPTIC_SINE
       SDL_HAPTIC_LEFTRIGHT
       SDL_HAPTIC_LEFTRIGHT
       SDL_HAPTIC_TRIANGLE
       SDL_HAPTIC_SAWTOOTHUP
       SDL_HAPTIC_SAWTOOTHDOWN
       SDL_HAPTIC_RAMP
       SDL_HAPTIC_SPRING
       SDL_HAPTIC_DAMPER
       SDL_HAPTIC_INERTIA
       SDL_HAPTIC_FRICTION
       SDL_HAPTIC_CUSTOM
       SDL_HAPTIC_GAIN
       SDL_HAPTIC_AUTOCENTER
       SDL_HAPTIC_STATUS
       SDL_HAPTIC_PAUSE.
   * \endverbatim
   *
   * \param flag the mask of feature flags.
   *
   * \return `true` if the haptic device supports the features; `false`
   otherwise.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto has_feature(const unsigned flag) const noexcept -> bool
  {
    return static_cast<bool>(flag & SDL_HapticQuery(m_haptic));
  }
};

/**
 * \brief Returns a textual representation of a haptic device.
 *
 * \tparam B the ownership semantics parameter for the haptic type.
 *
 * \param haptic the haptic device that will be converted.
 *
 * \return a string that represents a haptic device.
 *
 * \since 5.2.0
 */
template <typename B>
[[nodiscard]] auto to_string(const basic_haptic<B>& haptic) -> std::string
{
  const auto* name = haptic.name();
  const auto nameStr = name ? std::string{name} : std::string{"N/A"};
  return "[haptic | data: " + detail::address_of(haptic.get()) +
         ", name: " + nameStr + "]";
}

/**
 * \brief Prints a textual representation of a haptic device using a stream.
 *
 * \tparam B the ownership semantics parameter for the haptic type.
 *
 * \param stream the stream that will be used.
 * \param haptic the haptic device that will be printed.
 *
 * \return the used stream.
 *
 * \since 5.2.0
 */
template <typename B>
auto operator<<(std::ostream& stream, const basic_haptic<B>& haptic)
    -> std::ostream&
{
  stream << to_string(haptic);
  return stream;
}

/// \} End of input group

}  // namespace cen

#endif  // CENTURION_HAPTIC_HEADER
