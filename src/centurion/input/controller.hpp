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
#include "../core/common.hpp"
#include "../core/exception.hpp"
#include "../core/features.hpp"
#include "../core/sdl_string.hpp"
#include "../core/time.hpp"
#include "../detail/owner_handle_api.hpp"
#include "../detail/sdl_version_at_least.hpp"
#include "../detail/stdlib.hpp"
#include "button_state.hpp"
#include "joystick.hpp"
#include "sensor.hpp"
#include "touch.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen {

enum class ControllerButton {
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

  // clang-format off
  misc1 = SDL_CONTROLLER_BUTTON_MISC1, ///< Xbox Series X share button, PS5 microphone button, Nintendo Switch Pro capture button
  // clang-format on

  paddle1 = SDL_CONTROLLER_BUTTON_PADDLE1,    ///< Xbox Elite paddle P1
  paddle2 = SDL_CONTROLLER_BUTTON_PADDLE2,    ///< Xbox Elite paddle P3
  paddle3 = SDL_CONTROLLER_BUTTON_PADDLE3,    ///< Xbox Elite paddle P2
  paddle4 = SDL_CONTROLLER_BUTTON_PADDLE4,    ///< Xbox Elite paddle P4
  touchpad = SDL_CONTROLLER_BUTTON_TOUCHPAD,  ///< PS4/PS5 touchpad button

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  max = SDL_CONTROLLER_BUTTON_MAX
};

enum class ControllerAxis {
  invalid = SDL_CONTROLLER_AXIS_INVALID,
  left_x = SDL_CONTROLLER_AXIS_LEFTX,
  left_y = SDL_CONTROLLER_AXIS_LEFTY,
  right_x = SDL_CONTROLLER_AXIS_RIGHTX,
  right_y = SDL_CONTROLLER_AXIS_RIGHTY,
  trigger_left = SDL_CONTROLLER_AXIS_TRIGGERLEFT,
  trigger_right = SDL_CONTROLLER_AXIS_TRIGGERRIGHT,
  max = SDL_CONTROLLER_AXIS_MAX
};

enum class ControllerBindType {
  none = SDL_CONTROLLER_BINDTYPE_NONE,
  button = SDL_CONTROLLER_BINDTYPE_BUTTON,
  axis = SDL_CONTROLLER_BINDTYPE_AXIS,
  hat = SDL_CONTROLLER_BINDTYPE_HAT
};

#if SDL_VERSION_ATLEAST(2, 0, 12)

enum class ControllerType {
  // clang-format off
  unknown = SDL_CONTROLLER_TYPE_UNKNOWN,   ///< An unknown controller.
  xbox_360 = SDL_CONTROLLER_TYPE_XBOX360,  ///< An Xbox 360 controller.
  xbox_one = SDL_CONTROLLER_TYPE_XBOXONE,  ///< An Xbox One controller.
  ps3 = SDL_CONTROLLER_TYPE_PS3,           ///< A PS3 controller.
  ps4 = SDL_CONTROLLER_TYPE_PS4,           ///< A PS4 controller.

#if SDL_VERSION_ATLEAST(2, 0, 14)

  ps5 = SDL_CONTROLLER_TYPE_PS5,       ///< A PS5 controller.
  virt = SDL_CONTROLLER_TYPE_VIRTUAL,  ///< A virtual controller.

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

#if SDL_VERSION_ATLEAST(2, 0, 16)

  amazon_luna = SDL_CONTROLLER_TYPE_AMAZON_LUNA,     ///< An Amazon Luna controller.
  google_stadia = SDL_CONTROLLER_TYPE_GOOGLE_STADIA, ///< A Google Stadia controller.

#endif // SDL_VERSION_ATLEAST(2, 0, 16)

  nintendo_switch_pro = SDL_CONTROLLER_TYPE_NINTENDO_SWITCH_PRO  ///< A Nintendo Switch Pro controller.
  // clang-format on
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
    case ControllerButton::invalid:
      return "invalid";

    case ControllerButton::a:
      return "a";

    case ControllerButton::b:
      return "b";

    case ControllerButton::x:
      return "x";

    case ControllerButton::y:
      return "y";

    case ControllerButton::back:
      return "back";

    case ControllerButton::guide:
      return "guide";

    case ControllerButton::start:
      return "start";

    case ControllerButton::left_stick:
      return "left_stick";

    case ControllerButton::right_stick:
      return "right_stick";

    case ControllerButton::left_shoulder:
      return "left_shoulder";

    case ControllerButton::right_shoulder:
      return "right_shoulder";

    case ControllerButton::dpad_up:
      return "dpad_up";

    case ControllerButton::dpad_down:
      return "dpad_down";

    case ControllerButton::dpad_left:
      return "dpad_left";

    case ControllerButton::dpad_right:
      return "dpad_right";

#if SDL_VERSION_ATLEAST(2, 0, 14)

    case ControllerButton::misc1:
      return "misc1";

    case ControllerButton::paddle1:
      return "paddle1";

    case ControllerButton::paddle2:
      return "paddle2";

    case ControllerButton::paddle3:
      return "paddle3";

    case ControllerButton::paddle4:
      return "paddle4";

    case ControllerButton::touchpad:
      return "touchpad";

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

    case ControllerButton::max:
      return "max";

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
    case ControllerAxis::invalid:
      return "invalid";

    case ControllerAxis::left_x:
      return "left_x";

    case ControllerAxis::left_y:
      return "left_y";

    case ControllerAxis::right_x:
      return "right_x";

    case ControllerAxis::right_y:
      return "right_y";

    case ControllerAxis::trigger_left:
      return "trigger_left";

    case ControllerAxis::trigger_right:
      return "trigger_right";

    case ControllerAxis::max:
      return "max";

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
    case ControllerBindType::none:
      return "none";

    case ControllerBindType::button:
      return "button";

    case ControllerBindType::axis:
      return "axis";

    case ControllerBindType::hat:
      return "hat";

    default:
      throw Error{"Did not recognzie controller bind type!"};
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
    case ControllerType::unknown:
      return "unknown";

    case ControllerType::nintendo_switch_pro:
      return "nintendo_switch_pro";

    case ControllerType::xbox_360:
      return "xbox_360";

    case ControllerType::xbox_one:
      return "xbox_one";

    case ControllerType::ps3:
      return "ps3";

    case ControllerType::ps4:
      return "ps4";

#if SDL_VERSION_ATLEAST(2, 0, 14)

    case ControllerType::ps5:
      return "ps5";

    case ControllerType::virt:
      return "virt";

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

#if SDL_VERSION_ATLEAST(2, 0, 16)

    case ControllerType::amazon_luna:
      return "amazon_luna";

    case ControllerType::google_stadia:
      return "google_stadia";

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
