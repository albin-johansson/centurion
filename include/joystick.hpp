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
 * @brief Provides the joystick API.
 *
 * @file joystick.hpp
 * @author Albin Johansson
 * @copyright MIT License
 * @date 2019-2020
 */

#ifndef CENTURION_JOYSTICK_HEADER
#define CENTURION_JOYSTICK_HEADER

#include <SDL_joystick.h>

#include "button_state.hpp"
#include "centurion_api.hpp"
#include "centurion_utils.hpp"

namespace centurion {

/**
 * @typedef JoystickID
 * @brief A type alias for SDL_JoystickID.
 *
 * @deprecated since 4.2.0, prefer `SDL_JoystickID`.
 *
 * @since 4.0.0
 */
using JoystickID = SDL_JoystickID;

/**
 * @class Joystick
 * @brief Represents various types of joysticks.
 *
 * @details `Joystick` instances are movable but not copyable.
 *
 * @todo Cover `SDL_JoystickGetGUIDString`.
 *
 * @headerfile joystick.hpp
 * @since 4.2.0
 *
 * @see `SDL_Joystick`
 */
class Joystick final {
 public:
  /**
   * @enum Power
   * @brief Mirrors the SDL_JoystickPowerLevel enum.
   *
   * @headerfile joystick.hpp
   * @since 4.2.0
   */
  enum class Power {
    Unknown = SDL_JOYSTICK_POWER_UNKNOWN, /**< Unknown power level. */
    Empty = SDL_JOYSTICK_POWER_EMPTY,     /**< Indicates <= 5% power. */
    Low = SDL_JOYSTICK_POWER_LOW,         /**< Indicates <= 20% power. */
    Medium = SDL_JOYSTICK_POWER_MEDIUM,   /**< Indicates <= 70% power. */
    Full = SDL_JOYSTICK_POWER_FULL,       /**< Indicates <= 100% power. */
    Wired = SDL_JOYSTICK_POWER_WIRED,     /**< Wired joystick, no need to
                                           * worry about power. */
    Max = SDL_JOYSTICK_POWER_MAX          /**< Maximum power level. */
  };

  /**
   * @enum HatState
   * @brief Represents the various states of a joystick hat.
   *
   * @headerfile joystick.hpp
   * @since 4.2.0
   */
  enum class HatState {
    Centered = SDL_HAT_CENTERED,   /**< The hat is centered. */
    Up = SDL_HAT_UP,               /**< The hat is directed "north". */
    Right = SDL_HAT_RIGHT,         /**< The hat is directed "east". */
    Down = SDL_HAT_DOWN,           /**< The hat is directed "south". */
    Left = SDL_HAT_LEFT,           /**< The hat is directed "west". */
    RightUp = SDL_HAT_RIGHTUP,     /**< The hat is directed "north-east". */
    RightDown = SDL_HAT_RIGHTDOWN, /**< The hat is directed "south-east". */
    LeftUp = SDL_HAT_LEFTUP,       /**< The hat is directed "north-west". */
    LeftDown = SDL_HAT_LEFTDOWN,   /**< The hat is directed "south-west". */
  };

  /**
   * @enum Type
   * @brief Mirrors the SDL_JoystickType enum.
   *
   * @since 4.2.0
   * @headerfile joystick.hpp
   */
  enum class Type {
    Unknown = SDL_JOYSTICK_TYPE_UNKNOWN,
    GameController = SDL_JOYSTICK_TYPE_GAMECONTROLLER,
    Wheel = SDL_JOYSTICK_TYPE_WHEEL,
    ArcadeStick = SDL_JOYSTICK_TYPE_ARCADE_STICK,
    FlightStick = SDL_JOYSTICK_TYPE_FLIGHT_STICK,
    DancePad = SDL_JOYSTICK_TYPE_DANCE_PAD,
    Guitar = SDL_JOYSTICK_TYPE_GUITAR,
    DrumKit = SDL_JOYSTICK_TYPE_DRUM_KIT,
    ArcadePad = SDL_JOYSTICK_TYPE_ARCADE_PAD,
    Throttle = SDL_JOYSTICK_TYPE_THROTTLE
  };

  /**
   * @struct BallAxisChange
   * @brief Represents the difference in a joystick ball axis position.
   *
   * @since 4.2.0
   * @headerfile joystick.hpp
   *
   * @var BallAxisChange::dx
   * Difference in x-axis position since last poll.
   *
   * @var BallAxisChange::dy
   * Difference in y-axis position since last poll.
   */
  struct BallAxisChange {
    int dx;
    int dy;
  };

  /**
   * @brief Creates a `Joystick` instance based on a device index.
   *
   * @warning The device index is not the same as the instance ID used to
   * identify the joystick in future events.
   *
   * @param deviceIndex refers to the N'th joystick that is currently
   * recognized by SDL.
   *
   * @throws CenturionException if the joystick cannot be created.
   *
   * @since 4.2.0
   */
  CENTURION_API explicit Joystick(int deviceIndex);

  /**
   * @brief Creates a `Joystick` instance based on an existing `SDL_Joystick*`.
   *
   * @pre `joystick` must not be null.
   *
   * @param joystick a pointer to the `SDL_Joystick` that will be claimed.
   *
   * @throws CenturionException if the joystick cannot be created.
   *
   * @since 4.2.0
   */
  CENTURION_API explicit Joystick(Owner<SDL_Joystick*> joystick);

  /**
   * @brief Creates a `Joystick` instance by moving the supplied joystick
   * into this one.
   *
   * @param other the joystick that will be moved.
   *
   * @since 4.2.0
   */
  CENTURION_API Joystick(Joystick&& other) noexcept;

  Joystick(const Joystick&) = delete;

  /**
   * @brief Moves the contents of the supplied joystick into this one.
   *
   * @param other the joystick that will be moved.
   *
   * @return a reference to the joystick that claimed the supplied joystick.
   *
   * @since 4.2.0
   */
  CENTURION_API Joystick& operator=(Joystick&& other) noexcept;

  Joystick& operator=(const Joystick&) = delete;

  CENTURION_API ~Joystick() noexcept;

  /**
   * @brief Creates and returns a unique pointer to a `Joystick` instance.
   *
   * @invariant This method never returns a null pointer.
   *
   * @param deviceIndex refers to the N'th joystick that is currently
   * recognized by SDL.
   *
   * @return a unique pointer to a `Joystick` instance.
   *
   * @throws CenturionException if the joystick cannot be created.
   *
   * @since 4.2.0
   */
  [[nodiscard]] CENTURION_API static UniquePtr<Joystick> unique(
      int deviceIndex);

  /**
   * @brief Creates and returns a unique pointer to a `Joystick` instance.
   *
   * @pre `joystick` must not be null.
   *
   * @invariant This method never returns a null pointer.
   *
   * @param joystick a pointer to the `SDL_Joystick` that will be claimed.
   *
   * @return a unique pointer to a `Joystick` instance.
   *
   * @throws CenturionException if the joystick cannot be created.
   *
   * @since 4.2.0
   */
  [[nodiscard]] CENTURION_API static UniquePtr<Joystick> unique(
      Owner<SDL_Joystick*> joystick);

  /**
   * @brief Creates and returns a shared pointer to a `Joystick` instance.
   *
   * @invariant This method never returns a null pointer.
   *
   * @param deviceIndex refers to the N'th joystick that is currently
   * recognized by SDL.
   *
   * @return a shared pointer to a `Joystick` instance.
   *
   * @throws CenturionException if the joystick cannot be created.
   *
   * @since 4.2.0
   */
  [[nodiscard]] CENTURION_API static SharedPtr<Joystick> shared(
      int deviceIndex);

  /**
   * @brief Creates and returns a shared pointer to a `Joystick` instance.
   *
   * @pre `joystick` must not be null.
   *
   * @invariant This method never returns a null pointer.
   *
   * @param joystick a pointer to the `SDL_Joystick` that will be claimed.
   *
   * @return a shared pointer to a `Joystick` instance.
   *
   * @throws CenturionException if the joystick cannot be created.
   *
   * @since 4.2.0
   */
  [[nodiscard]] CENTURION_API static SharedPtr<Joystick> shared(
      Owner<SDL_Joystick*> joystick);

  /**
   * @brief Updates the state of all open joysticks.
   *
   * @note This is done automatically by the event loop if any joystick
   * events are enabled.
   *
   * @since 4.2.0
   */
  CENTURION_API static void update() noexcept;

  /**
   * @brief Locks the access to all joysticks.
   *
   * @details If you are using the joystick API from multiple threads you
   * should use this method to restrict access to the joysticks.
   *
   * @see SDL_LockJoysticks
   * @since 4.2.0
   */
  CENTURION_API static void lock() noexcept;

  /**
   * @brief Unlocks the access to all joysticks.
   *
   * @see SDL_UnlockJoysticks
   * @since 4.2.0
   */
  CENTURION_API static void unlock() noexcept;

  /**
   * @brief Specifies whether or not joystick event polling is enabled.
   *
   * @details If joystick event polling is disabled, then you must manually call
   * `Joystick::update()` in order to update the joystick state.
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
  CENTURION_API static void set_polling(bool enabled) noexcept;

  /**
   * @brief Indicates whether or not joystick event polling is enabled.
   *
   * @return `true` if joystick event polling is enabled; `false` otherwise.
   *
   * @since 4.2.0
   */
  CENTURION_API static bool polling() noexcept;

  /**
   * @brief Returns a pointer to an `SDL_Joystick` associated with the ID.
   *
   * @param id the joystick ID associated with the desired joystick.
   *
   * @return a pointer to an `SDL_Joystick` instance if there is a joystick
   * associated with the supplied ID; null otherwise.
   *
   * @since 4.2.0
   */
  [[nodiscard]] CENTURION_API static SDL_Joystick* from_instance_id(
      SDL_JoystickID id) noexcept;

  /**
   * @brief Returns a pointer to the joystick associated with the specified
   * player index.
   *
   * @param playerIndex the player index of the desired joystick.
   *
   * @return a pointer to the associated joystick; `nullptr` if there is none.
   *
   * @since 4.2.0
   */
  [[nodiscard]] CENTURION_API static SDL_Joystick* from_player_index(
      int playerIndex) noexcept;

  /**
   * @brief Returns the amount of currently available joysticks.
   *
   * @return the current amount of available joysticks; `nothing` if
   * something goes wrong.
   *
   * @since 4.2.0
   */
  [[nodiscard]] CENTURION_API static Optional<int> amount() noexcept;

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
  [[nodiscard]] CENTURION_API static SDL_JoystickGUID guid(
      int deviceIndex) noexcept;

  /**
   * @brief Returns the player index of the joystick associated with the
   * specified device index.
   *
   * @note This method can be called before any joysticks are opened.
   *
   * @param deviceIndex the device index of the joystick that will be queried.
   *
   * @return the player index of the desired joystick; `nothing` if it can't
   * be obtained.
   *
   * @since 4.2.0
   */
  [[nodiscard]] CENTURION_API static Optional<int> player_index(
      int deviceIndex) noexcept;

  /**
   * @brief Returns the USB vendor ID for the joystick associated with the
   * specified device index.
   *
   * @param deviceIndex the device index of the joystick that will be queried.
   *
   * @return the USB vendor ID of the desired joystick; `nothing` if it can't
   * be obtained.
   *
   * @since 4.2.0
   */
  [[nodiscard]] CENTURION_API static Optional<Uint16> vendor(
      int deviceIndex) noexcept;

  /**
   * @brief Returns the USB product ID for the joystick associated with the
   * specified device index.
   *
   * @param deviceIndex the device index of the joystick that will be queried.
   *
   * @return the USB product ID of the desired joystick; `nothing` if it can't
   * be obtained.
   *
   * @since 4.2.0
   */
  [[nodiscard]] CENTURION_API static Optional<Uint16> product(
      int deviceIndex) noexcept;

  /**
   * @brief Returns the product version for the joystick associated with the
   * specified device index.
   *
   * @param deviceIndex the device index of the joystick that will be queried.
   *
   * @return the product version of the desired joystick; `nothing` if it
   * can't be obtained.
   *
   * @since 4.2.0
   */
  [[nodiscard]] CENTURION_API static Optional<Uint16> product_version(
      int deviceIndex) noexcept;

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
  [[nodiscard]] CENTURION_API static Type type(int deviceIndex) noexcept;

  /**
   * @brief Returns the instance ID for the joystick associated with the
   * specified device index.
   *
   * @param deviceIndex the device index of the joystick that will be queried.
   *
   * @return the instance ID of the desired joystick; `nothing` if it can't
   * be obtained.
   *
   * @since 4.2.0
   */
  [[nodiscard]] CENTURION_API static Optional<SDL_JoystickID> instance_id(
      int deviceIndex) noexcept;

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
  [[nodiscard]] CENTURION_API static CZString name(int deviceIndex) noexcept;

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
  [[nodiscard]] CENTURION_API static SDL_JoystickGUID guid_from_string(
      gsl::not_null<CZString> str) noexcept;

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
  CENTURION_API void rumble(Uint16 lowFreq,
                            Uint16 highFreq,
                            Uint32 duration) noexcept;

  /**
   * @brief Sets the player index to be associated with the joystick.
   *
   * @param index the player index that will be used.
   *
   * @since 4.2.0
   */
  CENTURION_API void set_player_index(int index) noexcept;

  /**
   * @brief Returns the player index of the joystick, if available.
   *
   * @details For XInput controllers this returns the XInput user index.
   *
   * @return the player index associated with the joystick; `nothing` if it
   * can't be obtained
   *
   * @since 4.2.0
   */
  [[nodiscard]] CENTURION_API Optional<int> player_index() const noexcept;

  /**
   * @brief Returns the type associated with the joystick.
   *
   * @return a `Joystick::Type` value that represents the type of the joystick.
   *
   * @since 4.2.0
   */
  [[nodiscard]] CENTURION_API Type type() const noexcept;

  /**
   * @brief Returns the USB vendor ID of the joystick.
   *
   * @return the USB vendor ID associated with the joystick; `nothing` if it
   * isn't available.
   *
   * @since 4.2.0
   */
  [[nodiscard]] CENTURION_API Optional<Uint16> vendor() const noexcept;

  /**
   * @brief Returns the USB product ID of the joystick.
   *
   * @return the USB product ID associated with the joystick; `nothing` if it
   * isn't available.
   *
   * @since 4.2.0
   */
  [[nodiscard]] CENTURION_API Optional<Uint16> product() const noexcept;

  /**
   * @brief Returns the product version of the joystick, if available.
   *
   * @return the product version of the joystick; `nothing` if it isn't
   * available.
   *
   * @since 4.2.0
   */
  [[nodiscard]] CENTURION_API Optional<Uint16> product_version() const noexcept;

  /**
   * @brief Returns the ball axis change since the last poll.
   *
   * @note Trackballs can only return relative motion since the last call, these
   * motion deltas are placed into the `BallAxisChange` struct.
   *
   * @param ball the ball index to check, start at 0.
   *
   * @return a `JoystickBallAxisChange` instance or `nothing` if something goes
   * wrong.
   *
   * @since 4.2.0
   */
  [[nodiscard]] CENTURION_API Optional<BallAxisChange> ball_axis_change(
      int ball) const noexcept;

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
   * specified axis; `nothing` if something goes wrong.
   *
   * @since 4.2.0
   */
  [[nodiscard]] CENTURION_API Optional<Sint16> axis_pos(
      unsigned int axis) const noexcept;

  /**
   * @brief Returns the initial state of the specified axis on the joystick.
   *
   * @param axis the axis that will be queried. Starts at 0.
   *
   * @return the initial state of the axis; `nothing` if the axis doesn't
   * have an initial state.
   *
   * @since 4.2.0
   */
  [[nodiscard]] CENTURION_API Optional<Sint16> axis_initial_state(
      unsigned int axis) const noexcept;

  /**
   * @brief Indicates whether or not the joystick is attached to the system.
   *
   * @return `true` if the joystick is attached to the system; false otherwise.
   *
   * @since 4.2.0
   */
  [[nodiscard]] CENTURION_API bool attached() const noexcept;

  /**
   * @brief Returns the amount of hats on the joystick.
   *
   * @return the amount of hats on the joystick.
   *
   * @since 4.2.0
   */
  [[nodiscard]] CENTURION_API int num_hats() const noexcept;

  /**
   * @brief Returns the amount of general axis controls on the joystick.
   *
   * @return the amount of general axis controls on the joystick.
   *
   * @since 4.2.0
   */
  [[nodiscard]] CENTURION_API int num_axes() const noexcept;

  /**
   * @brief Returns the amount of trackballs on the joystick.
   *
   * @return the amount of trackballs on the joystick.
   *
   * @since 4.2.0
   */
  [[nodiscard]] CENTURION_API int num_trackballs() const noexcept;

  /**
   * @brief Returns the amount of buttons on the joystick.
   *
   * @return the amount of buttons on the joystick.
   *
   * @since 4.2.0
   */
  [[nodiscard]] CENTURION_API int num_buttons() const noexcept;

  /**
   * @brief Returns the instance ID associated with the joystick.
   *
   * @return the instance ID associated with the joystick.
   *
   * @since 4.2.0
   */
  [[nodiscard]] CENTURION_API SDL_JoystickID instance_id() const noexcept;

  /**
   * @brief Returns the GUID associated with the joystick.
   *
   * @note The GUID is implementation-dependent.
   *
   * @return the GUID associated with the joystick.
   *
   * @since 4.2.0
   */
  [[nodiscard]] CENTURION_API SDL_JoystickGUID guid() noexcept;

  /**
   * @brief Returns the name associated with the joystick.
   *
   * @note If no name can be found, this method returns a null string.
   *
   * @return the name of the joystick; `nullptr` if no name is found.
   *
   * @since 4.2.0
   */
  [[nodiscard]] CENTURION_API CZString name() const noexcept;

  /**
   * @brief Returns the current power level of the joystick.
   *
   * @return a `Joystick::Power` value that represents the current power level.
   *
   * @since 4.2.0
   */
  [[nodiscard]] CENTURION_API Power power() const noexcept;

  /**
   * @brief Returns the button state of the button associated with the index.
   *
   * @param button the button index to get the state from, starting at 0.
   *
   * @return the state of the button.
   *
   * @since 4.2.0
   */
  [[nodiscard]] CENTURION_API ButtonState
  button_state(int button) const noexcept;

  /**
   * @brief Returns the state of a specific joystick hat.
   *
   * @param hat the index of the hat to query, indices start at 0.
   *
   * @return a `HatState` value that represents the current state of the hat.
   *
   * @since 4.2.0
   *
   * @see `Joystick::HatState`
   */
  [[nodiscard]] CENTURION_API HatState hat_state(int hat) const noexcept;

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
  [[nodiscard]] SDL_Joystick* get() const noexcept { return m_joystick; }

  /**
   * @brief Returns the maximum possible value of an axis control on a joystick.
   *
   * @return the maximum possible value of an axis control.
   *
   * @since 4.2.0
   */
  [[nodiscard]] static constexpr Sint16 axis_max() noexcept
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
  [[nodiscard]] static constexpr Sint16 axis_min() noexcept
  {
    return SDL_JOYSTICK_AXIS_MIN;
  }

 private:
  SDL_Joystick* m_joystick;

  void move(Joystick&& other) noexcept;

  void destroy() noexcept;
};

/**
 * @brief Indicates whether or not two joystick power values are the same.
 *
 * @param lhs the left-hand side power type.
 * @param rhs the right-hand side power type.
 *
 * @return `true` if the values are the same; `false` otherwise.
 *
 * @since 4.3.0
 */
[[nodiscard]] CENTURION_API bool operator==(
    Joystick::Power lhs,
    SDL_JoystickPowerLevel rhs) noexcept;

/**
 * @brief Indicates whether or not two joystick power values are the same.
 *
 * @param lhs the left-hand side power type.
 * @param rhs the right-hand side power type.
 *
 * @return `true` if the values are the same; `false` otherwise.
 *
 * @since 4.3.0
 */
[[nodiscard]] CENTURION_API bool operator==(SDL_JoystickPowerLevel lhs,
                                            Joystick::Power rhs) noexcept;

/**
 * @brief Indicates whether or not two joystick power values aren't the same.
 *
 * @param lhs the left-hand side power type.
 * @param rhs the right-hand side power type.
 *
 * @return `true` if the values aren't the same; `false` otherwise.
 *
 * @since 4.3.0
 */
[[nodiscard]] CENTURION_API bool operator!=(
    Joystick::Power lhs,
    SDL_JoystickPowerLevel rhs) noexcept;

/**
 * @brief Indicates whether or not two joystick power values aren't the same.
 *
 * @param lhs the left-hand side power type.
 * @param rhs the right-hand side power type.
 *
 * @return `true` if the values aren't the same; `false` otherwise.
 *
 * @since 4.3.0
 */
[[nodiscard]] CENTURION_API bool operator!=(SDL_JoystickPowerLevel lhs,
                                            Joystick::Power rhs) noexcept;

/**
 * @brief Indicates whether or not two joystick type values are the same.
 *
 * @param lhs the left-hand side joystick type value.
 * @param rhs the right-hand side joystick type value.
 *
 * @return `true` if the values are the same; `false` otherwise.
 *
 * @since 4.3.0
 */
[[nodiscard]] CENTURION_API bool operator==(Joystick::Type lhs,
                                            SDL_JoystickType rhs) noexcept;

/**
 * @brief Indicates whether or not two joystick type values are the same.
 *
 * @param lhs the left-hand side joystick type value.
 * @param rhs the right-hand side joystick type value.
 *
 * @return `true` if the values are the same; `false` otherwise.
 *
 * @since 4.3.0
 */
[[nodiscard]] CENTURION_API bool operator==(SDL_JoystickType lhs,
                                            Joystick::Type rhs) noexcept;

/**
 * @brief Indicates whether or not two joystick type values aren't the same.
 *
 * @param lhs the left-hand side joystick type value.
 * @param rhs the right-hand side joystick type value.
 *
 * @return `true` if the values aren't the same; `false` otherwise.
 *
 * @since 4.3.0
 */
[[nodiscard]] CENTURION_API bool operator!=(Joystick::Type lhs,
                                            SDL_JoystickType rhs) noexcept;

/**
 * @brief Indicates whether or not two joystick type values aren't the same.
 *
 * @param lhs the left-hand side joystick type value.
 * @param rhs the right-hand side joystick type value.
 *
 * @return `true` if the values aren't the same; `false` otherwise.
 *
 * @since 4.3.0
 */
[[nodiscard]] CENTURION_API bool operator!=(SDL_JoystickType lhs,
                                            Joystick::Type rhs) noexcept;

}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "joystick.cpp"
#endif  // CENTURION_HEADER_ONLY

#endif  // CENTURION_JOYSTICK_HEADER