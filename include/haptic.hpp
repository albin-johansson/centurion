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

#include <optional>     // optional
#include <type_traits>  // true_type, false_type, enable_if_t

#include "centurion_cfg.hpp"
#include "czstring.hpp"
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

// TODO consistency: noexcept-specifier when using duration::count()?

namespace cen {

// Features:
//  - SDL_HAPTIC_CONSTANT
//  - SDL_HAPTIC_SINE
//  - SDL_HAPTIC_LEFTRIGHT
//  - SDL_HAPTIC_TRIANGLE
//  - SDL_HAPTIC_SAWTOOTHUP
//  - SDL_HAPTIC_SAWTOOTHDOWN
//  - SDL_HAPTIC_RAMP
//  - SDL_HAPTIC_SPRING
//  - SDL_HAPTIC_DAMPER
//  - SDL_HAPTIC_INERTIA
//  - SDL_HAPTIC_FRICTION
//  - SDL_HAPTIC_CUSTOM
//  - SDL_HAPTIC_GAIN
//  - SDL_HAPTIC_AUTOCENTER
//  - SDL_HAPTIC_STATUS
//  - SDL_HAPTIC_PAUSE
//  - ?? SDL_HAPTIC_POLAR ??
//  - ?? SDL_HAPTIC_CARTESIAN ??
//  - ?? SDL_HAPTIC_SPHERICAL ??

enum class haptic_feature  // TODO verify that these are all of the "features"
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

template <typename Derived>
class haptic_effect
{
  template <typename T>
  using has_envelope = std::enable_if_t<T::hasEnvelope, bool>;

  template <typename T>
  using has_trigger = std::enable_if_t<T::hasTrigger, bool>;

  template <typename T>
  using has_delay = std::enable_if_t<T::hasDelay, bool>;

 public:
  /// \name Replay functions
  /// \{

  void set_duration(const milliseconds<u32> ms)
  {
    rep().length = ms.count();
  }

  template <typename D = Derived, has_delay<D> = true>
  void set_delay(const milliseconds<u16> ms)
  {
    rep().delay = ms.count();
  }

  // Duration of effect (ms).
  [[nodiscard]] auto duration() const -> milliseconds<u32>
  {
    return milliseconds<u32>{rep().length};
  }

  // Delay before starting effect.
  template <typename D = Derived, has_delay<D> = true>
  [[nodiscard]] auto delay() const -> milliseconds<u16>
  {
    return milliseconds<u16>{rep().delay};
  }

  /// \} End of replay functions

  /// \name Trigger functions
  /// \{

  template <typename D = Derived, has_trigger<D> = true>
  void set_button(const u16 button) noexcept
  {
    rep().button = button;
  }

  template <typename D = Derived, has_trigger<D> = true>
  void set_interval(const milliseconds<u16> ms)
  {
    rep().interval = ms.count();
  }

  // Button that triggers effect.
  template <typename D = Derived, has_trigger<D> = true>
  [[nodiscard]] auto button() const noexcept -> u16
  {
    return rep().button;
  }

  // How soon before effect can be triggered again.
  template <typename D = Derived, has_trigger<D> = true>
  [[nodiscard]] auto interval() const -> milliseconds<u16>
  {
    return milliseconds<u16>{rep().interval};
  }

  /// \} End of trigger functions

  /// \name Envelope functions
  /// \{

  template <typename D = Derived, has_envelope<D> = true>
  void set_attack_level(const u16 level) noexcept
  {
    rep().attack_level = level;
  }

  template <typename D = Derived, has_envelope<D> = true>
  void set_fade_level(const u16 level) noexcept
  {
    rep().fade_level = level;
  }

  template <typename D = Derived, has_envelope<D> = true>
  void set_attack_duration(const milliseconds<u16> ms)
  {
    rep().attack_length = ms.count();
  }

  template <typename D = Derived, has_envelope<D> = true>
  void set_fade_duration(const milliseconds<u16> ms)
  {
    rep().fade_length = ms.count();
  }

  // Level at the start of the attack.
  template <typename D = Derived, has_envelope<D> = true>
  [[nodiscard]] auto attack_level() const noexcept -> u16
  {
    return rep().attack_level;
  }

  // Level at the end of the fade.
  template <typename D = Derived, has_envelope<D> = true>
  [[nodiscard]] auto fade_level() const noexcept -> u16
  {
    return rep().fade_level;
  }

  // Duration of the attack.
  template <typename D = Derived, has_envelope<D> = true>
  [[nodiscard]] auto attack_duration() const -> milliseconds<u16>
  {
    return milliseconds<u16>{rep().attack_length};
  }

  // Duration of the fade out.
  template <typename D = Derived, has_envelope<D> = true>
  [[nodiscard]] auto fade_duration() const -> milliseconds<u16>
  {
    return milliseconds<u16>{rep().fade_length};
  }

  /// \} End of envelope functions

  [[nodiscard]] auto type() const noexcept -> u16
  {
    return rep().type;
  }

  // TODO SDL_HapticDirection

  [[nodiscard]] auto get() noexcept -> SDL_HapticEffect&
  {
    return m_effect;
  }

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

class haptic_constant final : public haptic_effect<haptic_constant>
{
 public:
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

  [[nodiscard]] auto representation() noexcept -> SDL_HapticConstant&
  {
    return m_effect.constant;
  }

  [[nodiscard]] auto representation() const noexcept
      -> const SDL_HapticConstant&
  {
    return m_effect.constant;
  }
};

class haptic_periodic final : public haptic_effect<haptic_periodic>
{
 public:
  inline constexpr static bool hasEnvelope = true;
  inline constexpr static bool hasTrigger = true;
  inline constexpr static bool hasDelay = true;

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
  haptic_periodic() noexcept
  {
    m_effect.periodic = {};
    representation().type = SDL_HAPTIC_SINE;
  }

  void set_type(const periodic_type type) noexcept
  {
    representation().type = static_cast<u16>(type);
  }

  // Period of the wave.
  void set_period(const milliseconds<u16> ms)
  {
    representation().period = ms.count();
  }

  // Peak value; if negative, equivalent to 180 degrees extra phase shift.
  void set_magnitude(const i16 magnitude) noexcept
  {
    representation().magnitude = magnitude;
  }

  // Mean value of the wave.
  void set_offset(const i16 offset) noexcept
  {
    representation().offset = offset;
  }

  // Positive phase shift given by hundredth of a degree.
  void set_phase(const u16 phase) noexcept
  {
    representation().phase = phase;
  }

  [[nodiscard]] auto period() const -> milliseconds<u16>
  {
    return milliseconds<u16>{representation().period};
  }

  [[nodiscard]] auto magnitude() const noexcept -> i16
  {
    return representation().magnitude;
  }

  [[nodiscard]] auto offset() const noexcept -> i16
  {
    return representation().offset;
  }

  [[nodiscard]] auto phase() const noexcept -> u16
  {
    return representation().phase;
  }

  [[nodiscard]] auto representation() noexcept -> SDL_HapticPeriodic&
  {
    return m_effect.periodic;
  }

  [[nodiscard]] auto representation() const noexcept
      -> const SDL_HapticPeriodic&
  {
    return m_effect.periodic;
  }
};

class haptic_ramp final : public haptic_effect<haptic_ramp>
{
 public:
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

  // Beginning strength level.
  void set_start_strength(const i16 start) noexcept
  {
    representation().start = start;
  }

  // Ending strength level.
  void set_end_strength(const i16 end) noexcept
  {
    representation().end = end;
  }

  [[nodiscard]] auto start_strength() const noexcept -> i16
  {
    return representation().start;
  }

  [[nodiscard]] auto end_strength() const noexcept -> i16
  {
    return representation().end;
  }

  [[nodiscard]] auto representation() noexcept -> SDL_HapticRamp&
  {
    return m_effect.ramp;
  }

  [[nodiscard]] auto representation() const noexcept -> const SDL_HapticRamp&
  {
    return m_effect.ramp;
  }
};

class haptic_custom final : public haptic_effect<haptic_custom>
{
 public:
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

  // Axes to use, minimum of one.
  void set_axis_count(const u8 count) noexcept
  {
    representation().channels = detail::max(u8{1}, count);
  }

  void set_sample_period(const milliseconds<u16> ms)
  {
    representation().period = ms.count();
  }

  // Amount of samples.
  void set_sample_count(const u16 count) noexcept
  {
    representation().samples = count;
  }

  void set_data(u16* data) noexcept
  {
    representation().data = data;
  }

  [[nodiscard]] auto axis_count() const noexcept -> u8
  {
    return representation().channels;
  }

  [[nodiscard]] auto sample_period() const -> milliseconds<u16>
  {
    return milliseconds<u16>{representation().period};
  }

  [[nodiscard]] auto sample_count() const noexcept -> u16
  {
    return representation().samples;
  }

  [[nodiscard]] auto data() const noexcept -> u16*
  {
    return representation().data;
  }

  [[nodiscard]] auto representation() noexcept -> SDL_HapticCustom&
  {
    return m_effect.custom;
  }

  [[nodiscard]] auto representation() const noexcept -> const SDL_HapticCustom&
  {
    return m_effect.custom;
  }
};

class haptic_condition final : public haptic_effect<haptic_condition>
{
 public:
  inline constexpr static bool hasEnvelope = false;
  inline constexpr static bool hasTrigger = true;
  inline constexpr static bool hasDelay = true;

  enum condition_type : u32
  {
    spring = SDL_HAPTIC_SPRING,     ///< Based on axes position.
    damper = SDL_HAPTIC_DAMPER,     ///< Based on axes velocity.
    inertia = SDL_HAPTIC_INERTIA,   ///< Based on axes acceleration.
    friction = SDL_HAPTIC_FRICTION  ///< Based on axes movement.
  };

  explicit haptic_condition(const condition_type type = spring) noexcept
  {
    m_effect.condition = {};
    set_type(type);
  }

  void set_type(const condition_type type) noexcept
  {
    representation().type = type;
  }

  /// Level when joystick is to the positive side; max 0xFFFF.
  void set_joystick_positive_level(const vector3<u16>& level) noexcept
  {
    representation().right_sat[0] = level.x;
    representation().right_sat[1] = level.y;
    representation().right_sat[2] = level.z;
  }

  /// Level when joystick is to the negative side; max 0xFFFF.
  void set_joystick_negative_level(const vector3<u16>& level) noexcept
  {
    representation().left_sat[0] = level.x;
    representation().left_sat[1] = level.y;
    representation().left_sat[2] = level.z;
  }

  /// How fast to increase the force towards the positive side.
  void set_force_rate_positive(const vector3<i16>& rate) noexcept
  {
    representation().right_coeff[0] = rate.x;
    representation().right_coeff[1] = rate.y;
    representation().right_coeff[2] = rate.z;
  }

  // How fast to increase the force towards the negative side.
  void set_force_rate_negative(const vector3<i16>& rate) noexcept
  {
    representation().left_coeff[0] = rate.x;
    representation().left_coeff[1] = rate.y;
    representation().left_coeff[2] = rate.z;
  }

  /// Size of the dead zone; max 0xFFFF: whole axis-range when 0-centered.
  void set_deadband(const vector3<u16>& size) noexcept
  {
    representation().deadband[0] = size.x;
    representation().deadband[1] = size.y;
    representation().deadband[2] = size.z;
  }

  /// Position of the dead zone.
  void set_center(const vector3<i16>& center) noexcept
  {
    representation().center[0] = center.x;
    representation().center[1] = center.y;
    representation().center[2] = center.z;
  }

  [[nodiscard]] auto joystick_positive_level() const noexcept -> vector3<u16>
  {
    const auto& level = representation().right_sat;
    return {level[0], level[1], level[2]};
  }

  [[nodiscard]] auto joystick_negative_level() const noexcept -> vector3<u16>
  {
    const auto& level = representation().left_sat;
    return {level[0], level[1], level[2]};
  }

  [[nodiscard]] auto force_rate_positive() const noexcept -> vector3<i16>
  {
    const auto& rate = representation().right_coeff;
    return {rate[0], rate[1], rate[2]};
  }

  [[nodiscard]] auto force_rate_negative() const noexcept -> vector3<i16>
  {
    const auto& rate = representation().left_coeff;
    return {rate[0], rate[1], rate[2]};
  }

  [[nodiscard]] auto deadband() const noexcept -> vector3<u16>
  {
    const auto& band = representation().deadband;
    return {band[0], band[1], band[2]};
  }

  [[nodiscard]] auto center() const noexcept -> vector3<i16>
  {
    const auto& center = representation().center;
    return {center[0], center[1], center[2]};
  }

  [[nodiscard]] auto representation() noexcept -> SDL_HapticCondition&
  {
    return m_effect.condition;
  }

  [[nodiscard]] auto representation() const noexcept
      -> const SDL_HapticCondition&
  {
    return m_effect.condition;
  }
};

class haptic_left_right final : public haptic_effect<haptic_left_right>
{
 public:
  inline constexpr static bool hasEnvelope = false;
  inline constexpr static bool hasTrigger = false;
  inline constexpr static bool hasDelay = false;

  haptic_left_right() noexcept
  {
    m_effect.leftright = {};
    representation().type = SDL_HAPTIC_LEFTRIGHT;
  }

  // Control of the large controller motor.
  void set_large_magnitude(const u16 magnitude) noexcept
  {
    representation().large_magnitude = magnitude;
  }

  // Control of the small controller motor.
  void set_small_magnitude(const u16 magnitude) noexcept
  {
    representation().small_magnitude = magnitude;
  }

  [[nodiscard]] auto large_magnitude() const noexcept -> u16
  {
    return representation().large_magnitude;
  }

  [[nodiscard]] auto small_magnitude() const noexcept -> u16
  {
    return representation().small_magnitude;
  }

  [[nodiscard]] auto representation() noexcept -> SDL_HapticLeftRight&
  {
    return m_effect.leftright;
  }

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
class basic_haptic final  // TODO RtD entry
{
 public:
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
  template <typename BB = B, detail::is_owner<BB> = true>
  [[nodiscard]] static auto from_joystick(joystick_handle joystick)
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

  // TODO SDL_HapticDestroyEffect     -> destroy_effect
  // TODO SDL_HapticGetEffectStatus   -> effect_status
  // TODO SDL_HapticSetGain           -> set_gain
  // TODO SDL_HapticSetAutocenter     -> set_autocenter
  // TODO SDL_HapticPause             -> pause
  // TODO SDL_HapticUnpause           -> unpause
  // TODO SDL_HapticStopAll           -> stop_all

  template <typename D>
  auto add(const haptic_effect<D>& effect) noexcept -> std::optional<int>
  {
    auto copy = effect.get();
    const auto id = SDL_HapticNewEffect(m_haptic, &copy);
    if (id != -1) {
      return id;
    } else {
      return std::nullopt;
    }
  }

  template <typename D>
  auto update(const int id, const haptic_effect<D>& effect) -> bool
  {
    auto copy = effect.get();
    return SDL_HapticUpdateEffect(m_haptic, id, &copy) == 0;
  }

  auto run(const int id, const u32 iterations = 1) -> bool
  {
    return SDL_HapticRunEffect(m_haptic, id, iterations) == 0;
  }

  auto stop(const int id) -> bool
  {
    return SDL_HapticStopEffect(m_haptic, id) == 0;
  }

  template <typename D>
  [[nodiscard]] auto is_supported(const haptic_effect<D>& effect) const noexcept
      -> bool
  {
    auto copy = effect.get();
    return SDL_HapticEffectSupported(m_haptic, &copy) == SDL_TRUE;
  }

  /// \}

  /// \name Feature checks
  /// \{

  [[nodiscard]] auto has_feature(const haptic_feature feature) const noexcept
      -> bool
  {
    return has_feature(static_cast<unsigned>(feature));
  }

  [[nodiscard]] auto has_feature_constant() const noexcept -> bool
  {
    return has_feature(haptic_feature::constant);
  }

  [[nodiscard]] auto has_feature_sine() const noexcept -> bool
  {
    return has_feature(haptic_feature::sine);
  }

  [[nodiscard]] auto has_feature_left_right() const noexcept -> bool
  {
    return has_feature(haptic_feature::left_right);
  }

  [[nodiscard]] auto has_feature_triangle() const noexcept -> bool
  {
    return has_feature(haptic_feature::triangle);
  }

  [[nodiscard]] auto has_feature_sawtooth_up() const noexcept -> bool
  {
    return has_feature(haptic_feature::sawtooth_up);
  }

  [[nodiscard]] auto has_feature_sawtooth_down() const noexcept -> bool
  {
    return has_feature(haptic_feature::sawtooth_down);
  }

  [[nodiscard]] auto has_feature_ramp() const noexcept -> bool
  {
    return has_feature(haptic_feature::ramp);
  }

  [[nodiscard]] auto has_feature_spring() const noexcept -> bool
  {
    return has_feature(haptic_feature::spring);
  }

  [[nodiscard]] auto has_feature_damper() const noexcept -> bool
  {
    return has_feature(haptic_feature::damper);
  }

  [[nodiscard]] auto has_feature_inertia() const noexcept -> bool
  {
    return has_feature(haptic_feature::inertia);
  }

  [[nodiscard]] auto has_feature_friction() const noexcept -> bool
  {
    return has_feature(haptic_feature::friction);
  }

  [[nodiscard]] auto has_feature_gain() const noexcept -> bool
  {
    return has_feature(haptic_feature::gain);
  }

  [[nodiscard]] auto has_feature_autocenter() const noexcept -> bool
  {
    return has_feature(haptic_feature::autocenter);
  }

  [[nodiscard]] auto has_feature_status() const noexcept -> bool
  {
    return has_feature(haptic_feature::status);
  }

  [[nodiscard]] auto has_feature_pause() const noexcept -> bool
  {
    return has_feature(haptic_feature::pause);
  }

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

}  // namespace cen

#endif  // CENTURION_HAPTIC_HEADER
