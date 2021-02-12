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

#ifndef CENTURION_JOYSTICK_HEADER
#define CENTURION_JOYSTICK_HEADER

#include <SDL.h>

#include <cassert>      // assert
#include <optional>     // optional
#include <type_traits>  // true_type, false_type, is_same_v

#include "button_state.hpp"
#include "centurion_cfg.hpp"
#include "color.hpp"
#include "czstring.hpp"
#include "detail/owner_handle_api.hpp"
#include "exception.hpp"
#include "integers.hpp"
#include "not_null.hpp"
#include "time.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/// \addtogroup input
/// \{

template <typename B>
class basic_joystick;

/**
 * \typedef joystick
 *
 * \brief Represents an owning joystick.
 *
 * \since 5.0.0
 */
using joystick = basic_joystick<std::true_type>;

/**
 * \typedef joystick_handle
 *
 * \brief Represents a non-owning joystick.
 *
 * \since 5.0.0
 */
using joystick_handle = basic_joystick<std::false_type>;

/**
 * \class basic_joystick
 *
 * \brief Represents a joystick device.
 *
 * \details The game controller API is built on top of the joystick API, which
 * means that the game controller is higher-level and easier to use.
 *
 * \tparam B `std::true_type` for a owning joysticks; `std::false_type` for
 * non-owning joysticks.
 *
 * \since 4.2.0
 *
 * \see joystick
 * \see joystick_handle
 *
 * \headerfile joystick.hpp
 */
template <typename B>
class basic_joystick final
{
  inline static constexpr bool isOwner = std::is_same_v<B, std::true_type>;
  inline static constexpr bool isHandle = std::is_same_v<B, std::false_type>;

 public:
  /**
   * \enum power
   *
   * \brief Mirrors the `SDL_JoystickPowerLevel` enum.
   *
   * \since 4.2.0
   *
   * \todo Centurion 6: Rename to joystick_power and move out of class.
   *
   * \headerfile joystick.hpp
   */
  enum class power
  {
    unknown = SDL_JOYSTICK_POWER_UNKNOWN,  ///< Unknown power level.
    empty = SDL_JOYSTICK_POWER_EMPTY,      ///< Indicates <= 5% power.
    low = SDL_JOYSTICK_POWER_LOW,          ///< Indicates <= 20% power.
    medium = SDL_JOYSTICK_POWER_MEDIUM,    ///< Indicates <= 70% power.
    full = SDL_JOYSTICK_POWER_FULL,        ///< Indicates <= 100% power.
    wired = SDL_JOYSTICK_POWER_WIRED,      /**< Wired joystick, no need to
                                            * worry about power. */
    max = SDL_JOYSTICK_POWER_MAX           ///< Maximum power level.
  };

  /**
   * \enum hat_state
   *
   * \brief Represents the various states of a joystick hat.
   *
   * \since 4.2.0
   *
   * \todo Centurion 6: Rename to joystick_hat_state and move out of class.
   *
   * \headerfile joystick.hpp
   */
  enum class hat_state
  {
    centered = SDL_HAT_CENTERED,     ///< The hat is centered.
    up = SDL_HAT_UP,                 ///< The hat is directed "north".
    right = SDL_HAT_RIGHT,           ///< The hat is directed "east".
    down = SDL_HAT_DOWN,             ///< The hat is directed "south".
    left = SDL_HAT_LEFT,             ///< The hat is directed "west".
    right_up = SDL_HAT_RIGHTUP,      ///< The hat is directed "north-east".
    right_down = SDL_HAT_RIGHTDOWN,  ///< The hat is directed "south-east".
    left_up = SDL_HAT_LEFTUP,        ///< The hat is directed "north-west".
    left_down = SDL_HAT_LEFTDOWN,    ///< The hat is directed "south-west".
  };

  /**
   * \enum type
   *
   * \brief Mirrors the `SDL_JoystickType` enum.
   *
   * \since 4.2.0
   *
   * \todo Centurion 6: Rename to joystick_type and move out of class.
   *
   * \headerfile joystick.hpp
   */
  enum class type
  {
    unknown = SDL_JOYSTICK_TYPE_UNKNOWN,
    game_controller = SDL_JOYSTICK_TYPE_GAMECONTROLLER,
    wheel = SDL_JOYSTICK_TYPE_WHEEL,
    arcade_stick = SDL_JOYSTICK_TYPE_ARCADE_STICK,
    flight_stick = SDL_JOYSTICK_TYPE_FLIGHT_STICK,
    dance_pad = SDL_JOYSTICK_TYPE_DANCE_PAD,
    guitar = SDL_JOYSTICK_TYPE_GUITAR,
    drum_kit = SDL_JOYSTICK_TYPE_DRUM_KIT,
    arcade_pad = SDL_JOYSTICK_TYPE_ARCADE_PAD,
    throttle = SDL_JOYSTICK_TYPE_THROTTLE
  };

  /**
   * \struct ball_axis_change
   *
   * \brief Represents the difference in a joystick ball axis position.
   *
   * \since 4.2.0
   * \headerfile joystick.hpp
   *
   * \var ball_axis_change::dx
   * Difference in x-axis position since last poll.
   *
   * \var ball_axis_change::dy
   * Difference in y-axis position since last poll.
   */
  struct ball_axis_change final
  {
    int dx;
    int dy;
  };

  /// \name Construction
  /// \{

  /**
   * \brief Creates a joystick instance based on an existing SDL joystick.
   *
   * \note The created instance will only claim ownership of the supplied
   * pointer if the class has owning semantics, i.e. if it's a ``joystick``
   * instance.
   *
   * \param joystick a pointer to the existing joystick.
   *
   * \throws exception if the supplied pointer is null and the joystick is
   * owning.
   */
  explicit basic_joystick(SDL_Joystick* joystick) noexcept(isHandle)
      : m_joystick{joystick}
  {
    if constexpr (isOwner) {
      if (!m_joystick) {
        throw exception{"Cannot create joystick from null pointer!"};
      }
    }
  }

  /**
   * \brief Creates an owning joystick based on a joystick device index.
   *
   * \tparam BB dummy parameter for SFINAE.
   *
   * \param index the device index of the joystick.
   *
   * \throws sdl_error if the joystick couldn't be opened.
   */
  template <typename BB = B, detail::is_owner<BB> = true>
  explicit basic_joystick(const int index = 0)
      : m_joystick{SDL_JoystickOpen(index)}
  {
    if (!m_joystick) {
      throw sdl_error{};
    }
  }

  /**
   * \brief Creates a handle to an owning joystick.
   *
   * \tparam BB dummy parameter for SFINAE.
   *
   * \param owner the owning joystick instance.
   */
  template <typename BB = B, detail::is_handle<BB> = true>
  explicit basic_joystick(const joystick& owner) noexcept
      : m_joystick{owner.get()}
  {}

  /**
   * \brief Returns a handle to the joystick associated with the specified ID.
   *
   * \ingroup input
   *
   * \param id the joystick ID associated with the desired joystick.
   *
   * \return a handle to the joystick associated with the supplied ID, might be
   * empty.
   *
   * \since 5.0.0
   */
  template <typename BB = B, detail::is_handle<BB> = true>
  [[nodiscard]] static auto from_instance_id(const SDL_JoystickID id) noexcept
      -> joystick_handle
  {
    return joystick_handle{SDL_JoystickFromInstanceID(id)};
  }

  /**
   * \brief Returns a handle to the joystick associated with the specified
   * player index.
   *
   * \ingroup input
   *
   * \param playerIndex the player index of the desired joystick.
   *
   * \return a handle to the associated joystick, which might be empty.
   *
   * \since 5.0.0
   */
  template <typename BB = B, detail::is_handle<BB> = true>
  [[nodiscard]] static auto from_player_index(const int playerIndex) noexcept
      -> joystick_handle
  {
    return joystick_handle{SDL_JoystickFromPlayerIndex(playerIndex)};
  }

  /// \} End of construction

  /**
   * \brief Makes the joystick rumble.
   *
   * \details Invoking this method cancels any previous rumble effects. This
   * method has no effect if the joystick doesn't support rumble effects.
   *
   * \param lowFreq the intensity of the low frequency (left) motor.
   * \param highFreq the intensity of the high frequency (right) motor.
   * \param duration the duration of the rumble effect, in milliseconds.
   *
   * \since 4.2.0
   */
  void rumble(const u16 lowFreq,
              const u16 highFreq,
              const milliseconds<u32> duration)
  {
    SDL_JoystickRumble(m_joystick, lowFreq, highFreq, duration.count());
  }

#if SDL_VERSION_ATLEAST(2, 0, 14)

  /**
   * \brief Starts a rumble effect in the joystick's triggers.
   *
   * \details Calls to this function cancels any previously active rumble
   * effect. Furthermore, supplying 0 as intensities will stop the rumble
   * effect.
   *
   * \param left the intensity used by the left rumble motor.
   * \param right the intensity used by the right rumble motor.
   * \param duration the duration of the rumble.
   *
   * \return `true` on success; `false` otherwise.
   *
   * \since 5.2.0
   */
  auto rumble_triggers(const u16 left,
                       const u16 right,
                       const milliseconds<u32> duration) -> bool
  {
    return SDL_JoystickRumbleTriggers(m_joystick,
                                      left,
                                      right,
                                      duration.count()) == 0;
  }

  /**
   * \brief Sets the color of the LED light, if the joystick has one.
   *
   * \param color the color that will be used by the LED, note that the alpha
   * component is ignored.
   *
   * \return `true` on success; `false` otherwise.
   *
   * \since 5.2.0
   */
  auto set_led(const color& color) noexcept -> bool
  {
    return SDL_JoystickSetLED(m_joystick,
                              color.red(),
                              color.green(),
                              color.blue()) == 0;
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  /**
   * \brief Sets the player index to be associated with the joystick.
   *
   * \param index the player index that will be used.
   *
   * \since 4.2.0
   */
  void set_player_index(const int index) noexcept
  {
    SDL_JoystickSetPlayerIndex(m_joystick, index);
  }

  /// \name Virtual joystick API
  /// \{

#if SDL_VERSION_ATLEAST(2, 0, 14)

  /**
   * \brief Attaches a new virtual joystick.
   *
   * \param type the type of the virtual joystick.
   * \param nAxes the number of axes.
   * \param nButtons the number of buttons.
   * \param nHats the number of joystick hats.
   *
   * \return the device index of the virtual joystick; `std::nullopt` if
   * something went wrong.
   *
   * \since 5.2.0
   */
  [[nodiscard]] static auto attach_virtual(const type type,
                                           const int nAxes,
                                           const int nButtons,
                                           const int nHats) noexcept
      -> std::optional<int>
  {
    const auto index =
        SDL_JoystickAttachVirtual(static_cast<SDL_JoystickType>(type),
                                  nAxes,
                                  nButtons,
                                  nHats);
    if (index != -1) {
      return index;
    } else {
      return std::nullopt;
    }
  }

  /**
   * \brief Detaches a virtual joystick.
   *
   * \param index the device index of the virtual joystick.
   *
   * \return `true` on success; `false` otherwise.
   *
   * \since 5.2.0
   */
  static auto detach_virtual(const int index) noexcept -> bool
  {
    return SDL_JoystickDetachVirtual(index) == 0;
  }

  /**
   * \brief Sets the value of a virtual joystick axis.
   *
   * \param axis the axis that will be modified.
   * \param value the new value of the axis.
   *
   * \return `true` on success; `false` otherwise.
   *
   * \since 5.2.0
   */
  auto set_virtual_axis(const int axis, const i16 value) noexcept -> bool
  {
    return SDL_JoystickSetVirtualAxis(m_joystick, axis, value) == 0;
  }

  /**
   * \brief Sets the state of a virtual button.
   *
   * \param button the index of the button that will be set.
   * \param state the new button state.
   *
   * \return `true` on success; `false` otherwise.
   *
   * \since 5.2.0
   */
  auto set_virtual_button(const int button, const button_state state) noexcept
      -> bool
  {
    return SDL_JoystickSetVirtualButton(m_joystick,
                                        button,
                                        static_cast<u8>(state)) == 0;
  }

  /**
   * \brief Sets the state of a virtual joystick hat.
   *
   * \param hat the index of the hat that will be changed.
   * \param state the new state of the virtual joystick hat.
   *
   * \return `true` on success; `false` otherwise.
   *
   * \since 5.2.0
   */
  auto set_virtual_hat(const int hat, const hat_state state) noexcept -> bool
  {
    // clang-format off
    return SDL_JoystickSetVirtualHat(m_joystick, hat, static_cast<u8>(state)) == 0;
    // clang-format on
  }

  /**
   * \brief Indicates whether or not a joystick is virtual.
   *
   * \param index the device index of the joystick that will be queried.
   *
   * \return `true` if the specified joystick is virtual; `false` otherwise.
   *
   * \since 5.2.0
   */
  [[nodiscard]] static auto is_virtual(const int index) noexcept -> bool
  {
    return SDL_JoystickIsVirtual(index) == SDL_TRUE;
  }

#endif  // #if SDL_VERSION_ATLEAST(2, 0, 14)

  /// \} End of virtual joystick API

  /// \name Instance-based queries
  /// \{

  /**
   * \brief Returns the player index of the joystick, if available.
   *
   * \details For XInput controllers this returns the XInput user index.
   *
   * \return the player index associated with the joystick; `std::nullopt` if it
   * can't be obtained
   *
   * \since 4.2.0
   */
  [[nodiscard]] auto player_index() const noexcept -> std::optional<int>
  {
    const auto index = SDL_JoystickGetPlayerIndex(m_joystick);
    if (index == -1) {
      return std::nullopt;
    } else {
      return index;
    }
  }

  /**
   * \brief Returns the type associated with the joystick.
   *
   * \return a `joystick::Type` value that represents the type of the joystick.
   *
   * \since 4.2.0
   */
  [[nodiscard]] auto get_type() const noexcept -> type
  {
    return static_cast<type>(SDL_JoystickGetType(m_joystick));
  }

  /**
   * \brief Returns the USB vendor ID of the joystick.
   *
   * \return the USB vendor ID associated with the joystick; `std::nullopt` if
   * it isn't available.
   *
   * \since 4.2.0
   */
  [[nodiscard]] auto vendor() const noexcept -> std::optional<u16>
  {
    const auto vendor = SDL_JoystickGetVendor(m_joystick);
    if (vendor == 0) {
      return std::nullopt;
    } else {
      return vendor;
    }
  }

  /**
   * \brief Returns the USB product ID of the joystick.
   *
   * \return the USB product ID associated with the joystick; `std::nullopt` if
   * it isn't available.
   *
   * \since 4.2.0
   */
  [[nodiscard]] auto product() const noexcept -> std::optional<u16>
  {
    const auto product = SDL_JoystickGetProduct(m_joystick);
    if (product == 0) {
      return std::nullopt;
    } else {
      return product;
    }
  }

  /**
   * \brief Returns the product version of the joystick, if available.
   *
   * \return the product version of the joystick; `std::nullopt` if it isn't
   * available.
   *
   * \since 4.2.0
   */
  [[nodiscard]] auto product_version() const noexcept -> std::optional<u16>
  {
    const auto version = SDL_JoystickGetProductVersion(m_joystick);
    if (version == 0) {
      return std::nullopt;
    } else {
      return version;
    }
  }

  /**
   * \brief Returns the GUID associated with the joystick.
   *
   * \note The GUID is implementation-dependent.
   *
   * \return the GUID associated with the joystick.
   *
   * \since 4.2.0
   */
  [[nodiscard]] auto guid() noexcept -> SDL_JoystickGUID
  {
    return SDL_JoystickGetGUID(m_joystick);
  }

  /**
   * \brief Returns the name associated with the joystick.
   *
   * \note If no name can be found, this method returns a null string.
   *
   * \return the name of the joystick; a null pointer if no name is found.
   *
   * \since 4.2.0
   */
  [[nodiscard]] auto name() const noexcept -> czstring
  {
    return SDL_JoystickName(m_joystick);
  }

  /**
   * \brief Returns the instance ID associated with the joystick.
   *
   * \return the instance ID associated with the joystick.
   *
   * \since 4.2.0
   */
  [[nodiscard]] auto instance_id() const noexcept -> SDL_JoystickID
  {
    return SDL_JoystickInstanceID(m_joystick);
  }

#if SDL_VERSION_ATLEAST(2, 0, 14)

  /**
   * \brief Returns the serial number associated with the joystick.
   *
   * \return the serial number of the joystick; a null pointer is returned if
   * the serial number isn't available.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto serial() const noexcept -> czstring
  {
    return SDL_JoystickGetSerial(m_joystick);
  }

  /**
   * \brief Indicates whether or not the joystick features a LED light.
   *
   * \return `true` if the joystick features a LED light; `false` otherwise.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto has_led() const noexcept -> bool
  {
    return SDL_JoystickHasLED(m_joystick) == SDL_TRUE;
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  /// \} End of instance-based queries

  /// \name Index-based queries
  /// \{

  /**
   * \brief Returns the player index of the joystick associated with the
   * specified device index.
   *
   * \note This method can be called before any joysticks are opened.
   *
   * \param deviceIndex the device index of the joystick that will be queried.
   *
   * \return the player index of the desired joystick; `std::nullopt` if it
   * can't be obtained.
   *
   * \since 4.2.0
   */
  [[nodiscard]] static auto player_index(const int deviceIndex) noexcept
      -> std::optional<int>
  {
    const auto index = SDL_JoystickGetDevicePlayerIndex(deviceIndex);
    if (index == -1) {
      return std::nullopt;
    } else {
      return index;
    }
  }

  /**
   * \brief Returns the type of the joystick associated with the specified
   * device index.
   *
   * \param deviceIndex the device index of the joystick that will be queried.
   *
   * \return the type of the specified joystick.
   *
   * \since 4.2.0
   */
  [[nodiscard]] static auto get_type(const int deviceIndex) noexcept -> type
  {
    return static_cast<type>(SDL_JoystickGetDeviceType(deviceIndex));
  }

  /**
   * \brief Returns the USB vendor ID for the joystick associated with the
   * specified device index.
   *
   * \param deviceIndex the device index of the joystick that will be queried.
   *
   * \return the USB vendor ID of the desired joystick; `std::nullopt` if it
   * can't be obtained.
   *
   * \since 4.2.0
   */
  [[nodiscard]] static auto vendor(const int deviceIndex) noexcept
      -> std::optional<u16>
  {
    const auto vendor = SDL_JoystickGetDeviceVendor(deviceIndex);
    if (vendor == 0) {
      return std::nullopt;
    } else {
      return vendor;
    }
  }

  /**
   * \brief Returns the USB product ID for the joystick associated with the
   * specified device index.
   *
   * \param deviceIndex the device index of the joystick that will be queried.
   *
   * \return the USB product ID of the desired joystick; `std::nullopt` if it
   * can't be obtained.
   *
   * \since 4.2.0
   */
  [[nodiscard]] static auto product(const int deviceIndex) noexcept
      -> std::optional<u16>
  {
    const auto product = SDL_JoystickGetDeviceProduct(deviceIndex);
    if (product == 0) {
      return std::nullopt;
    } else {
      return product;
    }
  }

  /**
   * \brief Returns the product version for the joystick associated with the
   * specified device index.
   *
   * \param deviceIndex the device index of the joystick that will be queried.
   *
   * \return the product version of the desired joystick; `std::nullopt` if it
   * can't be obtained.
   *
   * \since 4.2.0
   */
  [[nodiscard]] static auto product_version(const int deviceIndex) noexcept
      -> std::optional<u16>
  {
    const auto version = SDL_JoystickGetDeviceProductVersion(deviceIndex);
    if (version == 0) {
      return std::nullopt;
    } else {
      return version;
    }
  }

  /**
   * \brief Returns the GUID for the joystick associated with the specified
   * device index.
   *
   * \note The GUID is implementation-dependent.
   * \note This function can be called before any joysticks are opened.
   *
   * \param deviceIndex refers to the N'th joystick that is currently recognized
   * by SDL.
   *
   * \return the GUID of the joystick associated with the device index.
   *
   * \since 4.2.0
   */
  [[nodiscard]] static auto guid(const int deviceIndex) noexcept
      -> SDL_JoystickGUID
  {
    return SDL_JoystickGetDeviceGUID(deviceIndex);
  }

  /**
   * \brief Returns the associated with the joystick with the specified
   * device index.
   *
   * \param deviceIndex refers to the N'th joystick that is currently recognized
   * by SDL.
   *
   * \return the name associated with the joystick; `nullptr` if no name is
   * found.
   *
   * \since 4.2.0
   */
  [[nodiscard]] static auto name(const int deviceIndex) noexcept -> czstring
  {
    return SDL_JoystickNameForIndex(deviceIndex);
  }

  /**
   * \brief Returns the instance ID for the joystick associated with the
   * specified device index.
   *
   * \param deviceIndex the device index of the joystick that will be queried.
   *
   * \return the instance ID of the desired joystick; `std::nullopt` if it can't
   * be obtained.
   *
   * \since 4.2.0
   */
  [[nodiscard]] static auto instance_id(const int deviceIndex) noexcept
      -> std::optional<SDL_JoystickID>
  {
    const auto id = SDL_JoystickGetDeviceInstanceID(deviceIndex);
    if (id == -1) {
      return std::nullopt;
    } else {
      return id;
    }
  }

  /// \} End of index-based queries

  /**
   * \brief Returns the ball axis change since the last poll.
   *
   * \note Trackballs can only return relative motion since the last call, these
   * motion deltas are placed into the `BallAxisChange` struct.
   *
   * \param ball the ball index to check, start at 0.
   *
   * \return a `JoystickBallAxisChange` instance or `std::nullopt` if something
   * goes wrong.
   *
   * \since 4.2.0
   */
  [[nodiscard]] auto get_ball_axis_change(const int ball) const noexcept
      -> std::optional<ball_axis_change>
  {
    ball_axis_change change{};
    const auto result =
        SDL_JoystickGetBall(m_joystick, ball, &change.dx, &change.dy);
    if (result == 0) {
      return change;
    } else {
      return std::nullopt;
    }
  }

  /**
   * \brief Returns the current position of the specified axis.
   *
   * \details Most modern joysticks let the X-axis be represented by 0
   * and the Y-axis by 1. To account for jitter, it may be necessary to impose
   * some kind of tolerance on the returned value.
   *
   * \note Some joysticks use axes 2 and 3 for extra buttons.
   *
   * \param axis the ID of the axis to query.
   *
   * \return a 16-bit signed integer that represents the position of the
   * specified axis; `std::nullopt` if something goes wrong.
   *
   * \since 4.2.0
   */
  [[nodiscard]] auto axis_pos(const int axis) const noexcept
      -> std::optional<i16>
  {
    const auto result = SDL_JoystickGetAxis(m_joystick, axis);
    if (result == 0) {
      return std::nullopt;
    } else {
      return result;
    }
  }

  /**
   * \brief Returns the initial state of the specified axis on the joystick.
   *
   * \param axis the axis that will be queried. Starts at 0.
   *
   * \return the initial state of the axis; `std::nullopt` if the axis doesn't
   * have an initial state.
   *
   * \since 4.2.0
   */
  [[nodiscard]] auto axis_initial_state(const int axis) const noexcept
      -> std::optional<i16>
  {
    i16 state{};
    const auto hadInitialState =
        SDL_JoystickGetAxisInitialState(m_joystick, axis, &state);
    if (hadInitialState) {
      return state;
    } else {
      return std::nullopt;
    }
  }

  /**
   * \brief Indicates whether or not the joystick is attached to the system.
   *
   * \return `true` if the joystick is attached to the system; false otherwise.
   *
   * \since 4.2.0
   */
  [[nodiscard]] auto is_attached() const noexcept -> bool
  {
    return SDL_JoystickGetAttached(m_joystick);
  }

  /**
   * \brief Returns the amount of hats on the joystick.
   *
   * \return the amount of hats on the joystick.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto hat_count() const noexcept -> int
  {
    return SDL_JoystickNumHats(m_joystick);
  }

  /**
   * \brief Returns the amount of hats on the joystick.
   *
   * \return the amount of hats on the joystick.
   *
   * \deprecated Since 5.2.0, use `hat_count()` instead.
   *
   * \since 4.2.0
   */
  [[nodiscard, deprecated]] auto num_hats() const noexcept -> int
  {
    return hat_count();
  }

  /**
   * \brief Returns the amount of general axis controls on the joystick.
   *
   * \return the amount of general axis controls on the joystick.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto axis_count() const noexcept -> int
  {
    return SDL_JoystickNumAxes(m_joystick);
  }

  /**
   * \brief Returns the amount of general axis controls on the joystick.
   *
   * \return the amount of general axis controls on the joystick.
   *
   * \deprecated Since 5.2.0, use `axis_count()` instead.
   *
   * \since 4.2.0
   */
  [[nodiscard, deprecated]] auto num_axes() const noexcept -> int
  {
    return axis_count();
  }

  /**
   * \brief Returns the amount of trackballs on the joystick.
   *
   * \return the amount of trackballs on the joystick.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto trackball_count() const noexcept -> int
  {
    return SDL_JoystickNumBalls(m_joystick);
  }

  /**
   * \brief Returns the amount of trackballs on the joystick.
   *
   * \return the amount of trackballs on the joystick.
   *
   * \deprecated Since 5.2.0, use `trackball_count()` instead.
   *
   * \since 4.2.0
   */
  [[nodiscard, deprecated]] auto num_trackballs() const noexcept -> int
  {
    return trackball_count();
  }

  /**
   * \brief Returns the amount of buttons on the joystick.
   *
   * \return the amount of buttons on the joystick.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto button_count() const noexcept -> int
  {
    return SDL_JoystickNumButtons(m_joystick);
  }

  /**
   * \brief Returns the amount of buttons on the joystick.
   *
   * \return the amount of buttons on the joystick.
   *
   * \deprecated Since 5.2.0, use `button_count()` instead.
   *
   * \since 4.2.0
   */
  [[nodiscard, deprecated]] auto num_buttons() const noexcept -> int
  {
    return button_count();
  }

  /**
   * \brief Returns the current power level of the joystick.
   *
   * \return a `joystick::Power` value that represents the current power level.
   *
   * \since 4.2.0
   */
  [[nodiscard]] auto get_power() const noexcept -> power
  {
    return static_cast<power>(SDL_JoystickCurrentPowerLevel(m_joystick));
  }

  /**
   * \brief Returns the button state of the button associated with the index.
   *
   * \param button the button index to get the state from, starting at 0.
   *
   * \return the state of the button.
   *
   * \since 4.2.0
   */
  [[nodiscard]] auto get_button_state(const int button) const noexcept
      -> button_state
  {
    return static_cast<button_state>(SDL_JoystickGetButton(m_joystick, button));
  }

  /**
   * \brief Returns the state of a specific joystick hat.
   *
   * \param hat the index of the hat to query, indices start at 0.
   *
   * \return a `HatState` value that represents the current state of the hat.
   *
   * \since 4.2.0
   *
   * \see `joystick::HatState`
   */
  [[nodiscard]] auto get_hat_state(const int hat) const noexcept -> hat_state
  {
    return static_cast<hat_state>(SDL_JoystickGetHat(m_joystick, hat));
  }

  /**
   * \brief Updates the state of all open joysticks.
   *
   * \note This is done automatically by the event loop if any joystick
   * events are enabled.
   *
   * \since 4.2.0
   */
  static void update() noexcept
  {
    SDL_JoystickUpdate();
  }

  /**
   * \brief Locks the access to all joysticks.
   *
   * \details If you are using the joystick API from multiple threads you
   * should use this method to restrict access to the joysticks.
   *
   * \see SDL_LockJoysticks
   * \since 4.2.0
   */
  static void lock() noexcept
  {
    SDL_LockJoysticks();
  }

  /**
   * \brief Unlocks the access to all joysticks.
   *
   * \see SDL_UnlockJoysticks
   * \since 4.2.0
   */
  static void unlock() noexcept
  {
    SDL_UnlockJoysticks();
  }

  /**
   * \brief Specifies whether or not joystick event polling is enabled.
   *
   * \details If joystick event polling is disabled, then you must manually call
   * `joystick::update()` in order to update the joystick state.
   *
   * \note It's recommended to leave joystick event polling enabled.
   *
   * \warning Calling this function might cause all events currently in
   * the event queue to be deleted.
   *
   * \param enabled `true` if joystick event polling should be enabled;
   * `false` otherwise.
   *
   * \see SDL_JoystickEventState(int)
   *
   * \since 4.2.0
   */
  static void set_polling(const bool enabled) noexcept
  {
    SDL_JoystickEventState(enabled ? SDL_ENABLE : SDL_DISABLE);
  }

  /**
   * \brief Indicates whether or not joystick event polling is enabled.
   *
   * \return `true` if joystick event polling is enabled; `false` otherwise.
   *
   * \since 4.2.0
   */
  [[nodiscard]] static auto is_polling() noexcept -> bool
  {
    return SDL_JoystickEventState(SDL_QUERY);
  }

  /**
   * \brief Returns the amount of currently available joysticks.
   *
   * \return the current amount of available joysticks; `std::nullopt` if
   * something goes wrong.
   *
   * \since 5.1.0
   */
  [[nodiscard]] static auto count() noexcept -> std::optional<int>
  {
    const auto result = SDL_NumJoysticks();
    if (result < 0) {
      return std::nullopt;
    } else {
      return result;
    }
  }

  /**
   * \brief Returns the amount of currently available joysticks.
   *
   * \return the current amount of available joysticks; `std::nullopt` if
   * something goes wrong.
   *
   * \deprecated Since 5.1.0, use `count()` instead.
   *
   * \since 4.2.0
   */
  [[nodiscard, deprecated]] static auto amount() noexcept -> std::optional<int>
  {
    return count();
  }

  /**
   * \brief Returns a joystick GUID based on the supplied string.
   *
   * \param str the string used to obtain the GUID, can't be null.
   *
   * \return the obtained GUID.
   *
   * \see `SDL_JoystickGetGUIDFromString`
   * \since 4.2.0
   */
  [[nodiscard]] static auto guid_from_string(not_null<czstring> str) noexcept
      -> SDL_JoystickGUID
  {
    assert(str);
    return SDL_JoystickGetGUIDFromString(str);
  }

  /**
   * \brief Returns the maximum possible value of an axis control on a joystick.
   *
   * \return the maximum possible value of an axis control.
   *
   * \since 4.2.0
   */
  [[nodiscard]] constexpr static auto axis_max() noexcept -> i16
  {
    return SDL_JOYSTICK_AXIS_MAX;
  }

  /**
   * \brief Returns the minimum possible value of an axis control on a joystick.
   *
   * \return the minimum possible value of an axis control.
   *
   * \since 4.2.0
   */
  [[nodiscard]] constexpr static auto axis_min() noexcept -> i16
  {
    return SDL_JOYSTICK_AXIS_MIN;
  }

  /**
   * \brief Indicates whether or not a handle holds a non-null pointer.
   *
   * \tparam U dummy parameter for SFINAE.
   * \return `true` if the handle holds a non-null pointer; `false` otherwise.
   *
   * \since 5.0.0
   */
  template <typename BB = B, detail::is_handle<BB> = true>
  explicit operator bool() const noexcept
  {
    return m_joystick != nullptr;
  }

  /**
   * \brief Returns a pointer to the associated `SDL_Joystick`.
   *
   * \warning Use of this method is not recommended. However, it can be useful
   * since many SDL calls use non-const pointers even when no change will be
   * applied.
   *
   * \warning Don't take ownership of the returned pointer!
   *
   * \return a pointer to the internal `SDL_Joystick`.
   *
   * \since 4.2.0
   */
  [[nodiscard]] auto get() const noexcept -> SDL_Joystick*
  {
    return m_joystick.get();
  }

 private:
  struct deleter final
  {
    void operator()(SDL_Joystick* joystick) noexcept
    {
      if (SDL_JoystickGetAttached(joystick)) {
        SDL_JoystickClose(joystick);
      }
    }
  };
  detail::pointer_manager<B, SDL_Joystick, deleter> m_joystick;
};

/**
 * \brief Indicates whether or not two joystick power values are the same.
 *
 * \param lhs the left-hand side power type.
 * \param rhs the right-hand side power type.
 *
 * \return `true` if the values are the same; `false` otherwise.
 *
 * \since 4.3.0
 */
[[nodiscard]] constexpr auto operator==(
    const joystick::power lhs,
    const SDL_JoystickPowerLevel rhs) noexcept -> bool
{
  return static_cast<SDL_JoystickPowerLevel>(lhs) == rhs;
}

/**
 * \brief Indicates whether or not two joystick power values are the same.
 *
 * \param lhs the left-hand side power type.
 * \param rhs the right-hand side power type.
 *
 * \return `true` if the values are the same; `false` otherwise.
 *
 * \since 4.3.0
 */
[[nodiscard]] constexpr auto operator==(const SDL_JoystickPowerLevel lhs,
                                        const joystick::power rhs) noexcept
    -> bool
{
  return rhs == lhs;
}

/**
 * \brief Indicates whether or not two joystick power values aren't the same.
 *
 * \param lhs the left-hand side power type.
 * \param rhs the right-hand side power type.
 *
 * \return `true` if the values aren't the same; `false` otherwise.
 *
 * \since 4.3.0
 */
[[nodiscard]] constexpr auto operator!=(
    const joystick::power lhs,
    const SDL_JoystickPowerLevel rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/**
 * \brief Indicates whether or not two joystick power values aren't the same.
 *
 * \param lhs the left-hand side power type.
 * \param rhs the right-hand side power type.
 *
 * \return `true` if the values aren't the same; `false` otherwise.
 *
 * \since 4.3.0
 */
[[nodiscard]] constexpr auto operator!=(const SDL_JoystickPowerLevel lhs,
                                        const joystick::power rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/**
 * \brief Indicates whether or not two joystick type values are the same.
 *
 * \param lhs the left-hand side joystick type value.
 * \param rhs the right-hand side joystick type value.
 *
 * \return `true` if the values are the same; `false` otherwise.
 *
 * \since 4.3.0
 */
[[nodiscard]] constexpr auto operator==(const joystick::type lhs,
                                        const SDL_JoystickType rhs) noexcept
    -> bool
{
  return static_cast<SDL_JoystickType>(lhs) == rhs;
}

/**
 * \brief Indicates whether or not two joystick type values are the same.
 *
 * \param lhs the left-hand side joystick type value.
 * \param rhs the right-hand side joystick type value.
 *
 * \return `true` if the values are the same; `false` otherwise.
 *
 * \since 4.3.0
 */
[[nodiscard]] constexpr auto operator==(const SDL_JoystickType lhs,
                                        const joystick::type rhs) noexcept
    -> bool
{
  return rhs == lhs;
}

/**
 * \brief Indicates whether or not two joystick type values aren't the same.
 *
 * \param lhs the left-hand side joystick type value.
 * \param rhs the right-hand side joystick type value.
 *
 * \return `true` if the values aren't the same; `false` otherwise.
 *
 * \since 4.3.0
 */
[[nodiscard]] constexpr auto operator!=(const joystick::type lhs,
                                        const SDL_JoystickType rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/**
 * \brief Indicates whether or not two joystick type values aren't the same.
 *
 * \param lhs the left-hand side joystick type value.
 * \param rhs the right-hand side joystick type value.
 *
 * \return `true` if the values aren't the same; `false` otherwise.
 *
 * \since 4.3.0
 */
[[nodiscard]] constexpr auto operator!=(const SDL_JoystickType lhs,
                                        const joystick::type rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/// \}

}  // namespace cen

#endif  // CENTURION_JOYSTICK_HEADER