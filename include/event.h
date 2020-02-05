#pragma once
#include <cstdint>
#include <SDL.h>
#include "centurion_api.h"

namespace centurion::event {

// TODO decide whether or not the methods should prefer int over uint32_t

/**
 * The EventType enum class mirrors the SDL_EventType enum.
 *
 * @since 3.1.0
 */
enum class EventType {
  Quit = SDL_QUIT,

  AppTerminating = SDL_APP_TERMINATING,
  AppLowMemory = SDL_APP_LOWMEMORY,
  AppWillEnterBackground = SDL_APP_WILLENTERBACKGROUND,
  AppDidEnterBackground = SDL_APP_DIDENTERBACKGROUND,
  AppDidEnterForeground = SDL_APP_DIDENTERFOREGROUND,

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

  JoystickAxisMotion = SDL_JOYAXISMOTION,
  JoystickBallMotion = SDL_JOYBALLMOTION,
  JoystickHatMotion = SDL_JOYHATMOTION,
  JoystickButtonDown = SDL_JOYBUTTONDOWN,
  JoystickButtonUp = SDL_JOYBUTTONUP,
  JoystickDeviceAdded = SDL_JOYDEVICEADDED,
  JoystickDeviceRemoved = SDL_JOYDEVICEREMOVED,

  ControllerAxisMotion = SDL_CONTROLLERAXISMOTION,
  ControllerButtonDown = SDL_CONTROLLERBUTTONDOWN,
  ControllerButtonUp = SDL_CONTROLLERBUTTONUP,
  ControllerDeviceAdded = SDL_CONTROLLERDEVICEADDED,
  ControllerDeviceRemoved = SDL_CONTROLLERDEVICEREMOVED,
  ControllerDeviceRemapped = SDL_CONTROLLERDEVICEREMAPPED,

  TouchDown = SDL_FINGERDOWN,
  TouchUp = SDL_FINGERUP,
  TouchMotion = SDL_FINGERMOTION,

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

  User = SDL_USEREVENT // no real support for custom user events
};

/**
 * Indicates whether or not two event type values are the same.
 *
 * @param lhs the left-hand side Centurion value.
 * @param rhs the right-hand side SDL value.
 * @return true if the values represent the same event type; false otherwise.
 * @since 3.1.0
 */
[[nodiscard]]
inline bool operator==(EventType lhs, SDL_EventType rhs) noexcept {
  return static_cast<SDL_EventType>(lhs) == rhs;
}

/**
 * Indicates whether or not two event type values are the same.
 *
 * @param lhs the left-hand side SDL value.
 * @param rhs the right-hand side Centurion value.
 * @return true if the values represent the same event type; false otherwise.
 * @since 3.1.0
 */
[[nodiscard]]
inline bool operator==(SDL_EventType lhs, EventType rhs) noexcept {
  return lhs == static_cast<SDL_EventType>(rhs);
}

/**
 * Indicates whether or not two event type values aren't the same.
 *
 * @param lhs the left-hand side Centurion value.
 * @param rhs the right-hand side SDL value.
 * @return true if the values don't represent the same event type; false otherwise.
 * @since 3.1.0
 */
[[nodiscard]]
inline bool operator!=(EventType lhs, SDL_EventType rhs) noexcept {
  return !(lhs == rhs);
}

/**
 * Indicates whether or not two event type values aren't the same.
 *
 * @param lhs the left-hand side SDL value.
 * @param rhs the right-hand side Centurion value.
 * @return true if the values don't represent the same event type; false otherwise.
 * @since 3.1.0
 */
[[nodiscard]]
inline bool operator!=(SDL_EventType lhs, EventType rhs) noexcept {
  return !(lhs == rhs);
}

/**
 * The ButtonState enum class provides the possible states for a button.
 *
 * @since 3.1.0
 */
enum class ButtonState {
  Released = SDL_RELEASED,
  Pressed = SDL_PRESSED
};

/**
 * The KeyModifier enum class mirrors the values of the SDL_Keymod enum.
 *
 * @since 3.1.0
 */
enum class KeyModifier {
  None = KMOD_NONE,
  LeftShift = KMOD_LSHIFT,
  RightShift = KMOD_RSHIFT,
  LeftControl = KMOD_LCTRL,
  RightControl = KMOD_RCTRL,
  LeftAlt = KMOD_LALT,
  RightAlt = KMOD_RALT,
  LeftGUI = KMOD_LGUI,
  RightGUI = KMOD_RGUI,
  Num = KMOD_NUM,
  Caps = KMOD_CAPS,
  Mode = KMOD_MODE
};

/**
 * Indicates whether or not two key modifier values are the same.
 *
 * @param lhs the left-hand side Centurion value.
 * @param rhs the right-hand side SDL value.
 * @return true if the key modifier values are the same; false otherwise.
 * @since 3.1.0
 */
[[nodiscard]]
inline bool operator==(KeyModifier lhs, SDL_Keymod rhs) noexcept {
  return static_cast<SDL_Keymod>(lhs) == rhs;
}

/**
 * Indicates whether or not two key modifier values are the same.
 *
 * @param lhs the left-hand side SDL value.
 * @param rhs the right-hand side Centurion value.
 * @return true if the key modifier values are the same; false otherwise.
 * @since 3.1.0
 */
[[nodiscard]]
inline bool operator==(SDL_Keymod lhs, KeyModifier rhs) noexcept {
  return lhs == static_cast<SDL_Keymod>(rhs);
}

/**
 * Indicates whether or not two key modifier values aren't the same.
 *
 * @param lhs the left-hand side Centurion value.
 * @param rhs the right-hand side SDL value.
 * @return true if the key modifier values aren't the same; false otherwise.
 * @since 3.1.0
 */
[[nodiscard]]
inline bool operator!=(KeyModifier lhs, SDL_Keymod rhs) noexcept {
  return !(lhs == rhs);
}

/**
 * Indicates whether or not two key modifier values aren't the same.
 *
 * @param lhs the left-hand side SDL value.
 * @param rhs the right-hand side Centurion value.
 * @return true if the key modifier values aren't the same; false otherwise.
 * @since 3.1.0
 */
[[nodiscard]]
inline bool operator!=(SDL_Keymod lhs, KeyModifier rhs) noexcept {
  return !(lhs == rhs);
}

/**
 * The KeyEvent class is a wrapper for the SDL_KeyboardEvent struct.
 *
 * @since 3.1.0
 */
class CENTURION_API KeyEvent final {
 private:
  SDL_KeyboardEvent event;

 public:
  /**
   * @param keyEvent the associated keyboard event.
   * @since 3.1.0
   */
  CENTURION_API explicit KeyEvent(SDL_KeyboardEvent keyEvent) noexcept;

  /**
   * Indicates whether or not the supplied keycode represents the same key that triggered this
   * keyboard event.
   *
   * @param keycode the keycode of the key that will be checked.
   * @return true if the key associated with the supplied keycode caused this keyboard event;
   * false otherwise.
   * @since 3.1.0
   */
  [[nodiscard]]
  CENTURION_API bool is_key_active(SDL_Keycode keycode) const noexcept;

  /**
   * Indicates whether or not the supplied scancode represents the same key that triggered this
   * keyboard event.
   *
   * @param scancode the scancode of the key that will be checked.
   * @return true if the key associated with the supplied scancode caused this keyboard event;
   * false otherwise.
   * @since 3.1.0
   */
  [[nodiscard]]
  CENTURION_API bool is_key_active(SDL_Scancode scancode) const noexcept;

  /**
   * Indicates whether or not the specified key modifier is active. Multiple key modifiers can be
   * active at the same time.
   *
   * @param modifier the key modifier that will be checked.
   * @return true if the specified key modifier is active; false otherwise.
   * @since 3.1.0
   */
  [[nodiscard]]
  CENTURION_API bool is_modifier_active(KeyModifier modifier) const noexcept;

  /**
   * Indicates whether or not any of the CTRL-keys are associated with the keyboard event.
   *
   * @return true if any of the CTRL-keys are associated with the keyboard event; false otherwise.
   * @since 3.1.0
   */
  [[nodiscard]]
  CENTURION_API bool is_control_active() const noexcept;

  /**
   * Indicates whether or not any of the Shift-keys are associated with the keyboard event.
   *
   * @return true if any of the Shift-keys are associated with the keyboard event; false otherwise.
   * @since 3.1.0
   */
  [[nodiscard]]
  CENTURION_API bool is_shift_active() const noexcept;

  /**
   * Indicates whether or not any of the Alt-keys are associated with the keyboard event.
   *
   * @return true if any of the Alt-keys are associated with the keyboard event; false otherwise.
   * @since 3.1.0
   */
  [[nodiscard]]
  CENTURION_API bool is_alt_active() const noexcept;

  /**
   * Indicates whether or not any of the GUI-keys are associated with the keyboard event.
   *
   * @return true if any of the GUI-keys are associated with the keyboard event; false otherwise.
   * @since 3.1.0
   */
  [[nodiscard]]
  CENTURION_API bool is_gui_active() const noexcept;

  /**
   * Indicates whether or not the key associated with this key event was repeatedly triggered.
   *
   * @return true if the key associated with the event was repeated; false otherwise.
   * @since 3.1.0
   */
  [[nodiscard]]
  CENTURION_API bool is_repeated() const noexcept;

  /**
   * Returns the button state of the key associated with the event.
   *
   * @return the button state of the key associated with the event.
   * @since 3.1.0
   */
  [[nodiscard]]
  CENTURION_API ButtonState get_state() const noexcept;

  /**
   * Returns the ID of the parent window of the keyboard event.
   *
   * @return the ID of the parent window of the keyboard event.
   * @since 3.1.0
   */
  [[nodiscard]]
  CENTURION_API uint32_t get_window_id() const noexcept;

  /**
   * Returns the time that the event was created. The value is obtained through SDL_GetTicks.
   *
   * @return the time that the event was created, in milliseconds.
   * @since 3.1.0
   */
  [[nodiscard]]
  CENTURION_API uint32_t get_time() const noexcept;
};

/**
 * The MouseButton enum class provides values that represent various mouse buttons.
 *
 * @since 3.1.0
 */
enum class MouseButton {
  Left = SDL_BUTTON_LEFT,
  Middle = SDL_BUTTON_MIDDLE,
  Right = SDL_BUTTON_RIGHT,
  X1 = SDL_BUTTON_X1,
  X2 = SDL_BUTTON_X2
};

/**
 * The MouseButtonEvent class is a wrapper class for the SDL_MouseButtonEvent struct.
 *
 * @since 3.1.0
 */
class CENTURION_API MouseButtonEvent final {
 private:
  SDL_MouseButtonEvent event;

 public:
  /**
   * @param buttonEvent the associated SDL mouse button event.
   * @since 3.1.0
   */
  CENTURION_API explicit MouseButtonEvent(SDL_MouseButtonEvent buttonEvent) noexcept;

  /**
   * Returns the mouse button that triggered the event.
   *
   * @return the mouse button that triggered the event.
   * @since 3.1.0
   */
  [[nodiscard]]
  CENTURION_API MouseButton get_button() const noexcept;

  /**
   * Returns the x-coordinate of the mouse.
   *
   * @return the x-coordinate of the mouse.
   * @since 3.1.0
   */
  [[nodiscard]]
  CENTURION_API int get_x() const noexcept;

  /**
   * Returns the y-coordinate of the mouse.
   *
   * @return the y-coordinate of the mouse.
   * @since 3.1.0
   */
  [[nodiscard]]
  CENTURION_API int get_y() const noexcept;

  /**
   * Returns the state of the mouse button that triggered the event.
   *
   * @return the state of the mouse button that triggered the event.
   * @since 3.1.0
   */
  [[nodiscard]]
  CENTURION_API ButtonState get_state() const noexcept;

  /**
   * Indicates whether or not a single-click triggered the event.
   *
   * @return true if a single-click triggered the event; false otherwise.
   * @since 3.1.0
   */
  [[nodiscard]]
  CENTURION_API bool was_single_click() const noexcept;

  /**
   * Indicates whether or not a double-click triggered the event.
   *
   * @return true if a double-click triggered the event; false otherwise.
   * @since 3.1.0
   */
  [[nodiscard]]
  CENTURION_API bool was_double_click() const noexcept;

  /**
   * Indicates whether or not the event was triggered by a touch input device.
   *
   * @return true if the event was triggered by a touch input device; false otherwise.
   * @since 3.1.0
   */
  [[nodiscard]]
  CENTURION_API bool was_touch() const noexcept;

  /**
   * Returns the ID of the window with mouse focus.
   *
   * @return the ID of the window with mouse focus.
   * @since 3.1.0
   */
  [[nodiscard]]
  CENTURION_API uint32_t get_window_id() const noexcept;

  /**
   * Returns the time that the event was created. The value is obtained through SDL_GetTicks.
   *
   * @return the time that the event was created, in milliseconds.
   * @since 3.1.0
   */
  [[nodiscard]]
  CENTURION_API uint32_t get_time() const noexcept;
};

/**
 * The MouseMotionEvent class is a wrapper for the SDL_MouseMotionEvent struct.
 *
 * @since 3.1.0
 */
class CENTURION_API MouseMotionEvent final {
 private:
  SDL_MouseMotionEvent event;

 public:
  /**
   * @param motionEvent the associated SDL mouse motion event.
   * @since 3.1.0
   */
  CENTURION_API explicit MouseMotionEvent(SDL_MouseMotionEvent motionEvent) noexcept;

  /**
   * Returns the x-coordinate of the mouse.
   *
   * @return the x-coordinate of the mouse.
   * @since 3.1.0
   */
  [[nodiscard]]
  CENTURION_API int get_x() const noexcept;

  /**
   * Returns the y-coordinate of the mouse.
   *
   * @return the y-coordinate of the mouse.
   * @since 3.1.0
   */
  [[nodiscard]]
  CENTURION_API int get_y() const noexcept;

  /**
   * Returns the relative motion of the mouse, along the x-axis.
   *
   * @return the relative motion of the mouse, along the x-axis.
   * @since 3.1.0
   */
  [[nodiscard]]
  CENTURION_API int get_x_movement() const noexcept;

  /**
   * Returns the relative motion of the mouse, along the y-axis.
   *
   * @return the relative motion of the mouse, along the y-axis.
   * @since 3.1.0
   */
  [[nodiscard]]
  CENTURION_API int get_y_movement() const noexcept;

  /**
   * Indicates whether or not the event was triggered by a touch input device.
   *
   * @return true if the event was triggered by a touch input device; false otherwise.
   * @since 3.1.0
   */
  [[nodiscard]]
  CENTURION_API bool was_touch() const noexcept;

  /**
   * Indicates whether or not a mouse button is down.
   *
   * @param button the mouse button that will be checked.
   * @return true if the specified mouse button is down; false otherwise.
   * @since 3.1.0
   */
  [[nodiscard]]
  CENTURION_API bool is_button_down(MouseButton button) const noexcept;

  /**
   * Returns the ID of the window with mouse focus.
   *
   * @return the ID of the window with mouse focus.
   * @since 3.1.0
   */
  [[nodiscard]]
  CENTURION_API uint32_t get_window_id() const noexcept;

  /**
   * Returns the time that the event was created. The value is obtained through SDL_GetTicks.
   *
   * @return the time that the event was created, in milliseconds.
   * @since 3.1.0
   */
  [[nodiscard]]
  CENTURION_API uint32_t get_time() const noexcept;
};

/**
 * The MouseWheelDirection enum class mirrors the values of the SDL_MouseWheelDirection enum.
 *
 * @since 3.1.0
 */
enum class MouseWheelDirection {
  Normal = SDL_MOUSEWHEEL_NORMAL,
  Flipped = SDL_MOUSEWHEEL_FLIPPED
};

/**
 * The MouseWheelEvent class is a wrapper for the SDL_MouseWheelEvent struct.
 *
 * @since 3.1.0
 */
class CENTURION_API MouseWheelEvent final {
 private:
  SDL_MouseWheelEvent event;

 public:
  /**
   * @param wheelEvent the associated SDL mouse wheel event.
   * @since 3.1.0
   */
  CENTURION_API explicit MouseWheelEvent(SDL_MouseWheelEvent wheelEvent) noexcept;

  /**
   * Returns the amount scrolled horizontally.
   *
   * @return the amount scrolled horizontally.
   * @since 3.1.0
   */
  [[nodiscard]]
  CENTURION_API int get_horizontal_scroll() const noexcept;

  /**
   * Returns the amount scrolled vertically.
   *
   * @return the amount scrolled vertically.
   * @since 3.1.0
   */
  [[nodiscard]]
  CENTURION_API int get_vertical_scroll() const noexcept;

  /**
   * Returns the direction of the mouse wheel.
   *
   * @return the direction of the mouse wheel.
   * @since 3.1.0
   */
  [[nodiscard]]
  CENTURION_API MouseWheelDirection get_wheel_direction() const noexcept;

  /**
   * Indicates whether or not the event was triggered by a touch input device.
   *
   * @return true if the event was triggered by a touch input device; false otherwise.
   * @since 3.1.0
   */
  [[nodiscard]]
  CENTURION_API bool was_touch() const noexcept;

  /**
   * Returns the ID of the window with mouse focus.
   *
   * @return the ID of the window with mouse focus.
   * @since 3.1.0
   */
  [[nodiscard]]
  CENTURION_API uint32_t get_window_id() const noexcept;

  /**
   * Returns the time that the event was created. The value is obtained through SDL_GetTicks.
   *
   * @return the time that the event was created, in milliseconds.
   * @since 3.1.0
   */
  [[nodiscard]]
  CENTURION_API uint32_t get_time() const noexcept;
};

/**
 * The QuitEvent class is a wrapper for the SDL_QuitEvent struct.
 *
 * @since 3.1.0
 */
class CENTURION_API QuitEvent final {
 private:
  uint32_t time;

 public:
  /**
   * @param quitEvent the associated quit event.
   * @since 3.1.0
   */
  CENTURION_API explicit QuitEvent(SDL_QuitEvent quitEvent) noexcept;

  /**
   * Returns the time that the event was created. The value is obtained through SDL_GetTicks.
   *
   * @return the time that the event was created, in milliseconds.
   * @since 3.1.0
   */
  [[nodiscard]]
  CENTURION_API uint32_t get_time() const noexcept;
};

/**
 * The Event class is a wrapper for the SDL_Event struct.
 *
 * @since 3.1.0
 */
class CENTURION_API Event final {
 private:
  SDL_Event event;

 public:
  /**
   * Flushes all current events from the event queue.
   *
   * @since 3.1.0
   */
  CENTURION_API static void flush() noexcept;

  /**
   * Polls the next available event, if there is one.
   *
   * @return true if there are any pending events; false otherwise.
   * @since 3.1.0
   */
  [[nodiscard]]
  CENTURION_API bool poll() noexcept;

  /**
   * Returns the type of the event. This method can always be safely called on an event instance.
   *
   * @return the type of the event.
   * @since 3.1.0
   */
  [[nodiscard]]
  CENTURION_API EventType get_type() const noexcept;

  /**
   * Returns the internal SDL event as a key event. Ensure that the actual type of the internal
   * event is a key event, otherwise you might end up with undefined behaviour!
   *
   * @return the internal event as a key event.
   * @since 3.1.0
   */
  [[nodiscard]]
  CENTURION_API KeyEvent as_key_event() const noexcept;

  [[nodiscard]]
  CENTURION_API MouseButtonEvent as_mouse_button_event() const noexcept;

  [[nodiscard]]
  CENTURION_API MouseMotionEvent as_mouse_motion_event() const noexcept;

  [[nodiscard]]
  CENTURION_API MouseWheelEvent as_mouse_wheel_event() const noexcept;

  /**
   * Returns the internal SDL event as a quit event. Ensure that the actual type of the internal
   * event is a quit event, otherwise you might end up with undefined behaviour!
   *
   * @return the internal event as a quit event.
   * @since 3.1.0
   */
  [[nodiscard]]
  CENTURION_API QuitEvent as_quit_event() const noexcept;
};

}
