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

#include <type_traits>  // true_type, false_type

#include "centurion_cfg.hpp"
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
    const auto res = SDL_HapticRumbleInit(m_haptic);
    return res == 0;
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
    const auto res = SDL_HapticRumblePlay(m_haptic,
                                          detail::clamp(strength, 0.0f, 1.0f),
                                          duration.count());
    return res == 0;
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
    const auto res = SDL_HapticRumbleStop(m_haptic);
    return res == 0;
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

  /// \name Feature checks
  /// \{

  [[nodiscard]] auto has_feature(const haptic_feature feature) const noexcept
      -> bool
  {
    return has_feature(static_cast<unsigned>(feature));
  }

  [[nodiscard]] auto has_feature_constant() const noexcept -> bool
  {
    return has_feature(SDL_HAPTIC_CONSTANT);
  }

  [[nodiscard]] auto has_feature_sine() const noexcept -> bool
  {
    return has_feature(SDL_HAPTIC_SINE);
  }

  [[nodiscard]] auto has_feature_left_right() const noexcept -> bool
  {
    return has_feature(SDL_HAPTIC_LEFTRIGHT);
  }

  [[nodiscard]] auto has_feature_triangle() const noexcept -> bool
  {
    return has_feature(SDL_HAPTIC_TRIANGLE);
  }

  [[nodiscard]] auto has_feature_sawtooth_up() const noexcept -> bool
  {
    return has_feature(SDL_HAPTIC_SAWTOOTHUP);
  }

  [[nodiscard]] auto has_feature_sawtooth_down() const noexcept -> bool
  {
    return has_feature(SDL_HAPTIC_SAWTOOTHDOWN);
  }

  [[nodiscard]] auto has_feature_ramp() const noexcept -> bool
  {
    return has_feature(SDL_HAPTIC_RAMP);
  }

  [[nodiscard]] auto has_feature_spring() const noexcept -> bool
  {
    return has_feature(SDL_HAPTIC_SPRING);
  }

  [[nodiscard]] auto has_feature_damper() const noexcept -> bool
  {
    return has_feature(SDL_HAPTIC_DAMPER);
  }

  [[nodiscard]] auto has_feature_inertia() const noexcept -> bool
  {
    return has_feature(SDL_HAPTIC_INERTIA);
  }

  [[nodiscard]] auto has_feature_friction() const noexcept -> bool
  {
    return has_feature(SDL_HAPTIC_FRICTION);
  }

  [[nodiscard]] auto has_feature_gain() const noexcept -> bool
  {
    return has_feature(SDL_HAPTIC_GAIN);
  }

  [[nodiscard]] auto has_feature_autocenter() const noexcept -> bool
  {
    return has_feature(SDL_HAPTIC_AUTOCENTER);
  }

  [[nodiscard]] auto has_feature_status() const noexcept -> bool
  {
    return has_feature(SDL_HAPTIC_STATUS);
  }

  [[nodiscard]] auto has_feature_pause() const noexcept -> bool
  {
    return has_feature(SDL_HAPTIC_PAUSE);
  }

  [[nodiscard]] auto has_feature_custom() const noexcept -> bool
  {
    return has_feature(SDL_HAPTIC_CUSTOM);
  }

  /// \} End of feature queries

 private:
  struct deleter final
  {
    void operator()(SDL_Haptic* haptic) noexcept
    {
      SDL_HapticClose(haptic);
    }
  };
  detail::pointer_manager<B, SDL_Haptic, deleter> m_haptic{};

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
  [[nodiscard]] auto has_feature(unsigned flag) const noexcept -> bool
  {
    return static_cast<bool>(flag & SDL_HapticQuery(m_haptic));
  }
};

}  // namespace cen

#endif  // CENTURION_HAPTIC_HEADER
