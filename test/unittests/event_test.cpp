#include <catch.hpp>

#include "event_type.h"

using namespace centurion::event;

TEST_CASE("EventType operator==", "[EventType]")
{
  CHECK(EventType::Quit == SDL_EventType::SDL_QUIT);
  CHECK(EventType::AppTerminating == SDL_APP_TERMINATING);
  CHECK(EventType::AppLowMemory == SDL_APP_LOWMEMORY);
  CHECK(EventType::AppWillEnterBackground == SDL_APP_WILLENTERBACKGROUND);
  CHECK(EventType::AppDidEnterBackground == SDL_APP_DIDENTERBACKGROUND);
  CHECK(EventType::AppDidEnterForeground == SDL_APP_DIDENTERFOREGROUND);
  CHECK(EventType::Display == SDL_DISPLAYEVENT);
  CHECK(EventType::Window == SDL_WINDOWEVENT);
  CHECK(EventType::System == SDL_SYSWMEVENT);
  CHECK(EventType::KeyDown == SDL_KEYDOWN);
  CHECK(EventType::KeyUp == SDL_KEYUP);
  CHECK(EventType::TextEditing == SDL_TEXTEDITING);
  CHECK(EventType::TextInput == SDL_TEXTINPUT);
  CHECK(EventType::KeymapChanged == SDL_KEYMAPCHANGED);
  CHECK(EventType::MouseMotion == SDL_MOUSEMOTION);
  CHECK(EventType::MouseButtonDown == SDL_MOUSEBUTTONDOWN);
  CHECK(EventType::MouseButtonUp == SDL_MOUSEBUTTONUP);
  CHECK(EventType::MouseWheel == SDL_MOUSEWHEEL);
  CHECK(EventType::JoystickAxisMotion == SDL_JOYAXISMOTION);
  CHECK(EventType::JoystickBallMotion == SDL_JOYBALLMOTION);
  CHECK(EventType::JoystickHatMotion == SDL_JOYHATMOTION);
  CHECK(EventType::JoystickButtonDown == SDL_JOYBUTTONDOWN);
  CHECK(EventType::JoystickButtonUp == SDL_JOYBUTTONUP);
  CHECK(EventType::JoystickDeviceAdded == SDL_JOYDEVICEADDED);
  CHECK(EventType::JoystickDeviceRemoved == SDL_JOYDEVICEREMOVED);
  CHECK(EventType::ControllerAxisMotion == SDL_CONTROLLERAXISMOTION);
  CHECK(EventType::ControllerButtonDown == SDL_CONTROLLERBUTTONDOWN);
  CHECK(EventType::ControllerButtonUp == SDL_CONTROLLERBUTTONUP);
  CHECK(EventType::ControllerDeviceAdded == SDL_CONTROLLERDEVICEADDED);
  CHECK(EventType::ControllerDeviceRemoved == SDL_CONTROLLERDEVICEREMOVED);
  CHECK(EventType::ControllerDeviceRemapped == SDL_CONTROLLERDEVICEREMAPPED);
  CHECK(EventType::TouchDown == SDL_FINGERDOWN);
  CHECK(EventType::TouchUp == SDL_FINGERUP);
  CHECK(EventType::TouchMotion == SDL_FINGERMOTION);
  CHECK(EventType::DollarGesture == SDL_DOLLARGESTURE);
  CHECK(EventType::DollarRecord == SDL_DOLLARRECORD);
  CHECK(EventType::MultiGesture == SDL_MULTIGESTURE);
  CHECK(EventType::ClipboardUpdate == SDL_CLIPBOARDUPDATE);
  CHECK(EventType::DropFile == SDL_DROPFILE);
  CHECK(EventType::DropText == SDL_DROPTEXT);
  CHECK(EventType::DropBegin == SDL_DROPBEGIN);
  CHECK(EventType::DropComplete == SDL_DROPCOMPLETE);
  CHECK(EventType::AudioDeviceAdded == SDL_AUDIODEVICEADDED);
  CHECK(EventType::AudioDeviceRemoved == SDL_AUDIODEVICEREMOVED);
  CHECK(EventType::SensorUpdate == SDL_SENSORUPDATE);
  CHECK(EventType::RenderTargetsReset == SDL_RENDER_TARGETS_RESET);
  CHECK(EventType::RenderDeviceReset == SDL_RENDER_DEVICE_RESET);
  CHECK(EventType::User == SDL_USEREVENT);

  CHECK(SDL_QUIT == EventType::Quit);
  CHECK(SDL_APP_TERMINATING == EventType::AppTerminating);
  CHECK(SDL_APP_LOWMEMORY == EventType::AppLowMemory);
  CHECK(SDL_APP_WILLENTERBACKGROUND == EventType::AppWillEnterBackground);
  CHECK(SDL_APP_DIDENTERBACKGROUND == EventType::AppDidEnterBackground);
  CHECK(SDL_APP_DIDENTERFOREGROUND == EventType::AppDidEnterForeground);
  CHECK(SDL_DISPLAYEVENT == EventType::Display);
  CHECK(SDL_WINDOWEVENT == EventType::Window);
  CHECK(SDL_SYSWMEVENT == EventType::System);
  CHECK(SDL_KEYDOWN == EventType::KeyDown);
  CHECK(SDL_KEYUP == EventType::KeyUp);
  CHECK(SDL_TEXTEDITING == EventType::TextEditing);
  CHECK(SDL_TEXTINPUT == EventType::TextInput);
  CHECK(SDL_KEYMAPCHANGED == EventType::KeymapChanged);
  CHECK(SDL_MOUSEMOTION == EventType::MouseMotion);
  CHECK(SDL_MOUSEBUTTONDOWN == EventType::MouseButtonDown);
  CHECK(SDL_MOUSEBUTTONUP == EventType::MouseButtonUp);
  CHECK(SDL_MOUSEWHEEL == EventType::MouseWheel);
  CHECK(SDL_JOYAXISMOTION == EventType::JoystickAxisMotion);
  CHECK(SDL_JOYBALLMOTION == EventType::JoystickBallMotion);
  CHECK(SDL_JOYHATMOTION == EventType::JoystickHatMotion);
  CHECK(SDL_JOYBUTTONDOWN == EventType::JoystickButtonDown);
  CHECK(SDL_JOYBUTTONUP == EventType::JoystickButtonUp);
  CHECK(SDL_JOYDEVICEADDED == EventType::JoystickDeviceAdded);
  CHECK(SDL_JOYDEVICEREMOVED == EventType::JoystickDeviceRemoved);
  CHECK(SDL_CONTROLLERAXISMOTION == EventType::ControllerAxisMotion);
  CHECK(SDL_CONTROLLERBUTTONDOWN == EventType::ControllerButtonDown);
  CHECK(SDL_CONTROLLERBUTTONUP == EventType::ControllerButtonUp);
  CHECK(SDL_CONTROLLERDEVICEADDED == EventType::ControllerDeviceAdded);
  CHECK(SDL_CONTROLLERDEVICEREMOVED == EventType::ControllerDeviceRemoved);
  CHECK(SDL_CONTROLLERDEVICEREMAPPED == EventType::ControllerDeviceRemapped);
  CHECK(SDL_FINGERDOWN == EventType::TouchDown);
  CHECK(SDL_FINGERUP == EventType::TouchUp);
  CHECK(SDL_FINGERMOTION == EventType::TouchMotion);
  CHECK(SDL_DOLLARGESTURE == EventType::DollarGesture);
  CHECK(SDL_DOLLARRECORD == EventType::DollarRecord);
  CHECK(SDL_MULTIGESTURE == EventType::MultiGesture);
  CHECK(SDL_CLIPBOARDUPDATE == EventType::ClipboardUpdate);
  CHECK(SDL_DROPFILE == EventType::DropFile);
  CHECK(SDL_DROPTEXT == EventType::DropText);
  CHECK(SDL_DROPBEGIN == EventType::DropBegin);
  CHECK(SDL_DROPCOMPLETE == EventType::DropComplete);
  CHECK(SDL_AUDIODEVICEADDED == EventType::AudioDeviceAdded);
  CHECK(SDL_AUDIODEVICEREMOVED == EventType::AudioDeviceRemoved);
  CHECK(SDL_SENSORUPDATE == EventType::SensorUpdate);
  CHECK(SDL_RENDER_TARGETS_RESET == EventType::RenderTargetsReset);
  CHECK(SDL_RENDER_DEVICE_RESET == EventType::RenderDeviceReset);
  CHECK(SDL_USEREVENT == EventType::User);
}

TEST_CASE("EventType operator!=", "[EventType]")
{
  CHECK(EventType::DollarGesture != SDL_RENDER_DEVICE_RESET);
  CHECK(SDL_MOUSEMOTION != EventType::ControllerDeviceRemoved);
}
