#ifndef CENTURION_INPUT_JOYSTICK_HPP_
#define CENTURION_INPUT_JOYSTICK_HPP_

#include <SDL.h>

#include <cassert>      // assert
#include <optional>     // optional
#include <ostream>      // ostream
#include <string>       // string, to_string
#include <string_view>  // string_view

#include "../color.hpp"
#include "../common.hpp"
#include "../features.hpp"
#include "../detail/owner_handle_api.hpp"
#include "../detail/sdl_version_at_least.hpp"
#include "../detail/stdlib.hpp"
#include "button_state.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen {

/// \addtogroup input
/// \{

enum class JoystickType {
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

enum class JoystickPower {
  Unknown = SDL_JOYSTICK_POWER_UNKNOWN,  ///< Unknown power level.
  Empty = SDL_JOYSTICK_POWER_EMPTY,      ///< Indicates <= 5% power.
  Low = SDL_JOYSTICK_POWER_LOW,          ///< Indicates <= 20% power.
  Medium = SDL_JOYSTICK_POWER_MEDIUM,    ///< Indicates <= 70% power.
  Full = SDL_JOYSTICK_POWER_FULL,        ///< Indicates <= 100% power.
  Wired = SDL_JOYSTICK_POWER_WIRED,      ///< No need to worry about power.
  Max = SDL_JOYSTICK_POWER_MAX
};

enum class HatState : Uint8 {
  Centered = SDL_HAT_CENTERED,    ///< The hat is centered.
  Up = SDL_HAT_UP,                ///< The hat is directed "north".
  Right = SDL_HAT_RIGHT,          ///< The hat is directed "east".
  Down = SDL_HAT_DOWN,            ///< The hat is directed "south".
  Left = SDL_HAT_LEFT,            ///< The hat is directed "west".
  RightUp = SDL_HAT_RIGHTUP,      ///< The hat is directed "north-east".
  RightDown = SDL_HAT_RIGHTDOWN,  ///< The hat is directed "south-east".
  LeftUp = SDL_HAT_LEFTUP,        ///< The hat is directed "north-west".
  LeftDown = SDL_HAT_LEFTDOWN,    ///< The hat is directed "south-west".
};

struct BallAxisChange final {
  int dx{};  ///< Difference in x-axis position since last poll.
  int dy{};  ///< Difference in y-axis position since last poll.
};

template <typename T>
class BasicJoystick;

using Joystick = BasicJoystick<detail::OwnerTag>;
using JoystickHandle = BasicJoystick<detail::HandleTag>;

template <typename T>
class BasicJoystick final {
 public:
  explicit BasicJoystick(MaybeOwner<SDL_Joystick*> joystick) noexcept(detail::is_handle<T>)
      : mJoystick{joystick}
  {
    if constexpr (detail::is_owner<T>) {
      if (!mJoystick) {
        throw Error{"Cannot create joystick from null pointer!"};
      }
    }
  }

  template <typename TT = T, detail::EnableOwner<TT> = 0>
  explicit BasicJoystick(const int index = 0) : mJoystick{SDL_JoystickOpen(index)}
  {
    if (!mJoystick) {
      throw SDLError{};
    }
  }

  template <typename TT = T, detail::EnableHandle<TT> = 0>
  explicit BasicJoystick(const Joystick& owner) noexcept : mJoystick{owner.get()}
  {}

  template <typename TT = T, detail::EnableHandle<TT> = 0>
  [[nodiscard]] static auto FromID(const SDL_JoystickID id) noexcept -> JoystickHandle
  {
    return JoystickHandle{SDL_JoystickFromInstanceID(id)};
  }

#if SDL_VERSION_ATLEAST(2, 0, 12)

  template <typename TT = T, detail::EnableHandle<TT> = 0>
  [[nodiscard]] static auto FromPlayerIndex(const int index) noexcept -> JoystickHandle
  {
    return JoystickHandle{SDL_JoystickFromPlayerIndex(index)};
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

  auto Rumble(const Uint16 lowFreq,
              const Uint16 highFreq,
              const U32_Millis duration) noexcept(noexcept(duration.count())) -> Result
  {
    return SDL_JoystickRumble(mJoystick, lowFreq, highFreq, duration.count()) == 0;
  }

#if SDL_VERSION_ATLEAST(2, 0, 14)

  auto RumbleTriggers(const Uint16 left,
                      const Uint16 right,
                      const U32_Millis duration) noexcept(noexcept(duration.count())) -> Result
  {
    return SDL_JoystickRumbleTriggers(mJoystick, left, right, duration.count()) == 0;
  }

  auto SetLED(const Color& color) noexcept -> Result
  {
    return SDL_JoystickSetLED(mJoystick, color.GetRed(), color.GetGreen(), color.GetBlue()) ==
           0;
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

#if SDL_VERSION_ATLEAST(2, 0, 12)

  /* Sets the player index associated with the joystick. */
  void SetPlayerIndex(const int index) noexcept
  {
    SDL_JoystickSetPlayerIndex(mJoystick, index);
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

#if SDL_VERSION_ATLEAST(2, 0, 16)

  /* Sends a packet of joystick specific data. */
  auto SendEffect(const void* data, const int size) -> Result
  {
    return SDL_JoystickSendEffect(mJoystick, data, size) == 0;
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 16)

#if SDL_VERSION_ATLEAST(2, 0, 14)

  /* Attaches a new virtual joystick, returns the device index. */
  [[nodiscard]] static auto AttachVirtual(const JoystickType type,
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

  /* Detaches a virtual joystick. */
  static auto DetachVirtual(const int index) noexcept -> Result
  {
    return SDL_JoystickDetachVirtual(index) == 0;
  }

  auto SetVirtualAxis(const int axis, const Sint16 value) noexcept -> Result
  {
    return SDL_JoystickSetVirtualAxis(mJoystick, axis, value) == 0;
  }

  auto SetVirtualButton(const int button, const ButtonState state) noexcept -> Result
  {
    return SDL_JoystickSetVirtualButton(mJoystick, button, ToUnderlying(state)) == 0;
  }

  auto SetVirtualHat(const int hat, const HatState state) noexcept -> Result
  {
    return SDL_JoystickSetVirtualHat(mJoystick, hat, ToUnderlying(state)) == 0;
  }

  [[nodiscard]] static auto IsVirtual(const int index) noexcept -> bool
  {
    return SDL_JoystickIsVirtual(index) == SDL_TRUE;
  }

#endif  // #if SDL_VERSION_ATLEAST(2, 0, 14)

  [[nodiscard]] auto GetPlayerIndex() const noexcept -> std::optional<int>
  {
    const auto index = SDL_JoystickGetPlayerIndex(mJoystick);
    if (index != -1) {
      return index;
    }
    else {
      return std::nullopt;
    }
  }

  [[nodiscard]] auto GetType() const noexcept -> JoystickType
  {
    return static_cast<JoystickType>(SDL_JoystickGetType(mJoystick));
  }

  [[nodiscard]] auto GetVendor() const noexcept -> std::optional<Uint16>
  {
    const auto vendor = SDL_JoystickGetVendor(mJoystick);
    if (vendor != 0) {
      return vendor;
    }
    else {
      return std::nullopt;
    }
  }

  [[nodiscard]] auto GetProduct() const noexcept -> std::optional<Uint16>
  {
    const auto product = SDL_JoystickGetProduct(mJoystick);
    if (product != 0) {
      return product;
    }
    else {
      return std::nullopt;
    }
  }

  [[nodiscard]] auto GetProductVersion() const noexcept -> std::optional<Uint16>
  {
    const auto version = SDL_JoystickGetProductVersion(mJoystick);
    if (version != 0) {
      return version;
    }
    else {
      return std::nullopt;
    }
  }

  [[nodiscard]] auto GetGUID() noexcept -> SDL_JoystickGUID
  {
    return SDL_JoystickGetGUID(mJoystick);
  }

  [[nodiscard]] auto GetID() const noexcept -> SDL_JoystickID
  {
    return SDL_JoystickInstanceID(mJoystick);
  }

  [[nodiscard]] auto GetName() const noexcept -> const char*
  {
    return SDL_JoystickName(mJoystick);
  }

#if SDL_VERSION_ATLEAST(2, 0, 14)

  [[nodiscard]] auto GetSerial() const noexcept -> const char*
  {
    return SDL_JoystickGetSerial(mJoystick);
  }

  [[nodiscard]] auto HasLED() const noexcept -> bool
  {
    return SDL_JoystickHasLED(mJoystick) == SDL_TRUE;
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  [[nodiscard]] static auto GetPlayerIndex(const int deviceIndex) noexcept
      -> std::optional<int>
  {
    const auto index = SDL_JoystickGetDevicePlayerIndex(deviceIndex);
    if (index != -1) {
      return index;
    }
    else {
      return std::nullopt;
    }
  }

  [[nodiscard]] static auto GetType(const int deviceIndex) noexcept -> JoystickType
  {
    return static_cast<JoystickType>(SDL_JoystickGetDeviceType(deviceIndex));
  }

  [[nodiscard]] static auto GetVendor(const int deviceIndex) noexcept -> std::optional<Uint16>
  {
    const auto vendor = SDL_JoystickGetDeviceVendor(deviceIndex);
    if (vendor != 0) {
      return vendor;
    }
    else {
      return std::nullopt;
    }
  }

  [[nodiscard]] static auto GetProduct(const int deviceIndex) noexcept -> std::optional<Uint16>
  {
    const auto product = SDL_JoystickGetDeviceProduct(deviceIndex);
    if (product != 0) {
      return product;
    }
    else {
      return std::nullopt;
    }
  }

  [[nodiscard]] static auto GetProductVersion(const int deviceIndex) noexcept
      -> std::optional<Uint16>
  {
    const auto version = SDL_JoystickGetDeviceProductVersion(deviceIndex);
    if (version != 0) {
      return version;
    }
    else {
      return std::nullopt;
    }
  }

  [[nodiscard]] static auto GetGUID(const int deviceIndex) noexcept -> SDL_JoystickGUID
  {
    return SDL_JoystickGetDeviceGUID(deviceIndex);
  }

  [[nodiscard]] static auto GetID(const int deviceIndex) noexcept
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

  [[nodiscard]] static auto GetName(const int deviceIndex) noexcept -> const char*
  {
    return SDL_JoystickNameForIndex(deviceIndex);
  }

  [[nodiscard]] auto GetBallAxisChange(const int ball) const noexcept
      -> std::optional<BallAxisChange>
  {
    BallAxisChange change{};
    if (SDL_JoystickGetBall(mJoystick, ball, &change.dx, &change.dy) == 0) {
      return change;
    }
    else {
      return std::nullopt;
    }
  }

  [[nodiscard]] auto GetAxis(const int axis) const noexcept -> Sint16
  {
    return SDL_JoystickGetAxis(mJoystick, axis);
  }

  [[nodiscard]] auto GetAxisInitialState(const int axis) const noexcept
      -> std::optional<Sint16>
  {
    Sint16 state{};
    if (SDL_JoystickGetAxisInitialState(mJoystick, axis, &state)) {
      return state;
    }
    else {
      return std::nullopt;
    }
  }

  [[nodiscard]] auto IsAttached() const noexcept -> bool
  {
    return SDL_JoystickGetAttached(mJoystick);
  }

  [[nodiscard]] auto GetHats() const noexcept -> int { return SDL_JoystickNumHats(mJoystick); }

  [[nodiscard]] auto GetAxes() const noexcept -> int { return SDL_JoystickNumAxes(mJoystick); }

  [[nodiscard]] auto GetTrackballs() const noexcept -> int
  {
    return SDL_JoystickNumBalls(mJoystick);
  }

  [[nodiscard]] auto GetButtons() const noexcept -> int
  {
    return SDL_JoystickNumButtons(mJoystick);
  }

  [[nodiscard]] auto GetPower() const noexcept -> JoystickPower
  {
    return static_cast<JoystickPower>(SDL_JoystickCurrentPowerLevel(mJoystick));
  }

  [[nodiscard]] auto GetButtonState(const int button) const noexcept -> ButtonState
  {
    return static_cast<ButtonState>(SDL_JoystickGetButton(mJoystick, button));
  }

  [[nodiscard]] auto GetHatState(const int hat) const noexcept -> HatState
  {
    return static_cast<HatState>(SDL_JoystickGetHat(mJoystick, hat));
  }

  /* Updates the state of all open joysticks. */
  static void Update() noexcept { SDL_JoystickUpdate(); }

  static void Lock() noexcept { SDL_LockJoysticks(); }

  static void Unlock() noexcept { SDL_UnlockJoysticks(); }

  static void SetPolling(const bool enabled) noexcept
  {
    SDL_JoystickEventState(enabled ? SDL_ENABLE : SDL_DISABLE);
  }

  [[nodiscard]] static auto IsPolling() noexcept -> bool
  {
    return SDL_JoystickEventState(SDL_QUERY);
  }

  [[nodiscard]] static auto GetAmount() noexcept -> std::optional<int>
  {
    const auto result = SDL_NumJoysticks();
    if (result >= 0) {
      return result;
    }
    else {
      return std::nullopt;
    }
  }

  [[nodiscard]] static auto GetGUID(const char* str) noexcept -> SDL_JoystickGUID
  {
    assert(str);
    return SDL_JoystickGetGUIDFromString(str);
  }

  [[nodiscard]] static auto GetGUID(const std::string& str) noexcept -> SDL_JoystickGUID
  {
    return GetGUID(str.c_str());
  }

  [[nodiscard]] constexpr static auto GetAxisMax() noexcept -> Sint16
  {
    return SDL_JOYSTICK_AXIS_MAX;
  }

  [[nodiscard]] constexpr static auto GetAxisMin() noexcept -> Sint16
  {
    return SDL_JOYSTICK_AXIS_MIN;
  }

  template <typename TT = T, detail::EnableHandle<TT> = 0>
  explicit operator bool() const noexcept
  {
    return mJoystick != nullptr;
  }

  [[nodiscard]] auto get() const noexcept -> SDL_Joystick* { return mJoystick.get(); }

 private:
  detail::Pointer<T, SDL_Joystick> mJoystick;
};

[[nodiscard]] constexpr auto to_string(const JoystickType type) -> std::string_view
{
  switch (type) {
    case JoystickType::Unknown:
      return "Unknown";

    case JoystickType::GameController:
      return "GameController";

    case JoystickType::Wheel:
      return "Wheel";

    case JoystickType::ArcadeStick:
      return "ArcadeStick";

    case JoystickType::FlightStick:
      return "FlightStick";

    case JoystickType::DancePad:
      return "DancePad";

    case JoystickType::Guitar:
      return "Guitar";

    case JoystickType::DrumKit:
      return "DrumKit";

    case JoystickType::ArcadePad:
      return "ArcadePad";

    case JoystickType::Throttle:
      return "Throttle";

    default:
      throw Error{"Did not recognize joystick type!"};
  }
}

inline auto operator<<(std::ostream& stream, const JoystickType type) -> std::ostream&
{
  return stream << to_string(type);
}

[[nodiscard]] constexpr auto to_string(const JoystickPower power) -> std::string_view
{
  switch (power) {
    case JoystickPower::Unknown:
      return "Unknown";

    case JoystickPower::Empty:
      return "Empty";

    case JoystickPower::Low:
      return "Low";

    case JoystickPower::Medium:
      return "Medium";

    case JoystickPower::Full:
      return "Full";

    case JoystickPower::Wired:
      return "Wired";

    case JoystickPower::Max:
      return "Max";

    default:
      throw Error{"Did not recognize joystick power!"};
  }
}

inline auto operator<<(std::ostream& stream, const JoystickPower power) -> std::ostream&
{
  return stream << to_string(power);
}

[[nodiscard]] constexpr auto to_string(const HatState state) -> std::string_view
{
  switch (state) {
    case HatState::Centered:
      return "Centered";

    case HatState::Up:
      return "Up";

    case HatState::Right:
      return "Right";

    case HatState::Down:
      return "Down";

    case HatState::Left:
      return "Left";

    case HatState::RightUp:
      return "RightUp";

    case HatState::RightDown:
      return "RightDown";

    case HatState::LeftUp:
      return "LeftUp";

    case HatState::LeftDown:
      return "LeftDown";

    default:
      throw Error{"Did not recognize hat state!"};
  }
}

inline auto operator<<(std::ostream& stream, const HatState state) -> std::ostream&
{
  return stream << to_string(state);
}

template <typename T>
[[nodiscard]] auto to_string(const BasicJoystick<T>& joystick) -> std::string
{
  const char* serial{};
  if constexpr (detail::sdl_version_at_least(2, 0, 14)) {
    serial = joystick.GetSerial();
  }

#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("Joystick(data: {}, id: {}, name: {}, serial: {})",
                     detail::address_of(joystick.get()),
                     joystick.GetID(),
                     str_or_na(joystick.GetName()),
                     str_or_na(serial));
#else
  return "Joystick(data: " + detail::address_of(joystick.get()) +
         ", id: " + std::to_string(joystick.GetID()) +
         ", name: " + str_or_na(joystick.GetName()) + ", serial: " + str_or_na(serial) + ")";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

template <typename T>
auto operator<<(std::ostream& stream, const BasicJoystick<T>& joystick) -> std::ostream&
{
  return stream << to_string(joystick);
}

}  // namespace cen

#endif  // CENTURION_JOYSTICK_HPP_