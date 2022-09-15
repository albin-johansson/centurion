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

#ifndef CENTURION_JOYSTICK_HPP_
#define CENTURION_JOYSTICK_HPP_

#include <SDL.h>

#include <cassert>      // assert
#include <optional>     // optional, nullopt
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

struct ball_axis_delta final
{
  int dx{};  ///< Difference in x-axis position since last poll.
  int dy{};  ///< Difference in y-axis position since last poll.
};

enum class joystick_type
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

enum class joystick_power
{
  unknown = SDL_JOYSTICK_POWER_UNKNOWN,  ///< Unknown power level.
  empty = SDL_JOYSTICK_POWER_EMPTY,      ///< Indicates <= 5% power.
  low = SDL_JOYSTICK_POWER_LOW,          ///< Indicates <= 20% power.
  medium = SDL_JOYSTICK_POWER_MEDIUM,    ///< Indicates <= 70% power.
  full = SDL_JOYSTICK_POWER_FULL,        ///< Indicates <= 100% power.
  wired = SDL_JOYSTICK_POWER_WIRED,      ///< No need to worry about power.

  max = SDL_JOYSTICK_POWER_MAX
};

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

enum class hat_state : uint8
{
  centered = SDL_HAT_CENTERED,
  up = SDL_HAT_UP,
  right = SDL_HAT_RIGHT,
  down = SDL_HAT_DOWN,
  left = SDL_HAT_LEFT,
  right_up = SDL_HAT_RIGHTUP,
  right_down = SDL_HAT_RIGHTDOWN,
  left_up = SDL_HAT_LEFTUP,
  left_down = SDL_HAT_LEFTDOWN,
};

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

#if SDL_VERSION_ATLEAST(2, 24, 0)

class virtual_joystick_desc final
{
 public:
  using update_callback = void(SDLCALL*)(void*);
  using set_player_index_callback = void(SDLCALL*)(void*, int);
  using rumble_callback = int(SDLCALL*)(void*, uint16, uint16);
  using rumble_triggers_callback = int(SDLCALL*)(void*, uint16, uint16);
  using set_led_callback = int(SDLCALL*)(void*, uint8, uint8, uint8);
  using send_effect_callback = int(SDLCALL*)(void*, const void*, int);

  virtual_joystick_desc() noexcept { mDesc.version = SDL_VIRTUAL_JOYSTICK_DESC_VERSION; }

  void set_type(const joystick_type type) noexcept { mDesc.type = static_cast<uint16>(type); }

  void set_axis_count(const uint16 n) noexcept { mDesc.naxes = n; }
  void set_button_count(const uint16 n) noexcept { mDesc.nbuttons = n; }
  void set_hat_count(const uint16 n) noexcept { mDesc.nhats = n; }

  void set_vendor_id(const uint16 id) noexcept { mDesc.vendor_id = id; }
  void set_product_id(const uint16 id) noexcept { mDesc.product_id = id; }

  void set_button_mask(const uint32 mask) noexcept { mDesc.button_mask = mask; }
  void set_axis_mask(const uint32 mask) noexcept { mDesc.axis_mask = mask; }

  void set_name(const char* name) noexcept { mDesc.name = name; }

  void set_user_data(void* data) noexcept { mDesc.userdata = data; }

  void on_update(update_callback callback) noexcept { mDesc.Update = callback; }

  void on_set_player_index(set_player_index_callback callback) noexcept
  {
    mDesc.SetPlayerIndex = callback;
  }

  void on_rumble(rumble_callback callback) noexcept { mDesc.Rumble = callback; }

  void on_rumble_triggers(rumble_triggers_callback callback) noexcept
  {
    mDesc.RumbleTriggers = callback;
  }

  void on_set_led(set_led_callback callback) noexcept { mDesc.SetLED = callback; }

  void on_send_effect(send_effect_callback callback) noexcept { mDesc.SendEffect = callback; }

  [[nodiscard]] auto data() noexcept -> SDL_VirtualJoystickDesc* { return &mDesc; }
  [[nodiscard]] auto data() const noexcept -> const SDL_VirtualJoystickDesc* { return &mDesc; }

  [[nodiscard]] auto get() noexcept -> SDL_VirtualJoystickDesc& { return mDesc; }
  [[nodiscard]] auto get() const noexcept -> const SDL_VirtualJoystickDesc& { return mDesc; }

 private:
  SDL_VirtualJoystickDesc mDesc{};
};

#endif  // SDL_VERSION_ATLEAST(2, 24, 0)

template <typename T>
class basic_joystick;

using joystick = basic_joystick<detail::owner_tag>;          ///< An owning joystick.
using joystick_handle = basic_joystick<detail::handle_tag>;  ///< A non-owning joystick.

/**
 * Represents a joystick device.
 *
 * The joystick is lower level than the game controller API, which is built on top of the
 * joystick API. As a result, the game controller API is easier to use and should be preferred
 * over the joystick API.
 *
 * \see joystick
 * \see joystick_handle
 * \see basic_controller
 */
template <typename T>
class basic_joystick final
{
 public:
  using device_index = int;
  using id_type = SDL_JoystickID;
  using guid_type = SDL_JoystickGUID;

  /**
   * Creates a joystick instance based on an existing SDL joystick.
   *
   * Ownership of the pointer is claimed if the joystick has owning semantics.
   *
   * \param joystick a pointer to an SDL joystick.
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

  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  explicit basic_joystick(const device_index index = 0) : mJoystick{SDL_JoystickOpen(index)}
  {
    if (!mJoystick) {
      throw sdl_error{};
    }
  }

  template <typename TT = T, detail::enable_for_handle<TT> = 0>
  explicit basic_joystick(const joystick& owner) noexcept : mJoystick{owner.get()}
  {}

  template <typename TT = T, detail::enable_for_handle<TT> = 0>
  [[nodiscard]] static auto from_id(const id_type id) noexcept -> joystick_handle
  {
    return joystick_handle{SDL_JoystickFromInstanceID(id)};
  }

#if SDL_VERSION_ATLEAST(2, 0, 12)

  template <typename TT = T, detail::enable_for_handle<TT> = 0>
  [[nodiscard]] static auto from_player_index(const int index) noexcept -> joystick_handle
  {
    return joystick_handle{SDL_JoystickFromPlayerIndex(index)};
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

  [[nodiscard]] auto name() const noexcept -> const char*
  {
    return SDL_JoystickName(mJoystick);
  }

  [[nodiscard]] static auto name(const device_index index) noexcept -> const char*
  {
    return SDL_JoystickNameForIndex(index);
  }

  [[nodiscard]] auto type() const noexcept -> joystick_type
  {
    return static_cast<joystick_type>(SDL_JoystickGetType(mJoystick));
  }

  [[nodiscard]] static auto type(const device_index index) noexcept -> joystick_type
  {
    return static_cast<joystick_type>(SDL_JoystickGetDeviceType(index));
  }

  [[nodiscard]] auto vendor() const noexcept -> maybe<uint16>
  {
    const auto vendor = SDL_JoystickGetVendor(mJoystick);
    if (vendor != 0) {
      return vendor;
    }
    else {
      return nothing;
    }
  }

  [[nodiscard]] static auto vendor(const device_index index) noexcept -> maybe<uint16>
  {
    const auto vendor = SDL_JoystickGetDeviceVendor(index);
    if (vendor != 0) {
      return vendor;
    }
    else {
      return nothing;
    }
  }

  [[nodiscard]] auto product() const noexcept -> maybe<uint16>
  {
    const auto product = SDL_JoystickGetProduct(mJoystick);
    if (product != 0) {
      return product;
    }
    else {
      return nothing;
    }
  }

  [[nodiscard]] static auto product(const device_index index) noexcept -> maybe<uint16>
  {
    const auto product = SDL_JoystickGetDeviceProduct(index);
    if (product != 0) {
      return product;
    }
    else {
      return nothing;
    }
  }

  [[nodiscard]] auto product_version() const noexcept -> maybe<uint16>
  {
    const auto version = SDL_JoystickGetProductVersion(mJoystick);
    if (version != 0) {
      return version;
    }
    else {
      return nothing;
    }
  }

  [[nodiscard]] static auto product_version(const device_index index) noexcept -> maybe<uint16>
  {
    const auto version = SDL_JoystickGetDeviceProductVersion(index);
    if (version != 0) {
      return version;
    }
    else {
      return nothing;
    }
  }

  [[nodiscard]] auto guid() noexcept -> guid_type { return SDL_JoystickGetGUID(mJoystick); }

  [[nodiscard]] static auto guid(const device_index index) noexcept -> guid_type
  {
    return SDL_JoystickGetDeviceGUID(index);
  }

#if SDL_VERSION_ATLEAST(2, 24, 0)

  [[nodiscard]] auto path() const noexcept -> const char*
  {
    return SDL_JoystickPath(mJoystick);
  }

  [[nodiscard]] static auto path(const device_index index) noexcept -> const char*
  {
    return SDL_JoystickPathForIndex(index);
  }

  [[nodiscard]] auto firmware_version() const noexcept -> maybe<uint16>
  {
    const auto version = SDL_JoystickGetFirmwareVersion(mJoystick);
    if (version != 0) {
      return version;
    }
    else {
      return nothing;
    }
  }

#endif  // SDL_VERSION_ATLEAST(2, 24, 0)

#if SDL_VERSION_ATLEAST(2, 0, 14)

  [[nodiscard]] auto serial() const noexcept -> const char*
  {
    return SDL_JoystickGetSerial(mJoystick);
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  [[nodiscard]] auto button_count() const noexcept -> int
  {
    return SDL_JoystickNumButtons(mJoystick);
  }

  [[nodiscard]] auto hat_count() const noexcept -> int
  {
    return SDL_JoystickNumHats(mJoystick);
  }

  [[nodiscard]] auto axis_count() const noexcept -> int
  {
    return SDL_JoystickNumAxes(mJoystick);
  }

  [[nodiscard]] auto trackball_count() const noexcept -> int
  {
    return SDL_JoystickNumBalls(mJoystick);
  }

  [[nodiscard]] auto id() const noexcept -> id_type
  {
    return SDL_JoystickInstanceID(mJoystick);
  }

  [[nodiscard]] static auto id(const device_index index) noexcept -> maybe<id_type>
  {
    const auto id = SDL_JoystickGetDeviceInstanceID(index);
    if (id != -1) {
      return id;
    }
    else {
      return nothing;
    }
  }

  [[nodiscard]] auto attached() const noexcept -> bool
  {
    return SDL_JoystickGetAttached(mJoystick);
  }

  [[nodiscard]] auto power() const noexcept -> joystick_power
  {
    return static_cast<joystick_power>(SDL_JoystickCurrentPowerLevel(mJoystick));
  }

  auto rumble(const uint16 lo,
              const uint16 hi,
              const u32ms duration) noexcept(noexcept(duration.count())) -> result
  {
    return SDL_JoystickRumble(mJoystick, lo, hi, duration.count()) == 0;
  }

  auto stop_rumble() -> result { return rumble(0, 0, u32ms::zero()); }

#if SDL_VERSION_ATLEAST(2, 0, 14)

  auto rumble_triggers(const uint16 left,
                       const uint16 right,
                       const u32ms duration) noexcept(noexcept(duration.count())) -> result
  {
    return SDL_JoystickRumbleTriggers(mJoystick, left, right, duration.count()) == 0;
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

#if SDL_VERSION_ATLEAST(2, 0, 18)

  [[nodiscard]] auto has_rumble() const noexcept -> bool
  {
    return SDL_JoystickHasRumble(mJoystick) == SDL_TRUE;
  }

  [[nodiscard]] auto has_rumble_triggers() const noexcept -> bool
  {
    return SDL_JoystickHasRumbleTriggers(mJoystick) == SDL_TRUE;
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 18)

#if SDL_VERSION_ATLEAST(2, 0, 14)

  auto set_led(const color& color) noexcept -> result
  {
    return SDL_JoystickSetLED(mJoystick, color.red(), color.green(), color.blue()) == 0;
  }

  [[nodiscard]] auto has_led() const noexcept -> bool
  {
    return SDL_JoystickHasLED(mJoystick) == SDL_TRUE;
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

#if SDL_VERSION_ATLEAST(2, 24, 0)

  [[nodiscard]] static auto attach_virtual(const virtual_joystick_desc& desc) noexcept
      -> maybe<device_index>
  {
    const auto index = SDL_JoystickAttachVirtualEx(desc.data());
    if (index != -1) {
      return index;
    }
    else {
      return nothing;
    }
  }

#endif  // SDL_VERSION_ATLEAST(2, 24, 0)

#if SDL_VERSION_ATLEAST(2, 0, 14)

  [[nodiscard]] static auto attach_virtual(const joystick_type type,
                                           const int axes,
                                           const int buttons,
                                           const int hats) noexcept -> maybe<device_index>
  {
    const auto index =
        SDL_JoystickAttachVirtual(static_cast<SDL_JoystickType>(type), axes, buttons, hats);
    if (index != -1) {
      return index;
    }
    else {
      return nothing;
    }
  }

  static auto detach_virtual(const device_index index) noexcept -> result
  {
    return SDL_JoystickDetachVirtual(index) == 0;
  }

  auto set_virtual_axis(const int axis, const int16 value) noexcept -> result
  {
    return SDL_JoystickSetVirtualAxis(mJoystick, axis, value) == 0;
  }

  auto set_virtual_button(const int button, const button_state state) noexcept -> result
  {
    return SDL_JoystickSetVirtualButton(mJoystick, button, to_underlying(state)) == 0;
  }

  auto set_virtual_hat(const int hat, const hat_state state) noexcept -> result
  {
    return SDL_JoystickSetVirtualHat(mJoystick, hat, to_underlying(state)) == 0;
  }

  [[nodiscard]] static auto is_virtual(const device_index index) noexcept -> bool
  {
    return SDL_JoystickIsVirtual(index) == SDL_TRUE;
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  [[nodiscard]] auto query_button(const int button) const noexcept -> button_state
  {
    return static_cast<button_state>(SDL_JoystickGetButton(mJoystick, button));
  }

  [[nodiscard]] auto query_hat(const int hat) const noexcept -> hat_state
  {
    return static_cast<hat_state>(SDL_JoystickGetHat(mJoystick, hat));
  }

  [[nodiscard]] auto query_axis(const int axis) const noexcept -> int16
  {
    return SDL_JoystickGetAxis(mJoystick, axis);
  }

  [[nodiscard]] auto axis_initial_state(const int axis) const noexcept -> maybe<int16>
  {
    int16 state{};
    if (SDL_JoystickGetAxisInitialState(mJoystick, axis, &state)) {
      return state;
    }
    else {
      return nothing;
    }
  }

  [[nodiscard]] auto get_ball_axis_delta(const int ball) const noexcept
      -> maybe<ball_axis_delta>
  {
    ball_axis_delta change{};
    if (SDL_JoystickGetBall(mJoystick, ball, &change.dx, &change.dy) == 0) {
      return change;
    }
    else {
      return nothing;
    }
  }

#if SDL_VERSION_ATLEAST(2, 0, 16)

  auto send_effect(const void* data, const int size) -> result
  {
    return SDL_JoystickSendEffect(mJoystick, data, size) == 0;
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 16)

#if SDL_VERSION_ATLEAST(2, 0, 12)

  void set_player_index(const int index) noexcept
  {
    SDL_JoystickSetPlayerIndex(mJoystick, index);
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

  [[nodiscard]] auto player_index() const noexcept -> maybe<int>
  {
    const auto index = SDL_JoystickGetPlayerIndex(mJoystick);
    if (index != -1) {
      return index;
    }
    else {
      return nothing;
    }
  }

  [[nodiscard]] static auto player_index(const device_index index) noexcept -> maybe<int>
  {
    const auto player = SDL_JoystickGetDevicePlayerIndex(index);
    if (player != -1) {
      return player;
    }
    else {
      return nothing;
    }
  }

  [[nodiscard]] static auto to_guid(const char* str) noexcept -> guid_type
  {
    assert(str);
    return SDL_JoystickGetGUIDFromString(str);
  }

  [[nodiscard]] static auto to_guid(const std::string& str) noexcept -> guid_type
  {
    return to_guid(str.c_str());
  }

  static void lock() noexcept { SDL_LockJoysticks(); }

  static void unlock() noexcept { SDL_UnlockJoysticks(); }

  static void update() noexcept { SDL_JoystickUpdate(); }

  static void set_polling(const bool enabled) noexcept
  {
    SDL_JoystickEventState(enabled ? SDL_ENABLE : SDL_DISABLE);
  }

  [[nodiscard]] static auto polling() noexcept -> bool
  {
    return SDL_JoystickEventState(SDL_QUERY);
  }

  [[nodiscard]] static auto count() noexcept -> maybe<int>
  {
    const auto result = SDL_NumJoysticks();
    if (result >= 0) {
      return result;
    }
    else {
      return nothing;
    }
  }

  [[nodiscard]] constexpr static auto axis_max() noexcept -> int16
  {
    return SDL_JOYSTICK_AXIS_MAX;
  }

  [[nodiscard]] constexpr static auto axis_min() noexcept -> int16
  {
    return SDL_JOYSTICK_AXIS_MIN;
  }

  /// Indicates whether a handle holds a non-null pointer.
  template <typename TT = T, detail::enable_for_handle<TT> = 0>
  explicit operator bool() const noexcept
  {
    return mJoystick != nullptr;
  }

  [[nodiscard]] auto get() const noexcept -> SDL_Joystick* { return mJoystick.get(); }

 private:
  detail::pointer<T, SDL_Joystick> mJoystick;
};

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

}  // namespace cen

#endif  // CENTURION_JOYSTICK_HPP_