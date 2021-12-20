#ifndef CENTURION_EVENTS_EVENT_TYPE_HPP_
#define CENTURION_EVENTS_EVENT_TYPE_HPP_

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../common.hpp"
#include "../core/exception.hpp"

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

}  // namespace cen

#endif  // CENTURION_EVENTS_EVENT_TYPE_HPP_