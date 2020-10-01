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
 * @file controller.hpp
 *
 * @brief Provides the game controller API.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

#ifndef CENTURION_GAME_CONTROLLER_HEADER
#define CENTURION_GAME_CONTROLLER_HEADER

#include <SDL.h>

#include <memory>       // unique_ptr
#include <optional>     // optional, nullopt
#include <ostream>      // ostream
#include <string>       // string
#include <type_traits>  // enable_if_t, conditional_t, is_same_v, ...

#include "button_state.hpp"
#include "centurion_api.hpp"
#include "detail/utils.hpp"
#include "joystick_handle.hpp"
#include "sdl_string.hpp"
#include "types.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/// @addtogroup input
/// @{

/**
 * @enum controller_type
 *
 * @brief Mirrors the `SDL_GameControllerType` enum.
 *
 * @see `SDL_GameControllerType`
 *
 * @since 5.0.0
 *
 * @headerfile controller.hpp
 */
enum class controller_type {
  unknown = SDL_CONTROLLER_TYPE_UNKNOWN,   ///< An unknown controller.
  xbox_360 = SDL_CONTROLLER_TYPE_XBOX360,  ///< An Xbox 360 controller.
  xbox_one = SDL_CONTROLLER_TYPE_XBOXONE,  ///< An Xbox One controller.
  ps3 = SDL_CONTROLLER_TYPE_PS3,           ///< A PS3 controller.
  ps4 = SDL_CONTROLLER_TYPE_PS4,           ///< A PS4 controller.
  nintendo_switch_pro =
      SDL_CONTROLLER_TYPE_NINTENDO_SWITCH_PRO  ///< A Nintendo Switch Pro
                                               ///< controller.
};

/**
 * @enum controller_axis
 *
 * @brief Mirrors the values of the `SDL_GameControllerAxis` enum.
 *
 * @see `SDL_GameControllerAxis`
 *
 * @since 4.0.0
 *
 * @headerfile controller.hpp
 */
enum class controller_axis {
  invalid = SDL_CONTROLLER_AXIS_INVALID,
  left_x = SDL_CONTROLLER_AXIS_LEFTX,
  left_y = SDL_CONTROLLER_AXIS_LEFTY,
  right_x = SDL_CONTROLLER_AXIS_RIGHTX,
  right_y = SDL_CONTROLLER_AXIS_RIGHTY,
  trigger_left = SDL_CONTROLLER_AXIS_TRIGGERLEFT,
  trigger_right = SDL_CONTROLLER_AXIS_TRIGGERRIGHT,
  max = SDL_CONTROLLER_AXIS_MAX
};

/**
 * @enum controller_button
 *
 * @brief Mirrors the values of the `SDL_GameControllerButton` enum.
 *
 * @since 4.0.0
 *
 * @headerfile controller.hpp
 */
enum class controller_button {
  invalid = SDL_CONTROLLER_BUTTON_INVALID,
  a = SDL_CONTROLLER_BUTTON_A,
  b = SDL_CONTROLLER_BUTTON_B,
  x = SDL_CONTROLLER_BUTTON_X,
  y = SDL_CONTROLLER_BUTTON_Y,
  back = SDL_CONTROLLER_BUTTON_BACK,
  guide = SDL_CONTROLLER_BUTTON_GUIDE,
  start = SDL_CONTROLLER_BUTTON_START,
  left_stick = SDL_CONTROLLER_BUTTON_LEFTSTICK,
  right_stick = SDL_CONTROLLER_BUTTON_RIGHTSTICK,
  left_shoulder = SDL_CONTROLLER_BUTTON_LEFTSHOULDER,
  right_shoulder = SDL_CONTROLLER_BUTTON_RIGHTSHOULDER,
  dpad_up = SDL_CONTROLLER_BUTTON_DPAD_UP,
  dpad_down = SDL_CONTROLLER_BUTTON_DPAD_DOWN,
  dpad_left = SDL_CONTROLLER_BUTTON_DPAD_LEFT,
  dpad_right = SDL_CONTROLLER_BUTTON_DPAD_RIGHT,
  max = SDL_CONTROLLER_BUTTON_MAX
};

/**
 * @enum controller_bind_type
 *
 * @brief Mirrors the values of the `SDL_GameControllerBindType` enum.
 *
 * @since 5.0.0
 *
 * @headerfile controller.hpp
 */
enum class controller_bind_type {
  none = SDL_CONTROLLER_BINDTYPE_NONE,
  button = SDL_CONTROLLER_BINDTYPE_BUTTON,
  axis = SDL_CONTROLLER_BINDTYPE_AXIS,
  hat = SDL_CONTROLLER_BINDTYPE_HAT
};

/**
 * @class basic_controller
 *
 * @brief Represents a game controller, e.g. an xbox-controller.
 *
 * @tparam T the derived controller class, must provide a getter to obtain a
 * pointer to the associated `SDL_GameController`.
 *
 * @since 5.0.0
 *
 * @headerfile controller.hpp
 */
template <typename T>
class basic_controller
{
 public:
  using mapping_index = int;
  using joystick_index = int;
  using player_index = int;

  /**
   * @brief Triggers a rumble effect.
   *
   * @details Calls to this function cancels any previously active rumble
   * effect. Furthermore, supplying 0 as intensities will stop the rumble
   * effect.
   *
   * @note This function has no effect if rumbling isn't supported by the
   * controller.
   *
   * @param lo the intensity of the low frequency rumble.
   * @param hi the intensity of the high frequency rumble.
   * @param duration the duration of the rumble effect.
   *
   * @since 5.0.0
   */
  void rumble(u16 lo, u16 hi, milliseconds<u32> duration) noexcept
  {
    SDL_GameControllerRumble(ptr(), lo, hi, duration.count());
  }

  /**
   * @brief Stops any currently active rumble effect.
   *
   * @since 5.0.0
   */
  void stop_rumble() noexcept { rumble(0, 0, milliseconds<u32>::zero()); }

  /**
   * @brief Sets the player index associated with the controller.
   *
   * @param index the player index that will be used.
   *
   * @since 5.0.0
   */
  void set_player_index(player_index index) noexcept
  {
    SDL_GameControllerSetPlayerIndex(ptr(), index);
  }

  /**
   * @brief Returns the USB product ID of the controller.
   *
   * @return the USB product ID; `std::nullopt` if the product ID isn't
   * available.
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto product() const noexcept -> std::optional<u16>
  {
    const auto id = SDL_GameControllerGetProduct(ptr());
    if (id != 0) {
      return id;
    } else {
      return std::nullopt;
    }
  }

  /**
   * @brief Returns the USB vendor ID of the controller.
   *
   * @return the USB vendor ID; `std::nullopt` if the vendor ID isn't available.
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto vendor() const noexcept -> std::optional<u16>
  {
    const auto id = SDL_GameControllerGetVendor(ptr());
    if (id != 0) {
      return id;
    } else {
      return std::nullopt;
    }
  }

  /**
   * @brief Returns the product version of the controller.
   *
   * @return the product version; `std::nullopt` if the product version isn't
   * available.
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto product_version() const noexcept -> std::optional<u16>
  {
    const auto id = SDL_GameControllerGetProductVersion(ptr());
    if (id != 0) {
      return id;
    } else {
      return std::nullopt;
    }
  }

  /**
   * @brief Returns the player index associated with the controller.
   *
   * @note If this is an XInput controller, the returned value is the user
   * index.
   *
   * @return the player index associated with the controller; `std::nullopt`
   * if the index isn't available.
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto index() const noexcept -> std::optional<player_index>
  {
    const auto result = SDL_GameControllerGetPlayerIndex(ptr());
    if (result != -1) {
      return result;
    } else {
      return std::nullopt;
    }
  }

  /**
   * @brief Indicates whether or not the game controller is currently connected.
   *
   * @return `true` if the game controller is connected; `false` otherwise.
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto is_connected() const noexcept -> bool
  {
    return static_cast<bool>(SDL_GameControllerGetAttached(ptr()));
  }

  /**
   * @brief Returns the name associated with the game controller.
   *
   * @note This function might return a null pointer if there is no name
   * associated with the game controller.
   *
   * @return the name of the game controller, might be null.
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto name() const noexcept -> czstring
  {
    return SDL_GameControllerName(ptr());
  }

  /**
   * @brief Returns the type of the controller.
   *
   * @return the type of the controller.
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto type() const noexcept -> controller_type
  {
    return static_cast<controller_type>(SDL_GameControllerGetType(ptr()));
  }

  /**
   * @brief Returns the axis associated with the specified string.
   *
   * @note You don't need this function unless you are parsing game controller
   * mappings by yourself.
   *
   * @param str the string that represents a game controller axis, e.g "rightx".
   *
   * @return a game controller axis value.
   *
   * @since 5.0.0
   */
  [[nodiscard]] static auto get_axis(nn_czstring str) noexcept
      -> controller_axis
  {
    return static_cast<controller_axis>(
        SDL_GameControllerGetAxisFromString(str));
  }

  /**
   * @brief Returns the button associated with the specified string.
   *
   * @param str the string that represents a controller button, e.g "a".
   *
   * @return a game controller button value.
   *
   * @since 5.0.0
   */
  [[nodiscard]] static auto get_button(czstring str) noexcept
      -> controller_button
  {
    return static_cast<controller_button>(
        SDL_GameControllerGetButtonFromString(str));
  }

  /**
   * @brief Returns a string representation of a controller axis.
   *
   * @param axis the controller axis that will be converted.
   *
   * @return a string that represents the axis, might be null.
   *
   * @since 5.0.0
   */
  [[nodiscard]] static auto stringify(controller_axis axis) noexcept -> czstring
  {
    return SDL_GameControllerGetStringForAxis(
        static_cast<SDL_GameControllerAxis>(axis));
  }

  /**
   * @brief Returns a string representation of a controller button.
   *
   * @param button the controller button that will be converted.
   *
   * @return a string that represents the button, might be null.
   *
   * @since 5.0.0
   */
  [[nodiscard]] static auto stringify(controller_button button) noexcept
      -> czstring
  {
    return SDL_GameControllerGetStringForButton(
        static_cast<SDL_GameControllerButton>(button));
  }

  /**
   * @brief Returns the bindings for a controller axis.
   *
   * @param axis the axis of the bindings.
   *
   * @return the bindings for a controller axis; `std::nullopt` on failure.
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto get_binding(controller_axis axis) const
      -> std::optional<SDL_GameControllerButtonBind>
  {
    const auto result = SDL_GameControllerGetBindForAxis(
        ptr(), static_cast<SDL_GameControllerAxis>(axis));
    if (result.bindType != SDL_CONTROLLER_BINDTYPE_NONE) {
      return result;
    } else {
      return std::nullopt;
    }
  }

  /**
   * @brief Returns the bindings for a controller button.
   *
   * @param button the button of the bindings.
   *
   * @return the bindings for a controller button; `std::nullopt` on failure.
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto get_binding(controller_button button) noexcept
      -> std::optional<SDL_GameControllerButtonBind>
  {
    const auto result = SDL_GameControllerGetBindForButton(
        ptr(), static_cast<SDL_GameControllerButton>(button));
    if (result.bindType != SDL_CONTROLLER_BINDTYPE_NONE) {
      return result;
    } else {
      return std::nullopt;
    }
  }

  /**
   * @brief Returns the type of the controller associated with the specified
   * joystick index.
   *
   * @param index the joystick index of the desired game controller.
   *
   * @return the type of the game controller associated with the index.
   *
   * @since 5.0.0
   */
  [[nodiscard]] static auto type(joystick_index index) noexcept
      -> controller_type
  {
    return static_cast<controller_type>(SDL_GameControllerTypeForIndex(index));
  }

  /**
   * @brief Returns the state of the specified game controller button.
   *
   * @param button the button that will be checked.
   *
   * @return the current button state of the specified button.
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto get_state(controller_button button) const noexcept
      -> button_state
  {
    const auto state = SDL_GameControllerGetButton(
        ptr(), static_cast<SDL_GameControllerButton>(button));
    return static_cast<button_state>(state);
  }

  /**
   * @brief Indicates if the specified button is pressed.
   *
   * @param button the button that will be checked.
   *
   * @return `true` if the specified button is pressed; `false` otherwise.
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto is_pressed(controller_button button) const noexcept -> bool
  {
    return get_state(button) == button_state::pressed;
  }

  /**
   * @brief Indicates if the specified button is released.
   *
   * @param button the button that will be checked.
   *
   * @return `true` if the specified button is released; `false` otherwise.
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto is_released(controller_button button) const noexcept
      -> bool
  {
    return get_state(button) == button_state::released;
  }

  /**
   * @brief Returns the value of the specified axis.
   *
   * @param axis the controller axis that will be checked.
   *
   * @return the current value of the specified axis.
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto get_axis(controller_axis axis) const noexcept -> i32
  {
    return SDL_GameControllerGetAxis(ptr(),
                                     static_cast<SDL_GameControllerAxis>(axis));
  }

  /**
   * @brief Returns a handle to the associated joystick.
   *
   * @return a handle to the associated joystick.
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto get_joystick() noexcept -> joystick_handle
  {
    return joystick_handle{SDL_GameControllerGetJoystick(ptr())};
  }

  /// @name Mapping functions
  /// @{

  /**
   * @brief Adds a game controller mapping.
   *
   * @param mapping the string that encodes the game controller mapping.
   *
   * @return `true` if a new mapping was added; `false` if a previous mapping
   * was updated.
   *
   * @throws sdl_error if something goes wrong whilst adding the mapping.
   *
   * @since 5.0.0
   */
  static auto add_mapping(nn_czstring mapping) -> bool
  {
    const auto result = SDL_GameControllerAddMapping(mapping);
    if (result == 1) {
      return true;
    } else if (result == 0) {
      return false;
    } else {
      throw sdl_error{"Failed to add game controller mapping"};
    }
  }

  /**
   * @brief Loads a set of game controller mappings from a file.
   *
   * @details A collection of game controller mappings can be found at <a
   * href="https://github.com/gabomdq/SDL_GameControllerDB">here</a>. New
   * mappings for previously known GUIDs will overwrite the previous mappings.
   * Furthermore, mappings for different platforms than the current platform
   * will be ignored.
   *
   * @remarks It's possible to call this function several times to use multiple
   * mapping files.
   *
   * @note The text database is stored entirely in memory during processing.
   *
   * @param file the path of the mapping file.
   *
   * @return the amount of mappings added.
   *
   * @throws sdl_error if the mapping couldn't be added.
   *
   * @since 5.0.0
   */
  static auto load_mappings(nn_czstring file) -> int
  {
    const auto result = SDL_GameControllerAddMappingsFromFile(file);
    if (result != -1) {
      return result;
    } else {
      throw sdl_error{"Failed to add game controller mappings from file"};
    }
  }

  /**
   * @brief Returns the mapping associated with the controller.
   *
   * @return the mapping string associated with the controller.
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto mapping() const noexcept -> sdl_string
  {
    return sdl_string{SDL_GameControllerMapping(ptr())};
  }

  /**
   * @brief Returns the mapping associated with a game controller.
   *
   * @param index the joystick index of the desired game controller.
   *
   * @return the mapping string associated with a controller.
   *
   * @since 5.0.0
   */
  [[nodiscard]] static auto mapping(joystick_index index) noexcept -> sdl_string
  {
    return sdl_string{SDL_GameControllerMappingForDeviceIndex(index)};
  }

  /**
   * @brief Returns the mapping string associated with a joystick GUID.
   *
   * @param guid the GUID to obtain the mapping for.
   *
   * @return the mapping string for a GUID:
   *
   * @since 5.0.0
   */
  [[nodiscard]] static auto mapping(SDL_JoystickGUID guid) noexcept
      -> sdl_string
  {
    return sdl_string{SDL_GameControllerMappingForGUID(guid)};
  }

  /**
   * @brief Returns the mapping at a specific index.
   *
   * @param index the index of the desired mapping.
   *
   * @return the mapping at the specified index.
   *
   * @since 5.0.0
   */
  [[nodiscard]] static auto mapping_by_index(mapping_index index) noexcept
      -> sdl_string
  {
    return sdl_string{SDL_GameControllerMappingForIndex(index)};
  }

  /**
   * @brief Returns the number of installed mappings.
   *
   * @return the amount of installed mappings.
   *
   * @since 5.0.0
   */
  [[nodiscard]] static auto num_mappings() noexcept -> int
  {
    return SDL_GameControllerNumMappings();
  }

  /// @}

  /**
   * @brief Updates the state of all open game controllers.
   *
   * @note This is done automatically if game controller events are enabled.
   *
   * @since 5.0.0
   */
  static void update() { SDL_GameControllerUpdate(); }

  /**
   * @brief Indicates whether or not the specified value is usable as a
   * controller index.
   *
   * @param index the index that will be checked.
   *
   * @return `true` if the supplied index is supported; `false` otherwise.
   *
   * @since 5.0.0
   */
  [[nodiscard]] static auto is_supported(joystick_index index) noexcept -> bool
  {
    return static_cast<bool>(SDL_IsGameController(index));
  }

  /**
   * @brief Sets whether or not game controller event polling is enabled.
   *
   * @details If this property is set to `false`, then you have to call
   * `update` by yourself.
   *
   * @param polling `true` to enable automatic game controller event polling;
   * `false` otherwise.
   *
   * @since 5.0.0
   */
  static void set_polling(bool polling) noexcept
  {
    SDL_GameControllerEventState(polling ? SDL_ENABLE : SDL_DISABLE);
  }

  /**
   * @brief Indicates whether or not game controller event polling is enabled.
   *
   * @return `true` if game controller event polling is enabled; `false`
   * otherwise.
   *
   * @since 5.0.0
   */
  [[nodiscard]] static auto is_polling() noexcept -> bool
  {
    return SDL_GameControllerEventState(SDL_QUERY);
  }

 private:
  [[nodiscard]] auto ptr() const noexcept -> SDL_GameController*
  {
    return static_cast<const T*>(this)->get();
  }
};

/**
 * @class controller
 *
 * @brief Represents an owning game controller.
 *
 * @since 5.0.0
 *
 * @headerfile controller.hpp
 */
class controller final : public basic_controller<controller>
{
 public:
  /**
   * @brief Creates a game controller from an existing SDL game controller.
   *
   * @param controller a pointer to the associated game controller.
   *
   * @throws exception if the supplied pointer is null.
   *
   * @since 5.0.0
   */
  explicit controller(owner<SDL_GameController*> controller)
      : m_controller{controller}
  {
    if (!m_controller) {
      throw exception{"Cannot create controller from null pointer!"};
    }
  }

  /**
   * @brief Attempts to create a game controller.
   *
   * @details The joystick index is the same as the device index passed to the
   * `joystick` constructor. The index passed as an argument refers to the
   * n'th game controller on the system.
   *
   * @note The supplied index is not the value which will identify the
   * controller in controller events. Instead, the joystick's instance id
   * (`SDL_JoystickID`) will be used.
   *
   * @remark This constructor is only available for owning game controllers.
   *
   * @param index the device index, can't be >= than the amount of number of
   * joysticks.
   *
   * @throws sdl_error if the game controller cannot be opened.
   *
   * @since 5.0.0
   */
  explicit controller(int index) : m_controller{SDL_GameControllerOpen(index)}
  {
    if (!m_controller) {
      throw sdl_error{"Failed to open game controller"};
    }
  }

  /**
   * @brief Creates a game controller from an existing joystick ID.
   *
   * @remark This function is only available for owning game controllers.
   *
   * @param id the identifier associated with the joystick to base the game
   * controller on.
   *
   * @return a game controller instance.
   *
   * @throws sdl_error if the game controller cannot be created.
   *
   * @since 5.0.0
   */
  [[nodiscard]] static auto from_joystick(SDL_JoystickID id) -> controller
  {
    if (auto* ptr = SDL_GameControllerFromInstanceID(id)) {
      return controller{ptr};
    } else {
      throw sdl_error{"Failed to create controller from joystick ID"};
    }
  }

  /**
   * @brief Creates and returns a controller based on a player index.
   *
   * @param index the player index of the game controller.
   *
   * @return a game controller associated with the specified player index.
   *
   * @throws sdl_error if the game controller cannot be created.
   *
   * @since 5.0.0
   */
  [[nodiscard]] static auto from_index(player_index index) -> controller
  {
    if (auto* ptr = SDL_GameControllerFromPlayerIndex(index)) {
      return controller{ptr};
    } else {
      throw sdl_error{"Failed to create controller from player index"};
    }
  }

  /**
   * @brief Returns a pointer to the associated SDL game controller.
   *
   * @warning Do *not* claim ownership of the returned pointer.
   *
   * @return a pointer to the associated SDL game controller.
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto get() const noexcept -> SDL_GameController*
  {
    return m_controller.get();
  }

 private:
  struct deleter final
  {
    void operator()(SDL_GameController* controller) noexcept
    {
      SDL_GameControllerClose(controller);
    }
  };
  std::unique_ptr<SDL_GameController, deleter> m_controller;
};

/**
 * @class controller_handle
 *
 * @brief Represents a non-owning handle to a game controller.
 *
 * @see controller
 *
 * @since 5.0.0
 *
 * @headerfile controller.hpp
 */
class controller_handle final : public basic_controller<controller_handle>
{
 public:
  /**
   * @brief Creates a game controller handle.
   *
   * @warning Calling any member functions other than `operator bool()` is
   * undefined behavior if the supplied pointer is null!
   *
   * @param controller a pointer to the associated game controller, can
   * safely be null.
   *
   * @since 5.0.0
   */
  explicit controller_handle(SDL_GameController* controller) noexcept
      : m_controller{controller}
  {}

  /**
   * @brief Creates a handle to an existing controller instance.
   *
   * @param controller the controller that owns the `SDL_GameController`
   * pointer.
   *
   * @since 5.0.0
   */
  explicit controller_handle(controller& controller) noexcept
      : m_controller{controller.get()}
  {}

  /**
   * @brief Indicates whether or not the internal pointer is non-null.
   *
   * @return `true` if the internal pointer is non-null; `false` otherwise.
   *
   * @since 5.0.0
   */
  explicit operator bool() const noexcept { return m_controller; }

  /**
   * @brief Returns a pointer to the associated SDL game controller.
   *
   * @return a pointer to the associated SDL game controller.
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto get() const noexcept -> SDL_GameController*
  {
    return m_controller;
  }

 private:
  SDL_GameController* m_controller;
};

/**
 * @brief Returns a textual representation of a game controller.
 *
 * @param controller the game controller that will be converted.
 *
 * @return a string that represents a game controller.
 *
 * @since 5.0.0
 */
CENTURION_QUERY
auto to_string(const controller& controller) -> std::string;

/**
 * @brief Returns a textual representation of a game controller handle.
 *
 * @param handle the game controller handle that will be converted.
 *
 * @return a string that represents a game controller handle.
 *
 * @since 5.0.0
 */
CENTURION_QUERY
auto to_string(controller_handle handle) -> std::string;

/**
 * @brief Prints a textual representation of a game controller.
 *
 * @param stream the stream that will be used.
 * @param controller the game controller that will be printed.
 *
 * @return the used stream.
 *
 * @since 5.0.0
 */
CENTURION_API
auto operator<<(std::ostream& stream, const controller& controller)
    -> std::ostream&;

/**
 * @brief Prints a textual representation of a game controller handle.
 *
 * @param stream the stream that will be used.
 * @param handle the game controller handle that will be printed.
 *
 * @return the used stream.
 *
 * @since 5.0.0
 */
CENTURION_API
auto operator<<(std::ostream& stream, controller_handle handle)
    -> std::ostream&;

/**
 * @brief Indicates whether or not to controller type values are the same.
 *
 * @param lhs the left-hand side controller type value.
 * @param rhs the right-hand side controller type value.
 *
 * @return `true` if the controller type values are the same; `false` otherwise.
 *
 * @since 5.0.0
 */
[[nodiscard]] inline constexpr auto operator==(
    controller_type lhs,
    SDL_GameControllerType rhs) noexcept -> bool
{
  return static_cast<SDL_GameControllerType>(lhs) == rhs;
}

/**
 * @copydoc operator==(controller_type, SDL_GameControllerType)
 */
[[nodiscard]] inline constexpr auto operator==(SDL_GameControllerType lhs,
                                               controller_type rhs) noexcept
    -> bool
{
  return rhs == lhs;
}

/**
 * @brief Indicates whether or not to controller type values aren't the same.
 *
 * @param lhs the left-hand side controller type value.
 * @param rhs the right-hand side controller type value.
 *
 * @return `true` if the controller type values aren't the same; `false`
 * otherwise.
 *
 * @since 5.0.0
 */
[[nodiscard]] inline constexpr auto operator!=(
    controller_type lhs,
    SDL_GameControllerType rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/**
 * @copydoc operator!=(controller_type, SDL_GameControllerType)
 */
[[nodiscard]] inline constexpr auto operator!=(SDL_GameControllerType lhs,
                                               controller_type rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/**
 * @brief Indicates whether or not two game controller axis values are the same.
 *
 * @param lhs the left-hand-side game controller axis value.
 * @param rhs the right-hand-side game controller axis value.
 *
 * @return `true` if the values are the same; `false` otherwise.
 *
 * @since 4.0.0
 */
[[nodiscard]] inline constexpr auto operator==(
    controller_axis lhs,
    SDL_GameControllerAxis rhs) noexcept -> bool
{
  return static_cast<SDL_GameControllerAxis>(lhs) == rhs;
}

/**
 * @copydoc operator==(controller_axis, SDL_GameControllerAxis)
 */
[[nodiscard]] inline constexpr auto operator==(SDL_GameControllerAxis lhs,
                                               controller_axis rhs) noexcept
    -> bool
{
  return rhs == lhs;
}

/**
 * @brief Indicates whether or not two game controller axis values aren't the
 * same.
 *
 * @param lhs the left-hand-side game controller axis value.
 * @param rhs the right-hand-side game controller axis value.
 *
 * @return `true` if the values aren't the same; `false` otherwise.
 *
 * @since 4.0.0
 */
[[nodiscard]] inline constexpr auto operator!=(
    controller_axis lhs,
    SDL_GameControllerAxis rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/**
 * @copydoc operator!=(controller_axis, SDL_GameControllerAxis)
 */
[[nodiscard]] inline constexpr auto operator!=(SDL_GameControllerAxis lhs,
                                               controller_axis rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/**
 * @brief Indicates whether or not two game controller button values are the
 * same.
 *
 * @param lhs the left-hand side game controller button value.
 * @param rhs the right-hand side game controller button value.
 *
 * @return `true` if the game controller button values are the same; `false`
 * otherwise.
 *
 * @since 4.0.0
 */
[[nodiscard]] inline constexpr auto operator==(
    controller_button lhs,
    SDL_GameControllerButton rhs) noexcept -> bool
{
  return static_cast<SDL_GameControllerButton>(lhs) == rhs;
}

/**
 * @copydoc operator==(controller_button, SDL_GameControllerButton)
 */
[[nodiscard]] inline constexpr auto operator==(SDL_GameControllerButton lhs,
                                               controller_button rhs) noexcept
    -> bool
{
  return rhs == lhs;
}

/**
 * @brief Indicates whether or not two game controller button values aren't the
 * same.
 *
 * @param lhs the left-hand side game controller button value.
 * @param rhs the right-hand side game controller button value.
 *
 * @return `true` if the game controller button values aren't the same; `false`
 * otherwise.
 *
 * @since 4.0.0
 */
[[nodiscard]] inline constexpr auto operator!=(
    controller_button lhs,
    SDL_GameControllerButton rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/**
 * @copydoc operator!=(controller_button, SDL_GameControllerButton)
 */
[[nodiscard]] inline constexpr auto operator!=(SDL_GameControllerButton lhs,
                                               controller_button rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/**
 * @brief Indicates whether or not two controller bind type values are the same.
 *
 * @param lhs the left-hand-side controller bind type value.
 * @param rhs the right-hand-side controller bind type value.
 *
 * @return `true` if the values are the same; `false` otherwise.
 *
 * @since 5.0.0
 */
[[nodiscard]] inline constexpr auto operator==(
    controller_bind_type lhs,
    SDL_GameControllerBindType rhs) noexcept -> bool
{
  return static_cast<SDL_GameControllerBindType>(lhs) == rhs;
}

/**
 * @copydoc operator==(controller_bind_type, SDL_GameControllerBindType)
 */
[[nodiscard]] inline constexpr auto operator==(
    SDL_GameControllerBindType lhs,
    controller_bind_type rhs) noexcept -> bool
{
  return rhs == lhs;
}

/**
 * @brief Indicates whether or not two controller bind type values aren't the
 * same.
 *
 * @param lhs the left-hand-side controller bind type value.
 * @param rhs the right-hand-side controller bind type value.
 *
 * @return `true` if the values aren't the same; `false` otherwise.
 *
 * @since 5.0.0
 */
[[nodiscard]] inline constexpr auto operator!=(
    controller_bind_type lhs,
    SDL_GameControllerBindType rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/**
 * @copydoc operator!=(controller_bind_type, SDL_GameControllerBindType)
 */
[[nodiscard]] inline constexpr auto operator!=(
    SDL_GameControllerBindType lhs,
    controller_bind_type rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// @}

}  // namespace cen

#endif  // CENTURION_GAME_CONTROLLER_HEADER
