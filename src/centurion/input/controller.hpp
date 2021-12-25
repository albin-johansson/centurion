#ifndef CENTURION_INPUT_CONTROLLER_HPP_
#define CENTURION_INPUT_CONTROLLER_HPP_

#include <SDL.h>

#include <array>        // array
#include <cassert>      // assert
#include <cstddef>      // size_t
#include <optional>     // optional
#include <ostream>      // ostream
#include <string>       // string
#include <string_view>  // string_view

#include "../color.hpp"
#include "../common.hpp"
#include "../core/sdl_string.hpp"
#include "../detail/owner_handle_api.hpp"
#include "../detail/sdl_version_at_least.hpp"
#include "../detail/stdlib.hpp"
#include "../features.hpp"
#include "button_state.hpp"
#include "joystick.hpp"
#include "sensor.hpp"
#include "touch.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen {

enum class ControllerButton {
  Invalid = SDL_CONTROLLER_BUTTON_INVALID,

  A = SDL_CONTROLLER_BUTTON_A,
  B = SDL_CONTROLLER_BUTTON_B,
  X = SDL_CONTROLLER_BUTTON_X,
  Y = SDL_CONTROLLER_BUTTON_Y,

  Back = SDL_CONTROLLER_BUTTON_BACK,
  Guide = SDL_CONTROLLER_BUTTON_GUIDE,
  Start = SDL_CONTROLLER_BUTTON_START,

  LeftStick = SDL_CONTROLLER_BUTTON_LEFTSTICK,
  RightStick = SDL_CONTROLLER_BUTTON_RIGHTSTICK,
  LeftShoulder = SDL_CONTROLLER_BUTTON_LEFTSHOULDER,
  RightShoulder = SDL_CONTROLLER_BUTTON_RIGHTSHOULDER,

  DpadUp = SDL_CONTROLLER_BUTTON_DPAD_UP,
  DpadDown = SDL_CONTROLLER_BUTTON_DPAD_DOWN,
  DpadLeft = SDL_CONTROLLER_BUTTON_DPAD_LEFT,
  DpadRight = SDL_CONTROLLER_BUTTON_DPAD_RIGHT,

#if SDL_VERSION_ATLEAST(2, 0, 14)

  Misc1 = SDL_CONTROLLER_BUTTON_MISC1,

  Paddle1 = SDL_CONTROLLER_BUTTON_PADDLE1,
  Paddle2 = SDL_CONTROLLER_BUTTON_PADDLE2,
  Paddle3 = SDL_CONTROLLER_BUTTON_PADDLE3,
  Paddle4 = SDL_CONTROLLER_BUTTON_PADDLE4,
  Touchpad = SDL_CONTROLLER_BUTTON_TOUCHPAD,

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  Max = SDL_CONTROLLER_BUTTON_MAX
};

enum class ControllerAxis {
  Invalid = SDL_CONTROLLER_AXIS_INVALID,

  LeftX = SDL_CONTROLLER_AXIS_LEFTX,
  LeftY = SDL_CONTROLLER_AXIS_LEFTY,
  RightX = SDL_CONTROLLER_AXIS_RIGHTX,
  RightY = SDL_CONTROLLER_AXIS_RIGHTY,

  TriggerLeft = SDL_CONTROLLER_AXIS_TRIGGERLEFT,
  TriggerRight = SDL_CONTROLLER_AXIS_TRIGGERRIGHT,

  Max = SDL_CONTROLLER_AXIS_MAX
};

enum class ControllerBindType {
  None = SDL_CONTROLLER_BINDTYPE_NONE,
  Button = SDL_CONTROLLER_BINDTYPE_BUTTON,
  Axis = SDL_CONTROLLER_BINDTYPE_AXIS,
  Hat = SDL_CONTROLLER_BINDTYPE_HAT
};

#if SDL_VERSION_ATLEAST(2, 0, 12)

enum class ControllerType {
  Unknown = SDL_CONTROLLER_TYPE_UNKNOWN,

  Xbox360 = SDL_CONTROLLER_TYPE_XBOX360,
  XboxOne = SDL_CONTROLLER_TYPE_XBOXONE,
  PS3 = SDL_CONTROLLER_TYPE_PS3,
  PS4 = SDL_CONTROLLER_TYPE_PS4,
  NintendoSwitchPro = SDL_CONTROLLER_TYPE_NINTENDO_SWITCH_PRO,

#if SDL_VERSION_ATLEAST(2, 0, 14)

  PS5 = SDL_CONTROLLER_TYPE_PS5,
  Virtual = SDL_CONTROLLER_TYPE_VIRTUAL,

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

#if SDL_VERSION_ATLEAST(2, 0, 16)

  AmazonLuna = SDL_CONTROLLER_TYPE_AMAZON_LUNA,
  GoogleStadia = SDL_CONTROLLER_TYPE_GOOGLE_STADIA

#endif  // SDL_VERSION_ATLEAST(2, 0, 16)
};

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

enum class ControllerMappingResult {
  Error,
  Updated,
  Added
};

template <typename T>
class BasicController;

using Controller = BasicController<detail::OwnerTag>;
using ControllerHandle = BasicController<detail::HandleTag>;

template <typename T>
class BasicController final {
 public:
  using MappingIndex = int;
  using JoystickIndex = int;
  using PlayerIndex = int;

  // clang-format off

  explicit BasicController(MaybeOwner<SDL_GameController*> controller) noexcept(detail::is_handle<T>)
      : mController{controller}
  {
    if constexpr (detail::is_owner<T>) {
      if (!mController) {
        throw Error{"Cannot create controller from null pointer!"};
      }
    }
  }

  // clang-format on

  template <typename TT = T, detail::EnableHandle<TT> = 0>
  explicit BasicController(const Controller& owner) noexcept : mController{owner.get()}
  {}

  template <typename TT = T, detail::EnableOwner<TT> = 0>
  explicit BasicController(const int index = 0) : mController{SDL_GameControllerOpen(index)}
  {
    if (!mController) {
      throw SDLError{};
    }
  }

  template <typename TT = T, detail::EnableOwner<TT> = 0>
  [[nodiscard]] static auto FromJoystick(const SDL_JoystickID id) -> BasicController
  {
    if (auto* ptr = SDL_GameControllerFromInstanceID(id)) {
      return BasicController{ptr};
    }
    else {
      throw SDLError{};
    }
  }

#if SDL_VERSION_ATLEAST(2, 0, 12)

  template <typename TT = T, detail::EnableOwner<TT> = 0>
  [[nodiscard]] static auto FromIndex(const PlayerIndex index) -> BasicController
  {
    if (auto* ptr = SDL_GameControllerFromPlayerIndex(index)) {
      return BasicController{ptr};
    }
    else {
      throw SDLError{};
    }
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

  auto Rumble(const Uint16 lo,
              const Uint16 hi,
              const U32_Millis duration) noexcept(noexcept(duration.count())) -> Result
  {
    return SDL_GameControllerRumble(mController, lo, hi, duration.count()) == 0;
  }

  void StopRumble() { Rumble(0, 0, U32_Millis::zero()); }

  [[nodiscard]] auto GetVendor() const noexcept -> std::optional<Uint16>
  {
    const auto id = SDL_GameControllerGetVendor(mController);
    if (id != 0) {
      return id;
    }
    else {
      return std::nullopt;
    }
  }

  [[nodiscard]] auto GetProduct() const noexcept -> std::optional<Uint16>
  {
    const auto id = SDL_GameControllerGetProduct(mController);
    if (id != 0) {
      return id;
    }
    else {
      return std::nullopt;
    }
  }

  [[nodiscard]] auto GetProductVersion() const noexcept -> std::optional<Uint16>
  {
    const auto id = SDL_GameControllerGetProductVersion(mController);
    if (id != 0) {
      return id;
    }
    else {
      return std::nullopt;
    }
  }

  [[nodiscard]] auto GetIndex() const noexcept -> std::optional<PlayerIndex>
  {
    const auto result = SDL_GameControllerGetPlayerIndex(mController);
    if (result != -1) {
      return result;
    }
    else {
      return std::nullopt;
    }
  }

  [[nodiscard]] auto GetName() const noexcept -> const char*
  {
    return SDL_GameControllerName(mController);
  }

  [[nodiscard]] auto GetJoystick() noexcept -> JoystickHandle
  {
    return JoystickHandle{SDL_GameControllerGetJoystick(mController)};
  }

  [[nodiscard]] auto GetAxis(const ControllerAxis axis) const noexcept -> Sint16
  {
    return SDL_GameControllerGetAxis(mController, static_cast<SDL_GameControllerAxis>(axis));
  }

  [[nodiscard]] auto GetState(const ControllerButton button) const noexcept -> ButtonState
  {
    const auto state =
        SDL_GameControllerGetButton(mController,
                                    static_cast<SDL_GameControllerButton>(button));
    return static_cast<ButtonState>(state);
  }

  [[nodiscard]] auto IsPressed(const ControllerButton button) const noexcept -> bool
  {
    return GetState(button) == ButtonState::Pressed;
  }

  [[nodiscard]] auto IsReleased(const ControllerButton button) const noexcept -> bool
  {
    return GetState(button) == ButtonState::Released;
  }

  [[nodiscard]] auto IsConnected() const noexcept -> bool
  {
    return SDL_GameControllerGetAttached(mController) == SDL_TRUE;
  }

  [[nodiscard]] auto GetBinding(const ControllerAxis axis) const
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

  [[nodiscard]] auto GetBinding(const ControllerButton button) noexcept
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

  [[nodiscard]] auto GetMapping() const noexcept -> sdl_string
  {
    return sdl_string{SDL_GameControllerMapping(mController)};
  }

  static void Update() { SDL_GameControllerUpdate(); }

  static void SetPolling(const bool polling) noexcept
  {
    SDL_GameControllerEventState(polling ? SDL_ENABLE : SDL_DISABLE);
  }

  [[nodiscard]] static auto IsPolling() noexcept -> bool
  {
    return SDL_GameControllerEventState(SDL_QUERY);
  }

  [[nodiscard]] static auto IsSupported(const JoystickIndex index) noexcept -> bool
  {
    return SDL_IsGameController(index) == SDL_TRUE;
  }

  [[nodiscard]] static auto GetButton(const char* str) noexcept -> ControllerButton
  {
    assert(str);
    return static_cast<ControllerButton>(SDL_GameControllerGetButtonFromString(str));
  }

  [[nodiscard]] static auto GetButton(const std::string& str) noexcept -> ControllerButton
  {
    return GetButton(str.c_str());
  }

  [[nodiscard]] static auto GetAxis(const char* str) noexcept -> ControllerAxis
  {
    assert(str);
    return static_cast<ControllerAxis>(SDL_GameControllerGetAxisFromString(str));
  }

  [[nodiscard]] static auto GetAxis(const std::string& str) noexcept -> ControllerAxis
  {
    return GetAxis(str.c_str());
  }

  [[nodiscard]] static auto Stringify(const ControllerAxis axis) noexcept -> const char*
  {
    return SDL_GameControllerGetStringForAxis(static_cast<SDL_GameControllerAxis>(axis));
  }

  [[nodiscard]] static auto Stringify(const ControllerButton button) noexcept -> const char*
  {
    return SDL_GameControllerGetStringForButton(static_cast<SDL_GameControllerButton>(button));
  }

  [[nodiscard]] static auto GetMapping(const JoystickIndex index) noexcept -> sdl_string
  {
    return sdl_string{SDL_GameControllerMappingForDeviceIndex(index)};
  }

  [[nodiscard]] static auto GetMapping(const SDL_JoystickGUID guid) noexcept -> sdl_string
  {
    return sdl_string{SDL_GameControllerMappingForGUID(guid)};
  }

  [[nodiscard]] static auto GetMappingByIndex(const MappingIndex index) noexcept -> sdl_string
  {
    return sdl_string{SDL_GameControllerMappingForIndex(index)};
  }

  [[nodiscard]] static auto GetAmount() noexcept -> int
  {
    const auto joysticks = SDL_NumJoysticks();

    auto amount = 0;
    for (auto i = 0; i < joysticks; ++i) {
      if (IsSupported(i)) {
        ++amount;
      }
    }

    return amount;
  }

#if SDL_VERSION_ATLEAST(2, 0, 12)

  void SetPlayerIndex(const PlayerIndex index) noexcept
  {
    SDL_GameControllerSetPlayerIndex(mController, index);
  }

  [[nodiscard]] auto GetType() const noexcept -> ControllerType
  {
    return static_cast<ControllerType>(SDL_GameControllerGetType(mController));
  }

  [[nodiscard]] static auto GetType(const JoystickIndex index) noexcept -> ControllerType
  {
    return static_cast<ControllerType>(SDL_GameControllerTypeForIndex(index));
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

#if SDL_VERSION_ATLEAST(2, 0, 14)

  auto RumbleTriggers(const Uint16 lo,
                      const Uint16 hi,
                      const U32_Millis duration) noexcept(noexcept(duration.count())) -> Result
  {
    return SDL_GameControllerRumbleTriggers(mController, lo, hi, duration.count()) == 0;
  }

  auto SetLED(const Color& color) noexcept -> Result
  {
    return SDL_GameControllerSetLED(mController,
                                    color.GetRed(),
                                    color.GetGreen(),
                                    color.GetBlue()) == 0;
  }

  auto SetSensorEnabled(const sensor_type type, const bool enabled) noexcept -> Result
  {
    const auto value = static_cast<SDL_SensorType>(type);
    const auto state = enabled ? SDL_TRUE : SDL_FALSE;
    return SDL_GameControllerSetSensorEnabled(mController, value, state) == 0;
  }

  [[nodiscard]] auto GetSerial() const noexcept -> const char*
  {
    return SDL_GameControllerGetSerial(mController);
  }

  [[nodiscard]] auto HasLED() const noexcept -> bool
  {
    return SDL_GameControllerHasLED(mController) == SDL_TRUE;
  }

  [[nodiscard]] auto HasSensor(const sensor_type type) const noexcept -> bool
  {
    const auto value = static_cast<SDL_SensorType>(type);
    return SDL_GameControllerHasSensor(mController, value) == SDL_TRUE;
  }

  [[nodiscard]] auto HasAxis(const ControllerAxis axis) const noexcept -> bool
  {
    const auto value = static_cast<SDL_GameControllerAxis>(axis);
    return SDL_GameControllerHasAxis(mController, value) == SDL_TRUE;
  }

  [[nodiscard]] auto HasButton(const ControllerButton button) const noexcept -> bool
  {
    const auto value = static_cast<SDL_GameControllerButton>(button);
    return SDL_GameControllerHasButton(mController, value) == SDL_TRUE;
  }

  [[nodiscard]] auto IsSensorEnabled(const sensor_type type) const noexcept -> bool
  {
    const auto value = static_cast<SDL_SensorType>(type);
    return SDL_GameControllerIsSensorEnabled(mController, value) == SDL_TRUE;
  }

  [[nodiscard]] auto GetNumTouchpads() const noexcept -> int
  {
    return SDL_GameControllerGetNumTouchpads(mController);
  }

  [[nodiscard]] auto GetTouchpadFingerCapacity(const int touchpad) const noexcept -> int
  {
    return SDL_GameControllerGetNumTouchpadFingers(mController, touchpad);
  }

  [[nodiscard]] auto GetTouchpadFingerState(const int touchpad,
                                            const int finger) const noexcept
      -> std::optional<touch::finger_state>
  {
    touch::finger_state result{};
    Uint8 state{};

    const auto res = SDL_GameControllerGetTouchpadFinger(mController,
                                                         touchpad,
                                                         finger,
                                                         &state,
                                                         &result.x,
                                                         &result.y,
                                                         &result.pressure);
    result.state = static_cast<ButtonState>(state);

    if (res != -1) {
      return result;
    }
    else {
      return std::nullopt;
    }
  }

  template <std::size_t Size>
  [[nodiscard]] auto GetSensorData(const sensor_type type) const noexcept
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

  auto SendEffect(const void* data, const int size) -> Result
  {
    return SDL_GameControllerSendEffect(mController, data, size) == 0;
  }

  [[nodiscard]] auto GetSensorDataRate(const sensor_type type) const noexcept -> float
  {
    return SDL_GameControllerGetSensorDataRate(mController, static_cast<SDL_SensorType>(type));
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 16)

  [[nodiscard]] auto get() const noexcept -> SDL_GameController* { return mController.get(); }

  template <typename TT = T, detail::EnableHandle<TT> = 0>
  explicit operator bool() const noexcept
  {
    return mController != nullptr;
  }

 private:
  detail::Pointer<T, SDL_GameController> mController;
};

inline auto AddControllerMapping(const char* mapping) noexcept -> ControllerMappingResult
{
  assert(mapping);
  const auto result = SDL_GameControllerAddMapping(mapping);
  if (result == 1) {
    return ControllerMappingResult::Added;
  }
  else if (result == 0) {
    return ControllerMappingResult::Updated;
  }
  else {
    return ControllerMappingResult::Error;
  }
}

inline auto AddControllerMapping(const std::string& mapping) noexcept
    -> ControllerMappingResult
{
  return AddControllerMapping(mapping.c_str());
}

inline auto LoadControllerMappings(const char* file) noexcept -> std::optional<int>
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

inline auto LoadControllerMappings(const std::string& file) noexcept -> std::optional<int>
{
  return LoadControllerMappings(file.c_str());
}

[[nodiscard]] inline auto GetNumControllerMappings() noexcept -> int
{
  return SDL_GameControllerNumMappings();
}

[[nodiscard]] constexpr auto to_string(const ControllerButton button) -> std::string_view
{
  switch (button) {
    case ControllerButton::Invalid:
      return "Invalid";

    case ControllerButton::A:
      return "A";

    case ControllerButton::B:
      return "B";

    case ControllerButton::X:
      return "X";

    case ControllerButton::Y:
      return "Y";

    case ControllerButton::Back:
      return "Back";

    case ControllerButton::Guide:
      return "Guide";

    case ControllerButton::Start:
      return "Start";

    case ControllerButton::LeftStick:
      return "LeftStick";

    case ControllerButton::RightStick:
      return "RightStick";

    case ControllerButton::LeftShoulder:
      return "LeftShoulder";

    case ControllerButton::RightShoulder:
      return "RightShoulder";

    case ControllerButton::DpadUp:
      return "DpadUp";

    case ControllerButton::DpadDown:
      return "DpadDown";

    case ControllerButton::DpadLeft:
      return "DpadLeft";

    case ControllerButton::DpadRight:
      return "DpadRight";

#if SDL_VERSION_ATLEAST(2, 0, 14)

    case ControllerButton::Misc1:
      return "Misc1";

    case ControllerButton::Paddle1:
      return "Paddle1";

    case ControllerButton::Paddle2:
      return "Paddle2";

    case ControllerButton::Paddle3:
      return "Paddle3";

    case ControllerButton::Paddle4:
      return "Paddle4";

    case ControllerButton::Touchpad:
      return "Touchpad";

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

    case ControllerButton::Max:
      return "Max";

    default:
      throw Error{"Did not recognize controller button!"};
  }
}

inline auto operator<<(std::ostream& stream, const ControllerButton button) -> std::ostream&
{
  return stream << to_string(button);
}

[[nodiscard]] constexpr auto to_string(const ControllerAxis axis) -> std::string_view
{
  switch (axis) {
    case ControllerAxis::Invalid:
      return "Invalid";

    case ControllerAxis::LeftX:
      return "LeftX";

    case ControllerAxis::LeftY:
      return "LeftY";

    case ControllerAxis::RightX:
      return "RightX";

    case ControllerAxis::RightY:
      return "RightY";

    case ControllerAxis::TriggerLeft:
      return "TriggerLeft";

    case ControllerAxis::TriggerRight:
      return "TriggerRight";

    case ControllerAxis::Max:
      return "Max";

    default:
      throw Error{"Did not recognize controller axis!"};
  }
}

inline auto operator<<(std::ostream& stream, const ControllerAxis axis) -> std::ostream&
{
  return stream << to_string(axis);
}

[[nodiscard]] constexpr auto to_string(const ControllerBindType type) -> std::string_view
{
  switch (type) {
    case ControllerBindType::None:
      return "None";

    case ControllerBindType::Button:
      return "Button";

    case ControllerBindType::Axis:
      return "Axis";

    case ControllerBindType::Hat:
      return "Hat";

    default:
      throw Error{"Did not recognize controller bind type!"};
  }
}

inline auto operator<<(std::ostream& stream, const ControllerBindType type) -> std::ostream&
{
  return stream << to_string(type);
}

#if SDL_VERSION_ATLEAST(2, 0, 12)

[[nodiscard]] constexpr auto to_string(const ControllerType type) -> std::string_view
{
  switch (type) {
    case ControllerType::Unknown:
      return "Unknown";

    case ControllerType::NintendoSwitchPro:
      return "NintendoSwitchPro";

    case ControllerType::Xbox360:
      return "Xbox360";

    case ControllerType::XboxOne:
      return "XboxOne";

    case ControllerType::PS3:
      return "PS3";

    case ControllerType::PS4:
      return "PS4";

#if SDL_VERSION_ATLEAST(2, 0, 14)

    case ControllerType::PS5:
      return "PS5";

    case ControllerType::Virtual:
      return "Virtual";

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

#if SDL_VERSION_ATLEAST(2, 0, 16)

    case ControllerType::AmazonLuna:
      return "AmazonLuna";

    case ControllerType::GoogleStadia:
      return "GoogleStadia";

#endif  // SDL_VERSION_ATLEAST(2, 0, 16)

    default:
      throw Error{"Did not recognize controller type!"};
  }
}

inline auto operator<<(std::ostream& stream, const ControllerType type) -> std::ostream&
{
  return stream << to_string(type);
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

[[nodiscard]] inline auto to_string(const ControllerMappingResult result) -> std::string_view
{
  switch (result) {
    case ControllerMappingResult::Error:
      return "Error";

    case ControllerMappingResult::Updated:
      return "Updated";

    case ControllerMappingResult::Added:
      return "Added";

    default:
      throw Error{"Did not recognize controller mapping result!"};
  }
}

inline auto operator<<(std::ostream& stream, const ControllerMappingResult result)
    -> std::ostream&
{
  return stream << to_string(result);
}

template <typename T>
[[nodiscard]] auto to_string(const BasicController<T>& controller) -> std::string
{
  const auto* name = controller.GetName();

  const char* serial{};
  if constexpr (detail::sdl_version_at_least(2, 0, 14)) {
    serial = controller.GetSerial();
  }

#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("Controller(data: {}, name: {}, serial: {})",
                     detail::address_of(controller.get()),
                     str_or_na(name),
                     str_or_na(serial));
#else
  return "Controller(data: " + detail::address_of(controller.get()) +
         ", name: " + str_or_na(name) + ", serial: " + str_or_na(serial) + ")";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

template <typename T>
auto operator<<(std::ostream& stream, const BasicController<T>& controller) -> std::ostream&
{
  return stream << to_string(controller);
}

}  // namespace cen

#endif  // CENTURION_INPUT_CONTROLLER_HPP_
