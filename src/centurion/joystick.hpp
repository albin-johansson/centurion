#ifndef CENTURION_JOYSTICK_HPP_
#define CENTURION_JOYSTICK_HPP_

#include <SDL.h>

#include <cassert>      // assert
#include <optional>     // optional
#include <ostream>      // ostream
#include <string>       // string, to_string
#include <string_view>  // string_view

#include "color.hpp"
#include "common.hpp"
#include "detail/owner_handle_api.hpp"
#include "detail/sdl_version_at_least.hpp"
#include "detail/stdlib.hpp"
#include "features.hpp"
#include "input.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen {

/**
 * \ingroup input
 * \defgroup joystick Joystick
 *
 * \brief Provides the low-level joystick API.
 */

/// \addtogroup joystick
/// \{

/**
 * \brief Represents the difference in a joystick ball axis position.
 */
struct ball_axis_delta final {
  int dx{};  ///< Difference in x-axis position since last poll.
  int dy{};  ///< Difference in y-axis position since last poll.
};

/**
 * \brief Represents different types of joysticks.
 */
enum class joystick_type {
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

/// \name Joystick type functions
/// \{

[[nodiscard]] constexpr auto to_string(const joystick_type type) -> std::string_view
{
  switch (type) {
    case joystick_type::unknown:
      return "unknown";

    case joystick_type::game_controller:
      return "game_controller";

    case joystick_type::wheel:
      return "wheel";

    case joystick_type::arcade_stick:
      return "arcade_stick";

    case joystick_type::flight_stick:
      return "flight_stick";

    case joystick_type::dance_pad:
      return "dance_pad";

    case joystick_type::guitar:
      return "guitar";

    case joystick_type::drum_kit:
      return "drum_kit";

    case joystick_type::arcade_pad:
      return "arcade_pad";

    case joystick_type::throttle:
      return "throttle";

    default:
      throw exception{"Did not recognize joystick type!"};
  }
}

inline auto operator<<(std::ostream& stream, const joystick_type type) -> std::ostream&
{
  return stream << to_string(type);
}

/// \} End of joystick type functions

/**
 * \brief Represents different joystick power states.
 */
enum class joystick_power {
  unknown = SDL_JOYSTICK_POWER_UNKNOWN,  ///< Unknown power level.
  empty = SDL_JOYSTICK_POWER_EMPTY,      ///< Indicates <= 5% power.
  low = SDL_JOYSTICK_POWER_LOW,          ///< Indicates <= 20% power.
  medium = SDL_JOYSTICK_POWER_MEDIUM,    ///< Indicates <= 70% power.
  full = SDL_JOYSTICK_POWER_FULL,        ///< Indicates <= 100% power.
  wired = SDL_JOYSTICK_POWER_WIRED,      ///< No need to worry about power.

  max = SDL_JOYSTICK_POWER_MAX
};

/// \name Joystick power functions
/// \{

[[nodiscard]] constexpr auto to_string(const joystick_power power) -> std::string_view
{
  switch (power) {
    case joystick_power::unknown:
      return "unknown";

    case joystick_power::empty:
      return "empty";

    case joystick_power::low:
      return "low";

    case joystick_power::medium:
      return "medium";

    case joystick_power::full:
      return "full";

    case joystick_power::wired:
      return "wired";

    case joystick_power::max:
      return "max";

    default:
      throw exception{"Did not recognize joystick power!"};
  }
}

inline auto operator<<(std::ostream& stream, const joystick_power power) -> std::ostream&
{
  return stream << to_string(power);
}

/// \} End of joystick power functions

/**
 * \brief Represents the various states of a joystick "hat".
 */
enum class hat_state : uint8 {
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

/// \name Hat state functions
/// \{

[[nodiscard]] constexpr auto to_string(const hat_state state) -> std::string_view
{
  switch (state) {
    case hat_state::centered:
      return "centered";

    case hat_state::up:
      return "up";

    case hat_state::right:
      return "right";

    case hat_state::down:
      return "down";

    case hat_state::left:
      return "left";

    case hat_state::right_up:
      return "right_up";

    case hat_state::right_down:
      return "right_down";

    case hat_state::left_up:
      return "left_up";

    case hat_state::left_down:
      return "left_down";

    default:
      throw exception{"Did not recognize hat state!"};
  }
}

inline auto operator<<(std::ostream& stream, const hat_state state) -> std::ostream&
{
  return stream << to_string(state);
}

/// \} End of hat state functions

template <typename T>
class basic_joystick;

using joystick = basic_joystick<detail::owner_tag>;          ///< An owning joystick.
using joystick_handle = basic_joystick<detail::handle_tag>;  ///< A non-owning joystick.

/**
 * \brief Represents a joystick device.
 *
 * \details The joystick is lower level than the game controller API, which is built on top of
 * the joystick API. As a result, the game controller API is easier to use and should be
 * preferred over the joystick API.
 *
 * \ownerhandle `joystick`/`joystick_handle`
 *
 * \see `joystick`
 * \see `joystick_handle`
 *
 * \see `basic_controller`
 */
template <typename T>
class basic_joystick final {
 public:
  using device_index = int;
  using id_type = SDL_JoystickID;
  using guid_type = SDL_JoystickGUID;

  /// \name Construction
  /// \{

  /**
   * \brief Creates a joystick instance based on an existing SDL joystick.
   *
   * \details Ownership of the pointer is claimed if the joystick has owning semantics.
   *
   * \param joystick a pointer to the existing joystick instance.
   *
   * \throws exception if the pointer is null and the joystick is owning.
   */
  explicit basic_joystick(maybe_owner<SDL_Joystick*> joystick) noexcept(detail::is_handle<T>)
      : mJoystick{joystick}
  {
    if constexpr (detail::is_owner<T>) {
      if (!mJoystick) {
        throw exception{"Cannot create joystick from null pointer!"};
      }
    }
  }

  /**
   * \brief Opens a joystick based on a device index.
   *
   * \param index the device index of the joystick.
   *
   * \throws sdl_error if the joystick cannot be opened.
   */
  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  explicit basic_joystick(const device_index index = 0) : mJoystick{SDL_JoystickOpen(index)}
  {
    if (!mJoystick) {
      throw sdl_error{};
    }
  }

  /**
   * \brief Creates a handle to an owning joystick.
   *
   * \param owner the existing owning joystick.
   */
  template <typename TT = T, detail::enable_for_handle<TT> = 0>
  explicit basic_joystick(const joystick& owner) noexcept : mJoystick{owner.get()}
  {}

  /// \} End of construction

  /// \name Factory functions
  /// \{

  /**
   * \brief Returns a handle to the joystick associated with a specific ID.
   *
   * \param id the ID of with the desired joystick.
   *
   * \return a potentially empty joystick handle.
   */
  template <typename TT = T, detail::enable_for_handle<TT> = 0>
  [[nodiscard]] static auto from_id(const id_type id) noexcept -> joystick_handle
  {
    return joystick_handle{SDL_JoystickFromInstanceID(id)};
  }

#if SDL_VERSION_ATLEAST(2, 0, 12)

  /**
   * \brief Returns a handle to the joystick associated with a player index.
   *
   * \param index the player index of the desired joystick.
   *
   * \return a potentially empty joystick handle.
   */
  template <typename TT = T, detail::enable_for_handle<TT> = 0>
  [[nodiscard]] static auto from_player_index(const int index) noexcept -> joystick_handle
  {
    return joystick_handle{SDL_JoystickFromPlayerIndex(index)};
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

  /// \} End of factory functions

  /// \name General information
  /// \{

  /**
   * \brief Returns the name associated with the joystick.
   *
   * \return the joystick name; a null pointer is returned if the name is unavailable.
   */
  [[nodiscard]] auto name() const noexcept -> const char*
  {
    return SDL_JoystickName(mJoystick);
  }

  /**
   * \brief Returns the name associated with a joystick.
   *
   * \param index the device index of the joystick to query.
   *
   * \return the joystick name; a null pointer is returned if the name is unavailable.
   */
  [[nodiscard]] static auto name(const device_index index) noexcept -> const char*
  {
    return SDL_JoystickNameForIndex(index);
  }

  /**
   * \brief Returns the type of the joystick.
   *
   * \return the joystick type.
   */
  [[nodiscard]] auto type() const noexcept -> joystick_type
  {
    return static_cast<joystick_type>(SDL_JoystickGetType(mJoystick));
  }

  /**
   * \brief Returns the type of a joystick.
   *
   * \param index the device index of the joystick to query.
   *
   * \return the joystick type.
   */
  [[nodiscard]] static auto type(const device_index index) noexcept -> joystick_type
  {
    return static_cast<joystick_type>(SDL_JoystickGetDeviceType(index));
  }

  /**
   * \brief Returns the USB vendor ID of the joystick.
   *
   * \return the joystick USB vendor ID; an empty optional is returned upon failure.
   */
  [[nodiscard]] auto vendor() const noexcept -> std::optional<uint16>
  {
    const auto vendor = SDL_JoystickGetVendor(mJoystick);
    if (vendor != 0) {
      return vendor;
    }
    else {
      return std::nullopt;
    }
  }

  /**
   * \brief Returns the USB vendor ID of a joystick.
   *
   * \param index the device index of the joystick that will be queried.
   *
   * \return the joystick USB vendor ID; an empty optional is returned upon failure.
   */
  [[nodiscard]] static auto vendor(const device_index index) noexcept -> std::optional<uint16>
  {
    const auto vendor = SDL_JoystickGetDeviceVendor(index);
    if (vendor != 0) {
      return vendor;
    }
    else {
      return std::nullopt;
    }
  }

  /**
   * \brief Returns the USB product ID of the joystick.
   *
   * \return the joystick USB product ID; an empty optional is returned upon failure.
   */
  [[nodiscard]] auto product() const noexcept -> std::optional<uint16>
  {
    const auto product = SDL_JoystickGetProduct(mJoystick);
    if (product != 0) {
      return product;
    }
    else {
      return std::nullopt;
    }
  }

  /**
   * \brief Returns the USB product ID of a joystick.
   *
   * \param index the device index of the joystick that will be queried.
   *
   * \return the joystick USB product ID; an empty optional is returned upon failure.
   */
  [[nodiscard]] static auto product(const device_index index) noexcept -> std::optional<uint16>
  {
    const auto product = SDL_JoystickGetDeviceProduct(index);
    if (product != 0) {
      return product;
    }
    else {
      return std::nullopt;
    }
  }

  /**
   * \brief Returns the product version of the joystick.
   *
   * \return the joystick product version; an empty optional is returned upon failure.
   */
  [[nodiscard]] auto product_version() const noexcept -> std::optional<uint16>
  {
    const auto version = SDL_JoystickGetProductVersion(mJoystick);
    if (version != 0) {
      return version;
    }
    else {
      return std::nullopt;
    }
  }

  /**
   * \brief Returns the product version of a joystick.
   *
   * \param index the device index of the joystick that will be queried.
   *
   * \return the joystick product version; an empty optional is returned upon failure.
   */
  [[nodiscard]] static auto product_version(const device_index index) noexcept
      -> std::optional<uint16>
  {
    const auto version = SDL_JoystickGetDeviceProductVersion(index);
    if (version != 0) {
      return version;
    }
    else {
      return std::nullopt;
    }
  }

  /**
   * \brief Returns the GUID of the joystick.
   *
   * \return the joystick GUID; a zeroed GUID is returned for an invalid index.
   */
  [[nodiscard]] auto guid() noexcept -> guid_type { return SDL_JoystickGetGUID(mJoystick); }

  /**
   * \brief Returns the GUID of a joystick.
   *
   * \param index the device index of the joystick that will be queried.
   *
   * \return the joystick GUID; a zeroed GUID is returned for an invalid index.
   */
  [[nodiscard]] static auto guid(const device_index index) noexcept -> guid_type
  {
    return SDL_JoystickGetDeviceGUID(index);
  }

#if SDL_VERSION_ATLEAST(2, 0, 14)

  /**
   * \brief Returns the serial number associated with the joystick.
   *
   * \return the joystick serial number; a null pointer is returned upon failure.
   */
  [[nodiscard]] auto serial() const noexcept -> const char*
  {
    return SDL_JoystickGetSerial(mJoystick);
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  /**
   * \brief Returns the amount of buttons on the joystick.
   *
   * \return the joystick button count.
   */
  [[nodiscard]] auto button_count() const noexcept -> int
  {
    return SDL_JoystickNumButtons(mJoystick);
  }

  /**
   * \brief Returns the amount of hats on the joystick.
   *
   * \return the joystick hat count.
   */
  [[nodiscard]] auto hat_count() const noexcept -> int
  {
    return SDL_JoystickNumHats(mJoystick);
  }

  /**
   * \brief Returns the amount of axis controls on the joystick.
   *
   * \return the joystick axis control count.
   */
  [[nodiscard]] auto axis_count() const noexcept -> int
  {
    return SDL_JoystickNumAxes(mJoystick);
  }

  /**
   * \brief Returns the amount of trackballs on the joystick.
   *
   * \return the joystick trackball count.
   */
  [[nodiscard]] auto trackball_count() const noexcept -> int
  {
    return SDL_JoystickNumBalls(mJoystick);
  }

  /// \} End of general information

  /// \name Queries
  /// \{

  /**
   * \brief Returns the ID associated with the joystick.
   *
   * \return a joystick identifier.
   */
  [[nodiscard]] auto id() const noexcept -> id_type
  {
    return SDL_JoystickInstanceID(mJoystick);
  }

  /**
   * \brief Returns the ID associated with a joystick.
   *
   * \param index the device index of the joystick that will be queried.
   *
   * \return a joystick identifier; an empty optional is returned upon failure.
   */
  [[nodiscard]] static auto id(const device_index index) noexcept -> std::optional<id_type>
  {
    const auto id = SDL_JoystickGetDeviceInstanceID(index);
    if (id != -1) {
      return id;
    }
    else {
      return std::nullopt;
    }
  }

  /**
   * \brief Indicates whether the joystick has been opened.
   *
   * \return `true` if the joystick is opened; false otherwise.
   */
  [[nodiscard]] auto attached() const noexcept -> bool
  {
    return SDL_JoystickGetAttached(mJoystick);
  }

  /**
   * \brief Returns the current power state of the joystick.
   *
   * \return the joystick power state.
   */
  [[nodiscard]] auto power() const noexcept -> joystick_power
  {
    return static_cast<joystick_power>(SDL_JoystickCurrentPowerLevel(mJoystick));
  }

  /// \} End of queries

  /// \name Rumble functions
  /// \{

  /**
   * \brief Makes the joystick rumble.
   *
   * \details This function cancels any previously active rumble effects.
   *
   * \note This function has no effect if rumbling isn't supported by joystick.
   *
   * \param lo the intensity of the low frequency (left) motor.
   * \param hi the intensity of the high frequency (right) motor.
   * \param duration the duration of the rumble effect.
   *
   * \return `success` if the rumble was successful; `failure` otherwise.
   */
  auto rumble(const uint16 lo,
              const uint16 hi,
              const u32ms duration) noexcept(noexcept(duration.count())) -> result
  {
    return SDL_JoystickRumble(mJoystick, lo, hi, duration.count()) == 0;
  }

  /**
   * \brief Stops any currently playing rumble effect.
   *
   * \return `success` if the operation succeeded; `failure` otherwise.
   */
  auto stop_rumble() -> result { return rumble(0, 0, u32ms::zero()); }

#if SDL_VERSION_ATLEAST(2, 0, 14)

  /**
   * \brief Makes the joystick triggers rumble.
   *
   * \details This function cancels any previously active rumble effects.
   *
   * \note This function has no effect if rumbling isn't supported by joystick.
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
    return SDL_JoystickRumbleTriggers(mJoystick, left, right, duration.count()) == 0;
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  /// \} End of rumble functions

  /// \name LED functions
  /// \{

#if SDL_VERSION_ATLEAST(2, 0, 14)

  auto set_led(const color& color) noexcept -> result
  {
    return SDL_JoystickSetLED(mJoystick, color.red(), color.green(), color.blue()) == 0;
  }

  /**
   * \brief Indicates whether the joystick features a LED light.
   *
   * \return `true` if the joystick has a LED light; `false` otherwise.
   */
  [[nodiscard]] auto has_led() const noexcept -> bool
  {
    return SDL_JoystickHasLED(mJoystick) == SDL_TRUE;
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  /// \} End of LED functions

  /// \name Virtual joystick API
  /// \{

#if SDL_VERSION_ATLEAST(2, 0, 14)

  /**
   * \brief Attaches a new virtual joystick.
   *
   * \param type the type of the joystick.
   * \param axes the number of axes.
   * \param buttons the number of buttons.
   * \param hats the number of joystick hats.
   *
   * \return the virtual joystick device index; an empty optional is returned upon failure.
   */
  [[nodiscard]] static auto attach_virtual(const joystick_type type,
                                           const int axes,
                                           const int buttons,
                                           const int hats) noexcept
      -> std::optional<device_index>
  {
    const auto index =
        SDL_JoystickAttachVirtual(static_cast<SDL_JoystickType>(type), axes, buttons, hats);
    if (index != -1) {
      return index;
    }
    else {
      return std::nullopt;
    }
  }

  /**
   * \brief Detaches a virtual joystick.
   *
   * \param index the device index of the virtual joystick.
   *
   * \return `success` if the joystick was disconnected; `failure` otherwise.
   */
  static auto detach_virtual(const device_index index) noexcept -> result
  {
    return SDL_JoystickDetachVirtual(index) == 0;
  }

  /**
   * \brief Sets the value of a virtual joystick axis.
   *
   * \param axis the axis that will be modified.
   * \param value the new axis value.
   *
   * \return `success` if the axis was updated; `failure` otherwise.
   */
  auto set_virtual_axis(const int axis, const int16 value) noexcept -> result
  {
    return SDL_JoystickSetVirtualAxis(mJoystick, axis, value) == 0;
  }

  /**
   * \brief Sets the state of a virtual button.
   *
   * \param button the index of the button that will be set.
   * \param state the new button state.
   *
   * \return `success` if the button was updated; `failure` otherwise.
   */
  auto set_virtual_button(const int button, const button_state state) noexcept -> result
  {
    return SDL_JoystickSetVirtualButton(mJoystick, button, to_underlying(state)) == 0;
  }

  /**
   * \brief Sets the state of a virtual joystick hat.
   *
   * \param hat the index of the hat that will be changed.
   * \param state the new hat state.
   *
   * \return `success` if the hat was updated; `failure` otherwise.
   */
  auto set_virtual_hat(const int hat, const hat_state state) noexcept -> result
  {
    return SDL_JoystickSetVirtualHat(mJoystick, hat, to_underlying(state)) == 0;
  }

  /**
   * \brief Indicates whether a joystick is virtual.
   *
   * \param index the device index of the joystick to query.
   *
   * \return `true` if the joystick is virtual; `false` otherwise.
   */
  [[nodiscard]] static auto is_virtual(const device_index index) noexcept -> bool
  {
    return SDL_JoystickIsVirtual(index) == SDL_TRUE;
  }

#endif  // #if SDL_VERSION_ATLEAST(2, 0, 14)

  /// \} End of virtual joystick API

  /// \name Button and axis functions
  /// \{

  /**
   * \brief Returns the state of a joystick button.
   *
   * \param button the index of the button to query.
   *
   * \return the button state.
   */
  [[nodiscard]] auto query_button(const int button) const noexcept -> button_state
  {
    return static_cast<button_state>(SDL_JoystickGetButton(mJoystick, button));
  }

  /**
   * \brief Returns the state of a joystick hat.
   *
   * \param hat the index of the hat to query.
   *
   * \return the hat state.
   */
  [[nodiscard]] auto query_hat(const int hat) const noexcept -> hat_state
  {
    return static_cast<hat_state>(SDL_JoystickGetHat(mJoystick, hat));
  }

  /**
   * \brief Returns the position of an axis.
   *
   * \details Most modern joysticks let the X-axis be represented by 0 and the Y-axis by 1. It
   * might be a good idea to combat jitter by imposing thresholds on the returned values.
   *
   * \note Some joysticks use axes 2 and 3 for extra buttons.
   *
   * \param axis the index of the axis to query.
   *
   * \return the axis position.
   */
  [[nodiscard]] auto query_axis(const int axis) const noexcept -> int16
  {
    return SDL_JoystickGetAxis(mJoystick, axis);
  }

  /**
   * \brief Returns the initial state of an axis on the joystick.
   *
   * \param axis the index of the axis that will be queried.
   *
   * \return the initial state of the axis; an empty optional is returned if there is none.
   */
  [[nodiscard]] auto axis_initial_state(const int axis) const noexcept -> std::optional<int16>
  {
    int16 state{};
    if (SDL_JoystickGetAxisInitialState(mJoystick, axis, &state)) {
      return state;
    }
    else {
      return std::nullopt;
    }
  }

  /**
   * \brief Returns the ball axis delta since the last poll.
   *
   * \details Trackballs can only return relative motion since the last call.
   *
   * \param ball the index of the trackball to query.
   *
   * \return the axis delta; an empty optional is returned upon failure.
   */
  [[nodiscard]] auto get_ball_axis_delta(const int ball) const noexcept
      -> std::optional<ball_axis_delta>
  {
    ball_axis_delta change{};
    if (SDL_JoystickGetBall(mJoystick, ball, &change.dx, &change.dy) == 0) {
      return change;
    }
    else {
      return std::nullopt;
    }
  }

  /// \} End of button and axis functions

  /// \name Effects
  /// \{

#if SDL_VERSION_ATLEAST(2, 0, 16)

  /**
   * \brief Sends a packet of joystick specific data.
   *
   * \param data the data that will be sent.
   * \param size the size of the data.
   *
   * \return `success` if the data was sent successfully; `failure` if the joystick
   * or driver doesn't support effect packets.
   */
  auto send_effect(const void* data, const int size) -> result
  {
    return SDL_JoystickSendEffect(mJoystick, data, size) == 0;
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 16)

  /// \} End of effects

  /// \name Setters
  /// \{

#if SDL_VERSION_ATLEAST(2, 0, 12)

  /**
   * \brief Sets the player index associated with the joystick.
   *
   * \param index new the player index.
   */
  void set_player_index(const int index) noexcept
  {
    SDL_JoystickSetPlayerIndex(mJoystick, index);
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

  /// \} End of setters

  /// \name Getters
  /// \{

  /**
   * \brief Returns the player index associated with the joystick.
   *
   * \return the joystick player index; an empty optional is returned upon failure.
   */
  [[nodiscard]] auto player_index() const noexcept -> std::optional<int>
  {
    const auto index = SDL_JoystickGetPlayerIndex(mJoystick);
    if (index != -1) {
      return index;
    }
    else {
      return std::nullopt;
    }
  }

  /**
   * \brief Returns the player index associated with a joystick.
   *
   * \param index the device index of the joystick to query.
   *
   * \return the joystick player index; an empty optional is returned upon failure.
   */
  [[nodiscard]] static auto player_index(const device_index index) noexcept
      -> std::optional<int>
  {
    const auto player = SDL_JoystickGetDevicePlayerIndex(index);
    if (player != -1) {
      return player;
    }
    else {
      return std::nullopt;
    }
  }

  /// \} End of getters

  /// \name GUID string conversions
  /// \{

  /**
   * \brief Returns a joystick GUID based on a string.
   *
   * \param str the string used to obtain the GUID.
   *
   * \return the obtained GUID.
   */
  [[nodiscard]] static auto to_guid(const char* str) noexcept -> guid_type
  {
    assert(str);
    return SDL_JoystickGetGUIDFromString(str);
  }

  /// \copydoc to_guid()
  [[nodiscard]] static auto to_guid(const std::string& str) noexcept -> guid_type
  {
    return to_guid(str.c_str());
  }

  /// \} End of GUID string conversions

  /// \name Joystick management
  /// \{

  /**
   * \brief Locks the access to all joysticks.
   *
   * \details If you are using the joystick API from multiple threads you should use this
   * function to restrict access to the joysticks.
   */
  static void lock() noexcept { SDL_LockJoysticks(); }

  /**
   * \brief Unlocks the access to all joysticks.
   */
  static void unlock() noexcept { SDL_UnlockJoysticks(); }

  /**
   * \brief Updates the state of all open joysticks.
   *
   * \note This is done automatically by the event loop if joystick events are enabled.
   */
  static void update() noexcept { SDL_JoystickUpdate(); }

  /**
   * \brief Sets whether joystick event polling is enabled.
   *
   * \details If polling is disabled, then you have to call `update()` by yourself.
   *
   * \param enabled `true` to enable automatic joystick event polling; `false` otherwise.
   */
  static void set_polling(const bool enabled) noexcept
  {
    SDL_JoystickEventState(enabled ? SDL_ENABLE : SDL_DISABLE);
  }

  /**
   * \brief Indicates whether joystick event polling is enabled.
   *
   * \return `true` if joystick event polling is enabled; `false` otherwise.
   */
  [[nodiscard]] static auto polling() noexcept -> bool
  {
    return SDL_JoystickEventState(SDL_QUERY);
  }

  /// \} End of joystick management

  /// \name Global joystick information
  /// \{

  /**
   * \brief Returns the amount of available joysticks.
   *
   * \return the amount of available joysticks; an empty optional is returned upon failure.
   */
  [[nodiscard]] static auto count() noexcept -> std::optional<int>
  {
    const auto result = SDL_NumJoysticks();
    if (result >= 0) {
      return result;
    }
    else {
      return std::nullopt;
    }
  }

  /**
   * \brief Returns the maximum possible value of an joystick axis control.
   *
   * \return the maximum value of an axis control.
   */
  [[nodiscard]] constexpr static auto axis_max() noexcept -> int16
  {
    return SDL_JOYSTICK_AXIS_MAX;
  }

  /**
   * \brief Returns the minimum possible value of an joystick axis control.
   *
   * \return the minimum value of an axis control.
   */
  [[nodiscard]] constexpr static auto axis_min() noexcept -> int16
  {
    return SDL_JOYSTICK_AXIS_MIN;
  }

  /// \} End of global joystick information

  /// \name Misc functions
  /// \{

  /**
   * \brief Indicates whether a handle holds a non-null pointer.
   *
   * \return `true` if the internal pointer isn't null; `false` otherwise.
   */
  template <typename TT = T, detail::enable_for_handle<TT> = 0>
  explicit operator bool() const noexcept
  {
    return mJoystick != nullptr;
  }

  [[nodiscard]] auto get() const noexcept -> SDL_Joystick* { return mJoystick.get(); }

  /// \} End of misc functions

 private:
  detail::pointer<T, SDL_Joystick> mJoystick;
};

/// \name Joystick functions
/// \{

template <typename T>
[[nodiscard]] auto to_string(const basic_joystick<T>& joystick) -> std::string
{
  const char* serial{};
  if constexpr (detail::sdl_version_at_least(2, 0, 14)) {
    serial = joystick.serial();
  }

#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("joystick(data: {}, id: {}, name: '{}', serial: {})",
                     detail::address_of(joystick.get()),
                     joystick.GetID(),
                     str_or_na(joystick.GetName()),
                     str_or_na(serial));
#else
  return "joystick(data: " + detail::address_of(joystick.get()) +
         ", id: " + std::to_string(joystick.id()) + ", name: '" + str_or_na(joystick.name()) +
         ", serial: " + str_or_na(serial) + "')";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

template <typename T>
auto operator<<(std::ostream& stream, const basic_joystick<T>& joystick) -> std::ostream&
{
  return stream << to_string(joystick);
}

/// \} End of joystick functions

/// \} End of group joystick

}  // namespace cen

#endif  // CENTURION_JOYSTICK_HPP_