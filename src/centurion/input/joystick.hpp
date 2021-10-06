#ifndef CENTURION_JOYSTICK_HEADER
#define CENTURION_JOYSTICK_HEADER

#include <SDL.h>

#include <cassert>   // assert
#include <optional>  // optional
#include <ostream>   // ostream
#include <string>    // string, to_string

#include "../compiler/features.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

#include "../core/exception.hpp"
#include "../core/integers.hpp"
#include "../core/not_null.hpp"
#include "../core/owner.hpp"
#include "../core/result.hpp"
#include "../core/str.hpp"
#include "../core/str_or_na.hpp"
#include "../core/time.hpp"
#include "../core/to_underlying.hpp"
#include "../detail/address_of.hpp"
#include "../detail/owner_handle_api.hpp"
#include "../detail/sdl_version_at_least.hpp"
#include "../video/color.hpp"
#include "button_state.hpp"
#include "hat_state.hpp"
#include "joystick_power.hpp"
#include "joystick_type.hpp"

namespace cen {

/// \addtogroup input
/// \{

/**
 * \struct ball_axis_change
 *
 * \brief Represents the difference in a joystick ball axis position.
 *
 * \since 4.2.0
 */
struct ball_axis_change final
{
  int dx;  ///< Difference in x-axis position since last poll.
  int dy;  ///< Difference in y-axis position since last poll.
};

template <typename T>
class basic_joystick;

/**
 * \typedef joystick
 *
 * \brief Represents an owning joystick.
 *
 * \since 5.0.0
 */
using joystick = basic_joystick<detail::owning_type>;

/**
 * \typedef joystick_handle
 *
 * \brief Represents a non-owning joystick.
 *
 * \since 5.0.0
 */
using joystick_handle = basic_joystick<detail::handle_type>;

/**
 * \class basic_joystick
 *
 * \brief Represents a joystick device.
 *
 * \ownerhandle `joystick`/`joystick_handle`
 *
 * \details The game controller API is built on top of the joystick API, which means that
 * the game controller is higher-level and easier to use.
 *
 * \since 4.2.0
 *
 * \see joystick
 * \see joystick_handle
 */
template <typename T>
class basic_joystick final
{
 public:
  /// \name Construction
  /// \{

  // clang-format off

  /**
   * \brief Creates a joystick instance based on an existing SDL joystick.
   *
   * \note The created instance will only claim ownership of the supplied pointer if the
   * class has owning semantics, i.e. if it's a `joystick` instance.
   *
   * \param joystick a pointer to the existing joystick.
   *
   * \throws cen_error if the supplied pointer is null and the joystick is owning.
   */
  explicit basic_joystick(maybe_owner<SDL_Joystick*> joystick) noexcept(!detail::is_owning<T>())
      : m_joystick{joystick}
  {
    if constexpr (detail::is_owning<T>())
    {
      if (!m_joystick)
      {
        throw cen_error{"Cannot create joystick from null pointer!"};
      }
    }
  }

  // clang-format on

  /**
   * \brief Creates an owning joystick based on a joystick device index.
   *
   * \param index the device index of the joystick.
   *
   * \throws sdl_error if the joystick couldn't be opened.
   */
  template <typename TT = T, detail::is_owner<TT> = 0>
  explicit basic_joystick(const int index = 0) : m_joystick{SDL_JoystickOpen(index)}
  {
    if (!m_joystick) {
      throw sdl_error{};
    }
  }

  /**
   * \brief Creates a handle to an owning joystick.
   *
   * \param owner the owning joystick instance.
   */
  template <typename TT = T, detail::is_handle<TT> = 0>
  explicit basic_joystick(const joystick& owner) noexcept : m_joystick{owner.get()}
  {}

  /**
   * \brief Returns a handle to the joystick associated with the specified ID.
   *
   * \param id the joystick ID associated with the desired joystick.
   *
   * \return a handle to the joystick associated with the supplied ID, might be empty.
   *
   * \since 5.0.0
   */
  template <typename TT = T, detail::is_handle<TT> = 0>
  [[nodiscard]] static auto from_instance_id(const SDL_JoystickID id) noexcept
      -> joystick_handle
  {
    return joystick_handle{SDL_JoystickFromInstanceID(id)};
  }

#if SDL_VERSION_ATLEAST(2, 0, 12)

  /**
   * \brief Returns a handle to the joystick associated with the specified player index.
   *
   * \param playerIndex the player index of the desired joystick.
   *
   * \return a handle to the associated joystick, which might be empty.
   *
   * \since 5.0.0
   */
  template <typename TT = T, detail::is_handle<TT> = 0>
  [[nodiscard]] static auto from_player_index(const int playerIndex) noexcept
      -> joystick_handle
  {
    return joystick_handle{SDL_JoystickFromPlayerIndex(playerIndex)};
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

  /// \} End of construction

  /**
   * \brief Makes the joystick rumble.
   *
   * \details Invoking this function cancels any previous rumble effects. This function
   * has no effect if the joystick doesn't support rumble effects.
   *
   * \param lowFreq the intensity of the low frequency (left) motor.
   * \param highFreq the intensity of the high frequency (right) motor.
   * \param duration the duration of the rumble effect, in milliseconds.
   *
   * \return `success` if nothing went wrong; `failure` otherwise.
   *
   * \since 4.2.0
   */
  auto rumble(const u16 lowFreq,
              const u16 highFreq,
              const milliseconds<u32> duration) noexcept(noexcept(duration.count())) -> result
  {
    return SDL_JoystickRumble(m_joystick, lowFreq, highFreq, duration.count()) == 0;
  }

#if SDL_VERSION_ATLEAST(2, 0, 14)

  // clang-format off

  /**
   * \brief Starts a rumble effect in the joystick's triggers.
   *
   * \details Calls to this function cancels any previously active rumble effect.
   * Furthermore, supplying 0 as intensities will stop the rumble effect.
   *
   * \param left the intensity used by the left rumble motor.
   * \param right the intensity used by the right rumble motor.
   * \param duration the duration of the rumble.
   *
   * \return `success` if nothing went wrong; `failure` otherwise.
   *
   * \since 5.2.0
   */
  auto rumble_triggers(const u16 left,
                       const u16 right,
                       const milliseconds<u32> duration) noexcept(noexcept(duration.count()))
      -> result
  {
    return SDL_JoystickRumbleTriggers(m_joystick,
                                      left,
                                      right,
                                      duration.count()) == 0;
  }

  // clang-format on

  /**
   * \brief Sets the color of the LED light, if the joystick has one.
   *
   * \param color the color that will be used by the LED, note that the alpha component is
   * ignored.
   *
   * \return `success` if nothing went wrong; `failure` otherwise.
   *
   * \since 5.2.0
   */
  auto set_led(const color& color) noexcept -> result
  {
    return SDL_JoystickSetLED(m_joystick, color.red(), color.green(), color.blue()) == 0;
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

#if SDL_VERSION_ATLEAST(2, 0, 12)

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

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

#if SDL_VERSION_ATLEAST(2, 0, 16)

  /**
   * \brief Sends a packet of joystick specific data.
   *
   * \param data the data that will be sent.
   * \param size the size of the data.
   *
   * \return `success` if the data was sent successfully; `failure` if the joystick
   * or driver doesn't support effect packets.
   *
   * \since 6.2.0
   */
  auto send_effect(const void* data, const int size) -> result
  {
    return SDL_JoystickSendEffect(m_joystick, data, size) == 0;
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 16)

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
   * \return the device index of the virtual joystick; `std::nullopt` if something went
   * wrong.
   *
   * \since 5.2.0
   */
  [[nodiscard]] static auto attach_virtual(const joystick_type type,
                                           const int nAxes,
                                           const int nButtons,
                                           const int nHats) noexcept -> std::optional<int>
  {
    const auto index =
        SDL_JoystickAttachVirtual(static_cast<SDL_JoystickType>(type), nAxes, nButtons, nHats);
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
   * \return `success` if the joystick was successfully disconnected; `failure` otherwise.
   *
   * \since 5.2.0
   */
  static auto detach_virtual(const int index) noexcept -> result
  {
    return SDL_JoystickDetachVirtual(index) == 0;
  }

  /**
   * \brief Sets the value of a virtual joystick axis.
   *
   * \param axis the axis that will be modified.
   * \param value the new value of the axis.
   *
   * \return `success` if nothing went wrong; `failure` otherwise.
   *
   * \since 5.2.0
   */
  auto set_virtual_axis(const int axis, const i16 value) noexcept -> result
  {
    return SDL_JoystickSetVirtualAxis(m_joystick, axis, value) == 0;
  }

  /**
   * \brief Sets the state of a virtual button.
   *
   * \param button the index of the button that will be set.
   * \param state the new button state.
   *
   * \return `success` if nothing went wrong; `failure` otherwise.
   *
   * \since 5.2.0
   */
  auto set_virtual_button(const int button, const button_state state) noexcept -> result
  {
    return SDL_JoystickSetVirtualButton(m_joystick, button, to_underlying(state)) == 0;
  }

  /**
   * \brief Sets the state of a virtual joystick hat.
   *
   * \param hat the index of the hat that will be changed.
   * \param state the new state of the virtual joystick hat.
   *
   * \return `success` if nothing went wrong; `failure` otherwise.
   *
   * \since 5.2.0
   */
  auto set_virtual_hat(const int hat, const hat_state state) noexcept -> result
  {
    return SDL_JoystickSetVirtualHat(m_joystick, hat, to_underlying(state)) == 0;
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
   * \return the player index associated with the joystick; `std::nullopt` if it can't be
   * obtained
   *
   * \since 4.2.0
   */
  [[nodiscard]] auto player_index() const noexcept -> std::optional<int>
  {
    const auto index = SDL_JoystickGetPlayerIndex(m_joystick);
    if (index != -1) {
      return index;
    }
    else {
      return std::nullopt;
    }
  }

  /**
   * \brief Returns the type associated with the joystick.
   *
   * \return the type of the joystick.
   *
   * \since 4.2.0
   */
  [[nodiscard]] auto type() const noexcept -> joystick_type
  {
    return static_cast<joystick_type>(SDL_JoystickGetType(m_joystick));
  }

  /**
   * \brief Returns the USB vendor ID of the joystick.
   *
   * \return the USB vendor ID associated with the joystick; `std::nullopt` if it isn't
   * available.
   *
   * \since 4.2.0
   */
  [[nodiscard]] auto vendor() const noexcept -> std::optional<u16>
  {
    const auto vendor = SDL_JoystickGetVendor(m_joystick);
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
   * \return the USB product ID associated with the joystick; `std::nullopt` if it isn't
   * available.
   *
   * \since 4.2.0
   */
  [[nodiscard]] auto product() const noexcept -> std::optional<u16>
  {
    const auto product = SDL_JoystickGetProduct(m_joystick);
    if (product != 0) {
      return product;
    }
    else {
      return std::nullopt;
    }
  }

  /**
   * \brief Returns the product version of the joystick, if available.
   *
   * \return the product version of the joystick; `std::nullopt` if it isn't available.
   *
   * \since 4.2.0
   */
  [[nodiscard]] auto product_version() const noexcept -> std::optional<u16>
  {
    const auto version = SDL_JoystickGetProductVersion(m_joystick);
    if (version != 0) {
      return version;
    }
    else {
      return std::nullopt;
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
   * \note If no name can be found, this function returns a null string.
   *
   * \return the name of the joystick; a null pointer if no name is found.
   *
   * \since 4.2.0
   */
  [[nodiscard]] auto name() const noexcept -> str
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
   * \return the serial number of the joystick; a null pointer is returned if the serial
   * number isn't available.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto serial() const noexcept -> str
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
   * \brief Returns the player index of the joystick associated with the specified device
   * index.
   *
   * \note This function can be called before any joysticks are opened.
   *
   * \param deviceIndex the device index of the joystick that will be queried.
   *
   * \return the player index of the desired joystick; `std::nullopt` if it can't be
   * obtained.
   *
   * \since 4.2.0
   */
  [[nodiscard]] static auto player_index(const int deviceIndex) noexcept -> std::optional<int>
  {
    const auto index = SDL_JoystickGetDevicePlayerIndex(deviceIndex);
    if (index != -1) {
      return index;
    }
    else {
      return std::nullopt;
    }
  }

  /**
   * \brief Returns the type of the joystick associated with the specified device index.
   *
   * \param deviceIndex the device index of the joystick that will be queried.
   *
   * \return the type of the specified joystick.
   *
   * \since 4.2.0
   */
  [[nodiscard]] static auto type(const int deviceIndex) noexcept -> joystick_type
  {
    return static_cast<joystick_type>(SDL_JoystickGetDeviceType(deviceIndex));
  }

  /**
   * \brief Returns the USB vendor ID for the joystick associated with the specified
   * device index.
   *
   * \param deviceIndex the device index of the joystick that will be queried.
   *
   * \return the USB vendor ID of the desired joystick; `std::nullopt` if it can't be
   * obtained.
   *
   * \since 4.2.0
   */
  [[nodiscard]] static auto vendor(const int deviceIndex) noexcept -> std::optional<u16>
  {
    const auto vendor = SDL_JoystickGetDeviceVendor(deviceIndex);
    if (vendor != 0) {
      return vendor;
    }
    else {
      return std::nullopt;
    }
  }

  /**
   * \brief Returns the USB product ID for the joystick associated with the specified
   * device index.
   *
   * \param deviceIndex the device index of the joystick that will be queried.
   *
   * \return the USB product ID of the desired joystick; `std::nullopt` if it can't be
   * obtained.
   *
   * \since 4.2.0
   */
  [[nodiscard]] static auto product(const int deviceIndex) noexcept -> std::optional<u16>
  {
    const auto product = SDL_JoystickGetDeviceProduct(deviceIndex);
    if (product != 0) {
      return product;
    }
    else {
      return std::nullopt;
    }
  }

  /**
   * \brief Returns the product version for the joystick associated with the specified
   * device index.
   *
   * \param deviceIndex the device index of the joystick that will be queried.
   *
   * \return the product version of the desired joystick; `std::nullopt` if it can't be
   * obtained.
   *
   * \since 4.2.0
   */
  [[nodiscard]] static auto product_version(const int deviceIndex) noexcept
      -> std::optional<u16>
  {
    const auto version = SDL_JoystickGetDeviceProductVersion(deviceIndex);
    if (version != 0) {
      return version;
    }
    else {
      return std::nullopt;
    }
  }

  /**
   * \brief Returns the GUID for the joystick associated with the specified device index.
   *
   * \note The GUID is implementation-dependent.
   * \note This function can be called before any joysticks are opened.
   *
   * \param deviceIndex refers to the N'th joystick that is currently recognized by SDL.
   *
   * \return the GUID of the joystick associated with the device index.
   *
   * \since 4.2.0
   */
  [[nodiscard]] static auto guid(const int deviceIndex) noexcept -> SDL_JoystickGUID
  {
    return SDL_JoystickGetDeviceGUID(deviceIndex);
  }

  /**
   * \brief Returns the associated with the joystick with the specified device index.
   *
   * \param deviceIndex refers to the N'th joystick that is currently recognized by SDL.
   *
   * \return the name associated with the joystick; a null string is returned if no name
   * is found.
   *
   * \since 4.2.0
   */
  [[nodiscard]] static auto name(const int deviceIndex) noexcept -> str
  {
    return SDL_JoystickNameForIndex(deviceIndex);
  }

  /**
   * \brief Returns the instance ID for the joystick associated with the specified device
   * index.
   *
   * \param deviceIndex the device index of the joystick that will be queried.
   *
   * \return the instance ID of the desired joystick; `std::nullopt` if it can't be
   * obtained.
   *
   * \since 4.2.0
   */
  [[nodiscard]] static auto instance_id(const int deviceIndex) noexcept
      -> std::optional<SDL_JoystickID>
  {
    const auto id = SDL_JoystickGetDeviceInstanceID(deviceIndex);
    if (id != -1) {
      return id;
    }
    else {
      return std::nullopt;
    }
  }

  /// \} End of index-based queries

  /**
   * \brief Returns the ball axis change since the last poll.
   *
   * \note Trackballs can only return relative motion since the last call, these motion
   * deltas are placed into the `BallAxisChange` struct.
   *
   * \param ball the ball index to check, start at 0.
   *
   * \return a `JoystickBallAxisChange` instance or `std::nullopt` if something goes
   * wrong.
   *
   * \since 4.2.0
   */
  [[nodiscard]] auto get_ball_axis_change(const int ball) const noexcept
      -> std::optional<ball_axis_change>
  {
    ball_axis_change change{};
    if (SDL_JoystickGetBall(m_joystick, ball, &change.dx, &change.dy) == 0) {
      return change;
    }
    else {
      return std::nullopt;
    }
  }

  /**
   * \brief Returns the current position of the specified axis.
   *
   * \details Most modern joysticks let the X-axis be represented by 0 and the Y-axis
   * by 1. To account for jitter, it may be necessary to impose some kind of tolerance on
   * the returned value.
   *
   * \note Some joysticks use axes 2 and 3 for extra buttons.
   *
   * \param axis the ID of the axis to query.
   *
   * \return the position of the specified axis.
   *
   * \since 4.2.0
   */
  [[nodiscard]] auto axis_pos(const int axis) const noexcept -> i16
  {
    return SDL_JoystickGetAxis(m_joystick, axis);
  }

  /**
   * \brief Returns the initial state of the specified axis on the joystick.
   *
   * \param axis the axis that will be queried. Starts at 0.
   *
   * \return the initial state of the axis; `std::nullopt` if the axis doesn't have an
   * initial state.
   *
   * \since 4.2.0
   */
  [[nodiscard]] auto axis_initial_state(const int axis) const noexcept -> std::optional<i16>
  {
    i16 state{};
    if (SDL_JoystickGetAxisInitialState(m_joystick, axis, &state)) {
      return state;
    }
    else {
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
   * \brief Returns the current power level of the joystick.
   *
   * \return the current power level.
   *
   * \since 4.2.0
   */
  [[nodiscard]] auto get_power() const noexcept -> joystick_power
  {
    return static_cast<joystick_power>(SDL_JoystickCurrentPowerLevel(m_joystick));
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
  [[nodiscard]] auto get_button_state(const int button) const noexcept -> button_state
  {
    return static_cast<button_state>(SDL_JoystickGetButton(m_joystick, button));
  }

  /**
   * \brief Returns the state of a specific joystick hat.
   *
   * \param hat the index of the hat to query, indices start at 0.
   *
   * \return the current state of the hat.
   *
   * \since 4.2.0
   */
  [[nodiscard]] auto get_hat_state(const int hat) const noexcept -> hat_state
  {
    return static_cast<hat_state>(SDL_JoystickGetHat(m_joystick, hat));
  }

  /**
   * \brief Updates the state of all open joysticks.
   *
   * \note This is done automatically by the event loop if any joystick events are
   * enabled.
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
   * \details If you are using the joystick API from multiple threads you should use this
   * function to restrict access to the joysticks.
   *
   * \since 4.2.0
   */
  static void lock() noexcept
  {
    SDL_LockJoysticks();
  }

  /**
   * \brief Unlocks the access to all joysticks.
   *
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
   * `basic_joystick::update()` in order to update the joystick state.
   *
   * \note It's recommended to leave joystick event polling enabled.
   *
   * \warning Calling this function might cause all events currently in the event queue to
   * be deleted.
   *
   * \param enabled `true` if joystick event polling should be enabled; `false` otherwise.
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
   * \return the current amount of available joysticks; `std::nullopt` if something goes
   * wrong.
   *
   * \since 5.1.0
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
   * \brief Returns a joystick GUID based on the supplied string.
   *
   * \param str the string used to obtain the GUID, can't be null.
   *
   * \return the obtained GUID.
   *
   * \since 4.2.0
   */
  [[nodiscard]] static auto guid_from_string(const not_null<str> str) noexcept
      -> SDL_JoystickGUID
  {
    assert(str);
    return SDL_JoystickGetGUIDFromString(str);
  }

  /**
   * \brief Returns a joystick GUID based on the supplied string.
   *
   * \param str the string used to obtain the GUID.
   *
   * \return the obtained GUID.
   *
   * \since 5.3.0
   */
  [[nodiscard]] static auto guid_from_string(const std::string& str) noexcept
      -> SDL_JoystickGUID
  {
    return guid_from_string(str.c_str());
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
   * \return `true` if the handle holds a non-null pointer; `false` otherwise.
   *
   * \since 5.0.0
   */
  template <typename TT = T, detail::is_handle<TT> = 0>
  explicit operator bool() const noexcept
  {
    return m_joystick != nullptr;
  }

  /**
   * \brief Returns a pointer to the associated `SDL_Joystick`.
   *
   * \warning Don't take ownership of the returned pointer!
   *
   * \return a pointer to the associated `SDL_Joystick`.
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
  detail::pointer_manager<T, SDL_Joystick, deleter> m_joystick;
};

/// \name String conversions
/// \{

/**
 * \brief Returns a textual representation of a joystick.
 *
 * \tparam T the ownership semantics tag for the joystick.
 *
 * \param joystick the joystick that will be converted.
 *
 * \return a string representation of the joystick.
 *
 * \since 6.0.0
 */
template <typename T>
[[nodiscard]] auto to_string(const basic_joystick<T>& joystick) -> std::string
{
  str serial{};
  if constexpr (detail::sdl_version_at_least(2, 0, 14)) {
    serial = joystick.serial();
  }

#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("joystick{{data: {}, id: {}, name: {}, serial: {}}}",
                     detail::address_of(joystick.get()),
                     joystick.instance_id(),
                     str_or_na(joystick.name()),
                     str_or_na(joystick.serial()));
#else
  return "joystick{data: " + detail::address_of(joystick.get()) +
         ", id: " + std::to_string(joystick.instance_id()) +
         ", name: " + str_or_na(joystick.name()) + ", serial: " + str_or_na(serial) + "}";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a joystick using a stream.
 *
 * \tparam T the ownership semantics tag for the joystick.
 *
 * \param stream the stream that will be used to print the joystick.
 * \param joystick the joystick that will be printed.
 *
 * \return the used stream.
 *
 * \since 6.0.0
 */
template <typename T>
auto operator<<(std::ostream& stream, const basic_joystick<T>& joystick) -> std::ostream&
{
  return stream << to_string(joystick);
}

/// \} End of streaming

/// \} End of group input

}  // namespace cen

#endif  // CENTURION_JOYSTICK_HEADER