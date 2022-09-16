/*
 * MIT License
 *
 * Copyright (c) 2019-2022 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef CENTURION_CONTROLLER_HPP_
#define CENTURION_CONTROLLER_HPP_

#include <SDL.h>

#include <array>        // array
#include <cassert>      // assert
#include <cstddef>      // size_t
#include <optional>     // optional
#include <ostream>      // ostream
#include <string>       // string
#include <string_view>  // string_view

#include "color.hpp"
#include "common.hpp"
#include "detail/owner_handle_api.hpp"
#include "detail/sdl_version_at_least.hpp"
#include "detail/stdlib.hpp"
#include "features.hpp"
#include "input.hpp"
#include "joystick.hpp"
#include "sensor.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen {

enum class controller_button
{
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

#if SDL_VERSION_ATLEAST(2, 0, 14)

  misc1 = SDL_CONTROLLER_BUTTON_MISC1,

  paddle1 = SDL_CONTROLLER_BUTTON_PADDLE1,
  paddle2 = SDL_CONTROLLER_BUTTON_PADDLE2,
  paddle3 = SDL_CONTROLLER_BUTTON_PADDLE3,
  paddle4 = SDL_CONTROLLER_BUTTON_PADDLE4,
  touchpad = SDL_CONTROLLER_BUTTON_TOUCHPAD,

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  max = SDL_CONTROLLER_BUTTON_MAX
};

[[nodiscard]] constexpr auto to_string(const controller_button button) -> std::string_view
{
  switch (button) {
    case controller_button::invalid:
      return "invalid";

    case controller_button::a:
      return "a";

    case controller_button::b:
      return "b";

    case controller_button::x:
      return "x";

    case controller_button::y:
      return "y";

    case controller_button::back:
      return "back";

    case controller_button::guide:
      return "guide";

    case controller_button::start:
      return "start";

    case controller_button::left_stick:
      return "left_stick";

    case controller_button::right_stick:
      return "right_stick";

    case controller_button::left_shoulder:
      return "left_shoulder";

    case controller_button::right_shoulder:
      return "right_shoulder";

    case controller_button::dpad_up:
      return "dpad_up";

    case controller_button::dpad_down:
      return "dpad_down";

    case controller_button::dpad_left:
      return "dpad_left";

    case controller_button::dpad_right:
      return "dpad_right";

#if SDL_VERSION_ATLEAST(2, 0, 14)

    case controller_button::misc1:
      return "misc1";

    case controller_button::paddle1:
      return "paddle1";

    case controller_button::paddle2:
      return "paddle2";

    case controller_button::paddle3:
      return "paddle3";

    case controller_button::paddle4:
      return "paddle4";

    case controller_button::touchpad:
      return "touchpad";

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

    case controller_button::max:
      return "max";

    default:
      throw exception{"Did not recognize controller button!"};
  }
}

inline auto operator<<(std::ostream& stream, const controller_button button) -> std::ostream&
{
  return stream << to_string(button);
}

enum class controller_axis
{
  invalid = SDL_CONTROLLER_AXIS_INVALID,

  left_x = SDL_CONTROLLER_AXIS_LEFTX,
  left_y = SDL_CONTROLLER_AXIS_LEFTY,
  right_x = SDL_CONTROLLER_AXIS_RIGHTX,
  right_y = SDL_CONTROLLER_AXIS_RIGHTY,

  trigger_left = SDL_CONTROLLER_AXIS_TRIGGERLEFT,
  trigger_right = SDL_CONTROLLER_AXIS_TRIGGERRIGHT,

  max = SDL_CONTROLLER_AXIS_MAX
};

[[nodiscard]] constexpr auto to_string(const controller_axis axis) -> std::string_view
{
  switch (axis) {
    case controller_axis::invalid:
      return "invalid";

    case controller_axis::left_x:
      return "left_x";

    case controller_axis::left_y:
      return "left_y";

    case controller_axis::right_x:
      return "right_x";

    case controller_axis::right_y:
      return "right_y";

    case controller_axis::trigger_left:
      return "trigger_left";

    case controller_axis::trigger_right:
      return "trigger_right";

    case controller_axis::max:
      return "max";

    default:
      throw exception{"Did not recognize controller axis!"};
  }
}

inline auto operator<<(std::ostream& stream, const controller_axis axis) -> std::ostream&
{
  return stream << to_string(axis);
}

enum class controller_bind_type
{
  none = SDL_CONTROLLER_BINDTYPE_NONE,
  button = SDL_CONTROLLER_BINDTYPE_BUTTON,
  axis = SDL_CONTROLLER_BINDTYPE_AXIS,
  hat = SDL_CONTROLLER_BINDTYPE_HAT
};

[[nodiscard]] constexpr auto to_string(const controller_bind_type type) -> std::string_view
{
  switch (type) {
    case controller_bind_type::none:
      return "none";

    case controller_bind_type::button:
      return "button";

    case controller_bind_type::axis:
      return "axis";

    case controller_bind_type::hat:
      return "hat";

    default:
      throw exception{"Did not recognize controller bind type!"};
  }
}

inline auto operator<<(std::ostream& stream, const controller_bind_type type) -> std::ostream&
{
  return stream << to_string(type);
}

#if SDL_VERSION_ATLEAST(2, 0, 12)

enum class controller_type
{
  unknown = SDL_CONTROLLER_TYPE_UNKNOWN,

  xbox_360 = SDL_CONTROLLER_TYPE_XBOX360,
  xbox_one = SDL_CONTROLLER_TYPE_XBOXONE,
  ps3 = SDL_CONTROLLER_TYPE_PS3,
  ps4 = SDL_CONTROLLER_TYPE_PS4,
  nintendo_switch_pro = SDL_CONTROLLER_TYPE_NINTENDO_SWITCH_PRO,

#if SDL_VERSION_ATLEAST(2, 0, 14)

  ps5 = SDL_CONTROLLER_TYPE_PS5,
  virt = SDL_CONTROLLER_TYPE_VIRTUAL,

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

#if SDL_VERSION_ATLEAST(2, 0, 16)

  amazon_luna = SDL_CONTROLLER_TYPE_AMAZON_LUNA,
  google_stadia = SDL_CONTROLLER_TYPE_GOOGLE_STADIA

#endif  // SDL_VERSION_ATLEAST(2, 0, 16)
};

[[nodiscard]] constexpr auto to_string(const controller_type type) -> std::string_view
{
  switch (type) {
    case controller_type::unknown:
      return "unknown";

    case controller_type::nintendo_switch_pro:
      return "nintendo_switch_pro";

    case controller_type::xbox_360:
      return "xbox_360";

    case controller_type::xbox_one:
      return "xbox_one";

    case controller_type::ps3:
      return "ps3";

    case controller_type::ps4:
      return "ps4";

#if SDL_VERSION_ATLEAST(2, 0, 14)

    case controller_type::ps5:
      return "ps5";

    case controller_type::virt:
      return "virt";

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

#if SDL_VERSION_ATLEAST(2, 0, 16)

    case controller_type::amazon_luna:
      return "amazon_luna";

    case controller_type::google_stadia:
      return "google_stadia";

#endif  // SDL_VERSION_ATLEAST(2, 0, 16)

    default:
      throw exception{"Did not recognize controller type!"};
  }
}

inline auto operator<<(std::ostream& stream, const controller_type type) -> std::ostream&
{
  return stream << to_string(type);
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

enum class controller_mapping_result
{
  error,    ///< An error occurred.
  updated,  ///< Updated a previous mapping.
  added     ///< Added a new mapping.
};

[[nodiscard]] inline auto to_string(const controller_mapping_result result) -> std::string_view
{
  switch (result) {
    case controller_mapping_result::error:
      return "error";

    case controller_mapping_result::updated:
      return "updated";

    case controller_mapping_result::added:
      return "added";

    default:
      throw exception{"Did not recognize controller mapping result!"};
  }
}

inline auto operator<<(std::ostream& stream, const controller_mapping_result result)
    -> std::ostream&
{
  return stream << to_string(result);
}

struct controller_finger_state final
{
  button_state state{};  ///< Whether the finger is pressed or release.
  float x{};             ///< The current x-coordinate.
  float y{};             ///< The current y-coordinate.
  float pressure{};      ///< The currently applied pressure.
};

template <typename T>
class basic_controller;

using controller = basic_controller<detail::owner_tag>;          ///< An owning controller.
using controller_handle = basic_controller<detail::handle_tag>;  ///< A non-owning controller.

/**
 * Represents a game controller, such as Xbox and Playstation controllers.
 *
 * You may need to load appropriate game controller mappings before you can begin using the
 * game controller API with certain controllers. This can be accomplished using the
 * load_controller_mappings and add_controller_mapping functions.
 *
 * For a community managed database file of game controller mappings, see
 * `https://github.com/gabomdq/SDL_GameControllerDB` (if the link doesn't work for some
 * reason, you should be able to find a copy in the Centurion test resources folder).
 *
 * \see controller
 * \see controller_handle
 * \see add_controller_mapping
 * \see load_controller_mappings
 */
template <typename T>
class basic_controller final
{
 public:
  using mapping_index = int;
  using joystick_index = int;
  using player_index = int;

  // clang-format off

  /**
   * Creates a controller.
   *
   * Ownership of the pointer is claimed if the controller has owning semantics.
   *
   * \param controller a pointer to an SDL controller.
   */
  explicit basic_controller(maybe_owner<SDL_GameController*> controller) noexcept(detail::is_handle<T>)
      : mController{controller}
  {
    if constexpr (detail::is_owner<T>) {
      if (!mController) {
        throw exception{"Cannot create controller from null pointer!"};
      }
    }
  }

  // clang-format on

  /**
   * Opens a game controller.
   *
   * \param index the device index, in the range [0, `basic_joystick::count()`].
   */
  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  explicit basic_controller(const joystick_index index = 0)
      : mController{SDL_GameControllerOpen(index)}
  {
    if (!mController) {
      throw sdl_error{};
    }
  }

  template <typename TT = T, detail::enable_for_handle<TT> = 0>
  explicit basic_controller(const controller& owner) noexcept : mController{owner.get()}
  {}

  /// Creates a controller instance based on an existing joystick.
  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  [[nodiscard]] static auto from_joystick(const SDL_JoystickID id) -> basic_controller
  {
    if (auto* ptr = SDL_GameControllerFromInstanceID(id)) {
      return basic_controller{ptr};
    }
    else {
      throw sdl_error{};
    }
  }

#if SDL_VERSION_ATLEAST(2, 0, 12)

  /// Creates a controller based on a player index.
  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  [[nodiscard]] static auto from_index(const player_index index) -> basic_controller
  {
    if (auto* ptr = SDL_GameControllerFromPlayerIndex(index)) {
      return basic_controller{ptr};
    }
    else {
      throw sdl_error{};
    }
  }

  void set_player_index(const player_index index) noexcept
  {
    SDL_GameControllerSetPlayerIndex(mController, index);
  }

  [[nodiscard]] auto type() const noexcept -> controller_type
  {
    return static_cast<controller_type>(SDL_GameControllerGetType(mController));
  }

  [[nodiscard]] static auto type(const joystick_index index) noexcept -> controller_type
  {
    return static_cast<controller_type>(SDL_GameControllerTypeForIndex(index));
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

#if SDL_VERSION_ATLEAST(2, 24, 0)

  [[nodiscard]] auto path() const noexcept -> const char*
  {
    return SDL_GameControllerPath(mController);
  }

  [[nodiscard]] auto firmware_version() const noexcept -> maybe<uint16>
  {
    const auto version = SDL_GameControllerGetFirmwareVersion(mController);
    if (version != 0) {
      return version;
    }
    else {
      return nothing;
    }
  }

#endif  // SDL_VERSION_ATLEAST(2, 24, 0)

  static void update() { SDL_GameControllerUpdate(); }

  static void set_polling(const bool polling) noexcept
  {
    SDL_GameControllerEventState(polling ? SDL_ENABLE : SDL_DISABLE);
  }

  [[nodiscard]] static auto polling() noexcept -> bool
  {
    return SDL_GameControllerEventState(SDL_QUERY);
  }

  [[nodiscard]] static auto supported(const joystick_index index) noexcept -> bool
  {
    return SDL_IsGameController(index) == SDL_TRUE;
  }

  [[nodiscard]] static auto count() noexcept -> int
  {
    const auto joysticks = SDL_NumJoysticks();

    auto amount = 0;
    for (auto i = 0; i < joysticks; ++i) {
      if (supported(i)) {
        ++amount;
      }
    }

    return amount;
  }

  auto rumble(const uint16 lo,
              const uint16 hi,
              const u32ms duration) noexcept(noexcept(duration.count())) -> result
  {
    return SDL_GameControllerRumble(mController, lo, hi, duration.count()) == 0;
  }

  auto stop_rumble() -> result { return rumble(0, 0, u32ms::zero()); }

#if SDL_VERSION_ATLEAST(2, 0, 14)

  auto rumble_triggers(const uint16 left,
                       const uint16 right,
                       const u32ms duration) noexcept(noexcept(duration.count())) -> result
  {
    return SDL_GameControllerRumbleTriggers(mController, left, right, duration.count()) == 0;
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

#if SDL_VERSION_ATLEAST(2, 0, 18)

  [[nodiscard]] auto has_rumble() const noexcept -> bool
  {
    return SDL_GameControllerHasRumble(mController) == SDL_TRUE;
  }

  [[nodiscard]] auto has_rumble_triggers() const noexcept -> bool
  {
    return SDL_GameControllerHasRumbleTriggers(mController) == SDL_TRUE;
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 18)

  [[nodiscard]] auto state(const controller_button button) const noexcept -> button_state
  {
    const auto state =
        SDL_GameControllerGetButton(mController,
                                    static_cast<SDL_GameControllerButton>(button));
    return static_cast<button_state>(state);
  }

  [[nodiscard]] auto pressed(const controller_button button) const noexcept -> bool
  {
    return state(button) == button_state::pressed;
  }

  [[nodiscard]] auto released(const controller_button button) const noexcept -> bool
  {
    return state(button) == button_state::released;
  }

  [[nodiscard]] static auto button(const char* str) noexcept -> controller_button
  {
    assert(str);
    return static_cast<controller_button>(SDL_GameControllerGetButtonFromString(str));
  }

  [[nodiscard]] static auto button(const std::string& str) noexcept -> controller_button
  {
    return button(str.c_str());
  }

  [[nodiscard]] static auto stringify(const controller_button button) noexcept -> const char*
  {
    return SDL_GameControllerGetStringForButton(static_cast<SDL_GameControllerButton>(button));
  }

#if SDL_VERSION_ATLEAST(2, 0, 14)

  auto set_led(const color& color) noexcept -> result
  {
    return SDL_GameControllerSetLED(mController, color.red(), color.green(), color.blue()) ==
           0;
  }

  [[nodiscard]] auto has_led() const noexcept -> bool
  {
    return SDL_GameControllerHasLED(mController) == SDL_TRUE;
  }

  [[nodiscard]] auto has_button(const controller_button button) const noexcept -> bool
  {
    const auto value = static_cast<SDL_GameControllerButton>(button);
    return SDL_GameControllerHasButton(mController, value) == SDL_TRUE;
  }

  [[nodiscard]] auto has_axis(const controller_axis axis) const noexcept -> bool
  {
    const auto value = static_cast<SDL_GameControllerAxis>(axis);
    return SDL_GameControllerHasAxis(mController, value) == SDL_TRUE;
  }

  auto set_sensor(const sensor_type type, const bool enabled) noexcept -> result
  {
    const auto value = static_cast<SDL_SensorType>(type);
    const auto state = enabled ? SDL_TRUE : SDL_FALSE;
    return SDL_GameControllerSetSensorEnabled(mController, value, state) == 0;
  }

  [[nodiscard]] auto has_sensor(const sensor_type type) const noexcept -> bool
  {
    const auto value = static_cast<SDL_SensorType>(type);
    return SDL_GameControllerHasSensor(mController, value) == SDL_TRUE;
  }

  [[nodiscard]] auto is_sensor_enabled(const sensor_type type) const noexcept -> bool
  {
    const auto value = static_cast<SDL_SensorType>(type);
    return SDL_GameControllerIsSensorEnabled(mController, value) == SDL_TRUE;
  }

  template <usize Size>
  [[nodiscard]] auto sensor_data(const sensor_type type) const noexcept
      -> maybe<std::array<float, Size>>
  {
    std::array<float, Size> array{};
    if (SDL_GameControllerGetSensorData(mController,
                                        static_cast<SDL_SensorType>(type),
                                        array.data(),
                                        isize(array)) != -1) {
      return array;
    }
    else {
      return nothing;
    }
  }

  [[nodiscard]] auto serial() const noexcept -> const char*
  {
    return SDL_GameControllerGetSerial(mController);
  }

  [[nodiscard]] auto touchpad_count() const noexcept -> int
  {
    return SDL_GameControllerGetNumTouchpads(mController);
  }

  [[nodiscard]] auto touchpad_finger_capacity(const int touchpad) const noexcept -> int
  {
    return SDL_GameControllerGetNumTouchpadFingers(mController, touchpad);
  }

  [[nodiscard]] auto touchpad_finger_state(const int touchpad, const int finger) const noexcept
      -> maybe<controller_finger_state>
  {
    controller_finger_state result;
    uint8 state{};

    const auto res = SDL_GameControllerGetTouchpadFinger(mController,
                                                         touchpad,
                                                         finger,
                                                         &state,
                                                         &result.x,
                                                         &result.y,
                                                         &result.pressure);
    result.state = static_cast<button_state>(state);

    if (res != -1) {
      return result;
    }
    else {
      return nothing;
    }
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  [[nodiscard]] auto binding(const controller_button button) noexcept
      -> maybe<SDL_GameControllerButtonBind>
  {
    const auto result =
        SDL_GameControllerGetBindForButton(mController,
                                           static_cast<SDL_GameControllerButton>(button));
    if (result.bindType != SDL_CONTROLLER_BINDTYPE_NONE) {
      return result;
    }
    else {
      return nothing;
    }
  }

  [[nodiscard]] auto axis(const controller_axis axis) const noexcept -> int16
  {
    return SDL_GameControllerGetAxis(mController, static_cast<SDL_GameControllerAxis>(axis));
  }

  [[nodiscard]] static auto axis(const char* str) noexcept -> controller_axis
  {
    assert(str);
    return static_cast<controller_axis>(SDL_GameControllerGetAxisFromString(str));
  }

  [[nodiscard]] static auto axis(const std::string& str) noexcept -> controller_axis
  {
    return axis(str.c_str());
  }

  [[nodiscard]] static auto stringify(const controller_axis axis) noexcept -> const char*
  {
    return SDL_GameControllerGetStringForAxis(static_cast<SDL_GameControllerAxis>(axis));
  }

  [[nodiscard]] auto binding(const controller_axis axis) const
      -> maybe<SDL_GameControllerButtonBind>
  {
    const auto result =
        SDL_GameControllerGetBindForAxis(mController,
                                         static_cast<SDL_GameControllerAxis>(axis));
    if (result.bindType != SDL_CONTROLLER_BINDTYPE_NONE) {
      return result;
    }
    else {
      return nothing;
    }
  }

#if SDL_VERSION_ATLEAST(2, 0, 16)

  auto send_effect(const void* data, const int size) -> result
  {
    return SDL_GameControllerSendEffect(mController, data, size) == 0;
  }

  [[nodiscard]] auto sensor_data_rate(const sensor_type type) const noexcept -> float
  {
    return SDL_GameControllerGetSensorDataRate(mController, static_cast<SDL_SensorType>(type));
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 16)

  [[nodiscard]] auto mapping() const noexcept -> sdl_string
  {
    return sdl_string{SDL_GameControllerMapping(mController)};
  }

  [[nodiscard]] static auto mapping(const joystick_index index) noexcept -> sdl_string
  {
    return sdl_string{SDL_GameControllerMappingForDeviceIndex(index)};
  }

  [[nodiscard]] static auto mapping(const SDL_JoystickGUID guid) noexcept -> sdl_string
  {
    return sdl_string{SDL_GameControllerMappingForGUID(guid)};
  }

  [[nodiscard]] static auto mapping_by_index(const mapping_index index) noexcept -> sdl_string
  {
    return sdl_string{SDL_GameControllerMappingForIndex(index)};
  }

  [[nodiscard]] auto name() const noexcept -> const char*
  {
    return SDL_GameControllerName(mController);
  }

  [[nodiscard]] auto vendor() const noexcept -> maybe<uint16>
  {
    const auto id = SDL_GameControllerGetVendor(mController);
    if (id != 0) {
      return id;
    }
    else {
      return nothing;
    }
  }

  [[nodiscard]] auto product() const noexcept -> maybe<uint16>
  {
    const auto id = SDL_GameControllerGetProduct(mController);
    if (id != 0) {
      return id;
    }
    else {
      return nothing;
    }
  }

  [[nodiscard]] auto product_version() const noexcept -> maybe<uint16>
  {
    const auto id = SDL_GameControllerGetProductVersion(mController);
    if (id != 0) {
      return id;
    }
    else {
      return nothing;
    }
  }

#if SDL_VERSION_ATLEAST(2, 0, 18)

  [[nodiscard]] auto apple_sf_symbols_name(const controller_button button) const noexcept
      -> const char*
  {
    const auto value = static_cast<SDL_GameControllerButton>(button);
    return SDL_GameControllerGetAppleSFSymbolsNameForButton(mController, value);
  }

  [[nodiscard]] auto apple_sf_symbols_name(const controller_axis axis) const noexcept -> const
      char*
  {
    const auto value = static_cast<SDL_GameControllerAxis>(axis);
    return SDL_GameControllerGetAppleSFSymbolsNameForAxis(mController, value);
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 18)

  [[nodiscard]] auto connected() const noexcept -> bool
  {
    return SDL_GameControllerGetAttached(mController) == SDL_TRUE;
  }

  [[nodiscard]] auto index() const noexcept -> maybe<player_index>
  {
    const auto result = SDL_GameControllerGetPlayerIndex(mController);
    if (result != -1) {
      return result;
    }
    else {
      return nothing;
    }
  }

  [[nodiscard]] auto get_joystick() noexcept -> joystick_handle
  {
    return joystick_handle{SDL_GameControllerGetJoystick(mController)};
  }

  [[nodiscard]] auto get() const noexcept -> SDL_GameController* { return mController.get(); }

  /// Indicates whether a joystick handle holds a non-null pointer.
  template <typename TT = T, detail::enable_for_handle<TT> = 0>
  explicit operator bool() const noexcept
  {
    return mController != nullptr;
  }

 private:
  detail::pointer<T, SDL_GameController> mController;
};

inline auto add_controller_mapping(const char* mapping) noexcept -> controller_mapping_result
{
  assert(mapping);
  const auto result = SDL_GameControllerAddMapping(mapping);
  if (result == 1) {
    return controller_mapping_result::added;
  }
  else if (result == 0) {
    return controller_mapping_result::updated;
  }
  else {
    return controller_mapping_result::error;
  }
}

inline auto add_controller_mapping(const std::string& mapping) noexcept
    -> controller_mapping_result
{
  return add_controller_mapping(mapping.c_str());
}

inline auto load_controller_mappings(const char* file) noexcept -> maybe<int>
{
  assert(file);
  const auto result = SDL_GameControllerAddMappingsFromFile(file);
  if (result != -1) {
    return result;
  }
  else {
    return nothing;
  }
}

inline auto load_controller_mappings(const std::string& file) noexcept -> maybe<int>
{
  return load_controller_mappings(file.c_str());
}

[[nodiscard]] inline auto controller_mapping_count() noexcept -> int
{
  return SDL_GameControllerNumMappings();
}

template <typename T>
[[nodiscard]] auto to_string(const basic_controller<T>& controller) -> std::string
{
  const auto* name = controller.name();

  const char* serial{};
  if constexpr (detail::sdl_version_at_least(2, 0, 14)) {
    serial = controller.serial();
  }

#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("controller(data: {}, name: '{}', serial: '{}')",
                     detail::address_of(controller.get()),
                     str_or_na(name),
                     str_or_na(serial));
#else
  return "controller(data: " + detail::address_of(controller.get()) + ", name: '" +
         str_or_na(name) + "', serial: '" + str_or_na(serial) + "')";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

template <typename T>
auto operator<<(std::ostream& stream, const basic_controller<T>& controller) -> std::ostream&
{
  return stream << to_string(controller);
}

}  // namespace cen

#endif  // CENTURION_CONTROLLER_HPP_
