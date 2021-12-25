#ifndef CENTURION_EVENTS_HPP_
#define CENTURION_EVENTS_HPP_

#include <SDL.h>

#include <array>        // array
#include <ostream>      // ostream
#include <string_view>  // string_view
#include <utility>      // move

#include "common.hpp"
#include "detail/array_utils.hpp"
#include "detail/stdlib.hpp"
#include "input/button_state.hpp"
#include "input/controller.hpp"
#include "input/sensor.hpp"
#include "keyboard.hpp"
#include "mouse.hpp"

namespace cen {

/// Represents the different event types.
enum class EventType : Uint32 {
  Quit = SDL_QUIT,

  AppTerminating = SDL_APP_TERMINATING,
  AppLowMemory = SDL_APP_LOWMEMORY,
  AppWillEnterBackground = SDL_APP_WILLENTERBACKGROUND,
  AppDidEnterBackground = SDL_APP_DIDENTERBACKGROUND,
  AppWillEnterForeground = SDL_APP_WILLENTERFOREGROUND,
  AppDidEnterForeground = SDL_APP_DIDENTERFOREGROUND,

#if SDL_VERSION_ATLEAST(2, 0, 14)
  LocaleChanged = SDL_LOCALECHANGED,
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  Display = SDL_DISPLAYEVENT,
  Window = SDL_WINDOWEVENT,
  System = SDL_SYSWMEVENT,

  KeyDown = SDL_KEYDOWN,
  KeyUp = SDL_KEYUP,
  TextEditing = SDL_TEXTEDITING,
  TextInput = SDL_TEXTINPUT,
  KeymapChanged = SDL_KEYMAPCHANGED,

  MouseMotion = SDL_MOUSEMOTION,
  MouseButtonDown = SDL_MOUSEBUTTONDOWN,
  MouseButtonUp = SDL_MOUSEBUTTONUP,
  MouseWheel = SDL_MOUSEWHEEL,

  JoyAxisMotion = SDL_JOYAXISMOTION,
  JoyBallMotion = SDL_JOYBALLMOTION,
  JoyHatMotion = SDL_JOYHATMOTION,
  JoyButtonDown = SDL_JOYBUTTONDOWN,
  JoyButtonUp = SDL_JOYBUTTONUP,
  JoyDeviceAdded = SDL_JOYDEVICEADDED,
  JoyDeviceRemoved = SDL_JOYDEVICEREMOVED,

  ControllerAxisMotion = SDL_CONTROLLERAXISMOTION,
  ControllerButtonDown = SDL_CONTROLLERBUTTONDOWN,
  ControllerButtonUp = SDL_CONTROLLERBUTTONUP,
  ControllerDeviceAdded = SDL_CONTROLLERDEVICEADDED,
  ControllerDeviceRemoved = SDL_CONTROLLERDEVICEREMOVED,
  ControllerDeviceRemapped = SDL_CONTROLLERDEVICEREMAPPED,

#if SDL_VERSION_ATLEAST(2, 0, 14)
  ControllerTouchpadDown = SDL_CONTROLLERTOUCHPADDOWN,
  ControllerTouchpadMotion = SDL_CONTROLLERTOUCHPADMOTION,
  ControllerTouchpadUp = SDL_CONTROLLERTOUCHPADUP,
  ControllerSensorUpdate = SDL_CONTROLLERSENSORUPDATE,
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  FingerDown = SDL_FINGERDOWN,
  FingerUp = SDL_FINGERUP,
  FingerMotion = SDL_FINGERMOTION,

  DollarGesture = SDL_DOLLARGESTURE,
  DollarRecord = SDL_DOLLARRECORD,
  MultiGesture = SDL_MULTIGESTURE,

  ClipboardUpdate = SDL_CLIPBOARDUPDATE,

  DropFile = SDL_DROPFILE,
  DropText = SDL_DROPTEXT,
  DropBegin = SDL_DROPBEGIN,
  DropComplete = SDL_DROPCOMPLETE,

  AudioDeviceAdded = SDL_AUDIODEVICEADDED,
  AudioDeviceRemoved = SDL_AUDIODEVICEREMOVED,

  SensorUpdate = SDL_SENSORUPDATE,

  RenderTargetsReset = SDL_RENDER_TARGETS_RESET,
  RenderDeviceReset = SDL_RENDER_DEVICE_RESET,

  User = SDL_USEREVENT
};

enum class JoyHatPosition : Uint8 {
  LeftUp = SDL_HAT_LEFTUP,
  Left = SDL_HAT_LEFT,
  LeftDown = SDL_HAT_LEFTDOWN,
  Up = SDL_HAT_UP,
  Centered = SDL_HAT_CENTERED,
  Down = SDL_HAT_DOWN,
  RightUp = SDL_HAT_RIGHTUP,
  Right = SDL_HAT_RIGHT,
  RightDown = SDL_HAT_RIGHTDOWN
};

enum class MouseWheelDirection : Uint32 {
  Normal = SDL_MOUSEWHEEL_NORMAL,
  Flipped = SDL_MOUSEWHEEL_FLIPPED
};

enum class WindowEventID {
  None = SDL_WINDOWEVENT_NONE,
  Shown = SDL_WINDOWEVENT_SHOWN,
  Hidden = SDL_WINDOWEVENT_HIDDEN,
  Exposed = SDL_WINDOWEVENT_EXPOSED,
  Moved = SDL_WINDOWEVENT_MOVED,
  Resized = SDL_WINDOWEVENT_RESIZED,
  SizeChanged = SDL_WINDOWEVENT_SIZE_CHANGED,
  Minimized = SDL_WINDOWEVENT_MINIMIZED,
  Maximized = SDL_WINDOWEVENT_MAXIMIZED,
  Restored = SDL_WINDOWEVENT_RESTORED,
  Enter = SDL_WINDOWEVENT_ENTER,
  Leave = SDL_WINDOWEVENT_LEAVE,
  FocusGained = SDL_WINDOWEVENT_FOCUS_GAINED,
  FocusLost = SDL_WINDOWEVENT_FOCUS_LOST,
  Close = SDL_WINDOWEVENT_CLOSE,
  TakeFocus = SDL_WINDOWEVENT_TAKE_FOCUS,
  HitTest = SDL_WINDOWEVENT_HIT_TEST
};

/// The templated base class of all Centurion events.
///
/// This class defines the common API of all events and provides the storage of the SDL event.
///
/// \tparam T the SDL event type.
template <typename T>
class EventBase {
 public:
  explicit EventBase(const EventType type) noexcept
  {
    SetTimestamp(SDL_GetTicks());
    SetType(type);
  }

  explicit EventBase(const T& event) noexcept : mEvent{event} {}

  explicit EventBase(T&& event) noexcept : mEvent{std::move(event)} {}

  /// Sets the timestamp of the creation of the event. TODO U32_Millis?
  void SetTimestamp(const Uint32 timestamp) noexcept { mEvent.timestamp = timestamp; }

  void SetType(const EventType type) noexcept { mEvent.type = ToUnderlying(type); }

  [[nodiscard]] auto GetTimestamp() const noexcept -> Uint32 { return mEvent.timestamp; }

  [[nodiscard]] auto GetType() const noexcept -> EventType { return EventType{mEvent.type}; }

  [[nodiscard]] auto get() const noexcept -> const T& { return mEvent; }

 protected:
  T mEvent{};
};

// TODO
class quit_event final : public EventBase<SDL_QuitEvent> {
 public:
  quit_event() noexcept : EventBase{EventType::Quit} {}

  explicit quit_event(const SDL_QuitEvent& event) noexcept : EventBase{event} {}
};

class AudioDeviceEvent final : public EventBase<SDL_AudioDeviceEvent> {
 public:
  AudioDeviceEvent() noexcept : EventBase{EventType::AudioDeviceAdded} {}

  explicit AudioDeviceEvent(const SDL_AudioDeviceEvent& event) noexcept : EventBase{event} {}

  void SetWhich(const Uint32 which) noexcept { mEvent.which = which; }
  void SetCapture(const bool capture) noexcept { mEvent.iscapture = capture; }

  [[nodiscard]] auto GetWhich() const noexcept -> Uint32 { return mEvent.which; }
  [[nodiscard]] auto IsCapture() const noexcept -> bool { return mEvent.iscapture; }
  [[nodiscard]] auto IsOutput() const noexcept -> bool { return !IsCapture(); }
};

class JoyAxisEvent final : public EventBase<SDL_JoyAxisEvent> {
 public:
  JoyAxisEvent() noexcept : EventBase{EventType::JoyAxisMotion} {}

  explicit JoyAxisEvent(const SDL_JoyAxisEvent& event) noexcept : EventBase{event} {}

  void SetWhich(const SDL_JoystickID which) noexcept { mEvent.which = which; }

  void SetAxis(const Uint8 axis) noexcept { mEvent.axis = axis; }

  void SetValue(const Sint16 value) noexcept { mEvent.value = value; }

  [[nodiscard]] auto GetWhich() const noexcept -> SDL_JoystickID { return mEvent.which; }

  [[nodiscard]] auto GetAxis() const noexcept -> Uint8 { return mEvent.axis; }

  [[nodiscard]] auto GetValue() const noexcept -> Sint16 { return mEvent.value; }
};

class JoyBallEvent final : public EventBase<SDL_JoyBallEvent> {
 public:
  JoyBallEvent() noexcept : EventBase{EventType::JoyBallMotion} {}

  explicit JoyBallEvent(const SDL_JoyBallEvent& event) noexcept : EventBase{event} {}

  void SetWhich(const SDL_JoystickID which) noexcept { mEvent.which = which; }
  void SetBall(const Uint8 ball) noexcept { mEvent.ball = ball; }

  void SetDeltaX(const Sint16 dx) noexcept { mEvent.xrel = dx; }
  void SetDeltaY(const Sint16 dy) noexcept { mEvent.yrel = dy; }

  [[nodiscard]] auto GetWhich() const noexcept -> SDL_JoystickID { return mEvent.which; }
  [[nodiscard]] auto GetBall() const noexcept -> Uint8 { return mEvent.ball; }

  [[nodiscard]] auto GetDeltaX() const noexcept -> Sint16 { return mEvent.xrel; }
  [[nodiscard]] auto GetDeltaY() const noexcept -> Sint16 { return mEvent.yrel; }
};

class JoyButtonEvent final : public EventBase<SDL_JoyButtonEvent> {
 public:
  JoyButtonEvent() noexcept : EventBase{EventType::JoyButtonDown} {}

  explicit JoyButtonEvent(const SDL_JoyButtonEvent& event) noexcept : EventBase{event} {}

  void SetWhich(const SDL_JoystickID id) noexcept { mEvent.which = id; }

  void SetButton(const Uint8 index) noexcept { mEvent.button = index; }

  void SetState(const ButtonState state) noexcept { mEvent.state = ToUnderlying(state); }

  [[nodiscard]] auto GetWhich() const noexcept -> SDL_JoystickID { return mEvent.which; }

  [[nodiscard]] auto GetButton() const noexcept -> Uint8 { return mEvent.button; }

  [[nodiscard]] auto GetState() const noexcept -> ButtonState
  {
    return static_cast<ButtonState>(mEvent.state);
  }

  [[nodiscard]] auto IsPressed() const noexcept -> bool
  {
    return GetState() == ButtonState::Pressed;
  }

  [[nodiscard]] auto IsReleased() const noexcept -> bool
  {
    return GetState() == ButtonState::Released;
  }
};

class JoyDeviceEvent final : public EventBase<SDL_JoyDeviceEvent> {
 public:
  JoyDeviceEvent() noexcept : EventBase{EventType::JoyDeviceAdded} {}

  explicit JoyDeviceEvent(const SDL_JoyDeviceEvent& event) noexcept : EventBase{event} {}

  void SetWhich(const Sint32 which) noexcept { mEvent.which = which; }

  [[nodiscard]] auto GetWhich() const noexcept -> Sint32 { return mEvent.which; }
};

class JoyHatEvent final : public EventBase<SDL_JoyHatEvent> {
 public:
  JoyHatEvent() noexcept : EventBase{EventType::JoyHatMotion} {}

  explicit JoyHatEvent(const SDL_JoyHatEvent& event) noexcept : EventBase{event} {}

  void SetHat(const Uint8 hat) noexcept { mEvent.hat = hat; }

  void SetPosition(const JoyHatPosition value) noexcept { mEvent.value = ToUnderlying(value); }

  [[nodiscard]] auto GetHat() const noexcept -> Uint8 { return mEvent.hat; }

  [[nodiscard]] auto GetPosition() const noexcept -> JoyHatPosition
  {
    return static_cast<JoyHatPosition>(mEvent.value);
  }
};

class ControllerAxisEvent final : public EventBase<SDL_ControllerAxisEvent> {
 public:
  ControllerAxisEvent() noexcept : EventBase{EventType::ControllerAxisMotion} {}

  explicit ControllerAxisEvent(const SDL_ControllerAxisEvent& event) noexcept
      : EventBase{event}
  {}

  void SetWhich(const SDL_JoystickID which) noexcept { mEvent.which = which; }
  void SetAxis(const ControllerAxis axis) noexcept { mEvent.axis = static_cast<Uint8>(axis); }
  void SetValue(const Sint16 value) noexcept { mEvent.value = value; }

  [[nodiscard]] auto GetWhich() const noexcept -> SDL_JoystickID { return mEvent.which; }
  [[nodiscard]] auto GetAxis() const noexcept -> ControllerAxis
  {
    return static_cast<ControllerAxis>(mEvent.axis);
  }
  [[nodiscard]] auto GetValue() const noexcept -> Sint16 { return mEvent.value; }
};

class ControllerButtonEvent final : public EventBase<SDL_ControllerButtonEvent> {
 public:
  ControllerButtonEvent() noexcept : EventBase{EventType::ControllerButtonDown} {}

  explicit ControllerButtonEvent(const SDL_ControllerButtonEvent& event) noexcept
      : EventBase{event}
  {}

  void SetWhich(const SDL_JoystickID id) noexcept { mEvent.which = id; }

  void SetButton(const ControllerButton button) noexcept
  {
    mEvent.button = static_cast<Uint8>(button);
  }

  void SetState(const ButtonState state) noexcept { mEvent.state = ToUnderlying(state); }

  [[nodiscard]] auto GetWhich() const noexcept -> SDL_JoystickID { return mEvent.which; }

  [[nodiscard]] auto GetButton() const noexcept -> ControllerButton
  {
    return static_cast<ControllerButton>(mEvent.button);
  }

  [[nodiscard]] auto GetState() const noexcept -> ButtonState
  {
    return static_cast<ButtonState>(mEvent.state);
  }

  [[nodiscard]] auto IsPressed() const noexcept -> bool
  {
    return GetState() == ButtonState::Pressed;
  }

  [[nodiscard]] auto IsReleased() const noexcept -> bool
  {
    return GetState() == ButtonState::Released;
  }
};

class ControllerDeviceEvent final : public EventBase<SDL_ControllerDeviceEvent> {
 public:
  ControllerDeviceEvent() noexcept : EventBase{EventType::ControllerDeviceAdded} {}

  explicit ControllerDeviceEvent(const SDL_ControllerDeviceEvent& event) noexcept
      : EventBase{event}
  {}

  void SetWhich(const Sint32 which) noexcept { mEvent.which = which; }

  [[nodiscard]] auto GetWhich() const noexcept -> Sint32 { return mEvent.which; }
};

#if SDL_VERSION_ATLEAST(2, 0, 14)

class ControllerSensorEvent final : public EventBase<SDL_ControllerSensorEvent> {
 public:
  ControllerSensorEvent() noexcept : EventBase{EventType::ControllerSensorUpdate} {}

  explicit ControllerSensorEvent(const SDL_ControllerSensorEvent& event) noexcept
      : EventBase{event}
  {}

  void SetWhich(const SDL_JoystickID id) noexcept { mEvent.which = id; }

  void SetSensor(const sensor_type sensor) noexcept { mEvent.sensor = ToUnderlying(sensor); }

  void SetData(const std::array<float, 3>& values) { detail::assign(values, mEvent.data); }

  [[nodiscard]] auto GetWhich() const noexcept -> SDL_JoystickID { return mEvent.which; }

  [[nodiscard]] auto GetSensor() const noexcept -> sensor_type
  {
    return sensor_type{mEvent.sensor};
  }

  [[nodiscard]] auto GetData() const -> std::array<float, 3>
  {
    return detail::to_array(mEvent.data);
  }
};

class ControllerTouchpadEvent final : public EventBase<SDL_ControllerTouchpadEvent> {
 public:
  ControllerTouchpadEvent() noexcept : EventBase{EventType::ControllerTouchpadDown} {}

  explicit ControllerTouchpadEvent(const SDL_ControllerTouchpadEvent& event) noexcept
      : EventBase{event}
  {}

  void SetWhich(const SDL_JoystickID id) noexcept { mEvent.which = id; }

  void SetTouchpadIndex(const Sint32 index) noexcept { mEvent.touchpad = index; }
  void SetFingerIndex(const Sint32 index) noexcept { mEvent.finger = index; }

  void SetX(const float x) noexcept { mEvent.x = detail::clamp(x, 0.0f, 1.0f); }
  void SetY(const float y) noexcept { mEvent.y = detail::clamp(y, 0.0f, 1.0f); }

  void SetPressure(const float pressure) noexcept
  {
    mEvent.pressure = detail::clamp(pressure, 0.0f, 1.0f);
  }

  [[nodiscard]] auto GetWhich() const noexcept -> SDL_JoystickID { return mEvent.which; }

  [[nodiscard]] auto GetTouchpadIndex() const noexcept -> Sint32 { return mEvent.touchpad; }
  [[nodiscard]] auto GetFingerIndex() const noexcept -> Sint32 { return mEvent.finger; }

  [[nodiscard]] auto GetX() const noexcept -> float { return mEvent.x; }
  [[nodiscard]] auto GetY() const noexcept -> float { return mEvent.y; }

  [[nodiscard]] auto GetPressure() const noexcept -> float { return mEvent.pressure; }
};

enum class DisplayEventID {
  None = SDL_DISPLAYEVENT_NONE,
  Orientation = SDL_DISPLAYEVENT_ORIENTATION,
  Connected = SDL_DISPLAYEVENT_CONNECTED,
  Disconnected = SDL_DISPLAYEVENT_DISCONNECTED,
};

class DisplayEvent final : public EventBase<SDL_DisplayEvent> {
 public:
  DisplayEvent() noexcept : EventBase{EventType::Display} {}

  explicit DisplayEvent(const SDL_DisplayEvent& event) noexcept : EventBase{event} {}

  void SetEventID(const DisplayEventID id) noexcept
  {
    mEvent.event = static_cast<Uint8>(ToUnderlying(id));
  }

  void SetIndex(const Uint32 index) noexcept { mEvent.display = index; }

  void SetData1(const Sint32 data) noexcept { mEvent.data1 = data; }

  [[nodiscard]] auto GetEventID() const noexcept -> DisplayEventID
  {
    return static_cast<DisplayEventID>(mEvent.event);
  }

  [[nodiscard]] auto GetIndex() const noexcept -> Uint32 { return mEvent.display; }

  [[nodiscard]] auto GetData1() const noexcept -> Sint32 { return mEvent.data1; }
};

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

// TODO
class dollar_gesture_event final : public EventBase<SDL_DollarGestureEvent> {
 public:
  dollar_gesture_event() noexcept : EventBase{EventType::DollarGesture} {}

  explicit dollar_gesture_event(const SDL_DollarGestureEvent& event) noexcept
      : EventBase{event}
  {}

  void set_touch_id(const SDL_TouchID id) noexcept { mEvent.touchId = id; }

  void set_gesture_id(const SDL_GestureID id) noexcept { mEvent.gestureId = id; }

  void set_fingers(const Uint32 fingers) noexcept { mEvent.numFingers = fingers; }

  void set_error(const float error) noexcept { mEvent.error = error; }

  void set_x(const float x) noexcept { mEvent.x = x; }

  void set_y(const float y) noexcept { mEvent.y = y; }

  [[nodiscard]] auto touch_id() const noexcept -> SDL_TouchID { return mEvent.touchId; }

  [[nodiscard]] auto gesture_id() const noexcept -> SDL_GestureID { return mEvent.gestureId; }

  [[nodiscard]] auto finger_count() const noexcept -> Uint32 { return mEvent.numFingers; }

  [[nodiscard]] auto error() const noexcept -> float { return mEvent.error; }

  [[nodiscard]] auto x() const noexcept -> float { return mEvent.x; }

  [[nodiscard]] auto y() const noexcept -> float { return mEvent.y; }
};

class DropEvent final : public EventBase<SDL_DropEvent> {
 public:
  DropEvent() noexcept : EventBase{EventType::DropFile} {}

  explicit DropEvent(const SDL_DropEvent& event) noexcept : EventBase{event} {}

  ~DropEvent() noexcept { MaybeDestroyFile(); }

  void SetWillFreeFile(const bool freeFile) noexcept { mFreeFile = freeFile; }

  void SetFile(char* file) noexcept
  {
    MaybeDestroyFile();
    mEvent.file = file;
  }

  void SetWindowID(const Uint32 id) noexcept { mEvent.windowID = id; }

  [[nodiscard]] auto WillFreeFile() const noexcept -> bool { return mFreeFile; }

  [[nodiscard]] auto GetFile() const noexcept -> char* { return mEvent.file; }

  [[nodiscard]] auto GetWindowID() const noexcept -> Uint32 { return mEvent.windowID; }

 private:
  bool mFreeFile{false};

  void MaybeDestroyFile() noexcept
  {
    if (mEvent.file && mFreeFile) {
      SDL_free(mEvent.file);
    }
  }
};

class KeyboardEvent final : public EventBase<SDL_KeyboardEvent> {
 public:
  KeyboardEvent() noexcept : EventBase{EventType::KeyDown} {}

  explicit KeyboardEvent(const SDL_KeyboardEvent& event) noexcept : EventBase{event} {}

  void SetScanCode(const ScanCode code) noexcept { mEvent.keysym.scancode = code.get(); }

  void SetKeyCode(const KeyCode code) noexcept { mEvent.keysym.sym = code.get(); }

  void SetButtonState(const ButtonState state) noexcept { mEvent.state = ToUnderlying(state); }

  void SetModifier(const KeyMod mod, const bool active) noexcept
  {
    if (active) {
      mEvent.keysym.mod |= ToUnderlying(mod);
    }
    else {
      mEvent.keysym.mod &= ~ToUnderlying(mod);
    }
  }

  void SetRepeated(const bool repeated) noexcept { mEvent.repeat = repeated; }

  void SetWindowID(const Uint32 id) noexcept { mEvent.windowID = id; }

  [[nodiscard]] auto IsActive(const ScanCode& code) const noexcept -> bool
  {
    return mEvent.keysym.scancode == code.get();
  }

  [[nodiscard]] auto IsActive(const KeyCode& code) const noexcept -> bool
  {
    return static_cast<SDL_KeyCode>(mEvent.keysym.sym) == code.get();
  }

  [[nodiscard]] auto IsActive(const KeyMod mod) const noexcept -> bool
  {
    return detail::IsActive(mod, mEvent.keysym.mod);
  }

  [[nodiscard]] auto IsOnlyActive(const KeyMod mod) const noexcept -> bool
  {
    return detail::IsOnlyActive(mod, mEvent.keysym.mod);
  }

  [[nodiscard]] auto IsOnlyAnyOfActive(const KeyMod mod) const noexcept -> bool
  {
    return detail::IsOnlyAnyOfActive(mod, mEvent.keysym.mod);
  }

  [[nodiscard]] auto IsRepeated() const noexcept -> bool { return mEvent.repeat; }

  [[nodiscard]] auto GetState() const noexcept -> ButtonState
  {
    return static_cast<ButtonState>(mEvent.state);
  }

  [[nodiscard]] auto IsReleased() const noexcept -> bool
  {
    return GetState() == ButtonState::Released;
  }

  [[nodiscard]] auto IsPressed() const noexcept -> bool
  {
    return GetState() == ButtonState::Pressed;
  }

  [[nodiscard]] auto GetScanCode() const noexcept -> ScanCode
  {
    return mEvent.keysym.scancode;
  }

  [[nodiscard]] auto GetKeyCode() const noexcept -> KeyCode
  {
    return static_cast<SDL_KeyCode>(mEvent.keysym.sym);
  }

  [[nodiscard]] auto GetWindowID() const noexcept -> Uint32 { return mEvent.windowID; }
};

class MouseButtonEvent final : public EventBase<SDL_MouseButtonEvent> {
 public:
  MouseButtonEvent() noexcept : EventBase{EventType::MouseButtonDown} {}

  explicit MouseButtonEvent(const SDL_MouseButtonEvent& event) noexcept : EventBase{event} {}

  void SetWindowID(const Uint32 id) noexcept { mEvent.windowID = id; }
  void SetWhich(const Uint32 which) noexcept { mEvent.which = which; }

  void SetButton(const MouseButton button) noexcept { mEvent.button = ToUnderlying(button); }
  void SetState(const ButtonState state) noexcept { mEvent.state = ToUnderlying(state); }

  void SetClicks(const Uint8 clicks) noexcept { mEvent.clicks = clicks; }

  void SetX(const Sint32 x) noexcept { mEvent.x = x; }
  void SetY(const Sint32 y) noexcept { mEvent.y = y; }

  [[nodiscard]] auto GetWindowID() const noexcept -> Uint32 { return mEvent.windowID; }
  [[nodiscard]] auto GetWhich() const noexcept -> Uint32 { return mEvent.which; }

  [[nodiscard]] auto GetButton() const noexcept -> MouseButton
  {
    return static_cast<MouseButton>(mEvent.button);
  }

  [[nodiscard]] auto GetState() const noexcept -> ButtonState
  {
    return static_cast<ButtonState>(mEvent.state);
  }

  [[nodiscard]] auto IsPressed() const noexcept -> bool
  {
    return GetState() == ButtonState::Pressed;
  }

  [[nodiscard]] auto IsReleased() const noexcept -> bool
  {
    return GetState() == ButtonState::Released;
  }

  [[nodiscard]] auto GetClicks() const noexcept -> Uint8 { return mEvent.clicks; }

  [[nodiscard]] auto GetX() const noexcept -> Sint32 { return mEvent.x; }
  [[nodiscard]] auto GetY() const noexcept -> Sint32 { return mEvent.y; }
};

class MouseMotionEvent final : public EventBase<SDL_MouseMotionEvent> {
 public:
  MouseMotionEvent() noexcept : EventBase{EventType::MouseMotion} {}

  explicit MouseMotionEvent(const SDL_MouseMotionEvent& event) noexcept : EventBase{event} {}

  void SetWindowID(const Uint32 id) noexcept { mEvent.windowID = id; }
  void SetWhich(const Uint32 which) noexcept { mEvent.which = which; }

  void SetState(const Uint32 state) noexcept { mEvent.state = state; }

  void SetX(const Sint32 x) noexcept { mEvent.x = x; }
  void SetY(const Sint32 y) noexcept { mEvent.y = y; }

  void SetDeltaX(const Sint32 dx) noexcept { mEvent.xrel = dx; }
  void SetDeltaY(const Sint32 dy) noexcept { mEvent.yrel = dy; }

  [[nodiscard]] auto GetWindowID() const noexcept -> Uint32 { return mEvent.windowID; }
  [[nodiscard]] auto GetWhich() const noexcept -> Uint32 { return mEvent.which; }

  [[nodiscard]] auto GetState() const noexcept -> Uint32 { return mEvent.state; }

  [[nodiscard]] auto IsPressed(const MouseButton button) const noexcept -> bool
  {
    return mEvent.state & SDL_BUTTON(ToUnderlying(button));
  }

  [[nodiscard]] auto GetX() const noexcept -> Sint32 { return mEvent.x; }
  [[nodiscard]] auto GetY() const noexcept -> Sint32 { return mEvent.y; }

  [[nodiscard]] auto GetDeltaX() const noexcept -> Sint32 { return mEvent.xrel; }
  [[nodiscard]] auto GetDeltaY() const noexcept -> Sint32 { return mEvent.yrel; }
};

class MouseWheelEvent final : public EventBase<SDL_MouseWheelEvent> {
 public:
  MouseWheelEvent() noexcept : EventBase{EventType::MouseWheel} {}

  explicit MouseWheelEvent(const SDL_MouseWheelEvent& event) noexcept : EventBase{event} {}

  void SetWindowID(const Uint32 id) noexcept { mEvent.windowID = id; }
  void SetWhich(const Uint32 which) noexcept { mEvent.which = which; }

  void SetXScroll(const Sint32 xScroll) noexcept { mEvent.x = xScroll; }
  void SetYScroll(const Sint32 yScroll) noexcept { mEvent.y = yScroll; }

  void SetDirection(const MouseWheelDirection direction) noexcept
  {
    mEvent.direction = ToUnderlying(direction);
  }

  [[nodiscard]] auto GetWindowID() const noexcept -> Uint32 { return mEvent.windowID; }
  [[nodiscard]] auto GetWhich() const noexcept -> Uint32 { return mEvent.which; }

  [[nodiscard]] auto GetXScroll() const noexcept -> Sint32 { return mEvent.x; }
  [[nodiscard]] auto GetYScroll() const noexcept -> Sint32 { return mEvent.y; }

  [[nodiscard]] auto GetDirection() const noexcept -> MouseWheelDirection
  {
    return static_cast<MouseWheelDirection>(mEvent.direction);
  }
};

// TODO
class multi_gesture_event final : public EventBase<SDL_MultiGestureEvent> {
 public:
  multi_gesture_event() noexcept : EventBase{EventType::MultiGesture} {}

  explicit multi_gesture_event(const SDL_MultiGestureEvent& event) noexcept : EventBase{event}
  {}

  void set_touch_id(const SDL_TouchID id) noexcept { mEvent.touchId = id; }

  void set_delta_theta(const float dTheta) noexcept { mEvent.dTheta = dTheta; }

  void set_delta_distance(const float dDistance) noexcept { mEvent.dDist = dDistance; }

  void set_center_x(const float centerX) noexcept { mEvent.x = centerX; }

  void set_center_y(const float centerY) noexcept { mEvent.y = centerY; }

  void set_finger_count(const Uint16 count) noexcept { mEvent.numFingers = count; }

  [[nodiscard]] auto touch_id() const noexcept -> SDL_TouchID { return mEvent.touchId; }

  [[nodiscard]] auto delta_theta() const noexcept -> float { return mEvent.dTheta; }

  [[nodiscard]] auto delta_distance() const noexcept -> float { return mEvent.dDist; }

  [[nodiscard]] auto center_x() const noexcept -> float { return mEvent.x; }

  [[nodiscard]] auto center_y() const noexcept -> float { return mEvent.y; }

  [[nodiscard]] auto finger_count() const noexcept -> Uint16 { return mEvent.numFingers; }
};

// TODO
class sensor_event final : public EventBase<SDL_SensorEvent> {
 public:
  using data_type = std::array<float, 6>;

  sensor_event() noexcept : EventBase{EventType::SensorUpdate} {}

  explicit sensor_event(const SDL_SensorEvent& event) noexcept : EventBase{event} {}

  void set_which(const Sint32 id) noexcept { mEvent.which = id; }

  void set_data(const data_type& values) { detail::assign(values, mEvent.data); }

  [[nodiscard]] auto which() const noexcept -> Sint32 { return mEvent.which; }

  [[nodiscard]] auto data() const -> data_type { return detail::to_array(mEvent.data); }
};

// TODO
class text_editing_event final : public EventBase<SDL_TextEditingEvent> {
 public:
  text_editing_event() noexcept : EventBase{EventType::TextEditing} { check_length(); }

  explicit text_editing_event(const SDL_TextEditingEvent& event) noexcept : EventBase{event}
  {
    check_length();
  }

  void set_window_id(const Uint32 id) noexcept { mEvent.windowID = id; }

  void set_start(const Sint32 start) noexcept { mEvent.start = start; }

  void set_length(const Sint32 length) noexcept
  {
    mEvent.length = detail::clamp(length, 0, 32);
  }

  [[nodiscard]] auto window_id() const noexcept -> Uint32 { return mEvent.windowID; }

  [[nodiscard]] auto text() const noexcept -> std::string_view
  {
    return std::string_view{static_cast<const char*>(mEvent.text)};
  }

  [[nodiscard]] auto start() const noexcept -> Sint32 { return mEvent.start; }

  [[nodiscard]] auto length() const noexcept -> Sint32 { return mEvent.length; }

 private:
  void check_length() noexcept { mEvent.length = detail::clamp(mEvent.length, 0, 32); }
};

// TODO
class text_input_event final : public EventBase<SDL_TextInputEvent> {
 public:
  text_input_event() noexcept : EventBase{EventType::TextInput} {}

  explicit text_input_event(const SDL_TextInputEvent& event) noexcept : EventBase{event} {}

  void set_window_id(const Uint32 id) noexcept { mEvent.windowID = id; }

  [[nodiscard]] auto window_id() const noexcept -> Uint32 { return mEvent.windowID; }

  [[nodiscard]] auto text_utf8() const noexcept -> std::string_view
  {
    return std::string_view{static_cast<const char*>(mEvent.text)};
  }
};

// TODO
class touch_finger_event final : public EventBase<SDL_TouchFingerEvent> {
 public:
  touch_finger_event() noexcept : EventBase{EventType::FingerDown} {}

  explicit touch_finger_event(const SDL_TouchFingerEvent& event) noexcept : EventBase{event} {}

  void set_touch_id(const SDL_TouchID id) noexcept { mEvent.touchId = id; }

  void set_finger_id(const SDL_FingerID id) noexcept { mEvent.fingerId = id; }

#if SDL_VERSION_ATLEAST(2, 0, 12)

  void set_window_id(const Uint32 id) noexcept { mEvent.windowID = id; }

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

  void set_x(const float x) noexcept { mEvent.x = detail::clamp(x, 0.0f, 1.0f); }

  void set_y(const float y) noexcept { mEvent.y = detail::clamp(y, 0.0f, 1.0f); }

  void set_dx(const float dx) noexcept { mEvent.dx = detail::clamp(dx, -1.0f, 1.0f); }

  void set_dy(const float dy) noexcept { mEvent.dy = detail::clamp(dy, -1.0f, 1.0f); }

  void set_pressure(const float pressure) noexcept
  {
    mEvent.pressure = detail::clamp(pressure, 0.0f, 1.0f);
  }

  [[nodiscard]] auto touch_id() const noexcept -> SDL_TouchID { return mEvent.touchId; }

  [[nodiscard]] auto finger_id() const noexcept -> SDL_FingerID { return mEvent.fingerId; }

#if SDL_VERSION_ATLEAST(2, 0, 12)

  [[nodiscard]] auto window_id() const noexcept -> Uint32 { return mEvent.windowID; }

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

  [[nodiscard]] auto x() const noexcept -> float { return mEvent.x; }

  [[nodiscard]] auto y() const noexcept -> float { return mEvent.y; }

  [[nodiscard]] auto dx() const noexcept -> float { return mEvent.dx; }

  [[nodiscard]] auto dy() const noexcept -> float { return mEvent.dy; }

  [[nodiscard]] auto pressure() const noexcept -> float { return mEvent.pressure; }
};

class UserEvent final : public EventBase<SDL_UserEvent> {
 public:
  UserEvent() noexcept : EventBase{EventType::User} {}

  explicit UserEvent(const SDL_UserEvent& event) noexcept : EventBase{event} {}

  void SetWindowID(const Uint32 id) noexcept { mEvent.windowID = id; }

  void SetCode(const Sint32 code) noexcept { mEvent.code = code; }

  void SetData1(void* data) noexcept { mEvent.data1 = data; }
  void SetData2(void* data) noexcept { mEvent.data2 = data; }

  [[nodiscard]] auto GetWindowID() const noexcept -> Uint32 { return mEvent.windowID; }

  [[nodiscard]] auto GetCode() const noexcept -> Sint32 { return mEvent.code; }

  [[nodiscard]] auto GetData1() noexcept -> void* { return mEvent.data1; }
  [[nodiscard]] auto GetData1() const noexcept -> const void* { return mEvent.data1; }

  [[nodiscard]] auto GetData2() noexcept -> void* { return mEvent.data2; }
  [[nodiscard]] auto GetData2() const noexcept -> const void* { return mEvent.data2; }
};

class WindowEvent final : public EventBase<SDL_WindowEvent> {
 public:
  WindowEvent() noexcept : EventBase{EventType::Window} {}

  explicit WindowEvent(const SDL_WindowEvent& event) noexcept : EventBase{event} {}

  void SetEventID(const WindowEventID id) noexcept { mEvent.event = static_cast<Uint8>(id); }

  void SetData1(const Sint32 value) noexcept { mEvent.data1 = value; }
  void SetData2(const Sint32 value) noexcept { mEvent.data2 = value; }

  [[nodiscard]] auto GetEventID() const noexcept -> WindowEventID
  {
    return static_cast<WindowEventID>(mEvent.event);
  }

  [[nodiscard]] auto GetData1() const noexcept -> Sint32 { return mEvent.data1; }
  [[nodiscard]] auto GetData2() const noexcept -> Sint32 { return mEvent.data2; }
};

template <typename T>
[[nodiscard]] auto AsSDLEvent(const EventBase<T>& event) -> SDL_Event;

template <>
inline auto AsSDLEvent(const EventBase<SDL_QuitEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.quit = event.get();
  return e;
}

template <>
inline auto AsSDLEvent(const EventBase<SDL_AudioDeviceEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.adevice = event.get();
  return e;
}

template <>
inline auto AsSDLEvent(const EventBase<SDL_JoyAxisEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.jaxis = event.get();
  return e;
}

template <>
inline auto AsSDLEvent(const EventBase<SDL_JoyBallEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.jball = event.get();
  return e;
}

template <>
inline auto AsSDLEvent(const EventBase<SDL_JoyButtonEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.jbutton = event.get();
  return e;
}

template <>
inline auto AsSDLEvent(const EventBase<SDL_JoyDeviceEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.jdevice = event.get();
  return e;
}

template <>
inline auto AsSDLEvent(const EventBase<SDL_JoyHatEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.jhat = event.get();
  return e;
}

template <>
inline auto AsSDLEvent(const EventBase<SDL_ControllerAxisEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.caxis = event.get();
  return e;
}

template <>
inline auto AsSDLEvent(const EventBase<SDL_ControllerButtonEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.cbutton = event.get();
  return e;
}

template <>
inline auto AsSDLEvent(const EventBase<SDL_ControllerDeviceEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.cdevice = event.get();
  return e;
}

#if SDL_VERSION_ATLEAST(2, 0, 14)

template <>
inline auto AsSDLEvent(const EventBase<SDL_ControllerSensorEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.csensor = event.get();
  return e;
}

template <>
inline auto AsSDLEvent(const EventBase<SDL_ControllerTouchpadEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.ctouchpad = event.get();
  return e;
}

template <>
inline auto AsSDLEvent(const EventBase<SDL_DisplayEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.display = event.get();
  return e;
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

template <>
inline auto AsSDLEvent(const EventBase<SDL_DollarGestureEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.dgesture = event.get();
  return e;
}

template <>
inline auto AsSDLEvent(const EventBase<SDL_DropEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.drop = event.get();
  return e;
}

template <>
inline auto AsSDLEvent(const EventBase<SDL_KeyboardEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.key = event.get();
  return e;
}

template <>
inline auto AsSDLEvent(const EventBase<SDL_MouseButtonEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.button = event.get();
  return e;
}

template <>
inline auto AsSDLEvent(const EventBase<SDL_MouseMotionEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.motion = event.get();
  return e;
}

template <>
inline auto AsSDLEvent(const EventBase<SDL_MouseWheelEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.wheel = event.get();
  return e;
}

template <>
inline auto AsSDLEvent(const EventBase<SDL_MultiGestureEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.mgesture = event.get();
  return e;
}

template <>
inline auto AsSDLEvent(const EventBase<SDL_SensorEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.sensor = event.get();
  return e;
}

template <>
inline auto AsSDLEvent(const EventBase<SDL_TextEditingEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.edit = event.get();
  return e;
}

template <>
inline auto AsSDLEvent(const EventBase<SDL_TextInputEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.text = event.get();
  return e;
}

template <>
inline auto AsSDLEvent(const EventBase<SDL_TouchFingerEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.tfinger = event.get();
  return e;
}

template <>
inline auto AsSDLEvent(const EventBase<SDL_UserEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.user = event.get();
  return e;
}

template <>
inline auto AsSDLEvent(const EventBase<SDL_WindowEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.window = event.get();
  return e;
}

[[nodiscard]] constexpr auto to_string(const EventType type) -> std::string_view
{
  switch (type) {
    case EventType::Quit:
      return "Quit";

    case EventType::AppTerminating:
      return "AppTerminating";

    case EventType::AppLowMemory:
      return "AppLowMemory";

    case EventType::AppWillEnterBackground:
      return "AppWillEnterBackground";

    case EventType::AppDidEnterBackground:
      return "AppDidEnterBackground";

    case EventType::AppWillEnterForeground:
      return "AppWillEnterForeground";

    case EventType::AppDidEnterForeground:
      return "AppDidEnterForeground";

#if SDL_VERSION_ATLEAST(2, 0, 14)
    case EventType::LocaleChanged:
      return "LocaleChanged";
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

    case EventType::Display:
      return "Display";

    case EventType::Window:
      return "Window";

    case EventType::System:
      return "System";

    case EventType::KeyDown:
      return "KeyDown";

    case EventType::KeyUp:
      return "KeyUp";

    case EventType::TextEditing:
      return "TextEditing";

    case EventType::TextInput:
      return "TextInput";

    case EventType::KeymapChanged:
      return "KeymapChanged";

    case EventType::MouseMotion:
      return "MouseMotion";

    case EventType::MouseButtonDown:
      return "MouseButtonDown";

    case EventType::MouseButtonUp:
      return "MouseButtonUp";

    case EventType::MouseWheel:
      return "MouseWheel";

    case EventType::JoyAxisMotion:
      return "JoyAxisMotion";

    case EventType::JoyBallMotion:
      return "JoyBallMotion";

    case EventType::JoyHatMotion:
      return "JoyHatMotion";

    case EventType::JoyButtonDown:
      return "JoyButtonDown";

    case EventType::JoyButtonUp:
      return "JoyButtonUp";

    case EventType::JoyDeviceAdded:
      return "JoyDeviceAdded";

    case EventType::JoyDeviceRemoved:
      return "JoyDeviceRemoved";

    case EventType::ControllerAxisMotion:
      return "ControllerAxisMotion";

    case EventType::ControllerButtonDown:
      return "ControllerButtonDown";

    case EventType::ControllerButtonUp:
      return "ControllerButtonUp";

    case EventType::ControllerDeviceAdded:
      return "ControllerDeviceAdded";

    case EventType::ControllerDeviceRemoved:
      return "ControllerDeviceRemoved";

    case EventType::ControllerDeviceRemapped:
      return "ControllerDeviceRemapped";

#if SDL_VERSION_ATLEAST(2, 0, 14)
    case EventType::ControllerTouchpadDown:
      return "ControllerTouchpadDown";

    case EventType::ControllerTouchpadUp:
      return "ControllerTouchpadUp";

    case EventType::ControllerTouchpadMotion:
      return "ControllerTouchpadMotion";

    case EventType::ControllerSensorUpdate:
      return "ControllerSensorUpdate";
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

    case EventType::FingerDown:
      return "FingerDown";

    case EventType::FingerUp:
      return "FingerUp";

    case EventType::FingerMotion:
      return "FingerMotion";

    case EventType::DollarGesture:
      return "DollarGesture";

    case EventType::DollarRecord:
      return "DollarRecord";

    case EventType::MultiGesture:
      return "MultiGesture";

    case EventType::ClipboardUpdate:
      return "ClipboardUpdate";

    case EventType::DropFile:
      return "DropFile";

    case EventType::DropText:
      return "DropText";

    case EventType::DropBegin:
      return "DropBegin";

    case EventType::DropComplete:
      return "DropComplete";

    case EventType::AudioDeviceAdded:
      return "AudioDeviceAdded";

    case EventType::AudioDeviceRemoved:
      return "AudioDeviceRemoved";

    case EventType::SensorUpdate:
      return "SensorUpdate";

    case EventType::RenderTargetsReset:
      return "RenderTargetsReset";

    case EventType::RenderDeviceReset:
      return "RenderDeviceReset";

    case EventType::User:
      return "User";

    default:
      throw Error{"Did not recognize event type!"};
  }
}

inline auto operator<<(std::ostream& stream, const EventType type) -> std::ostream&
{
  return stream << to_string(type);
}

[[nodiscard]] constexpr auto to_string(const JoyHatPosition position) -> std::string_view
{
  switch (position) {
    case JoyHatPosition::LeftUp:
      return "LeftUp";

    case JoyHatPosition::Left:
      return "Left";

    case JoyHatPosition::LeftDown:
      return "LeftDown";

    case JoyHatPosition::Up:
      return "Up";

    case JoyHatPosition::Centered:
      return "Centered";

    case JoyHatPosition::Down:
      return "Down";

    case JoyHatPosition::RightUp:
      return "RightUp";

    case JoyHatPosition::Right:
      return "Right";

    case JoyHatPosition::RightDown:
      return "RightDown";

    default:
      throw Error{"Did not recognize joystick hat position!"};
  }
}

inline auto operator<<(std::ostream& stream, const JoyHatPosition position) -> std::ostream&
{
  return stream << to_string(position);
}

#if SDL_VERSION_ATLEAST(2, 0, 14)

[[nodiscard]] constexpr auto to_string(const DisplayEventID id) -> std::string_view
{
  switch (id) {
    case DisplayEventID::None:
      return "None";

    case DisplayEventID::Orientation:
      return "Orientation";

    case DisplayEventID::Connected:
      return "Connected";

    case DisplayEventID::Disconnected:
      return "Disconnected";

    default:
      throw Error{"Did not recognize display event ID!"};
  }
}

inline auto operator<<(std::ostream& stream, const DisplayEventID id) -> std::ostream&
{
  return stream << to_string(id);
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

[[nodiscard]] constexpr auto to_string(const MouseWheelDirection dir) -> std::string_view
{
  switch (dir) {
    case MouseWheelDirection::Normal:
      return "Normal";

    case MouseWheelDirection::Flipped:
      return "Flipped";

    default:
      throw Error{"Did not recognize mouse wheel direction!"};
  }
}

inline auto operator<<(std::ostream& stream, const MouseWheelDirection dir) -> std::ostream&
{
  return stream << to_string(dir);
}

[[nodiscard]] constexpr auto to_string(const WindowEventID id) -> std::string_view
{
  switch (id) {
    case WindowEventID::None:
      return "None";

    case WindowEventID::Shown:
      return "Shown";

    case WindowEventID::Hidden:
      return "Hidden";

    case WindowEventID::Exposed:
      return "Exposed";

    case WindowEventID::Moved:
      return "Moved";

    case WindowEventID::Resized:
      return "Resized";

    case WindowEventID::SizeChanged:
      return "SizeChanged";

    case WindowEventID::Minimized:
      return "Minimized";

    case WindowEventID::Maximized:
      return "Maximized";

    case WindowEventID::Restored:
      return "Restored";

    case WindowEventID::Enter:
      return "Enter";

    case WindowEventID::Leave:
      return "Leave";

    case WindowEventID::FocusGained:
      return "FocusGained";

    case WindowEventID::FocusLost:
      return "FocusLost";

    case WindowEventID::Close:
      return "Close";

    case WindowEventID::TakeFocus:
      return "TakeFocus";

    case WindowEventID::HitTest:
      return "HitTest";

    default:
      throw Error{"Did not recognize window event ID!"};
  }
}

inline auto operator<<(std::ostream& stream, const WindowEventID id) -> std::ostream&
{
  return stream << to_string(id);
}

}  // namespace cen

#endif  // CENTURION_EVENTS_HPP_
