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
#include <type_traits>  // true_type, false_type

#include "centurion_cfg.hpp"
#include "czstring.hpp"
#include "detail/clamp.hpp"
#include "detail/owner_handle_api.hpp"
#include "exception.hpp"
#include "integers.hpp"
#include "joystick.hpp"
#include "time.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE


namespace cen {


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
 public:

  void set_duration(const milliseconds<u32> ms)
  {
    representation().length = ms.count();
  }

  void set_delay(const milliseconds<u16> ms)
  {
    representation().delay = ms.count();
  }

  void set_interval(const milliseconds<u16> ms)
  {
    representation().interval = ms.count();
  }

  void set_attack_duration(const milliseconds<u16> ms)
  {
    representation().attack_length = ms.count();
  }

  void set_fade_duration(const milliseconds<u16> ms)
  {
    representation().fade_length = ms.count();
  }

  void set_button(const u16 button) noexcept
  {
    representation().button = button;
  }

  void set_attack_level(const u16 level) noexcept
  {
    representation().attack_level = level;
  }

  void set_fade_level(const u16 level) noexcept
  {
    representation().fade_level = level;
  }

  // Duration of effect (ms).
  [[nodiscard]] auto duration() const -> milliseconds<u32>
  {
    return milliseconds<u32>{representation().length};
  }

  // Delay before starting effect.
  [[nodiscard]] auto delay() const -> milliseconds<u16>
  {
    return milliseconds<u16>{representation().delay};
  }

  // How soon before effect can be triggered again.
  [[nodiscard]] auto interval() const noexcept -> milliseconds<u16>
  {
    return milliseconds<u16>{representation().interval};
  }

  // Duration of the attack.
  [[nodiscard]] auto attack_duration() const noexcept -> milliseconds<u16>
  {
    return milliseconds<u16>{representation().attack_length};
  }

  // Duration of the fade out.
  [[nodiscard]] auto fade_duration() const noexcept -> milliseconds<u16>
  {
    return milliseconds<u16>{representation().fade_length};
  }

  // Button that triggers effect.
  [[nodiscard]] auto button() const noexcept -> u16
  {
    return representation().button;
  }

  // Level at the start of the attack.
  [[nodiscard]] auto attack_level() const noexcept -> u16
  {
    return representation().attack_level;
  }

  // Level at the end of the fade.
  [[nodiscard]] auto fade_level() const noexcept -> u16
  {
    return representation().fade_level;
  }

  [[nodiscard]] auto type() const noexcept -> u16
  {
    return representation().type;
  }

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

  [[nodiscard]] auto representation() noexcept -> auto&
  {
    return derived()->representation();
  }

  [[nodiscard]] auto representation() const noexcept -> const auto&
  {
    return derived()->representation();
  }
};

class haptic_constant final : public haptic_effect<haptic_constant>
{
 public:
  /**
   * \brief Creates a constant haptic effect.
   *
   * \since 5.2.0
   */
  haptic_constant() noexcept
  {
    m_effect.constant = {};
    m_effect.constant.type = SDL_HAPTIC_CONSTANT;
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
   * \details The type of the effects defaults to `SDL_HAPTIC_SINE`.
   *
   * \since 5.2.0
   */
  haptic_periodic() noexcept
  {
    m_effect.periodic = {};
    m_effect.periodic.type = SDL_HAPTIC_SINE;
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
