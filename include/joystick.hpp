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
 * @file joystick.hpp
 *
 * @ingroup input
 *
 * @brief Provides the `joystick` class.
 *
 * @author Albin Johansson
 *
 * @copyright MIT License
 *
 * @date 2019-2020
 */

#ifndef CENTURION_JOYSTICK_HEADER
#define CENTURION_JOYSTICK_HEADER

#include <SDL_joystick.h>

#include <memory>       // unique_ptr
#include <type_traits>  // enable_if_t, true_type, false_type, is_same_v

#include "button_state.hpp"
#include "centurion_api.hpp"
#include "detail/utils.hpp"
#include "types.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

template <typename T>
using is_joystick_owning =
    std::enable_if_t<std::is_same_v<T, std::true_type>, bool>;

template <typename T>
using is_joystick_handle =
    std::enable_if_t<std::is_same_v<T, std::false_type>, bool>;

/**
 * @class basic_joystick
 *
 * @brief Represents a joystick device.
 *
 * @details The game controller API is built on top of the joystick API, which
 * means that the game controller is higher-level and easier to use.
 *
 * @tparam T `std::true_type` for a owning joysticks; `std::false_type` for
 * non-owning joysticks.
 *
 * @since 4.2.0
 *
 * @see joystick
 * @see joystick_handle
 *
 * @headerfile joystick.hpp
 */
template <typename T>
class basic_joystick final
{
  using owner_t = basic_joystick<std::true_type>;
  using handle_t = basic_joystick<std::false_type>;

 public:
  /**
   * @enum power
   *
   * @brief Mirrors the `SDL_JoystickPowerLevel` enum.
   *
   * @since 4.2.0
   *
   * @headerfile joystick.hpp
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
   * @enum hat_state
   *
   * @brief Represents the various states of a joystick hat.
   *
   * @since 4.2.0
   *
   * @headerfile joystick.hpp
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
   * @enum type
   *
   * @brief Mirrors the `SDL_JoystickType` enum.
   *
   * @since 4.2.0
   *
   * @headerfile joystick.hpp
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
   * @struct ball_axis_change
   *
   * @brief Represents the difference in a joystick ball axis position.
   *
   * @since 4.2.0
   * @headerfile joystick.hpp
   *
   * @var ball_axis_change::dx
   * Difference in x-axis position since last poll.
   *
   * @var ball_axis_change::dy
   * Difference in y-axis position since last poll.
   */
  struct ball_axis_change final
  {
    int dx;
    int dy;
  };

  template <typename U = T, is_joystick_owning<U> = true>
  explicit basic_joystick(int deviceIndex)
      : m_joystick{SDL_JoystickOpen(deviceIndex)}
  {
    if (!m_joystick) {
      throw sdl_error{"Failed to open joystick from device index!"};
    }
  }

  template <typename U = T, is_joystick_handle<U> = true>
  explicit basic_joystick(const owner_t& joystick) noexcept
      : m_joystick{joystick.get()}
  {}

  /**
   * @brief Returns a handle to the joystick associated with the specified ID.
   *
   * @ingroup input
   *
   * @param id the joystick ID associated with the desired joystick.
   *
   * @return a handle to the joystick associated with the supplied ID, might be
   * empty.
   *
   * @since 5.0.0
   */
  template <typename U = T, is_joystick_handle<U> = true>
  [[nodiscard]] static auto from_instance_id(SDL_JoystickID id) noexcept
      -> handle_t
  {
    return handle_t{SDL_JoystickFromInstanceID(id)};
  }

  /**
   * @brief Returns a handle to the joystick associated with the specified
   * player index.
   *
   * @ingroup input
   *
   * @param playerIndex the player index of the desired joystick.
   *
   * @return a handle to the associated joystick, which might be empty.
   *
   * @since 5.0.0
   */
  template <typename U = T, is_joystick_handle<U> = true>
  [[nodiscard]] static auto from_player_index(int playerIndex) noexcept
      -> handle_t
  {
    return handle_t{SDL_JoystickFromPlayerIndex(playerIndex)};
  }

  /**
   * @brief Makes the joystick rumble.
   *
   * @details Invoking this method cancels any previous rumble effects. This
   * method has no effect if the joystick doesn't support rumble effects.
   *
   * @param lowFreq the intensity of the low frequency (left) motor.
   * @param highFreq the intensity of the high frequency (right) motor.
   * @param duration the duration of the rumble effect, in milliseconds.
   *
   * @since 4.2.0
   */
  void rumble(u16 lowFreq, u16 highFreq, milliseconds<u32> duration) noexcept
  {
    SDL_JoystickRumble(get(), lowFreq, highFreq, duration.count());
  }

  /**
   * @brief Sets the player index to be associated with the joystick.
   *
   * @param index the player index that will be used.
   *
   * @since 4.2.0
   */
  void set_player_index(int index) noexcept
  {
    SDL_JoystickSetPlayerIndex(get(), index);
  }

  /**
   * @brief Returns the player index of the joystick, if available.
   *
   * @details For XInput controllers this returns the XInput user index.
   *
   * @return the player index associated with the joystick; `std::nullopt` if it
   * can't be obtained
   *
   * @since 4.2.0
   */
  [[nodiscard]] auto player_index() const noexcept -> std::optional<int>
  {
    const auto index = SDL_JoystickGetPlayerIndex(get());
    if (index == -1) {
      return std::nullopt;
    } else {
      return index;
    }
  }

  /**
   * @brief Returns the player index of the joystick associated with the
   * specified device index.
   *
   * @note This method can be called before any joysticks are opened.
   *
   * @param deviceIndex the device index of the joystick that will be queried.
   *
   * @return the player index of the desired joystick; `std::nullopt` if it
   * can't be obtained.
   *
   * @since 4.2.0
   */
  [[nodiscard]] static auto player_index(int deviceIndex) noexcept
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
   * @brief Returns the type associated with the joystick.
   *
   * @return a `joystick::Type` value that represents the type of the joystick.
   *
   * @since 4.2.0
   */
  [[nodiscard]] auto get_type() const noexcept -> type
  {
    return static_cast<type>(SDL_JoystickGetType(get()));
  }

  /**
   * @brief Returns the type of the joystick associated with the specified
   * device index.
   *
   * @param deviceIndex the device index of the joystick that will be queried.
   *
   * @return the type of the specified joystick.
   *
   * @since 4.2.0
   */
  [[nodiscard]] static auto get_type(int deviceIndex) noexcept -> type
  {
    return static_cast<type>(SDL_JoystickGetDeviceType(deviceIndex));
  }

  /**
   * @brief Returns the USB vendor ID of the joystick.
   *
   * @return the USB vendor ID associated with the joystick; `std::nullopt` if
   * it isn't available.
   *
   * @since 4.2.0
   */
  [[nodiscard]] auto vendor() const noexcept -> std::optional<u16>
  {
    const auto vendor = SDL_JoystickGetVendor(get());
    if (vendor == 0) {
      return std::nullopt;
    } else {
      return vendor;
    }
  }

  /**
   * @brief Returns the USB vendor ID for the joystick associated with the
   * specified device index.
   *
   * @param deviceIndex the device index of the joystick that will be queried.
   *
   * @return the USB vendor ID of the desired joystick; `std::nullopt` if it
   * can't be obtained.
   *
   * @since 4.2.0
   */
  [[nodiscard]] static auto vendor(int deviceIndex) noexcept
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
   * @brief Returns the USB product ID of the joystick.
   *
   * @return the USB product ID associated with the joystick; `std::nullopt` if
   * it isn't available.
   *
   * @since 4.2.0
   */
  [[nodiscard]] auto product() const noexcept -> std::optional<u16>
  {
    const auto product = SDL_JoystickGetProduct(get());
    if (product == 0) {
      return std::nullopt;
    } else {
      return product;
    }
  }

  /**
   * @brief Returns the USB product ID for the joystick associated with the
   * specified device index.
   *
   * @param deviceIndex the device index of the joystick that will be queried.
   *
   * @return the USB product ID of the desired joystick; `std::nullopt` if it
   * can't be obtained.
   *
   * @since 4.2.0
   */
  [[nodiscard]] static auto product(int deviceIndex) noexcept
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
   * @brief Returns the product version of the joystick, if available.
   *
   * @return the product version of the joystick; `std::nullopt` if it isn't
   * available.
   *
   * @since 4.2.0
   */
  [[nodiscard]] auto product_version() const noexcept -> std::optional<u16>
  {
    const auto version = SDL_JoystickGetProductVersion(get());
    if (version == 0) {
      return std::nullopt;
    } else {
      return version;
    }
  }

  /**
   * @brief Returns the product version for the joystick associated with the
   * specified device index.
   *
   * @param deviceIndex the device index of the joystick that will be queried.
   *
   * @return the product version of the desired joystick; `std::nullopt` if it
   * can't be obtained.
   *
   * @since 4.2.0
   */
  [[nodiscard]] static auto product_version(int deviceIndex) noexcept
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
   * @brief Returns the ball axis change since the last poll.
   *
   * @note Trackballs can only return relative motion since the last call, these
   * motion deltas are placed into the `BallAxisChange` struct.
   *
   * @param ball the ball index to check, start at 0.
   *
   * @return a `JoystickBallAxisChange` instance or `std::nullopt` if something
   * goes wrong.
   *
   * @since 4.2.0
   */
  [[nodiscard]] auto get_ball_axis_change(int ball) const noexcept
      -> std::optional<ball_axis_change>
  {
    ball_axis_change change{};
    const auto result =
        SDL_JoystickGetBall(get(), ball, &change.dx, &change.dy);
    if (result == 0) {
      return change;
    } else {
      return std::nullopt;
    }
  }

  /**
   * @brief Returns the current position of the specified axis.
   *
   * @details Most modern joysticks let the X-axis be represented by 0
   * and the Y-axis by 1. To account for jitter, it may be necessary to impose
   * some kind of tolerance on the returned value.
   *
   * @note Some joysticks use axes 2 and 3 for extra buttons.
   *
   * @param axis the ID of the axis to query.
   *
   * @return a 16-bit signed integer that represents the position of the
   * specified axis; `std::nullopt` if something goes wrong.
   *
   * @since 4.2.0
   */
  [[nodiscard]] auto axis_pos(int axis) const noexcept -> std::optional<i16>
  {
    const auto result = SDL_JoystickGetAxis(get(), axis);
    if (result == 0) {
      return std::nullopt;
    } else {
      return result;
    }
  }

  /**
   * @brief Returns the initial state of the specified axis on the joystick.
   *
   * @param axis the axis that will be queried. Starts at 0.
   *
   * @return the initial state of the axis; `std::nullopt` if the axis doesn't
   * have an initial state.
   *
   * @since 4.2.0
   */
  [[nodiscard]] auto axis_initial_state(int axis) const noexcept
      -> std::optional<i16>
  {
    i16 state{};
    const auto hadInitialState =
        SDL_JoystickGetAxisInitialState(get(), axis, &state);
    if (hadInitialState) {
      return state;
    } else {
      return std::nullopt;
    }
  }

  /**
   * @brief Indicates whether or not the joystick is attached to the system.
   *
   * @return `true` if the joystick is attached to the system; false otherwise.
   *
   * @since 4.2.0
   */
  [[nodiscard]] auto is_attached() const noexcept -> bool
  {
    return SDL_JoystickGetAttached(get());
  }

  /**
   * @brief Returns the amount of hats on the joystick.
   *
   * @return the amount of hats on the joystick.
   *
   * @since 4.2.0
   */
  [[nodiscard]] auto num_hats() const noexcept -> int
  {
    return SDL_JoystickNumHats(get());
  }

  /**
   * @brief Returns the amount of general axis controls on the joystick.
   *
   * @return the amount of general axis controls on the joystick.
   *
   * @since 4.2.0
   */
  [[nodiscard]] auto num_axes() const noexcept -> int
  {
    return SDL_JoystickNumAxes(get());
  }

  /**
   * @brief Returns the amount of trackballs on the joystick.
   *
   * @return the amount of trackballs on the joystick.
   *
   * @since 4.2.0
   */
  [[nodiscard]] auto num_trackballs() const noexcept -> int
  {
    return SDL_JoystickNumBalls(get());
  }

  /**
   * @brief Returns the amount of buttons on the joystick.
   *
   * @return the amount of buttons on the joystick.
   *
   * @since 4.2.0
   */
  [[nodiscard]] auto num_buttons() const noexcept -> int
  {
    return SDL_JoystickNumButtons(get());
  }

  /**
   * @brief Returns the instance ID associated with the joystick.
   *
   * @return the instance ID associated with the joystick.
   *
   * @since 4.2.0
   */
  [[nodiscard]] auto instance_id() const noexcept -> SDL_JoystickID
  {
    return SDL_JoystickInstanceID(get());
  }

  /**
   * @brief Returns the instance ID for the joystick associated with the
   * specified device index.
   *
   * @param deviceIndex the device index of the joystick that will be queried.
   *
   * @return the instance ID of the desired joystick; `std::nullopt` if it can't
   * be obtained.
   *
   * @since 4.2.0
   */
  [[nodiscard]] static auto instance_id(int deviceIndex) noexcept
      -> std::optional<SDL_JoystickID>
  {
    const auto id = SDL_JoystickGetDeviceInstanceID(deviceIndex);
    if (id == -1) {
      return std::nullopt;
    } else {
      return id;
    }
  }

  /**
   * @brief Returns the GUID associated with the joystick.
   *
   * @note The GUID is implementation-dependent.
   *
   * @return the GUID associated with the joystick.
   *
   * @since 4.2.0
   */
  [[nodiscard]] auto guid() noexcept -> SDL_JoystickGUID
  {
    return SDL_JoystickGetGUID(get());
  }

  /**
   * @brief Returns the GUID for the joystick associated with the specified
   * device index.
   *
   * @note The GUID is implementation-dependent.
   * @note This function can be called before any joysticks are opened.
   *
   * @param deviceIndex refers to the N'th joystick that is currently recognized
   * by SDL.
   *
   * @return the GUID of the joystick associated with the device index.
   *
   * @since 4.2.0
   */
  [[nodiscard]] static auto guid(int deviceIndex) noexcept -> SDL_JoystickGUID
  {
    return SDL_JoystickGetDeviceGUID(deviceIndex);
  }

  /**
   * @brief Returns the name associated with the joystick.
   *
   * @note If no name can be found, this method returns a null string.
   *
   * @return the name of the joystick; `nullptr` if no name is found.
   *
   * @since 4.2.0
   */
  [[nodiscard]] auto name() const noexcept -> czstring
  {
    return SDL_JoystickName(get());
  }

  /**
   * @brief Returns the associated with the joystick with the specified
   * device index.
   *
   * @param deviceIndex refers to the N'th joystick that is currently recognized
   * by SDL.
   *
   * @return the name associated with the joystick; `nullptr` if no name is
   * found.
   *
   * @since 4.2.0
   */
  [[nodiscard]] static auto name(int deviceIndex) noexcept -> czstring
  {
    return SDL_JoystickNameForIndex(deviceIndex);
  }

  /**
   * @brief Returns the current power level of the joystick.
   *
   * @return a `joystick::Power` value that represents the current power level.
   *
   * @since 4.2.0
   */
  [[nodiscard]] auto get_power() const noexcept -> power
  {
    return static_cast<power>(SDL_JoystickCurrentPowerLevel(get()));
  }

  /**
   * @brief Returns the button state of the button associated with the index.
   *
   * @param button the button index to get the state from, starting at 0.
   *
   * @return the state of the button.
   *
   * @since 4.2.0
   */
  [[nodiscard]] auto get_button_state(int button) const noexcept -> button_state
  {
    return static_cast<button_state>(SDL_JoystickGetButton(get(), button));
  }

  /**
   * @brief Returns the state of a specific joystick hat.
   *
   * @param hat the index of the hat to query, indices start at 0.
   *
   * @return a `HatState` value that represents the current state of the hat.
   *
   * @since 4.2.0
   *
   * @see `joystick::HatState`
   */
  [[nodiscard]] auto get_hat_state(int hat) const noexcept -> hat_state
  {
    return static_cast<hat_state>(SDL_JoystickGetHat(get(), hat));
  }

  /**
   * @brief Updates the state of all open joysticks.
   *
   * @note This is done automatically by the event loop if any joystick
   * events are enabled.
   *
   * @since 4.2.0
   */
  static void update() noexcept
  {
    SDL_JoystickUpdate();
  }

  /**
   * @brief Locks the access to all joysticks.
   *
   * @details If you are using the joystick API from multiple threads you
   * should use this method to restrict access to the joysticks.
   *
   * @see SDL_LockJoysticks
   * @since 4.2.0
   */
  static void lock() noexcept
  {
    SDL_LockJoysticks();
  }

  /**
   * @brief Unlocks the access to all joysticks.
   *
   * @see SDL_UnlockJoysticks
   * @since 4.2.0
   */
  static void unlock() noexcept
  {
    SDL_UnlockJoysticks();
  }

  /**
   * @brief Specifies whether or not joystick event polling is enabled.
   *
   * @details If joystick event polling is disabled, then you must manually call
   * `joystick::update()` in order to update the joystick state.
   *
   * @note It's recommended to leave joystick event polling enabled.
   *
   * @warning Calling this function might cause all events currently in
   * the event queue to be deleted.
   *
   * @param enabled `true` if joystick event polling should be enabled;
   * `false` otherwise.
   *
   * @see SDL_JoystickEventState(int)
   *
   * @since 4.2.0
   */
  static void set_polling(bool enabled) noexcept
  {
    SDL_JoystickEventState(enabled ? SDL_ENABLE : SDL_DISABLE);
  }

  /**
   * @brief Indicates whether or not joystick event polling is enabled.
   *
   * @return `true` if joystick event polling is enabled; `false` otherwise.
   *
   * @since 4.2.0
   */
  static auto is_polling() noexcept -> bool
  {
    return SDL_JoystickEventState(SDL_QUERY);
  }

  /**
   * @brief Returns the amount of currently available joysticks.
   *
   * @return the current amount of available joysticks; `std::nullopt` if
   * something goes wrong.
   *
   * @since 4.2.0
   */
  [[nodiscard]] static auto amount() noexcept -> std::optional<int>
  {
    const auto result = SDL_NumJoysticks();
    if (result < 0) {
      return std::nullopt;
    } else {
      return result;
    }
  }

  /**
   * @brief Returns a joystick GUID based on the supplied string.
   *
   * @param str the string used to obtain the GUID, can't be null.
   *
   * @return the obtained GUID.
   *
   * @see `SDL_JoystickGetGUIDFromString`
   * @since 4.2.0
   */
  [[nodiscard]] static auto guid_from_string(nn_czstring str) noexcept
      -> SDL_JoystickGUID
  {
    return SDL_JoystickGetGUIDFromString(str);
  }

  /**
   * @brief Returns the maximum possible value of an axis control on a joystick.
   *
   * @return the maximum possible value of an axis control.
   *
   * @since 4.2.0
   */
  [[nodiscard]] constexpr static auto axis_max() noexcept -> i16
  {
    return SDL_JOYSTICK_AXIS_MAX;
  }

  /**
   * @brief Returns the minimum possible value of an axis control on a joystick.
   *
   * @return the minimum possible value of an axis control.
   *
   * @since 4.2.0
   */
  [[nodiscard]] constexpr static auto axis_min() noexcept -> i16
  {
    return SDL_JOYSTICK_AXIS_MIN;
  }

  template <typename U = T, is_joystick_handle<U> = true>
  explicit operator bool() const noexcept
  {
    return m_joystick != nullptr;
  }

  /**
   * @brief Returns a pointer to the associated `SDL_Joystick`.
   *
   * @warning Use of this method is not recommended, since it purposefully
   * breaks const-correctness. However, it can be useful since many SDL calls
   * use non-const pointers even when no change will be applied. Don't take
   * ownership of the returned pointer, or bad things will happen.
   *
   * @return a pointer to the internal `SDL_Joystick`.
   *
   * @since 4.2.0
   */
  [[nodiscard]] auto get() const noexcept -> SDL_Joystick*
  {
    if constexpr (is_owning()) {
      return m_joystick.get();
    } else {
      return m_joystick;
    }
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

  using rep_t = std::conditional_t<T::value,
                                   std::unique_ptr<SDL_Joystick, deleter>,
                                   SDL_Joystick*>;
  rep_t m_joystick;

  [[nodiscard]] constexpr static auto is_owning() noexcept -> bool
  {
    return std::is_same_v<T, std::true_type>;
  }

  [[nodiscard]] constexpr static auto is_handle() noexcept -> bool
  {
    return std::is_same_v<T, std::false_type>;
  }

  explicit basic_joystick(SDL_Joystick* joystick) noexcept(is_handle())
      : m_joystick{joystick}
  {
    if constexpr (is_owning()) {
      if (!m_joystick) {
        throw exception{"Cannot create joystick from null pointer!"};
      }
    }
  }
};

/**
 * @typedef joystick
 *
 * @brief Represents an owning joystick.
 *
 * @since 5.0.0
 */
using joystick = basic_joystick<std::true_type>;

/**
 * @typedef joystick_handle
 *
 * @brief Represents a non-owning joystick.
 *
 * @since 5.0.0
 */
using joystick_handle = basic_joystick<std::false_type>;

/**
 * @brief Indicates whether or not two joystick power values are the same.
 *
 * @ingroup input
 *
 * @param lhs the left-hand side power type.
 * @param rhs the right-hand side power type.
 *
 * @return `true` if the values are the same; `false` otherwise.
 *
 * @since 4.3.0
 */
[[nodiscard]] inline constexpr auto operator==(
    joystick::power lhs,
    SDL_JoystickPowerLevel rhs) noexcept -> bool
{
  return static_cast<SDL_JoystickPowerLevel>(lhs) == rhs;
}

/**
 * @brief Indicates whether or not two joystick power values are the same.
 *
 * @ingroup input
 *
 * @param lhs the left-hand side power type.
 * @param rhs the right-hand side power type.
 *
 * @return `true` if the values are the same; `false` otherwise.
 *
 * @since 4.3.0
 */
[[nodiscard]] inline constexpr auto operator==(SDL_JoystickPowerLevel lhs,
                                               joystick::power rhs) noexcept
    -> bool
{
  return rhs == lhs;
}

/**
 * @brief Indicates whether or not two joystick power values aren't the same.
 *
 * @ingroup input
 *
 * @param lhs the left-hand side power type.
 * @param rhs the right-hand side power type.
 *
 * @return `true` if the values aren't the same; `false` otherwise.
 *
 * @since 4.3.0
 */
[[nodiscard]] inline constexpr auto operator!=(
    joystick::power lhs,
    SDL_JoystickPowerLevel rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/**
 * @brief Indicates whether or not two joystick power values aren't the same.
 *
 * @ingroup input
 *
 * @param lhs the left-hand side power type.
 * @param rhs the right-hand side power type.
 *
 * @return `true` if the values aren't the same; `false` otherwise.
 *
 * @since 4.3.0
 */
[[nodiscard]] inline constexpr auto operator!=(SDL_JoystickPowerLevel lhs,
                                               joystick::power rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/**
 * @brief Indicates whether or not two joystick type values are the same.
 *
 * @ingroup input
 *
 * @param lhs the left-hand side joystick type value.
 * @param rhs the right-hand side joystick type value.
 *
 * @return `true` if the values are the same; `false` otherwise.
 *
 * @since 4.3.0
 */
[[nodiscard]] inline constexpr auto operator==(joystick::type lhs,
                                               SDL_JoystickType rhs) noexcept
    -> bool
{
  return static_cast<SDL_JoystickType>(lhs) == rhs;
}

/**
 * @brief Indicates whether or not two joystick type values are the same.
 *
 * @ingroup input
 *
 * @param lhs the left-hand side joystick type value.
 * @param rhs the right-hand side joystick type value.
 *
 * @return `true` if the values are the same; `false` otherwise.
 *
 * @since 4.3.0
 */
[[nodiscard]] inline constexpr auto operator==(SDL_JoystickType lhs,
                                               joystick::type rhs) noexcept
    -> bool
{
  return rhs == lhs;
}

/**
 * @brief Indicates whether or not two joystick type values aren't the same.
 *
 * @ingroup input
 *
 * @param lhs the left-hand side joystick type value.
 * @param rhs the right-hand side joystick type value.
 *
 * @return `true` if the values aren't the same; `false` otherwise.
 *
 * @since 4.3.0
 */
[[nodiscard]] inline constexpr auto operator!=(joystick::type lhs,
                                               SDL_JoystickType rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/**
 * @brief Indicates whether or not two joystick type values aren't the same.
 *
 * @ingroup input
 *
 * @param lhs the left-hand side joystick type value.
 * @param rhs the right-hand side joystick type value.
 *
 * @return `true` if the values aren't the same; `false` otherwise.
 *
 * @since 4.3.0
 */
[[nodiscard]] inline constexpr auto operator!=(SDL_JoystickType lhs,
                                               joystick::type rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

}  // namespace cen

#endif  // CENTURION_JOYSTICK_HEADER