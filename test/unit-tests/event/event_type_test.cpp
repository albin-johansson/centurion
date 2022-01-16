#include <gtest/gtest.h>

#include <iostream>  // clog

#include "common.hpp"
#include "event.hpp"

using Type = cen::EventType;

TEST(EventType, Values)
{
  ASSERT_EQ(to_underlying(Type::Quit), SDL_QUIT);

  ASSERT_EQ(to_underlying(Type::AppTerminating), SDL_APP_TERMINATING);
  ASSERT_EQ(to_underlying(Type::AppLowMemory), SDL_APP_LOWMEMORY);
  ASSERT_EQ(to_underlying(Type::AppWillEnterBackground), SDL_APP_WILLENTERBACKGROUND);
  ASSERT_EQ(to_underlying(Type::AppDidEnterBackground), SDL_APP_DIDENTERBACKGROUND);
  ASSERT_EQ(to_underlying(Type::AppDidEnterForeground), SDL_APP_DIDENTERFOREGROUND);

  ASSERT_EQ(to_underlying(Type::Display), SDL_DISPLAYEVENT);
  ASSERT_EQ(to_underlying(Type::Window), SDL_WINDOWEVENT);
  ASSERT_EQ(to_underlying(Type::System), SDL_SYSWMEVENT);

  ASSERT_EQ(to_underlying(Type::KeyDown), SDL_KEYDOWN);
  ASSERT_EQ(to_underlying(Type::KeyUp), SDL_KEYUP);
  ASSERT_EQ(to_underlying(Type::TextEditing), SDL_TEXTEDITING);
  ASSERT_EQ(to_underlying(Type::TextInput), SDL_TEXTINPUT);
  ASSERT_EQ(to_underlying(Type::KeymapChanged), SDL_KEYMAPCHANGED);

  ASSERT_EQ(to_underlying(Type::MouseMotion), SDL_MOUSEMOTION);
  ASSERT_EQ(to_underlying(Type::MouseButtonDown), SDL_MOUSEBUTTONDOWN);
  ASSERT_EQ(to_underlying(Type::MouseButtonUp), SDL_MOUSEBUTTONUP);
  ASSERT_EQ(to_underlying(Type::MouseWheel), SDL_MOUSEWHEEL);

  ASSERT_EQ(to_underlying(Type::JoyAxisMotion), SDL_JOYAXISMOTION);
  ASSERT_EQ(to_underlying(Type::JoyBallMotion), SDL_JOYBALLMOTION);
  ASSERT_EQ(to_underlying(Type::JoyHatMotion), SDL_JOYHATMOTION);
  ASSERT_EQ(to_underlying(Type::JoyButtonDown), SDL_JOYBUTTONDOWN);
  ASSERT_EQ(to_underlying(Type::JoyButtonUp), SDL_JOYBUTTONUP);
  ASSERT_EQ(to_underlying(Type::JoyDeviceAdded), SDL_JOYDEVICEADDED);
  ASSERT_EQ(to_underlying(Type::JoyDeviceRemoved), SDL_JOYDEVICEREMOVED);

  ASSERT_EQ(to_underlying(Type::ControllerAxisMotion), SDL_CONTROLLERAXISMOTION);
  ASSERT_EQ(to_underlying(Type::ControllerButtonDown), SDL_CONTROLLERBUTTONDOWN);
  ASSERT_EQ(to_underlying(Type::ControllerButtonUp), SDL_CONTROLLERBUTTONUP);
  ASSERT_EQ(to_underlying(Type::ControllerDeviceAdded), SDL_CONTROLLERDEVICEADDED);
  ASSERT_EQ(to_underlying(Type::ControllerDeviceRemoved), SDL_CONTROLLERDEVICEREMOVED);
  ASSERT_EQ(to_underlying(Type::ControllerDeviceRemapped), SDL_CONTROLLERDEVICEREMAPPED);

  ASSERT_EQ(to_underlying(Type::FingerDown), SDL_FINGERDOWN);
  ASSERT_EQ(to_underlying(Type::FingerUp), SDL_FINGERUP);
  ASSERT_EQ(to_underlying(Type::FingerMotion), SDL_FINGERMOTION);

  ASSERT_EQ(to_underlying(Type::DollarGesture), SDL_DOLLARGESTURE);
  ASSERT_EQ(to_underlying(Type::DollarRecord), SDL_DOLLARRECORD);
  ASSERT_EQ(to_underlying(Type::MultiGesture), SDL_MULTIGESTURE);

  ASSERT_EQ(to_underlying(Type::ClipboardUpdate), SDL_CLIPBOARDUPDATE);

  ASSERT_EQ(to_underlying(Type::DropFile), SDL_DROPFILE);
  ASSERT_EQ(to_underlying(Type::DropText), SDL_DROPTEXT);
  ASSERT_EQ(to_underlying(Type::DropBegin), SDL_DROPBEGIN);
  ASSERT_EQ(to_underlying(Type::DropComplete), SDL_DROPCOMPLETE);

  ASSERT_EQ(to_underlying(Type::AudioDeviceAdded), SDL_AUDIODEVICEADDED);
  ASSERT_EQ(to_underlying(Type::AudioDeviceRemoved), SDL_AUDIODEVICEREMOVED);

  ASSERT_EQ(to_underlying(Type::SensorUpdate), SDL_SENSORUPDATE);

  ASSERT_EQ(to_underlying(Type::RenderTargetsReset), SDL_RENDER_TARGETS_RESET);
  ASSERT_EQ(to_underlying(Type::RenderDeviceReset), SDL_RENDER_DEVICE_RESET);

  ASSERT_EQ(to_underlying(Type::User), SDL_USEREVENT);

#if SDL_VERSION_ATLEAST(2, 0, 14)
  ASSERT_EQ(to_underlying(Type::LocaleChanged), SDL_LOCALECHANGED);

  ASSERT_EQ(to_underlying(Type::ControllerTouchpadDown), SDL_CONTROLLERTOUCHPADDOWN);
  ASSERT_EQ(to_underlying(Type::ControllerTouchpadUp), SDL_CONTROLLERTOUCHPADUP);
  ASSERT_EQ(to_underlying(Type::ControllerTouchpadMotion), SDL_CONTROLLERTOUCHPADMOTION);
  ASSERT_EQ(to_underlying(Type::ControllerSensorUpdate), SDL_CONTROLLERSENSORUPDATE);
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)
}

TEST(EventType, ToString)
{
  ASSERT_EQ("Quit", ToString(Type::Quit));

  ASSERT_EQ("AppTerminating", ToString(Type::AppTerminating));
  ASSERT_EQ("AppLowMemory", ToString(Type::AppLowMemory));
  ASSERT_EQ("AppWillEnterBackground", ToString(Type::AppWillEnterBackground));
  ASSERT_EQ("AppDidEnterBackground", ToString(Type::AppDidEnterBackground));
  ASSERT_EQ("AppDidEnterForeground", ToString(Type::AppDidEnterForeground));

  ASSERT_EQ("Display", ToString(Type::Display));
  ASSERT_EQ("Window", ToString(Type::Window));
  ASSERT_EQ("System", ToString(Type::System));

  ASSERT_EQ("KeyDown", ToString(Type::KeyDown));
  ASSERT_EQ("KeyUp", ToString(Type::KeyUp));
  ASSERT_EQ("TextEditing", ToString(Type::TextEditing));
  ASSERT_EQ("TextInput", ToString(Type::TextInput));
  ASSERT_EQ("KeymapChanged", ToString(Type::KeymapChanged));

  ASSERT_EQ("MouseMotion", ToString(Type::MouseMotion));
  ASSERT_EQ("MouseButtonDown", ToString(Type::MouseButtonDown));
  ASSERT_EQ("MouseButtonUp", ToString(Type::MouseButtonUp));
  ASSERT_EQ("MouseWheel", ToString(Type::MouseWheel));

  ASSERT_EQ("JoyAxisMotion", ToString(Type::JoyAxisMotion));
  ASSERT_EQ("JoyBallMotion", ToString(Type::JoyBallMotion));
  ASSERT_EQ("JoyHatMotion", ToString(Type::JoyHatMotion));
  ASSERT_EQ("JoyButtonDown", ToString(Type::JoyButtonDown));
  ASSERT_EQ("JoyButtonUp", ToString(Type::JoyButtonUp));
  ASSERT_EQ("JoyDeviceAdded", ToString(Type::JoyDeviceAdded));
  ASSERT_EQ("JoyDeviceRemoved", ToString(Type::JoyDeviceRemoved));

  ASSERT_EQ("ControllerAxisMotion", ToString(Type::ControllerAxisMotion));
  ASSERT_EQ("ControllerButtonDown", ToString(Type::ControllerButtonDown));
  ASSERT_EQ("ControllerButtonUp", ToString(Type::ControllerButtonUp));
  ASSERT_EQ("ControllerDeviceAdded", ToString(Type::ControllerDeviceAdded));
  ASSERT_EQ("ControllerDeviceRemoved", ToString(Type::ControllerDeviceRemoved));
  ASSERT_EQ("ControllerDeviceRemapped", ToString(Type::ControllerDeviceRemapped));

  ASSERT_EQ("FingerDown", ToString(Type::FingerDown));
  ASSERT_EQ("FingerUp", ToString(Type::FingerUp));
  ASSERT_EQ("FingerMotion", ToString(Type::FingerMotion));

  ASSERT_EQ("DollarGesture", ToString(Type::DollarGesture));
  ASSERT_EQ("DollarRecord", ToString(Type::DollarRecord));
  ASSERT_EQ("MultiGesture", ToString(Type::MultiGesture));

  ASSERT_EQ("ClipboardUpdate", ToString(Type::ClipboardUpdate));

  ASSERT_EQ("DropFile", ToString(Type::DropFile));
  ASSERT_EQ("DropText", ToString(Type::DropText));
  ASSERT_EQ("DropBegin", ToString(Type::DropBegin));
  ASSERT_EQ("DropComplete", ToString(Type::DropComplete));

  ASSERT_EQ("AudioDeviceAdded", ToString(Type::AudioDeviceAdded));
  ASSERT_EQ("AudioDeviceRemoved", ToString(Type::AudioDeviceRemoved));

  ASSERT_EQ("SensorUpdate", ToString(Type::SensorUpdate));

  ASSERT_EQ("RenderTargetsReset", ToString(Type::RenderTargetsReset));
  ASSERT_EQ("RenderDeviceReset", ToString(Type::RenderDeviceReset));

  ASSERT_EQ("User", ToString(Type::User));

#if SDL_VERSION_ATLEAST(2, 0, 14)
  ASSERT_EQ("LocaleChanged", ToString(Type::LocaleChanged));

  ASSERT_EQ("ControllerTouchpadDown", ToString(Type::ControllerTouchpadDown));
  ASSERT_EQ("ControllerTouchpadUp", ToString(Type::ControllerTouchpadUp));
  ASSERT_EQ("ControllerTouchpadMotion", ToString(Type::ControllerTouchpadMotion));
  ASSERT_EQ("ControllerSensorUpdate", ToString(Type::ControllerSensorUpdate));
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  std::clog << "Event type example: " << Type::AppLowMemory << '\n';
}
