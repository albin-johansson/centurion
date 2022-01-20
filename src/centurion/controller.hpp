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

/**
 * \ingroup input
 * \defgroup game-controller Controller
 *
 * \brief Provides the game controller API.
 */

/// \addtogroup game-controller
/// \{

/**
 * \brief Represents various game controller buttons.
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

/// \name Controller button functions
/// \{

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

/// \} End of controller button functions

/**
 * \brief Represents different game controller axes.
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

/// \name Controller axis functions
/// \{

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

/// \} End of controller axis functions

/**
 * \brief Represents different game controller bind types.
 */
enum class controller_bind_type {
  none = SDL_CONTROLLER_BINDTYPE_NONE,
  button = SDL_CONTROLLER_BINDTYPE_BUTTON,
  axis = SDL_CONTROLLER_BINDTYPE_AXIS,
  hat = SDL_CONTROLLER_BINDTYPE_HAT
};

/// \name Controller bind type functions
/// \{

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

/// \} End of controller bind type functions

#if SDL_VERSION_ATLEAST(2, 0, 12)

/**
 * \brief Represents different game controller types.
 */
enum class controller_type {
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

/// \name Controller type functions
/// \{

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

/// \} End of controller type functions

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

/**
 * \brief Represents different results from adding controller mappings.
 */
enum class controller_mapping_result {
  error,    ///< An error occurred.
  updated,  ///< Updated a previous mapping.
  added     ///< Added a new mapping.
};

/// \name Controller mapping result functions
/// \{

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

/// \} End of controller mapping result functions

struct controller_finger_state final {
  button_state state{};  ///< Whether or not the finger is pressed or release.
  float x{};             ///< The current x-coordinate.
  float y{};             ///< The current y-coordinate.
  float pressure{};      ///< The current applied pressure.
};

template <typename T>
class basic_controller;

using controller = basic_controller<detail::owner_tag>;          ///< An owning controller.
using controller_handle = basic_controller<detail::handle_tag>;  ///< A non-owning controller.

/**
 * \brief Represents a game controller, such as Xbox and Playstation controllers.
 *
 * \ownerhandle `controller`/`controller_handle`
 *
 * \details You may need to load appropriate game controller mappings before you can begin
 * using the game controller API with certain controllers. This can be accomplished using
 * the `load_controller_mappings()` and `add_controller_mapping()` functions.
 *
 * \details For a community managed database file of game controller mappings, see
 * `https://github.com/gabomdq/SDL_GameControllerDB` (if the link doesn't work for some
 * reason, you should be able to find a copy in the Centurion test resources folder).
 *
 * \see `controller`
 * \see `controller_handle`
 *
 * \see `add_controller_mapping()`
 * \see `load_controller_mappings()`
 *
 * \see `SDL_GameController`
 */
template <typename T>
class basic_controller final {
 public:
  using mapping_index = int;
  using joystick_index = int;
  using player_index = int;

  /// \name Construction
  /// \{

  // clang-format off

  /**
   * \brief Creates a controller.
   *
   * \details Ownership of the pointer is claimed if the controller has owning semantics.
   *
   * \param controller a pointer to the SDL controller.
   *
   * \throws exception if the pointer is null and the controller has owning semantics.
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
   * \brief Opens a game controller.
   *
   * \param index the device index, in the range [0, `basic_joystick::count()`].
   *
   * \throws sdl_error if the controller cannot be opened.
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

  /// \} End of construction

  /// \name Factory functions
  /// \{

  /**
   * \brief Creates a controller instance based on an existing joystick.
   *
   * \param id the identifier of the joystick to wrap.
   *
   * \return the created controller.
   *
   * \throws sdl_error if the controller cannot be created.
   */
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

  /**
   * \brief Creates a controller based on a player index.
   *
   * \param index the player index of the game controller.
   *
   * \return the created controller.
   *
   * \throws sdl_error if the game controller cannot be created.
   */
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

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

  /// \} End of factory functions

  /// \name Rumble functions
  /// \{

  /**
   * \brief Starts a rumble effect.
   *
   * \details This function cancels any previously active rumble effect. Furthermore, supplying
   * 0 as the intensities will stop the rumble effect.
   *
   * \note This function has no effect if rumbling isn't supported by the controller.
   *
   * \param lo the intensity of the low frequency motor.
   * \param hi the intensity of the high frequency motor.
   * \param duration the duration of the rumble effect.
   *
   * \return `success` if the rumble was successful; `failure` otherwise.
   */
  auto rumble(const uint16 lo,
              const uint16 hi,
              const u32ms duration) noexcept(noexcept(duration.count())) -> result
  {
    return SDL_GameControllerRumble(mController, lo, hi, duration.count()) == 0;
  }

  /**
   * \brief Stops any currently playing rumble effect.
   *
   * \return `success` if the operation succeeded; `failure` otherwise.
   */
  auto stop_rumble() -> result { return rumble(0, 0, u32ms::zero()); }

#if SDL_VERSION_ATLEAST(2, 0, 14)

  /**
   * \brief Starts a rumble effect in the controller's triggers.
   *
   * \details This function cancels any previously active rumble effect. Furthermore, supplying
   * 0 as the intensities will stop the rumble effect.
   *
   * \note This function has no effect if rumbling isn't supported by the controller.
   *
   * \param left the intensity of the left trigger motor.
   * \param right the intensity of the right trigger motor.
   * \param duration the duration of the rumble effect.
   *
   * \return `success` if the rumble was successful; `failure` otherwise.
   */
  auto rumble_triggers(const uint16 left,
                       const uint16 right,
                       const u32ms duration) noexcept(noexcept(duration.count())) -> result
  {
    return SDL_GameControllerRumbleTriggers(mController, left, right, duration.count()) == 0;
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  /// \} End of rumble functions

  /// \name Button functions
  /// \{

  /**
   * \brief Returns the state of a specific controller button.
   *
   * \param button the button to query.
   *
   * \return the button state.
   */
  [[nodiscard]] auto state(const controller_button button) const noexcept -> button_state
  {
    const auto state =
        SDL_GameControllerGetButton(mController,
                                    static_cast<SDL_GameControllerButton>(button));
    return static_cast<button_state>(state);
  }

  /**
   * \brief Indicates if a specific button is pressed.
   *
   * \param button the button to query.
   *
   * \return `true` if the button is pressed; `false` otherwise.
   */
  [[nodiscard]] auto pressed(const controller_button button) const noexcept -> bool
  {
    return state(button) == button_state::pressed;
  }

  /**
   * \brief Indicates if a specific button is released.
   *
   * \param button the button to query.
   *
   * \return `true` if the button is released; `false` otherwise.
   */
  [[nodiscard]] auto released(const controller_button button) const noexcept -> bool
  {
    return state(button) == button_state::released;
  }

  /**
   * \brief Returns the button associated with a specific string.
   *
   * \param str the string that represents a button, e.g "a".
   *
   * \return a game controller button.
   */
  [[nodiscard]] static auto button(const char* str) noexcept -> controller_button
  {
    assert(str);
    return static_cast<controller_button>(SDL_GameControllerGetButtonFromString(str));
  }

  /// \copydoc button()
  [[nodiscard]] static auto button(const std::string& str) noexcept -> controller_button
  {
    return button(str.c_str());
  }

  /**
   * \brief Returns a string representation of a controller button.
   *
   * \param button the controller button to convert.
   *
   * \return the button string representation, might be null.
   */
  [[nodiscard]] static auto stringify(const controller_button button) noexcept -> const char*
  {
    return SDL_GameControllerGetStringForButton(static_cast<SDL_GameControllerButton>(button));
  }

#if SDL_VERSION_ATLEAST(2, 0, 14)

  /**
   * \brief Indicates whether the controller has a specific button.
   *
   * \param button the button to look for.
   *
   * \return `true` if the controller has the button; `false` otherwise.
   */
  [[nodiscard]] auto has_button(const controller_button button) const noexcept -> bool
  {
    const auto value = static_cast<SDL_GameControllerButton>(button);
    return SDL_GameControllerHasButton(mController, value) == SDL_TRUE;
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  /**
   * \brief Returns the binding for a controller button.
   *
   * \param button the button to query.
   *
   * \return the controller button binding; an empty optional is returned upon failure.
   */
  [[nodiscard]] auto binding(const controller_button button) noexcept
      -> std::optional<SDL_GameControllerButtonBind>
  {
    const auto result =
        SDL_GameControllerGetBindForButton(mController,
                                           static_cast<SDL_GameControllerButton>(button));
    if (result.bindType != SDL_CONTROLLER_BINDTYPE_NONE) {
      return result;
    }
    else {
      return std::nullopt;
    }
  }

  /// \} End of button functions

  /// \name Axis functions
  /// \{

  /**
   * \brief Returns the value of a specific axis.
   *
   * \param axis the axis to query.
   *
   * \return the axis value.
   */
  [[nodiscard]] auto axis(const controller_axis axis) const noexcept -> int16
  {
    return SDL_GameControllerGetAxis(mController, static_cast<SDL_GameControllerAxis>(axis));
  }

  /**
   * \brief Returns the axis associated with the specified string.
   *
   * \note You don't need this function unless you are parsing game controller mappings by
   * yourself.
   *
   * \param str the string that represents a game controller axis, e.g "rightx".
   *
   * \return a game controller axis value.
   */
  [[nodiscard]] static auto axis(const char* str) noexcept -> controller_axis
  {
    assert(str);
    return static_cast<controller_axis>(SDL_GameControllerGetAxisFromString(str));
  }

  /// \copydoc axis(const char*)
  [[nodiscard]] static auto axis(const std::string& str) noexcept -> controller_axis
  {
    return axis(str.c_str());
  }

  /**
   * \brief Returns a string representation of a controller axis.
   *
   * \param axis the controller axis to convert.
   *
   * \return the axis string representation, might be null.
   */
  [[nodiscard]] static auto stringify(const controller_axis axis) noexcept -> const char*
  {
    return SDL_GameControllerGetStringForAxis(static_cast<SDL_GameControllerAxis>(axis));
  }

#if SDL_VERSION_ATLEAST(2, 0, 14)

  /**
   * \brief Indicates whether the controller has a specific axis.
   *
   * \return `true` if the controller has the axis; `false` otherwise.
   */
  [[nodiscard]] auto has_axis(const controller_axis axis) const noexcept -> bool
  {
    const auto value = static_cast<SDL_GameControllerAxis>(axis);
    return SDL_GameControllerHasAxis(mController, value) == SDL_TRUE;
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  /**
   * \brief Returns the binding for a controller axis.
   *
   * \param axis the axis to query.
   *
   * \return the controller axis binding; an empty optional is returned upon failure.
   */
  [[nodiscard]] auto binding(const controller_axis axis) const
      -> std::optional<SDL_GameControllerButtonBind>
  {
    const auto result =
        SDL_GameControllerGetBindForAxis(mController,
                                         static_cast<SDL_GameControllerAxis>(axis));
    if (result.bindType != SDL_CONTROLLER_BINDTYPE_NONE) {
      return result;
    }
    else {
      return std::nullopt;
    }
  }

  /// \} End of axis functions

  /// \name Sensor functions
  /// \{

#if SDL_VERSION_ATLEAST(2, 0, 14)

  /**
   * \brief Sets whether data reporting is enabled for a sensor.
   *
   * \param type the type of the sensor that will be changed.
   * \param enabled `true` if data reporting should be enabled; `false` otherwise.
   *
   * \return `success` if the sensor was updated; `failure` otherwise.
   */
  auto set_sensor(const sensor_type type, const bool enabled) noexcept -> result
  {
    const auto value = static_cast<SDL_SensorType>(type);
    const auto state = enabled ? SDL_TRUE : SDL_FALSE;
    return SDL_GameControllerSetSensorEnabled(mController, value, state) == 0;
  }

  /**
   * \brief Indicates whether the controller has a specific sensor.
   *
   * \param type the sensor to look for.
   *
   * \return `true` if the controller has the sensor; `false` otherwise.
   */
  [[nodiscard]] auto has_sensor(const sensor_type type) const noexcept -> bool
  {
    const auto value = static_cast<SDL_SensorType>(type);
    return SDL_GameControllerHasSensor(mController, value) == SDL_TRUE;
  }

  /**
   * \brief Indicates whether data reporting is enabled for a sensor.
   *
   * \param type the sensor that will be queried.
   *
   * \return `true` if data reporting is enabled for the sensor; `false` otherwise.
   */
  [[nodiscard]] auto is_sensor_enabled(const sensor_type type) const noexcept -> bool
  {
    const auto value = static_cast<SDL_SensorType>(type);
    return SDL_GameControllerIsSensorEnabled(mController, value) == SDL_TRUE;
  }

  /**
   * \brief Returns the state of the specified sensor.
   *
   * \tparam Size the amount of data elements.
   *
   * \param type the type of the sensor that will be queried.
   *
   * \return the sensor data; an empty optional is returned upon failure.
   */
  template <std::size_t Size>
  [[nodiscard]] auto sensor_data(const sensor_type type) const noexcept
      -> std::optional<std::array<float, Size>>
  {
    std::array<float, Size> array{};
    if (SDL_GameControllerGetSensorData(mController,
                                        static_cast<SDL_SensorType>(type),
                                        array.data(),
                                        isize(array)) != -1) {
      return array;
    }
    else {
      return std::nullopt;
    }
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

#if SDL_VERSION_ATLEAST(2, 0, 16)

  /**
   * \brief Returns the data rate of a controller sensor.
   *
   * \details The data rate is the number of supported events per second.
   *
   * \param type the sensor that will be queried.
   *
   * \return the data rate; zero if the data rate is unavailable.
   */
  [[nodiscard]] auto sensor_data_rate(const sensor_type type) const noexcept -> float
  {
    return SDL_GameControllerGetSensorDataRate(mController, static_cast<SDL_SensorType>(type));
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 16)

  /// \} End of sensor functions

  /// \name LED functions
  /// \{

#if SDL_VERSION_ATLEAST(2, 0, 14)

  /**
   * \brief Sets the color of the associated LED light.
   *
   * \param color the new LED color.
   *
   * \return `success` if the LED color was updated; `failure` otherwise.
   */
  auto set_led(const color& color) noexcept -> result
  {
    return SDL_GameControllerSetLED(mController, color.red(), color.green(), color.blue()) ==
           0;
  }

  /**
   * \brief Indicates whether the controller features a LED light.
   *
   * \return `true` if the controller has a LED light; `false` otherwise.
   */
  [[nodiscard]] auto has_led() const noexcept -> bool
  {
    return SDL_GameControllerHasLED(mController) == SDL_TRUE;
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  /// \} End of LED functions

  /// \name Mapping functions
  /// \{

  /**
   * \brief Returns the mapping associated with the controller.
   *
   * \return the associated mapping.
   */
  [[nodiscard]] auto mapping() const noexcept -> sdl_string
  {
    return sdl_string{SDL_GameControllerMapping(mController)};
  }

  /**
   * \brief Returns the mapping associated with a game controller.
   *
   * \param index the joystick index of the controller to query.
   *
   * \return the associated mapping.
   */
  [[nodiscard]] static auto mapping(const joystick_index index) noexcept -> sdl_string
  {
    return sdl_string{SDL_GameControllerMappingForDeviceIndex(index)};
  }

  /**
   * \brief Returns the mapping string associated with a joystick GUID.
   *
   * \param guid the GUID of the joystick to query.
   *
   * \return the associated mapping.
   */
  [[nodiscard]] static auto mapping(const SDL_JoystickGUID guid) noexcept -> sdl_string
  {
    return sdl_string{SDL_GameControllerMappingForGUID(guid)};
  }

  /**
   * \brief Returns the mapping at a specific index.
   *
   * \param index the index of the desired mapping.
   *
   * \return the associated mapping.
   */
  [[nodiscard]] static auto mapping_by_index(const mapping_index index) noexcept -> sdl_string
  {
    return sdl_string{SDL_GameControllerMappingForIndex(index)};
  }

  /// \} End of mapping functions

  /// \name Touchpad functions
  /// \{

#if SDL_VERSION_ATLEAST(2, 0, 14)

  /**
   * \brief Returns the amount of touchpads on the controller.
   *
   * \return the amount of controller touchpads.
   */
  [[nodiscard]] auto touchpad_count() const noexcept -> int
  {
    return SDL_GameControllerGetNumTouchpads(mController);
  }

  /**
   * \brief Returns the amount of supported simultaneous fingers for a touchpad.
   *
   * \param touchpad the index associated with the touchpad that will be queried.
   *
   * \return the maximum amount of fingers.
   */
  [[nodiscard]] auto touchpad_finger_capacity(const int touchpad) const noexcept -> int
  {
    return SDL_GameControllerGetNumTouchpadFingers(mController, touchpad);
  }

  /**
   * \brief Returns the state of a finger on a touchpad.
   *
   * \param touchpad the touchpad to query.
   * \param finger the index of the finger that will be queried.
   *
   * \return the state of the finger; an empty optional is returned upon failure.
   */
  [[nodiscard]] auto touchpad_finger_state(const int touchpad, const int finger) const noexcept
      -> std::optional<controller_finger_state>
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
      return std::nullopt;
    }
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  /// \} End of touchpad functions

  /// \name General information
  /// \{

  /**
   * \brief Returns the name associated with the controller.
   *
   * \return the name of the game controller; a null string is returned if there is no name.
   */
  [[nodiscard]] auto name() const noexcept -> const char*
  {
    return SDL_GameControllerName(mController);
  }

  /**
   * \brief Returns the USB vendor ID of the controller.
   *
   * \return the USB vendor ID; an empty optional is returned if it is unavailable.
   */
  [[nodiscard]] auto vendor() const noexcept -> std::optional<uint16>
  {
    const auto id = SDL_GameControllerGetVendor(mController);
    if (id != 0) {
      return id;
    }
    else {
      return std::nullopt;
    }
  }

  /**
   * \brief Returns the USB product ID of the controller.
   *
   * \return the USB product ID; an empty optional is returned if it is unavailable.
   */
  [[nodiscard]] auto product() const noexcept -> std::optional<uint16>
  {
    const auto id = SDL_GameControllerGetProduct(mController);
    if (id != 0) {
      return id;
    }
    else {
      return std::nullopt;
    }
  }

  /**
   * \brief Returns the product version of the controller.
   *
   * \return the product version; an empty optional is returned if it is unavailable.
   */
  [[nodiscard]] auto product_version() const noexcept -> std::optional<uint16>
  {
    const auto id = SDL_GameControllerGetProductVersion(mController);
    if (id != 0) {
      return id;
    }
    else {
      return std::nullopt;
    }
  }

#if SDL_VERSION_ATLEAST(2, 0, 12)

  /**
   * \brief Returns the type of the controller.
   *
   * \return the controller type.
   */
  [[nodiscard]] auto type() const noexcept -> controller_type
  {
    return static_cast<controller_type>(SDL_GameControllerGetType(mController));
  }

  /**
   * \brief Returns the type of the controller associated with the specified joystick index.
   *
   * \param index the joystick index of the controller to query.
   *
   * \return the controller type.
   */
  [[nodiscard]] static auto type(const joystick_index index) noexcept -> controller_type
  {
    return static_cast<controller_type>(SDL_GameControllerTypeForIndex(index));
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

#if SDL_VERSION_ATLEAST(2, 0, 14)

  /**
   * \brief Returns the serial number associated with the controller.
   *
   * \return the serial number associated with the controller; a null pointer is returned if
   * the serial number is unavailable.
   */
  [[nodiscard]] auto serial() const noexcept -> const char*
  {
    return SDL_GameControllerGetSerial(mController);
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  /// \} End of general information

  /// \name Effects
  /// \{

#if SDL_VERSION_ATLEAST(2, 0, 16)

  /**
   * \brief Sends a packet of controller specific data.
   *
   * \param data the data that will be sent.
   * \param size the size of the data.
   *
   * \return `success` if the data was sent successfully; `failure` if the controller or driver
   * doesn't support effect packets.
   */
  auto send_effect(const void* data, const int size) -> result
  {
    return SDL_GameControllerSendEffect(mController, data, size) == 0;
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 16)

  /// \name Setters
  /// \{

#if SDL_VERSION_ATLEAST(2, 0, 12)

  /**
   * \brief Sets the player index associated with the controller.
   *
   * \param index the player index that will be used.
   */
  void set_player_index(const player_index index) noexcept
  {
    SDL_GameControllerSetPlayerIndex(mController, index);
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

  /// \} End of setters

  /// \} End of effects

  /// \name Queries
  /// \{

  /**
   * \brief Indicates whether the game controller is currently connected.
   *
   * \return `true` if the controller is connected; `false` otherwise.
   */
  [[nodiscard]] auto connected() const noexcept -> bool
  {
    return SDL_GameControllerGetAttached(mController) == SDL_TRUE;
  }

  /**
   * \brief Returns the player index associated with the controller.
   *
   * \note If this is an XInput controller, the returned value is the user index.
   *
   * \return the player index associated with the controller; an empty optional is returned if
   * it is unavailable.
   */
  [[nodiscard]] auto index() const noexcept -> std::optional<player_index>
  {
    const auto result = SDL_GameControllerGetPlayerIndex(mController);
    if (result != -1) {
      return result;
    }
    else {
      return std::nullopt;
    }
  }

  /**
   * \brief Returns a handle to the associated joystick.
   *
   * \return the associated joystick.
   */
  [[nodiscard]] auto get_joystick() noexcept -> joystick_handle
  {
    return joystick_handle{SDL_GameControllerGetJoystick(mController)};
  }

  /// \} End of queries

  /// \name Controller event management
  /// \{

  /**
   * \brief Updates the state of all open game controllers.
   *
   * \note This is done automatically if game controller events are enabled.
   */
  static void update() { SDL_GameControllerUpdate(); }

  /**
   * \brief Sets whether game controller event polling is enabled.
   *
   * \details If polling is disabled, then you have to call `update()` by yourself.
   *
   * \param polling `true` to enable automatic controller event polling; `false` otherwise.
   */
  static void set_polling(const bool polling) noexcept
  {
    SDL_GameControllerEventState(polling ? SDL_ENABLE : SDL_DISABLE);
  }

  /**
   * \brief Indicates whether game controller event polling is enabled.
   *
   * \return `true` if controller event polling is enabled; `false` otherwise.
   */
  [[nodiscard]] static auto polling() noexcept -> bool
  {
    return SDL_GameControllerEventState(SDL_QUERY);
  }

  /// \} End of controller event management

  /// \name Global controller information
  /// \{

  /**
   * \brief Indicates whether an index is usable as a controller index.
   *
   * \param index the index that will be checked.
   *
   * \return `true` if the index is supported; `false` otherwise.
   */
  [[nodiscard]] static auto supported(const joystick_index index) noexcept -> bool
  {
    return SDL_IsGameController(index) == SDL_TRUE;
  }

  /**
   * \brief Returns the amount of available game controllers on the system.
   *
   * \return the amount of available game controllers.
   */
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

  /// \} End of global controller information

  /// \name Misc functions
  /// \{

  [[nodiscard]] auto get() const noexcept -> SDL_GameController* { return mController.get(); }

  /**
   * \brief Indicates whether a handle holds a non-null pointer.
   *
   * \return `true` if the internal pointer is non-null; `false` otherwise.
   */
  template <typename TT = T, detail::enable_for_handle<TT> = 0>
  explicit operator bool() const noexcept
  {
    return mController != nullptr;
  }

  /// \} End of misc functions

 private:
  detail::pointer<T, SDL_GameController> mController;
};

/// \name Controller mapping functions
/// \{

/**
 * \brief Adds a game controller mapping.
 *
 * \param mapping the string that encodes the game controller mapping.
 *
 * \return `added` if a new mapping was added;
 *         `updated` if a previous mapping was updated;
 *         `error` if something went wrong.
 */
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

/// \copydoc add_controller_mapping()
inline auto add_controller_mapping(const std::string& mapping) noexcept
    -> controller_mapping_result
{
  return add_controller_mapping(mapping.c_str());
}

/**
 * \brief Loads a set of game controller mappings from a file.
 *
 * \details A collection of game controller mappings can be found at <a
 * href="https://github.com/gabomdq/SDL_GameControllerDB">here</a>. New mappings for previously
 * known GUIDs will overwrite the previous mappings. Furthermore, mappings for different
 * platforms than the current platform will be ignored.
 *
 * \details It's possible to call this function several times to use multiple mapping files.
 *
 * \note The text database is stored entirely in memory during processing.
 *
 * \param file the path of the source mapping file.
 *
 * \return the amount of mappings added; an empty optional is returned upon failure.
 */
inline auto load_controller_mappings(const char* file) noexcept -> std::optional<int>
{
  assert(file);
  const auto result = SDL_GameControllerAddMappingsFromFile(file);
  if (result != -1) {
    return result;
  }
  else {
    return std::nullopt;
  }
}

/// \copydoc load_controller_mappings()
inline auto load_controller_mappings(const std::string& file) noexcept -> std::optional<int>
{
  return load_controller_mappings(file.c_str());
}

/**
 * \brief Returns the number of installed mappings.
 *
 * \return the amount of installed mappings.
 */
[[nodiscard]] inline auto controller_mapping_count() noexcept -> int
{
  return SDL_GameControllerNumMappings();
}

/// \} End of controller mapping functions

/// \name Controller functions
/// \{

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

/// \} End of controller functions

/// \} End of group game-controller

}  // namespace cen

#endif  // CENTURION_CONTROLLER_HPP_
